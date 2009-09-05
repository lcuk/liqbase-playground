// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### buttonrollover :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * buttonrollover widget refresh, all params set, present yourself to the user.
 */	
static int buttonrollover_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * buttonrollover dialog_open - the user zoomed into the dialog
 */	
static int buttonrollover_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * buttonrollover dialog_close - the dialog was closed
 */	
static int buttonrollover_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * buttonrollover widget shown - occurs once per lifetime
 */	
static int buttonrollover_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	char *fnf=NULL;
		  fnf = liqcell_propgets(self,"imagefilename_released",NULL);
	if(fnf)
	{
		liqcell_setimage(self, liqimage_cache_getfile(fnf, 0,0,1) );
	}	
	return 0;
}
/**	
 * buttonrollover mouse - occurs all the time as you stroke the screen
 */	
static int buttonrollover_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *buttonrollover)
{
	//liqcell *lbltitle = liqcell_child_lookup(buttonrollover, "lbltitle");
	char *fnf=NULL;
	if(args->mcnt==1)
	{
		// starting
		fnf = liqcell_propgets(self,"imagefilename_pressed",NULL);
		//liqcell_setenabled(lbltitle,0);
		liqcell_propsets(  self, "backcolor", "rgb(0,64,0)" );
	}
	else
	{
		if(args->mez)
		{
			// in progress
		}
		else
		{
			// finishing
			fnf = liqcell_propgets(self,"imagefilename_released",NULL);
			//liqcell_setenabled(lbltitle,1);
			liqcell_propremoves(  self, "backcolor" );
		}
	}
	if(fnf)
	{
		liqcell_setimage(self, liqimage_cache_getfile(fnf, 0,0,1) );
	}
	return 0;
}
/**	
 * buttonrollover click - occurs when a short mouse stroke occured
 */	
static int buttonrollover_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * buttonrollover keypress - the user pressed a key
 */	
static int buttonrollover_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * buttonrollover keyrelease - the user released a key
 */	
static int buttonrollover_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * buttonrollover paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int buttonrollover_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * buttonrollover dynamic resizing
 */	
static int buttonrollover_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *lbltitle = liqcell_child_lookup(self, "lbltitle");
	liqcell_setrect_autoscale( lbltitle, 32,34, 154,46, sx,sy);
	return 0;
}

/**	
 * buttonrollover_child_test_seek this function shows how to access members
 */	
	  
static void buttonrollover_child_test_seek(liqcell *self)
{	  
	liqcell *lbltitle = liqcell_child_lookup(self, "lbltitle");
}	  
/**	
 * create a new buttonrollover widget
 */	
liqcell *buttonrollover_create()
{
	liqcell *self = liqcell_quickcreatewidget("buttonrollover", "form", 214, 114);
	if(!self) {liqapp_log("liqcell error not create 'buttonrollover'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
/*	//############################# lbltitle:label
	liqcell *lbltitle = liqcell_quickcreatevis("lbltitle", "label", 32, 34, 154, 46);
	liqcell_setfont(	lbltitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(lbltitle, "RolloverButton" );
	liqcell_propsets(  lbltitle, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  lbltitle, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  lbltitle, "textalign", 2 );
	liqcell_child_append(  self, lbltitle);
 */	
	
	//liqcell_propsets(  self, "backcolor", "rgb(0,64,0)" );
	liqcell_handleradd_withcontext(self, "refresh", buttonrollover_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", buttonrollover_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", buttonrollover_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", buttonrollover_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", buttonrollover_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", buttonrollover_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", buttonrollover_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", buttonrollover_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", buttonrollover_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", buttonrollover_dialog_close ,self);
	return self;
}

