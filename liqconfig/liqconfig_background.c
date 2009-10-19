// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqconfig_background :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqconfig_background widget refresh, all params set, present yourself to the user.
 */	
static int liqconfig_background_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqconfig_background dialog_open - the user zoomed into the dialog
 */	
static int liqconfig_background_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_background dialog_close - the dialog was closed
 */	
static int liqconfig_background_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_background widget shown - occurs once per lifetime
 */	
static int liqconfig_background_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_background mouse - occurs all the time as you stroke the screen
 */	
static int liqconfig_background_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_background click - occurs when a short mouse stroke occured
 */	
static int liqconfig_background_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_background keypress - the user pressed a key
 */	
static int liqconfig_background_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_background keyrelease - the user released a key
 */	
static int liqconfig_background_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_background paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqconfig_background_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqconfig_background dynamic resizing
 */	
static int liqconfig_background_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *picfront = liqcell_child_lookup(self, "picfront");
	liqcell *pichead = liqcell_child_lookup(self, "pichead");
	liqcell *cmdpicchoose = liqcell_child_lookup(self, "cmdpicchoose");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell_setrect_autoscale( picfront, 208,162, 368,186, sx,sy);
	liqcell_setrect_autoscale( pichead, 208,124, 368,36, sx,sy);
	liqcell_setrect_autoscale( cmdpicchoose, 300,350, 176,52, sx,sy);
	liqcell_setrect_autoscale( label1, 38,56, 724,102, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 594,432, 206,48, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
	return 0;
}

/**	
 * liqconfig_background.cmdpicchoose clicked
 */	
static int cmdpicchoose_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqconfig_background)
{
	return 0;
}
/**	
 * liqconfig_background.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqconfig_background)
{
	return 0;
}
/**	
 * liqconfig_background_child_test_seek this function shows how to access members
 */	
	  
static void liqconfig_background_child_test_seek(liqcell *liqconfig_background)
{	  
	liqcell *picfront = liqcell_child_lookup(liqconfig_background, "picfront");
	liqcell *pichead = liqcell_child_lookup(liqconfig_background, "pichead");
	liqcell *cmdpicchoose = liqcell_child_lookup(liqconfig_background, "cmdpicchoose");
	liqcell *cmdaccept = liqcell_child_lookup(liqconfig_background, "cmdaccept");
	liqcell *title = liqcell_child_lookup(liqconfig_background, "title");
	liqcell *label1 = liqcell_child_lookup(liqconfig_background, "label1");
}	  
/**	
 * create a new liqconfig_background widget
 */	
liqcell *liqconfig_background_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqconfig_background", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqconfig_background'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# picfront:picturebox
	liqcell *picfront = liqcell_quickcreatevis("picfront", "picturebox", 208, 162, 368, 186);
	liqcell_setfont(	picfront, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_propsets(  picfront, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  picfront, "backcolor", "rgb(64,0,0)" );
	liqcell_propsets(  picfront, "bordercolor", "rgb(255,255,255)" );
	liqcell_child_append(  self, picfront);
	//############################# pichead:label
	liqcell *pichead = liqcell_quickcreatevis("pichead", "label", 208, 124, 368, 36);
	liqcell_setfont(	pichead, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(pichead, "Picture" );
	liqcell_propsets(  pichead, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  pichead, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  pichead, "textalign", 0 );
	liqcell_propseti(  pichead, "textaligny", 0 );
	liqcell_child_append(  self, pichead);
	//############################# cmdpicchoose:label
	liqcell *cmdpicchoose = liqcell_quickcreatevis("cmdpicchoose", "label", 300, 350, 176, 52);
	liqcell_setfont(	cmdpicchoose, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdpicchoose, "Choose" );
	liqcell_propsets(  cmdpicchoose, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdpicchoose, "backcolor", "xrgb(0,0,64)" );
	liqcell_propsets(  cmdpicchoose, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdpicchoose, "textalign", 2 );
	liqcell_propseti(  cmdpicchoose, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdpicchoose, "click", cmdpicchoose_click, self );
	liqcell_child_append(  self, cmdpicchoose);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 594, 432, 206, 48);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Update" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Desktop Background Selection" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 38, 56, 724, 102);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label1, "Select an image you want as your background" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label1, "textalign", 2 );
	liqcell_propseti(  label1, "textaligny", 2 );
	liqcell_child_append(  self, label1);
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqconfig_background_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqconfig_background_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqconfig_background_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqconfig_background_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqconfig_background_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqconfig_background_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqconfig_background_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqconfig_background_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqconfig_background_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqconfig_background_dialog_close ,self);
	return self;
}

