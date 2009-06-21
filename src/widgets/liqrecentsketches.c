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
#include <liqbase/liqcell_dllcache.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqcell_arrange.h>


static int monitor_run(liqcell *context);

	
//#####################################################################
//#####################################################################
//##################################################################### liqrecentsketches :: by gary birkett 
//#####################################################################
//#####################################################################

static int liqrecentsketches_sketch_add(liqcell *self,char *filenamebuffer)
{
	// 20090528_215559 lcuk : first attempt at runtime expansion
	// 20090528_215639 lcuk : its a hack because i should be using the filemonitor class elsewhere
	// 20090528_215654 lcuk : and it should be automatic
	// 20090528_215943 lcuk : class should be pre-tested or something here
	// 20090528_215951 lcuk : this runtime function would obviously be too slow for normal use

	liqapp_log("adding %s",filenamebuffer);

	struct pagefilename pfn;
	
	if(	(pagefilename_breakapart(&pfn,filenamebuffer) == 0) )
	{
		
		
		char buf[FILENAME_MAX];			snprintf(buf,sizeof(buf),"%s%s",pfn.filedate,pfn.filetitle);

		liqcell *body = liqcell_child_lookup( self,"body");
	
						liqcell *c = liqcell_quickcreatevis(buf,   "sketch",   1,1,1,1    );
						liqcell_propseti(c,"lockaspect",1);
						liqcell_propsets(c,"sketchfilename",filenamebuffer);

						liqcell_child_insertsortedbyname( body, c,0);
						
						
						liqcell_setsize(body,self->w,self->h);
						liqcell_child_arrange_makegrid(body,3,3);
	}					
}











	static int timer_tick(liqcell *self, liqcellmouseeventargs *args, liqcell *context)
	{
		liqcell_propseti(self,"timerinterval", 32767 );
		liqcell_setenabled(self,0);
		// now, run the channel? :D
		//liqfilemonitor_run((liqcell*)self->tag);
		monitor_run(context);
		
		return 0;
	}









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
		
		struct pagefilename pfn;
		
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
				//if(
				//	strcasecmp(ext,"page")==0 ||
				//	strcasecmp(ext,"sketch")==0 
				//  )
				
				if(	stristr(ft,"liq.") && (pagefilename_breakapart(&pfn,ft) == 0) )
				{
					
					

					//if(	pagefilename_breakapart(&pfn,ft) == 0)
					{
						// got it ok, lets confirm...
				
						//liqapp_log("pagefilename: ok  path:'%s', dat:'%s', cls:'%s', tit:'%s'",pfn.filepath,pfn.filedate,pfn.fileclass,pfn.filetitle);
						
						
						char buf[FILENAME_MAX];			snprintf(buf,sizeof(buf),"%s%s",pfn.filedate,pfn.filetitle);
						//pagefilename_rebuild(&pfn,buf,sizeof(buf));

						liqcell *c = liqcell_quickcreatevis(buf,   "sketch",   1,1,1,1    );
						liqcell_propseti(c,"lockaspect",1);
						liqcell_propsets(c,"sketchfilename",fn);

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



liqcell *liqrecentsketches_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqrecentsketches","form", 800,480);

	if(self)
	{
	//	liqcell_propsets(  self, "backcolor", "rgb(255,255,255)" );




		char buf[FILENAME_MAX];    snprintf(buf,sizeof(buf),"%s/sketches",app.userdatapath);


if(liqapp_pathexists(buf))
{
	
	liqapp_log("recent sketches buf=%s",buf);
	
		liqcell *body = liqcell_quickcreatevis("body","frame",0 ,0,   self->w,self->h);

		liqcell_scan_folder_for_images(body,buf);
		
		liqcell_child_insert( self, body );
		
		
		liqcell_propsets(  self, "monitorpath" , buf);
		//liqcell_propsets(  self, "watchpattern" , "liq.*");

		int cnt=0;
		liqcell *c=NULL;

		liqcell_child_arrange_makegrid(body,3,3);

		c=liqcell_lastchild(body);

		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		//liqcell_handleradd(self,    "click",   float_click);


// 20090619_221734 lcuk : VERY strange, if I compile with this block in place, when run from the console its ok
// 20090619_221809 lcuk : but when run from the icon the app closes and does not run
// 20090619_221830 lcuk : very curious


//#ifdef USE_INOTIFY
		//############################# timer1:liqtimer
		liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
		// store ourselves on the tag for use later
		// this does feel like a workaround, but hell, it works!
		//liqcell_settag(timer1,liqcell_hold(self));
		liqcell_propseti(timer1,"timerinterval", 1 );
		liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
		liqcell_setenabled(timer1,1);
		liqcell_child_insert( self,timer1);
//#endif


}

	}
	
	return self;
}




//http://darkeside.blogspot.com/2007/12/linux-inotify-example.html




























#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/inotify.h>





// 20090620_215315 lcuk : this was defined as 1024 units, WAY over the top

#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*32)




static void monitor_get_event(int fd, const char * target,liqcell *context)
{
   ssize_t len=0, i = 0;
   char action[81+FILENAME_MAX] = {0};
   char buff[BUFF_SIZE] = {0};

	//liqapp_log("inotify_getevent reading from '%s'",target);

   len = read (fd, buff, BUFF_SIZE);
   
   while (i < len)
   {
		liqapp_log("inotify_getevent '%s', %i %i",target,i,len);
      struct inotify_event *pevent = (struct inotify_event *)&buff[i];
      char action[81+FILENAME_MAX] = {0};
	  
	  if ( (pevent->len) )
	  {
		
		
		snprintf(action,sizeof(action),"%s/%s",target,pevent->name);
		
		// dealing with a file
		  if(pevent->mask & IN_CLOSE_WRITE)
			liqrecentsketches_sketch_add(context,action);
		//  if(pevent->mask & IN_CREATE)
		//    liqrecentsketches_sketch_add(context,pevent->name);
	  }
/*
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

	  liqfilemonitor_showmsg(liqfilemonitor,action);
*/	  
	  
	  


	  
      i += sizeof(struct inotify_event) + pevent->len;

   }

} 





static int monitor_run(liqcell *context)
{
   char *target;//[FILENAME_MAX];
   int result;
   int fd;
   int wd;   /* watch descriptor */

	char * folder = liqcell_propgets(context,"monitorpath",".");

	if( (!folder) || (!*folder) || (!liqapp_pathexists(folder)) )
	{
      liqapp_log( "inotify monitor path does not exist\n");
      return -1;		
	}

   //strcpy (target, folder);
   target=strdup(folder);
   if(!target)
   {
      liqapp_log( "inotify could not alloc target\n");
      return -1;	
   }
   
   liqapp_log("inotify about to init() for '%s'",target);
   fd = inotify_init();
   liqapp_log("inotify init() returned %i",fd);
   if (fd < 0)
   {
      liqapp_log( "monitor error init: %s\n", strerror(errno));
	  free(target);
      return 1;
   }
   liqapp_log("inotify about to add_watch for '%s'",target);
   wd = inotify_add_watch(fd, target, IN_CLOSE_WRITE);//IN_ALL_EVENTS);
   liqapp_log("inotify add_watch returned %i",wd);
   if (wd < 0)
   {
      liqapp_log( "monitor error add: %s\n", strerror(errno));
	  free(target);
      return -1;
   }
   
   liqapp_log("inotify looping for '%s'",target);

         //monitor_get_event(fd, target,context);
  
   while (1)
   {
		liqapp_sleep(25);
        monitor_get_event(fd, target,context);
   }
   
   free(target);

   return 0;
}
