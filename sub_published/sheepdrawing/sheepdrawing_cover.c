// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### sheepdrawing_cover :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * sheepdrawing_cover widget filter, the system is asking you to filter to the specified .
 */	
static int sheepdrawing_cover_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * sheepdrawing_cover widget refresh, all params set, present yourself to the user.
 */	
static int sheepdrawing_cover_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_cover dialog_open - the user zoomed into the dialog
 */	
static int sheepdrawing_cover_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdrawing_cover dialog_close - the dialog was closed
 */	
static int sheepdrawing_cover_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdrawing_cover widget shown - occurs once per lifetime
 */	
static int sheepdrawing_cover_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_cover mouse - occurs all the time as you stroke the screen
 */	
static int sheepdrawing_cover_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_cover click - occurs when a short mouse stroke occured
 */	
static int sheepdrawing_cover_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_cover keypress - the user pressed a key
 */	
static int sheepdrawing_cover_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_cover keyrelease - the user released a key
 */	
static int sheepdrawing_cover_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_cover paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int sheepdrawing_cover_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * sheepdrawing_cover dynamic resizing
 */	
static int sheepdrawing_cover_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *author = liqcell_child_lookup(self, "author");
	liqcell *slidetext3 = liqcell_child_lookup(self, "slidetext3");
	liqcell *slidetext2 = liqcell_child_lookup(self, "slidetext2");
	liqcell *slidetext1 = liqcell_child_lookup(self, "slidetext1");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell_setrect_autoscale( label3, 14,446, 764,30, sx,sy);
	liqcell_setrect_autoscale( title, 18,0, 644,80, sx,sy);
	liqcell_setrect_autoscale( author, 24,84, 696,48, sx,sy);
	liqcell_setrect_autoscale( slidetext3, 26,308, 442,30, sx,sy);
	liqcell_setrect_autoscale( slidetext2, 26,266, 442,30, sx,sy);
	liqcell_setrect_autoscale( slidetext1, 26,226, 442,30, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 516,178, 206,68, sx,sy);
	liqcell_setrect_autoscale( label1, 516,288, 206,68, sx,sy);
	return 0;
}

/**	
 * sheepdrawing_cover.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_cover)
{
	return 0;
}
/**	
 * sheepdrawing_cover_child_test_seek this function shows how to access members
 */	
	  
static void sheepdrawing_cover_child_test_seek(liqcell *sheepdrawing_cover)
{	  
	liqcell *label3 = liqcell_child_lookup(sheepdrawing_cover, "label3");
	liqcell *title = liqcell_child_lookup(sheepdrawing_cover, "title");
	liqcell *author = liqcell_child_lookup(sheepdrawing_cover, "author");
	liqcell *slidetext3 = liqcell_child_lookup(sheepdrawing_cover, "slidetext3");
	liqcell *slidetext2 = liqcell_child_lookup(sheepdrawing_cover, "slidetext2");
	liqcell *slidetext1 = liqcell_child_lookup(sheepdrawing_cover, "slidetext1");
	liqcell *cmdaccept = liqcell_child_lookup(sheepdrawing_cover, "cmdaccept");
	liqcell *label1 = liqcell_child_lookup(sheepdrawing_cover, "label1");
}	  
/**	
 * create a new sheepdrawing_cover widget
 */	
liqcell *sheepdrawing_cover_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdrawing_cover", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'sheepdrawing_cover'"); return NULL;  } 
	
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
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 18, 0, 644, 80);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (58), 0) );
	liqcell_setcaption(title, "sheepdrawing" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  title, "backcolor", "xrgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# author:label
	liqcell *author = liqcell_quickcreatevis("author", "label", 24, 84, 696, 48);
	liqcell_setfont(	author, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(author, "written by Gary Birkett." );
	liqcell_propsets(  author, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  author, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  author, "textalign", 0 );
	liqcell_propseti(  author, "textaligny", 0 );
	liqcell_child_append(  self, author);
	//############################# slidetext3:label
	liqcell *slidetext3 = liqcell_quickcreatevis("slidetext3", "label", 26, 308, 442, 30);
	liqcell_setfont(	slidetext3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext3, "enjoy" );
	liqcell_propsets(  slidetext3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext3, "textalign", 0 );
	liqcell_propseti(  slidetext3, "textaligny", 0 );
	liqcell_child_append(  self, slidetext3);
	//############################# slidetext2:label
	liqcell *slidetext2 = liqcell_quickcreatevis("slidetext2", "label", 26, 266, 442, 30);
	liqcell_setfont(	slidetext2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext2, "upload to talk.maemo.org" );
	liqcell_propsets(  slidetext2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext2, "textalign", 0 );
	liqcell_propseti(  slidetext2, "textaligny", 0 );
	liqcell_child_append(  self, slidetext2);
	//############################# slidetext1:label
	liqcell *slidetext1 = liqcell_quickcreatevis("slidetext1", "label", 26, 226, 442, 30);
	liqcell_setfont(	slidetext1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext1, "draw a sheep" );
	liqcell_propsets(  slidetext1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext1, "textalign", 0 );
	liqcell_propseti(  slidetext1, "textaligny", 0 );
	liqcell_child_append(  self, slidetext1);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 516, 178, 206, 68);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "configure" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 516, 288, 206, 68);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(label1, "draw!" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,64,0)" );
	liqcell_propsets(  label1, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  label1, "textalign", 2 );
	liqcell_propseti(  label1, "textaligny", 2 );
	liqcell_child_append(  self, label1);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/sheepdrawing/media/sheepdrawing_cover_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", sheepdrawing_cover_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", sheepdrawing_cover_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", sheepdrawing_cover_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", sheepdrawing_cover_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", sheepdrawing_cover_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", sheepdrawing_cover_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", sheepdrawing_cover_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", sheepdrawing_cover_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", sheepdrawing_cover_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", sheepdrawing_cover_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", sheepdrawing_cover_dialog_close ,self);
	return self;
}

