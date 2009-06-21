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
 * Header for text documents
 *
 */


#ifndef LIQDOC_H
#define LIQDOC_H





#include <liqbase/liqfont.h>

#include <liqbase/filebuf.h>


//##########################################################################	
//##########################################################################	docline class.  quick and dirty single line
//##########################################################################

struct doc;	

//##########################################################################	

struct docline 
{ 	
	struct doc			*linkparent;	// link to our master
	struct docline		*linkprev;		// link to the previous
	struct docline		*linknext;		// link to the next
	
	char 				*linedata;		// ALLOCATED data (if modified, make sure you free it...)
	int					linelength;		// length of line
	int					formatw;
	int					formath;
};
//##########################################################################	


int 					docline_init(struct docline *self,char *linedata,int linelength);
//##########################################################################	

int 					docline_close(struct docline *self);

	


//##########################################################################	
//##########################################################################	doc class.  quick and dirty way to get a line oriented file
//##########################################################################	

struct docline;
	
//##########################################################################	

struct doc
{
	struct docline		*linefirst;		// first line in the document
	struct docline		*linelast;		// last line in the document
	int					linecount;		// total count of lines
	int					linelongest;	// longest line (in characters)
	
	liqfont				*renderfont;
	int					rendermarginright;
	int					rendertotw;
	int					rendertoth;
	//int					rendermarginbottom;
};

//##########################################################################	


int 					doc_appendline(struct doc *self,char *linedata,int linelength);

//##########################################################################	

int 					doc_split_std(struct doc *self,char *data,int datalength);

int 					doc_split_render(struct doc *self,char *data,int datalength);
int 					doc_init(struct doc *self,char *data,int datalength);
//##########################################################################	
int 					doc_initfromfilebuf(struct doc *self,struct filebuf *filebuf);
//##########################################################################	
int 					doc_initfromfilename(struct doc *self,char *filename);

//##########################################################################	
int						doc_close(struct doc *self);


#endif
