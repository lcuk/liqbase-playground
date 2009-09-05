// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqpostcard_start :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqpostcard_start widget refresh, all params set, present yourself to the user.
 */	
static int liqpostcard_start_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqpostcard_start dialog_open - the user zoomed into the dialog
 */	
static int liqpostcard_start_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_start dialog_close - the dialog was closed
 */	
static int liqpostcard_start_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_start widget shown - occurs once per lifetime
 */	
static int liqpostcard_start_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_start mouse - occurs all the time as you stroke the screen
 */	
static int liqpostcard_start_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_start click - occurs when a short mouse stroke occured
 */	
static int liqpostcard_start_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_start keypress - the user pressed a key
 */	
static int liqpostcard_start_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_start keyrelease - the user released a key
 */	
static int liqpostcard_start_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_start paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqpostcard_start_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqpostcard_start dynamic resizing
 */	
static int liqpostcard_start_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *label6 = liqcell_child_lookup(self, "label6");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *label4 = liqcell_child_lookup(self, "label4");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");
	liqcell_setrect_autoscale( label6, 88,362, 622,34, sx,sy);
	liqcell_setrect_autoscale( label5, 622,428, 178,52, sx,sy);
	liqcell_setrect_autoscale( label4, 254,438, 364,32, sx,sy);
	liqcell_setrect_autoscale( label3, 88,334, 622,34, sx,sy);
	liqcell_setrect_autoscale( label2, 88,306, 622,34, sx,sy);
	liqcell_setrect_autoscale( label1, 140,80, 502,40, sx,sy);
	liqcell_setrect_autoscale( cmdsend, 242,160, 298,104, sx,sy);
	return 0;
}

/**	
 * liqpostcard_start.cmdsend clicked
 */	
static int cmdsend_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_start)
{
	return 0;
}
/**	
 * liqpostcard_start_child_test_seek this function shows how to access members
 */	
	  
static void liqpostcard_start_child_test_seek(liqcell *self)
{	  
	liqcell *label6 = liqcell_child_lookup(self, "label6");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *label4 = liqcell_child_lookup(self, "label4");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");
}	  
/**	
 * create a new liqpostcard_start widget
 */	
liqcell *liqpostcard_start_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqpostcard_start", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqpostcard_start'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# label6:label
	liqcell *label6 = liqcell_quickcreatevis("label6", "label", 88, 362, 622, 34);
	liqcell_setfont(	label6, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label6, "Open source letters." );
	liqcell_propsets(  label6, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label6, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label6, "textalign", 2 );
	liqcell_child_append(  self, label6);
	//############################# label5:label
	liqcell *label5 = liqcell_quickcreatevis("label5", "label", 622, 428, 178, 52);
	liqcell_setfont(	label5, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(label5, "Configure" );
	liqcell_propsets(  label5, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  label5, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  label5, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  label5, "textalign", 2 );
	liqcell_child_append(  self, label5);
	//############################# label4:label
	liqcell *label4 = liqcell_quickcreatevis("label4", "label", 254, 438, 364, 32);
	liqcell_setfont(	label4, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label4, "Click here to configure accounts" );
	liqcell_propsets(  label4, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label4, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label4, "textalign", 0 );
	liqcell_child_append(  self, label4);
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 88, 334, 622, 34);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label3, "They are public and viewable by everyone." );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label3, "textalign", 2 );
	liqcell_child_append(  self, label3);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 88, 306, 622, 34);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label2, "A postcard is an open message sent from the heart." );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label2, "textalign", 2 );
	liqcell_child_append(  self, label2);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 140, 80, 502, 40);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label1, "send a postcard to a friend" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label1, "textalign", 2 );
	liqcell_child_append(  self, label1);
	//############################# cmdsend:label
	liqcell *cmdsend = liqcell_quickcreatevis("cmdsend", "label", 242, 160, 298, 104);
	liqcell_setfont(	cmdsend, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsend, "Start" );
	liqcell_propsets(  cmdsend, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  cmdsend, "backcolor", "xrgb(255,255,0)" );
	liqcell_propsets(  cmdsend, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdsend, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdsend, "click", cmdsend_click, self );
	liqcell_child_append(  self, cmdsend);
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqpostcard_start_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqpostcard_start_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqpostcard_start_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqpostcard_start_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqpostcard_start_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqpostcard_start_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqpostcard_start_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqpostcard_start_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqpostcard_start_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqpostcard_start_dialog_close ,self);
	return self;
}

