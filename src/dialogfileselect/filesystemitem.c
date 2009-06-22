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
//##################################################################### filesystemitem :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * filesystemitem widget shown
 */	
static int filesystemitem_shown(liqcell *self,liqcelleventargs *args, void *context)
{
	char *fn = self->name;

	liqcell *folderico = liqcell_child_lookup(self, "folderico");
	liqcell *foldersize = liqcell_child_lookup(self, "foldersize");
	liqcell *foldername = liqcell_child_lookup(self, "foldername");

	//liqapp_log("filesystemitem_shown statting: '%s'",fn);

		DIR           *	dir_p;
		struct dirent *	dir_entry_p;

			struct stat     statbuf;
			if(stat(fn , &statbuf) == -1)
			{
				liqapp_log("filesystemitem_shown stat failed: '%s'",fn);
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
				
				
					liqcell_setcaption(folderico, "FOL");
					liqcell_setcaption(foldername, ft);
					liqcell_setcaption(foldersize, "");
					
					///home/user/svn/liqbase-playground/src/media/quickicons/folder.png
					liqcell_propsets(  folderico, "imagefilename", "/usr/share/liqbase/media/quickicons/folder.png");
					//liqcell_propsets(  folderico, "backcolor", "rgb(0,192,0)" );
					
					liqcell_propsets(  foldername, "textcolor", "rgb(255,255,200)" );

					//liqcell_propsets(  foldername, "backcolor", "rgb(0,40,0)" );
					return 0;
			}


			if ( S_ISREG(statbuf.st_mode) )
			{
				char *ext=liqapp_filename_walktoextension(fn);
				
				
				if(!ext || !*ext)
				{
					// nothing to see here..
					//liqcell_setcaption(folderico, "FIL");
					liqcell_setcaption(foldername, ft);
					liqcell_setcaption(foldersize, "");	
					liqcell_propsets(  folderico, "imagefilename", "/usr/share/liqbase/media/quickicons/txt.png");
					
					liqcell_propsets(  foldername, "textcolor", "rgb(200,200,200)" );
				}
				else
				//if(
				//	strcasecmp(ext,"png")==0  ||
				//	strcasecmp(ext,"jpg")==0  ||
				//	strcasecmp(ext,"jpeg")==0
				//  )
				{
					//liqcell_setcaption(folderico, ext);
					liqcell_setcaption(foldername, ft);
					liqcell_setcaption(foldersize, "");
					
					//liqcell_propsets(  foldername, "backcolor", "rgb(0,0,40)" );
					
					//liqcell_propsets(  folderico, "imagefilename", fn );
					liqcell_propsets(  folderico, "imagefilename", "/usr/share/liqbase/media/quickicons/txt.png");
					
					//liqcell_propsets(  foldername, "backcolor", "rgb(255,200,255)" );

					//liqcell *c = liqcell_quickcreatevis(fn,   classtocreate,   1,1,1,1    );
					//liqcell_child_insertsorted( self, c );
					
				}
				
				return 0;
				
			}
				
		


			// mmm
				//liqcell_setcaption(folderico, ext);
				liqcell_setcaption(foldername, ft);
				liqcell_setcaption(foldersize, "");
				
				//liqcell_propsets(  foldername, "backcolor", "rgb(0,0,40)" );
				
				//liqcell_propsets(  folderico, "imagefilename", fn );
				liqcell_propsets(  folderico, "imagefilename", "/usr/share/liqbase/media/quickicons/txt.png");
				
				liqcell_propsets(  foldername, "textcolor", "rgb(255,200,200)" );



 	
}
/**	
 * filesystemitem widget refresh, all params set, present yourself to the user.
 */	
static int filesystemitem_refresh(liqcell *self,liqcelleventargs *args, void *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
}
/**	
 * filesystemitem_child_test_seek this function shows how to access members
 */	
	  
static void filesystemitem_child_test_seek(liqcell *self)
{	  
	liqcell *folderico = liqcell_child_lookup(self, "folderico");
	liqcell *foldersize = liqcell_child_lookup(self, "foldersize");
	liqcell *foldername = liqcell_child_lookup(self, "foldername");
}	  
/**	
 * create a new filesystemitem widget
 */

//####################################################################################

static int filesystemitem_resize_big(liqcell *self, liqcelleventargs *args, void *context)
{
	liqcell *folderico = liqcell_child_lookup(self, "folderico");
	liqcell *foldersize = liqcell_child_lookup(self, "foldersize");
	liqcell *foldername = liqcell_child_lookup(self, "foldername");

// could I use a style parameter here?
// 

	liqcell_setrect(folderico, 4,(self->h-46)/2, 46,46);
	liqcell_setrect(foldersize, 0,0,0,0);
	liqcell_setrect(foldername, 50,0,self->w-50,self->h);
	return 1;
}


// 20090615_014159 lcuk : big version, suffix big items with big :)
liqcell *filesystemitem_create_big()
{
	liqcell *self = liqcell_quickcreatewidget("filesystemitem", "form", 342, 60);
	if(!self) {liqapp_log("liqcell error not create 'filesystemitem'"); return NULL;  } 
	
	//############################# folderico:label
	liqcell *folderico = liqcell_quickcreatevis("folderico", "label", -1,-1,1,1);
	//liqcell_setfont(	folderico, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(folderico, "ico" );
	//liqcell_propsets(  folderico, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  folderico, "backcolor", "rgb(192,192,0)" );
	//liqcell_propseti(  folderico, "textalign", 0 );
	liqcell_child_append(  self, folderico);
	//############################# foldersize:label
	liqcell *foldersize = liqcell_quickcreatevis("foldersize", "label", -1,-1,1,1);
	liqcell_setfont(	foldersize, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(foldersize, "foldersize" );
	//liqcell_propsets(  foldersize, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  foldersize, "backcolor", "rgb(224,224,224)" );
	liqcell_propseti(  foldersize, "textalign", 0 );
	liqcell_child_append(  self, foldersize);
	//############################# foldername:label
	liqcell *foldername = liqcell_quickcreatevis("foldername", "label", -1,-1,1,1);
	liqcell_setfont(	foldername, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (40), 0) );
	liqcell_setcaption(foldername, "foldername" );
	//liqcell_propsets(  foldername, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  foldername, "backcolor", "rgb(255,255,255)" );
	liqcell_propseti(  foldername, "textalign",  0 );
	liqcell_propseti(  foldername, "textaligny", 2 );
	liqcell_child_append(  self, foldername);
	//liqcell_propsets(  self, "backcolor", "rgb(0,40,0)" );
	liqcell_handleradd(self, "refresh", filesystemitem_refresh );
	liqcell_handleradd(self, "shown", filesystemitem_shown );
	liqcell_handleradd(self, "resize", filesystemitem_resize_big );
	
	liqcell_handlerrun(self, "resize", NULL );
	return self;
}

liqcell *filesystemitem_create()
{
	return filesystemitem_create_big();
}
