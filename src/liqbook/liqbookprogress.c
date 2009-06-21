#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>









#include <liqbase/liqbase.h>



















static char *liqbookprogress_historyfilename = "liqbase_bookhistory.dat";

struct liqbookprogressitem
{
	char *		bookname;
	int		 	booksize;
	int		 	bookupto;
};


static struct liqbookprogressitem *recentbooklist=NULL;	// buffer for the book history
static int 						recentbookcount=0;		// how many slots are used
static int 						recentbooktotal=0;		// total number available

void liqbookprogress_shutdown()
{
	if(recentbooktotal>0)
	{
		while(recentbookcount>0)
		{
			recentbookcount--;
			free(recentbooklist[recentbookcount].bookname);
			//free(recentbooklist[recentbookcount].booksize);
			//free(recentbooklist[recentbookcount].bookupto);
		}
		free((void*)recentbooklist);
		recentbooklist=NULL;
		recentbookcount=0;
		recentbooktotal=0;
		
	}	
}

void liqbookprogress_add(char *name,int size, int upto)
{
				if(recentbookcount < recentbooktotal)
				{
					// we can add this book now
					recentbooklist[recentbookcount].bookname = strdup(name);
					recentbooklist[recentbookcount].booksize = size;
					recentbooklist[recentbookcount].bookupto = upto;
					
					recentbookcount++;
				}	
}


int liqbookprogress_startup()
{
	// book file format is simple..
	if(recentbooktotal>0)
	{
		// already open :)
		return 0;
	}
	
	recentbooktotal=256;
	recentbookcount=0;
	
	recentbooklist = (struct liqbookprogressitem *) malloc( sizeof(struct liqbookprogressitem) * recentbooktotal );
	if(!recentbooklist)
	{
		// fail
		liqapp_log("liqbookprogress could not alloc memory");
		recentbooktotal=0;
		recentbookcount=0;
		return -1;
	}
	
	
	char buf[FILENAME_MAX+1];
	snprintf(buf,FILENAME_MAX,"%s/%s",app.userdatapath,liqbookprogress_historyfilename);
	
	
	FILE *ff = fopen(buf,"r");
	if(!ff)
	{
		liqapp_log("liqbookprogress could not open history file to parse");
		return -2;
	}
	char linebuf[2048];
	while(!feof(ff))
	{
		char *linedata = fgets(linebuf,2048,ff);
		if(linedata)
		{
			// we are good to go :)
			// remember to remove the \r\n
			char *t=linedata;
			while(t)
			{
				if(*t=='\r' || *t=='\n'){ *t=0; break; }
				t++;
			}
			
			
			char *cols[32];
			int colcount=0;
			{
				char *indat=linedata;
				while(*indat && colcount<32)
				{
					char *p=strchr(indat,'\t');
					if(p)
					{
						//liqapp_log("col: %i,%s",colcount,indat);
						*p=0;
						cols[colcount++] = strdup(indat);
						indat=p+1;
					}
					else
					{
						// all the way to the end
						cols[colcount++] = strdup(indat);
						
						break;					
					}
				}
			}
			
			if(colcount==3)
			{
				// w0000t!
				if(recentbookcount < recentbooktotal)
				{
					// we can add this book now
					recentbooklist[recentbookcount].bookname = strdup( cols[0] );
					recentbooklist[recentbookcount].booksize = atoi(   cols[1] );
					recentbooklist[recentbookcount].bookupto = atoi(   cols[2] );
					recentbookcount++;
					
					//liqapp_log(">>>> %i,%s",colcount,linedata);
				}
			}
			// free the columns..
			while(colcount)
			{
				free( cols[--colcount] );
			}
		}
	}
	fclose(ff);
	
	return 0;
}





void liqbookprogress_finishedreading_storeposition(char *bookfilename,int filelength,int readupto)
{
	liqapp_log("liqbookprogress finished reading: '%s',%i,%i",bookfilename,filelength,readupto);
	// store away this as the most recent book
	if(liqbookprogress_startup()!=0)
	{
		// shit
		liqapp_log("liqbookprogress not available");
		return;
	}
	
	char buf[FILENAME_MAX+1];
	snprintf(buf,FILENAME_MAX,"%s/%s",app.userdatapath,liqbookprogress_historyfilename);
	
	FILE *ff=fopen(buf,"a");
	if(!ff)
	{
		liqapp_log("liqbookprogress couldn't append");
		return;
	}
	fprintf(ff,"%s\t%i\t%i\n",bookfilename,filelength,readupto);
	fclose(ff);
	
	
	// horrid way to reload.. especially when i could just add one, but its simpler than updating from the middle of the list for now
	liqbookprogress_shutdown();
	liqbookprogress_startup();
	
	
	//liqbookprogress_add(bookfilename,filelength,readupto);
	
}

char * liqbookprogress_getmostrecent()
{
	if(liqbookprogress_startup()!=0)
	{
		// shit
		return NULL;
	}
	if(recentbookcount==0)
	{
		return NULL;		
	}
	return recentbooklist[recentbookcount-1].bookname;
}

int liqbookprogress_startreading_lookupposition(char *bookfilename,int *storedfilelength,int *storedreadupto)
{
	*storedfilelength=0;
	*storedreadupto=0;
	// get the info about the named book
	// if we need to read the progress file, fair enough
	if(liqbookprogress_startup()!=0)
	{
		// shit
		return 0;
	}
	
	if(recentbookcount==0)
	{
		// nothing available
	//		liqapp_log("liqbookprogress start reading: '%s', *unknown.empty*",bookfilename);
		return 0;
	}
	
	int idx = recentbookcount-1;
	while(idx>=0)
	{
		if(strncasecmp(recentbooklist[idx].bookname, bookfilename, FILENAME_MAX)==0)
		{
			// found it!!!
			*storedfilelength=recentbooklist[idx].booksize;
			*storedreadupto=recentbooklist[idx].bookupto;
			liqapp_log("liqbookprogress start reading: '%s',%i,%i",bookfilename,*storedfilelength,*storedreadupto);
			return 1;
			
		}
		idx--;
	}
	//		liqapp_log("liqbookprogress start reading: '%s', *unknown*",bookfilename);
	return 0;
}
