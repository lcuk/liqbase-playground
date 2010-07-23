// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### invar_calibrate :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * invar_calibrate widget filter, the system is asking you to filter to the specified .
 */	
static int invar_calibrate_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
{
	// system is indicating the user has typed into the search box
	// you are expected to filter your content based upon this searchterm.
	// show or hide details and rearrange contents to apply this filter.
	char *searchterm = NULL;
	args->resultoutof=0;  // total number of searchable contents
	args->resultshown=0;  // count of options remaining after filtering.
	searchterm = args->searchterm;
	if(searchterm && *searchterm)
	{
		 // check the name property
		 args->resultoutof++;
		 if( stristr(self->name,searchterm) != NULL )
		 {
			  args->resultshown++;
		 }
		 // check the classname property
		 args->resultoutof++;
		 if( stristr(self->classname,searchterm) != NULL )
		 {
			  args->resultshown++;
		 }
		 // check any other properties or children and increment counters
		 // filter out list items recursively
	}
	return 0;
}
/**	
 * invar_calibrate widget refresh, all params set, present yourself to the user.
 */	
static int invar_calibrate_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * invar_calibrate dialog_open - the user zoomed into the dialog
 */	
static int invar_calibrate_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * invar_calibrate dialog_close - the dialog was closed
 */	
static int invar_calibrate_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * invar_calibrate widget shown - occurs once per lifetime
 */	
static int invar_calibrate_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * invar_calibrate mouse - occurs all the time as you stroke the screen
 */	
static int invar_calibrate_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_calibrate click - occurs when a short mouse stroke occured
 */	
static int invar_calibrate_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_calibrate keypress - the user pressed a key
 */	
static int invar_calibrate_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_calibrate keyrelease - the user released a key
 */	
static int invar_calibrate_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_calibrate paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int invar_calibrate_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * invar_calibrate dynamic resizing
 */	
static int invar_calibrate_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *cmdbottomleft = liqcell_child_lookup(self, "cmdbottomleft");
	liqcell *cmdsave = liqcell_child_lookup(self, "cmdsave");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdbottomright = liqcell_child_lookup(self, "cmdbottomright");
	liqcell *cmdtopleft = liqcell_child_lookup(self, "cmdtopleft");
	liqcell *cmdtopright = liqcell_child_lookup(self, "cmdtopright");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *lblbackground = liqcell_child_lookup(self, "lblbackground");
	liqcell_setrect_autoscale( label1, 142,430, 422,36, sx,sy);
	liqcell_setrect_autoscale( label3, 0,86, 800,30, sx,sy);
	liqcell_setrect_autoscale( cmdbottomleft, 102,334, 144,64, sx,sy);
	liqcell_setrect_autoscale( cmdsave, 574,418, 226,62, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
	liqcell_setrect_autoscale( cmdbottomright, 536,334, 144,64, sx,sy);
	liqcell_setrect_autoscale( cmdtopleft, 102,134, 144,64, sx,sy);
	liqcell_setrect_autoscale( cmdtopright, 536,134, 144,64, sx,sy);
	liqcell_setrect_autoscale( label2, 0,56, 800,30, sx,sy);
	liqcell_setrect_autoscale( lblbackground, 98,130, 586,272, sx,sy);
	return 0;
}

/**	
 * invar_calibrate.cmdbottomleft clicked
 */	
static int cmdbottomleft_click(liqcell *self,liqcellclickeventargs *args, liqcell *invar_calibrate)
{
	return 0;
}
/**	
 * invar_calibrate.cmdsave clicked
 */	
static int cmdsave_click(liqcell *self,liqcellclickeventargs *args, liqcell *invar_calibrate)
{
	return 0;
}
/**	
 * invar_calibrate.cmdbottomright clicked
 */	
static int cmdbottomright_click(liqcell *self,liqcellclickeventargs *args, liqcell *invar_calibrate)
{
	return 0;
}
/**	
 * invar_calibrate.cmdtopleft clicked
 */	
static int cmdtopleft_click(liqcell *self,liqcellclickeventargs *args, liqcell *invar_calibrate)
{
	return 0;
}
/**	
 * invar_calibrate.cmdtopright clicked
 */	
static int cmdtopright_click(liqcell *self,liqcellclickeventargs *args, liqcell *invar_calibrate)
{
	return 0;
}
/**	
 * invar_calibrate_child_test_seek this function shows how to access members
 */	
	  
static void invar_calibrate_child_test_seek(liqcell *invar_calibrate)
{	  
	liqcell *label1 = liqcell_child_lookup(invar_calibrate, "label1");
	liqcell *label3 = liqcell_child_lookup(invar_calibrate, "label3");
	liqcell *cmdbottomleft = liqcell_child_lookup(invar_calibrate, "cmdbottomleft");
	liqcell *cmdsave = liqcell_child_lookup(invar_calibrate, "cmdsave");
	liqcell *title = liqcell_child_lookup(invar_calibrate, "title");
	liqcell *cmdbottomright = liqcell_child_lookup(invar_calibrate, "cmdbottomright");
	liqcell *cmdtopleft = liqcell_child_lookup(invar_calibrate, "cmdtopleft");
	liqcell *cmdtopright = liqcell_child_lookup(invar_calibrate, "cmdtopright");
	liqcell *label2 = liqcell_child_lookup(invar_calibrate, "label2");
	liqcell *lblbackground = liqcell_child_lookup(invar_calibrate, "lblbackground");
}	  
/**	
 * create a new invar_calibrate widget
 */	
liqcell *invar_calibrate_create()
{
	liqcell *self = liqcell_quickcreatewidget("invar_calibrate", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'invar_calibrate'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 142, 430, 422, 36);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label1, "Calibration incomplete" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  label1, "backcolor", "rgb(255,0,0)" );
	liqcell_propseti(  label1, "textalign", 2 );
	liqcell_propseti(  label1, "textaligny", 2 );
	liqcell_child_append(  self, label1);
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 0, 86, 800, 30);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label3, "Place device in each corner of the detection range and click corrposponding button" );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label3, "backcolor", "rgb(0,64,0)" );
	liqcell_propseti(  label3, "textalign", 2 );
	liqcell_propseti(  label3, "textaligny", 2 );
	liqcell_child_append(  self, label3);

	//############################# cmdsave:label
	liqcell *cmdsave = liqcell_quickcreatevis("cmdsave", "label", 574, 418, 226, 62);
	liqcell_setfont(	cmdsave, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsave, "Save" );
	liqcell_propsets(  cmdsave, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdsave, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdsave, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdsave, "textalign", 2 );
	liqcell_propseti(  cmdsave, "textaligny", 2 );
	liqcell_setenabled(  cmdsave, 0 );
	liqcell_handleradd_withcontext(cmdsave, "click", (void*)cmdsave_click, self );
	liqcell_child_append(  self, cmdsave);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "invar :: calibration utility" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(64,64,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	
	
	
	//############################# lblbackground:label
	liqcell *lblbackground = liqcell_quickcreatevis("lblbackground", "label", 98, 130, 586, 272);
	liqcell_setfont(	lblbackground, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(lblbackground, "Label4" );
	liqcell_propsets(  lblbackground, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  lblbackground, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  lblbackground, "textalign", 0 );
	liqcell_propseti(  lblbackground, "textaligny", 0 );
	liqcell_child_append(  self, lblbackground);
	//############################# cmdbottomright:label
	liqcell *cmdbottomright = liqcell_quickcreatevis("cmdbottomright", "label", 536, 334, 144, 64);
	liqcell_setfont(	cmdbottomright, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdbottomright, "bottom right" );
	liqcell_propsets(  cmdbottomright, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdbottomright, "backcolor", "xrgb(64,0,0)" );
	liqcell_propseti(  cmdbottomright, "textalign", 2 );
	liqcell_propseti(  cmdbottomright, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdbottomright, "click", (void*)cmdbottomright_click, self );
	liqcell_child_append(  self, cmdbottomright);
	//############################# cmdtopleft:label
	liqcell *cmdtopleft = liqcell_quickcreatevis("cmdtopleft", "label", 102, 134, 144, 64);
	liqcell_setfont(	cmdtopleft, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdtopleft, "top left" );
	liqcell_propsets(  cmdtopleft, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdtopleft, "backcolor", "xrgb(64,0,0)" );
	liqcell_propseti(  cmdtopleft, "textalign", 2 );
	liqcell_propseti(  cmdtopleft, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdtopleft, "click", (void*)cmdtopleft_click, self );
	liqcell_child_append(  self, cmdtopleft);
	//############################# cmdtopright:label
	liqcell *cmdtopright = liqcell_quickcreatevis("cmdtopright", "label", 536, 134, 144, 64);
	liqcell_setfont(	cmdtopright, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdtopright, "top right" );
	liqcell_propsets(  cmdtopright, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdtopright, "backcolor", "xrgb(64,0,0)" );
	liqcell_propseti(  cmdtopright, "textalign", 2 );
	liqcell_propseti(  cmdtopright, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdtopright, "click", (void*)cmdtopright_click, self );
	liqcell_child_append(  self, cmdtopright);
	//############################# cmdbottomleft:label
	liqcell *cmdbottomleft = liqcell_quickcreatevis("cmdbottomleft", "label", 102, 334, 144, 64);
	liqcell_setfont(	cmdbottomleft, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdbottomleft, "bottom left" );
	liqcell_propsets(  cmdbottomleft, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdbottomleft, "backcolor", "xrgb(64,0,0)" );
	liqcell_propseti(  cmdbottomleft, "textalign", 2 );
	liqcell_propseti(  cmdbottomleft, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdbottomleft, "click", (void*)cmdbottomleft_click, self );
	liqcell_child_append(  self, cmdbottomleft);
	
	
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 0, 56, 800, 30);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label2, "Calibration tool for Inverted AR positioning system" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label2, "backcolor", "rgb(0,64,0)" );
	liqcell_propseti(  label2, "textalign", 2 );
	liqcell_propseti(  label2, "textaligny", 2 );
	liqcell_child_append(  self, label2);

	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/invar/media/invar_calibrate_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter",		 (void*)invar_calibrate_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh",		(void*)invar_calibrate_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown",		  (void*)invar_calibrate_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize",	  (void*)invar_calibrate_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress",	(void*)invar_calibrate_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", (void*)invar_calibrate_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse",		(void*)invar_calibrate_mouse,self );
	//liqcell_handleradd_withcontext(self, "click",		(void*)invar_calibrate_click ,self);
	//liqcell_handleradd_withcontext(self, "paint",		(void*)invar_calibrate_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open",  (void*)invar_calibrate_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", (void*)invar_calibrate_dialog_close ,self);
	return self;
}

