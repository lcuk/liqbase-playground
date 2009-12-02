// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### oneinteract :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * oneinteract widget refresh, all params set, present yourself to the user.
 */	
static int oneinteract_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * oneinteract dialog_open - the user zoomed into the dialog
 */	
static int oneinteract_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * oneinteract dialog_close - the dialog was closed
 */	
static int oneinteract_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * oneinteract widget shown - occurs once per lifetime
 */	
static int oneinteract_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * oneinteract mouse - occurs all the time as you stroke the screen
 */	
static int oneinteract_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneinteract click - occurs when a short mouse stroke occured
 */	
static int oneinteract_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneinteract keypress - the user pressed a key
 */	
static int oneinteract_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneinteract keyrelease - the user released a key
 */	
static int oneinteract_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneinteract paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int oneinteract_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * oneinteract dynamic resizing
 */	
static int oneinteract_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *messagetext = liqcell_child_lookup(self, "messagetext");
	liqcell *cmdspeak = liqcell_child_lookup(self, "cmdspeak");
	liqcell *cmdtilt = liqcell_child_lookup(self, "cmdtilt");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdtouch = liqcell_child_lookup(self, "cmdtouch");
	liqcell_setrect_autoscale( messagetext, 20,86, 764,128, sx,sy);
	liqcell_setrect_autoscale( cmdspeak, 548,256, 198,164, sx,sy);
	liqcell_setrect_autoscale( cmdtilt, 304,256, 198,164, sx,sy);
	liqcell_setrect_autoscale( label1, 20,48, 326,30, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,38, sx,sy);
	liqcell_setrect_autoscale( cmdtouch, 60,256, 198,164, sx,sy);
	return 0;
}

/**	
 * oneinteract.cmdspeak clicked
 */	
static int cmdspeak_click(liqcell *self,liqcelleventargs *args, liqcell *oneinteract)
{
	return 0;
}
/**	
 * oneinteract.cmdtilt clicked
 */	
static int cmdtilt_click(liqcell *self,liqcelleventargs *args, liqcell *oneinteract)
{
	return 0;
}
/**	
 * oneinteract.cmdtouch clicked
 */	
static int cmdtouch_click(liqcell *self,liqcelleventargs *args, liqcell *oneinteract)
{
	return 0;
}
/**	
 * oneinteract_child_test_seek this function shows how to access members
 */	
	  
static void oneinteract_child_test_seek(liqcell *self)
{	  
	liqcell *messagetext = liqcell_child_lookup(self, "messagetext");
	liqcell *cmdspeak = liqcell_child_lookup(self, "cmdspeak");
	liqcell *cmdtilt = liqcell_child_lookup(self, "cmdtilt");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdtouch = liqcell_child_lookup(self, "cmdtouch");
}	  
/**	
 * create a new oneinteract widget
 */	
liqcell *oneinteract_create()
{
	liqcell *self = liqcell_quickcreatewidget("oneinteract", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'oneinteract'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# messagetext:textbox
	liqcell *messagetext = liqcell_quickcreatevis("messagetext", "textbox", 20, 86, 764, 128);
	liqcell_setfont(	messagetext, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (58), 0) );
	liqcell_setcaption(messagetext, "Message text" );
	liqcell_propsets(  messagetext, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  messagetext, "backcolor", "rgb(64,64,0)" );
	liqcell_propsets(  messagetext, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  messagetext, "textalign", 0 );
	liqcell_child_append(  self, messagetext);
	//############################# cmdspeak:label
	liqcell *cmdspeak = liqcell_quickcreatevis("cmdspeak", "label", 548, 256, 198, 164);
	liqcell_setfont(	cmdspeak, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdspeak, "speak" );
	liqcell_propsets(  cmdspeak, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdspeak, "backcolor", "rgb(0,0,64)" );
	liqcell_propsets(  cmdspeak, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  cmdspeak, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdspeak, "click", cmdspeak_click, self );
	liqcell_child_append(  self, cmdspeak);
	//############################# cmdtilt:label
	liqcell *cmdtilt = liqcell_quickcreatevis("cmdtilt", "label", 304, 256, 198, 164);
	liqcell_setfont(	cmdtilt, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdtilt, "tilt" );
	liqcell_propsets(  cmdtilt, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdtilt, "backcolor", "rgb(0,64,0)" );
	liqcell_propsets(  cmdtilt, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  cmdtilt, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdtilt, "click", cmdtilt_click, self );
	liqcell_child_append(  self, cmdtilt);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 20, 48, 326, 30);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label1, "Your message:" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_child_append(  self, label1);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 38);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(title, "onedotzero :: interact" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdtouch:label
	liqcell *cmdtouch = liqcell_quickcreatevis("cmdtouch", "label", 60, 256, 198, 164);
	liqcell_setfont(	cmdtouch, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdtouch, "touch" );
	liqcell_propsets(  cmdtouch, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdtouch, "backcolor", "rgb(64,0,0)" );
	liqcell_propsets(  cmdtouch, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  cmdtouch, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdtouch, "click", cmdtouch_click, self );
	liqcell_child_append(  self, cmdtouch);
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", oneinteract_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", oneinteract_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", oneinteract_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", oneinteract_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", oneinteract_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", oneinteract_mouse,self );
	liqcell_handleradd_withcontext(self, "click", oneinteract_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", oneinteract_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", oneinteract_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", oneinteract_dialog_close ,self);

	liqapp_log("app codepath = '%s'",app.codepath);
	char fnbuf[FILENAME_MAX];  snprintf(fnbuf,sizeof(fnbuf),"%s/onedotzero/media/motion_blur.png",app.codepath);
	liqcell_propsets( self ,  "imagefilename", fnbuf );
	liqcell_propseti( self ,  "lockaspect", 0 );
	//liqcell_propsets( self ,  "imagefloat", "0,0,0,0" );	// a bit of magic if it works..
	
	return self;
}

