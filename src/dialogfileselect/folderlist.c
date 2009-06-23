

// this will expand to a folderlist
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
//##################################################################### folderlist :: by Gary Birkett :)
//#####################################################################
//#####################################################################


	static int folderlist_item_select(liqcell *group, liqcell *item)
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
	static int filesystemitem_click(liqcell *self, liqcellclickeventargs *args, liqcell *folderlist)
	{
		liqapp_log("clickity : %s:%s",self->name,self->classname);
		
		//folderlist_changedir(folderlist, self->name);
		liqcell *backplane = liqcell_child_lookup(folderlist, "backplane");	
		folderlist_item_select(backplane,self);
	
		if(liqapp_folderexists(self->name))
		{
			// folder
			liqcell_hold(folderlist);
			
			
			liqcell_propsets(folderlist, "startpath", self->name );
			//liqcell_handlerrun(folderlist,"refresh",NULL);	// hmmm this should work for handlers not requiring params..
			liqcell_handlerrun(folderlist,"changedir",NULL);
			liqcell_release(folderlist);
		}
		else
		{
			// file
		}

		return 1;
	}


static int folderlist_scan_folder(liqcell *self,char *path)
{
	
	liqapp_log("folderlist_scan_folder opendir: '%s'",path);
	
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
			liqapp_log("folderlist_scan_folder opendir failed: '%s'",widgetpath);
			return -1;			// heh thanks kot :)
		}				
		while( NULL != (dir_entry_p = readdir(dir_p)))
		{
			if( dir_entry_p->d_name[0]=='.' && (dir_entry_p->d_name[1]=='.' || dir_entry_p->d_name[1]==0) )
				continue;



			
			ft=dir_entry_p->d_name;
			
			snprintf(fn , FILENAME_MAX , "%s/%s", widgetpath , ft);
			
			struct stat     statbuf;
			if(stat(fn, &statbuf) == -1)
			{
				liqapp_log("folderlist_scan_folder stat failed: '%s'",fn);
				return -1;
			}
			// got the information we need
			if ( S_ISDIR(statbuf.st_mode) )
			{
				//printf(" DIR  ");
				//liqcell_scan_folder_for_images(self,fn);	

					liqcell *c = liqcell_quickcreatevis(fn,   "dialogfileselect.filesystemitem",   0,0,0,0    );
					liqcell_handleradd_withcontext(c,    "click",   filesystemitem_click, self);

					liqcell_child_insertsorted( backplane, c );
					

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
					

					//liqcell *c = liqcell_quickcreatevis(fn,   "filesystemitem",   0,0,0,0    );
					//liqcell_handleradd_withcontext(c,    "click",   filesystemitem_click, self);

					//liqcell_child_insertsorted( backplane, c );

					
				//	liqcell *c = liqcell_quickcreatevis(fn,   "filesystemitem",   0,0,0,0    );
				//	liqcell_handleradd_withcontext(c,    "click",   filesystemitem_click,self);
				//	liqcell_child_insertsorted( backplane, c );
				}
			}
 		}
		closedir(dir_p);
}


//
//static int folderlist_changedir(liqcell *self, char *newpath)
//{
	
	
//}

static int backplane_move(liqcell *backplane, liqcelleventargs *args, liqcell *self)
{
	//liqcell *backplane = liqcell_child_lookup(self, "backplane");
	
	char buf[FILENAME_MAX];
	snprintf(buf,sizeof(buf), "[%s].offset", liqcell_propgets(self, "startpath","") );
	
	liqapp_log(buf);
	
	liqcell_propseti(self,buf,backplane->y);
	
}

/**	
 * folderlist widget refresh, all params set, present yourself to the user.
 */	
static int folderlist_refresh(liqcell *self,liqcelleventargs *args, void *context)
{
	liqcell *backplane = liqcell_child_lookup(self, "backplane");

	char * startpath = liqcell_propgets(self, "startpath", "/usr/share/liqbase/media");
	if(!startpath)return 0;
	liqapp_log("folderlist_refresh...%s to %s",self->name,startpath);


	char buf[FILENAME_MAX];
	snprintf(buf,sizeof(buf), "[%s].offset", liqcell_propgets(self, "startpath","") );
	int historyy = liqcell_propgeti(self,buf,0) ;

	//liqapp_log("Changing folderlist on %s to : %s",self->name,startpath);
	
	
	liqcell_child_removeallvisual( backplane );
	//liqcell_setcaption(title, newpath );
	folderlist_scan_folder(self,startpath);
	//liqcell_propsets(self, "startpath", newpath );
	
	liqcell_handlerrun(self,"resize",NULL);	// hmmm this should work for handlers not requiring params..



	liqcell_setpos(backplane,backplane->x,historyy);

	
	return 1;
}

/**	
 * folderlist widget shown
 */	
static int folderlist_shown(liqcell *self,liqcelleventargs *args, void *context)
{
	//


	char * startpath = liqcell_propgets(self, "startpath", NULL);
	if(!startpath)
	{
		liqcell_propsets(self, "startpath", "/usr/share/liqbase/media");
	}
	
	liqcell_handlerrun(self,"refresh",NULL);
	return 1;
}


static int folderlist_resize(liqcell *self, liqcelleventargs *args, void *context)
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

liqcell *folderlist_create()
{
	liqcell *self = liqcell_quickcreatewidget("folderlist","form", 800,480);

	if(self)
	{
		
		
		
		liqcell *backplane = liqcell_quickcreatevis("backplane", "frame", 0,0,self->w,self->h);
		liqcell_handleradd(backplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_append(  self, backplane);
		
		liqcell_handleradd_withcontext(backplane, "move", backplane_move,self );

		liqcell_handleradd(self, "refresh", folderlist_refresh );
		liqcell_handleradd(self, "shown", folderlist_shown );
		liqcell_handleradd(self, "resize", folderlist_resize );


	}
	return self;
}



