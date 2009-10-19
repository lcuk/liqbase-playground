// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### doorbell_main :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * doorbell_main widget filter, the system is asking you to filter to the specified .
 */	
static int doorbell_main_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * doorbell_main widget refresh, all params set, present yourself to the user.
 */	
static int doorbell_main_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * doorbell_main dialog_open - the user zoomed into the dialog
 */	
static int doorbell_main_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * doorbell_main dialog_close - the dialog was closed
 */	
static int doorbell_main_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * doorbell_main widget shown - occurs once per lifetime
 */	
static int doorbell_main_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * doorbell_main mouse - occurs all the time as you stroke the screen
 */	
static int doorbell_main_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * doorbell_main click - occurs when a short mouse stroke occured
 */	
static int doorbell_main_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * doorbell_main keypress - the user pressed a key
 */	
static int doorbell_main_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * doorbell_main keyrelease - the user released a key
 */	
static int doorbell_main_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * doorbell_main paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int doorbell_main_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * doorbell_main dynamic resizing
 */	
static int doorbell_main_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *cmdturnon = liqcell_child_lookup(self, "cmdturnon");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell_setrect_autoscale( cmdturnon, 360,254, 94,86, sx,sy);
	liqcell_setrect_autoscale( label2, 286,130, 232,332, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,44, sx,sy);
	liqcell_setrect_autoscale( label1, 134,74, 562,106, sx,sy);
	return 0;
}

/**	
 * doorbell_main.cmdturnon clicked
 */	
static int cmdturnon_click(liqcell *self,liqcellclickeventargs *args, liqcell *doorbell_main)
{
	return 0;
}
/**	
 * doorbell_main_child_test_seek this function shows how to access members
 */	
	  
static void doorbell_main_child_test_seek(liqcell *doorbell_main)
{	  
	liqcell *cmdturnon = liqcell_child_lookup(doorbell_main, "cmdturnon");
	liqcell *label2 = liqcell_child_lookup(doorbell_main, "label2");
	liqcell *title = liqcell_child_lookup(doorbell_main, "title");
	liqcell *label1 = liqcell_child_lookup(doorbell_main, "label1");
}	  
/**	
 * create a new doorbell_main widget
 */	
liqcell *doorbell_main_create()
{
	liqcell *self = liqcell_quickcreatewidget("doorbell_main", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'doorbell_main'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# cmdturnon:label
	liqcell *cmdturnon = liqcell_quickcreatevis("cmdturnon", "label", 360, 254, 94, 86);
	liqcell_setfont(	cmdturnon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (43), 0) );
	liqcell_setcaption(cmdturnon, "" );
	liqcell_propsets(  cmdturnon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdturnon, "backcolor", "xrgb(0,64,0)" );
	liqcell_propseti(  cmdturnon, "textalign", 2 );
	liqcell_propseti(  cmdturnon, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdturnon, "click", cmdturnon_click, self );
	liqcell_child_append(  self, cmdturnon);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 286, 130, 232, 332);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label2, "" );
	liqcell_propsets(  label2, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  label2, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label2, "textalign", 0 );
	liqcell_propseti(  label2, "textaligny", 0 );
	liqcell_child_append(  self, label2);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 44);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "doorbell" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 134, 74, 562, 106);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(label1, "theres somebody at the door!" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label1, "textalign", 2 );
	liqcell_propseti(  label1, "textaligny", 2 );
	liqcell_child_append(  self, label1);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/doorbell/media/doorbell_main_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", doorbell_main_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", doorbell_main_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", doorbell_main_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", doorbell_main_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", doorbell_main_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", doorbell_main_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", doorbell_main_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", doorbell_main_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", doorbell_main_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", doorbell_main_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", doorbell_main_dialog_close ,self);
	return self;
}

