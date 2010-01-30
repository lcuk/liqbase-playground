// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>


extern int liqcell_easyrun_fingerpressed;

//#####################################################################
//#####################################################################
//##################################################################### liqmic_run :: by gary birkett
//#####################################################################
//#####################################################################
		
		
//int listen_main(liqcell *liqmic_run) {

/**	
 * handle the timer to fire the session off
 */	

static int liqmic_run_timer1_tick(liqcell *self, liqcellmouseeventargs *args, void *liqmic_run)
{
    liqcell_propseti(self,"timerinterval", 32767 );
    liqcell_setenabled(self,0);
	listen_main(liqmic_run);
}
		
/**	
 * liqmic_run widget refresh, all params set, present yourself to the user.
 */	
static int liqmic_run_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqmic_run dialog_open - the user zoomed into the dialog
 */	
static int liqmic_run_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmic_run dialog_close - the dialog was closed
 */	
static int liqmic_run_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmic_run widget shown - occurs once per lifetime
 */	
static int liqmic_run_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmic_run mouse - occurs all the time as you stroke the screen
 */	
static int liqmic_run_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmic_run click - occurs when a short mouse stroke occured
 */	
static int liqmic_run_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmic_run keypress - the user pressed a key
 */	
static int liqmic_run_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmic_run keyrelease - the user released a key
 */	
static int liqmic_run_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}

/**	
 * liqmic_run paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
static int liqmic_run_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{

	// big heavy event, use sparingly
	return 0;
}

/**	
 * liqmic_run dynamic resizing
 */	
static int liqmic_run_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
/*	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
		liqcell *canvas = liqcell_child_lookup(backplane, "canvas");
	liqcell *liqanimframecounter1 = liqcell_child_lookup(self, "liqanimframecounter1");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *cmdrecordstop = liqcell_child_lookup(self, "cmdrecordstop");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( cmdrecordstop, 652,432, 148,48, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,38, sx,sy);
	liqcell_setrect_autoscale( liqanimframecounter1, 54,432, 594,48, sx,sy);
	liqcell_setrect_autoscale( label1, 606,0, 136,36, sx,sy);
	liqcell_setrect_autoscale( backplane, 0,40, 800,388, sx,sy);
	liqcell_setrect_autoscale( canvas, 584,0, 216,388, sx,sy);
*/	return 0;
}

/**	
 * liqmic_run.cmdrecordstop clicked
 */	
static int cmdrecordstop_click(liqcell *self,liqcelleventargs *args, liqcell *liqmic_run)
{
    // get the accelerometer data
    // and add it to a sketch
    
    
    
	return 0;
}
/**	
 * liqmic_run_child_test_seek this function shows how to access members
 */	
	  
static void liqmic_run_child_test_seek(liqcell *self)
{	  
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
		liqcell *canvas = liqcell_child_lookup(backplane, "canvas");
	//liqcell *liqanimframecounter1 = liqcell_child_lookup(self, "liqanimframecounter1");
	//liqcell *label1 = liqcell_child_lookup(self, "label1");
	//liqcell *cmdrecordstop = liqcell_child_lookup(self, "cmdrecordstop");
	liqcell *title = liqcell_child_lookup(self, "title");
}	  
/**	
 * create a new liqmic_run widget
 */	
liqcell *liqmic_run_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqmic_run", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqmic_run'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# backplane:picturebox
	liqcell *backplane = liqcell_quickcreatevis("backplane", "picturebox", 0, 40, 800, 440);
	//liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  backplane, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  backplane, "backcolor", "rgb(128,128,128)" );
		//############################# canvas:label
		liqcell *canvas = liqcell_quickcreatevis("canvas", "label", 584, 0, 216, 440);
		//liqcell_setfont(	canvas, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_setcaption(canvas, "canvas" );
		//liqcell_propsets(  canvas, "textcolor", "rgb(255,0,0)" );
		//liqcell_propsets(  canvas, "backcolor", "rgb(64,64,64)" );
		//liqcell_propseti(  canvas, "textalign", 2 );
        liqcell_propseti( canvas ,  "lockaspect", 0 );
        liqcell_propseti(canvas,"sketchediting",1);
		liqcell_child_append(  backplane, canvas);
		liqcell_handleradd_withcontext(canvas, "mouse", liqcell_easyhandler_kinetic_mouse ,self);
		
		
	liqcell_child_append(  self, backplane);
	

	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 38);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "microphone recording" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);



    liqsketch *sketch = liqcell_getsketch(canvas);
    if(!sketch)
    {
        sketch = liqsketch_new();
		if(!sketch)
		{
			liqapp_log("liqsketchedit_save_click nothing to save");
			return 0;
		}
					
        sketch->pixelwidth =32767;
        sketch->pixelheight=0;
        
        sketch->dpix=225;	// damn, dont like using this here
        sketch->dpiy=225;
        
        
		if(!sketch)
		{
			liqapp_log("liqsketchedit_save_click nothing to save");
			return 0;
		}
        
        canvas->x=backplane->w;
        canvas->w=0;
        
        liqcell_setsketch(canvas,sketch);
    }
    



	
    //############################# timer1:liqtimer
    liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
    liqcell_propseti(timer1,"timerinterval", 25 );
    liqcell_handleradd_withcontext(timer1,"timertick",liqmic_run_timer1_tick,self);
    liqcell_setenabled(timer1,1);
    liqcell_child_insert( self,timer1);
	
	
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqmic_run_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqmic_run_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqmic_run_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqmic_run_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqmic_run_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqmic_run_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqmic_run_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqmic_run_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqmic_run_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqmic_run_dialog_close ,self);
	return self;
}

