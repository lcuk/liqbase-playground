// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
int slidebar_setvalue(liqcell *self,float percentvalue);
//#####################################################################
//#####################################################################
//##################################################################### onetouchslide :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * onetouchslide widget refresh, all params set, present yourself to the user.
 */	
static int onetouchslide_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * onetouchslide dialog_open - the user zoomed into the dialog
 */	
static int onetouchslide_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onetouchslide dialog_close - the dialog was closed
 */	
static int onetouchslide_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onetouchslide widget shown - occurs once per lifetime
 */	
static int onetouchslide_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onetouchslide mouse - occurs all the time as you stroke the screen
 */	
static int onetouchslide_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetouchslide click - occurs when a short mouse stroke occured
 */	
static int onetouchslide_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetouchslide keypress - the user pressed a key
 */	
static int onetouchslide_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetouchslide keyrelease - the user released a key
 */	
static int onetouchslide_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetouchslide paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int onetouchslide_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * onetouchslide dynamic resizing
 */	
static int onetouchslide_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *slidebar1 = liqcell_child_lookup(self, "slidebar1");
	liqcell *slidebar2 = liqcell_child_lookup(self, "slidebar2");
	liqcell *slidebar3 = liqcell_child_lookup(self, "slidebar3");
	liqcell *cmdsave = liqcell_child_lookup(self, "cmdsave");
	liqcell *label4 = liqcell_child_lookup(self, "label4");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *onetouchslide = liqcell_child_lookup(self, "onetouchslide");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( slidebar1, 184,172, 524,64, sx,sy);
	liqcell_setrect_autoscale( slidebar2, 182,250, 524,64, sx,sy);
	liqcell_setrect_autoscale( slidebar3, 182,328, 524,64, sx,sy);
	liqcell_setrect_autoscale( cmdsave, 586,424, 198,48, sx,sy);
	liqcell_setrect_autoscale( label4, 62,342, 100,36, sx,sy);
	liqcell_setrect_autoscale( label3, 26,100, 762,40, sx,sy);
	liqcell_setrect_autoscale( label2, 26,56, 762,40, sx,sy);
	liqcell_setrect_autoscale( label1, 62,264, 100,36, sx,sy);
	liqcell_setrect_autoscale( onetouchslide, 64,184, 100,40, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,46, sx,sy);
	return 0;
}

/**	
 * onetouchslide.cmdsave clicked
 */	
static int cmdsave_click(liqcell *self,liqcelleventargs *args, liqcell *onetouchslide)
{
	liqcell *slidebar1 = liqcell_child_lookup(onetouchslide, "slidebar1");
	liqcell *slidebar2 = liqcell_child_lookup(onetouchslide, "slidebar2");
	liqcell *slidebar3 = liqcell_child_lookup(onetouchslide, "slidebar3");


	slidebar_setvalue( slidebar1, 50 );
	slidebar_setvalue( slidebar2, 50 );
	slidebar_setvalue( slidebar3, 50 );

	return 0;
}
/**	
 * onetouchslide_child_test_seek this function shows how to access members
 */	
	  
static void onetouchslide_child_test_seek(liqcell *self)
{	  
	liqcell *slidebar1 = liqcell_child_lookup(self, "slidebar1");
	liqcell *slidebar2 = liqcell_child_lookup(self, "slidebar2");
	liqcell *slidebar3 = liqcell_child_lookup(self, "slidebar3");
	liqcell *cmdsave = liqcell_child_lookup(self, "cmdsave");
	liqcell *label4 = liqcell_child_lookup(self, "label4");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *onetouchslide = liqcell_child_lookup(self, "onetouchslide");
	liqcell *title = liqcell_child_lookup(self, "title");
}	  
/**	
 * create a new onetouchslide widget
 */	
liqcell *onetouchslide_create()
{
	liqcell *self = liqcell_quickcreatewidget("onetouchslide", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'onetouchslide'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# slidebar1:slidebar
	liqcell *slidebar1 = liqcell_quickcreatevis("slidebar1", "slidebar", 184, 172, 524, 64);
	liqcell_child_append(  self, slidebar1);
	//############################# slidebar2:slidebar
	liqcell *slidebar2 = liqcell_quickcreatevis("slidebar2", "slidebar", 182, 250, 524, 64);
	liqcell_child_append(  self, slidebar2);
	//############################# slidebar3:slidebar
	liqcell *slidebar3 = liqcell_quickcreatevis("slidebar3", "slidebar", 182, 328, 524, 64);
	liqcell_child_append(  self, slidebar3);
	//############################# cmdsave:label
	liqcell *cmdsave = liqcell_quickcreatevis("cmdsave", "label", 586, 420, 198, 60);
	liqcell_setfont(	cmdsave, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsave, "reset" );
	//liqcell_propsets(  cmdsave, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  cmdsave, "backcolor", "rgb(0,0,128)" );
	//liqcell_propsets(  cmdsave, "bordercolor", "rgb(200,100,100)" );	
	//liqcell_propseti(  cmdsave, "textalign", 2 );
	
	
		liqcell_propsets(  cmdsave, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  knob, "backcolor", "rgb(0,0,128)" );
		//liqcell_propsets(  knob, "bordercolor", "rgb(200,100,100)" );
		liqcell_propseti(  cmdsave, "textalign", 2 );
		liqcell_propseti(  cmdsave, "textaligny", 2 );
		liqcell_propsets(  cmdsave, "imagefilename",  "/usr/share/liqbase/onedotzero/media/button_back.png" );
		liqcell_propseti(  cmdsave,  "lockaspect",  0 );

	
	liqcell_handleradd_withcontext(cmdsave, "click", cmdsave_click, self );
	liqcell_child_append(  self, cmdsave);
	//############################# label4:label
	liqcell *label4 = liqcell_quickcreatevis("label4", "label", 62, 342, 100, 36);
	liqcell_setfont(	label4, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label4, "size" );
	liqcell_propsets(  label4, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label4, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label4, "textalign", 0 );
	liqcell_child_append(  self, label4);
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 26, 100, 762, 40);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label3, "Watch the projector to see the results." );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,0)" );
	//liqcell_propsets(  label3, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label3, "textalign", 0 );
	liqcell_child_append(  self, label3);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 26, 56, 762, 40);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label2, "Use your finger to change the slide bars." );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,0)" );
	//liqcell_propsets(  label2, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label2, "textalign", 0 );
	liqcell_child_append(  self, label2);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 62, 264, 100, 36);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label1, "down" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label1, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_child_append(  self, label1);
	//############################# onetouchslide:label
	liqcell *onetouchslide = liqcell_quickcreatevis("onetouchslide", "label", 64, 184, 100, 40);
	liqcell_setfont(	onetouchslide, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(onetouchslide, "across" );
	liqcell_propsets(  onetouchslide, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  onetouchslide, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  onetouchslide, "textalign", 0 );
	liqcell_child_append(  self, onetouchslide);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 46);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "onedotzero :: touch" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", onetouchslide_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", onetouchslide_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", onetouchslide_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", onetouchslide_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", onetouchslide_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", onetouchslide_mouse,self );
	liqcell_handleradd_withcontext(self, "click", onetouchslide_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", onetouchslide_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", onetouchslide_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", onetouchslide_dialog_close ,self);


	liqapp_log("app codepath = '%s'",app.codepath);
	char fnbuf[FILENAME_MAX];  snprintf(fnbuf,sizeof(fnbuf),"%s/onedotzero/media/motion_blur.png",app.codepath);
	liqcell_propsets( self ,  "imagefilename", fnbuf );
	liqcell_propseti( self ,  "lockaspect", 0 );
	liqcell_propsets( self ,  "imagefloat", "0,0,0,0" );	// a bit of magic if it works..


	slidebar_setvalue( slidebar1, 50 );
	slidebar_setvalue( slidebar2, 50 );
	slidebar_setvalue( slidebar3, 50 );

	return self;
}

