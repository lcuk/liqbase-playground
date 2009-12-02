// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
        
#include "osc_onedotzero.h"
		
//#####################################################################
//#####################################################################
//##################################################################### zoombox :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * zoombox widget refresh, all params set, present yourself to the user.
 */	
static int zoombox_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * zoombox dialog_open - the user zoomed into the dialog
 */	
static int zoombox_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * zoombox dialog_close - the dialog was closed
 */	
static int zoombox_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * zoombox widget shown - occurs once per lifetime
 */	
static int zoombox_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * zoombox mouse - occurs all the time as you stroke the screen
 */	
static int zoombox_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
    
    
    int yy = args->mey-args->oy;
    
	liqcell *knob = liqcell_child_lookup(self, "knob");
    knob->y = (yy-(knob->h/2));
    liqcell_forceinboundparent(knob);
    
    
    float zoom = ((float)knob->y) / ((float)(self->h-knob->h));
    
    //liqapp_log("mm %3i   %3i   %3.3f",args->mey,args->oy,zoom);
    
    osc_onedotzero_send_zoom(liqcell_getname(self), 1-zoom);
    
	return 0;
}
/**	
 * zoombox click - occurs when a short mouse stroke occured
 */	
static int zoombox_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * zoombox keypress - the user pressed a key
 */	
static int zoombox_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * zoombox keyrelease - the user released a key
 */	
static int zoombox_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * zoombox paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int zoombox_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * zoombox dynamic resizing
 */	
static int zoombox_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
/*	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *knob = liqcell_child_lookup(self, "knob");
	liqcell_setrect_autoscale( knob, 0, 45, 40, 10, sx,sy);
 */	return 0;
}



/**	
 * zoombox_child_test_seek this function shows how to access members
 */	
	  
static void zoombox_child_test_seek(liqcell *self)
{	  
	liqcell *resize1 = liqcell_child_lookup(self, "resize1");
	liqcell *knob = liqcell_child_lookup(self, "knob");
}	  
/**	
 * create a new zoombox widget
 */	
liqcell *zoombox_create()
{
	liqcell *self = liqcell_quickcreatewidget("zoombox", "form", 89, 100);
	if(!self) {liqapp_log("liqcell error not create 'zoombox'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# knob:label
	liqcell *knob = liqcell_quickcreatevis("knob", "label", 0, 45, 89, 55);
	//liqcell_setfont(	knob, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	//liqcell_setcaption(knob, "94" );
	//liqcell_propsets(  knob, "textcolor", "rgb(192,255,192)" );
	//liqcell_propsets(  knob, "backcolor", "xrgb(0,64,0)" );
	//liqcell_propsets(  knob, "bordercolor", "rgb(255,255,255)" );
	//liqcell_propseti(  knob, "textalign", 2 );
    
    liqcell_setimage(  knob,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/slider_blue_button.png", 0,0,1) );
    
    
    
	liqcell_child_append(  self, knob);
	//liqcell_propsets(  self, "backcolor", "xrgb(0,0,64)" );
	liqcell_handleradd_withcontext(self, "refresh", zoombox_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", zoombox_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", zoombox_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", zoombox_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", zoombox_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", zoombox_mouse,self );
	liqcell_handleradd_withcontext(self, "click", zoombox_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", zoombox_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", zoombox_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", zoombox_dialog_close ,self);
	return self;
}

