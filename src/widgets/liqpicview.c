

//  "/media/mmc1/svn/liqbase/libliqbase/media/jacobpics"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqbase.h>

//#####################################################################
//#####################################################################
//##################################################################### liqpicview :: by gary birkett 
//#####################################################################
//#####################################################################


	static int widget_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		//if(args->mez>0) return;
		// we only want mouseup
		
		//liqcell_easyrun( liqcell_getlinkancestor( self ) );


		liqcell_adjustpos(self,args->mdx,args->mdy);
		
		int liqcell_child_arrange_nooverlap(liqcell *self,liqcell *currentselection);
		
		int liqcell_child_arrange_gapfill(liqcell *self,liqcell *currentselection);
		
		
		liqcell_child_arrange_nooverlap( liqcell_getlinkparent(self), self );
		
	//	liqcell_child_arrange_gapfill( liqcell_getlinkparent(self), self );
		
		liqcell_child_arrange_nooverlap( liqcell_getlinkparent(self), self );


		liqcell_child_arrange_nooverlap( liqcell_getlinkparent(self), self );

		liqcell_child_arrange_nooverlap( liqcell_getlinkparent(self), self );
		
		liqcell_child_arrange_nooverlap( liqcell_getlinkparent(self), self );

		return 1;
	}		
		


liqcell *liqpicview_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqpicview","form", 800,480);

	if(self)
	{
		//liqcell_propsets(  self, "backcolor", "rgb(255,255,255)" );

		//char *widgetpath = "/media/mmc1/svn/liqbase/libliqbase/media/jacobpics";
		//char *widgetpath = "../media";
		char *widgetpath = "media/avatars";
		DIR           *	dir_p;
		struct dirent *	dir_entry_p;
		char 			fn[FILENAME_MAX+1];
		char          * ft;
		dir_p = opendir( widgetpath );			
		if(!dir_p)
		{
			liqapp_log("liqpicview_masterinit opendir failed: '%s'",widgetpath);
			return self;			// heh thanks kot :)
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
				liqapp_log("liqpicview_masterinit stat failed: '%s'",fn);
				return self;
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
					strcasecmp(ext,"png")==0  ||
					strcasecmp(ext,"jpg")==0  ||
					strcasecmp(ext,"jpeg")==0
				  )
				{
					
					
					liqcell *c = liqcell_quickcreatevis(ft,   "picture",   1,1,1,1    );
					liqcell_propseti(c,"lockaspect",1);
					
					//if(self->childcount==4)	
					//	liqcell_setselected(c, 1);
					
					//liqcell_setimage(  c ,  liqimage_cache_getfile( fn,0,0,1) );
					liqcell_propsets(c,"imagefilename",fn);
					
					liqcell_handleradd(c,    "mouse",   widget_mouse);
					
	
					liqcell_child_insert( self, c );
				}
			}
		}
		closedir(dir_p);
	}
	
	liqcell_child_arrange_easytile(self);
	
	liqcell_child_arrange_makegrid(self,6,6);
	
	/*
				
					liqcell *c = liqcell_quickcreatevis("test",   "picture",   0,0,10000,10008    );
					liqcell_propseti(c,"lockaspect",0);
					liqcell_propsets(c,"imagefilename","/media/mmc1/svn/liqbase/libliqbase/media/berlin-map-metro-big.png");
					liqcell_handleradd(c,    "mouse",   widget_mouse);
					liqcell_child_insert( self, c );
	*/				
	
	return self;
}

