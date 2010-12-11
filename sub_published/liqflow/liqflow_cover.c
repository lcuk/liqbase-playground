// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqflow_cover :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqflow_cover widget filter, the system is asking you to filter to the specified .
 */	
static int liqflow_cover_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * liqflow_cover widget refresh, all params set, present yourself to the user.
 */	
static int liqflow_cover_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqflow_cover dialog_open - the user zoomed into the dialog
 */	
static int liqflow_cover_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqflow_cover dialog_close - the dialog was closed
 */	
static int liqflow_cover_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqflow_cover widget shown - occurs once per lifetime
 */	
static int liqflow_cover_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqflow_cover mouse - occurs all the time as you stroke the screen
 */	
static int liqflow_cover_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqflow_cover click - occurs when a short mouse stroke occured
 */	
static int liqflow_cover_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqflow_cover keypress - the user pressed a key
 */	
static int liqflow_cover_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqflow_cover keyrelease - the user released a key
 */	
static int liqflow_cover_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqflow_cover paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqflow_cover_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqflow_cover dynamic resizing
 */	
static int liqflow_cover_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *slidepreview = liqcell_child_lookup(self, "slidepreview");
	liqcell *slidetext1 = liqcell_child_lookup(self, "slidetext1");
	liqcell *slidetext2 = liqcell_child_lookup(self, "slidetext2");
	liqcell *slidetext3 = liqcell_child_lookup(self, "slidetext3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell_setrect_autoscale( slidepreview, 492,204, 240,204, sx,sy);
	liqcell_setrect_autoscale( slidetext1, 42,234, 442,30, sx,sy);
	liqcell_setrect_autoscale( slidetext2, 44,294, 442,30, sx,sy);
	liqcell_setrect_autoscale( slidetext3, 44,354, 442,30, sx,sy);
	liqcell_setrect_autoscale( label2, 42,90, 696,48, sx,sy);
	liqcell_setrect_autoscale( label1, 36,6, 644,80, sx,sy);
	return 0;
}

/**	
 * liqflow_cover_child_test_seek this function shows how to access members
 */	
	  
static void liqflow_cover_child_test_seek(liqcell *liqflow_cover)
{	  
	liqcell *slidepreview = liqcell_child_lookup(liqflow_cover, "slidepreview");
	liqcell *slidetext1 = liqcell_child_lookup(liqflow_cover, "slidetext1");
	liqcell *slidetext2 = liqcell_child_lookup(liqflow_cover, "slidetext2");
	liqcell *slidetext3 = liqcell_child_lookup(liqflow_cover, "slidetext3");
	liqcell *label2 = liqcell_child_lookup(liqflow_cover, "label2");
	liqcell *label1 = liqcell_child_lookup(liqflow_cover, "label1");
}	  
/**	
 * create a new liqflow_cover widget
 */	
liqcell *liqflow_cover_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqflow_cover", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqflow_cover'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# slidepreview:label
	liqcell *slidepreview = liqcell_quickcreatevis("slidepreview", "label", 492, 204, 240, 100);
	//liqcell_setfont(	slidepreview, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(slidepreview, "" );
	//liqcell_propsets(  slidepreview, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  slidepreview, "backcolor", "rgb(32,64,64)" );
	liqcell_propseti(  slidepreview, "textalign", 0 );
	liqcell_propseti(  slidepreview, "textaligny", 0 );
	
	{
		 liqcell *x = liqcell_quickcreatevis("liqflow_run1", "liqflow_run", 0,0,-1,-1);
		 liqcell_setcontent(slidepreview,x);
		 liqcell_propseti(slidepreview,"lockaspect",1);
		 liqcell_handleradd_withcontext(slidepreview, "click", liqcell_easyhandler_content_zoom_click, self );
	}
	liqcell_child_append(  self, slidepreview);
	
	
	//############################# slideconfig:label
	liqcell *slideconfig = liqcell_quickcreatevis("slideconfig", "label", 492, 304, 240, 100);
	//liqcell_setfont(	slideconfig, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(slideconfig, "" );
	//liqcell_propsets(  slideconfig, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  slideconfig, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  slideconfig, "textalign", 0 );
	liqcell_propseti(  slideconfig, "textaligny", 0 );
	
	

	{
		 liqcell *x = liqcell_quickcreatevis("liqflow_run1", "liqflow_config", 0,0,-1,-1);
		 liqcell_setcontent(slideconfig,x);
		 liqcell_propseti(slideconfig,"lockaspect",1);
		 liqcell_handleradd_withcontext(slideconfig, "click", liqcell_easyhandler_content_zoom_click, self );
	}
	liqcell_child_append(  self, slideconfig);
 
	

	//############################# slidetext1:label
	liqcell *slidetext1 = liqcell_quickcreatevis("slidetext1", "label", 42, 234, 442, 30);
	liqcell_setfont(	slidetext1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext1, "fluid dynamics at your fingertips" );
	liqcell_propsets(  slidetext1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext1, "textalign", 0 );
	liqcell_propseti(  slidetext1, "textaligny", 0 );
	liqcell_child_append(  self, slidetext1);
	//############################# slidetext2:label
	liqcell *slidetext2 = liqcell_quickcreatevis("slidetext2", "label", 44, 294, 442, 30);
	liqcell_setfont(	slidetext2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext2, "natural flowing patterns" );
	liqcell_propsets(  slidetext2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext2, "textalign", 0 );
	liqcell_propseti(  slidetext2, "textaligny", 0 );
	liqcell_child_append(  self, slidetext2);
	//############################# slidetext3:label
	liqcell *slidetext3 = liqcell_quickcreatevis("slidetext3", "label", 44, 354, 442, 30);
	liqcell_setfont(	slidetext3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext3, "Accelerometer controllable" );
	liqcell_propsets(  slidetext3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext3, "textalign", 0 );
	liqcell_propseti(  slidetext3, "textaligny", 0 );
	liqcell_child_append(  self, slidetext3);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 42, 90, 696, 48);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(label2, "written by Gary Birkett." );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label2, "textalign", 0 );
	liqcell_propseti(  label2, "textaligny", 0 );
	liqcell_child_append(  self, label2);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 36, 6, 644, 80);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (58), 0) );
	liqcell_setcaption(label1, "liqflow" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_propseti(  label1, "textaligny", 0 );
	liqcell_child_append(  self, label1);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/liqflow/media/liqflow_cover_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", liqflow_cover_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", liqflow_cover_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqflow_cover_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", liqflow_cover_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqflow_cover_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqflow_cover_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", liqflow_cover_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", liqflow_cover_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqflow_cover_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqflow_cover_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqflow_cover_dialog_close ,self);
	return self;
}

