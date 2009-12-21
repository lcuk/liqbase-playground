// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/vgraph.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### colorcube :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * colorcube widget refresh, all params set, present yourself to the user.
 */	
static int colorcube_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * colorcube dialog_open - the user zoomed into the dialog
 */	
static int colorcube_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * colorcube dialog_close - the dialog was closed
 */	
static int colorcube_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * colorcube widget shown - occurs once per lifetime
 */	
static int colorcube_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * colorcube mouse - occurs all the time as you stroke the screen
 */	
static int colorcube_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * colorcube click - occurs when a short mouse stroke occured
 */	
static int colorcube_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * colorcube keypress - the user pressed a key
 */	
static int colorcube_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * colorcube keyrelease - the user released a key
 */	
static int colorcube_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * colorcube paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
static int colorcube_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{
//	// big heavy event, use sparingly
	int cy = liqcell_propgeti(self,"colorcube_brightness",128);

    vgraph_setpencolor(  args->graph,vcolor_YUV(cy,128,128) );
    vgraph_drawcolorcube(args->graph,0,0,self->w,self->h);
	return 0;
}
/**	
 * colorcube dynamic resizing
 */	
static int colorcube_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	//liqcell *image1 = liqcell_child_lookup(self, "image1");
	//liqcell_setrect_autoscale( image1, 0,0, 236,204, sx,sy);
	return 0;
}

/**	
 * colorcube_child_test_seek this function shows how to access members
 */	
	  
static void colorcube_child_test_seek(liqcell *colorcube)
{	  
	//liqcell *image1 = liqcell_child_lookup(colorcube, "image1");
}	  
/**	
 * create a new colorcube widget
 */	
liqcell *colorcube_create()
{
	liqcell *self = liqcell_quickcreatewidget("colorcube", "form", 294, 284);
	if(!self) {liqapp_log("liqcell error not create 'colorcube'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# image1:image
	//liqcell *image1 = liqcell_quickcreatevis("image1", "image", 0, 0, 236, 204);
	//liqcell_propsets(  image1, "bordercolor", "rgb(255,255,255)" );
	//liqcell_child_append(  self, image1);
	//liqcell_propsets(  self, "backcolor", "rgb(235,233,237)" );
	liqcell_handleradd_withcontext(self, "refresh", colorcube_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", colorcube_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", colorcube_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", colorcube_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", colorcube_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", colorcube_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", colorcube_click ,self);
	liqcell_handleradd_withcontext(self, "paint", colorcube_paint ,self); // use only if required, heavyweight
	//liqcell_handleradd_withcontext(self, "dialog_open", colorcube_dialog_open ,self);
	//liqcell_handleradd_withcontext(self, "dialog_close", colorcube_dialog_close ,self);
	return self;
}

