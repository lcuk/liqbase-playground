// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### onetiltcontrol :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * onetiltcontrol widget refresh, all params set, present yourself to the user.
 */	
static int onetiltcontrol_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * onetiltcontrol dialog_open - the user zoomed into the dialog
 */	
static int onetiltcontrol_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onetiltcontrol dialog_close - the dialog was closed
 */	
static int onetiltcontrol_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    osc_onedotzero_send_menufinished(0);
	return 0;
}
/**	
 * onetiltcontrol widget shown - occurs once per lifetime
 */	
static int onetiltcontrol_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onetiltcontrol mouse - occurs all the time as you stroke the screen
 */	
static int onetiltcontrol_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetiltcontrol click - occurs when a short mouse stroke occured
 */	
static int onetiltcontrol_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetiltcontrol keypress - the user pressed a key
 */	
static int onetiltcontrol_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetiltcontrol keyrelease - the user released a key
 */	
static int onetiltcontrol_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetiltcontrol paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
static int onetiltcontrol_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{
	// big heavy event, use sparingly
    liqcell_setdirty(  self, 1);
	return 0;
}
/**	
 * onetiltcontrol dynamic resizing
 */	
static int onetiltcontrol_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	//float sx=((float)self->w)/((float)self->innerw);
	//float sy=((float)self->h)/((float)self->innerh);
	
	//liqcell *liqaccelview1 = liqcell_child_lookup(self, "liqaccelview1");
	//liqcell *zoombox1 = liqcell_child_lookup(self, "zoombox1");
	//liqcell_setrect_autoscale( liqaccelview1, 78,78, 496,354, sx,sy);
	//liqcell_setrect_autoscale( zoombox1, 644,78, 80,352, sx,sy);
	return 0;
}

/**	
 * onetiltcontrol_child_test_seek this function shows how to access members
 */	
	  
static void onetiltcontrol_child_test_seek(liqcell *self)
{	  
	liqcell *liqaccelview1 = liqcell_child_lookup(self, "liqaccelview1");
	//liqcell *zoombox1 = liqcell_child_lookup(self, "zoombox1");
}	  
/**	
 * create a new onetiltcontrol widget
 */	
liqcell *onetiltcontrol_create()
{
	liqcell *self = liqcell_quickcreatewidget("onetiltcontrol", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'onetiltcontrol'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# liqaccelview1:liqaccelview
	liqcell *arrr = liqcell_quickcreatevis("liqaccelview1", "liqaccelview_alternative", 0,0,-1,-1);
    
	liqcell *liqaccelview1 = liqcell_quickcreatevis("liqaccelview1", NULL, 175, 78, 450, 300);
	liqcell_setcontent(  liqaccelview1,arrr);
    liqcell_propseti(  liqaccelview1, "aspectlock", 1 );
    liqcell_child_append(  self, liqaccelview1);
     
    
	//############################# zoombox1:zoombox
	liqcell *zooml = liqcell_quickcreatevis("zooml", "zoombox", 30, 30, 120, 420);
	liqcell_child_append(  self, zooml);
    
	//############################# zoombox1:zoombox
	liqcell *zoomr = liqcell_quickcreatevis("zoomr", "zoombox", 630,30, 120,420);
	liqcell_child_append(  self, zoomr);    
    
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", onetiltcontrol_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", onetiltcontrol_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", onetiltcontrol_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", onetiltcontrol_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", onetiltcontrol_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", onetiltcontrol_mouse,self );
	liqcell_handleradd_withcontext(self, "click", onetiltcontrol_click ,self);
	liqcell_handleradd_withcontext(self, "paint", onetiltcontrol_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", onetiltcontrol_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", onetiltcontrol_dialog_close ,self);
	return self;
}

