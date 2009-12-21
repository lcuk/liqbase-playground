// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### sheepdog_levelstickers :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * sheepdog_levelstickers widget filter, the system is asking you to filter to the specified .
 */	
static int sheepdog_levelstickers_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * sheepdog_levelstickers widget refresh, all params set, present yourself to the user.
 */	
static int sheepdog_levelstickers_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelstickers dialog_open - the user zoomed into the dialog
 */	
static int sheepdog_levelstickers_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdog_levelstickers dialog_close - the dialog was closed
 */	
static int sheepdog_levelstickers_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdog_levelstickers widget shown - occurs once per lifetime
 */	
static int sheepdog_levelstickers_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelstickers mouse - occurs all the time as you stroke the screen
 */	
static int sheepdog_levelstickers_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelstickers click - occurs when a short mouse stroke occured
 */	
static int sheepdog_levelstickers_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelstickers keypress - the user pressed a key
 */	
static int sheepdog_levelstickers_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelstickers keyrelease - the user released a key
 */	
static int sheepdog_levelstickers_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelstickers paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int sheepdog_levelstickers_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * sheepdog_levelstickers dynamic resizing
 */	
static int sheepdog_levelstickers_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *cmdall = liqcell_child_lookup(self, "cmdall");
	liqcell *cmdnone = liqcell_child_lookup(self, "cmdnone");
	liqcell_setrect_autoscale( backplane, 4,40, 702,388, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 396,38, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 594,432, 206,48, sx,sy);
	liqcell_setrect_autoscale( cmdall, 714,88, 86,96, sx,sy);
	liqcell_setrect_autoscale( cmdnone, 714,190, 86,116, sx,sy);
	return 0;
}

/**	
 * sheepdog_levelstickers.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdog_levelstickers)
{
	return 0;
}
/**	
 * sheepdog_levelstickers.cmdall clicked
 */	
static int cmdall_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdog_levelstickers)
{
	return 0;
}
/**	
 * sheepdog_levelstickers.cmdnone clicked
 */	
static int cmdnone_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdog_levelstickers)
{
	return 0;
}
/**	
 * sheepdog_levelstickers_child_test_seek this function shows how to access members
 */	
	  
static void sheepdog_levelstickers_child_test_seek(liqcell *sheepdog_levelstickers)
{	  
	liqcell *backplane = liqcell_child_lookup(sheepdog_levelstickers, "backplane");
	liqcell *title = liqcell_child_lookup(sheepdog_levelstickers, "title");
	liqcell *cmdaccept = liqcell_child_lookup(sheepdog_levelstickers, "cmdaccept");
	liqcell *cmdall = liqcell_child_lookup(sheepdog_levelstickers, "cmdall");
	liqcell *cmdnone = liqcell_child_lookup(sheepdog_levelstickers, "cmdnone");
}	  
/**	
 * create a new sheepdog_levelstickers widget
 */	
liqcell *sheepdog_levelstickers_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdog_levelstickers", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'sheepdog_levelstickers'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# backplane:label
	liqcell *backplane = liqcell_quickcreatevis("backplane", "label", 4, 40, 702, 388);
	liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(backplane, "backplane" );
	liqcell_propsets(  backplane, "textcolor", "rgb(255,0,0)" );
	liqcell_propsets(  backplane, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  backplane, "textalign", 2 );
	liqcell_propseti(  backplane, "textaligny", 2 );
	liqcell_child_append(  self, backplane);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 396, 38);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "add level details" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 594, 432, 206, 48);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Save" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# cmdall:label
	liqcell *cmdall = liqcell_quickcreatevis("cmdall", "label", 714, 88, 86, 96);
	liqcell_setfont(	cmdall, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdall, "add" );
	liqcell_propsets(  cmdall, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdall, "backcolor", "xrgb(0,64,64)" );
	liqcell_propsets(  cmdall, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdall, "textalign", 2 );
	liqcell_propseti(  cmdall, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdall, "click", cmdall_click, self );
	liqcell_child_append(  self, cmdall);
	//############################# cmdnone:label
	liqcell *cmdnone = liqcell_quickcreatevis("cmdnone", "label", 714, 190, 86, 116);
	liqcell_setfont(	cmdnone, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdnone, "del" );
	liqcell_propsets(  cmdnone, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdnone, "backcolor", "xrgb(0,64,64)" );
	liqcell_propsets(  cmdnone, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdnone, "textalign", 2 );
	liqcell_propseti(  cmdnone, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdnone, "click", cmdnone_click, self );
	liqcell_child_append(  self, cmdnone);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/sheepdog/media/sheepdog_levelstickers_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", sheepdog_levelstickers_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", sheepdog_levelstickers_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", sheepdog_levelstickers_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", sheepdog_levelstickers_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", sheepdog_levelstickers_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", sheepdog_levelstickers_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", sheepdog_levelstickers_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", sheepdog_levelstickers_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", sheepdog_levelstickers_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", sheepdog_levelstickers_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", sheepdog_levelstickers_dialog_close ,self);
	return self;
}

