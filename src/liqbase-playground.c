/**
 * @file	vworld.c
 * @author  Gary Birkett
 * @brief 	This is the main program file
 * 
 * Copyright (C) 2008 Gary Birkett
 *
 * @section LICENSE
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
 *
 */

// #
// # test of font rendering
// #

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <X11/keysym.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <pthread.h>
#include <sched.h>

#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easypaint.h>
#include <liqbase/liqcell_dllcache.h>
#include <liqbase/liqcell_prop.h>




//liqcell *newsketches;

liqcell *universe;			// global universal root
liqcell *mirror;				// mirror of the universe

int liqcell_parse_liqbrain(liqcell *self,char *inputdata);
int liqcell_parse_liqbrain_filename(liqcell *self,char *filename);
int liqsimpletest_run();


/*

#include <X11/extensions/Xrandr.h>

static Rotation xrotation_get()
{
  XRRScreenConfiguration *rr_screen;
  Rotation current_rotation;
  Display *dpy;
  int screen;

  dpy = XOpenDisplay (NULL);
  screen = DefaultScreen (dpy);

  rr_screen = XRRGetScreenInfo (dpy, RootWindow (dpy, screen));
  XRRRotations (dpy, screen, &current_rotation);

  XRRFreeScreenConfigInfo (rr_screen);

  XCloseDisplay (dpy);

  return current_rotation;
}


static void
xrotation_set (Rotation rotation)
{
  Rotation sc_rotation;
  XRRScreenConfiguration *scr_config;
  Rotation current_rotation;
  int size;
  int i, mode, fb;
  Display *dpy;
  int screen;

  dpy = XOpenDisplay (NULL);
  screen = DefaultScreen (dpy);

  scr_config = XRRGetScreenInfo (dpy, RootWindow (dpy, screen));
  size = XRRConfigCurrentConfiguration (scr_config, &current_rotation);

  XRRSetScreenConfig (dpy, scr_config, RootWindow (dpy, screen), size, rotation, CurrentTime);
  XRRFreeScreenConfigInfo (scr_config);
  XCloseDisplay (dpy);
}




// xrotation_set(RR_Rotate_270);
// RR_Rotate_180
// RR_Rotate_90
// RR_Rotate_0



 */




































       
int superrun();
	   
	   
/**
 * Shuts down liqbase-playground, logs the shutdown, closes canvas, close the app
 *
 */
void closeall()
{
static int alreadyclosing=0;
	if(alreadyclosing++)return;
	liqapp_log("liqbase closing");
	liqapp_log("Closing canvas");
	liqcanvas_close();
	liqapp_log("closing app");
	liqapp_close();
	liqapp_log("goodbye.");
	alreadyclosing=0;
}

/**
 * The handler for SIGINT, SIGTERM, and SIGHUP which handles app shutdown
 * @param sig The Signal to handle
 * 
 */
void     signalhandler(int sig)
{
	liqapp_log("%s signal detected, closing",liqapp_gettitle());
	closeall();
	signal(SIGINT, SIG_DFL);
	kill(getpid(), SIGINT);
}

//##################################################################################
//##################################################################################
//##################################################################################

int main (int argc, char* argv[])
{
	// hello intrepid developer, this is the start :)

	//########################################################## configure our catchall
    signal(SIGINT, signalhandler);
	signal(SIGTERM, signalhandler);
	signal(SIGHUP, signalhandler);

	//########################################################## prepare the app

	if(liqapp_init(   argc,argv ,"liqbase-playground" ,"0.2") != 0)
	{
		{ return liqapp_errorandfail(-1,"liqapp_init failed"); }
	}

	//########################################################## open the screen


#ifdef USE_MAEMO
	//xrotation_set(RR_Rotate_90);
	//if(0!=liqcanvas_init( 480,800, 1))

	//xrotation_set(RR_Rotate_0);
	if(0!=liqcanvas_init( 800,480, 1))
    
    
	//if(0!=liqcanvas_init( 640,480, 1))
	//if(0!=liqcanvas_init( 400,240, 1))

#else
	if(0!=liqcanvas_init( 1024,768, 1))

#endif
	{
		liqapp_errorandfail(-1,"canvas Init");
		closeall();
		return -1;
	}

	//########################################################## run our application

	//liqsimpletest_run();
	
	superrun();


    
    closeall();

	//########################################################## we are done :)

	// goodbye, see you again
	
	
	system("browser --url=http://liqbase.net/playground.html");
	
    

	return 0;
}

//##################################################################################
//##################################################################################
//##################################################################################








	static int widget_mouse(liqcell *self, liqcellmouseeventargs *args)
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


	static int widget_dirty(liqcell *self, liqcelleventargs *args)
	{
		//args->newdialogtoopen = liqcell_getcontent( self );

		liqcell_setdirty(mirror,1);
		return 1;
	}
 


	static int widget_click(liqcell *self, liqcellclickeventargs *args)
	{
		args->newdialogtoopen = liqcell_getcontent( self );

		return 1;
	}




/**
 * Liqbase Framework test run function that runs the test app 
 *
 */



int superrun()
{
	universe = liqcell_quickcreatenameclass("universe","universe");
	
		mirror = liqcell_quickcreatevis("liqbase-playground",NULL,0,0, 800,480);
		liqcell_child_insert(universe,mirror);
		
		
	dllcacheitem *dllcache = NULL;
	int           dllcache_used = 0;
	
	dllcache = dllcache_getbase();
	if(!dllcache)
	{
		liqapp_log("could not init dllcache");
		return -1;
	}
	
	


int widgetcount=0;
liqcell *widgetrecent=NULL;
	
	dllcache_used = dllcache_getused();
	
	int idx=0;
	for(idx=0;idx<dllcache_used;idx++)
	{
		dllcacheitem * dllcacheitem = &dllcache[ idx ];
		
		// examine this item

		int isok=0;
		char *showwidget_arg = liqapp_getopt_str("showwidget",NULL);
        
        if(!showwidget_arg) showwidget_arg="tagcloud,liqcontrolpanel,liqrecentpics,liqcalendar,liqrecentphotos,ciroclock_minutes,liqtop,liqrecentsketches,liqrecentusers,liqaccelview,liqbook";
        
		
		if(showwidget_arg && *showwidget_arg)
		{
			isok=0;
			char buf[1024];
			snprintf(buf,sizeof(buf),"%s",showwidget_arg);
			//#####################
			char *tok = strtok(buf, ",");
			while (tok)
			{
				//liqapp_log("testing param: '%s' == '%s'",dllcacheitem->key,tok);
				if( (strcasecmp(dllcacheitem->key,tok)==0) )
				{
					// ok to show
					isok=1;
					break;
					}
				else
				{
					// no match, leave isok=0;
				}
				tok = strtok(NULL, ",");
			}
		}
		else
		{
			isok=1;
		}


		if(isok)
		{
			
			
			
			
			
			
			
			
			
			
			// try to actually create the instance now
			
			liqcell *d=dllcache_runconstructor(dllcacheitem->key);
			if(d)
			{
				//savethumb(d);
				
				liqcell_handleradd(d,    "dirty",   widget_dirty);
				liqapp_log("waaaa2 '%s'",d->name);

				char buf[128]; snprintf(buf,128,"%s1",liqcell_getname(d));
				liqcell *e=NULL;
				
				if(liqcell_propgeti(d,"universeliveview",0))
				{
					// live view
					e=d;
				}
				else
				{				
					e=liqcell_quickcreatevis(buf,NULL,0,0, 50,50) ;
					liqcell_setcontent( e, d);
					liqcell_propseti(e,"lockaspect",1);
				}

				//! Add the handlers
				//liqcell_handleradd(e,    "mouse",   widget_mouse);
				liqcell_handleradd(e,    "click",   widget_click);
				
				liqcell_child_insert( mirror,  e);
				
				widgetrecent=d;
				
				widgetcount++;
			}
		}
	}
	liqcell_child_arrange_easytile(mirror);
	//! Set the background image that we see


	// COMMENTED OUT BY ZACH: liqbrain was put out of use currently because of sqlite3 dependencies
	// int liqbrain_test();
	
	// liqbrain_test();

	
	if(widgetcount==1 && widgetrecent)
	{

		liqapp_log("Starting single");
		liqcell_easyrun( widgetrecent );		
	}
	else
	{
	

		liqcell_setimage(  mirror ,  liqimage_cache_getfile( "media/liqbase_back2.jpg",0,0,1) );
		liqapp_log("Starting global");

	//	liqcell_easyrun( liqcell_quickcreatevis("welcome", "liqwelcome", 0,0, 0,0) );
	


		liqcell_easyrun( mirror );
	}
	
	//liqcell_easyrun( liqcell_quickcreatevis("liqgoodbye", "liqgoodbye", 0,0, 0,0) );
	
	
	

	liqapp_log("completed");
	liqcell_release(universe);		
	return 0;
}
