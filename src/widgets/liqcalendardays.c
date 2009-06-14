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
#include <liqbase/liqcell_dllcache.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqcell_arrange.h>



	
//#####################################################################
//#####################################################################
//##################################################################### liqcalendardays :: by gary birkett 
//#####################################################################
//#####################################################################




	static int widget_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		args->newdialogtoopen = self;//liqcell_child_lookup( self, "body" );
		return 1;
	}

static liqcell *quickdialog_create()
{
	liqcell *self = liqcell_quickcreatewidget("editoverlay","edit", 800,480);
	if(self)
	{
		liqcell *c;
					c = liqcell_quickcreatevis("sketching",   "picture",   0,0,   800,480    );
					liqcell_propseti(c,"lockaspect",1);					
					liqcell_propsets(c,"imagefilename","media/lcuk_sig_headshot.png");
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   edit_click);
					liqcell_child_append( self, c );
	}
	return self;
}
	
		
	
	int edit_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("hello click edit!");
		liqcell *mydialog = quickdialog_create();
		liqcell_easyrun(mydialog);
		return 1;
	}	
	
	

static int liqcell_scan_folder_for_images(liqcell *self,char *path)
{
		char *widgetpath = path;
		DIR           *	dir_p;
		struct dirent *	dir_entry_p;
		char 			fn[FILENAME_MAX+1];
		char          * ft;
		dir_p = opendir( widgetpath );			
		if(!dir_p)
		{
			liqapp_log("liqcell_scan_folder_for_images opendir failed: '%s'",widgetpath);
			return -1;			// heh thanks kot :)
		}				
		while( NULL != (dir_entry_p = readdir(dir_p)))
		{
			if( dir_entry_p->d_name[0]=='.' )
				continue;
			
			ft=dir_entry_p->d_name;
			
			snprintf(fn , FILENAME_MAX , "%s/%s", widgetpath , ft);
			
			struct stat     statbuf;
			if(stat(fn, &statbuf) == -1)
			{
				liqapp_log("liqcell_scan_folder_for_images stat failed: '%s'",fn);
				return -1;
			}
			// got the information we need
			if ( S_ISREG(statbuf.st_mode) )
			{
				char *ext=liqapp_filename_walktoextension(ft);
				if(!ext || !*ext)
				{
					// nothing to see here..
				}

				else
				if(
					strcasecmp(ext,"page")==0 ||
					strcasecmp(ext,"sketch")==0 
				  )
				{
					
					struct pagefilename pfn;

					//if(	pagefilename_breakapart(&pfn,ft) == 0)
					{
						// got it ok, lets confirm...
				
						//liqapp_log("pagefilename: ok  path:'%s', dat:'%s', cls:'%s', tit:'%s'",pfn.filepath,pfn.filedate,pfn.fileclass,pfn.filetitle);
						
						
						//char buf[FILENAME_MAX];
						//pagefilename_rebuild(&pfn,buf,sizeof(buf));

						liqcell *c = liqcell_quickcreatevis(fn,   "sketch",   1,1,1,1    );
						liqcell_propseti(c,"lockaspect",1);
						liqcell_propsets(c,"sketchfilename",fn);
	
						liqcell_setfont(	c, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (16), 0) );
						liqcell_setcaption(c, ft );
						liqcell_propsets(  c, "textcolor", "rgb(100,100,0)" );
						//liqcell_propsets(  c, "bordercolor", "rgb(0,64,0)" );


						liqcell_child_insertsortedbyname( self, c,0);
					}
				}
			}
		}
		closedir(dir_p);
}



//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################



liqcell *liqcalendardays_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqcalendardays","form", 800,480);

	if(self)
	{
		liqcell *body = liqcell_quickcreatevis("body","frame",0 ,0,   self->w,self->h);
		
		char buf[FILENAME_MAX];    snprintf(buf,sizeof(buf),"%s/.cal",app.userdatapath);
		
		liqcell_scan_folder_for_images(body,buf);
		
		liqcell_child_insert( self, body );
		int cnt=0;
		liqcell *c=NULL;
		liqcell_child_arrange_makegrid(body,3,3);
		c=liqcell_lastchild(body);
		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		//liqcell_handleradd(self,    "click",   float_click);
	}
	
	return self;
}
