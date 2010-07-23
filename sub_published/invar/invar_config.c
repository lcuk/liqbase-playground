// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### invar_config :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * invar_config widget filter, the system is asking you to filter to the specified .
 */	
static int invar_config_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * invar_config widget refresh, all params set, present yourself to the user.
 */	
static int invar_config_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	liqcell *imgsurface = liqcell_child_lookup(self, "imgsurface");
    char *t =  liqapp_pref_getvalue_def("invar_surface", "/usr/share/liqbase/invar/media/invar_config.imgsurface.png");
    if(t && *t)
		liqcell_propsets(  imgsurface, "imagefilename", t );
	else
		liqcell_propsets(  imgsurface, "imagefilename", NULL );
	liqcell_setimage(imgsurface,NULL);
	
	return 0;
}
/**	
 * invar_config dialog_open - the user zoomed into the dialog
 */	
static int invar_config_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * invar_config dialog_close - the dialog was closed
 */	
static int invar_config_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * invar_config widget shown - occurs once per lifetime
 */	
static int invar_config_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * invar_config mouse - occurs all the time as you stroke the screen
 */	
static int invar_config_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_config click - occurs when a short mouse stroke occured
 */	
static int invar_config_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_config keypress - the user pressed a key
 */	
static int invar_config_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_config keyrelease - the user released a key
 */	
static int invar_config_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_config paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int invar_config_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * invar_config dynamic resizing
 */	
static int invar_config_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *cmdsave = liqcell_child_lookup(self, "cmdsave");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *liqbaseusernametitle = liqcell_child_lookup(self, "liqbaseusernametitle");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *cmdcalibrate = liqcell_child_lookup(self, "cmdcalibrate");
	liqcell *imgsurface = liqcell_child_lookup(self, "imgsurface");
	liqcell *cmdsurfaceselect = liqcell_child_lookup(self, "cmdsurfaceselect");
	liqcell *cmdsurfacereset = liqcell_child_lookup(self, "cmdsurfacereset");
	liqcell_setrect_autoscale( cmdsave, 574,418, 226,62, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
	liqcell_setrect_autoscale( liqbaseusernametitle, 14,116, 228,32, sx,sy);
	liqcell_setrect_autoscale( label2, 0,56, 800,30, sx,sy);
	liqcell_setrect_autoscale( cmdcalibrate, 228,320, 552,62, sx,sy);
	liqcell_setrect_autoscale( imgsurface, 292,112, 210,150, sx,sy);
	liqcell_setrect_autoscale( cmdsurfaceselect, 566,114, 226,62, sx,sy);
	liqcell_setrect_autoscale( cmdsurfacereset, 566,198, 226,62, sx,sy);
	return 0;
}

/**	
 * invar_config.cmdsave clicked
 */	
static int cmdsave_click(liqcell *self,liqcellclickeventargs *args, liqcell *invar_config)
{
	return 0;
}
/**	
 * invar_config.cmdcalibrate clicked
 */	
static int cmdcalibrate_click(liqcell *self,liqcellclickeventargs *args, liqcell *invar_config)
{
	return 0;
}
/**	
 * invar_config.cmdsurfaceselect clicked
 */	
static int cmdsurfaceselect_click(liqcell *self,liqcellclickeventargs *args, liqcell *invar_config)
{
	
	 liqcell *dialog = liqcell_quickcreatevis("imagepicker", "dialog_selectimage", 0,0, -1,-1);
	 liqcell_easyrun(dialog);
	 
	 
            // process dialog results      
            char *selfn=liqcell_propgets(  dialog, "imagefilenameselected",NULL );
            if( selfn && *selfn )
            {
                //
				liqapp_pref_setvalue("invar_surface", selfn );
				liqapp_prefs_save();
			
				// refresh the actual contents..
				liqcell_handlerrun(invar_config,"refresh",NULL);                
            }
 


	 liqcell_release(dialog);

	return 0;
}
/**	
 * invar_config.cmdsurfacereset clicked
 */	
static int cmdsurfacereset_click(liqcell *self,liqcellclickeventargs *args, liqcell *invar_config)
{
	return 0;
}
/**	
 * invar_config_child_test_seek this function shows how to access members
 */	
	  
static void invar_config_child_test_seek(liqcell *invar_config)
{	  
	liqcell *cmdsave = liqcell_child_lookup(invar_config, "cmdsave");
	liqcell *title = liqcell_child_lookup(invar_config, "title");
	liqcell *liqbaseusernametitle = liqcell_child_lookup(invar_config, "liqbaseusernametitle");
	liqcell *label2 = liqcell_child_lookup(invar_config, "label2");
	liqcell *cmdcalibrate = liqcell_child_lookup(invar_config, "cmdcalibrate");
	liqcell *imgsurface = liqcell_child_lookup(invar_config, "imgsurface");
	liqcell *cmdsurfaceselect = liqcell_child_lookup(invar_config, "cmdsurfaceselect");
	liqcell *cmdsurfacereset = liqcell_child_lookup(invar_config, "cmdsurfacereset");
}	  
/**	
 * create a new invar_config widget
 */	
liqcell *invar_config_create()
{
	liqcell *self = liqcell_quickcreatewidget("invar_config", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'invar_config'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# cmdsave:label
	liqcell *cmdsave = liqcell_quickcreatevis("cmdsave", "label", 574, 418, 226, 62);
	liqcell_setfont(	cmdsave, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsave, "Save" );
	liqcell_propsets(  cmdsave, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdsave, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdsave, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdsave, "textalign", 2 );
	liqcell_propseti(  cmdsave, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdsave, "click", (void*)cmdsave_click, self );
	liqcell_child_append(  self, cmdsave);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "invar :: configure options" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(64,64,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# liqbaseusernametitle:label
	liqcell *liqbaseusernametitle = liqcell_quickcreatevis("liqbaseusernametitle", "label", 14, 116, 228, 32);
	liqcell_setfont(	liqbaseusernametitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(liqbaseusernametitle, "Display surface" );
	liqcell_propsets(  liqbaseusernametitle, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  liqbaseusernametitle, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  liqbaseusernametitle, "textalign", 0 );
	liqcell_propseti(  liqbaseusernametitle, "textaligny", 0 );
	liqcell_child_append(  self, liqbaseusernametitle);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 0, 56, 800, 30);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label2, "The Inverse AR system needs calibrating" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label2, "backcolor", "rgb(0,64,0)" );
	liqcell_propseti(  label2, "textalign", 2 );
	liqcell_propseti(  label2, "textaligny", 2 );
	liqcell_child_append(  self, label2);
	//############################# cmdcalibrate:label
	liqcell *cmdcalibrate = liqcell_quickcreatevis("cmdcalibrate", "label", 228, 320, 552, 62);
	liqcell_setfont(	cmdcalibrate, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdcalibrate, "Calibration tool" );
	liqcell_propsets(  cmdcalibrate, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdcalibrate, "backcolor", "xrgb(0,64,64)" );
	liqcell_propsets(  cmdcalibrate, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdcalibrate, "textalign", 2 );
	liqcell_propseti(  cmdcalibrate, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdcalibrate, "click", (void*)cmdcalibrate_click, self );
	liqcell_child_append(  self, cmdcalibrate);
	//############################# imgsurface:image
	liqcell *imgsurface = liqcell_quickcreatevis("imgsurface", "image", 292, 112, 210, 150);
	liqcell_propsets(  imgsurface, "imagefilename", "/usr/share/liqbase/invar/media/invar_config.imgsurface.png" );
	liqcell_propsets(  imgsurface, "bordercolor", "rgb(255,255,255)" );
	liqcell_child_append(  self, imgsurface);
	//############################# cmdsurfaceselect:label
	liqcell *cmdsurfaceselect = liqcell_quickcreatevis("cmdsurfaceselect", "label", 566, 114, 226, 62);
	liqcell_setfont(	cmdsurfaceselect, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsurfaceselect, "Select" );
	liqcell_propsets(  cmdsurfaceselect, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdsurfaceselect, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdsurfaceselect, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdsurfaceselect, "textalign", 2 );
	liqcell_propseti(  cmdsurfaceselect, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdsurfaceselect, "click", (void*)cmdsurfaceselect_click, self );
	liqcell_child_append(  self, cmdsurfaceselect);
	//############################# cmdsurfacereset:label
	liqcell *cmdsurfacereset = liqcell_quickcreatevis("cmdsurfacereset", "label", 566, 198, 226, 62);
	liqcell_setfont(	cmdsurfacereset, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsurfacereset, "Reset" );
	liqcell_propsets(  cmdsurfacereset, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdsurfacereset, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdsurfacereset, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdsurfacereset, "textalign", 2 );
	liqcell_propseti(  cmdsurfacereset, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdsurfacereset, "click", (void*)cmdsurfacereset_click, self );
	liqcell_child_append(  self, cmdsurfacereset);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/invar/media/invar_config_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter",		 (void*)invar_config_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh",		(void*)invar_config_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown",		  (void*)invar_config_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize",	  (void*)invar_config_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress",	(void*)invar_config_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", (void*)invar_config_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse",		(void*)invar_config_mouse,self );
	//liqcell_handleradd_withcontext(self, "click",		(void*)invar_config_click ,self);
	//liqcell_handleradd_withcontext(self, "paint",		(void*)invar_config_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open",  (void*)invar_config_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", (void*)invar_config_dialog_close ,self);
	
	liqcell_handlerrun(self,"refresh",NULL);
	
	return self;
}

