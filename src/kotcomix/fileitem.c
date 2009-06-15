// this file is part of liqbase by Gary Birkett
		
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
				
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### fileitem :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * fileitem widget shown
 */	
static int fileitem_shown(liqcell *self,liqcelleventargs *args, void *context)
{
	char *fn = self->name;
	
	//liqapp_log("folderitem_shown statting: '%s'",fn);
	liqcell *filename = liqcell_child_lookup(self, "filename");
	liqcell *filesize = liqcell_child_lookup(self, "filesize");
	liqcell *filedate = liqcell_child_lookup(self, "filedate");
	liqcell *fileico = liqcell_child_lookup(self, "fileico");

		DIR           *	dir_p;
		struct dirent *	dir_entry_p;

			struct stat     statbuf;
			if(stat(fn , &statbuf) == -1)
			{
				liqapp_log("fileitem_shown stat failed: '%s'",fn);
				return -1;
			}
			char *ft=liqapp_filename_walkoverpath(fn);
			
			// got the information we need
			if ( S_ISDIR(statbuf.st_mode) )
			{
				//printf(" DIR  ");
				//liqcell_scan_folder_for_images(self,fn);	

				//	liqcell *c = liqcell_quickcreatevis(fn,   classtocreate,   1,1,1,1    );

				//	liqcell_child_insertsorted( self, c );
				
				
					liqcell_setcaption(fileico, "FOL");
					liqcell_setcaption(filename, ft);
					liqcell_setcaption(filesize, "");
					liqcell_setcaption(filedate,  ctime(&statbuf.st_mtime));

					//liqcell_propsets(  filename, "backcolor", "rgb(255,255,200)" );
			}
			else
			if ( S_ISREG(statbuf.st_mode) )
			{
				char *ext=liqapp_filename_walktoextension(fn);
				
				
				if(!ext || !*ext)
				{
					// nothing to see here..
				}			
				else
				if(
					strcasecmp(ext,"png")==0  ||
					strcasecmp(ext,"jpg")==0  ||
					strcasecmp(ext,"jpeg")==0
				  )
				{
					
					char buf[128];
					snprintf(buf,sizeof(buf),"%lld",(long long)statbuf.st_size);
					
					//liqcell_setcaption(fileico, ext);
					liqcell_setcaption(filename, ft);
					liqcell_setcaption(filesize, buf);
					
					liqcell_setcaption(filedate,  ctime(&statbuf.st_mtime));
					
					liqcell_propsets(  fileico, "imagefilename", fn );
					
					//liqcell_propsets(  filename, "backcolor", "rgb(255,200,255)" );

					//liqcell *c = liqcell_quickcreatevis(fn,   classtocreate,   1,1,1,1    );
					//liqcell_child_insertsorted( self, c );
					
				}
			}

}
/**	
 * fileitem widget refresh, all params set, present yourself to the user.
 */	
static int fileitem_refresh(liqcell *self,liqcelleventargs *args, void *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
}
/**	
 * fileitem_child_test_seek this function shows how to access members
 */	
	  
static void fileitem_child_test_seek(liqcell *self)
{	  
	liqcell *filename = liqcell_child_lookup(self, "filename");
	liqcell *filesize = liqcell_child_lookup(self, "filesize");
	liqcell *filedate = liqcell_child_lookup(self, "filedate");
	liqcell *fileico = liqcell_child_lookup(self, "fileico");
}	  
/**	
 * create a new fileitem widget
 */

// 20090615_014159 lcuk : not finger friendly version, suffix thin items with thin :)
liqcell *fileitem_create_thin()
{
	liqcell *self = liqcell_quickcreatewidget("fileitem", "form", 390, 30);
	if(!self) {liqapp_log("liqcell error not create 'fileitem'"); return NULL;  } 
	
	//############################# filename:label
	liqcell *filename = liqcell_quickcreatevis("filename", "label", 24, 4, 198, 22);
	liqcell_setfont(	filename, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
	liqcell_setcaption(filename, "filename" );
	//liqcell_propsets(  filename, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  filename, "backcolor", "rgb(255,255,255)" );
	liqcell_propseti(  filename, "textalign", 0 );
	liqcell_child_append(  self, filename);
	//############################# filesize:label
	liqcell *filesize = liqcell_quickcreatevis("filesize", "label", 226, 4, 70, 22);
	liqcell_setfont(	filesize, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(filesize, "filesize" );
	//liqcell_propsets(  filesize, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  filesize, "backcolor", "rgb(224,224,224)" );
	liqcell_propseti(  filesize, "textalign", 1 );
	liqcell_child_append(  self, filesize);
	//############################# filedate:label
	liqcell *filedate = liqcell_quickcreatevis("filedate", "label", 300, 4, 74, 22);
	liqcell_setfont(	filedate, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(filedate, "filedate" );
	//liqcell_propsets(  filedate, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  filedate, "backcolor", "rgb(224,224,224)" );
	liqcell_propseti(  filedate, "textalign", 0 );
	liqcell_child_append(  self, filedate);
	//############################# fileico:label
	liqcell *fileico = liqcell_quickcreatevis("fileico", "label", 4, 4, 18, 22);
	//liqcell_setfont(	fileico, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(fileico, "ico" );
	//liqcell_propsets(  fileico, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  fileico, "backcolor", "rgb(192,192,0)" );
	//liqcell_propseti(  fileico, "textalign", 0 );
	liqcell_child_append(  self, fileico);
	//liqcell_propsets(  self, "backcolor", "rgb(192,192,192)" );
	liqcell_handleradd(self, "refresh", fileitem_refresh );
	liqcell_handleradd(self, "shown", fileitem_shown );
	return self;
}

// 20090615_014159 lcuk : finger friendly version, suffix finger friendly items items with _finger :)
// 20090615_014245 lcuk : this is using the default constructor
// 20090615_014253 lcuk : once new ones are created and new suffixes become apparant it will work through
// 20090615_014318 lcuk : but these default constructors will remain as the failsafe
// 20090615_014329 lcuk : i will start making dllcache work on this part of the variation engine

liqcell *fileitem_create()
{
	liqcell *self = liqcell_quickcreatewidget("fileitem", "form", 128,128);
	if(!self) {liqapp_log("liqcell error not create 'fileitem'"); return NULL;  } 
	
	//############################# filename:label
	liqcell *filename = liqcell_quickcreatevis("filename", "label", 0,106, 128, 22);
	liqcell_setfont(	filename, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
	liqcell_setcaption(filename, "filename" );
	//liqcell_propsets(  filename, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  filename, "backcolor", "rgb(255,255,255)" );
	liqcell_propseti(  filename, "textalign", 2 );
	liqcell_child_append(  self, filename);
	//############################# filesize:label
	liqcell *filesize = liqcell_quickcreatevis("filesize", "label", -1,-1,1,1);
	liqcell_setfont(	filesize, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(filesize, "filesize" );
	//liqcell_propsets(  filesize, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  filesize, "backcolor", "rgb(224,224,224)" );
	liqcell_propseti(  filesize, "textalign", 1 );
	liqcell_child_append(  self, filesize);
	//############################# filedate:label
	liqcell *filedate = liqcell_quickcreatevis("filedate", "label", -1,-1,1,1);
	liqcell_setfont(	filedate, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(filedate, "filedate" );
	//liqcell_propsets(  filedate, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  filedate, "backcolor", "rgb(224,224,224)" );
	liqcell_propseti(  filedate, "textalign", 0 );
	liqcell_child_append(  self, filedate);
	//############################# fileico:label
	liqcell *fileico = liqcell_quickcreatevis("fileico", "label", 0,0, 128,106);
	//liqcell_setfont(	fileico, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(fileico, "ico" );
	//liqcell_propsets(  fileico, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  fileico, "backcolor", "rgb(192,192,0)" );
	//liqcell_propseti(  fileico, "textalign", 0 );
	liqcell_propseti(  fileico, "lockaspect", 1 );
	liqcell_child_append(  self, fileico);
	//liqcell_propsets(  self, "backcolor", "rgb(192,192,192)" );
	liqcell_handleradd(self, "refresh", fileitem_refresh );
	liqcell_handleradd(self, "shown", fileitem_shown );
	return self;
}
