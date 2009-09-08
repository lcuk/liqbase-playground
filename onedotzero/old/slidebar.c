// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### slidebar :: by gary birkett
//#####################################################################
//#####################################################################


/**	
 * slidebar set value.
 */	
int slidebar_setvalue(liqcell *self,float percentvalue)
{
	liqcell *knob = liqcell_child_lookup(self, "knob");
	//liqapp_log(">>>>>>>>slide1: %i, %f",knob->x,percentvalue);



	if(percentvalue<0)percentvalue=0;
	if(percentvalue>100)percentvalue=100;
	
	knob->x = 0.01 * percentvalue * ((float)(self->w-knob->w));
	//liqapp_log(">>>>>>>>slide2: %i, %f",knob->x,percentvalue);
	
	char knobcap[32];
	snprintf(knobcap,sizeof(knobcap),"%3.0f",percentvalue);
	liqcell_setcaption(knob, knobcap );
	
	
	return 0;
}
		
/**	
 * slidebar widget refresh, all params set, present yourself to the user.
 */	
static int slidebar_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit

	liqcell *knob = liqcell_child_lookup(self, "knob");


	float upto = 0;
	if((self->w-knob->w)>0)
	{
		upto = ((float)knob->x) / ((float)(self->w-knob->w));			
	}
	char knobcap[32];
	snprintf(knobcap,sizeof(knobcap),"%3.0f",upto * 100.0);
	
	liqcell_setcaption(knob, knobcap );
	
	
	return 0;
}
/**	
 * slidebar dialog_open - the user zoomed into the dialog
 */	
static int slidebar_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * slidebar dialog_close - the dialog was closed
 */	
static int slidebar_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * slidebar widget shown - occurs once per lifetime
 */	
static int slidebar_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	liqcell_handlerrun(self,"refresh",NULL);
	return 0;
}

/**	
 * slidebar mouse - occurs all the time as you stroke the screen
 */	
static int slidebar_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	liqcell *knob = liqcell_child_lookup(self, "knob");

	liqcell_setpos( knob, args->mex - args->ox - (knob->w/2), liqcell_gety(knob) );
	liqcell_forceinboundparent(knob);
	
	liqcell_handlerrun(self,"refresh",NULL);
	
	return 0;
}
/**	
 * slidebar click - occurs when a short mouse stroke occured
 */	
static int slidebar_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * slidebar keypress - the user pressed a key
 */	
static int slidebar_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * slidebar keyrelease - the user released a key
 */	
static int slidebar_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * slidebar paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int slidebar_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * slidebar dynamic resizing
 */	
static int slidebar_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *knob = liqcell_child_lookup(self, "knob");
	liqcell_setrect_autoscale( knob, 178,2, 150,30, sx,sy);
	return 0;
}

/**	
 * slidebar_child_test_seek this function shows how to access members
 */	
	  
static void slidebar_child_test_seek(liqcell *self)
{	  
	liqcell *resize1 = liqcell_child_lookup(self, "resize1");
	liqcell *knob = liqcell_child_lookup(self, "knob");
}	  
/**	
 * create a new slidebar widget
 */	
liqcell *slidebar_create()
{
	liqcell *self = liqcell_quickcreatewidget("slidebar", "form", 370, 34);
	if(!self) {liqapp_log("liqcell error not create 'slidebar'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# knob:label
	liqcell *knob = liqcell_quickcreatevis("knob", "label", 178, 2, 150, 30);
	liqcell_setfont(	knob, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (28), 0) );
	liqcell_setcaption(knob, "94" );
	
	//liqcell_propsets(  knob, "textcolor", "rgb(192,255,192)" );
	//liqcell_propsets(  knob, "backcolor", "rgb(0,64,0)" );
	//liqcell_propsets(  knob, "bordercolor", "rgb(200,100,100)" );
	//liqcell_propseti(  knob, "textalign", 2 );
	//liqcell_propseti(  knob, "textaligny", 2 );
	
		liqcell_propsets(  knob, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  knob, "backcolor", "rgb(0,0,128)" );
		//liqcell_propsets(  knob, "bordercolor", "rgb(200,100,100)" );
		liqcell_propseti(  knob, "textalign", 2 );
		liqcell_propseti(  knob, "textaligny", 2 );
		liqcell_propsets(  knob, "imagefilename",  "/usr/share/liqbase/onedotzero/media/button_back.png" );
		liqcell_propseti(  knob,  "lockaspect",  0 );

	
	liqcell_child_append(  self, knob);
	liqcell_propsets(  self, "backcolor", "rgba(0,0,64,128)" );
	liqcell_handleradd_withcontext(self, "refresh", slidebar_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", slidebar_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", slidebar_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", slidebar_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", slidebar_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", slidebar_mouse,self );
	liqcell_handleradd_withcontext(self, "click", slidebar_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", slidebar_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", slidebar_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", slidebar_dialog_close ,self);
	return self;
}

