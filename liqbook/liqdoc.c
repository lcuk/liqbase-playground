/* liqbase
 * Copyright (C) 2008 Gary Birkett
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*
 *
 * text document handler
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>


#include <liqbase/liqbase.h>
#include <liqbase/filebuf.h>
#include "liqdoc.h"
//##########################################################################	
//##########################################################################	docline class.  quick and dirty single line
//##########################################################################


//##########################################################################	

//##########################################################################	


int 					docline_init(struct docline *self,char *linedata,int linelength)
{
	// is it worth my while parsing the line now?
	//liqapp_log("docline_init, allocate a line %i",linelength);
	self->linelength = linelength;
	self->formatw=linelength;
	self->formath=1;
	
	self->linedata   = malloc(linelength+1);
	if(self->linedata==NULL)
	{
    	{ return liqapp_warnandcontinue(-1,"docline_init malloc line data failed"); }		
	}
	char *memres=memcpy(self->linedata,linedata,linelength);
	if(memres==NULL)
	{
    	{ return liqapp_warnandcontinue(-1,"docline_init memcpy failed"); }		
	}	
	// ensure its null terminated
	self->linedata[linelength]=0;
	

	return 0;
}
//##########################################################################	

int 					docline_close(struct docline *self)
{
	if(self->linedata){	free(self->linedata); self->linedata=NULL; }
	self->linelength = 0;
	return 0;
}



	


//##########################################################################	
//##########################################################################	doc class.  quick and dirty way to get a line oriented file
//##########################################################################	

//##########################################################################	


//##########################################################################	


int 					doc_appendline(struct doc *self,char *linedata,int linelength)
{
	// add the data as a new line

	//liqapp_log("doc_append, allocate a line %i",linelength);
	struct docline *line = (struct docline *)malloc(sizeof(struct docline));
	if(line==NULL)
	{
    	{ return liqapp_warnandcontinue(-1,"doc_appendline malloc line failed"); }		
	}
	
	//liqapp_log("doc_append, init the line");
	int err=docline_init(line,linedata,linelength);
	if(err)
	{
	   	{ return liqapp_warnandcontinue(-1,"doc_appendline line init failed"); }			
	}
	//liqapp_log("doc_append, link with neighbours");
	line->linkparent = self;
	line->linkprev   = self->linelast;
	line->linknext   = NULL;
	if(self->linelast)
		self->linelast->linknext = line;
	self->linecount++;
	if(self->linefirst==NULL)
		self->linefirst = line;
	self->linelast   = line;
	if(linelength>self->linelongest)
		self->linelongest = linelength;

/*	if(linelength==0)
	{
		liqapp_log("Short Line %i,%i:%s",self->linecount, linelength,line->linedata);
		//exit(0);
	}
	if(linelength>70)
	{
		liqapp_log("Long Line %i,%i:%s",self->linecount, linelength,line->linedata);
		exit(0);
	}
*/
	return 0;
}
	

//##########################################################################	

int 					doc_split_std(struct doc *self,char *data,int datalength)
{
	char *ch=data;
	char *ls=ch;
	int   ll=0;
	int pos;
	
	for(pos=0;pos<datalength;pos++)
	{
		switch(*ch)
		{
			case 10:
				ll++;
				ch++;
				// hit a newline, ls..ch is the line
				doc_appendline(self,ls,ll-1);	// take one off to remove the \n
				ls=ch;
				ll=0;
				break;
			default:
				ch++;
				ll++;
				break;
		}
		//if((self->linecount % 100)==0)
		//	liqapp_log("doc_init, ping now, %i lines",self->linecount);
	}
	if(ll)doc_appendline(self,ls,ll);
	return 0;
}


int 					doc_split_render(struct doc *self,char *data,int datalength)
{
	
	
	char *ch=data;
	char *ls=ch;
	int   ll=0;
	int pos;
	int x=0;
	int y=0;
	int w=0;
	self->rendertotw=0;
	self->rendertoth=0;
	
	//for(pos=0;pos<datalength;pos++)
	pos=0;
	while(pos<datalength)
	{
		//w=self->renderfont->glyphwidths[(int)*ch];
		w=liqfont_getglyphwidth( self->renderfont, (int)*ch);

		if((self->rendermarginright) && (x+w>self->rendermarginright)) 
		{
			if(x>800)
			{
				liqapp_log("mark ll=%i, x=%i rm=%i",ll,x,self->rendermarginright);
			}
			
			
			{
				{
					// we stepped over the mark.  newline now.
					if( isspace(*ch) ) //|| ispunct(*ch)) )
					{
						// advance it anyway, we have stepped over, but it wont really effect flow...
						while( isspace(*ch) )
						{
							ch++;
							pos++;		// inc cos we are
						}
					}
					else
					{
						// roll back only if we stepped over with an actual character
						char *startch=ch;
						int startpos=pos;
						int startx=x;
						while(ch>ls)
						{
							if(isspace(*ch))// || ispunct(*ch))
							{
								// found a break, jump for it
								while( isspace(*ch) )
								{
									ch++;
									pos++;
								}
								break;
							}
							else
							{
								// go back
								//x-=self->renderfont->glyphwidths[(int)*ch];
								x-=liqfont_getglyphwidth( self->renderfont, (int)*ch);
								ch--;
								pos--;
							}
						}
						if(ch<=ls)
						{
							ch=startch;
							pos=startpos;
							x=startx;
						}
					}
					ll=ch-ls;
					doc_appendline(self,ls,ll);
					self->linelast->formatw=x;
					self->linelast->formath=liqfont_textheight(self->renderfont);
					if(x>self->rendertotw)self->rendertotw=x;
					self->rendertoth+=liqfont_textheight(self->renderfont);
					x=0;
					y+=liqfont_textheight(self->renderfont);
					ls=ch;
					ll=0;
				}
			}
		}
		else
		{
			
			switch(*ch)
			{
				case 10:
					// hit a newline, ls..ch is the line
					doc_appendline(self,ls,ll);
					self->linelast->formatw=x;
					self->linelast->formath=liqfont_textheight(self->renderfont);
					if(x>self->rendertotw)self->rendertotw=x;
					self->rendertoth+=liqfont_textheight(self->renderfont);
					ll++;
					ch++;
					pos++;

					x=0;
					y+=liqfont_textheight(self->renderfont);
					ls=ch;
					ll=0;

					break;
				default:
					// Now,
					x=x+w;
					ch++;
					pos++;
					ll++;
					break;
			}
		}
		//if((self->linecount % 100)==0)
		//	liqapp_log("doc_init, ping now, %i lines",self->linecount);
	}
	if(ll)
	{
		doc_appendline(self,ls,ll);
					self->linelast->formatw=x;
					self->linelast->formath=liqfont_textheight(self->renderfont);
					if(x>self->rendertotw)self->rendertotw=x;
					self->rendertoth+=liqfont_textheight(self->renderfont);
	}
	liqapp_log("doc_init, finished now, %i lines",self->linecount);

	return 0;

}
int 					doc_init(struct doc *self,char *data,int datalength)
{
	self->linefirst   = NULL;
	self->linelast    = NULL;
	self->linecount   = 0;
	self->linelongest = 0;
	//liqapp_log("doc_init, splitting up %i bytes",datalength);
	int res=0;
	if(self->renderfont)
	{
		//liqapp_log("doc_init, using render mode split");
		res=doc_split_render(self,data,datalength);
	}
	else
	{
		//liqapp_log("doc_init, using std mode split");
		res=doc_split_std(self,data,datalength);
	}
	//liqapp_log("doc_init, finished now, %i lines",self->linecount);

	return res;

}
//##########################################################################	
int 					doc_initfromfilebuf(struct doc *self,struct filebuf *filebuf)
{
	int err=doc_init(self,filebuf->filedata,filebuf->filelength);
	if(err)
	{
    	{ return liqapp_warnandcontinue(-1,"doc_initfromfile couldnt init"); }				
	}	
	return 0;
}
//##########################################################################	
int 					doc_initfromfilename(struct doc *self,char *filename)
{
	struct filebuf filebuf;
	int err=filebuf_open(&filebuf,filename);
	if(err)
	{
    	{ return liqapp_warnandcontinue(-1,"doc_initfromfilename couldnt open file"); }				
	}
	err=doc_init(self,filebuf.filedata,filebuf.filelength);
	if(err)
	{
		filebuf_close(&filebuf);
    	{ return liqapp_warnandcontinue(-1,"doc_initfromfilename couldnt init"); }				
	}	
	filebuf_close(&filebuf);
	return 0;
}

//##########################################################################	
int						doc_close(struct doc *self)
{
	while(self->linefirst)
	{
		struct docline *line = self->linefirst;
		self->linefirst = line->linknext;
		docline_close(line);
		free(line);
	}
	self->linelast=NULL;
	self->linecount=0;
	self->linelongest=0;
	return 0;
}



