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
//##################################################################### oneconfigure :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * oneconfigure widget refresh, all params set, present yourself to the user.
 */	
static int oneconfigure_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * oneconfigure dialog_open - the user zoomed into the dialog
 */	
static int oneconfigure_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * oneconfigure dialog_close - the dialog was closed
 */	
static int oneconfigure_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{

	liqcell *osc_listen_port = liqcell_child_lookup(self, "osc_listen_port");
	liqcell *osc_send_port = liqcell_child_lookup(self, "osc_send_port");
	liqcell *osc_send_ip = liqcell_child_lookup(self, "osc_send_ip");

	// reload these to make sure we dont make the user think they are set

	liqcell_setcaption(osc_send_ip,    liqapp_pref_getvalue_def("osc_send_ip",    "224.0.0.1") );
	liqcell_setcaption(osc_send_port,  liqapp_pref_getvalue_def("osc_send_port",  "7770") );
	liqcell_setcaption(osc_listen_port,  liqapp_pref_getvalue_def("osc_listen_port","7771") );

	return 0;
}
/**	
 * oneconfigure widget shown - occurs once per lifetime
 */	
static int oneconfigure_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * oneconfigure mouse - occurs all the time as you stroke the screen
 */	
static int oneconfigure_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneconfigure click - occurs when a short mouse stroke occured
 */	
static int oneconfigure_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneconfigure keypress - the user pressed a key
 */	
static int oneconfigure_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneconfigure keyrelease - the user released a key
 */	
static int oneconfigure_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * oneconfigure paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int oneconfigure_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * oneconfigure dynamic resizing
 */	
static int oneconfigure_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
/*	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *osc_listen_port = liqcell_child_lookup(self, "osc_listen_port");
	liqcell *osc_send_port = liqcell_child_lookup(self, "osc_send_port");
	liqcell *osc_send_ip = liqcell_child_lookup(self, "osc_send_ip");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *cmdsave = liqcell_child_lookup(self, "cmdsave");
	liqcell_setrect_autoscale( osc_listen_port, 62,300, 720,54, sx,sy);
	liqcell_setrect_autoscale( osc_send_port, 62,188, 722,54, sx,sy);
	liqcell_setrect_autoscale( osc_send_ip, 62,86, 722,54, sx,sy);
	liqcell_setrect_autoscale( label3, 18,262, 326,30, sx,sy);
	liqcell_setrect_autoscale( label2, 18,150, 326,30, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,38, sx,sy);
	liqcell_setrect_autoscale( label1, 18,48, 326,30, sx,sy);
	liqcell_setrect_autoscale( cmdsave, 586,392, 198,80, sx,sy);
 */	return 0;
}

/**	
 * oneconfigure.cmdsave clicked
 */	
static int cmdsave_click(liqcell *self,liqcelleventargs *args, liqcell *oneconfigure)
{
	liqcell *osc_listen_port = liqcell_child_lookup(oneconfigure, "osc_listen_port");
	liqcell *osc_send_port = liqcell_child_lookup(oneconfigure, "osc_send_port");
	liqcell *osc_send_ip = liqcell_child_lookup(oneconfigure, "osc_send_ip");


	liqapp_pref_setvalue( "osc_send_ip", liqcell_getcaption(osc_send_ip) );
	liqapp_pref_setvalue( "osc_send_port", liqcell_getcaption(osc_send_port) );
	liqapp_pref_setvalue( "osc_listen_port", liqcell_getcaption(osc_listen_port) );

	liqapp_prefs_save();
	
	liqcell_propseti(oneconfigure,"dialog_running",0);
	
	
	// save and reopen the connection..
	osc_onedotzero_close();
	
	osc_onedotzero_init();

	return 0;
}

/**	
 * oneconfigure.cmdback clicked
 */	
static int cmdback_click(liqcell *self,liqcelleventargs *args, liqcell *oneconfigure)
{
    liqcell_setvisible(  oneconfigure,0 );
	return 0;
}

/**	
 * oneconfigure_child_test_seek this function shows how to access members
 */	
	  
static void oneconfigure_child_test_seek(liqcell *self)
{	  
	liqcell *osc_listen_port = liqcell_child_lookup(self, "osc_listen_port");
	liqcell *osc_send_port = liqcell_child_lookup(self, "osc_send_port");
	liqcell *osc_send_ip = liqcell_child_lookup(self, "osc_send_ip");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *cmdsave = liqcell_child_lookup(self, "cmdsave");
}	  
/**	
 * create a new oneconfigure widget
 */	
liqcell *oneconfigure_create()
{
	liqcell *self = liqcell_quickcreatewidget("oneconfigure", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'oneconfigure'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# osc_listen_port:textbox
	liqcell *osc_listen_port = liqcell_quickcreatevis("osc_listen_port", "textbox", 62, 300, 720, 54);
	liqcell_setfont(	osc_listen_port, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(osc_listen_port, "7770" );
	//liqcell_propsets(  osc_listen_port, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  osc_listen_port, "backcolor", "rgb(64,64,0)" );
	//liqcell_propsets(  osc_listen_port, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  osc_listen_port, "textalign", 0 );
	liqcell_child_append(  self, osc_listen_port);
	//############################# osc_send_port:textbox
	liqcell *osc_send_port = liqcell_quickcreatevis("osc_send_port", "textbox", 62, 188, 722, 54);
	liqcell_setfont(	osc_send_port, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(osc_send_port, "7771" );
	//liqcell_propsets(  osc_send_port, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  osc_send_port, "backcolor", "rgb(64,64,0)" );
	//liqcell_propsets(  osc_send_port, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  osc_send_port, "textalign", 0 );
	liqcell_child_append(  self, osc_send_port);
	//############################# osc_send_ip:textbox
	liqcell *osc_send_ip = liqcell_quickcreatevis("osc_send_ip", "textbox", 62, 86, 722, 54);
	liqcell_setfont(	osc_send_ip, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(osc_send_ip, "224.0.0.1" );
	//liqcell_propsets(  osc_send_ip, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  osc_send_ip, "backcolor", "rgb(64,64,0)" );
	//liqcell_propsets(  osc_send_ip, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  osc_send_ip, "textalign", 0 );
	liqcell_child_append(  self, osc_send_ip);
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 18, 262, 326, 30);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label3, "OSC Listen on Port" );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label3, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label3, "textalign", 0 );
	liqcell_child_append(  self, label3);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 18, 150, 326, 30);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label2, "OSC Send to Port" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label2, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label2, "textalign", 0 );
	liqcell_child_append(  self, label2);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 38);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(title, "onedotzero :: configure accounts" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  title, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 18, 48, 326, 30);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label1, "OSC Send to Ip" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label1, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_child_append(  self, label1);
	
	
	//############################# cmdsave:label
	liqcell *cmdsave = liqcell_quickcreatevis("cmdsave", "label", 586, 392, 198, 80);
	liqcell_setfont(	cmdsave, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsave, "save" );
	//liqcell_propsets(  cmdsave, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  cmdsave, "backcolor", "rgb(0,128,0)" );
	//liqcell_propsets(  cmdsave, "bordercolor", "rgb(200,100,100)" );
	//liqcell_propseti(  cmdsave, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdsave, "click", cmdsave_click, self );
	liqcell_propsets(  cmdsave, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  cmdsave, "backcolor", "rgb(0,128,0)" );
	//liqcell_propsets(  cmdsave, "bordercolor", "rgb(200,100,100)" );
	liqcell_setimage(  cmdsave,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/button_back.png", 0,0,1) );
	liqcell_propseti(  cmdsave, "textalign", 2 );
	liqcell_propseti(  cmdsave, "textaligny", 2 );
	liqcell_propseti(  cmdsave,  "lockaspect",  0 );
	liqcell_child_append(  self, cmdsave);
	
	
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", oneconfigure_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", oneconfigure_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", oneconfigure_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", oneconfigure_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", oneconfigure_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", oneconfigure_mouse,self );
	liqcell_handleradd_withcontext(self, "click", oneconfigure_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", oneconfigure_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", oneconfigure_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", oneconfigure_dialog_close ,self);

 


        //############################# cmdback:label
        liqcell *cmdback = liqcell_quickcreatevis("cmdback", "label", 670, 16, 101, 42);
        //liqcell_setfont(	cmdback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
        //liqcell_setcaption(cmdback, "back" );
        //liqcell_propsets(  cmdback, "textcolor", "rgb(0,0,0)" );
        //liqcell_propsets(  cmdback, "backcolor", "rgb(235,233,237)" );
        //liqcell_propseti(  cmdback, "textalign", 0 );
        liqcell_setimage(  cmdback,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/back_button.png", 0,0,1) );
        liqcell_handleradd_withcontext(cmdback, "click", cmdback_click, self );
        liqcell_child_append(  self, cmdback);



	liqcell_setcaption(osc_send_ip,    liqapp_pref_getvalue_def("osc_send_ip",    "224.0.0.1") );
	liqcell_setcaption(osc_send_port,  liqapp_pref_getvalue_def("osc_send_port",  "7770") );
	liqcell_setcaption(osc_listen_port,  liqapp_pref_getvalue_def("osc_listen_port","7771") );


	return self;
}

