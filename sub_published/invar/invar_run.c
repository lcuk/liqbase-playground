// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### invar_run :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * invar_run widget filter, the system is asking you to filter to the specified .
 */	
static int invar_run_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * invar_run widget refresh, all params set, present yourself to the user.
 */	
static int invar_run_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * invar_run dialog_open - the user zoomed into the dialog
 */	
static int invar_run_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	liqcell *body = liqcell_child_lookup(self, "body");
	liqcell_handlerrun(body,"refresh",NULL); 
	 return 0;
}
/**	
 * invar_run dialog_close - the dialog was closed
 */	
static int invar_run_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * invar_run widget shown - occurs once per lifetime
 */	
static int invar_run_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * invar_run mouse - occurs all the time as you stroke the screen
 */	
static int invar_run_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_run click - occurs when a short mouse stroke occured
 */	
static int invar_run_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_run keypress - the user pressed a key
 */	
static int invar_run_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_run keyrelease - the user released a key
 */	
static int invar_run_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * invar_run paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int invar_run_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * invar_run dynamic resizing
 */	
static int invar_run_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *body = liqcell_child_lookup(self, "body");
	liqcell_setrect_autoscale( body, 0,0, 800,480, sx,sy);
	return 0;
}

/**	
 * invar_run_child_test_seek this function shows how to access members
 */	
	  
static void invar_run_child_test_seek(liqcell *invar_run)
{	  
	liqcell *body = liqcell_child_lookup(invar_run, "body");
}	  
/**	
 * create a new invar_run widget
 */	
liqcell *invar_run_create()
{
	liqcell *self = liqcell_quickcreatewidget("invar_run", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'invar_run'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# body:label
	liqcell *body = liqcell_quickcreatevis("body", "invar_rawview", 0, 0, 800, 480);
	//liqcell_setfont(	body, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(body, "body" );
	//liqcell_propsets(  body, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  body, "backcolor", "rgb(64,64,64)" );
	//liqcell_propseti(  body, "textalign", 0 );
	//liqcell_propseti(  body, "textaligny", 0 );
	liqcell_child_append(  self, body);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/invar/media/invar_run_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter",		 (void*)invar_run_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh",		(void*)invar_run_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown",		  (void*)invar_run_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize",	  (void*)invar_run_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress",	(void*)invar_run_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", (void*)invar_run_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse",		(void*)invar_run_mouse,self );
	//liqcell_handleradd_withcontext(self, "click",		(void*)invar_run_click ,self);
	//liqcell_handleradd_withcontext(self, "paint",		(void*)invar_run_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open",  (void*)invar_run_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", (void*)invar_run_dialog_close ,self);
	return self;
}

