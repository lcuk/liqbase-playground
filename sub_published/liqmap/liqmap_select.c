// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqmap_select :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqmap_select widget filter, the system is asking you to filter to the specified .
 */	
static int liqmap_select_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
{
	// system is indicating the user has typed into the search box
	// you are expected to filter your content based upon this searchterm.
	// show or hide details and rearrange contents to apply this filter.
	char *searchterm = NULL;
	args->resultoutof=0;  // total number of searchable contents
	args->resultshown=0;  // count of options remaining after filtering.
	searchterm = args->searchterm;
	if(searchterm && *searchterm)
	{
		 // check the name property
		 args->resultoutof++;
		 if( stristr(self->name,searchterm) != NULL )
		 {
			  args->resultshown++;
		 }
		 // check the classname property
		 args->resultoutof++;
		 if( stristr(self->classname,searchterm) != NULL )
		 {
			  args->resultshown++;
		 }
		 // check any other properties or children and increment counters
		 // filter out list items recursively
	}
	return 0;
}
/**	
 * liqmap_select widget refresh, all params set, present yourself to the user.
 */	
static int liqmap_select_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmap_select dialog_open - the user zoomed into the dialog
 */	
static int liqmap_select_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqmap_select dialog_close - the dialog was closed
 */	
static int liqmap_select_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqmap_select widget shown - occurs once per lifetime
 */	
static int liqmap_select_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmap_select mouse - occurs all the time as you stroke the screen
 */	
static int liqmap_select_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_select click - occurs when a short mouse stroke occured
 */	
static int liqmap_select_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_select keypress - the user pressed a key
 */	
static int liqmap_select_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_select keyrelease - the user released a key
 */	
static int liqmap_select_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_select paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqmap_select_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqmap_select dynamic resizing
 */	
static int liqmap_select_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *picture1 = liqcell_child_lookup(self, "picture1");
		liqcell *itemx = liqcell_child_lookup(picture1, "itemx");
	liqcell *cmdrefresh = liqcell_child_lookup(self, "cmdrefresh");
	liqcell *command2 = liqcell_child_lookup(self, "command2");
	liqcell_setrect_autoscale( title, 0,0, 800,48, sx,sy);
	liqcell_setrect_autoscale( itemx, 0,0, 802,52, sx,sy);
	liqcell_setrect_autoscale( picture1, 0,48, 800,432, sx,sy);
	liqcell_setrect_autoscale( cmdrefresh, 400,432, 190,48, sx,sy);
	liqcell_setrect_autoscale( command2, 594,432, 206,48, sx,sy);
	return 0;
}

/**	
 * liqmap_select.cmdrefresh clicked
 */	
static int cmdrefresh_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqmap_select)
{
	return 0;
}
/**	
 * liqmap_select.command2 clicked
 */	
static int command2_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqmap_select)
{
	return 0;
}
/**	
 * liqmap_select_child_test_seek this function shows how to access members
 */	
	  
static void liqmap_select_child_test_seek(liqcell *liqmap_select)
{	  
	liqcell *title = liqcell_child_lookup(liqmap_select, "title");
	liqcell *picture1 = liqcell_child_lookup(liqmap_select, "picture1");
		liqcell *itemx = liqcell_child_lookup(picture1, "itemx");
	liqcell *cmdrefresh = liqcell_child_lookup(liqmap_select, "cmdrefresh");
	liqcell *command2 = liqcell_child_lookup(liqmap_select, "command2");
}	  
/**	
 * create a new liqmap_select widget
 */	
liqcell *liqmap_select_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqmap_select", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqmap_select'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 48);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "liqmap map select" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# picture1:picturebox
	liqcell *picture1 = liqcell_quickcreatevis("picture1", "picturebox", 0, 48, 800, 432);
	liqcell_setfont(	picture1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_propsets(  picture1, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  picture1, "backcolor", "rgb(128,64,64)" );
		//############################# itemx:liqmap_selectitem
		liqcell *itemx = liqcell_quickcreatevis("itemx", "liqmap_selectitem", 0, 0, 802, 52);
		liqcell_child_append(  picture1, itemx);
	liqcell_child_append(  self, picture1);
	//############################# cmdrefresh:commandbutton
	liqcell *cmdrefresh = liqcell_quickcreatevis("cmdrefresh", "commandbutton", 400, 432, 190, 48);
	liqcell_setfont(	cmdrefresh, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdrefresh, "Refresh" );
	liqcell_propsets(  cmdrefresh, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  cmdrefresh, "bordercolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdrefresh, "backcolor", "xrgb(0,64,64)" );
	liqcell_handleradd_withcontext(cmdrefresh, "click", cmdrefresh_click, self );
	liqcell_child_append(  self, cmdrefresh);
	//############################# command2:commandbutton
	liqcell *command2 = liqcell_quickcreatevis("command2", "commandbutton", 594, 432, 206, 48);
	liqcell_setfont(	command2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(command2, "Select" );
	liqcell_propsets(  command2, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  command2, "bordercolor", "rgb(255,255,255)" );
	liqcell_propsets(  command2, "backcolor", "xrgb(0,64,0)" );
	liqcell_handleradd_withcontext(command2, "click", command2_click, self );
	liqcell_child_append(  self, command2);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/liqmap/media/liqmap_select_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", liqmap_select_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", liqmap_select_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqmap_select_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", liqmap_select_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqmap_select_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqmap_select_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", liqmap_select_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", liqmap_select_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqmap_select_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqmap_select_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqmap_select_dialog_close ,self);
	return self;
}

