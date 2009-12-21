// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### sheepdog_leveldesign :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * sheepdog_leveldesign widget filter, the system is asking you to filter to the specified .
 */	
static int sheepdog_leveldesign_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * sheepdog_leveldesign widget refresh, all params set, present yourself to the user.
 */	
static int sheepdog_leveldesign_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_leveldesign dialog_open - the user zoomed into the dialog
 */	
static int sheepdog_leveldesign_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdog_leveldesign dialog_close - the dialog was closed
 */	
static int sheepdog_leveldesign_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdog_leveldesign widget shown - occurs once per lifetime
 */	
static int sheepdog_leveldesign_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_leveldesign mouse - occurs all the time as you stroke the screen
 */	
static int sheepdog_leveldesign_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_leveldesign click - occurs when a short mouse stroke occured
 */	
static int sheepdog_leveldesign_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_leveldesign keypress - the user pressed a key
 */	
static int sheepdog_leveldesign_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_leveldesign keyrelease - the user released a key
 */	
static int sheepdog_leveldesign_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_leveldesign paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int sheepdog_leveldesign_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * sheepdog_leveldesign dynamic resizing
 */	
static int sheepdog_leveldesign_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *preview = liqcell_child_lookup(self, "preview");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *cmdsetbackground = liqcell_child_lookup(self, "cmdsetbackground");
	liqcell *cmdaddstickers = liqcell_child_lookup(self, "cmdaddstickers");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *cmdaddholes = liqcell_child_lookup(self, "cmdaddholes");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *txttitle = liqcell_child_lookup(self, "txttitle");
	liqcell_setrect_autoscale( preview, 440,206, 308,194, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 396,46, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 594,432, 206,48, sx,sy);
	liqcell_setrect_autoscale( cmdsetbackground, 36,190, 330,48, sx,sy);
	liqcell_setrect_autoscale( cmdaddstickers, 36,246, 330,52, sx,sy);
	liqcell_setrect_autoscale( label3, 438,150, 308,44, sx,sy);
	liqcell_setrect_autoscale( cmdaddholes, 36,308, 330,52, sx,sy);
	liqcell_setrect_autoscale( label1, 28,64, 386,44, sx,sy);
	liqcell_setrect_autoscale( txttitle, 118,62, 664,48, sx,sy);
	return 0;
}

/**	
 * sheepdog_leveldesign.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdog_leveldesign)
{
	return 0;
}
/**	
 * sheepdog_leveldesign.cmdsetbackground clicked
 */	
static int cmdsetbackground_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdog_leveldesign)
{
	return 0;
}
/**	
 * sheepdog_leveldesign.cmdaddstickers clicked
 */	
static int cmdaddstickers_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdog_leveldesign)
{
	return 0;
}
/**	
 * sheepdog_leveldesign.cmdaddholes clicked
 */	
static int cmdaddholes_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdog_leveldesign)
{
	return 0;
}
/**	
 * sheepdog_leveldesign_child_test_seek this function shows how to access members
 */	
	  
static void sheepdog_leveldesign_child_test_seek(liqcell *sheepdog_leveldesign)
{	  
	liqcell *preview = liqcell_child_lookup(sheepdog_leveldesign, "preview");
	liqcell *title = liqcell_child_lookup(sheepdog_leveldesign, "title");
	liqcell *cmdaccept = liqcell_child_lookup(sheepdog_leveldesign, "cmdaccept");
	liqcell *cmdsetbackground = liqcell_child_lookup(sheepdog_leveldesign, "cmdsetbackground");
	liqcell *cmdaddstickers = liqcell_child_lookup(sheepdog_leveldesign, "cmdaddstickers");
	liqcell *label3 = liqcell_child_lookup(sheepdog_leveldesign, "label3");
	liqcell *cmdaddholes = liqcell_child_lookup(sheepdog_leveldesign, "cmdaddholes");
	liqcell *label1 = liqcell_child_lookup(sheepdog_leveldesign, "label1");
	liqcell *txttitle = liqcell_child_lookup(sheepdog_leveldesign, "txttitle");
}	  
/**	
 * create a new sheepdog_leveldesign widget
 */	
liqcell *sheepdog_leveldesign_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdog_leveldesign", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'sheepdog_leveldesign'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# preview:label
	liqcell *preview = liqcell_quickcreatevis("preview", "label", 440, 206, 308, 194);
	liqcell_setfont(	preview, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(preview, "preview goes here, click to test" );
	liqcell_propsets(  preview, "textcolor", "rgb(255,0,0)" );
	liqcell_propsets(  preview, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  preview, "textalign", 2 );
	liqcell_propseti(  preview, "textaligny", 2 );
	liqcell_child_append(  self, preview);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 396, 46);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Level designer" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 594, 432, 206, 48);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "save" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# cmdsetbackground:label
	liqcell *cmdsetbackground = liqcell_quickcreatevis("cmdsetbackground", "label", 36, 190, 330, 48);
	liqcell_setfont(	cmdsetbackground, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdsetbackground, "select background" );
	liqcell_propsets(  cmdsetbackground, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdsetbackground, "backcolor", "xrgb(0,64,64)" );
	liqcell_propseti(  cmdsetbackground, "textalign", 2 );
	liqcell_propseti(  cmdsetbackground, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdsetbackground, "click", cmdsetbackground_click, self );
	liqcell_child_append(  self, cmdsetbackground);
	//############################# cmdaddstickers:label
	liqcell *cmdaddstickers = liqcell_quickcreatevis("cmdaddstickers", "label", 36, 246, 330, 52);
	liqcell_setfont(	cmdaddstickers, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdaddstickers, "add stickers" );
	liqcell_propsets(  cmdaddstickers, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaddstickers, "backcolor", "xrgb(0,64,64)" );
	liqcell_propseti(  cmdaddstickers, "textalign", 2 );
	liqcell_propseti(  cmdaddstickers, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaddstickers, "click", cmdaddstickers_click, self );
	liqcell_child_append(  self, cmdaddstickers);
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 438, 150, 308, 44);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label3, "preview" );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label3, "textalign", 0 );
	liqcell_propseti(  label3, "textaligny", 0 );
	liqcell_child_append(  self, label3);
	//############################# cmdaddholes:label
	liqcell *cmdaddholes = liqcell_quickcreatevis("cmdaddholes", "label", 36, 308, 330, 52);
	liqcell_setfont(	cmdaddholes, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdaddholes, "add pens" );
	liqcell_propsets(  cmdaddholes, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaddholes, "backcolor", "xrgb(0,64,64)" );
	liqcell_propseti(  cmdaddholes, "textalign", 2 );
	liqcell_propseti(  cmdaddholes, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaddholes, "click", cmdaddholes_click, self );
	liqcell_child_append(  self, cmdaddholes);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 28, 64, 386, 44);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label1, "title" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_propseti(  label1, "textaligny", 0 );
	liqcell_child_append(  self, label1);
	//############################# txttitle:textbox
	liqcell *txttitle = liqcell_quickcreatevis("txttitle", "textbox", 118, 62, 664, 48);
	liqcell_setfont(	txttitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_setcaption(txttitle, "Text1" );
	liqcell_propsets(  txttitle, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  txttitle, "backcolor", "rgb(0,0,64)" );
	liqcell_propsets(  txttitle, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  txttitle, "textalign", 0 );
	liqcell_propseti(  txttitle, "textaligny", 0 );
	liqcell_child_append(  self, txttitle);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/sheepdog/media/sheepdog_leveldesign_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", sheepdog_leveldesign_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", sheepdog_leveldesign_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", sheepdog_leveldesign_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", sheepdog_leveldesign_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", sheepdog_leveldesign_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", sheepdog_leveldesign_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", sheepdog_leveldesign_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", sheepdog_leveldesign_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", sheepdog_leveldesign_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", sheepdog_leveldesign_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", sheepdog_leveldesign_dialog_close ,self);
	return self;
}

