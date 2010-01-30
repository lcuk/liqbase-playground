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


					//char imagethumb[ FILENAME_MAX ];
					//if( liqimage_find_thumbnail_for(imagethumb,sizeof(imagethumb),fn) == 0 )
					//{
						// w00t!   (hello btw)
					//}

static int monitor_run(liqcell *context);

int autothumb_getthumb(liqcell *self,char *bigfilename)
{
	// using the magical autothumb function, create a thumbnail from the filename
	
	//char tmp[FILENAME_MAX]={0};
	
	//strncpy(tmp,bigfilename,sizeof(tmp));
	//liqapp_ensurecleanusername(tmp);
	
	char thumbfn[FILENAME_MAX]={0};
	
	//snprintf(thumbfn,sizeof(thumbfn),"%s/thumbs/%s",app.userdatapath,tmp);
	
	if( liqimage_find_thumbnail_for_2(thumbfn,sizeof(thumbfn),bigfilename) == 0 )
	{
		// got one!
	}
	else
	{
		thumbfn[0] = 0;
	}
	
	liqapp_log("autothumb '%s'",thumbfn);
	if(thumbfn[0] && !liqapp_fileexists(thumbfn))
	{
		liqapp_log("autothumb '%s' no thumb yet",thumbfn);

			{
				// no thumbnail available, and nothing to work from, lets just wait
				return -1;
			}
	}
	
	
	liqapp_log("autothumb '%s' loading",thumbfn);
	
	liqcell_propsets(self,"imagefilenamebig",bigfilename);
	liqcell_propsets(self,"imagefilename",thumbfn);
	
	liqcell_threadloadimage(self);
	return 0;
	//return liqimage_newfromfile(thumbfn,0,0,1);
}



	//##########################################################################
	//########################################################################## later, lazy loaded event, try to replace with a thumb
	//##########################################################################
	
	static int liqrecentmedia_item_imageloaded(liqcell *self, liqcelleventargs *args, void *context)
	{
		// this occurs when the laxy loader has finished loading the image for this item
		liqapp_log("item loaded");
		liqimage *myimg = liqcell_getimage(self);
		if(myimg && liqcell_propgets(self,"imagefilenamebig",NULL)==NULL)
		{
			
			
			
			
			liqapp_log("item loaded, we loaded the full image, but we want the thumbnail");
			// the image assigned should be the BIG image
			// shall we throw it away and replace it with a thumb?
			// seems awfully wasted
			char *myimgname = liqcell_propgets(self,"imagefilename",NULL);
			if(myimgname && *myimgname)
			{
				liqapp_log("item loaded, got its filename");
			
				if(liqcell_propgeti(self,"imageisthumb",0) ==0)
				{
					liqapp_log("item loaded, its not a thumb yet");
					// this is not a thumbnail
					autothumb_getthumb(self,myimgname);
					/*
					if(thumb)
					{
						liqapp_log("item loaded, we got a thumb!");
						// replace the large image with a thumb :)
						liqcell_setimage(self,thumb);
						liqcell_propseti(self,"imageisthumb",1);
					}
					*/
				}

			}
		}
	}
	//##########################################################################
	//########################################################################## shown event, try to grab the thumb
	//##########################################################################

	static int liqrecentmedia_item_shown(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqapp_log("item shown");
		liqimage *myimg = liqcell_getimage(self);
		if(!myimg)
		{
			liqapp_log("item shown, no img yet");
			char *myimgname = liqcell_propgets(self,"imagefilename",NULL);
			if(myimgname && *myimgname)
			{
				liqapp_log("item shown got filename though");
				autothumb_getthumb(self,myimgname);
				/*
				if(thumb)
				{
					liqapp_log("item shown, got a thumb!");
					// take a short cut!
					liqcell_setimage(self,thumb);
					liqcell_propseti(self,"imageisthumb",1);
				}
				*/
			}
		}
	}


//#####################################################################
//#####################################################################
//##################################################################### liqrecentmedia :: by gary birkett
//#####################################################################
//#####################################################################




	static int liqrecentmedia_filter(liqcell *self, liqcellfiltereventargs *args, liqcell *liqrecentmedia)
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
        liqcell *body = liqcell_child_lookup( liqrecentmedia,"body");
       
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








	//##########################################################################
	//########################################################################## latest, click event
	//##########################################################################

	/**	
	* liqrecentmedia_item dialog_open - the user zoomed into the dialog
	*/	
	static int liqrecentmedia_item_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
	{
		char *myimgnamebig = liqcell_propgets(self,"imagefilenamebig",NULL);
		if(myimgnamebig && *myimgnamebig)
		{
			// only set after a thumbnailing
			char *myimgname = liqcell_propgets(self,"imagefilename",NULL);
			if(myimgname && *myimgname)
			{
				// set most of the time
				liqapp_log("liqrecentmedia_item_dialog_open %i,  %s=%s",strcasecmp(myimgnamebig,myimgname),myimgnamebig,myimgname);
				if(strcasecmp(myimgnamebig,myimgname)==0)
				{
					// same, do nothing
				}
				else
				{
					// different!  reload mighty image
					liqcell_propsets(self,"imagefilename",myimgnamebig);
					//liqcell_propremoves(self,"imagefilenamebig");
					liqcell_threadloadimage(self,myimgnamebig);
				}				
			}
		}
				
	   return 0;
	}
	
	/**	
	* liqrecentmedia_item dialog_close - the dialog was closed
	*/	
	static int liqrecentmedia_item_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
	{
		char *myimgnamebig = liqcell_propgets(self,"imagefilenamebig",NULL);
		if(myimgnamebig && *myimgnamebig)
		{
			char *myimgname = liqcell_propgets(self,"imagefilename",NULL);
			if(myimgname && *myimgname)
			{
				if(strcasecmp(myimgnamebig,myimgname)==0)
				{
					// same
					//liqcell_propsets(self,"imagefilename",myimgnamebig);
					liqcell_propremoves(self,"imagefilenamebig");
					autothumb_getthumb(self,myimgname);
				}
				else
				{
					// different!
				}				
			}
		}
	   return 0;
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












static int liqrecentmedia_additem(liqcell *self,char *path)
{
    
	liqcell *body= liqcell_child_lookup(self, "body");
	
		char *widgetpath = path;
		DIR           *	dir_p;
		struct dirent *	dir_entry_p;
		char 			fn[FILENAME_MAX+1];
		char          * ft;
        struct pagefilename pfn;





			snprintf(fn , FILENAME_MAX , "%s", path);
			ft=liqapp_filename_walkoverpath(fn);

			struct stat     statbuf;
			if(stat(fn, &statbuf) == -1)
			{
				liqapp_log("liqcell_scan_folder_for_images stat failed: '%s'",fn);
				return self;
			}

            
			if ( S_ISDIR(statbuf.st_mode) )
			{
				//printf(" DIR  ");
				//liqcell_scan_folder_for_images(self,fn);	
			}
			else
			// got the information we need
			if ( S_ISREG(statbuf.st_mode) )
			{
						struct tm     *pictm;
						pictm = localtime(&statbuf.st_mtime);
						char   picdate[64];
						strftime(picdate,sizeof(picdate), "%Y%m%d_%H%M%S",pictm);
                        
                        
						char pickey[FILENAME_MAX];
						snprintf(pickey,sizeof(pickey),"%s_%s", picdate, ft );

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
 
 
					char thumbfn[FILENAME_MAX]={0};
					
					//snprintf(thumbfn,sizeof(thumbfn),"%s/thumbs/%s",app.userdatapath,tmp);
					
					if( liqimage_find_thumbnail_for_2(thumbfn,sizeof(thumbfn),fn) == 0 )
					{
						// got one!
	
	
						liqcell *c = liqcell_quickcreatevis(pickey,   "picture",   1,1,1,1    );
						liqcell_propseti(c,"lockaspect",1);
						liqcell_propsets(c,"imagefilename",fn);
						//liqcell_handleradd(c,    "mouse",   widget_mouse);
						liqcell_handleradd(c,    "click",   widget_click);
						liqcell_handleradd(c,    "shown",   liqrecentmedia_item_shown);
						liqcell_handleradd(c,    "imageloaded",   liqrecentmedia_item_imageloaded);
	
						liqcell_handleradd_withcontext(c, "dialog_open", liqrecentmedia_item_dialog_open ,self);
						liqcell_handleradd_withcontext(c, "dialog_close", liqrecentmedia_item_dialog_close ,self);
	
	
	
						liqcell_child_insertsortedbyname( body, c,0);
				
					}


				}
                else
				if(	stristr(ft,"liq.") && (pagefilename_breakapart(&pfn,ft) == 0) )
				{
					//liqapp_log("mmmmmm %s",ft);

					liqcell *c = liqcell_quickcreatevis(pickey,   "picture",   1,1,1,1    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"sketchfilename",fn);
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					liqcell_handleradd(c,    "click",   widget_click);


					liqcell_child_insertsortedbyname( body, c,0);

                    
                }
				
			}
	return 0;

}

























static int liqcell_scan_folder_for_images(liqcell *self,char *path)
{
    
	liqcell *body= liqcell_child_lookup(self, "body");
	
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
            
			if ( S_ISDIR(statbuf.st_mode) )
			{
				//printf(" DIR  ");
				liqcell_scan_folder_for_images(self,fn);	
			}
			else
			// got the information we need
			if ( S_ISREG(statbuf.st_mode) )
			{
				liqrecentmedia_additem(self,fn);
			}
		}
		closedir(dir_p);

}



//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################



	static int timer_tick(liqcell *self, liqcellmouseeventargs *args, liqcell *context)
	{
		liqcell_propseti(self,"timerinterval", 32767 );
		liqcell_setenabled(self,0);
		// now, run the channel? :D
		//liqfilemonitor_run((liqcell*)self->tag);
		monitor_run(context);
		
		return 0;
	}





liqcell *liqrecentmedia_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqrecentmedia","form", 800,480);

	if(self)
	{

		
		
		liqcell *body = liqcell_quickcreatevis("body",NULL,0 ,0,   self->w,self->h);
		liqcell_child_insert( self, body );




			char buf[FILENAME_MAX];		
										snprintf(buf,sizeof(buf),"%s/MyDocs/.images",app.homepath);
			liqcell_scan_folder_for_images(self,buf);
	
			//							snprintf(buf,sizeof(buf),"%s/MyDocs/.camera",app.homepath);
			//liqcell_scan_folder_for_images(self,buf);
	
										snprintf(buf,sizeof(buf),"%s/MyDocs/DCIM",app.homepath);
			liqcell_scan_folder_for_images(self,buf);
            
										snprintf(buf,sizeof(buf),"%s/MyDocs/sheepdrawing",app.homepath);
			liqcell_scan_folder_for_images(self,buf);
	
			//							snprintf(buf,sizeof(buf),"%s/MyDocs",app.homepath);
			//liqcell_scan_folder_for_images(self,buf);
                        
                                        snprintf(buf,sizeof(buf),"%s/sketches",app.userdatapath);
            liqcell_scan_folder_for_images(self,buf);

                                        snprintf(buf,sizeof(buf),"%s/cal",app.userdatapath);
            liqcell_scan_folder_for_images(self,buf);




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

		//############################# timer1:liqtimer
		liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
		// store ourselves on the tag for use later
		// this does feel like a workaround, but hell, it works!
		//liqcell_settag(timer1,liqcell_hold(self));
		liqcell_propseti(timer1,"timerinterval", 1 );
		liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
		liqcell_setenabled(timer1,1);
		liqcell_child_insert( self,timer1);



		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );	
		liqcell_handleradd_withcontext(self,    "filter",   liqrecentmedia_filter,self);

	}

	return self;
}








#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/inotify.h>







// 20090620_215315 lcuk : this was defined as 1024 units, WAY over the top

#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*32)




static void monitor_get_event(int fd, const char * target,liqcell *context,int wd,int wd2)
{
   ssize_t len=0, i = 0;
   char action[81+FILENAME_MAX] = {0};
   char buff[BUFF_SIZE] = {0};

	//liqapp_log("inotify_getevent reading from '%s'",target);

   len = read (fd, buff, BUFF_SIZE);
   
   while (i < len)
   {
      struct inotify_event *pevent = (struct inotify_event *)&buff[i];
      char action[81+FILENAME_MAX] = {0};
	  
	  if ( (pevent->len) )
	  {

	char *torig=target;

	char buf[FILENAME_MAX];
if(pevent->wd==wd)
{
											snprintf(buf,sizeof(buf),"%s/MyDocs/DCIM",app.homepath);
	target=buf;
}
else
{

											snprintf(buf,sizeof(buf),"%s/sketches",app.userdatapath);
	target=buf;
}

        char *ext=liqapp_filename_walktoextension(pevent->name);
		if(!ext || !*ext)
        {
        }
        else
        {
            // silly hack
            if( strcasecmp(ext,"filepart")==0 ) goto nextitem;
        }

		snprintf(action,sizeof(action),"%s/%s",target,pevent->name);
		
		liqapp_log("inotify_getevent '%s', %i %i   %i::'%s'",target,i,len,pevent->mask,action);

   		  // dealing with a file
		  if( (pevent->mask & IN_CLOSE_WRITE) || (pevent->mask & IN_MOVED_TO) )
		  {
			liqrecentmedia_additem(context,action);
			liqcell *body = liqcell_child_lookup( context,"body");
			liqcell_setrect(body,0,0,context->w,context->h);
			liqcell_child_arrange_makegrid(body,4,4);
		  }
			
		//  if(pevent->mask & IN_CREATE)
		//    liqrecentsketches_sketch_add(context,pevent->name);
	  }
nextitem:
{}
      i += sizeof(struct inotify_event) + pevent->len;

   }

} 





static int monitor_run(liqcell *context)
{
   char *target;//[FILENAME_MAX];
   int result;
   int fd;
   int wd;   /* watch descriptor */
   int wd2;

//	char * folder = liqcell_propgets(context,"monitorpath",".");

//	if( (!folder) || (!*folder) || (!liqapp_pathexists(folder)) )
//	{
//      liqapp_log( "inotify monitor path does not exist\n");
//      return -1;		
//	}

	char *folder = "&&&IGNORED&&&";
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

	char *torig=target;

	char buf[FILENAME_MAX];

											snprintf(buf,sizeof(buf),"%s/MyDocs/DCIM",app.homepath);
	target=buf;



   liqapp_log("inotify about to add_watch for '%s'",target);
   wd = inotify_add_watch(fd, target, IN_CLOSE_WRITE | IN_MOVED_TO);//IN_ALL_EVENTS);
   //wd = inotify_add_watch(fd, target, IN_ALL_EVENTS);
   liqapp_log("inotify add_watch returned %i",wd);
   if (wd < 0)
   {
      liqapp_log( "monitor error add: %s\n", strerror(errno));
	  free(target);
      return -1;
   }


											snprintf(buf,sizeof(buf),"%s/sketches",app.userdatapath);
	target=buf;


   liqapp_log("inotify about to add_watch for '%s'",target);
   wd2 = inotify_add_watch(fd, target, IN_CLOSE_WRITE | IN_MOVED_TO);//IN_ALL_EVENTS);
   //wd = inotify_add_watch(fd, target, IN_ALL_EVENTS);
   liqapp_log("inotify add_watch returned %i",wd);
   if (wd2 < 0)
   {
      liqapp_log( "monitor error add: %s\n", strerror(errno));
	  free(target);
      return -1;
   }


	target=torig;
   
   liqapp_log("inotify looping for '%s'",target);

         //monitor_get_event(fd, target,context);
  
   while (1)
   {
		liqapp_sleep(25);
        monitor_get_event(fd, target,context,wd,wd2);
   }
   
   free(target);

   return 0;
}
