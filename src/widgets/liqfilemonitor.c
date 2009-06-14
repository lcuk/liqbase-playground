// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_dllcache.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
//#include "liqcell_arrange.h"


// c inotify api example from here
//http://darkeside.blogspot.com/2007/12/linux-inotify-example.html
// 20090516_125345 lcuk : converted to be visible in a liq window


int liqfilemonitor_run(liqcell *liqfilemonitor);


	static int timer_tick(liqcell *self, liqcellmouseeventargs *args, liqcell *context)
	{
		liqcell_propseti(self,"timerinterval", 32767 );
		liqcell_setenabled(self,0);
		// now, run the channel? :D
		//liqfilemonitor_run((liqcell*)self->tag);
		liqfilemonitor_run(context);
		
		return 0;
	}





/**	
 * create a new liqfilemonitor widget
 */	
liqcell *liqfilemonitor_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqfilemonitor", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqfilemonitor'"); return NULL;  } 
	
	//############################# buttonchannels:commandbutton
	//liqcell *buttonchannels = liqcell_quickcreatevis("buttonchannels", "commandbutton", 328, 432, 178, 42);
	//liqcell_setfont(	buttonchannels, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	//liqcell_setcaption(buttonchannels, "list channels" );
	//liqcell_propsets(  buttonchannels, "backcolor", "rgb(235,233,237)" );
	//liqcell_child_append(  self, buttonchannels);
	//############################# buttonback:commandbutton
	//liqcell *buttonback = liqcell_quickcreatevis("buttonback", "commandbutton", 8, 432, 202, 42);
	//liqcell_setfont(	buttonback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	//liqcell_setcaption(buttonback, "Back" );
	//liqcell_propsets(  buttonback, "backcolor", "rgb(235,233,237)" );
	//liqcell_child_append(  self, buttonback);
	//############################# list1:picturebox
	liqcell *list1 = liqcell_quickcreatevis("list1", "picturebox", 60, 56, 740, 480-56);
	liqcell_setfont(	list1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_propsets(  list1, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  list1, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  list1, "bordercolor", "rgb(200,100,100)" );
		//############################# listback:picturebox
		liqcell *listback = liqcell_quickcreatevis("listback", "picturebox", 0, 12, 740, 228);
		//liqcell_setfont(	listback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_propsets(  listback, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  listback, "backcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  listback, "bordercolor", "rgb(200,100,100)" );


/*			//############################# listitem:picturebox
			liqcell *listitem = liqcell_quickcreatevis("listitem", "picturebox", -2, 18, 790, 40);
			liqcell_setfont(	listitem, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
			liqcell_propsets(  listitem, "textcolor", "rgb(0,0,0)" );
			liqcell_propsets(  listitem, "backcolor", "rgb(0,0,0)" );
			liqcell_propsets(  listitem, "bordercolor", "rgb(200,100,100)" );
				//############################# listitemicon:picturebox
				liqcell *listitemicon = liqcell_quickcreatevis("listitemicon", "picturebox", 56, 2, 34, 32);
				liqcell_setfont(	listitemicon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				liqcell_propsets(  listitemicon, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  listitemicon, "backcolor", "rgb(192,255,192)" );
				liqcell_propsets(  listitemicon, "bordercolor", "rgb(200,100,100)" );
				liqcell_child_append(  listitem, listitemicon);
				//############################# listitemmessage:label
				liqcell *listitemmessage = liqcell_quickcreatevis("listitemmessage", "label", 202, 4, 582, 28);
				liqcell_setfont(	listitemmessage, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(listitemmessage, "message" );
				liqcell_propsets(  listitemmessage, "textcolor", "rgb(255,255,255)" );
				liqcell_propsets(  listitemmessage, "backcolor", "rgb(0,64,64)" );
				liqcell_propseti(  listitemmessage, "textalign", 0 );
				liqcell_child_append(  listitem, listitemmessage);
				//############################# listitemnick:label
				liqcell *listitemnick = liqcell_quickcreatevis("listitemnick", "label", 94, 4, 106, 28);
				liqcell_setfont(	listitemnick, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(listitemnick, "nick" );
				liqcell_propsets(  listitemnick, "textcolor", "rgb(255,255,255)" );
				liqcell_propsets(  listitemnick, "backcolor", "rgb(0,64,0)" );
				liqcell_propseti(  listitemnick, "textalign", 0 );
				liqcell_child_append(  listitem, listitemnick);
				//############################# listitemtime:label
				liqcell *listitemtime = liqcell_quickcreatevis("listitemtime", "label", 4, 4, 50, 28);
				liqcell_setfont(	listitemtime, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(listitemtime, "00:00" );
				liqcell_propsets(  listitemtime, "textcolor", "rgb(255,255,255)" );
				liqcell_propsets(  listitemtime, "backcolor", "rgb(0,64,0)" );
				liqcell_propseti(  listitemtime, "textalign", 0 );
				liqcell_child_append(  listitem, listitemtime);
			liqcell_child_append(  listback, listitem);
 */



			liqcell_child_arrange_easycol(  listback );
			
			liqcell_handleradd(listback,    "mouse",   liqcell_easyhandler_kinetic_mouse );

		liqcell_child_append(  list1, listback);
	liqcell_child_append(  self, list1);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 66, 8, 728, 40);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "linux inotify monitor" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 6, 8, 52, 40);
	liqcell_setfont(	icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(icon, "icon" );
	liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);
	//############################# timer1:liqtimer
	liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
	// store ourselves on the tag for use later
	// this does feel like a workaround, but hell, it works!
	//liqcell_settag(timer1,liqcell_hold(self));
	liqcell_propseti(timer1,"timerinterval", 1 );
	liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
	liqcell_setenabled(timer1,1);
	liqcell_child_insert( self,timer1);
	

	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_handleradd(self, "resize", liqfilemonitor_resize );
	return self;
}


static void liqfilemonitor_showmsg(liqcell *self,char *message)
{
	// add a new listitem into the flow
	// reflow
	// adjust the top position of the backport to compensate

	liqapp_log("showmsg == %s",self->name);

	//############################# list1:picturebox
	liqcell *list1 = liqcell_child_lookup( self,"list1");
		//############################# listback:picturebox
		liqcell *listback =liqcell_child_lookup( list1,"listback");
			//############################# listitem:picturebox
			liqcell *listitem = liqcell_quickcreatevis("listitem", "picturebox", 0, 0, 740, 28);
			//liqcell_setfont(	listitem, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
			//liqcell_propsets(  listitem, "textcolor", "rgb(0,0,0)" );
			//liqcell_propsets(  listitem, "backcolor", "rgb(0,0,0)" );
			//liqcell_propsets(  listitem, "bordercolor", "rgb(200,100,100)" );
				//############################# listitemicon:picturebox
				//liqcell *listitemicon = liqcell_quickcreatevis("listitemicon", "picturebox", 56, 2, 34, 32);
				//liqcell_setfont(	listitemicon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				//liqcell_propsets(  listitemicon, "textcolor", "rgb(0,0,0)" );
				//liqcell_propsets(  listitemicon, "backcolor", "rgb(192,255,192)" );
				//liqcell_propsets(  listitemicon, "bordercolor", "rgb(200,100,100)" );
				//liqcell_child_append(  listitem, listitemicon);
				//############################# listitemmessage:label
				liqcell *listitemmessage = liqcell_quickcreatevis("listitemmessage", "label", 0, 0, 740, 28);
				liqcell_setfont(	listitemmessage, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(listitemmessage, message );
				//liqcell_propsets(  listitemmessage, "textcolor", "rgb(255,255,255)" );
				//liqcell_propsets(  listitemmessage, "backcolor", "rgb(0,64,64)" );
				//liqcell_propseti(  listitemmessage, "textalign", 0 );
				liqcell_child_append(  listitem, listitemmessage);
				//############################# listitemnick:label
				liqcell *listitemnick = liqcell_quickcreatevis("listitemnick", "label", 94, 0, 0, 28);
				//liqcell_setfont(	listitemnick, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				//liqcell_setcaption(listitemnick, nick );
				//liqcell_propsets(  listitemnick, "textcolor", "rgb(255,255,255)" );
				//liqcell_propsets(  listitemnick, "backcolor", "rgb(0,64,0)" );
				//liqcell_propseti(  listitemnick, "textalign", 0 );
				liqcell_child_append(  listitem, listitemnick);
				//############################# listitemtime:label
				liqcell *listitemtime = liqcell_quickcreatevis("listitemtime", "label", 4, 0, 0, 28);
				//liqcell_setfont(	listitemtime, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				//liqcell_setcaption(listitemtime, time );
				//liqcell_propsets(  listitemtime, "textcolor", "rgb(255,255,255)" );
				//liqcell_propsets(  listitemtime, "backcolor", "rgb(0,64,0)" );
				//liqcell_propseti(  listitemtime, "textalign", 0 );
				liqcell_child_append(  listitem, listitemtime);
			liqcell_child_append(  listback, listitem);
			liqcell_child_arrange_easycol(  listback );
			if(listback->h <= list1->h)
			{
				listback->y=0;
			}
			else
			{
				listback->y=-(listback->h - list1->h);
			}
			
			//liqcell_child_append(  listback, listitem);
		//liqcell_child_append(  list1, listback);
	//liqcell_child_append(  self, list1);
	liqcell_setdirty(  self, 1);
}

//liqfilemonitor_showmsg(liqfilemanager,"00:00","msg",linebuf);








#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/inotify.h>

void get_event (int fd, const char * target,liqcell *liqfilemonitor);
void handle_error (int error);

/* ----------------------------------------------------------------- */
//int main (int argc, char *argv[])
int liqfilemonitor_run(liqcell *liqfilemonitor)
{
   char target[FILENAME_MAX];
   int result;
   int fd;
   int wd;   /* watch descriptor */

   //if (argc < 2) {
      fprintf (stderr, "Watching the current directory\n");
	  
	  liqfilemonitor_showmsg(liqfilemonitor,"Watching the current directory\n");

      strcpy (target, ".");
  // }
  // else {
  //    fprintf (stderr, "Watching %s\n", argv[1]);
  //    strcpy (target, argv[1]);
  // }

   fd = inotify_init();
   if (fd < 0) {
      handle_error (errno);
      return 1;
   }
   
   wd = inotify_add_watch (fd, target, IN_ALL_EVENTS);
   if (wd < 0) {
      handle_error (errno);
      return 1;
   }
   
   while (1) {
      get_event(fd, target,liqfilemonitor);
   }

   return 0;
}

/* ----------------------------------------------------------------- */
/* Allow for 1024 simultanious events */
#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*1024)

void get_event (int fd, const char * target,liqcell *liqfilemonitor)
{
   ssize_t len, i = 0;
   char action[81+FILENAME_MAX] = {0};
   char buff[BUFF_SIZE] = {0};

   len = read (fd, buff, BUFF_SIZE);
   
   while (i < len) {
      struct inotify_event *pevent = (struct inotify_event *)&buff[i];
      char action[81+FILENAME_MAX] = {0};

      if (pevent->len) 
         strcpy (action, pevent->name);
      else
         strcpy (action, target);
    
      if (pevent->mask & IN_ACCESS) 
         strcat(action, " was read");
      if (pevent->mask & IN_ATTRIB) 
         strcat(action, " Metadata changed");
      if (pevent->mask & IN_CLOSE_WRITE) 
         strcat(action, " opened for writing was closed");
      if (pevent->mask & IN_CLOSE_NOWRITE) 
         strcat(action, " not opened for writing was closed");
      if (pevent->mask & IN_CREATE) 
         strcat(action, " created in watched directory");
      if (pevent->mask & IN_DELETE) 
         strcat(action, " deleted from watched directory");
      if (pevent->mask & IN_DELETE_SELF) 
         strcat(action, "Watched file/directory was itself deleted");
      if (pevent->mask & IN_MODIFY) 
         strcat(action, " was modified");
      if (pevent->mask & IN_MOVE_SELF) 
         strcat(action, "Watched file/directory was itself moved");
      if (pevent->mask & IN_MOVED_FROM) 
         strcat(action, " moved out of watched directory");
      if (pevent->mask & IN_MOVED_TO) 
         strcat(action, " moved into watched directory");
      if (pevent->mask & IN_OPEN) 
         strcat(action, " was opened");
 
   /*
      printf ("wd=%d mask=%d cookie=%d len=%d dir=%s\n",
              pevent->wd, pevent->mask, pevent->cookie, pevent->len, 
              (pevent->mask & IN_ISDIR)?"yes":"no");

      if (pevent->len) printf ("name=%s\n", pevent->name);
   */

      //printf ("%s\n", action);
      
	  liqfilemonitor_showmsg(liqfilemonitor,action);

	  
      i += sizeof(struct inotify_event) + pevent->len;

   }

}  /* get_event */

/* ----------------------------------------------------------------- */

void handle_error (int error)
{
   fprintf (stderr, "liqfilemonitor Error: %s\n", strerror(error));

}  /* handle_error */

/* ----------------------------------------------------------------- */
