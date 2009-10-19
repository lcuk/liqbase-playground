// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>


liqcell *mkslide()
{
}

		
		
//#####################################################################
//#####################################################################
//##################################################################### liqslidehost :: by gary birkett
//#####################################################################
//#####################################################################




		
		
/**	
 * liqslidehost widget filter, the system is asking you to filter to the specified .
 */	
static int liqslidehost_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * liqslidehost widget refresh, all params set, present yourself to the user.
 */	
static int liqslidehost_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqslidehost dialog_open - the user zoomed into the dialog
 */	
static int liqslidehost_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqslidehost dialog_close - the dialog was closed
 */	
static int liqslidehost_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqslidehost widget shown - occurs once per lifetime
 */	
static int liqslidehost_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{


    liqcell *allslides = liqcell_child_lookup(self, "allslides");

    liqcell * vbparse_vbp_load(char *filename);
    liqcell * liqpages_vbcreate_from_project(liqcell *domproj);
    liqcell *domproj = vbparse_vbp_load("/usr/share/liqbase/maemosummit2009/media/xpres/Project1.vbp");
    //liqcell *domproj = vbparse_vbp_load("/home/svn/liqbase-playground/maemosummit2009/maemosummit2009.vbp");
    //liqcell *domproj = vbparse_vbp_load("/home/svn/maemosummit2009/maemosummit2009.vbp"); 
    liqpages_addpages_from_vbproject( allslides, domproj );
    liqcell_setname(allslides,"allslides");



	return 0;
}
/**	
 * liqslidehost mouse - occurs all the time as you stroke the screen
 */	
static int liqslidehost_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqslidehost click - occurs when a short mouse stroke occured
 */	
static int liqslidehost_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqslidehost keypress - the user pressed a key
 */	
static int liqslidehost_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqslidehost keyrelease - the user released a key
 */	
static int liqslidehost_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}

#define SGN(X) ( ((X)<0) ? -1 : (   ((X)>0) ? 1 : 0 )   )

/**	
 * liqslidehost paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
static int liqslidehost_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{
    
	// big heavy event, use sparingly
}
/**	
 * liqslidehost dynamic resizing
 */	
static int liqslidehost_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	//liqcell *backplane = liqcell_child_lookup(self, "backplane");
	//	liqcell *allslides = liqcell_child_lookup(backplane, "allslides");
	liqcell *timer = liqcell_child_lookup(self, "timer");
	liqcell *cmdprev = liqcell_child_lookup(self, "cmdprev");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *title = liqcell_child_lookup(self, "title");
	//liqcell_setrect_autoscale( backplane, 0,46, 800,384, sx,sy);
	//liqcell_setrect_autoscale( allslides, 0,0, 800,384, sx,sy);
	liqcell_setrect_autoscale( timer, 606,12, 114,18, sx,sy);
	liqcell_setrect_autoscale( cmdprev, 566,432, 96,48, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 664,432, 136,48, sx,sy);
	liqcell_setrect_autoscale( label1, 88,444, 464,30, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,46, sx,sy);
	return 0;
}

/**	
 * liqslidehost.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqslidehost)
{
    liqcell *allslides = liqcell_child_lookup(liqslidehost, "allslides");
    liqpages_movenext(allslides);


	return 0;
}

/**	
 * liqslidehost.cmdprev clicked
 */	
static int cmdprev_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqslidehost)
{
	liqcell *allslides = liqcell_child_lookup(liqslidehost, "allslides");
    liqpages_moveprev(allslides);

	return 0;
}

/**	
 * liqslidehost_child_test_seek this function shows how to access members
 */	
	  
static void liqslidehost_child_test_seek(liqcell *liqslidehost)
{	  
	//liqcell *backplane = liqcell_child_lookup(liqslidehost, "backplane");
	//	liqcell *allslides = liqcell_child_lookup(backplane, "allslides");
	liqcell *timer = liqcell_child_lookup(liqslidehost, "timer");
	liqcell *cmdprev = liqcell_child_lookup(liqslidehost, "cmdprev");
	liqcell *cmdaccept = liqcell_child_lookup(liqslidehost, "cmdaccept");
	liqcell *label1 = liqcell_child_lookup(liqslidehost, "label1");
	liqcell *title = liqcell_child_lookup(liqslidehost, "title");
}	  
/**	
 * create a new liqslidehost widget
 */	
liqcell *liqslidehost_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqslidehost", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqslidehost'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
     
           
    //############################# allslides:picturebox
    liqcell *allslides = liqcell_quickcreatevis("allslides", "liqpages", 0, 46, 800, 384);
    //liqcell_setfont(	allslides, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
    //liqcell_propsets(  allslides, "textcolor", "rgb(0,0,0)" );
    //liqcell_propsets(  allslides, "backcolor", "rgb(0,0,64)" );
    //liqcell_propsets(allslides,"slidenames", "liqslideitem_what,liqslideitem_opt,liqsketchedit,liqrecentsketches,liqrecentusers,liqflow");  
	//liqcell_child_append(  self, allslides);
    
    liqcell_child_append(  self, allslides);
            
    //liqcell_print(domproj  ,"dom",0);
    //liqcell_print(allslides,"sli",0);
            
	//############################# timer:label
	liqcell *timer = liqcell_quickcreatevis("timer", "label", 606, 12, 114, 18);
	liqcell_setfont(	timer, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(timer, "00:00" );
	liqcell_propsets(  timer, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  timer, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  timer, "textalign", 2 );
	liqcell_propseti(  timer, "textaligny", 2 );
	liqcell_child_append(  self, timer);
	//############################# cmdprev:label
	liqcell *cmdprev = liqcell_quickcreatevis("cmdprev", "label", 566, 432, 96, 48);
	liqcell_setfont(	cmdprev, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdprev, "<" );
	liqcell_propsets(  cmdprev, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdprev, "backcolor", "xrgb(64,64,0)" );
	liqcell_propsets(  cmdprev, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdprev, "textalign", 2 );
	liqcell_propseti(  cmdprev, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdprev, "click", cmdprev_click, self );
	liqcell_child_append(  self, cmdprev);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 664, 432, 136, 48);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, ">" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 88, 444, 464, 30);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label1, "liqbase by Gary Birkett :: liquid@gmail.com" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_propseti(  label1, "textaligny", 0 );
	liqcell_child_append(  self, label1);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 46);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "maemo & liqbase" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/maemosummit2009/media/liqslidehost_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", liqslidehost_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", liqslidehost_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqslidehost_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", liqslidehost_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqslidehost_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqslidehost_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", liqslidehost_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", liqslidehost_click ,self);
	liqcell_handleradd_withcontext(self, "paint", liqslidehost_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqslidehost_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqslidehost_dialog_close ,self);
    
    
     
    
	return self;
}

