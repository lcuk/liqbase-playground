// /home/user/MyDocs/.camera


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


//#include "liqdialogs.h"


//static int viewtree_click(liqcell *self, liqcellclickeventargs *args, void *context)
//{
//	liqdialog_showtree("view tree","showing tree","",(liqcell *)context);
//}



/*
 // completely remove this autothumb business for now
 // we have a decent thumbnailerd (some of the time at least)
 // using the system thumbs improves first time ux drastically :)

int autothumb_getthumb(liqcell *self,char *bigfilename)
{
	// using the magical autothumb function, create a thumbnail from the filename
	
	char tmp[FILENAME_MAX]={0};
	
	strncpy(tmp,bigfilename,sizeof(tmp));
	liqapp_ensurecleanusername(tmp);
	
	char thumbfn[FILENAME_MAX]={0};
	
	snprintf(thumbfn,sizeof(thumbfn),"%s/thumbs/%s",app.userdatapath,tmp);
	
	liqapp_log("autothumb '%s'",thumbfn);
	if(!liqapp_fileexists(thumbfn))
	{
		//liqapp_log("autothumb '%s' no thumb yet",thumbfn);
		// must create a thumb
			//################################## load in a thumbnail of the image
			liqimage *imgfull = liqcell_getimage(self);   //bigimagepreloaded;//liqimage_newfromfile(bigfilename,0,0,1);
			if(imgfull)
			{
				//liqapp_log("autothumb '%s' has big image, thumbnailing",thumbfn);
				liqimage *imgthumb = liqimage_getthumbnail(imgfull,128,64);
				if(imgthumb)
				{
					//liqapp_log("autothumb '%s' made a thumb!",thumbfn);
					//################################## save it 
					
					if(liqimage_pagesavepng(imgthumb,thumbfn))
					{
						liqapp_log("autothumb_getthumb: could not store thumb buffer as: '%s'",thumbfn);
						liqimage_release(imgthumb);
						return NULL;
					}
					
					//liqapp_log("autothumb '%s' setting thumb",thumbfn);
					
					liqcell_propsets(self,"imagefilenamebig",bigfilename);
					
					liqcell_setimage(self,imgthumb);
					return 0;
					
					//return imgthumb;
					//liqimage_release(imgthumb);
				}
				//liqimage_release(imgfull);
			}
			else
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

*/
	
//#####################################################################
//#####################################################################
//##################################################################### liqrecentphotos :: by gary birkett 
//#####################################################################
//#####################################################################


















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
	
	
	//##########################################################################
	//########################################################################## latest, click event
	//##########################################################################

	/**	
	* liqrecentphotos_item dialog_open - the user zoomed into the dialog
	*/	
	static int liqrecentphotos_item_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
	{
		/*
		 // this will need to return in working form soon
		 // though it will be replaced by opening liqmap on the filename :)
		 // which will be uber cool
		 // perhaps have liqmap come up on the original style footer menus
		 
		char *myimgnamebig = liqcell_propgets(self,"imagefilenamebig",NULL);
		if(myimgnamebig && *myimgnamebig)
		{
			// only set after a thumbnailing
			char *myimgname = liqcell_propgets(self,"imagefilename",NULL);
			if(myimgname && *myimgname)
			{
				// set most of the time
				liqapp_log("liqrecentphotos_item_dialog_open %i,  %s=%s",strcasecmp(myimgnamebig,myimgname),myimgnamebig,myimgname);
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
		*/
				
	   return 0;
	}
	
	/**	
	* liqrecentphotos_item dialog_close - the dialog was closed
	*/	
	static int liqrecentphotos_item_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
	{
		/*
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
		*/
	   return 0;
	}

	//##########################################################################
	//########################################################################## latest, click event
	//##########################################################################

	static int liqrecentphotos_item_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		// lets cheat a little
	//	liqcell_propseti(self,"imagewantbig",1);
	//	liqcell_setimage(self,NULL);
		args->newdialogtoopen = liqcell_hold( self );//liqcell_child_lookup( self, "body" );
		return 1;
	}



	//##########################################################################
	//########################################################################## later, lazy loaded event, try to replace with a thumb
	//##########################################################################
	
	static int liqrecentphotos_item_imageloaded(liqcell *self, liqcelleventargs *args, void *context)
	{
		// this occurs when the lazy loader has finished loading the image for this item
		return 0;
	}

	//##########################################################################
	//########################################################################## shown event, try to grab the thumb
	//##########################################################################

	static int liqrecentphotos_item_shown(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqapp_log("item shown");
		return 0;
	}






static int liqrecentphotos_item_add(liqcell *self,char *filenamebuffer)
{
	// 20090528_215559 lcuk : first attempt at runtime expansion
	// 20090528_215639 lcuk : its a hack because i should be using the filemonitor class elsewhere
	// 20090528_215654 lcuk : and it should be automatic
	// 20090528_215943 lcuk : class should be pre-tested or something here
	// 20090528_215951 lcuk : this runtime function would obviously be too slow for normal use

	liqapp_log("adding %s",filenamebuffer);

	//struct pagefilename pfn;
	//if(	(pagefilename_breakapart(&pfn,filenamebuffer) == 0) )
    
	{
		
		
		//char buf[FILENAME_MAX];			snprintf(buf,sizeof(buf),"%s%s",pfn.filedate,pfn.filetitle);

		liqcell *body = liqcell_child_lookup( self,"body");


			struct stat     statbuf;
			if(stat(filenamebuffer, &statbuf) == -1)
			{
				liqapp_log("liqrecentphotos_item_add stat failed: '%s'",filenamebuffer);
				return -1;
			}
                
						struct tm     *pictm;
						pictm = localtime(&statbuf.st_mtime);
						char   picdate[64];
						strftime(picdate,sizeof(picdate), "%Y%m%d_%H%M%S",pictm);
                        
                        
						char pickey[FILENAME_MAX];
						snprintf(pickey,sizeof(pickey),"%s_%s", picdate, liqapp_filename_walkoverpath(filenamebuffer) );
                        
                        
                        

	
						liqcell *c = liqcell_quickcreatevis(pickey,   "picture",   1,1,1,1    );
						liqcell_propseti(c,"lockaspect",1);
						liqcell_propsets(c,"imagefilename",filenamebuffer);
						
						liqcell_handleradd(c,    "shown",         liqrecentphotos_item_shown);
						liqcell_handleradd(c,    "click",         liqrecentphotos_item_click);
						liqcell_handleradd(c,    "imageloaded",   liqrecentphotos_item_imageloaded);

						liqcell_handleradd_withcontext(c, "dialog_open", liqrecentphotos_item_dialog_open ,self);
						liqcell_handleradd_withcontext(c, "dialog_close", liqrecentphotos_item_dialog_close ,self);


						liqcell_child_insertsortedbyname( body, c,0);
						
						
						
						liqcell_handlerrun(self,"layout",NULL);
						
						
						
						
						//liqcell_setsize(body,self->w,self->h);
						//liqcell_child_arrange_makegrid(body,3,3);
	}					
}








static liqcell *editoverlay_create(int w,int h)
{
	//

	liqcell *self = liqcell_quickcreatewidget("editoverlay","overlay", w,h);

	if(self)
	{
		liqcell *c;

					//liqcell_propseti(self,"levelofdetail",1);
					c = liqcell_quickcreatevis("zoom",   "picture",   w*0,0,w/4,h    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"imagefilename","/usr/share/liqbase/media/zoom.png");
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   widget_click);
					liqcell_child_append( self, c );


					//liqcell *c;
					c = liqcell_quickcreatevis("barcode",   "picture",   w*0.25,0,w/4,h    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"imagefilename","/usr/share/liqbase/media/barcode.png");
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   widget_click);
					liqcell_child_append( self, c );


					c = liqcell_quickcreatevis("postcard",   "picture",   w*0.5,0,w/4,h    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"imagefilename","/usr/share/liqbase/media/postcard.png");
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   widget_click);
					liqcell_child_append( self, c );
/*

					c = liqcell_quickcreatevis("more",   "picture",   w*0.75,0,w/4,h    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"imagefilename","media/more.png");
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					//liqcell_handleradd(c,    "click",   widget_click);
					liqcell_child_append( self, c );


					c = liqcell_quickcreatevis("management",   "picture",   w*0.75,0,w/4,h    );
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







	static int timer_tick(liqcell *self, liqcellmouseeventargs *args, liqcell *context)
	{
		liqcell_propseti(self,"timerinterval", 32767 );
		liqcell_setenabled(self,0);
		// now, run the channel? :D
		//liqfilemonitor_run((liqcell*)self->tag);
		monitor_run(context);
		
		return 0;
	}







//    struct tm     *tm;
//           tm = localtime(&statbuf.st_mtime);
//           strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
		   
		   
		   
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
			if ( S_ISDIR(statbuf.st_mode) )
			{
				//printf(" DIR  ");
				liqcell_scan_folder_for_images(self,fn);	
			}
			else
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
					
					
					
					// what i need to know is if this image has a thumbnail
					// ignore it if not
					char imagethumb[ FILENAME_MAX ];
					
					//int liqimage_find_thumbnail_for(char *resultbuffer,int resultsize,char *bigimagefilename);
					
					if( liqimage_find_thumbnail_for(imagethumb,sizeof(imagethumb),fn) == 0 )
					{
						// w00t!   (hello btw)
					
					
					
										
						struct tm     *pictm;
						pictm = localtime(&statbuf.st_mtime);
						char   picdate[64];
						strftime(picdate,sizeof(picdate), "%Y%m%d_%H%M%S",pictm);
						
						
						char pickey[FILENAME_MAX];
						snprintf(pickey,sizeof(pickey),"%s_%s",picdate,ft);


						liqcell *c = liqcell_quickcreatevis(pickey,   "picture",   1,1,1,1    );
						liqcell_propseti(c,"lockaspect",1);
						liqcell_propsets(c,"imagefilename",imagethumb);
						//liqcell_handleradd(c,    "mouse",   widget_mouse);
						liqcell_handleradd(c,    "shown",         liqrecentphotos_item_shown);
						liqcell_handleradd(c,    "click",         liqrecentphotos_item_click);
					//	liqcell_handleradd(c,    "imageloaded",   liqrecentphotos_item_imageloaded);
						liqcell_handleradd_withcontext(c, "dialog_open", liqrecentphotos_item_dialog_open ,self);
						liqcell_handleradd_withcontext(c, "dialog_close", liqrecentphotos_item_dialog_close ,self);


						liqcell_child_insertsortedbyname( body, c, 0 );

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



	static int liqrecentphotos_filter(liqcell *self, liqcellfiltereventargs *args, void *context)
	{
		// using the filter provided (which might be blank)
		
					int islike = 1;//liqcell_propgeti(  self, "filterlike", 1 );
		
		char *searchterm = NULL;
		
		if(args) args->resultoutof=0;
		if(args) args->resultshown=0;
		if(args) searchterm = args->searchterm;
		
		// examine each tag and if matches the search show it, otherwise dont..
		liqcell *body = liqcell_child_lookup(self,"body");
		
		liqcell *c = liqcell_getlinkchild_visual(body);
		while(c)
		{
			//if(liqcell_isclass(c,"picture"))
			{
				if(searchterm && *searchterm)
				{

					//struct pagefilename pfn;

					//pagefilename_breakapart(&pfn,c->name);
					
					
					char *key = c->name;
                    char *ifn = liqcell_propgets(c,"imagefilename",NULL);
                    if(ifn && *ifn)key=ifn;


					
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
			c=liqcell_getlinknext_visual(c);
		}
		liqcell_setrect(body,   0,0,self->w,self->h);
		liqcell_child_arrange_makegrid(body,3,3);
		//liqcell_propseti(self,"arrangecomplete",0);
		//liqcell_propseti(body,"easytileflyisfinished",0);

		return 1;
		
	}















/**	
 * liqrecentphotos layout - make any adjustments to fill the content as are required
 */	
static int liqrecentphotos_layout(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	
	liqcell *title= liqcell_child_lookup(self, "title");
	liqcell *body= liqcell_child_lookup(self, "body");
		liqcell *headskip= liqcell_child_lookup(body, "__headskip");
	
		// make a normal grid
		liqcell_setrect( body, 0, 0, liqcell_getw(self),liqcell_geth(self) );
		liqcell_child_arrange_makegrid(body,3,3);
		
//### use only if title in use
		
		// make sure the headerskip is adjusted
//		liqcell_setsize(headskip,liqcell_getw(title),liqcell_geth(title));
		// now flow the rest
//		liqcell_child_arrange_autoflow(body);
		// and make sure its positioned correctly
//		liqcell_setrect( body, 0, 0, liqcell_getw(self),liqcell_geth(body) );
		
 
	return 0;
}

liqcell *liqrecentphotos_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqrecentphotos","form", 800,480);

	if(self)
	{
	//	liqcell_propseti(self,"idle_lazyrun_wanted",1);			 // :)
	//	liqcell_propseti(self,"multitouch_test_range",5);
	
	liqcell_handleradd_withcontext(self, "layout", liqrecentphotos_layout ,self);

/*
		//############################# title:titlebar
		liqcell *title = liqcell_quickcreatevis("title", "titlebar", 0,0, 800, 50);
		liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(title, "Recent photos and pictures" );
		liqcell_propsets(  title, "imagefilename", "/usr/share/liqbase/media/titlebanner_left.png" );
		liqcell_propsets(  title, "textcolor", "rgb(255,255,0)" );
		//liqcell_propsets(  title, "backcolor", "rgb(0,0,60)" );
		liqcell_propseti(  title, "lockaspect", 0 );
		liqcell_propseti(  title, "textalign", 0 );
		liqcell_child_append(  self, title);


			//############################# cmddraw:label
			liqcell *cmddraw = liqcell_quickcreatevis("cmddraw", "label", 580, 0, 86, 48);
			liqcell_setfont(	cmddraw, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
			liqcell_setcaption(cmddraw, "draw" );
			liqcell_propsets(  cmddraw, "textcolor", "rgb(255,255,255)" );
			liqcell_propsets(  cmddraw, "backcolor", "rgb(0,64,64)" );
			liqcell_propsets(  cmddraw, "bordercolor", "rgb(200,100,100)" );
			liqcell_propseti(  cmddraw, "textalign", 2 );
			//liqcell_handleradd_withcontext(cmddraw, "click", cmddraw_click, self );
			liqcell_child_append(  title, cmddraw);
			//############################# cmdzoom:label
			liqcell *cmdzoom = liqcell_quickcreatevis("cmdzoom", "label", 492, 0, 86, 48);
			liqcell_setfont(	cmdzoom, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
			liqcell_setcaption(cmdzoom, "zoom" );
			liqcell_propsets(  cmdzoom, "textcolor", "rgb(255,255,255)" );
			liqcell_propsets(  cmdzoom, "backcolor", "rgb(0,64,64)" );
			liqcell_propsets(  cmdzoom, "bordercolor", "rgb(200,100,100)" );
			liqcell_propseti(  cmdzoom, "textalign", 2 );
			//liqcell_handleradd_withcontext(cmdzoom, "click", cmdzoom_click, self );
			liqcell_child_append(  title, cmdzoom);
			//############################# cmdsel:label
			liqcell *cmdsel = liqcell_quickcreatevis("cmdsel", "label", 404, 0, 86, 48);
			liqcell_setfont(	cmdsel, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
			liqcell_setcaption(cmdsel, "sel" );
			liqcell_propsets(  cmdsel, "textcolor", "rgb(255,255,255)" );
			liqcell_propsets(  cmdsel, "backcolor", "rgb(0,64,64)" );
			liqcell_propsets(  cmdsel, "bordercolor", "rgb(200,100,100)" );
			liqcell_propseti(  cmdsel, "textalign", 2 );
			//liqcell_handleradd_withcontext(cmdsel, "click", cmdsel_click, self );
			liqcell_child_append(  title, cmdsel);

 */



		liqcell *body = liqcell_quickcreatevis("body","frame",0 ,0,   self->w,self->h);

			// create a headskip blank
//			liqcell *headskip = liqcell_quickcreatevis("__headskip", NULL, 0, 0, liqcell_getw(title),liqcell_geth(title));
//			liqcell_child_append(  body, headskip);
			
			
		liqcell_child_insert( self, body );

	

			char buf[FILENAME_MAX];		
										snprintf(buf,sizeof(buf),"%s/MyDocs/.images",app.homepath);
			liqcell_scan_folder_for_images(self,buf);
	
										snprintf(buf,sizeof(buf),"%s/MyDocs/.camera",app.homepath);
			liqcell_scan_folder_for_images(self,buf);
	
										snprintf(buf,sizeof(buf),"%s/MyDocs/DCIM",app.homepath);
			liqcell_scan_folder_for_images(self,buf);

			//							snprintf(buf,sizeof(buf),"/home/user/MyDocs/.camera");
			//liqcell_scan_folder_for_images(self,buf);
	
			//							snprintf(buf,sizeof(buf),"/home/user/MyDocs/.images");
			//liqcell_scan_folder_for_images(self,buf);
		
		
		
		liqcell_handlerrun(self,"layout",NULL);
		
		
		
		liqcell_propsets(  self, "monitorpath" , buf);
		//liqcell_propsets(  self, "watchpattern" , "liq.*");

		int cnt=0;
		liqcell *c=NULL;

		//liqcell_child_arrange_makegrid(body,3,3);
		

		c=liqcell_lastchild(body);

		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		
		
		//liqcell_handleradd(self,    "click",   float_click);

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


        liqcell_handleradd(self,    "filter",   liqrecentphotos_filter);

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




static void monitor_get_event(int fd, const char * target,liqcell *context)
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
			liqrecentphotos_item_add(context,action);
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
   wd = inotify_add_watch(fd, target, IN_CLOSE_WRITE | IN_MOVED_TO);//IN_ALL_EVENTS);
   //wd = inotify_add_watch(fd, target, IN_ALL_EVENTS);
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
