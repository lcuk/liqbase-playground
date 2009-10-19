// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqconfig_liqbasenet_privacy :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqconfig_liqbasenet_privacy widget refresh, all params set, present yourself to the user.
 */	
static int liqconfig_liqbasenet_privacy_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqconfig_liqbasenet_privacy dialog_open - the user zoomed into the dialog
 */	
static int liqconfig_liqbasenet_privacy_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet_privacy dialog_close - the dialog was closed
 */	
static int liqconfig_liqbasenet_privacy_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet_privacy widget shown - occurs once per lifetime
 */	
static int liqconfig_liqbasenet_privacy_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet_privacy mouse - occurs all the time as you stroke the screen
 */	
static int liqconfig_liqbasenet_privacy_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet_privacy click - occurs when a short mouse stroke occured
 */	
static int liqconfig_liqbasenet_privacy_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet_privacy keypress - the user pressed a key
 */	
static int liqconfig_liqbasenet_privacy_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet_privacy keyrelease - the user released a key
 */	
static int liqconfig_liqbasenet_privacy_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet_privacy paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqconfig_liqbasenet_privacy_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqconfig_liqbasenet_privacy dynamic resizing
 */	
static int liqconfig_liqbasenet_privacy_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *check3 = liqcell_child_lookup(self, "check3");
	liqcell *check2 = liqcell_child_lookup(self, "check2");
	liqcell *check1 = liqcell_child_lookup(self, "check1");
	liqcell *sketch = liqcell_child_lookup(self, "sketch");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell_setrect_autoscale( check3, 96,334, 618,54, sx,sy);
	liqcell_setrect_autoscale( check2, 96,282, 618,54, sx,sy);
	liqcell_setrect_autoscale( check1, 96,170, 618,54, sx,sy);
	liqcell_setrect_autoscale( sketch, 96,116, 618,54, sx,sy);
	liqcell_setrect_autoscale( label2, 30,56, 724,54, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 594,432, 206,48, sx,sy);
	return 0;
}

/**	
 * liqconfig_liqbasenet_privacy.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqconfig_liqbasenet_privacy)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet_privacy_child_test_seek this function shows how to access members
 */	
	  
static void liqconfig_liqbasenet_privacy_child_test_seek(liqcell *liqconfig_liqbasenet_privacy)
{	  
	liqcell *check3 = liqcell_child_lookup(liqconfig_liqbasenet_privacy, "check3");
	liqcell *check2 = liqcell_child_lookup(liqconfig_liqbasenet_privacy, "check2");
	liqcell *check1 = liqcell_child_lookup(liqconfig_liqbasenet_privacy, "check1");
	liqcell *sketch = liqcell_child_lookup(liqconfig_liqbasenet_privacy, "sketch");
	liqcell *title = liqcell_child_lookup(liqconfig_liqbasenet_privacy, "title");
	liqcell *cmdaccept = liqcell_child_lookup(liqconfig_liqbasenet_privacy, "cmdaccept");
	liqcell *label2 = liqcell_child_lookup(liqconfig_liqbasenet_privacy, "label2");
}	  
/**	
 * create a new liqconfig_liqbasenet_privacy widget
 */	
liqcell *liqconfig_liqbasenet_privacy_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqconfig_liqbasenet_privacy", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqconfig_liqbasenet_privacy'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# check3:checkbox
	liqcell *check3 = liqcell_quickcreatevis("check3", "checkbox", 96, 334, 618, 54);
	liqcell_setfont(	check3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(check3, "Upload context screenshots" );
	liqcell_propsets(  check3, "textcolor", "rgb(255,255,128)" );
	liqcell_propsets(  check3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  check3, "textalign", 0 );
	liqcell_propseti(  check3, "textaligny", 0 );
	liqcell_child_append(  self, check3);
	//############################# check2:checkbox
	liqcell *check2 = liqcell_quickcreatevis("check2", "checkbox", 96, 282, 618, 54);
	liqcell_setfont(	check2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(check2, "Upload context sketches" );
	liqcell_propsets(  check2, "textcolor", "rgb(255,255,128)" );
	liqcell_propsets(  check2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  check2, "textalign", 0 );
	liqcell_propseti(  check2, "textaligny", 0 );
	liqcell_child_append(  self, check2);
	//############################# check1:checkbox
	liqcell *check1 = liqcell_quickcreatevis("check1", "checkbox", 96, 170, 618, 54);
	liqcell_setfont(	check1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(check1, "Upload Calendar sketches" );
	liqcell_propsets(  check1, "textcolor", "rgb(255,255,128)" );
	liqcell_propsets(  check1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  check1, "textalign", 0 );
	liqcell_propseti(  check1, "textaligny", 0 );
	liqcell_child_append(  self, check1);
	//############################# sketch:checkbox
	liqcell *sketch = liqcell_quickcreatevis("sketch", "checkbox", 96, 116, 618, 54);
	liqcell_setfont(	sketch, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(sketch, "Upload general sketches" );
	liqcell_propsets(  sketch, "textcolor", "rgb(255,255,128)" );
	liqcell_propsets(  sketch, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  sketch, "textalign", 0 );
	liqcell_propseti(  sketch, "textaligny", 0 );
	liqcell_child_append(  self, sketch);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Configure liqbase.net privacy settings" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 594, 432, 206, 48);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Save" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 30, 56, 724, 54);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label2, "Select options for liqbase.net uploading" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label2, "textalign", 2 );
	liqcell_propseti(  label2, "textaligny", 2 );
	liqcell_child_append(  self, label2);
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqconfig_liqbasenet_privacy_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqconfig_liqbasenet_privacy_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqconfig_liqbasenet_privacy_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqconfig_liqbasenet_privacy_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqconfig_liqbasenet_privacy_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqconfig_liqbasenet_privacy_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqconfig_liqbasenet_privacy_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqconfig_liqbasenet_privacy_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqconfig_liqbasenet_privacy_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqconfig_liqbasenet_privacy_dialog_close ,self);
	return self;
}

