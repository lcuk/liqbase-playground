// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqmic_cover :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqmic_cover widget filter, the system is asking you to filter to the specified .
 */	
static int liqmic_cover_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * liqmic_cover widget refresh, all params set, present yourself to the user.
 */	
static int liqmic_cover_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmic_cover dialog_open - the user zoomed into the dialog
 */	
static int liqmic_cover_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqmic_cover dialog_close - the dialog was closed
 */	
static int liqmic_cover_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqmic_cover widget shown - occurs once per lifetime
 */	
static int liqmic_cover_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmic_cover mouse - occurs all the time as you stroke the screen
 */	
static int liqmic_cover_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmic_cover click - occurs when a short mouse stroke occured
 */	
static int liqmic_cover_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmic_cover keypress - the user pressed a key
 */	
static int liqmic_cover_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmic_cover keyrelease - the user released a key
 */	
static int liqmic_cover_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmic_cover paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqmic_cover_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqmic_cover dynamic resizing
 */	
static int liqmic_cover_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *lbltitle = liqcell_child_lookup(self, "lbltitle");
	liqcell *author = liqcell_child_lookup(self, "author");
	liqcell *slidetext1 = liqcell_child_lookup(self, "slidetext1");
	liqcell *slidetext2 = liqcell_child_lookup(self, "slidetext2");
	liqcell *slidetext3 = liqcell_child_lookup(self, "slidetext3");
	liqcell *cmdtest1 = liqcell_child_lookup(self, "cmdtest1");
	liqcell *cmdusesmoothing = liqcell_child_lookup(self, "cmdusesmoothing");
	liqcell_setrect_autoscale( label3, 14,446, 764,30, sx,sy);
	liqcell_setrect_autoscale( lbltitle, 18,0, 644,80, sx,sy);
	liqcell_setrect_autoscale( author, 24,84, 696,48, sx,sy);
	liqcell_setrect_autoscale( slidetext1, 26,224, 442,30, sx,sy);
	liqcell_setrect_autoscale( slidetext2, 26,264, 442,30, sx,sy);
	liqcell_setrect_autoscale( slidetext3, 26,306, 442,30, sx,sy);
	liqcell_setrect_autoscale( cmdtest1, 446,146, 326,98, sx,sy);
	liqcell_setrect_autoscale( cmdusesmoothing, 446,372, 330,52, sx,sy);
	return 0;
}

/**	
 * liqmic_cover.cmdtest1 clicked
 */	
static int cmdtest1_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqmic_cover)
{
	liqcell *c = liqcell_quickcreatevis("item","liqmic.liqmic_run",0,0,-1,-1);
	args->newdialogtoopen= c ;
	//liqcell_easyrun(c);
	//liqcell_release(c);
	return 1;
}
/**	
 * liqmic_cover.cmdusesmoothing clicked
 */	
static int cmdusesmoothing_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqmic_cover)
{
		// for now, smoothing is assumed
	liqcell *cmdusesmoothing = liqcell_child_lookup(liqmic_cover, "cmdusesmoothing");
	char *cap = liqcell_getcaption(cmdusesmoothing);
	if( cap && *cap == 'U' )
	{
		// using smoothing
		//liqcell_setfont(	cmdusesmoothing, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(cmdusesmoothing, "Not using Smoothing" );
		liqcell_propsets(  cmdusesmoothing, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  cmdusesmoothing, "backcolor", "xrgb(64,0,0)" );
		
		liqapp_pref_setvalue("liqmic_usesmoothing","no");
		liqapp_prefs_save();
	}
	else
	{
		// Not using smoothing
		//liqcell_setfont(	cmdusesmoothing, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(cmdusesmoothing, "Using Smoothing" );
		liqcell_propsets(  cmdusesmoothing, "textcolor", "rgb(255,255,0)" );
		liqcell_propsets(  cmdusesmoothing, "backcolor", "xrgb(0,64,64)" );
		
		liqapp_pref_setvalue("liqmic_usesmoothing","yes");
		liqapp_prefs_save();
	}


	return 0;
}
/**	
 * liqmic_cover_child_test_seek this function shows how to access members
 */	
	  
static void liqmic_cover_child_test_seek(liqcell *liqmic_cover)
{	  
	liqcell *label3 = liqcell_child_lookup(liqmic_cover, "label3");
	liqcell *lbltitle = liqcell_child_lookup(liqmic_cover, "lbltitle");
	liqcell *author = liqcell_child_lookup(liqmic_cover, "author");
	liqcell *slidetext1 = liqcell_child_lookup(liqmic_cover, "slidetext1");
	liqcell *slidetext2 = liqcell_child_lookup(liqmic_cover, "slidetext2");
	liqcell *slidetext3 = liqcell_child_lookup(liqmic_cover, "slidetext3");
	liqcell *cmdtest1 = liqcell_child_lookup(liqmic_cover, "cmdtest1");
	liqcell *cmdusesmoothing = liqcell_child_lookup(liqmic_cover, "cmdusesmoothing");
}	  
/**	
 * create a new liqmic_cover widget
 */	
liqcell *liqmic_cover_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqmic_cover", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqmic_cover'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 14, 446, 764, 30);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label3, "open source comes from the heart.  please donate to all projects." );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label3, "textalign", 2 );
	liqcell_propseti(  label3, "textaligny", 2 );
	liqcell_child_append(  self, label3);
	//############################# lbltitle:label
	liqcell *lbltitle = liqcell_quickcreatevis("lbltitle", "label", 18, 0, 644, 80);
	liqcell_setfont(	lbltitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (58), 0) );
	liqcell_setcaption(lbltitle, "liqmic" );
	liqcell_propsets(  lbltitle, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  lbltitle, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lbltitle, "textalign", 0 );
	liqcell_propseti(  lbltitle, "textaligny", 0 );
	liqcell_child_append(  self, lbltitle);
	//############################# author:label
	liqcell *author = liqcell_quickcreatevis("author", "label", 24, 84, 696, 48);
	liqcell_setfont(	author, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(author, "written by Gary Birkett and Ian Molton." );
	liqcell_propsets(  author, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  author, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  author, "textalign", 0 );
	liqcell_propseti(  author, "textaligny", 0 );
	liqcell_child_append(  self, author);
	//############################# slidetext1:label
	liqcell *slidetext1 = liqcell_quickcreatevis("slidetext1", "label", 26, 224, 442, 30);
	liqcell_setfont(	slidetext1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext1, "quick recording waveform from the mic" );
	liqcell_propsets(  slidetext1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext1, "textalign", 0 );
	liqcell_propseti(  slidetext1, "textaligny", 0 );
	liqcell_child_append(  self, slidetext1);
	//############################# slidetext2:label
	liqcell *slidetext2 = liqcell_quickcreatevis("slidetext2", "label", 26, 264, 442, 30);
	liqcell_setfont(	slidetext2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext2, "25fps super smooth feedback" );
	liqcell_propsets(  slidetext2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext2, "textalign", 0 );
	liqcell_propseti(  slidetext2, "textaligny", 0 );
	liqcell_child_append(  self, slidetext2);
	//############################# slidetext3:label
	liqcell *slidetext3 = liqcell_quickcreatevis("slidetext3", "label", 26, 306, 442, 30);
	liqcell_setfont(	slidetext3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext3, "human oriented data points" );
	liqcell_propsets(  slidetext3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext3, "textalign", 0 );
	liqcell_propseti(  slidetext3, "textaligny", 0 );
	liqcell_child_append(  self, slidetext3);
	//############################# cmdtest1:label
	liqcell *cmdtest1 = liqcell_quickcreatevis("cmdtest1", "label", 446, 146, 326, 98);
	liqcell_setfont(	cmdtest1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdtest1, "run" );
	liqcell_propsets(  cmdtest1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdtest1, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdtest1, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdtest1, "textalign", 2 );
	liqcell_propseti(  cmdtest1, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdtest1, "click", cmdtest1_click, self );
	liqcell_child_append(  self, cmdtest1);
	//############################# cmdusesmoothing:checkbox
	liqcell *cmdusesmoothing = liqcell_quickcreatevis("cmdusesmoothing", "checkbox", 446, 372, 330, 52);
	liqcell_setfont(	cmdusesmoothing, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdusesmoothing, "Use Smoothing" );
	liqcell_propsets(  cmdusesmoothing, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdusesmoothing, "backcolor", "xrgb(0,64,64)" );
	liqcell_propseti(  cmdusesmoothing, "textalign", 0 );
	liqcell_propseti(  cmdusesmoothing, "textaligny", 0 );
	liqcell_handleradd_withcontext(cmdusesmoothing, "click", cmdusesmoothing_click, self );
	liqcell_child_append(  self, cmdusesmoothing);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	
	
	char *prefsmooth = liqapp_pref_getvalue_def("liqmic_usesmoothing","yes");
	
	if( (prefsmooth && *prefsmooth == 'y') )
	{
		liqcell_setcaption(cmdusesmoothing, "Using Smoothing" );
		liqcell_propsets(  cmdusesmoothing, "textcolor", "rgb(255,255,0)" );
		liqcell_propsets(  cmdusesmoothing, "backcolor", "xrgb(0,64,64)" );
		
	}
	else
	{
		liqcell_setcaption(cmdusesmoothing, "Not using Smoothing" );
		liqcell_propsets(  cmdusesmoothing, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  cmdusesmoothing, "backcolor", "xrgb(64,0,0)" );
				
	}

	
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/liqmic/media/liqmic_cover_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", liqmic_cover_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", liqmic_cover_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqmic_cover_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", liqmic_cover_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqmic_cover_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqmic_cover_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", liqmic_cover_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", liqmic_cover_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqmic_cover_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqmic_cover_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqmic_cover_dialog_close ,self);
	return self;
}

