

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
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqbase.h>



//#####################################################################
//#####################################################################
//##################################################################### liqallpics :: by gary birkett
//#####################################################################
//#####################################################################









static int liqcell_scan_folder_for_images(liqcell *self,char *path)
{
		char *widgetpath = path;//"/media/mmc1/svn/liqbase/libliqbase/media/mer/Mer_files";
		DIR           *	dir_p;
		struct dirent *	dir_entry_p;
		char 			fn[FILENAME_MAX+1];
		char          * ft;
		dir_p = opendir( widgetpath );
		if(!dir_p)
		{
			liqapp_log("liqcell_scan_folder_for_images opendir failed: '%s'",widgetpath);
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
				liqapp_log("liqcell_scan_folder_for_images stat failed: '%s'",fn);
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
                    liqcell_propseti(c,"imageallowalpha",0);

					//if(self->childcount==4)
					//	liqcell_setselected(c, 1);

					//liqcell_setimage(  c ,  liqimage_cache_getfile( fn,0,0,1) );
					liqcell_propsets(c,"imagefilename",fn);

					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   widget_click);


					liqcell_child_insertsorted( self, c );




				}

			}
		}
		closedir(dir_p);

		//liqcell_handleradd(self,    "mouse",   widget_mouse);

}



//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################



liqcell *liqallpics_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqallpics","form", 800,480);

	if(self)
	{

		liqcell *body = liqcell_quickcreatevis("body","frame",0 ,0,   self->w,self->h);
        
        
        char buf[FILENAME_MAX];    snprintf(buf,sizeof(buf),"%s/.sketches",app.userdatapath);

		liqcell_scan_folder_for_images(body, buf );
        
        
                                   snprintf(buf,sizeof(buf),"%s/MyDocs/.images",app.homepath);
        
        
		liqcell_scan_folder_for_images(body, buf );

        // quicktest for kot images
        ///media/mmc1/svn/Vol.1/_Cover.jpg
        //liqcell_scan_folder_for_images(body, "/media/mmc1/svn/Vol.1" );

		liqcell_child_insert( self, body );


		liqcell_child_arrange_makegrid(body,1,1);

		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );


		//liqcell_handleradd(self,    "mouse",   float_mouse);
		//liqcell_handleradd(self,    "click",   float_click);


	}

	return self;
}
