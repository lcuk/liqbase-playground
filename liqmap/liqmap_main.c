// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqmap_main :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqmap_main widget filter, the system is asking you to filter to the specified .
 */	
static int liqmap_main_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * liqmap_main widget refresh, all params set, present yourself to the user.
 */	
static int liqmap_main_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmap_main dialog_open - the user zoomed into the dialog
 */	
static int liqmap_main_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmap_main dialog_close - the dialog was closed
 */	
static int liqmap_main_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmap_main widget shown - occurs once per lifetime
 */	
static int liqmap_main_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmap_main mouse - occurs all the time as you stroke the screen
 */	
static int liqmap_main_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_main click - occurs when a short mouse stroke occured
 */	
static int liqmap_main_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_main keypress - the user pressed a key
 */	
static int liqmap_main_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_main keyrelease - the user released a key
 */	
static int liqmap_main_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_main paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqmap_main_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqmap_main dynamic resizing
 */	
static int liqmap_main_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *liqmapzoom1 = liqcell_child_lookup(self, "liqmapzoom1");
	liqcell *cmdreset = liqcell_child_lookup(self, "cmdreset");
	liqcell *cmdchange = liqcell_child_lookup(self, "cmdchange");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( liqmapzoom1, 0,56, 800,480-56, sx,sy);
	liqcell_setrect_autoscale( cmdreset, 434,0, 146,56, sx,sy);
	liqcell_setrect_autoscale( cmdchange, 582,0, 148,56, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
	return 0;
}

/**	
 * liqmap_main.cmdreset clicked
 */	
static int cmdreset_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqmap_main)
{
	return 0;
}
/**	
 * liqmap_main.cmdchange clicked
 */	
static int cmdchange_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqmap_main)
{

	liqcell *liqmapzoom1 = liqcell_child_lookup(liqmap_main, "liqmapzoom1");


		liqcell * dialog = liqcell_quickcreatevis("dialog","dialog_selectimage",0,0,-1,-1);		
		if(dialog)
		{
            // set dialog config options ..
            // ...
            // run dialog            
			liqcell_easyrun(dialog);
            // process dialog results      
            char *selfn=liqcell_propgets(  dialog, "imagefilenameselected",NULL );
            if( selfn && *selfn )
            {
                //
                int liqmapzoom_changeimagefilename(liqcell *liqmapzoom,char *imagefilename);
                
                liqmapzoom_changeimagefilename(liqmapzoom1,selfn);
            }
            
            // release dialog
                
			liqcell_release(dialog);
		}
    
	return 0;
}
/**	
 * liqmap_main_child_test_seek this function shows how to access members
 */	
	  
static void liqmap_main_child_test_seek(liqcell *liqmap_main)
{	  
	liqcell *liqmapzoom1 = liqcell_child_lookup(liqmap_main, "liqmapzoom1");
	liqcell *cmdreset = liqcell_child_lookup(liqmap_main, "cmdreset");
	liqcell *cmdchange = liqcell_child_lookup(liqmap_main, "cmdchange");
	liqcell *title = liqcell_child_lookup(liqmap_main, "title");
}	  
/**	
 * create a new liqmap_main widget
 */	
liqcell *liqmap_main_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqmap_main", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqmap_main'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# liqmapzoom1:liqmapzoom
	liqcell *liqmapzoom1 = liqcell_quickcreatevis("liqmapzoom1", "liqmapzoom", 0, 56, 800, 480-56);
	liqcell_child_append(  self, liqmapzoom1);
    
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "liqmap viewer" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
    //############################# cmdreset:label
	liqcell *cmdreset = liqcell_quickcreatevis("cmdreset", "label", 434, 0, 146, 56);
	liqcell_setfont(	cmdreset, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdreset, "reset" );
	liqcell_propsets(  cmdreset, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdreset, "backcolor", "xrgb(0,64,64)" );
	liqcell_propsets(  cmdreset, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdreset, "textalign", 2 );
	liqcell_propseti(  cmdreset, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdreset, "click", cmdreset_click, self );
	liqcell_child_append(  self, cmdreset);
	//############################# cmdchange:label
	liqcell *cmdchange = liqcell_quickcreatevis("cmdchange", "label", 582, 0, 148, 56);
	liqcell_setfont(	cmdchange, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdchange, "change" );
	liqcell_propsets(  cmdchange, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdchange, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdchange, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdchange, "textalign", 2 );
	liqcell_propseti(  cmdchange, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdchange, "click", cmdchange_click, self );
	liqcell_child_append(  self, cmdchange);

	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/liqmap/media/liqmap_main_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", liqmap_main_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", liqmap_main_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqmap_main_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", liqmap_main_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqmap_main_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqmap_main_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", liqmap_main_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", liqmap_main_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqmap_main_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqmap_main_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqmap_main_dialog_close ,self);
	return self;
}

