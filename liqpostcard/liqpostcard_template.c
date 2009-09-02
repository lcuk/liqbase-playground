// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqpostcard_template :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqpostcard_template widget refresh, all params set, present yourself to the user.
 */	
static int liqpostcard_template_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqpostcard_template dialog_open - the user zoomed into the dialog
 */	
static int liqpostcard_template_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_template dialog_close - the dialog was closed
 */	
static int liqpostcard_template_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_template widget shown - occurs once per lifetime
 */	
static int liqpostcard_template_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_template mouse - occurs all the time as you stroke the screen
 */	
static int liqpostcard_template_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_template click - occurs when a short mouse stroke occured
 */	
static int liqpostcard_template_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_template keypress - the user pressed a key
 */	
static int liqpostcard_template_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_template keyrelease - the user released a key
 */	
static int liqpostcard_template_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_template paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqpostcard_template_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqpostcard_template dynamic resizing
 */	
static int liqpostcard_template_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *notice = liqcell_child_lookup(self, "notice");
	liqcell *line4 = liqcell_child_lookup(self, "line4");
	liqcell *line3 = liqcell_child_lookup(self, "line3");
	liqcell *line2 = liqcell_child_lookup(self, "line2");
	liqcell *line1 = liqcell_child_lookup(self, "line1");
	liqcell *midbar = liqcell_child_lookup(self, "midbar");
	liqcell *stamp = liqcell_child_lookup(self, "stamp");
	liqcell_setrect_autoscale( stamp, 698,14, 94,124, sx,sy);
	liqcell_setrect_autoscale( midbar, 352,36, 2,376, sx,sy);
	liqcell_setrect_autoscale( line1, 384,190, 324,2, sx,sy);
	liqcell_setrect_autoscale( line2, 384,240, 324,2, sx,sy);
	liqcell_setrect_autoscale( line3, 384,292, 324,2, sx,sy);
	liqcell_setrect_autoscale( line4, 384,348, 324,2, sx,sy);
	liqcell_setrect_autoscale( notice, 420,456, 376,20, sx,sy);
	return 0;
}

/**	
 * liqpostcard_template_child_test_seek this function shows how to access members
 */	
	  
static void liqpostcard_template_child_test_seek(liqcell *self)
{	  
	liqcell *notice = liqcell_child_lookup(self, "notice");
	liqcell *line4 = liqcell_child_lookup(self, "line4");
	liqcell *line3 = liqcell_child_lookup(self, "line3");
	liqcell *line2 = liqcell_child_lookup(self, "line2");
	liqcell *line1 = liqcell_child_lookup(self, "line1");
	liqcell *midbar = liqcell_child_lookup(self, "midbar");
	liqcell *stamp = liqcell_child_lookup(self, "stamp");
}	  
/**	
 * create a new liqpostcard_template widget
 */	
liqcell *liqpostcard_template_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqpostcard_template", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqpostcard_template'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# notice:label
	liqcell *notice = liqcell_quickcreatevis("notice", "label", 420, 456, 376, 20);
	liqcell_setfont(	notice, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(notice, "postcard created within liqbase on maemo" );
	liqcell_propsets(  notice, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  notice, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  notice, "textalign", 1 );
	liqcell_child_append(  self, notice);
	//############################# line4:label
	liqcell *line4 = liqcell_quickcreatevis("line4", "label", 384, 348, 324, 2);
	liqcell_setfont(	line4, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(line4, "" );
	liqcell_propsets(  line4, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  line4, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  line4, "textalign", 0 );
	liqcell_child_append(  self, line4);
	//############################# line3:label
	liqcell *line3 = liqcell_quickcreatevis("line3", "label", 384, 292, 324, 2);
	liqcell_setfont(	line3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(line3, "" );
	liqcell_propsets(  line3, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  line3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  line3, "textalign", 0 );
	liqcell_child_append(  self, line3);
	//############################# line2:label
	liqcell *line2 = liqcell_quickcreatevis("line2", "label", 384, 240, 324, 2);
	liqcell_setfont(	line2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(line2, "" );
	liqcell_propsets(  line2, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  line2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  line2, "textalign", 0 );
	liqcell_child_append(  self, line2);
	//############################# line1:label
	liqcell *line1 = liqcell_quickcreatevis("line1", "label", 384, 190, 324, 2);
	liqcell_setfont(	line1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(line1, "" );
	liqcell_propsets(  line1, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  line1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  line1, "textalign", 0 );
	liqcell_child_append(  self, line1);
	//############################# midbar:label
	liqcell *midbar = liqcell_quickcreatevis("midbar", "label", 352, 36, 2, 376);
	liqcell_setfont(	midbar, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(midbar, "" );
	liqcell_propsets(  midbar, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  midbar, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  midbar, "textalign", 0 );
	liqcell_child_append(  self, midbar);
	//############################# stamp:label
	liqcell *stamp = liqcell_quickcreatevis("stamp", "label", 698, 14, 94, 124);
	liqcell_setfont(	stamp, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(stamp, "stamp" );
	liqcell_propsets(  stamp, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  stamp, "backcolor", "rgb(224,224,224)" );
	liqcell_propsets(  stamp, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  stamp, "textalign", 2 );
	liqcell_child_append(  self, stamp);
	liqcell_propsets(  self, "backcolor", "rgb(255,255,255)" );
	liqcell_handleradd_withcontext(self, "refresh", liqpostcard_template_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqpostcard_template_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqpostcard_template_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqpostcard_template_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqpostcard_template_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqpostcard_template_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqpostcard_template_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqpostcard_template_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqpostcard_template_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqpostcard_template_dialog_close ,self);
	return self;
}

