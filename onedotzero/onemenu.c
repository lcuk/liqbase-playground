// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>


#include "osc_onedotzero.h"


//    osc_onedotzero_send_();		
		
//#####################################################################
//#####################################################################
//##################################################################### onemenu :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * onemenu widget refresh, all params set, present yourself to the user.
 */	
static int onemenu_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * onemenu dialog_open - the user zoomed into the dialog
 */	
static int onemenu_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    osc_onedotzero_send_menuscreen();
	return 0;
}
/**	
 * onemenu dialog_close - the dialog was closed
 */	
static int onemenu_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onemenu widget shown - occurs once per lifetime
 */	
static int onemenu_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onemenu mouse - occurs all the time as you stroke the screen
 */	
static int onemenu_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemenu click - occurs when a short mouse stroke occured
 */	
static int onemenu_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemenu keypress - the user pressed a key
 */	
static int onemenu_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{

     if(args->keycode==111 && args->keymodifierstate==4)
     {
		liqcell * conf = liqcell_quickcreatevis("a","onedotzero.oneconfigure",0,0,-1,-1);

	    liqcell_easyrun(conf);          
     }
	 return 0;
}
/**	
 * onemenu keyrelease - the user released a key
 */	
static int onemenu_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemenu paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int onemenu_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * onemenu dynamic resizing
 */	
static int onemenu_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *cmdtilt = liqcell_child_lookup(self, "cmdtilt");
	liqcell *nokiapicture1 = liqcell_child_lookup(self, "nokiapicture1");
	liqcell *cmdshake = liqcell_child_lookup(self, "cmdshake");
	liqcell *cmdtouch = liqcell_child_lookup(self, "cmdtouch");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *lbltile = liqcell_child_lookup(self, "lbltile");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( cmdtilt, 54,144, 216,164, sx,sy);
	liqcell_setrect_autoscale( nokiapicture1, 652,438, 130,24, sx,sy);
	liqcell_setrect_autoscale( cmdshake, 284,144, 216,164, sx,sy);
	liqcell_setrect_autoscale( cmdtouch, 514,144, 216,164, sx,sy);
	liqcell_setrect_autoscale( label3, 12,46, 772,40, sx,sy);
	liqcell_setrect_autoscale( label2, 538,318, 166,34, sx,sy);
	liqcell_setrect_autoscale( label1, 312,318, 166,34, sx,sy);
	liqcell_setrect_autoscale( lbltile, 82,318, 166,34, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,38, sx,sy);
	return 0;
}

/**	
 * onemenu.cmdtilt clicked
 */	
static int cmdtilt_click(liqcell *self,liqcellclickeventargs *args, liqcell *onemenu)
{
	osc_onedotzero_send_menu(0);
	//args->newdialogtoopen = liqcell_quickcreatevis("a","onedotzero.liqaccelview_angle",0,0,-1,-1);
	//args->newdialogtoopen = liqcell_quickcreatevis("onedotzero.liqaccelview","onedotzero.liqaccelview_alternative",0,0,-1,-1);
	args->newdialogtoopen = liqcell_quickcreatevis("onetiltcontrol","onedotzero.onetiltcontrol",0,0,-1,-1);
	return 1;	
}
/**	
 * onemenu.cmdshake clicked
 */	
static int cmdshake_click(liqcell *self,liqcellclickeventargs *args, liqcell *onemenu)
{
	osc_onedotzero_send_menu(1);
	args->newdialogtoopen = liqcell_quickcreatevis("onedotzero.liqflow","onedotzero.liqflow",0,0,-1,-1);
	return 1;
}
/**	
 * onemenu.cmdtouch clicked
 */	
static int cmdtouch_click(liqcell *self,liqcellclickeventargs *args, liqcell *onemenu)
{
	osc_onedotzero_send_menu(2);
	args->newdialogtoopen = liqcell_quickcreatevis("onedotzero.onemove","onedotzero.onemove",0,0,-1,-1);
	return 1;
}
/**	
 * onemenu_child_test_seek this function shows how to access members
 */	
	  
static void onemenu_child_test_seek(liqcell *self)
{	  
	liqcell *cmdtilt = liqcell_child_lookup(self, "cmdtilt");
	liqcell *nokiapicture1 = liqcell_child_lookup(self, "nokiapicture1");
	liqcell *cmdshake = liqcell_child_lookup(self, "cmdshake");
	liqcell *cmdtouch = liqcell_child_lookup(self, "cmdtouch");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *lbltile = liqcell_child_lookup(self, "lbltile");
	liqcell *title = liqcell_child_lookup(self, "title");
}	  
/**	
 * create a new onemenu widget
 */	
liqcell *onemenu_create()
{
	liqcell *self = liqcell_quickcreatewidget("onemenu", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'onemenu'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# cmdtilt:buttonrollover
	liqcell *cmdtilt = liqcell_quickcreatevis("cmdtilt", "buttonrollover", 54, 144, 216, 164);
	liqcell_setcaption(cmdtilt, "Tilt" );
	liqcell_propsets(  cmdtilt, "imagefilename_pressed",  "/usr/share/liqbase/onedotzero/media/3_tilt_ico.png" );
	liqcell_propsets(  cmdtilt, "imagefilename_released", "/usr/share/liqbase/onedotzero/media/3_tilt_ico.png" );
	liqcell_handleradd_withcontext(cmdtilt, "click", cmdtilt_click, self );
	liqcell_child_append(  self, cmdtilt);
	//############################# nokiapicture1:nokiapicture
	liqcell *nokiapicture1 = liqcell_quickcreatevis("nokiapicture1", "nokiapicture", 652, 438, 130, 24);
	liqcell_child_append(  self, nokiapicture1);
	//############################# cmdshake:buttonrollover
	liqcell *cmdshake = liqcell_quickcreatevis("cmdshake", "buttonrollover", 284, 144, 216, 164);
	liqcell_setcaption(cmdshake, "Shake" );
	liqcell_handleradd_withcontext(cmdshake, "click", cmdshake_click, self );
	liqcell_propsets(  cmdshake, "imagefilename_pressed",  "/usr/share/liqbase/onedotzero/media/3_shake_ico.png" );
	liqcell_propsets(  cmdshake, "imagefilename_released", "/usr/share/liqbase/onedotzero/media/3_shake_ico.png" );
	liqcell_child_append(  self, cmdshake);
	//############################# cmdtouch:buttonrollover
	liqcell *cmdtouch = liqcell_quickcreatevis("cmdtouch", "buttonrollover", 514, 144, 216, 164);
	liqcell_setcaption(cmdtouch, "Touch" );
	liqcell_handleradd_withcontext(cmdtouch, "click", cmdtouch_click, self );
	liqcell_propsets(  cmdtouch, "imagefilename_pressed",  "/usr/share/liqbase/onedotzero/media/3_touch_ico.png" );
	liqcell_propsets(  cmdtouch, "imagefilename_released", "/usr/share/liqbase/onedotzero/media/3_touch_ico.png" );
	liqcell_child_append(  self, cmdtouch);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 538, 318, 166, 34);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (26), 0) );
	liqcell_setcaption(label2, "Touch" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label2, "textalign", 2 );
	liqcell_child_append(  self, label2);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 312, 318, 166, 34);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (26), 0) );
	liqcell_setcaption(label1, "Shake" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label1, "textalign", 2 );
	liqcell_child_append(  self, label1);
	
	
	//############################# lbltile:label
	liqcell *lbltile = liqcell_quickcreatevis("lbltile", "label", 82, 318, 166, 34);
	liqcell_setfont(	lbltile, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (26), 0) );
	liqcell_setcaption(lbltile, "Tilt" );
	liqcell_propsets(  lbltile, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  lbltile, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lbltile, "textalign", 2 );
	liqcell_child_append(  self, lbltile);
	
	
	/*
	//############################# label3:label
	liqcell *lbllastmessage = liqcell_quickcreatevis("label3", "label", 12, 0, 772, 40);
	liqcell_setfont(	lbllastmessage, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_propsets(  lbllastmessage, "textcolor", "rgb(255,255,0)" );
	//liqcell_propsets(  label3, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  lbllastmessage, "textalign", 0 );
	liqcell_child_append(  self, lbllastmessage);
	
	if(get_osc_onedotzero_lastmsg())
		liqcell_setcaption_printf(lbllastmessage, "Message: %s",get_osc_onedotzero_lastmsg() );
	else
		liqcell_setcaption_printf(lbllastmessage, "No message" );
	*/	
	
/*	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 38);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "onedotzero :: menu" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
 */	
//	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", onemenu_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", onemenu_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", onemenu_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", onemenu_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", onemenu_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", onemenu_mouse,self );
	liqcell_handleradd_withcontext(self, "click", onemenu_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", onemenu_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", onemenu_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", onemenu_dialog_close ,self);
	return self;
}

