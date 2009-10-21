// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>



int liqmapzoom_changeimagefilename(liqcell *liqmapzoom,char *imagefilename)
{
	liqcell *backplane = liqcell_child_lookup(liqmapzoom, "backplane");
        
	liqcell_propsets(backplane,"imagefilename",imagefilename);
    liqcell_setimage(backplane,NULL);
    liqcell_setrect(backplane,0,0,800,480);
    		
}
//#####################################################################
//#####################################################################
//##################################################################### liqmapzoom :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqmapzoom widget filter, the system is asking you to filter to the specified .
 */	
static int liqmapzoom_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * liqmapzoom widget refresh, all params set, present yourself to the user.
 */	
static int liqmapzoom_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmapzoom dialog_open - the user zoomed into the dialog
 */	
static int liqmapzoom_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmapzoom dialog_close - the dialog was closed
 */	
static int liqmapzoom_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmapzoom widget shown - occurs once per lifetime
 */	
static int liqmapzoom_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmapzoom mouse - occurs all the time as you stroke the screen
 */	
static int liqmapzoom_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmapzoom click - occurs when a short mouse stroke occured
 */	
static int liqmapzoom_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmapzoom keypress - the user pressed a key
 */	
static int liqmapzoom_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmapzoom keyrelease - the user released a key
 */	
static int liqmapzoom_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmapzoom paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqmapzoom_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqmapzoom dynamic resizing
 */	
static int liqmapzoom_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *zoom = liqcell_child_lookup(self, "zoom");
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	liqcell_setrect_autoscale( zoomknob, 0,0, 50,38, sx,sy);
	liqcell_setrect_autoscale( backplane, -2,0, 344,168, sx,sy);
	return 0;
}

/**	
 * liqmapzoom_child_test_seek this function shows how to access members
 */	
	  
static void liqmapzoom_child_test_seek(liqcell *liqmapzoom)
{	  
	liqcell *zoom = liqcell_child_lookup(liqmapzoom, "zoom");
	liqcell *backplane = liqcell_child_lookup(liqmapzoom, "backplane");
}	  
/**	
 * create a new liqmapzoom widget
 */	
liqcell *liqmapzoom_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqmapzoom", "form", 384, 190);
	if(!self) {liqapp_log("liqcell error not create 'liqmapzoom'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering

	//############################# backplane:picturebox
	liqcell *backplane = liqcell_quickcreatevis("backplane", "picturebox", -2, 0, 344, 168);
	//liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	//liqcell_propsets(  backplane, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  backplane, "backcolor", "rgb(0,0,64)" );

		liqcell_propseti(backplane,"lockaspect",0);
		liqcell_propseti(backplane,"autosize",1);
		liqcell_propseti(backplane,"imageallowalpha",0);
        
		liqcell_handleradd(backplane,    "mouse",   widget_mouse );

	liqcell_child_append(  self, backplane);
    


    //################################################ create the zoom slider
    liqcell *z = liqcell_quickcreatevis("zoom",   "picture",   0,0,100,480    );
    liqcell_propseti(z,"lockaspect",0);
    liqcell_handleradd(z,    "mouse",   zoom_mouse);
    liqcell_child_append( self, z );

        //################################################ create the zoom knob
        liqcell *zi = liqcell_quickcreatevis("knob",   "picture",   0,0,100,48    );
        liqcell_propseti(zi,"lockaspect",0);
        liqcell_propsets(zi,"imagefilename","/usr/share/liqbase/liqmap/media/zoom.png");
        liqcell_child_append( z, zi );

    
    
	//liqcell_propsets(  self, "backcolor", "rgb(0,64,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/liqmap/media/liqmapzoom_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", liqmapzoom_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", liqmapzoom_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqmapzoom_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", liqmapzoom_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqmapzoom_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqmapzoom_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", liqmapzoom_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", liqmapzoom_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqmapzoom_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqmapzoom_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqmapzoom_dialog_close ,self);
	return self;
}

