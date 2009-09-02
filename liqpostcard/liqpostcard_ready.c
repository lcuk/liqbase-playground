// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqpostcard_ready :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqpostcard_ready widget refresh, all params set, present yourself to the user.
 */	
static int liqpostcard_ready_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqpostcard_ready dialog_open - the user zoomed into the dialog
 */	
static int liqpostcard_ready_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_ready dialog_close - the dialog was closed
 */	
static int liqpostcard_ready_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_ready widget shown - occurs once per lifetime
 */	
static int liqpostcard_ready_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_ready mouse - occurs all the time as you stroke the screen
 */	
static int liqpostcard_ready_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_ready click - occurs when a short mouse stroke occured
 */	
static int liqpostcard_ready_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_ready keypress - the user pressed a key
 */	
static int liqpostcard_ready_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_ready keyrelease - the user released a key
 */	
static int liqpostcard_ready_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_ready paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqpostcard_ready_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqpostcard_ready dynamic resizing
 */	
static int liqpostcard_ready_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *picback = liqcell_child_lookup(self, "picback");
	liqcell *picfront = liqcell_child_lookup(self, "picfront");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");
	liqcell *cmddiscard = liqcell_child_lookup(self, "cmddiscard");
	liqcell_setrect_autoscale( picback, 406,112, 368,240, sx,sy);
	liqcell_setrect_autoscale( picfront, 20,112, 368,240, sx,sy);
	liqcell_setrect_autoscale( label3, 0,0, 800,56, sx,sy);
	liqcell_setrect_autoscale( label2, 406,74, 366,36, sx,sy);
	liqcell_setrect_autoscale( label1, 20,74, 368,36, sx,sy);
	liqcell_setrect_autoscale( cmdsend, 558,380, 226,80, sx,sy);
	liqcell_setrect_autoscale( cmddiscard, 342,380, 212,80, sx,sy);
	return 0;
}

/**	
 * liqpostcard_ready.cmdsend clicked
 */	
static int cmdsend_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_ready)
{
	return 0;
}
/**	
 * liqpostcard_ready.cmddiscard clicked
 */	
static int cmddiscard_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_ready)
{
	return 0;
}
/**	
 * liqpostcard_ready_child_test_seek this function shows how to access members
 */	
	  
static void liqpostcard_ready_child_test_seek(liqcell *self)
{	  
	liqcell *picback = liqcell_child_lookup(self, "picback");
	liqcell *picfront = liqcell_child_lookup(self, "picfront");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");
	liqcell *cmddiscard = liqcell_child_lookup(self, "cmddiscard");
}	  
/**	
 * create a new liqpostcard_ready widget
 */	
liqcell *liqpostcard_ready_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqpostcard_ready", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqpostcard_ready'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# picback:picturebox
	liqcell *picback = liqcell_quickcreatevis("picback", "picturebox", 406, 112, 368, 240);
	liqcell_setfont(	picback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_propsets(  picback, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  picback, "backcolor", "rgb(235,233,237)" );
	liqcell_propsets(  picback, "bordercolor", "rgb(200,100,100)" );
	liqcell_child_append(  self, picback);
	//############################# picfront:picturebox
	liqcell *picfront = liqcell_quickcreatevis("picfront", "picturebox", 20, 112, 368, 240);
	liqcell_setfont(	picfront, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_propsets(  picfront, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  picfront, "backcolor", "rgb(235,233,237)" );
	liqcell_propsets(  picfront, "bordercolor", "rgb(200,100,100)" );
	liqcell_child_append(  self, picfront);
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 0, 0, 800, 56);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(label3, "postcard :: Ready to send" );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label3, "backcolor", "rgb(64,64,0)" );
	liqcell_propseti(  label3, "textalign", 0 );
	liqcell_child_append(  self, label3);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 406, 74, 366, 36);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label2, "Back" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label2, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  label2, "textalign", 0 );
	liqcell_child_append(  self, label2);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 20, 74, 368, 36);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label1, "Front" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_child_append(  self, label1);
	//############################# cmdsend:label
	liqcell *cmdsend = liqcell_quickcreatevis("cmdsend", "label", 558, 380, 226, 80);
	liqcell_setfont(	cmdsend, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsend, "Send" );
	liqcell_propsets(  cmdsend, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdsend, "backcolor", "rgb(0,64,0)" );
	liqcell_propsets(  cmdsend, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  cmdsend, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdsend, "click", cmdsend_click, self );
	liqcell_child_append(  self, cmdsend);
	//############################# cmddiscard:label
	liqcell *cmddiscard = liqcell_quickcreatevis("cmddiscard", "label", 342, 380, 212, 80);
	liqcell_setfont(	cmddiscard, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmddiscard, "Discard" );
	liqcell_propsets(  cmddiscard, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmddiscard, "backcolor", "rgb(64,0,0)" );
	liqcell_propsets(  cmddiscard, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  cmddiscard, "textalign", 2 );
	liqcell_handleradd_withcontext(cmddiscard, "click", cmddiscard_click, self );
	liqcell_child_append(  self, cmddiscard);
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqpostcard_ready_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqpostcard_ready_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqpostcard_ready_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqpostcard_ready_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqpostcard_ready_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqpostcard_ready_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqpostcard_ready_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqpostcard_ready_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqpostcard_ready_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqpostcard_ready_dialog_close ,self);
	return self;
}

