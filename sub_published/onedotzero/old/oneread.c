// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### oneread :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * oneread widget refresh, all params set, present yourself to the user.
 */	
static int oneread_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * oneread dialog_open - the user zoomed into the dialog
 */	
static int oneread_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * oneread dialog_close - the dialog was closed
 */	
static int oneread_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	liqcell *backplane = liqcell_child_lookup(self, "backplane");

	liqcell_setkinetic(backplane, -liqcell_getx(backplane), -liqcell_gety(backplane) );
	return 0;
}
/**	
 * oneread widget shown - occurs once per lifetime
 */	
static int oneread_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * oneread mouse - occurs all the time as you stroke the screen
 */	
static int oneread_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneread click - occurs when a short mouse stroke occured
 */	
static int oneread_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneread keypress - the user pressed a key
 */	
static int oneread_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneread keyrelease - the user released a key
 */	
static int oneread_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneread paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int oneread_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * oneread dynamic resizing
 */	
static int oneread_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	liqcell_setrect_autoscale( title, 0,0, 800,38, sx,sy);
	liqcell_setrect_autoscale( backplane, 0,0, 800, 1413 * 800 / 440, sx,sy);
	return 0;
}

/**	
 * oneread_child_test_seek this function shows how to access members
 */	
	  
static void oneread_child_test_seek(liqcell *self)
{	  
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
}	  
/**	
 * create a new oneread widget
 */	
liqcell *oneread_create()
{
	liqcell *self = liqcell_quickcreatewidget("oneread", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'oneread'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 38);
	//liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	//liqcell_setcaption(title, "Put Title Here" );
	//liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  title, "backcolor", "rgb(128,128,128)" );
	//liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# backplane:label
	liqcell *backplane = liqcell_quickcreatevis("backplane", "label", 0, 0, 800, 1413 * 800 / 440);  // 800, 480);			//440 1413
	liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(backplane, "backplane" );
	liqcell_propsets(  backplane, "textcolor", "rgb(255,0,0)" );
	liqcell_propsets(  backplane, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  backplane, "textalign", 2 );
	
	
	liqapp_log("app codepath = '%s'",app.codepath);
	char fnbuf[FILENAME_MAX];  snprintf(fnbuf,sizeof(fnbuf),"%s/onedotzero/media/mb1montage_REPRINT.jpg",app.codepath);
	liqcell_propsets( backplane ,  "imagefilename", fnbuf );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( fnbuf ,0,0,0) );
	liqcell_propseti( backplane ,  "lockaspect", 0 );
	//liqcell_propseti( backplane ,  "autosize", 1 );
	
	liqcell_handleradd(backplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );

	
	liqcell_child_append(  self, backplane);
	
	
	
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", oneread_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", oneread_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", oneread_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", oneread_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", oneread_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", oneread_mouse,self );
	liqcell_handleradd_withcontext(self, "click", oneread_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", oneread_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", oneread_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", oneread_dialog_close ,self);
	return self;
}

