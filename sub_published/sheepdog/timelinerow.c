// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### timelinerow :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * timelinerow widget filter, the system is asking you to filter to the specified .
 */	
static int timelinerow_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * timelinerow widget refresh, all params set, present yourself to the user.
 */	
static int timelinerow_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * timelinerow dialog_open - the user zoomed into the dialog
 */	
static int timelinerow_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * timelinerow dialog_close - the dialog was closed
 */	
static int timelinerow_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * timelinerow widget shown - occurs once per lifetime
 */	
static int timelinerow_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * timelinerow mouse - occurs all the time as you stroke the screen
 */	
static int timelinerow_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * timelinerow click - occurs when a short mouse stroke occured
 */	
static int timelinerow_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * timelinerow keypress - the user pressed a key
 */	
static int timelinerow_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * timelinerow keyrelease - the user released a key
 */	
static int timelinerow_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * timelinerow paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int timelinerow_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * timelinerow dynamic resizing
 */	
static int timelinerow_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdconfig = liqcell_child_lookup(self, "cmdconfig");
	liqcell *cmdprev = liqcell_child_lookup(self, "cmdprev");
	liqcell *cmdframecount = liqcell_child_lookup(self, "cmdframecount");
	liqcell *cmdnext = liqcell_child_lookup(self, "cmdnext");
	liqcell_setrect_autoscale( title, 4,8, 146,40, sx,sy);
	liqcell_setrect_autoscale( cmdconfig, 726,4, 52,48, sx,sy);
	liqcell_setrect_autoscale( cmdprev, 158,4, 50,48, sx,sy);
	liqcell_setrect_autoscale( cmdframecount, 212,4, 454,48, sx,sy);
	liqcell_setrect_autoscale( cmdnext, 670,4, 52,48, sx,sy);
	return 0;
}

/**	
 * timelinerow.cmdconfig clicked
 */	
static int cmdconfig_click(liqcell *self,liqcellclickeventargs *args, liqcell *timelinerow)
{
	return 0;
}
/**	
 * timelinerow.cmdprev clicked
 */	
static int cmdprev_click(liqcell *self,liqcellclickeventargs *args, liqcell *timelinerow)
{
	return 0;
}
/**	
 * timelinerow.cmdframecount clicked
 */	
static int cmdframecount_click(liqcell *self,liqcellclickeventargs *args, liqcell *timelinerow)
{
	return 0;
}
/**	
 * timelinerow.cmdnext clicked
 */	
static int cmdnext_click(liqcell *self,liqcellclickeventargs *args, liqcell *timelinerow)
{
	return 0;
}
/**	
 * timelinerow_child_test_seek this function shows how to access members
 */	
	  
static void timelinerow_child_test_seek(liqcell *timelinerow)
{	  
	liqcell *title = liqcell_child_lookup(timelinerow, "title");
	liqcell *cmdconfig = liqcell_child_lookup(timelinerow, "cmdconfig");
	liqcell *cmdprev = liqcell_child_lookup(timelinerow, "cmdprev");
	liqcell *cmdframecount = liqcell_child_lookup(timelinerow, "cmdframecount");
	liqcell *cmdnext = liqcell_child_lookup(timelinerow, "cmdnext");
	liqcell *resize1 = liqcell_child_lookup(timelinerow, "resize1");
}	  
/**	
 * create a new timelinerow widget
 */	
liqcell *timelinerow_create()
{
	liqcell *self = liqcell_quickcreatewidget("timelinerow", "form", 784, 58);
	if(!self) {liqapp_log("liqcell error not create 'timelinerow'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 4, 8, 146, 40);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "timeline" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdconfig:label
	liqcell *cmdconfig = liqcell_quickcreatevis("cmdconfig", "label", 726, 4, 52, 48);
	liqcell_setfont(	cmdconfig, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdconfig, "%" );
	liqcell_propsets(  cmdconfig, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdconfig, "backcolor", "xrgb(0,0,64)" );
	liqcell_propsets(  cmdconfig, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdconfig, "textalign", 2 );
	liqcell_propseti(  cmdconfig, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdconfig, "click", cmdconfig_click, self );
	liqcell_child_append(  self, cmdconfig);
	//############################# cmdprev:label
	liqcell *cmdprev = liqcell_quickcreatevis("cmdprev", "label", 158, 4, 50, 48);
	liqcell_setfont(	cmdprev, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdprev, "<" );
	liqcell_propsets(  cmdprev, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdprev, "backcolor", "xrgb(0,64,64)" );
	liqcell_propsets(  cmdprev, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdprev, "textalign", 2 );
	liqcell_propseti(  cmdprev, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdprev, "click", cmdprev_click, self );
	liqcell_child_append(  self, cmdprev);
	//############################# cmdframecount:label
	liqcell *cmdframecount = liqcell_quickcreatevis("cmdframecount", "label", 212, 4, 454, 48);
	liqcell_setfont(	cmdframecount, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdframecount, "|...|...|...|...|...|...|...|...|...|...|...|..." );
	liqcell_propsets(  cmdframecount, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdframecount, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdframecount, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdframecount, "textalign", 2 );
	liqcell_propseti(  cmdframecount, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdframecount, "click", cmdframecount_click, self );
	liqcell_child_append(  self, cmdframecount);
	//############################# cmdnext:label
	liqcell *cmdnext = liqcell_quickcreatevis("cmdnext", "label", 670, 4, 52, 48);
	liqcell_setfont(	cmdnext, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdnext, ">" );
	liqcell_propsets(  cmdnext, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdnext, "backcolor", "xrgb(0,64,64)" );
	liqcell_propsets(  cmdnext, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdnext, "textalign", 2 );
	liqcell_propseti(  cmdnext, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdnext, "click", cmdnext_click, self );
	liqcell_child_append(  self, cmdnext);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/sheepdog/media/timelinerow_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", timelinerow_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", timelinerow_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", timelinerow_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", timelinerow_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", timelinerow_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", timelinerow_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", timelinerow_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", timelinerow_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", timelinerow_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", timelinerow_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", timelinerow_dialog_close ,self);
	return self;
}

