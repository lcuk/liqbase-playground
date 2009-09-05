// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### nokiapicture :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * nokiapicture widget refresh, all params set, present yourself to the user.
 */	
static int nokiapicture_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * nokiapicture dialog_open - the user zoomed into the dialog
 */	
static int nokiapicture_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * nokiapicture dialog_close - the dialog was closed
 */	
static int nokiapicture_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * nokiapicture widget shown - occurs once per lifetime
 */	
static int nokiapicture_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * nokiapicture mouse - occurs all the time as you stroke the screen
 */	
static int nokiapicture_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * nokiapicture click - occurs when a short mouse stroke occured
 */	
static int nokiapicture_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * nokiapicture keypress - the user pressed a key
 */	
static int nokiapicture_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * nokiapicture keyrelease - the user released a key
 */	
static int nokiapicture_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * nokiapicture paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int nokiapicture_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * nokiapicture dynamic resizing
 */	
static int nokiapicture_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *picnokia = liqcell_child_lookup(self, "picnokia");
	liqcell_setrect_autoscale( picnokia, 0,0, 132,24, sx,sy);
	return 0;
}

/**	
 * nokiapicture_child_test_seek this function shows how to access members
 */	
	  
static void nokiapicture_child_test_seek(liqcell *self)
{	  
	liqcell *picnokia = liqcell_child_lookup(self, "picnokia");
}	  
/**	
 * create a new nokiapicture widget
 */	
liqcell *nokiapicture_create()
{
	liqcell *self = liqcell_quickcreatewidget("nokiapicture", "form", 130, 24);
	if(!self) {liqapp_log("liqcell error not create 'nokiapicture'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
/*	//############################# picnokia:label
	liqcell *picnokia = liqcell_quickcreatevis("picnokia", "label", 0, 0, 132, 24);
	liqcell_setfont(	picnokia, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	liqcell_setcaption(picnokia, "Nokia" );
	liqcell_propsets(  picnokia, "textcolor", "rgb(192,192,192)" );
	liqcell_propsets(  picnokia, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  picnokia, "textalign", 2 );
	liqcell_child_append(  self, picnokia);
 */

	liqcell_propsets(  self, "imagefilename",  "/usr/share/liqbase/onedotzero/media/2_nokia.png" );
	liqcell_propseti(  self, "autosize", 1 );
	
	//liqcell_propsets(  self, "backcolor", "rgb(235,233,237)" );
	liqcell_handleradd_withcontext(self, "refresh", nokiapicture_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", nokiapicture_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", nokiapicture_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", nokiapicture_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", nokiapicture_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", nokiapicture_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", nokiapicture_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", nokiapicture_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", nokiapicture_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", nokiapicture_dialog_close ,self);
	return self;
}

