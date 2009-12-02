// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqtorch_run :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqtorch_run widget refresh, all params set, present yourself to the user.
 */	
static int liqtorch_run_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqtorch_run dialog_open - the user zoomed into the dialog
 */	
static int liqtorch_run_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtorch_run dialog_close - the dialog was closed
 */	
static int liqtorch_run_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtorch_run widget shown - occurs once per lifetime
 */	
static int liqtorch_run_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtorch_run mouse - occurs all the time as you stroke the screen
 */	
static int liqtorch_run_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtorch_run click - occurs when a short mouse stroke occured
 */	
static int liqtorch_run_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtorch_run keypress - the user pressed a key
 */	
static int liqtorch_run_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtorch_run keyrelease - the user released a key
 */	
static int liqtorch_run_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtorch_run paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqtorch_run_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqtorch_run dynamic resizing
 */	
static int liqtorch_run_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	return 0;
}

/**	
 * liqtorch_run_child_test_seek this function shows how to access members
 */	
	  
static void liqtorch_run_child_test_seek(liqcell *self)
{	  
}	  
/**	
 * create a new liqtorch_run widget
 */	
liqcell *liqtorch_run_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqtorch_run", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqtorch_run'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	liqcell_propsets(  self, "backcolor", "rgb(255,255,255)" );
	liqcell_handleradd_withcontext(self, "refresh", liqtorch_run_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqtorch_run_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqtorch_run_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqtorch_run_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqtorch_run_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqtorch_run_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqtorch_run_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqtorch_run_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqtorch_run_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqtorch_run_dialog_close ,self);
	return self;
}

