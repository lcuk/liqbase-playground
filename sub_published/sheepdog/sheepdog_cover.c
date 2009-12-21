// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### sheepdog_cover :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * sheepdog_cover widget filter, the system is asking you to filter to the specified .
 */	
static int sheepdog_cover_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * sheepdog_cover widget refresh, all params set, present yourself to the user.
 */	
static int sheepdog_cover_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_cover dialog_open - the user zoomed into the dialog
 */	
static int sheepdog_cover_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdog_cover dialog_close - the dialog was closed
 */	
static int sheepdog_cover_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdog_cover widget shown - occurs once per lifetime
 */	
static int sheepdog_cover_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_cover mouse - occurs all the time as you stroke the screen
 */	
static int sheepdog_cover_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_cover click - occurs when a short mouse stroke occured
 */	
static int sheepdog_cover_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_cover keypress - the user pressed a key
 */	
static int sheepdog_cover_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_cover keyrelease - the user released a key
 */	
static int sheepdog_cover_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_cover paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int sheepdog_cover_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * sheepdog_cover dynamic resizing
 */	
static int sheepdog_cover_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *appname = liqcell_child_lookup(self, "appname");
	liqcell *author = liqcell_child_lookup(self, "author");
	liqcell *slidetext3 = liqcell_child_lookup(self, "slidetext3");
	liqcell *slidetext2 = liqcell_child_lookup(self, "slidetext2");
	liqcell *slidetext1 = liqcell_child_lookup(self, "slidetext1");
	liqcell *preview = liqcell_child_lookup(self, "preview");
	liqcell *cmdplay = liqcell_child_lookup(self, "cmdplay");
	liqcell *cmdoptions = liqcell_child_lookup(self, "cmdoptions");
	liqcell_setrect_autoscale( cmdoptions, 98,370, 246,62, sx,sy);
	liqcell_setrect_autoscale( cmdplay, 442,370, 246,62, sx,sy);
	liqcell_setrect_autoscale( label3, 14,446, 764,30, sx,sy);
	liqcell_setrect_autoscale( appname, 18,0, 644,80, sx,sy);
	liqcell_setrect_autoscale( author, 24,84, 764,48, sx,sy);
	liqcell_setrect_autoscale( slidetext3, 26,308, 442,30, sx,sy);
	liqcell_setrect_autoscale( slidetext2, 26,266, 442,30, sx,sy);
	liqcell_setrect_autoscale( slidetext1, 26,226, 442,30, sx,sy);
	liqcell_setrect_autoscale( preview, 416,166, 294,184, sx,sy);
	return 0;
}

/**	
 * sheepdog_cover.cmdoptions clicked
 */	
static int cmdoptions_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdog_cover)
{
	return 0;
}
/**	
 * sheepdog_cover.cmdplay clicked
 */	
static int cmdplay_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdog_cover)
{

		liqcell *dayview = liqcell_quickcreatevis("flow", "sheepdog.sheepdog_flow", 0,0,-1,-1);
		liqcell_easyrun(dayview);
		liqcell_release(dayview);

	return 0;
}
/**	
 * sheepdog_cover_child_test_seek this function shows how to access members
 */	
	  
static void sheepdog_cover_child_test_seek(liqcell *sheepdog_cover)
{	  
	liqcell *label3 = liqcell_child_lookup(sheepdog_cover, "label3");
	liqcell *appname = liqcell_child_lookup(sheepdog_cover, "appname");
	liqcell *author = liqcell_child_lookup(sheepdog_cover, "author");
	liqcell *slidetext3 = liqcell_child_lookup(sheepdog_cover, "slidetext3");
	liqcell *slidetext2 = liqcell_child_lookup(sheepdog_cover, "slidetext2");
	liqcell *slidetext1 = liqcell_child_lookup(sheepdog_cover, "slidetext1");
	liqcell *preview = liqcell_child_lookup(sheepdog_cover, "preview");
	liqcell *cmdplay = liqcell_child_lookup(sheepdog_cover, "cmdplay");
	liqcell *cmdoptions = liqcell_child_lookup(sheepdog_cover, "cmdoptions");
}	  
/**	
 * create a new sheepdog_cover widget
 */	
liqcell *sheepdog_cover_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdog_cover", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'sheepdog_cover'"); return NULL;  } 
	
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
	//############################# appname:label
	liqcell *appname = liqcell_quickcreatevis("appname", "label", 18, 0, 644, 80);
	liqcell_setfont(	appname, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (58), 0) );
	liqcell_setcaption(appname, "sheepdog" );
	liqcell_propsets(  appname, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  appname, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  appname, "textalign", 0 );
	liqcell_propseti(  appname, "textaligny", 0 );
	liqcell_child_append(  self, appname);
	//############################# author:label
	liqcell *author = liqcell_quickcreatevis("author", "label", 24, 84, 764, 48);
	liqcell_setfont(	author, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(author, "by Gary Birkett and Kathy Smith" );
	liqcell_propsets(  author, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  author, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  author, "textalign", 0 );
	liqcell_propseti(  author, "textaligny", 0 );
	liqcell_child_append(  self, author);
	//############################# slidetext3:label
	liqcell *slidetext3 = liqcell_quickcreatevis("slidetext3", "label", 26, 308, 442, 30);
	liqcell_setfont(	slidetext3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext3, "up against the clock" );
	liqcell_propsets(  slidetext3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext3, "textalign", 0 );
	liqcell_propseti(  slidetext3, "textaligny", 0 );
	liqcell_child_append(  self, slidetext3);
	//############################# slidetext2:label
	liqcell *slidetext2 = liqcell_quickcreatevis("slidetext2", "label", 26, 266, 442, 30);
	liqcell_setfont(	slidetext2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext2, "get all the sheep into the pen" );
	liqcell_propsets(  slidetext2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext2, "textalign", 0 );
	liqcell_propseti(  slidetext2, "textaligny", 0 );
	liqcell_child_append(  self, slidetext2);
	//############################# slidetext1:label
	liqcell *slidetext1 = liqcell_quickcreatevis("slidetext1", "label", 26, 226, 442, 30);
	liqcell_setfont(	slidetext1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext1, "simple accelerometer base game" );
	liqcell_propsets(  slidetext1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext1, "textalign", 0 );
	liqcell_propseti(  slidetext1, "textaligny", 0 );
	liqcell_child_append(  self, slidetext1);
	//############################# preview:image
	liqcell *preview = liqcell_quickcreatevis("preview", "image", 416, 166, 294, 184);
	liqcell_propsets(  preview, "bordercolor", "rgb(255,255,255)" );
	liqcell_child_append(  self, preview);
	//############################# cmdplay:label
	liqcell *cmdplay = liqcell_quickcreatevis("cmdplay", "label", 442, 370, 246, 62);
	liqcell_setfont(	cmdplay, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (43), 0) );
	liqcell_setcaption(cmdplay, "Play" );
	liqcell_propsets(  cmdplay, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdplay, "backcolor", "xrgb(0,64,0)" );
	liqcell_propseti(  cmdplay, "textalign", 2 );
	liqcell_propseti(  cmdplay, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdplay, "click", cmdplay_click, self );
	liqcell_child_append(  self, cmdplay);
	//############################# cmdoptions:label
	liqcell *cmdoptions = liqcell_quickcreatevis("cmdoptions", "label", 98, 370, 246, 62);
	liqcell_setfont(	cmdoptions, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (43), 0) );
	liqcell_setcaption(cmdoptions, "Options" );
	liqcell_propsets(  cmdoptions, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdoptions, "backcolor", "xrgb(0,64,64)" );
	liqcell_propseti(  cmdoptions, "textalign", 2 );
	liqcell_propseti(  cmdoptions, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdoptions, "click", cmdoptions_click, self );
	liqcell_child_append(  self, cmdoptions);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/sheepdog/media/sheepdog_cover_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", sheepdog_cover_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", sheepdog_cover_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", sheepdog_cover_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", sheepdog_cover_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", sheepdog_cover_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", sheepdog_cover_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", sheepdog_cover_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", sheepdog_cover_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", sheepdog_cover_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", sheepdog_cover_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", sheepdog_cover_dialog_close ,self);
	return self;
}

