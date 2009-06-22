

// this will expand to a filelist
// it should account for: startpath, filefilter, selectedfile


// it should raise events when the folder is change or a file is selected from within

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
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


//#####################################################################
//#####################################################################
//##################################################################### filelist :: by Gary Birkett :)
//#####################################################################
//#####################################################################


	static int filelist_item_select(liqcell *group, liqcell *item)
	{
			//liqapp_log("grp.clr : %s:%s %i",group->name,group->classname,item==NULL);
		liqcell *c = liqcell_getlinkchild_visual(group);
		while(c)
		{

			liqcell_setselected(c,0);
			liqcell_propremoves(c, "backcolor"   );
			liqcell_propremoves(c, "bordercolor"   );
			
			c=liqcell_getlinknext_visual(c);
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






	/**	
	 * filesystemitem widget click
	 */	
	static int filesystemitem_click(liqcell *self, liqcellclickeventargs *args, liqcell *filelist)
	{
		liqapp_log("clickity : %s:%s",self->name,self->classname);
		
	
		if(liqapp_folderexists(self->name))
		{
			// folder
			liqcell_hold(filelist);
			
			//filelist_changedir(filelist, self->name);
			
			liqcell_propsets(filelist, "startpath", self->name );
			liqcell_handlerrun(filelist,"shown",NULL);	// hmmm this should work for handlers not requiring params..
			
			liqcell_release(filelist);
		}
		else
		{
			// file, should raise event
			//filelist_selectfile(filelist,self->name);
			liqcell *backplane = liqcell_child_lookup(filelist, "backplane");	
			filelist_item_select(backplane,self);
		}

		return 1;
	}


static int filelist_scan_folder(liqcell *self,char *path)
{
	
	liqapp_log("filelist_scan_folder opendir: '%s'",path);
	
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	
	
		char *widgetpath = path;
		DIR           *	dir_p;
		struct dirent *	dir_entry_p;
		char 			fn[FILENAME_MAX+1];
		char          * ft;
		
		
		struct pagefilename pfn;
		
		dir_p = opendir( widgetpath );			
		if(!dir_p)
		{
			liqapp_log("filelist_scan_folder opendir failed: '%s'",widgetpath);
			return -1;			// heh thanks kot :)
		}				
		while( NULL != (dir_entry_p = readdir(dir_p)))
		{
			if( dir_entry_p->d_name[0]=='.' && dir_entry_p->d_name[1]==0 )
				continue;
			
			ft=dir_entry_p->d_name;
			
			snprintf(fn , FILENAME_MAX , "%s/%s", widgetpath , ft);
			
			struct stat     statbuf;
			if(stat(fn, &statbuf) == -1)
			{
				liqapp_log("filelist_scan_folder stat failed: '%s'",fn);
				return -1;
			}
			// got the information we need
			if ( S_ISDIR(statbuf.st_mode) )
			{
				//printf(" DIR  ");
				//liqcell_scan_folder_for_images(self,fn);	

					//liqcell *c = liqcell_quickcreatevis(fn,   "filesystemitem",   0,0,0,0    );
					//liqcell_handleradd_withcontext(c,    "click",   filesystemitem_click, self);

					//liqcell_child_insertsorted( backplane, c );
					

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
				//if(
				//	strcasecmp(ext,"png")==0  ||
				//	strcasecmp(ext,"jpg")==0  ||
				//	strcasecmp(ext,"jpeg")==0
				//  )
				{
					// is it a member of the pattern?
					

					liqcell *c = liqcell_quickcreatevis(fn,   "dialogfileselect.filesystemitem",   0,0,0,0    );
					liqcell_handleradd_withcontext(c,    "click",   filesystemitem_click, self);

					liqcell_child_insertsorted( backplane, c );

					
				//	liqcell *c = liqcell_quickcreatevis(fn,   "filesystemitem",   0,0,0,0    );
				//	liqcell_handleradd_withcontext(c,    "click",   filesystemitem_click,self);
				//	liqcell_child_insertsorted( backplane, c );
				}
			}
 		}
		closedir(dir_p);
}


//
static int filelist_changedir(liqcell *self, char *newpath)
{
	
	liqapp_log("Changing filelist on %s to : %s",self->name,newpath);
	
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	
	liqcell_child_removeallvisual( backplane );
	//liqcell_setcaption(title, newpath );
	filelist_scan_folder(self,newpath);
	//liqcell_propsets(self, "startpath", newpath );
	
	liqcell_handlerrun(self,"resize",NULL);	// hmmm this should work for handlers not requiring params..
	
	liqcell_handlerrun(self,"changedir",NULL);
}



/**	
 * filelist widget refresh, all params set, present yourself to the user.
 */	
static int filelist_refresh(liqcell *self,liqcelleventargs *args, void *context)
{
	char * startpath = liqcell_propgets(self, "startpath", "/usr/share/liqbase/media");
	if(!startpath)return 0;
	liqapp_log("filelist_refresh...%s to %s",self->name,startpath);

	
	filelist_changedir(self,startpath);
	return 1;
}

/**	
 * filelist widget shown
 */	
static int filelist_shown(liqcell *self,liqcelleventargs *args, void *context)
{
	//


	char * startpath = liqcell_propgets(self, "startpath", "/usr/share/liqbase/media");
	if(!startpath)return 0;
	liqapp_log("filelist_shown... %s to %s",self->name,startpath);

	
	filelist_changedir(self,startpath);
	return 1;
}


static int filelist_resize(liqcell *self, liqcelleventargs *args, void *context)
{
liqcell *backplane = liqcell_child_lookup(self, "backplane");

	liqcell_setrect(backplane, 0,0,self->w,self->h);
	// make all the items to be the same width as me
	
	int cnt=0;
	
	liqcell *c = liqcell_getlinkchild_visual(backplane);
	while(c)
	{
		cnt++;
		liqcell_setsize(c, self->w,c->h);
		c=liqcell_getlinknext_visual(c);
	}
	liqcell_child_arrange_autoflow(backplane);
	
	if(backplane->h < self->h && cnt>0 && 0)
	{
		// lets spread them out a bit :)
		liqcell_setrect(backplane, 0,0,self->w,self->h);
		int hh = self->h / cnt;
		if(hh*cnt>self->h)hh--;
		
		liqcell *c = liqcell_getlinkchild_visual(backplane);
		while(c)
		{
			cnt++;
			liqcell_setsize(c, self->w,hh);
			c=liqcell_getlinknext_visual(c);
		}
		liqcell_child_arrange_autoflow(backplane);
	}
	
	return 1;
}

liqcell *filelist_create()
{
	liqcell *self = liqcell_quickcreatewidget("filelist","form", 800,480);

	if(self)
	{
		
		
		
		liqcell *backplane = liqcell_quickcreatevis("backplane", "frame", 0,0,self->w,self->h);
		liqcell_handleradd(backplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_append(  self, backplane);
		

		liqcell_handleradd(self, "refresh", filelist_refresh );
		liqcell_handleradd(self, "shown", filelist_shown );
		liqcell_handleradd(self, "resize", filelist_resize );


	}
	return self;
}



