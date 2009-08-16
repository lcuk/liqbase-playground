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


	static int liqrecentsketches_sketchitem_click(liqcell *self, liqcellclickeventargs *args, liqcell *liqrecentsketches)
	{
		//liqapp_log("general click");
		//args->newdialogtoopen = self;
        if(liqcell_getselected(self))
        {
			liqcell_setselected(self,0);
			//liqcell_propremoves(self, "textcolor"   );
			liqcell_propremoves(self, "backcolor"   );
			liqcell_propremoves(self, "bordercolor" );
        }
        else
        {
			liqcell_setselected(self,1);
			//liqcell_propsets(self, "textcolor",   "rgb(0,255,0)" );
			liqcell_propsets(self, "backcolor",   "rgb(0,40,0)" );
			liqcell_propsets(self, "bordercolor", "rgb(0,80,0)" );
        }
		return 1;
	}



static int liqrecentsketches_sketch_insert(liqcell *self,char *filenamebuffer)
{
	liqcell *body = liqcell_child_lookup( self,"body");

	struct pagefilename pfn;
	
	if(	(pagefilename_breakapart(&pfn,filenamebuffer) == 0) )
	{
		
		char buf[FILENAME_MAX];			snprintf(buf,sizeof(buf),"%s%s",pfn.filedate,pfn.filetitle);
		
		//liqapp_log("ins 1 %s",filenamebuffer);
		// valid file		
		char b[255]={0};
		snprintf(b,5,"%s",pfn.filedate); b[4]='\0';
		liqcell *xy=liqcell_child_lookup(body,b);
		if(!xy)
		{
			//liqapp_log("ins 2 %s",filenamebuffer);
			xy=liqcell_quickcreatevis(b,"year",  0,0, (self->w),self->h/15);
			liqcell_child_insertsortedbyname(body,xy,0);
			//snprintf(b,5,"%s",pfn.filedate); b[4]='\0';
			//brk=addframe(xy,b,(self->w),self->h/15);				// year break tile
			//brk->style=odd;
		}
		
		//liqapp_log("ins 3 %s",filenamebuffer);
		
		
			snprintf(b,3,"%s",&pfn.filedate[4]); b[2]='\0';
			liqcell *xm=liqcell_child_lookup(xy,b);
			if(!xm)
			{
				//liqapp_log("ins 4 %s",filenamebuffer);
				xm=liqcell_quickcreatevis(b,"month",  0,0, (self->w),self->h/15);
				liqcell_child_insertsortedbyname(xy,xm,0);
				//snprintf(b,7,"%s",pfn.filedate); b[6]='\0';
				//brk=addframe(xm,b,(self->w),self->h/15);			// month break tile
				//brk->style=odd;
			}
			
			//liqapp_log("ins 5 %s",filenamebuffer);
			
				snprintf(b,3,"%s",&pfn.filedate[6]); b[2]='\0';
				liqcell *xd=liqcell_child_lookup(xm,b);
				if(!xd)
				{
					//liqapp_log("ins 6 %s",filenamebuffer);
					xd=liqcell_quickcreatevis(b,"day",  0,0, (self->w),self->h/15);
					liqcell_child_insertsortedbyname(xm,xd,0);
					
					//liqapp_log("ins 7 %s",filenamebuffer);
					// add title header

					snprintf(b,10,"_%s",pfn.filedate); b[9]='\0';
					liqcell *brk=liqcell_quickcreatevis(b,"label",  0,0, (self->w),self->h/15);


					liqcell_setfont(	brk, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
					
					snprintf(b,9,"%s",pfn.filedate); b[8]='\0';
					
					liqcell_setcaption(brk, b );
					liqcell_propsets(  brk, "textcolor", "rgb(255,255,255)" );
					liqcell_propsets(  brk, "backcolor", "rgb(0,0,100)");
					liqcell_propseti(  brk, "textalign", 0 );

					liqcell_child_append(xd,brk);
				}
				
				//liqapp_log("ins 8 %s",filenamebuffer);
				

				liqcell *c = liqcell_quickcreatevis(buf,   "sketch",   0,0,(self->w/5),(self->h/4)    );
				liqcell_propseti(c,"lockaspect",1);
				liqcell_propsets(c,"sketchfilename",filenamebuffer);
				liqcell_handleradd_withcontext(c,"click",liqrecentsketches_sketchitem_click,self);
				
				
				liqcell_child_insertsortedbyname( xd, c,0);
				
				//liqapp_log("ins 9 %s",filenamebuffer);
				
				liqcell_setsize(xd, self->w, self->h/15 );
				liqcell_child_arrange_autoflow(xd);
			liqcell_child_arrange_easycol(xm);			
		liqcell_child_arrange_easycol(xy);
				
		liqcell_child_arrange_easycol(body);	
	}
}



	





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
		liqrecentsketches_sketch_insert(self,filenamebuffer);
		return 0;
/*		
		char buf[FILENAME_MAX];			snprintf(buf,sizeof(buf),"%s%s",pfn.filedate,pfn.filetitle);

		liqcell *body = liqcell_child_lookup( self,"body");
	
						liqcell *c = liqcell_quickcreatevis(buf,   "sketch",   1,1,1,1    );
						liqcell_propseti(c,"lockaspect",1);
						liqcell_propsets(c,"sketchfilename",filenamebuffer);
						
						
						//#########################################
						liqapp_log("name: %s",pfn.fileuser);
						char fn[FILENAME_MAX];
							snprintf(fn,sizeof(fn),"media/avatars/%s.png",pfn.fileuser);
						if(!liqapp_fileexists(fn))
						{
							snprintf(fn,sizeof(fn),"media/avatars/%s.jpg",pfn.fileuser);
						}
						if(liqapp_fileexists(fn))
						{
							liqcell *p = liqcell_quickcreatevis(fn,   "user",   0,0,42,42    );
							liqcell_propseti(p,"lockaspect",1);
							liqcell_propsets(p,"imagefilename",fn);
							liqcell_child_insert( c, p);
						}

						liqcell_child_insertsortedbyname( body, c,0);
						liqcell_setsize(body,self->w,self->h);
						liqcell_child_arrange_makegrid(body,3,3);
 */
	}
	return 0;
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
	
	liqcell *body = liqcell_child_lookup( self,"body");
	
	
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
					
					liqrecentsketches_sketch_insert(self,fn);
					
				/*	
					

					//if(	pagefilename_breakapart(&pfn,ft) == 0)
					{
						// got it ok, lets confirm...
				
						//liqapp_log("pagefilename: ok  path:'%s', dat:'%s', cls:'%s', tit:'%s'",pfn.filepath,pfn.filedate,pfn.fileclass,pfn.filetitle);
						
						
						char buf[FILENAME_MAX];			snprintf(buf,sizeof(buf),"%s%s",pfn.filedate,pfn.filetitle);
						//pagefilename_rebuild(&pfn,buf,sizeof(buf));

						liqcell *c = liqcell_quickcreatevis(buf,   "sketch",   1,1,1,1    );
						liqcell_propseti(c,"lockaspect",1);
						liqcell_propsets(c,"sketchfilename",fn);

						//#########################################
						//liqapp_log("name: %s",pfn.fileuser);
						char fn[FILENAME_MAX];
							snprintf(fn,sizeof(fn),"media/avatars/%s.png",pfn.fileuser);
						if(!liqapp_fileexists(fn))
						{
							snprintf(fn,sizeof(fn),"media/avatars/%s.jpg",pfn.fileuser);
						}
						if(liqapp_fileexists(fn))
						{
							liqcell *p = liqcell_quickcreatevis(fn,   "user",   0,0,42,42    );
							liqcell_propseti(p,"lockaspect",1);
							liqcell_propsets(p,"imagefilename",fn);
							liqcell_child_insert( c, p);
						}


						liqcell_child_insertsortedbyname( body, c,0);
					}
					
					
				*/
					
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

		
		liqcell_child_insert( self, body );
		
		liqcell_scan_folder_for_images(self,buf);
		
		liqcell_propsets(  self, "monitorpath" , buf);
		//liqcell_propsets(  self, "watchpattern" , "liq.*");

		int cnt=0;
		liqcell *c=NULL;

		//liqcell_child_arrange_makegrid(body,3,3);

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


		//############################# title:label
		liqcell *title = liqcell_quickcreatevis("title", "label", 0,0, 200, 50);
		liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(title, "Sketches" );
		liqcell_propsets(  title, "imagefilename", "media/titlebanner_left.png" );
		liqcell_propsets(  title, "textcolor", "rgb(255,255,0)" );
		//liqcell_propsets(  title, "backcolor", "rgb(0,0,60)" );
		liqcell_propseti(  title, "textalign", 0 );
		liqcell_child_append(  self, title);

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
	  }
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
