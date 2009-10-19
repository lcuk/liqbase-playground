// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqconfig_fullscreenwindow :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqconfig_fullscreenwindow widget refresh, all params set, present yourself to the user.
 */	
static int liqconfig_fullscreenwindow_refresh(liqcell *self,liqcelleventargs *args, liqcell *liqconfig_fullscreenwindow)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	liqcell *cmdwindowed = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdwindowed");
	liqcell *cmdfullscreen = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdfullscreen");

    int fullscreenflag = atoi(liqapp_pref_getvalue_def("fullscreen","0"));
    if(fullscreenflag)
    {
        liqcell_setselected(cmdwindowed,0);
        liqcell_setselected(cmdfullscreen,1);
        liqcell_propsets(  cmdwindowed, "backcolor", "xrgb(0,0,0)" );
        liqcell_propsets(  cmdfullscreen, "backcolor", "xrgb(0,0,0)" );        

    }
    else
    {
        liqcell_setselected(cmdwindowed,1);
        liqcell_setselected(cmdfullscreen,0);
        liqcell_propsets(  cmdwindowed, "backcolor", "xrgb(0,0,0)" );
        liqcell_propsets(  cmdfullscreen, "backcolor", "xrgb(0,0,0)" );
    }

	return 0;
}
/**	
 * liqconfig_fullscreenwindow dialog_open - the user zoomed into the dialog
 */	
static int liqconfig_fullscreenwindow_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    liqcell_handlerrun(self,"refresh",NULL);
	return 0;
}
/**	
 * liqconfig_fullscreenwindow dialog_close - the dialog was closed
 */	
static int liqconfig_fullscreenwindow_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    liqcell_handlerrun(self,"refresh",NULL);
	return 0;
}
/**	
 * liqconfig_fullscreenwindow widget shown - occurs once per lifetime
 */	
static int liqconfig_fullscreenwindow_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    liqcell_handlerrun(self,"refresh",NULL);
	return 0;
}
/**	
 * liqconfig_fullscreenwindow mouse - occurs all the time as you stroke the screen
 */	
static int liqconfig_fullscreenwindow_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_fullscreenwindow click - occurs when a short mouse stroke occured
 */	
static int liqconfig_fullscreenwindow_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_fullscreenwindow keypress - the user pressed a key
 */	
static int liqconfig_fullscreenwindow_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_fullscreenwindow keyrelease - the user released a key
 */	
static int liqconfig_fullscreenwindow_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqconfig_fullscreenwindow paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqconfig_fullscreenwindow_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqconfig_fullscreenwindow dynamic resizing
 */	
static int liqconfig_fullscreenwindow_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *cmdwindowed = liqcell_child_lookup(self, "cmdwindowed");
	liqcell *cmdfullscreen = liqcell_child_lookup(self, "cmdfullscreen");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell_setrect_autoscale( cmdwindowed, 406,186, 228,162, sx,sy);
	liqcell_setrect_autoscale( label1, 46,56, 724,102, sx,sy);
	liqcell_setrect_autoscale( cmdfullscreen, 138,186, 228,162, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 594,432, 206,48, sx,sy);
	return 0;
}

/**	
 * liqconfig_fullscreenwindow.cmdwindowed clicked
 */	
static int cmdwindowed_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqconfig_fullscreenwindow)
{
	liqcell *cmdwindowed = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdwindowed");
	liqcell *cmdfullscreen = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdfullscreen");
    
    liqcell_setselected(cmdwindowed,1);
    liqcell_setselected(cmdfullscreen,0);

    liqcell_propsets(  cmdwindowed, "backcolor", "xrgb(0,0,0)" );
    liqcell_propsets(  cmdfullscreen, "backcolor", "xrgb(0,0,0)" );
    
	return 0;
}
/**	
 * liqconfig_fullscreenwindow.cmdfullscreen clicked
 */	
static int cmdfullscreen_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqconfig_fullscreenwindow)
{
	liqcell *cmdwindowed = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdwindowed");
	liqcell *cmdfullscreen = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdfullscreen");
    
    liqcell_setselected(cmdwindowed,0);
    liqcell_setselected(cmdfullscreen,1);
    
    liqcell_propsets(  cmdwindowed, "backcolor", "xrgb(0,0,0)" );
    liqcell_propsets(  cmdfullscreen, "backcolor", "xrgb(0,0,0)" );
	return 0;
}
/**	
 * liqconfig_fullscreenwindow.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqconfig_fullscreenwindow)
{
	liqcell *cmdwindowed = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdwindowed");
	liqcell *cmdfullscreen = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdfullscreen");
    
    // get existing
    int fullscreenflag = atoi(liqapp_pref_getvalue_def("fullscreen","0"));
    
    // get new
    int newfullscreenflag=0;
    
    if(liqcell_getselected(cmdfullscreen))
        newfullscreenflag=1;
    else
        newfullscreenflag=0;
        
    if(fullscreenflag!=newfullscreenflag)
    {
        // only change if its different        
        if(newfullscreenflag)
        {
            liqapp_pref_setvalue("fullscreen","1");
            liqapp_prefs_save();
        }
        else
        {
            liqapp_pref_setvalue("fullscreen","0");
            liqapp_prefs_save();
        }
        
        int cw=liqcanvas_getwidth();
        int ch=liqcanvas_getheight();

        liqapp_log("liqconfig_fullscreenwindow: canvas closing");
        liqcanvas_close();
        
        liqapp_sleep(250);
        
        liqapp_sleep(250);
        
        liqapp_log("liqconfig_fullscreenwindow: canvas reopening to new state: %ix%i, fs=%i",cw,ch,newfullscreenflag);
        if(0!=liqcanvas_init( cw,ch, newfullscreenflag))
        {
            liqapp_errorandfail(-1,"liqconfig_fullscreenwindow: canvas Init failed");
            exit(0);                    
        }
    }
    
    

    
    liqcell_propseti(liqconfig_fullscreenwindow,"dialog_running",0);
	return 0;
}

/**	
 * liqconfig_fullscreenwindow_child_test_seek this function shows how to access members
 */	
	  
static void liqconfig_fullscreenwindow_child_test_seek(liqcell *liqconfig_fullscreenwindow)
{	  
	liqcell *cmdwindowed = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdwindowed");
	liqcell *cmdfullscreen = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdfullscreen");
	liqcell *title = liqcell_child_lookup(liqconfig_fullscreenwindow, "title");
	liqcell *cmdaccept = liqcell_child_lookup(liqconfig_fullscreenwindow, "cmdaccept");
	liqcell *label1 = liqcell_child_lookup(liqconfig_fullscreenwindow, "label1");
}	  
/**	
 * create a new liqconfig_fullscreenwindow widget
 */	
liqcell *liqconfig_fullscreenwindow_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqconfig_fullscreenwindow", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqconfig_fullscreenwindow'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# cmdwindowed:label
	liqcell *cmdwindowed = liqcell_quickcreatevis("cmdwindowed", "label", 406, 186, 228, 162);
	liqcell_setfont(	cmdwindowed, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdwindowed, "Windowed" );
	liqcell_propsets(  cmdwindowed, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdwindowed, "backcolor", "xrgb(0,0,0)" );
	liqcell_propsets(  cmdwindowed, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdwindowed, "textalign", 2 );
	liqcell_propseti(  cmdwindowed, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdwindowed, "click", cmdwindowed_click, self );
	liqcell_child_append(  self, cmdwindowed);
	//############################# cmdfullscreen:label
	liqcell *cmdfullscreen = liqcell_quickcreatevis("cmdfullscreen", "label", 138, 186, 228, 162);
	liqcell_setfont(	cmdfullscreen, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdfullscreen, "Fullscreen" );
	liqcell_propsets(  cmdfullscreen, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdfullscreen, "backcolor", "xrgb(0,0,0)" );
	liqcell_propsets(  cmdfullscreen, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdfullscreen, "textalign", 2 );
	liqcell_propseti(  cmdfullscreen, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdfullscreen, "click", cmdfullscreen_click, self );
	liqcell_child_append(  self, cmdfullscreen);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Playground fullscreen mode" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 594, 432, 206, 48);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Update" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 46, 56, 724, 102);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label1, "Select how the liqbase playground should be presented" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label1, "textalign", 2 );
	liqcell_propseti(  label1, "textaligny", 2 );
	liqcell_child_append(  self, label1);
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqconfig_fullscreenwindow_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqconfig_fullscreenwindow_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqconfig_fullscreenwindow_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqconfig_fullscreenwindow_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqconfig_fullscreenwindow_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqconfig_fullscreenwindow_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqconfig_fullscreenwindow_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqconfig_fullscreenwindow_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqconfig_fullscreenwindow_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqconfig_fullscreenwindow_dialog_close ,self);



	return self;
}

