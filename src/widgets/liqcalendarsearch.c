

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



	
//#####################################################################
//#####################################################################
//##################################################################### liqcalendarsearch :: by gary birkett 
//#####################################################################
//#####################################################################




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
					liqcell_propsets(c,"imagefilename","../media/lcuk_sig_headshot.png");
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
				if(
					strcasecmp(ext,"page")==0 ||
					strcasecmp(ext,"sketch")==0 
				  )
				{
					
					struct pagefilename pfn;

					//if(	pagefilename_breakapart(&pfn,ft) == 0)
					{
						// got it ok, lets confirm...
				
						//liqapp_log("pagefilename: ok  path:'%s', dat:'%s', cls:'%s', tit:'%s'",pfn.filepath,pfn.filedate,pfn.fileclass,pfn.filetitle);
						
						
						//char buf[FILENAME_MAX];
						//pagefilename_rebuild(&pfn,buf,sizeof(buf));

						liqcell *c = liqcell_quickcreatevis(fn,   "sketch",   1,1,1,1    );
						liqcell_propseti(c,"lockaspect",1);
						liqcell_propsets(c,"sketchfilename",fn);
	
						liqcell_setfont(	c, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (16), 0) );
						liqcell_setcaption(c, ft );
						liqcell_propsets(  c, "textcolor", "rgb(100,100,0)" );
						//liqcell_propsets(  c, "bordercolor", "rgb(0,64,0)" );


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


	static int search_mouse(liqcell *self, liqcellmouseeventargs *args, liqcell *searchmain)
	{
		liqapp_log("search mouse mex==%i, mey==%i, mez==%i",args->mex,args->mey,args->mez);
		// we do not want to eat this mouse event
		// always return 0 from here to allow other processors to operate
		if(args->mez!=0) return 0;
		
		liqcell *search = liqcell_child_lookup(searchmain,"search");
		liqcell *body = liqcell_child_lookup(searchmain,"body");
		
		
		
		if(!search || !body)
		{
			liqapp_log("invalid search or body");
			return 0;
		}
		
		// using the stroke in the search box
		// look over every sketch in the body box
		// load the sketch if needbe
		//
		
		liqsketch *searchsketch = liqcell_getsketch(search);
		if(searchsketch)
		{
			liqapp_log("got sketch");
			// now, loop the sketches
			liqcell *c = liqcell_getlinkchild(body);
			while(c)
			{
				if( strcasecmp( liqcell_getclassname(c) , "sketch" )==0 )
				{
					//liqapp_log("loading sketch");
					liqcell_sketch_autoload(c);
					
					liqapp_log("getting sketch");
					liqsketch *csketch = liqcell_getsketch(c);
					if(csketch)
					{
						// we have a sketch
						// isclass would be a better function name for this
						int quadmatch=1;
						liqstroke *s1 = searchsketch->strokefirst;
						while(s1)
						{
							char *s1quad = liqstroke_quadchainbuild(s1);
							if(s1quad)
							{
								int onematch=0;
								liqstroke *s2 = csketch->strokefirst;
								while(s2)
								{
									// compare the liqstroke_quadchainbuild results
									char *s2quad = liqstroke_quadchainbuild(s2);
									
									if( s2quad && strcasecmp( s1quad,s2quad )==0 )
									{
										// they match :)
										quadmatch++;
										onematch++;
										//goto quickfin;
									}
									else
									{
										// it might have been an invalid stroke
										
										if(!s2quad) onematch=1;
									}
									s2=s2->linknext;
								}
								if(!onematch)
								{
									// did not match one of our strokes
									quadmatch=0;
									goto quickfin;
								}
							}
							s1=s1->linknext;
						}
					quickfin:

						if(quadmatch)
						{
							liqcell_setvisible(c,1);
						}
						else
						{
							liqcell_setvisible(c,0);
						}
					}
				}
				c=liqcell_getlinknext(c);
			}
			liqcell_setsize(body,searchmain->w/2,searchmain->h);
			liqcell_child_arrange_makegrid(body,3,3);
		}
		
		
		//
		
		
		return 0;
	}

		
	
	int search_cleared(liqcell *self, liqcelleventargs *args, liqcell *searchmain)
	{
		//searchmain
		liqcell *body = liqcell_child_lookup(searchmain,"body");
		
		
		
		if(!body)
		{
			liqapp_log("invalid body");
			return 0;
		}

			liqcell *c = liqcell_getlinkchild(body);
			while(c)
			{
				if( strcasecmp( liqcell_getclassname(c) , "sketch" )==0 )
				{
					liqcell_setvisible(c,1);
				}
				c=liqcell_getlinknext(c);
			}
			liqcell_setsize(body,searchmain->w/2,searchmain->h);
			liqcell_child_arrange_makegrid(body,3,3);
		return 0;
	}	
	


liqcell *liqcalendarsearch_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqcalendarsearch","form", 800,480);

	if(self)
	{
		//liqcell_propsets(  self, "backcolor", "rgb(255,255,255)" );
		//char *widgetpath = "/media/mmc1/svn/liqbase/libliqbase/media/jacobpics";
		//char *widgetpath = "/media/mmc1/svn/liqbase/libliqbase/media/mer/Mer_files";
		//char *widgetpath = "/media/mmc1/_apg";
		//char *widgetpath = "/media/mmc1/_apg";
		
		
		liqcell *search = liqcell_quickcreatevis("search","liqtop",self->w*0.5,0,   self->w*0.5,self->h*0.9);
		liqcell_child_insert( self, search );
		liqcell_handleradd_withcontext(search,    "mouse",     search_mouse ,self);
		liqcell_handleradd_withcontext(search,    "cleared",   search_cleared ,self);



		liqcell *body = liqcell_quickcreatevis("body","frame",0 ,0,   self->w*0.5,self->h);
	//	liqcell_scan_folder_for_images(body,widgetpath);
		liqcell_scan_folder_for_images(body,"/media/mmc1/_cal");
		liqcell_scan_folder_for_images(body,"/media/mmc1/_apg");
		liqcell_child_insert( self, body );



		liqcell_child_arrange_makegrid(body,3,3);



		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		//liqcell_handleradd(self,    "click",   float_click);

	}
	
	return self;
}




//http://darkeside.blogspot.com/2007/12/linux-inotify-example.html
