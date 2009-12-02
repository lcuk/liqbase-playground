// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>

#include <liqbase/liqapp_prefs.h>
		
		
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
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *scsserver = liqcell_child_lookup(self, "scsserver");
	liqcell *twitterpassword = liqcell_child_lookup(self, "twitterpassword");
	liqcell *twitterusername = liqcell_child_lookup(self, "twitterusername");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *cmdsave = liqcell_child_lookup(self, "cmdsave");
	liqcell_setrect_autoscale( scsserver, 18,300, 764,58, sx,sy);
	liqcell_setrect_autoscale( twitterpassword, 18,188, 764,60, sx,sy);
	liqcell_setrect_autoscale( twitterusername, 18,86, 764,54, sx,sy);
	liqcell_setrect_autoscale( label3, 18,262, 700,30, sx,sy);
	liqcell_setrect_autoscale( label2, 18,150, 326,30, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,38, sx,sy);
	liqcell_setrect_autoscale( label1, 18,48, 326,30, sx,sy);
	liqcell_setrect_autoscale( cmdsave, 586,392, 198,80, sx,sy);
	return 0;
}

/**	
 * oneconfigure.cmdsave clicked
 */	
static int cmdsave_click(liqcell *self,liqcelleventargs *args, liqcell *oneconfigure)
{
	liqcell *twitterusername = liqcell_child_lookup(oneconfigure, "twitterusername");
	liqcell *twitterpassword = liqcell_child_lookup(oneconfigure, "twitterpassword");
	liqcell *scsserver = liqcell_child_lookup(oneconfigure, "scsserver");


	liqapp_pref_setvalue( "scsserver", liqcell_getcaption(scsserver) );
	liqapp_pref_setvalue( "twitname", liqcell_getcaption(twitterusername) );
	liqapp_pref_setvalue( "twitpass", liqcell_getcaption(twitterpassword) );

	liqapp_prefs_save();
	
	liqcell_propseti(oneconfigure,"dialog_running",0);

	return 0;
}
/**	
 * oneconfigure_child_test_seek this function shows how to access members
 */	
	  
static void oneconfigure_child_test_seek(liqcell *self)
{	  
	liqcell *scsserver = liqcell_child_lookup(self, "scsserver");
	liqcell *twitterpassword = liqcell_child_lookup(self, "twitterpassword");
	liqcell *twitterusername = liqcell_child_lookup(self, "twitterusername");
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
	//############################# scsserver:textbox
	liqcell *scsserver = liqcell_quickcreatevis("scsserver", "textbox", 18, 300, 764, 58);
	liqcell_setfont(	scsserver, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(scsserver, "SCS_server" );
	//liqcell_propsets(  scsserver, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  scsserver, "backcolor", "rgb(64,64,0)" );
	//liqcell_propsets(  scsserver, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  scsserver, "textalign", 0 );
	liqcell_child_append(  self, scsserver);
	//############################# twitterpassword:textbox
	liqcell *twitterpassword = liqcell_quickcreatevis("twitterpassword", "textbox", 18, 188, 764, 60);
	liqcell_setfont(	twitterpassword, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(twitterpassword, "twitter_password" );
	liqcell_propseti(  twitterpassword, "textispassword", 1 );
	//liqcell_propsets(  twitterpassword, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  twitterpassword, "backcolor", "rgb(64,64,0)" );
	//liqcell_propsets(  twitterpassword, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  twitterpassword, "textalign", 0 );
	liqcell_child_append(  self, twitterpassword);
	//############################# twitterusername:textbox
	liqcell *twitterusername = liqcell_quickcreatevis("twitterusername", "textbox", 18, 86, 764, 54);
	liqcell_setfont(	twitterusername, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(twitterusername, "twitter_username" );
	//liqcell_propsets(  twitterusername, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  twitterusername, "backcolor", "rgb(64,64,0)" );
	//liqcell_propsets(  twitterusername, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  twitterusername, "textalign", 0 );
	liqcell_child_append(  self, twitterusername);
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 18, 262, 700, 30);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label3, "SCS server:   scs servr receives strokes when drawn in liqflow.  leave blank." );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label3, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label3, "textalign", 0 );
	liqcell_child_append(  self, label3);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 18, 150, 326, 30);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label2, "Twitter Password:" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label2, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label2, "textalign", 0 );
	liqcell_child_append(  self, label2);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 38);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(title, "onedotzero :: configure accounts" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 18, 48, 326, 30);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label1, "Twitter Username:" );
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
	liqcell_child_append(  self, cmdsave);
	
	liqcell_propsets(  cmdsave, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  cmdsave, "backcolor", "rgb(0,128,0)" );
	//liqcell_propsets(  cmdsave, "bordercolor", "rgb(200,100,100)" );
	liqcell_setimage(  cmdsave,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/button_back.png", 0,0,1) );
	liqcell_propseti(  cmdsave, "textalign", 2 );
	liqcell_propseti(  cmdsave, "textaligny", 2 );
	liqcell_propseti(  cmdsave,  "lockaspect",  0 );
	
	
	
	
	
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
	
	//liqapp_pref_setvalue( "scsserver", liqcell_getcaption(scsserver) );
	//liqapp_pref_setvalue( "twitname",  liqcell_getcaption(twitterusername) );
	//liqapp_pref_setvalue( "twitpass",  liqcell_getcaption(twitterpassword) );
	
	liqcell_setcaption(scsserver,        liqapp_pref_getvalue_def("scsserver","") );
	liqcell_setcaption(twitterusername,  liqapp_pref_getvalue_def("twitname","") );
	liqcell_setcaption(twitterpassword,  liqapp_pref_getvalue_def("twitpass","") );
	
	return self;
}

