// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### dialogusername :: by gary birkett
//#####################################################################
//#####################################################################
		
		
		
		
		
	static int textbox_keyrelease(liqcell *self, liqcellkeyeventargs *args)
	{
		//liqcell *base = liqcell_getbasewidget(self);
		// i can then use my base to access members as defined by the widget itself
		//liqcell_setcaption(self,args->keystring);
	}
	
/**	
 * liqkeyboard keypress - the user faked pressing a key
 */	
static int liqkeyboard_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *dialogusername)
{
	
	liqcell *frame1 = liqcell_child_lookup(dialogusername, "frame1");
		liqcell *item1 = liqcell_child_lookup(frame1, "item1");
	liqcell *liqkeyboard = liqcell_child_lookup(dialogusername, "liqkeyboard");
	liqcell *buttondel = liqcell_child_lookup(dialogusername, "buttondel");
	liqcell *buttonaccept = liqcell_child_lookup(dialogusername, "buttonaccept");	
	//
	liqcell_handlerrun(item1,"keypress",args);
	
	return 0;
}
/**	
 * liqkeyboard keyrelease - the user faked released a key
 */	
static int liqkeyboard_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *dialogusername)
{
	liqcell *frame1 = liqcell_child_lookup(dialogusername, "frame1");
		liqcell *item1 = liqcell_child_lookup(frame1, "item1");
	liqcell *liqkeyboard = liqcell_child_lookup(dialogusername, "liqkeyboard");
	liqcell *buttondel = liqcell_child_lookup(dialogusername, "buttondel");
	liqcell *buttonaccept = liqcell_child_lookup(dialogusername, "buttonaccept");	
	//
	liqcell_handlerrun(item1,"keyrelease",args);
	
	return 0;
}		
		
		
		

/**	
 * dialogusername.buttondel clicked
 */	
static int buttondel_click(liqcell *self,liqcelleventargs *args, liqcell *dialogusername)
{
	liqcell *frame1 = liqcell_child_lookup(dialogusername, "frame1");
		liqcell *item1 = liqcell_child_lookup(frame1, "item1");
	liqcell *liqkeyboard = liqcell_child_lookup(dialogusername, "liqkeyboard");
	liqcell *buttondel = liqcell_child_lookup(dialogusername, "buttondel");
	liqcell *buttonaccept = liqcell_child_lookup(dialogusername, "buttonaccept");	
	//
	int textbox_fakebackspace(liqcell *textbox);
	textbox_fakebackspace(item1);
	return 0;
}
/**	
 * dialogusername.buttonaccept clicked
 */	
static int buttonaccept_click(liqcell *self,liqcelleventargs *args, liqcell *dialogusername)
{
	liqcell *frame1 = liqcell_child_lookup(dialogusername, "frame1");
		liqcell *item1 = liqcell_child_lookup(frame1, "item1");

	char *tryname = liqcell_getcaption(item1);

	char newname[32];
	
	snprintf(newname,32,tryname);
	liqapp_ensurecleanusername(newname);
	
	liqapp_log("dialogusername: changing user from '%s' to '%s', recommend logout",app.username,newname);
	
	free(app.username);
	app.username = strdup(newname);
	
	
	liqapp_pref_setvalue("username",app.username);
	liqapp_pref_setvalue("userpass","");
	liqapp_prefs_save();
	
	// clear password too

	liqcell_propseti(dialogusername,"dialog_result",1);
	liqcell_setvisible(dialogusername,0);
	return 0;
}
		
		
		
		
		
		
/**	
 * dialogusername widget refresh, all params set, present yourself to the user.
 */	
static int dialogusername_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * dialogusername dialog_open - the user zoomed into the dialog
 */	
static int dialogusername_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * dialogusername dialog_close - the dialog was closed
 */	
static int dialogusername_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * dialogusername widget shown - occurs once per lifetime
 */	
static int dialogusername_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * dialogusername mouse - occurs all the time as you stroke the screen
 */	
static int dialogusername_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * dialogusername click - occurs when a short mouse stroke occured
 */	
static int dialogusername_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * dialogusername keypress - the user pressed a key
 */	
static int dialogusername_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * dialogusername keyrelease - the user released a key
 */	
static int dialogusername_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * dialogusername paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int dialogusername_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * dialogusername dynamic resizing
 */	
static int dialogusername_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *liqkeyboard = liqcell_child_lookup(self, "liqkeyboard");
	liqcell *buttondel = liqcell_child_lookup(self, "buttondel");
	liqcell *frame1 = liqcell_child_lookup(self, "frame1");
		liqcell *item1 = liqcell_child_lookup(frame1, "item1");
		liqcell *label8 = liqcell_child_lookup(frame1, "label8");
		liqcell *label4 = liqcell_child_lookup(frame1, "label4");
		liqcell *label3 = liqcell_child_lookup(frame1, "label3");
		liqcell *label2 = liqcell_child_lookup(frame1, "label2");
		liqcell *label1 = liqcell_child_lookup(frame1, "label1");
		liqcell *item4 = liqcell_child_lookup(frame1, "item4");
		liqcell *clientmap = liqcell_child_lookup(frame1, "clientmap");
		liqcell *item2 = liqcell_child_lookup(frame1, "item2");
		liqcell *item3 = liqcell_child_lookup(frame1, "item3");
	liqcell *buttonaccept = liqcell_child_lookup(self, "buttonaccept");
	liqcell *icon = liqcell_child_lookup(self, "icon");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( buttondel, 710,380, 84,42, sx,sy);
	liqcell_setrect_autoscale( frame1, 10,56, 782,190, sx,sy);
	liqcell_setrect_autoscale( item1, 106,20, 274,36, sx,sy);
	liqcell_setrect_autoscale( label8, 6,202, 90,18, sx,sy);
	liqcell_setrect_autoscale( label4, 6,124, 88,16, sx,sy);
	liqcell_setrect_autoscale( label3, 6,166, 90,18, sx,sy);
	liqcell_setrect_autoscale( label2, 6,76, 90,16, sx,sy);
	liqcell_setrect_autoscale( label1, 8,30, 90,16, sx,sy);
	liqcell_setrect_autoscale( item4, 102,160, 274,34, sx,sy);
	liqcell_setrect_autoscale( clientmap, 102,200, 274,158, sx,sy);
	liqcell_setrect_autoscale( item2, 104,70, 116,34, sx,sy);
	liqcell_setrect_autoscale( item3, 104,116, 116,34, sx,sy);
	liqcell_setrect_autoscale( buttonaccept, 710,432, 84,42, sx,sy);
	liqcell_setrect_autoscale( icon, 6,8, 52,40, sx,sy);
	liqcell_setrect_autoscale( title, 66,6, 396,40, sx,sy);
	liqcell_setrect_autoscale( liqkeyboard, 0, 240, 700, 240, sx,sy);
	return 0;
}

/**	
 * dialogusername_child_test_seek this function shows how to access members
 */	
	  
static void dialogusername_child_test_seek(liqcell *self)
{	  
	liqcell *icon = liqcell_child_lookup(self, "icon");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *frame1 = liqcell_child_lookup(self, "frame1");
		liqcell *label1 = liqcell_child_lookup(frame1, "label1");
		liqcell *item1 = liqcell_child_lookup(frame1, "item1");
	liqcell *liqkeyboard = liqcell_child_lookup(self, "liqkeyboard");
	liqcell *buttondel = liqcell_child_lookup(self, "buttondel");
	liqcell *buttonaccept = liqcell_child_lookup(self, "buttonaccept");
}	  
/**	
 * create a new dialogusername widget
 */	
liqcell *dialogusername_create()
{
	liqcell *self = liqcell_quickcreatewidget("dialogusername", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'dialogusername'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering

	
	
	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 6, 8, 52, 40);
	liqcell_setfont(	icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(icon, "icon" );
	liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);



	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 66, 6, 800-66, 40);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Enter your liqbase username:" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);

	
	//############################# frame1:frame
	liqcell *frame1 = liqcell_quickcreatevis("frame1", "frame", 10, 56, 782, 180);
	liqcell_setfont(	frame1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(frame1, "you can signup for a liqbase account by visiting liqbase.net" );
	liqcell_propsets(  frame1, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  frame1, "backcolor", "rgb(64,64,64)" );

		//############################# label1:label
		liqcell *label1 = liqcell_quickcreatevis("label1", "label", 8, 30, 90, 16);
		liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		liqcell_setcaption(label1, "" );
		liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
		liqcell_propseti(  label1, "textalign", 1 );
		liqcell_child_append(  frame1, label1);

		char *data = app.username;
		if(!data)data="";
		
		//############################# item1:textbox
		liqcell *item1 = liqcell_quickcreatevis("item1", "textbox", 106, 49, 600, 82);
		liqcell_setfont(	item1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (60), 0) );
		liqcell_setcaption(item1, app.username );
		liqcell_propsets(  item1, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  item1, "backcolor", "rgb(0,0,0)" );
		liqcell_propsets(  item1, "bordercolor", "rgb(200,100,100)" );
		liqcell_propseti(  item1, "textalign", 0 );


			liqcell_propseti(  item1,  "selstart",  0 );
			liqcell_propseti(  item1,  "sellength", strlen(liqcell_getcaption(item1)) );
			liqcell_propseti(  item1,  "cursorpos", strlen(liqcell_getcaption(item1)) );

		liqcell_child_append(  frame1, item1);
		
	liqcell_child_append(  self, frame1);
	
	
	
	//############################# liqkeyboard:picturebox
	liqcell *liqkeyboard = liqcell_quickcreatevis("liqkeyboard", "liqkeyboard", 0, 240, 700, 240);
	liqcell_setfont(	liqkeyboard, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_propsets(  liqkeyboard, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  liqkeyboard, "backcolor", "rgb(0,128,128)" );
	liqcell_child_append(  self, liqkeyboard);

	liqcell_handleradd_withcontext(liqkeyboard, "keypress", liqkeyboard_keypress,self );
	liqcell_handleradd_withcontext(liqkeyboard, "keyrelease", liqkeyboard_keyrelease ,self);
	
	
	//############################# buttondel:commandbutton
	liqcell *buttondel = liqcell_quickcreatevis("buttondel", "commandbutton", 700, 240, 100, 120);
	liqcell_setfont(	buttondel, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(buttondel, "< DEL" );
	//liqcell_propsets(  buttondel, "backcolor", "rgb(235,233,237)" );
	liqcell_handleradd_withcontext(buttondel, "click", buttondel_click, self );
	liqcell_propseti(     buttondel,"textalign", 2 );
	liqcell_propseti(     buttondel,"textaligny",2 );
	liqcell_child_append(  self, buttondel);

	//############################# buttonaccept:commandbutton
	liqcell *buttonaccept = liqcell_quickcreatevis("buttonaccept", "commandbutton", 700, 360, 100, 120);
	liqcell_setcaption(buttonaccept, "ENTER" );
	liqcell_setfont(	buttonaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_propsets(  buttonaccept, "backcolor", "rgb(rgb(0,100,0))" );
	liqcell_handleradd_withcontext(buttonaccept, "click", buttonaccept_click, self );
	liqcell_propseti(     buttonaccept,"textalign", 2 );
	liqcell_propseti(     buttonaccept,"textaligny",2 );
	liqcell_child_append(  self, buttonaccept);
	
	
	
	
	
	
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", dialogusername_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", dialogusername_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", dialogusername_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", dialogusername_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", dialogusername_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", dialogusername_mouse,self );
	liqcell_handleradd_withcontext(self, "click", dialogusername_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", dialogusername_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", dialogusername_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", dialogusername_dialog_close ,self);
	return self;
}

