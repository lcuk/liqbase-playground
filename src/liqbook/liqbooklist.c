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
//##################################################################### liqbooklist :: by gary birkett
//#####################################################################
//#####################################################################





	static int item_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		//liqapp_log("general click");
		//args->newdialogtoopen = self;
        if(liqcell_getselected(self))
        {
			liqcell_setselected(self,0);
			liqcell_propremoves(self, "textcolor"   );
			liqcell_propremoves(self, "backcolor"   );
			//liqcell_propremoves(self, "bordercolor" );
        }
        else
        {
			liqcell_setselected(self,1);
			liqcell_propsets(self, "textcolor",   "rgb(0,255,0)" );
			liqcell_propsets(self, "backcolor",   "rgb(0,0,40)" );
			//liqcell_propsets(self, "bordercolor", "rgb(255,255,255)" );
        }
		return 1;
	}





static int scan_folder_for_contents(liqcell *self,char *path)
{
	
	liqcell *body = liqcell_child_lookup(self,"body");
	
		char *widgetpath = path;
		DIR           *	dir_p;
		struct dirent *	dir_entry_p;
		char 			fn[FILENAME_MAX+1];
		char          * ft;
		dir_p = opendir( widgetpath );			
		if(!dir_p)
		{
			liqapp_log("scan_folder_for_contents opendir failed: '%s'",widgetpath);
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
				liqapp_log("scan_folder_for_contents stat failed: '%s'",fn);
				return -1;
			}
			// got the information we need
			if ( S_ISDIR(statbuf.st_mode) )
			{
				//printf(" DIR  ");
				scan_folder_for_contents(self,fn);	
			}
			else
			if ( S_ISREG(statbuf.st_mode) )
			{
				char *ext=liqapp_filename_walktoextension(ft);
				if(!ext || !*ext)
				{
					// nothing to see here..
				}

				else
				if(
					strcasecmp(ext,"txt")==0 ||
					strcasecmp(ext,"rtf")==0 ||
					strcasecmp(ext,"doc")==0 ||
					strcasecmp(ext,"pdf")==0
				  )
				{


					
					liqfont *font = liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (34 ), 0);
					int ttw = liqfont_textwidth(font,fn);
					int tth = liqfont_textheight(font);
					
					
					
					liqcell *c = liqcell_quickcreatevis(fn,   "book",   0,0,ttw*1.2,tth    );
					
					//liqcell_propseti(c,"lockaspect",1);
					
					liqcell_setfont(	c, font );
					
					//liqcell_propseti(c,"autosize",1);
					liqcell_propseti(c,"textalign",0);
					//liqcell_propseti(c,"lockaspect",1);
					//liqcell_propsets(c,"imagefilename",fn);
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					liqcell_handleradd(c,    "click",   item_click);

					liqcell_child_insertsorted( body, c );



				}
			}
		}
		closedir(dir_p);
		
	return 0;
}


//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################





	static int liqbooklist_filter(liqcell *self, liqcellfiltereventargs *args, void *context)
	{
		// using the filter provided (which might be blank)
		
					int islike = 1;//liqcell_propgeti(  self, "filterlike", 1 );
		
		char *searchterm = NULL;
		
		if(args) args->resultoutof=0;
		if(args) args->resultshown=0;
		if(args) searchterm = args->searchterm;
		
		// examine each tag and if matches the search show it, otherwise dont..
		liqcell *body = liqcell_child_lookup(self,"body");
		
		liqcell *c = liqcell_getlinkchild(body);
		while(c)
		{
			if(liqcell_isclass(c,"book"))
			{
				if(searchterm && *searchterm)
				{

					//struct pagefilename pfn;

					//pagefilename_breakapart(&pfn,c->name);
					
					
					char *key = c->name;


					
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
					
					if(!isok)
					{
						// see if we can show it anyway
						if(liqcell_getselected(c)) isok=1;
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
			}
			c=liqcell_getlinknext(c);
		}
		liqcell_setrect(body,   0,0,self->w,self->h);
		liqcell_child_arrange_easycol(body);

		return 1;
		
	}


	static int liqbooklist_refresh(liqcell *self, liqcelleventargs *args, void *context)
	{

		liqcell *body = liqcell_child_lookup(self,"body");
		liqcell_setrect(body,   0,0,self->w,self->h);
		//liqcell_setsize(body,   self->w,self->h);
		liqcell_child_arrange_easycol(body);
		
		return 1;
	}
	


	static int liqbooklist_resize(liqcell *self, liqcelleventargs *args, void *context)
	{

		liqcell *body = liqcell_child_lookup(self,"body");
		liqcell_setrect(body,   0,0,self->w,self->h);
		//liqcell_setsize(body,   self->w,self->h);
		liqcell_child_arrange_easycol(body);
		
		return 1;
	}
	


liqcell *liqbooklist_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqbooklist","form", 800,480);

	if(self)
	{
	
		liqcell *body = liqcell_quickcreatevis("body",NULL,0 ,0,   self->w,self->h);
		
		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_insert( self, body );
		
		scan_folder_for_contents(self, "/home/user" );
		scan_folder_for_contents(self, "/media/mmc1" );
		scan_folder_for_contents(self, "/media/mmc2" );
		liqcell_child_arrange_easycol(body);
		
		liqcell_handleradd(self,    "refresh",   liqbooklist_refresh);
		liqcell_handleradd(self,    "resize",   liqbooklist_resize);
		liqcell_handleradd(self,    "filter",   liqbooklist_filter);

		liqbooklist_resize(self,NULL,NULL);

	}

	return self;
}

