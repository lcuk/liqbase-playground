// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### onetouch :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * onetouch widget refresh, all params set, present yourself to the user.
 */	
static int onetouch_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * onetouch dialog_open - the user zoomed into the dialog
 */	
static int onetouch_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onetouch dialog_close - the dialog was closed
 */	
static int onetouch_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onetouch widget shown - occurs once per lifetime
 */	
static int onetouch_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onetouch mouse - occurs all the time as you stroke the screen
 */	
static int onetouch_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetouch click - occurs when a short mouse stroke occured
 */	
static int onetouch_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetouch keypress - the user pressed a key
 */	
static int onetouch_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetouch keyrelease - the user released a key
 */	
static int onetouch_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetouch paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int onetouch_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * onetouch dynamic resizing
 */	
static int onetouch_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell_setrect_autoscale( label3, 548,256, 198,164, sx,sy);
	liqcell_setrect_autoscale( label2, 304,256, 198,164, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,38, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 60,256, 198,164, sx,sy);
	return 0;
}

/**	
 * onetouch.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcelleventargs *args, liqcell *onetouch)
{
	return 0;
}
/**	
 * onetouch_child_test_seek this function shows how to access members
 */	
	  
static void onetouch_child_test_seek(liqcell *self)
{	  
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
}	  
/**	
 * create a new onetouch widget
 */	
liqcell *onetouch_create()
{
	liqcell *self = liqcell_quickcreatewidget("onetouch", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'onetouch'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 548, 256, 198, 164);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(label3, "Reaction" );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label3, "backcolor", "rgb(0,0,64)" );
	liqcell_propsets(  label3, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label3, "textalign", 2 );
	liqcell_child_append(  self, label3);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 304, 256, 198, 164);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(label2, "Waves" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label2, "backcolor", "rgb(0,64,0)" );
	liqcell_propsets(  label2, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label2, "textalign", 2 );
	liqcell_child_append(  self, label2);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 38);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(title, "onedotzero :: touch" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 60, 256, 198, 164);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Shapes" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "rgb(64,0,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
//	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", onetouch_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", onetouch_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", onetouch_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", onetouch_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", onetouch_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", onetouch_mouse,self );
	liqcell_handleradd_withcontext(self, "click", onetouch_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", onetouch_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", onetouch_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", onetouch_dialog_close ,self);
	
	/*
	//http://helly7307-stock.deviantart.com/art/Dark-Clouds-BG-stock-57905063
	liqapp_log("app codepath = '%s'",app.codepath);
	char fnbuf[FILENAME_MAX];  snprintf(fnbuf,sizeof(fnbuf),"%s/onedotzero/media/clouds.png",app.codepath);
	liqcell_propsets( self ,  "imagefilename", fnbuf );
	liqcell_propseti( self ,  "lockaspect", 0 );
	liqcell_propsets( self ,  "imagefloat", "0,0,0,0" );	// a bit of magic if it works..
	*/

	liqapp_log("app codepath = '%s'",app.codepath);
	char fnbuf[FILENAME_MAX];  snprintf(fnbuf,sizeof(fnbuf),"%s/onedotzero/media/clouds.png",app.codepath);
	//liqcell_propsets( self ,  "imagefilename", fnbuf );
	liqcell_setimage( self ,   liqimage_cache_getfile( fnbuf ,0,0,0) );
	liqcell_propseti( self ,  "lockaspect", 0 );
	//liqcell_propsets( self ,  "imagefloat", "0,0,0,0" );	// a bit of magic if it works..
	
	
	return self;
}

