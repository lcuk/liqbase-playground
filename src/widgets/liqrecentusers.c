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

#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>



//#####################################################################
//#####################################################################
//##################################################################### liqrecentusers :: by gary birkett
//#####################################################################
//#####################################################################




	static int liqrecentusers_filter(liqcell *self, liqcellfiltereventargs *args, liqcell *liqrecentusers)
	{
		// using the filter provided (which might be blank)
		
        //liqapp_log("deep filter");
        
					int islike = 1;//liqcell_propgeti(  self, "filterlike", 1 );
		
		char *searchterm = NULL;
		
		if(args) args->resultoutof=0;
		if(args) args->resultshown=0;
		if(args) searchterm = args->searchterm;
        
        //liqapp_log("deep filter2");
		
		// examine each tag and if matches the search show it, otherwise dont..
        liqcell *body = liqcell_child_lookup( liqrecentusers,"body");
       
        //liqapp_log("deep filter3 %i",backplane==NULL);
		
		liqcell *c = liqcell_getlinkchild_visual(body);
		while(c)
		{
			if(searchterm && *searchterm)
			{

				//struct pagefilename pfn;
				//pagefilename_breakapart(&pfn,c->name);
				char *key = c->name;
              
                
               // liqapp_log("checking '%s' in '%s'",searchterm,key);

				int isok = (key!=NULL) && (*key |= 0);
				if(isok)
				{
					if(islike)
					{
						// anywhere in string
						isok = ( stristr(key,searchterm) != NULL );
					}
					else
					{
						// only from the start
						isok = ( c->name == stristr(key,searchterm) );
					}
				}

				if( isok ) // strstr(c->name,searchterm) )
				{
					// found a match!
					liqcell_setvisible(c,1);
					if(args) args->resultshown++;
				}
				else
				{
					// no match :(
					liqcell_setvisible(c,0);
				}
				if(args) args->resultoutof++;
			}
			else
			{
				// nothing to search for, show it
				liqcell_setvisible(c,1);
				if(args) args->resultoutof++;
				if(args) args->resultshown++;
			}

			c=liqcell_getlinknext_visual(c);
		}
		liqcell_setrect(body,   0,0,self->w,self->h);
		int cnt=liqcell_child_countvisible(body);
		if(cnt>=9)
			liqcell_child_arrange_makegrid(body,4,4);
		else
			liqcell_child_arrange_easytile(body);


		return 1;
	}













	static int widget_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("hmm why not clicking? %s",self->name);
		
		args->newdialogtoopen = self;//liqcell_child_lookup( self, "body" );
		//args->newdialogtoopen = liqcell_child_lookup( self, "body" );

		return 1;
	}













static liqcell *editoverlay_create(int w,int h)
{
	//

	liqcell *self = liqcell_quickcreatewidget("editoverlay","overlay", w,h);

	if(self)
	{
		liqcell *c;

					//liqcell_propseti(self,"levelofdetail",1);
					c = liqcell_quickcreatevis("sketching",   "picture",   w*0,0,w/4,h    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"imagefilename","media/lcuk_sig_headshot.png");
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   widget_click);
					liqcell_child_append( self, c );


					//liqcell *c;
					c = liqcell_quickcreatevis("barcode",   "picture",   w*0.25,0,w/4,h    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"imagefilename","media/barcode.png");
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   widget_click);
					liqcell_child_append( self, c );


					c = liqcell_quickcreatevis("tagging",   "picture",   w*0.5,0,w/4,h    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"imagefilename","media/tagging.png");
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   widget_click);
					liqcell_child_append( self, c );


					c = liqcell_quickcreatevis("more",   "picture",   w*0.75,0,w/4,h    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"imagefilename","media/more.png");
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   widget_click);
					liqcell_child_append( self, c );


			/*		c = liqcell_quickcreatevis("management",   "picture",   w*0.75,0,w/4,h    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"imagefilename","media/manage.png");
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   widget_click);
					liqcell_child_append( self, c );*/


			//liqcell_child_arrange_autoflow(self);
			//liqcell_child_arrange_easytile(self);

	}
	return self;
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
					liqcell_propsets(c,"imagefilename",fn);
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					liqcell_handleradd(c,    "click",   widget_click);


					liqcell_child_insertsorted( self, c );




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



liqcell *liqrecentusers_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqrecentusers","form", 800,480);

	if(self)
	{

		
		
		liqcell *body = liqcell_quickcreatevis("body",NULL,0 ,0,   self->w,self->h);

		//liqcell_scan_folder_for_images(body,widgetpath);

		liqcell_scan_folder_for_images(body,"/usr/share/liqbase/media/avatars");


		liqcell_child_insert( self, body );

		int cnt=0;
		liqcell *c=liqcell_lastchild(body);
		//liqcell *c=liqcell_getlinkchild(body);
		while(c)
		{
			if(liqcell_getvisible(c))
			{
				// work it!
				if(cnt++<9)
				{
					c->visible=1;
				}
				else
				{
				//	c->visible=0;
				}



			}
			//c=liqcell_getlinknext(c);
			c=liqcell_getlinkprev(c);
		}
		if(cnt>=9)
			liqcell_child_arrange_makegrid(body,4,4);
		else
			liqcell_child_arrange_easytile(body);
		// only show the most recent 12?

		c=liqcell_lastchild(body);
		//liqcell *c=liqcell_getlinkchild(self);
		while(c)
		{
			if(liqcell_getvisible(c))
			{
				// work it!


					liqcell *e = editoverlay_create(c->w,c->h*0.2);
					liqcell_setpos(e, 0, c->h*0.8);
					liqcell_child_insert( c, e );

			}
			//c=liqcell_getlinknext(c);
			c=liqcell_getlinkprev(c);
		}

		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );	
		liqcell_handleradd_withcontext(self,    "filter",   liqrecentusers_filter,self);

	}

	return self;
}

