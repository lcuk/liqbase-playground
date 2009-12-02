// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqmap_selectitem :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqmap_selectitem widget filter, the system is asking you to filter to the specified .
 */	
static int liqmap_selectitem_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * liqmap_selectitem widget refresh, all params set, present yourself to the user.
 */	
static int liqmap_selectitem_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmap_selectitem dialog_open - the user zoomed into the dialog
 */	
static int liqmap_selectitem_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqmap_selectitem dialog_close - the dialog was closed
 */	
static int liqmap_selectitem_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqmap_selectitem widget shown - occurs once per lifetime
 */	
static int liqmap_selectitem_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqmap_selectitem mouse - occurs all the time as you stroke the screen
 */	
static int liqmap_selectitem_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_selectitem click - occurs when a short mouse stroke occured
 */	
static int liqmap_selectitem_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_selectitem keypress - the user pressed a key
 */	
static int liqmap_selectitem_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_selectitem keyrelease - the user released a key
 */	
static int liqmap_selectitem_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqmap_selectitem paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqmap_selectitem_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqmap_selectitem dynamic resizing
 */	
static int liqmap_selectitem_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *lblname = liqcell_child_lookup(self, "lblname");
	liqcell *lblwidth = liqcell_child_lookup(self, "lblwidth");
	liqcell *lblheight = liqcell_child_lookup(self, "lblheight");
	liqcell *lblcountry = liqcell_child_lookup(self, "lblcountry");
	liqcell_setrect_autoscale( lblname, 6,6, 440,40, sx,sy);
	liqcell_setrect_autoscale( lblwidth, 628,10, 74,30, sx,sy);
	liqcell_setrect_autoscale( lblheight, 712,10, 76,30, sx,sy);
	liqcell_setrect_autoscale( lblcountry, 450,10, 170,30, sx,sy);
	return 0;
}

/**	
 * liqmap_selectitem_child_test_seek this function shows how to access members
 */	
	  
static void liqmap_selectitem_child_test_seek(liqcell *liqmap_selectitem)
{	  
	liqcell *lblname = liqcell_child_lookup(liqmap_selectitem, "lblname");
	liqcell *lblwidth = liqcell_child_lookup(liqmap_selectitem, "lblwidth");
	liqcell *lblheight = liqcell_child_lookup(liqmap_selectitem, "lblheight");
	liqcell *lblcountry = liqcell_child_lookup(liqmap_selectitem, "lblcountry");
}	  
/**	
 * create a new liqmap_selectitem widget
 */	
liqcell *liqmap_selectitem_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqmap_selectitem", "form", 800, 52);
	if(!self) {liqapp_log("liqcell error not create 'liqmap_selectitem'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# lblname:label
	liqcell *lblname = liqcell_quickcreatevis("lblname", "label", 6, 6, 440, 40);
	liqcell_setfont(	lblname, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(lblname, "London Underground" );
	liqcell_propsets(  lblname, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  lblname, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lblname, "textalign", 0 );
	liqcell_propseti(  lblname, "textaligny", 0 );
	liqcell_child_append(  self, lblname);
	//############################# lblwidth:label
	liqcell *lblwidth = liqcell_quickcreatevis("lblwidth", "label", 628, 10, 74, 30);
	liqcell_setfont(	lblwidth, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(lblwidth, "1600" );
	liqcell_propsets(  lblwidth, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  lblwidth, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lblwidth, "textalign", 1 );
	liqcell_propseti(  lblwidth, "textaligny", 1 );
	liqcell_child_append(  self, lblwidth);
	//############################# lblheight:label
	liqcell *lblheight = liqcell_quickcreatevis("lblheight", "label", 712, 10, 76, 30);
	liqcell_setfont(	lblheight, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(lblheight, "960" );
	liqcell_propsets(  lblheight, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  lblheight, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lblheight, "textalign", 1 );
	liqcell_propseti(  lblheight, "textaligny", 1 );
	liqcell_child_append(  self, lblheight);
	//############################# lblcountry:label
	liqcell *lblcountry = liqcell_quickcreatevis("lblcountry", "label", 450, 10, 170, 30);
	liqcell_setfont(	lblcountry, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(lblcountry, "United Kingdom" );
	liqcell_propsets(  lblcountry, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  lblcountry, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lblcountry, "textalign", 0 );
	liqcell_propseti(  lblcountry, "textaligny", 0 );
	liqcell_child_append(  self, lblcountry);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/liqmap/media/liqmap_selectitem_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", liqmap_selectitem_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", liqmap_selectitem_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqmap_selectitem_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", liqmap_selectitem_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqmap_selectitem_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqmap_selectitem_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", liqmap_selectitem_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", liqmap_selectitem_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqmap_selectitem_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqmap_selectitem_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqmap_selectitem_dialog_close ,self);
	return self;
}

