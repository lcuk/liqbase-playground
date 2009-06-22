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



extern int liqcell_showdebugboxes;




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




		
//#####################################################################
//#####################################################################
//##################################################################### dialogfileselect :: by gary birkett
//#####################################################################
//#####################################################################













//
static int dialogfileselect_changedir(liqcell *self, char *xxnewpath)
{
	char *newpath=strdup(xxnewpath);
	if(!newpath)return 0;
	liqapp_log("Changing dir on %s to : %s",self->name,newpath);
	liqcell *folderlist = liqcell_child_lookup(self, "folderlist");
	liqcell *filelist = liqcell_child_lookup(self, "filelist");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *icon = liqcell_child_lookup(self, "icon");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *label6 = liqcell_child_lookup(self, "label6");
	liqcell *label7 = liqcell_child_lookup(self, "label7");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	
	
	liqcell_propsets(folderlist, "startpath", newpath );
	liqcell_handlerrun(folderlist,"refresh",NULL);
	
	
	
	liqcell_propsets(filelist, "startpath", newpath );
	liqcell_handlerrun(filelist,"refresh",NULL);

	
	liqcell_setcaption(title, newpath );	
	liqcell_propsets(self, "startpath", newpath );
	
	
	free(newpath);
	
}

/**	
 * dialogfileselect.title clicked
 */	
static int title_click(liqcell *title,liqcelleventargs *args, liqcell *self)
{
	liqcell *folderlist = liqcell_child_lookup(self, "folderlist");
	liqcell *filelist = liqcell_child_lookup(self, "filelist");
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
		
			dialogfileselect_changedir(self, allpath);
		}
		else
		{
			dialogfileselect_changedir(self, "/");
		}
		
	}

}

/**	
 * dialogfileselect widget shown
 */	
static int dialogfileselect_shown(liqcell *self,liqcelleventargs *args, void *context)
{
	// 20090618_020248 lcuk : expect to be passed a parameter to specify "startpath"
	char * startpath = liqcell_propgets(self, "startpath", "/usr/share/liqbase/media");
	liqapp_log("dialogfileselect.startpath=%s",startpath);
	dialogfileselect_changedir(self, startpath);
}
/**	
 * dialogfileselect widget refresh, all params set, present yourself to the user.
 */	
static int dialogfileselect_refresh(liqcell *self,liqcelleventargs *args, void *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
}
/**	
 * dialogfileselect.buttonaccept clicked
 */	
static int buttonaccept_click(liqcell *self,liqcelleventargs *args, liqcell *dialogfileselect)
{
	// finished now :)
	liqcell_setvisible(dialogfileselect,0);
}



/**	
 * folderlist changedir
 */	
static int folderlist_changedir(liqcell *self,liqcelleventargs *args, liqcell *dialogfileselect)
{
	char * startpath = liqcell_propgets(self, "startpath", "/usr/share/liqbase/media");
	liqapp_log("folderlist_changedir=%s",startpath);
	dialogfileselect_changedir(dialogfileselect, startpath);

}

/**	
 * dialogfileselect.quicklocation clicked
 */	
static int quicklocation_click(liqcell *self,liqcelleventargs *args, liqcell *dialogfileselect)
{
	// read the location from a property :)
	
	char * startpath = liqcell_propgets(self, "startpath", "/usr/share/liqbase/media");
	dialogfileselect_changedir(dialogfileselect, startpath);
}

/**	
 * dialogfileselect_child_test_seek this function shows how to access members
 */	
	  
static void dialogfileselect_child_test_seek(liqcell *self)
{	  
	//liqcell *buttonaccept = liqcell_child_lookup(self, "buttonaccept");
	liqcell *folderlist = liqcell_child_lookup(self, "folderlist");
	liqcell *filelist = liqcell_child_lookup(self, "filelist");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *icon = liqcell_child_lookup(self, "icon");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *label6 = liqcell_child_lookup(self, "label6");
	liqcell *label7 = liqcell_child_lookup(self, "label7");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
}	  
/**	
 * create a new dialogfileselect widget
 */	
liqcell *dialogfileselect_create()
{
	
	//liqcell_showdebugboxes=1;
	
	liqcell *self = liqcell_quickcreatewidget("dialogfileselect", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'dialogfileselect'"); return NULL;  } 
	
	//############################# folderlist:frame
	liqcell *folderlist = liqcell_quickcreatevis("folderlist", "dialogfileselect.folderlist", 54, 46, 344, 422);
	liqcell_handleradd_withcontext(folderlist, "changedir", folderlist_changedir, self );
	liqcell_child_append(  self, folderlist);
	//############################# filelist:frame
	liqcell *filelist = liqcell_quickcreatevis("filelist", "dialogfileselect.filelist", 402, 46, 392, 480-46-40);
	liqcell_child_append(  self, filelist);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 62, 0, 800-62, 42);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "path" );
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
	liqcell_handleradd_withcontext(icon, "click", title_click, self );
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


	//############################# buttonview:commandbutton
	liqcell *buttonview = liqcell_quickcreatevis("buttonview", "commandbutton", 400, 440, 200, 40);
	liqcell_setfont(	buttonview, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (35), 0) );
	liqcell_setcaption(buttonview, "view" );
	liqcell_propsets(  buttonview, "textcolor",   "rgb(100,100,255)" );
	liqcell_propsets(  buttonview, "backcolor",   "rgb(0,0,40)" );
	liqcell_propsets(  buttonview, "bordercolor", "rgb(0,0,150)" );
	liqcell_propseti(  buttonview, "textalign",   2 );
	liqcell_propseti(  buttonview, "textaligny",  2 );
	liqcell_setvisible(buttonview, 0);
	liqcell_child_append(  self, buttonview);



	//############################# buttonaccept:commandbutton
	liqcell *buttonaccept = liqcell_quickcreatevis("buttonaccept", "commandbutton", 600, 440, 200, 40);
	liqcell_setfont(	buttonaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (35), 0) );
	liqcell_setcaption(buttonaccept, "select" );
	liqcell_propsets(  buttonaccept, "textcolor",   "rgb(0,255,0)" );
	liqcell_propsets(  buttonaccept, "backcolor",   "rgb(0,40,0)" );
	liqcell_propsets(  buttonaccept, "bordercolor", "rgb(0,150,0)" );
	liqcell_propseti(  buttonaccept, "textalign",   2 );
	liqcell_propseti(  buttonaccept, "textaligny",  2 );
	liqcell_handleradd_withcontext(buttonaccept, "click", buttonaccept_click, self );

	liqcell_child_append(  self, buttonaccept);




	liqcell_handleradd(self, "refresh", dialogfileselect_refresh );
	liqcell_handleradd(self, "shown", dialogfileselect_shown );
	
	
	//	dialogfileselect_changedir(self, "/home/user/svn/liqbase-playground/src/media");

	
	return self;
}





//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when dialogfileselect is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"dialogfileselect canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}

int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"dialogfileselect" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"dialogfileselect liqapp_init failed"); }
	 }
	 liqcell *self = dialogfileselect_create();
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}
