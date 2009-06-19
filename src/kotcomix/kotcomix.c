// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

static int lowest(int a,int b)
{
	if(abs(a)<abs(b))
	{
		liqapp_log("lowest %i :: %i = a %i",a,b,a);
		return a;
	}
	liqapp_log("lowest %i :: %i = b %i",a,b,b);
	return b;
}


static int dimension_ensurevisible( int rs,int re,    int ps,int pe, int ss,int se)
{
	// calculate the minimal adjustment within a dimension required to ensure S is visible through the portal that R provides
	// the adjustment will be applied to P upon returning from this function
	// to slide the rule along so s is visible :)
	//ss += ps;	// start by adjusting 
	//se += pe;
	
	liqapp_log("dim ol: r(%i,%i)   p(%i,%i)    s(%i,%i)",   rs,re,     ps,pe,     ss,se);
	if(re<=ss)
	{
		// S is way below, lets adjust
		return lowest(ss-rs,se-re);
	}
	if(rs<=ss)
	{
		// S is actually somewhat visible
		// but we might be chopping off the bottom of it
		if(re<=se)
		{
			return lowest(ss-rs,se-re);
		}
		// otherwise we let it be, floating somewhere within
		return 0;
	}

	// S is partially or entirely above us
	return lowest(ss-rs,se-re);
}

extern int liqcell_showdebugboxes;

static int liqcell_ensurevisible(liqcell *self)
{
	liqapp_log("ensure: %s",self->name);
	int xs=self->x;
	int xe=self->x+self->w;
	int ys=self->y;
	int ye=self->y+self->h;
	
	liqcell *p=liqcell_getlinkparent(self);
	//while(p)
	if(p)
	{
		liqcell *r=liqcell_getlinkparent(p);
		if(r)
		{
			liqapp_log("trying in : %s",p->name);
			xs+=p->x;
			xe+=p->x;
			ys+=p->y;
			ye+=p->y;

			//
			int ax = -dimension_ensurevisible(0,r->w,   p->x,p->x+p->w,   xs,xe);
			int ay = -dimension_ensurevisible(0,r->h,   p->y,p->y+p->h,   ys,ye);


			liqapp_log("gave me : a(%i,%i)",  ax,ay);

			liqcell_adjustpos(p,ax,ay);
			xs-=ax;
			xe-=ax;
			ys-=ay;
			ye-=ay;

		}
		//p=r;
	}
	
	
	
/*	
	liqcell *c = liqcell_getlinkchild(self);
	while(c)
	{
		if(liqcell_getflagvisual(c))
		{
			if(!liqcell_getselected(c)) liqcell_setselected(c,1);
		}
		c=liqcell_getlinknext(c);
	}
 */	return 0;
}



static int liqcell_child_selectall(liqcell *self)
{
	liqcell *c = liqcell_getlinkchild(self);
	while(c)
	{
		if(liqcell_getflagvisual(c))
		{
			if(!liqcell_getselected(c)) liqcell_setselected(c,1);
		}
		c=liqcell_getlinknext(c);
	}
}

static int liqcell_child_selectnone(liqcell *self)
{
	liqcell *c = liqcell_getlinkchild(self);
	while(c)
	{
		if(liqcell_getflagvisual(c))
		{
			if(liqcell_getselected(c)) liqcell_setselected(c,0);
		}
		c=liqcell_getlinknext(c);
	}
}
static int liqcell_child_selectinvert(liqcell *self)
{
	liqcell *c = liqcell_getlinkchild(self);
	while(c)
	{
		if(liqcell_getflagvisual(c))
		{
			if(liqcell_getselected(c))
				liqcell_setselected(c,0);
			else
				liqcell_setselected(c,1);
		}
		c=liqcell_getlinknext(c);
	}
}

static int liqcell_child_propremoves(liqcell *self,char *propname)
{
	liqcell *c = liqcell_getlinkchild(self);
	while(c)
	{
		//if(liqcell_getflagvisual(c))
		//{
			liqcell_propremoves(c, propname  );
		//}
		c=liqcell_getlinknext(c);
	}
}


































static int liqcell_scan_folder_for_folders(liqcell *self,char *path,char *classtocreate,void *clickhandler,liqcell*clickcontext)
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
			liqapp_log("liqcell_scan_folder_for_folders opendir failed: '%s'",widgetpath);
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
				liqapp_log("liqcell_scan_folder_for_folders stat failed: '%s'",fn);
				return -1;
			}
			// got the information we need
			if ( S_ISDIR(statbuf.st_mode) )
			{
				//printf(" DIR  ");
				//liqcell_scan_folder_for_images(self,fn);	

					liqcell *c = liqcell_quickcreatevis(fn,   classtocreate,   0,0,0,0    );

					liqcell_child_insertsorted( self, c );
					
					liqcell_handleradd_withcontext(c,    "click",   clickhandler,clickcontext);

			}
/*			else
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
					liqcell *c = liqcell_quickcreatevis(fn,   "picture",   0,0,0,0    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"imagefilename",fn);
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					liqcell_handleradd(c,    "click",   widget_click);
					liqcell_child_insertsorted( self, c );
				}
			}
 */		}
		closedir(dir_p);
}





static int liqcell_scan_folder_for_images(liqcell *self,char *path,char *classtocreate,void *clickhandler,liqcell*clickcontext)
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
			liqapp_log("liqcell_scan_folder_for_folders opendir failed: '%s'",widgetpath);
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
				liqapp_log("liqcell_scan_folder_for_folders stat failed: '%s'",fn);
				return -1;
			}
			// got the information we need
			if ( S_ISDIR(statbuf.st_mode) )
			{
				//printf(" DIR  ");
				//liqcell_scan_folder_for_images(self,fn);	

				//	liqcell *c = liqcell_quickcreatevis(fn,   classtocreate,   0,0,0,0    );

				//	liqcell_child_insertsorted( self, c );

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
					strcasecmp(ext,"png")==0  ||
					strcasecmp(ext,"jpg")==0  ||
					strcasecmp(ext,"jpeg")==0
				  )
				{
					liqcell *c = liqcell_quickcreatevis(fn,   classtocreate,   0,0,0,0    );
					liqcell_child_insertsorted( self, c );
					liqcell_handleradd_withcontext(c,    "click",   clickhandler,clickcontext);
				}
			}
 		}
		closedir(dir_p);
}

		
//#####################################################################
//#####################################################################
//##################################################################### kotcomix :: by gary birkett
//#####################################################################
//#####################################################################

	static int kotcomix_list_backplane_item_select(liqcell *group, liqcell *item)
	{
			//liqapp_log("grp.clr : %s:%s %i",group->name,group->classname,item==NULL);
		liqcell *c = liqcell_getlinkchild(group);
		while(c)
		{
			if(liqcell_getflagvisual(c))
			{
				liqcell_setselected(c,0);
				liqcell_propremoves(c, "backcolor"   );
				liqcell_propremoves(c, "bordercolor"   );
			}
			c=liqcell_getlinknext(c);
		}		
		if(item)
		{
			//liqapp_log("itm.sel : %s:%s",item->name,item->classname);
			liqcell_setselected(item,1);
			//liqcell_propsets(self, "textcolor",   "rgb(0,255,0)" );
			liqcell_propsets(item, "backcolor",   "rgb(0,0,80)" );
			liqcell_propsets(item, "bordercolor", "rgb(255,255,255)" );
		}
		return 1;
	}


	static int kotcomix_selectfile(liqcell *self, char *filename)
	{
		liqcell *buttonaccept = liqcell_child_lookup(self, "buttonaccept");
		liqcell *folderlist = liqcell_child_lookup(self, "folderlist");
			liqcell *folderbackplane = liqcell_child_lookup(folderlist, "folderbackplane");
				//liqcell *folderitem1 = liqcell_child_lookup(folderbackplane, "folderitem1");
		liqcell *filelist = liqcell_child_lookup(self, "filelist");
			liqcell *filebackplane = liqcell_child_lookup(filelist, "filebackplane");
				//liqcell *fileitem1 = liqcell_child_lookup(filebackplane, "fileitem1");
		liqcell *title = liqcell_child_lookup(self, "title");
		liqcell *icon = liqcell_child_lookup(self, "icon");
		liqcell *label5 = liqcell_child_lookup(self, "label5");
		liqcell *label6 = liqcell_child_lookup(self, "label6");
		liqcell *label7 = liqcell_child_lookup(self, "label7");
		liqcell *label1 = liqcell_child_lookup(self, "label1");
		
		liqcell *folderitem1 = liqcell_child_lookup_simple(folderbackplane,filename);
		kotcomix_list_backplane_item_select(folderbackplane, folderitem1 );
		if(folderitem1) liqcell_ensurevisible(folderitem1);
		
		liqcell *fileitem1 = liqcell_child_lookup_simple(filebackplane,filename);
		kotcomix_list_backplane_item_select(filebackplane, fileitem1 );
		if(fileitem1) liqcell_ensurevisible(fileitem1);
					
	}
		
	static int kotcomix_changedir(liqcell *self, char *newpath);


	static int kotcomix_folderitem_click(liqcell *self, liqcellclickeventargs *args, liqcell *kotcomix)
	{
		liqapp_log("clickity : %s:%s",self->name,self->classname);
		
	
		if(liqapp_folderexists(self->name))
		{
			// folder
			liqcell_hold(self);
			
			kotcomix_changedir(kotcomix, self->name);
			
			liqcell_release(self);
		}
		else
		{
			// file
			kotcomix_selectfile(kotcomix,self->name);
		}
		
	
	/*
		
		
		liqcell *par = liqcell_getlinkparent(self);
		
		liqcell *c = liqcell_getlinkchild(par);
		while(c)
		{
			if(liqcell_getflagvisual(c))
			{
				liqcell_setselected(c,0);
				liqcell_propremoves(c, "backcolor"   );
			}
			c=liqcell_getlinknext(c);
		}		
		
		//liqcell_child_selectnone(liqcell_getlinkparent(self));
		
		//
		if(liqapp_pathexists(self->name))
		{
			// folder?
		}
		else
		{
			// file?
		}
		
		
		//liqapp_log("general click");
		//args->newdialogtoopen = self;
        if(liqcell_getselected(self))
        {
			liqcell_setselected(self,0);
			//liqcell_propremoves(self, "textcolor"   );
			liqcell_propremoves(self, "backcolor"   );
			//liqcell_propremoves(self, "bordercolor" );
        }
        else
        {
			liqcell_setselected(self,1);
			//liqcell_propsets(self, "textcolor",   "rgb(0,255,0)" );
			liqcell_propsets(self, "backcolor",   "rgb(0,0,80)" );
			//liqcell_propsets(self, "bordercolor", "rgb(255,255,255)" );
        }

	*/

		return 1;
	}














//
static int kotcomix_changedir(liqcell *self, char *newpath)
{
	liqcell *buttonaccept = liqcell_child_lookup(self, "buttonaccept");
	liqcell *folderlist = liqcell_child_lookup(self, "folderlist");
		liqcell *folderbackplane = liqcell_child_lookup(folderlist, "folderbackplane");
			//liqcell *folderitem1 = liqcell_child_lookup(folderbackplane, "folderitem1");
	liqcell *filelist = liqcell_child_lookup(self, "filelist");
		liqcell *filebackplane = liqcell_child_lookup(filelist, "filebackplane");
			//liqcell *fileitem1 = liqcell_child_lookup(filebackplane, "fileitem1");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *icon = liqcell_child_lookup(self, "icon");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *label6 = liqcell_child_lookup(self, "label6");
	liqcell *label7 = liqcell_child_lookup(self, "label7");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	
	
	liqcell_child_removeallvisual( folderbackplane );
	liqcell_child_removeallvisual( filebackplane );
	
	liqcell_setcaption(title, newpath );
	
	liqcell_propsets(self, "startpath", newpath );
	
	
	liqcell_setrect(folderbackplane, 0,0,folderlist->w,folderlist->h);

	liqcell_setrect(filebackplane  , 0,0,filelist->w,filelist->h);
	
	// walk the directory and add items as discovered
	
	liqcell_scan_folder_for_folders( folderbackplane, newpath, "kotcomix.folderitem" , kotcomix_folderitem_click ,self);
	liqcell_scan_folder_for_images(  folderbackplane, newpath, "kotcomix.folderitem" , kotcomix_folderitem_click ,self);
	
	//liqcell_child_arrange_makegrid( folderbackplane, 1,10 );
	//liqcell_child_arrange_easycol(  folderbackplane );
	liqcell_child_arrange_autoflow(folderbackplane);
	
	liqcell_scan_folder_for_images(  filebackplane, newpath, "kotcomix.fileitem" , kotcomix_folderitem_click ,self);
	
	//liqcell_child_arrange_makegrid( filebackplane, 3,3 );
	//liqcell_child_arrange_easycol(  filebackplane );
	liqcell_child_arrange_autoflow(filebackplane);
}

/**	
 * kotcomix.title clicked
 */	
static int title_click(liqcell *title,liqcelleventargs *args, liqcell *self)
{
	liqcell *buttonaccept = liqcell_child_lookup(self, "buttonaccept");
	liqcell *folderlist = liqcell_child_lookup(self, "folderlist");
		liqcell *folderbackplane = liqcell_child_lookup(folderlist, "folderbackplane");
			//liqcell *folderitem1 = liqcell_child_lookup(folderbackplane, "folderitem1");
	liqcell *filelist = liqcell_child_lookup(self, "filelist");
		liqcell *filebackplane = liqcell_child_lookup(filelist, "filebackplane");
			//liqcell *fileitem1 = liqcell_child_lookup(filebackplane, "fileitem1");
	//liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *icon = liqcell_child_lookup(self, "icon");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *label6 = liqcell_child_lookup(self, "label6");
	liqcell *label7 = liqcell_child_lookup(self, "label7");
	liqcell *label1 = liqcell_child_lookup(self, "label1");	
	
	
	char * startpath = liqcell_propgets(self, "startpath", "/usr/share/liqbase/media");
	if(!startpath)return 0;
	// take a copy
	char buf[FILENAME_MAX];
	snprintf(buf,sizeof(buf),startpath);
	char *allpath=buf;	
	char *lastpart = liqapp_filename_walkoverpath(allpath);
	
	if(lastpart && lastpart>allpath)
	{
		lastpart[-1]=0;
		
		if(*allpath)
		{
		
			kotcomix_changedir(self, allpath);
		}
		else
		{
			kotcomix_changedir(self, "/");
		}
		
	}

}

/**	
 * kotcomix widget shown
 */	
static int kotcomix_shown(liqcell *self,liqcelleventargs *args, void *context)
{
	// 20090618_020248 lcuk : expect to be passed a parameter to specify "startpath"
	char * startpath = liqcell_propgets(self, "startpath", "/usr/share/liqbase/media");
	
	liqapp_log("kotcomix.startpath=%s",startpath);
	
	kotcomix_changedir(self, startpath);
}
/**	
 * kotcomix widget refresh, all params set, present yourself to the user.
 */	
static int kotcomix_refresh(liqcell *self,liqcelleventargs *args, void *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
}
/**	
 * kotcomix.buttonaccept clicked
 */	
static int buttonaccept_click(liqcell *self,liqcelleventargs *args, liqcell *kotcomix)
{
}


/**	
 * kotcomix.quicklocation clicked
 */	
static int quicklocation_click(liqcell *self,liqcelleventargs *args, liqcell *kotcomix)
{
	// read the location from a property :)
	
	char * startpath = liqcell_propgets(self, "startpath", "/usr/share/liqbase/media");
	
	kotcomix_changedir(kotcomix, startpath);
}

/**	
 * kotcomix_child_test_seek this function shows how to access members
 */	
	  
static void kotcomix_child_test_seek(liqcell *self)
{	  
	//liqcell *buttonaccept = liqcell_child_lookup(self, "buttonaccept");
	liqcell *folderlist = liqcell_child_lookup(self, "folderlist");
		liqcell *folderbackplane = liqcell_child_lookup(folderlist, "folderbackplane");
			//liqcell *folderitem1 = liqcell_child_lookup(folderbackplane, "folderitem1");
	liqcell *filelist = liqcell_child_lookup(self, "filelist");
		liqcell *filebackplane = liqcell_child_lookup(filelist, "filebackplane");
			//liqcell *fileitem1 = liqcell_child_lookup(filebackplane, "fileitem1");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *icon = liqcell_child_lookup(self, "icon");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *label6 = liqcell_child_lookup(self, "label6");
	liqcell *label7 = liqcell_child_lookup(self, "label7");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
}	  
/**	
 * create a new kotcomix widget
 */	
liqcell *kotcomix_create()
{
	
	//liqcell_showdebugboxes=1;
	
	liqcell *self = liqcell_quickcreatewidget("kotcomix", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'kotcomix'"); return NULL;  } 
	
	//############################# folderlist:frame
	liqcell *folderlist = liqcell_quickcreatevis("folderlist", "frame", 54, 46, 344, 422);
	//liqcell_setfont(	folderlist, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(folderlist, "Frame1" );
	//liqcell_propsets(  folderlist, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  folderlist, "backcolor", "rgb(64,64,64)" );
		//############################# folderbackplane:frame
		liqcell *folderbackplane = liqcell_quickcreatevis("folderbackplane", "frame", 0,0,folderlist->w,folderlist->h);
		//liqcell_setfont(	folderbackplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_setcaption(folderbackplane, "" );
		//liqcell_propsets(  folderbackplane, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  folderbackplane, "backcolor", "rgb(128,128,128)" );
			//############################# folderitem1:folderitem
			liqcell *folderitem1 = liqcell_quickcreatevis("folderitem1", "folderitem", 4, 4, 342, 32);
			liqcell_child_append(  folderbackplane, folderitem1);
		liqcell_handleradd(folderbackplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_append(  folderlist, folderbackplane);
	liqcell_child_append(  self, folderlist);
	//############################# filelist:frame
	liqcell *filelist = liqcell_quickcreatevis("filelist", "frame", 402, 46, 392, 422);
	//liqcell_setfont(	filelist, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(filelist, "Frame1" );
	//liqcell_propsets(  filelist, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  filelist, "backcolor", "rgb(64,64,64)" );
		//############################# filebackplane:frame
		liqcell *filebackplane = liqcell_quickcreatevis("filebackplane", "frame", 0,0,filelist->w,filelist->h);
		//liqcell_setfont(	filebackplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_setcaption(filebackplane, "Frame1" );
		//liqcell_propsets(  filebackplane, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  filebackplane, "backcolor", "rgb(128,128,128)" );
			//############################# fileitem1:fileitem
			//liqcell *fileitem1 = liqcell_quickcreatevis("fileitem1", "fileitem", 0, 0, 438, 32);
			//liqcell_child_append(  filebackplane, fileitem1);
			
		liqcell_handleradd(filebackplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		
		liqcell_child_append(  filelist, filebackplane);
	liqcell_child_append(  self, filelist);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 62, 0, 546, 42);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "kot comix" );
	liqcell_propsets(  title, "textcolor", "rgb(255,100,100)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_handleradd_withcontext(title, "click", title_click, self );
	liqcell_child_append(  self, title);
	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 2, 2, 52, 40);
	liqcell_setfont(	icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(icon, ".." );
	liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  icon, "backcolor", "rgb(0,0,128)" );
	liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);
	//############################# label5:label
	liqcell *label5 = liqcell_quickcreatevis("label5", "label", 2, 90, 52, 76);
	liqcell_setfont(	label5, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label5, "docs" );
	liqcell_propsets(  label5, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label5, "backcolor", "rgb(0,128,128)" );
	liqcell_propsets(  label5, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label5, "textalign", 2 );

	liqcell_propsets(  label5, "startpath", "/home/user/MyDocs" );
	liqcell_handleradd_withcontext(label5, "click", quicklocation_click, self );

	liqcell_child_append(  self, label5);
	//############################# label6:label
	liqcell *label6 = liqcell_quickcreatevis("label6", "label", 2, 172, 52, 68);
	liqcell_setfont(	label6, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label6, "mmc1" );
	liqcell_propsets(  label6, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label6, "backcolor", "rgb(0,128,128)" );
	liqcell_propsets(  label6, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label6, "textalign", 2 );
	
	liqcell_propsets(  label6, "startpath", "/media/mmc1" );
	liqcell_handleradd_withcontext(label6, "click", quicklocation_click, self );

	liqcell_child_append(  self, label6);
	//############################# label7:label
	liqcell *label7 = liqcell_quickcreatevis("label7", "label", 0, 246, 54, 64);
	liqcell_setfont(	label7, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label7, "mmc2" );
	liqcell_propsets(  label7, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label7, "backcolor", "rgb(0,128,128)" );
	liqcell_propsets(  label7, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label7, "textalign", 2 );
	liqcell_child_append(  self, label7);

	liqcell_propsets(  label7, "startpath", "/media/mmc2" );
	liqcell_handleradd_withcontext(label7, "click", quicklocation_click, self );

	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 0, 318, 54, 64);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label1, "liq" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,128,128)" );
	liqcell_propsets(  label1, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label1, "textalign", 2 );

	liqcell_propsets(  label1, "startpath", "/usr/share/liqbase/media" );
	liqcell_handleradd_withcontext(label1, "click", quicklocation_click, self );

	liqcell_child_append(  self, label1);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );

	//############################# buttonaccept:commandbutton
	liqcell *buttonaccept = liqcell_quickcreatevis("buttonaccept", "commandbutton", 600, 440, 200, 40);
	liqcell_setfont(	buttonaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (35), 0) );
	liqcell_setcaption(buttonaccept, "save" );
	liqcell_propsets(  buttonaccept, "textcolor",   "rgb(0,255,0)" );
	liqcell_propsets(  buttonaccept, "backcolor",   "rgb(0,40,0)" );
	liqcell_propsets(  buttonaccept, "bordercolor", "rgb(0,150,0)" );
	liqcell_propseti(  buttonaccept, "textalign",   2 );
	liqcell_propseti(  buttonaccept, "textaligny",  2 );
	liqcell_child_append(  self, buttonaccept);




	liqcell_handleradd(self, "refresh", kotcomix_refresh );
	liqcell_handleradd(self, "shown", kotcomix_shown );
	
	
	//	kotcomix_changedir(self, "/home/user/svn/liqbase-playground/src/media");

	
	return self;
}





//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when kotcomix is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"kotcomix canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}

int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"kotcomix" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"kotcomix liqapp_init failed"); }
	 }
	 liqcell *self = kotcomix_create();
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}
