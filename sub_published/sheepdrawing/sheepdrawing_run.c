// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### sheepdrawing_run :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * sheepdrawing_run widget filter, the system is asking you to filter to the specified .
 */	
static int sheepdrawing_run_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * sheepdrawing_run widget refresh, all params set, present yourself to the user.
 */	
static int sheepdrawing_run_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run dialog_open - the user zoomed into the dialog
 */	
static int sheepdrawing_run_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdrawing_run dialog_close - the dialog was closed
 */	
static int sheepdrawing_run_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdrawing_run widget shown - occurs once per lifetime
 */	
static int sheepdrawing_run_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run mouse - occurs all the time as you stroke the screen
 */	
static int sheepdrawing_run_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run click - occurs when a short mouse stroke occured
 */	
static int sheepdrawing_run_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run keypress - the user pressed a key
 */	
static int sheepdrawing_run_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run keyrelease - the user released a key
 */	
static int sheepdrawing_run_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int sheepdrawing_run_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * sheepdrawing_run dynamic resizing
 */	
static int sheepdrawing_run_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *cmdundo = liqcell_child_lookup(self, "cmdundo");
	liqcell *cmdclear = liqcell_child_lookup(self, "cmdclear");
	liqcell *cmdselect = liqcell_child_lookup(self, "cmdselect");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell_setrect_autoscale( backplane, 0,58, 800,422, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,58, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 594,434, 206,48, sx,sy);
	liqcell_setrect_autoscale( cmdundo, 728,60, 72,72, sx,sy);
	liqcell_setrect_autoscale( cmdclear, 728,132, 72,86, sx,sy);
	liqcell_setrect_autoscale( cmdselect, 728,344, 72,90, sx,sy);
	liqcell_setrect_autoscale( label1, 728,218, 72,124, sx,sy);
	return 0;
}

/**	
 * sheepdrawing_run.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_run)
{
	return 0;
}
/**	
 * sheepdrawing_run.cmdundo clicked
 */	
static int cmdundo_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_run)
{
	return 0;
}
/**	
 * sheepdrawing_run.cmdclear clicked
 */	
static int cmdclear_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_run)
{
	return 0;
}
/**	
 * sheepdrawing_run.cmdselect clicked
 */	
static int cmdselect_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_run)
{
	return 0;
}
/**	
 * sheepdrawing_run_child_test_seek this function shows how to access members
 */	
	  
static void sheepdrawing_run_child_test_seek(liqcell *sheepdrawing_run)
{	  
	liqcell *backplane = liqcell_child_lookup(sheepdrawing_run, "backplane");
	liqcell *title = liqcell_child_lookup(sheepdrawing_run, "title");
	liqcell *cmdaccept = liqcell_child_lookup(sheepdrawing_run, "cmdaccept");
	liqcell *cmdundo = liqcell_child_lookup(sheepdrawing_run, "cmdundo");
	liqcell *cmdclear = liqcell_child_lookup(sheepdrawing_run, "cmdclear");
	liqcell *cmdselect = liqcell_child_lookup(sheepdrawing_run, "cmdselect");
	liqcell *label1 = liqcell_child_lookup(sheepdrawing_run, "label1");
}	  
/**	
 * create a new sheepdrawing_run widget
 */	
liqcell *sheepdrawing_run_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdrawing_run", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'sheepdrawing_run'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# backplane:label
	liqcell *backplane = liqcell_quickcreatevis("backplane", "label", 0, 58, 800, 422);
	liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(backplane, "backplane" );
	liqcell_propsets(  backplane, "textcolor", "rgb(255,0,0)" );
	liqcell_propsets(  backplane, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  backplane, "textalign", 2 );
	liqcell_propseti(  backplane, "textaligny", 2 );
	liqcell_child_append(  self, backplane);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 58);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Draw your sheep" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 594, 434, 206, 48);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Upload" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# cmdundo:label
	liqcell *cmdundo = liqcell_quickcreatevis("cmdundo", "label", 728, 60, 72, 72);
	liqcell_setfont(	cmdundo, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdundo, "undo" );
	liqcell_propsets(  cmdundo, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdundo, "backcolor", "xrgb(64,0,64)" );
	liqcell_propsets(  cmdundo, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdundo, "textalign", 2 );
	liqcell_propseti(  cmdundo, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdundo, "click", cmdundo_click, self );
	liqcell_child_append(  self, cmdundo);
	//############################# cmdclear:label
	liqcell *cmdclear = liqcell_quickcreatevis("cmdclear", "label", 728, 132, 72, 86);
	liqcell_setfont(	cmdclear, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdclear, "clear" );
	liqcell_propsets(  cmdclear, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdclear, "backcolor", "xrgb(64,0,0)" );
	liqcell_propsets(  cmdclear, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdclear, "textalign", 2 );
	liqcell_propseti(  cmdclear, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdclear, "click", cmdclear_click, self );
	liqcell_child_append(  self, cmdclear);
	//############################# cmdselect:label
	liqcell *cmdselect = liqcell_quickcreatevis("cmdselect", "label", 728, 344, 72, 90);
	liqcell_setfont(	cmdselect, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdselect, "select" );
	liqcell_propsets(  cmdselect, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdselect, "backcolor", "xrgb(0,0,64)" );
	liqcell_propsets(  cmdselect, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdselect, "textalign", 2 );
	liqcell_propseti(  cmdselect, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdselect, "click", cmdselect_click, self );
	liqcell_child_append(  self, cmdselect);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 728, 218, 72, 124);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(label1, "color" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(64,64,0)" );
	liqcell_propsets(  label1, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  label1, "textalign", 2 );
	liqcell_propseti(  label1, "textaligny", 2 );
	liqcell_child_append(  self, label1);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/sheepdrawing/media/sheepdrawing_run_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", sheepdrawing_run_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", sheepdrawing_run_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", sheepdrawing_run_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", sheepdrawing_run_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", sheepdrawing_run_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", sheepdrawing_run_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", sheepdrawing_run_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", sheepdrawing_run_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", sheepdrawing_run_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", sheepdrawing_run_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", sheepdrawing_run_dialog_close ,self);
	return self;
}

