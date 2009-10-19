// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqpages :: by gary birkett
//#####################################################################
//#####################################################################
int liqpages_addpage(liqcell *liqpages,liqcell *page)
{
    // we are only shown once
    // at this point, we must actually create instances of everything requested.

	liqcell *backplane = liqcell_child_lookup(liqpages, "backplane");

	liqcell_child_append(  backplane, page);

    
    liqcell_child_arrange_easyrow(  backplane);
    liqcell_setpos(backplane,0,0);
    
    liqpages_movefirst(liqpages);
    
	return 0;
}

		
/**	
 * liqpages_movefirst
 */	
int liqpages_movefirst(liqcell *liqpages)
{

    char *currentslidename = NULL;//liqcell_propgets(liqpages,"slidecurrentname","");
	liqcell *backplane = liqcell_child_lookup(liqpages, "backplane");
	//	liqcell *slidex = liqcell_child_lookup(backplane, "slidex");
        //liqcell *currentslide = liqcell_getlinkchild_visual(backplane);
        //if(currentslide)
        {
            liqcell *s = liqcell_getlinkchild_visual(backplane);
            if(s)
            {
                // we can go further..
                liqcell_propsets(liqpages,"slidecurrentname",s->name);
                liqcell_setdirty(liqpages,1);
            }
        }

	return 0;
}	
/**	
 * liqpages_movenext
 */	
int liqpages_movenext(liqcell *liqpages)
{

    char *currentslidename = liqcell_propgets(liqpages,"slidecurrentname","");
	liqcell *backplane = liqcell_child_lookup(liqpages, "backplane");
	//	liqcell *slidex = liqcell_child_lookup(backplane, "slidex");
        liqcell *currentslide = liqcell_getlinkchild_visual(backplane);       
        if(currentslidename && *currentslidename)
        {
            currentslide = liqcell_child_lookup(backplane,currentslidename);
        }
        if(currentslide)
        {
            liqcell *s = liqcell_getlinknext_visual(currentslide);
            if(s)
            {
                // we can go further..
                liqcell_propsets(liqpages,"slidecurrentname",s->name);
                liqcell_setdirty(liqpages,1);
            }
        }

	return 0;
}

/**	
 * liqpages_moveprev
 */	
int liqpages_moveprev(liqcell *liqpages)
{

    char *currentslidename = liqcell_propgets(liqpages,"slidecurrentname","");
	liqcell *backplane = liqcell_child_lookup(liqpages, "backplane");
	//	liqcell *slidex = liqcell_child_lookup(backplane, "slidex");
        liqcell *currentslide = liqcell_getlinkchild_visual(backplane);       
        if(currentslidename && *currentslidename)
        {
            currentslide = liqcell_child_lookup(backplane,currentslidename);
        }
        if(currentslide)
        {
            liqcell *s = liqcell_getlinkprev_visual(currentslide);
            if(s)
            {
                // we can go further..
                liqcell_propsets(liqpages,"slidecurrentname",s->name);
                liqcell_setdirty(liqpages,1);
            }
        }

	return 0;
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    	
/**	
 * liqpages widget filter, the system is asking you to filter to the specified .
 */	
static int liqpages_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * liqpages widget refresh, all params set, present yourself to the user.
 */	
static int liqpages_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpages dialog_open - the user zoomed into the dialog
 */	
static int liqpages_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpages dialog_close - the dialog was closed
 */	
static int liqpages_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpages widget shown - occurs once per lifetime
 */	
static int liqpages_shown(liqcell *self,liqcelleventargs *args, liqcell *liqpages)
{
    // we are only shown once
    // at this point, we must actually create instances of everything requested.
	liqapp_log("arghhh");
	liqcell *backplane = liqcell_child_lookup(liqpages, "backplane");    
	char *slidenames = liqcell_propgets(liqpages,"slidenames","");
    if(slidenames && *slidenames)
    {
 
        liqcell_child_removeallvisual(backplane);
    
        while(slidenames && *slidenames)
        {
            char *com=stristr(slidenames,",");
            if(com) *com=0;
            
            liqapp_log("liqpages_shown adding %s",slidenames);
            
			liqcell *slidex = NULL;
			slidex = liqcell_quickcreatevis(slidenames, slidenames, 0,0, liqpages->w, liqpages->h);
			liqcell_child_append(  backplane, slidex);
            
            if(com)
                slidenames=&com[1];
            else
                slidenames=NULL;            
        }
    }

 


    
    liqcell_child_arrange_easyrow(  backplane);
    liqcell_setpos(backplane,0,0);
    
	return 0;
}
/**	
 * liqpages mouse - occurs all the time as you stroke the screen
 */	
static int liqpages_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpages click - occurs when a short mouse stroke occured
 */	
static int liqpages_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpages keypress - the user pressed a key
 */	
static int liqpages_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpages keyrelease - the user released a key
 */	
static int liqpages_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}

#define SGN(X) ( ((X)<0) ? -1 : (   ((X)>0) ? 1 : 0 )   )

/**	
 * liqpages paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
static int liqpages_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{
    
	// big heavy event, use sparingly
    
    char *currentslidename = liqcell_propgets(self,"slidecurrentname","");
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	//	liqcell *slidex = liqcell_child_lookup(backplane, "slidex");
        liqcell *currentslide = liqcell_getlinkchild_visual(backplane);       
        if(currentslidename && *currentslidename)
        {
            currentslide = liqcell_child_lookup(backplane,currentslidename);
        }
        if(currentslide && backplane->kineticx==0)
        {
            int dif = (-liqcell_getx(backplane)) - liqcell_getx(currentslide);
            if(dif)
            {
                int dd=(0.3*(dif));
                if(!dd)dd=SGN(dif);
                
                liqapp_log("dif=%i",dif);
                liqcell_setpos( backplane, liqcell_getx(backplane) + dd, liqcell_gety( backplane) );
                liqcell_setdirty(backplane,1);
            }
        }
}
/**	
 * liqpages dynamic resizing
 */	
static int liqpages_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	//	liqcell *slidex = liqcell_child_lookup(backplane, "slidex");

	liqcell_setrect_autoscale( backplane, 0,46, 800,384, sx,sy);
	//liqcell_setrect_autoscale( slidex, 0,0, 800,384, sx,sy);

	return 0;
}


/**	
 * liqpages_child_test_seek this function shows how to access members
 */	
	  
static void liqpages_child_test_seek(liqcell *liqpages)
{	  
	liqcell *backplane = liqcell_child_lookup(liqpages, "backplane");
	//	liqcell *slidex = liqcell_child_lookup(backplane, "slidex");
}	  
/**	
 * create a new liqpages widget
 */	
liqcell *liqpages_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqpages", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqpages'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# backplane:picturebox
	liqcell *backplane = liqcell_quickcreatevis("backplane", "picturebox", 0, 0, 800, 480);
	//liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  backplane, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  backplane, "backcolor", "rgb(64,64,64)" );
/*
		//############################# slidex:picturebox
		liqcell *slidex = liqcell_quickcreatevis("slidex", "picturebox", 0, 0, 800, 384);
		//liqcell_setfont(	slidex, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_propsets(  slidex, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  slidex, "backcolor", "rgb(0,0,64)" );
			liqcell *slidex = NULL;
			slidex = liqcell_quickcreatevis("liqslideitem_cocreate1", "liqslideitem_cocreate", 0,0, 800, 384);
			liqcell_child_append(  slidex, slidex);
			slidex = liqcell_quickcreatevis("liqslideitem_opt1", "liqslideitem_opt", 0,0, 800, 384);
			liqcell_child_append(  slidex, slidex);
			slidex = liqcell_quickcreatevis("liqslideitem_what1", "liqslideitem_what", 0,0, 800, 384);
			liqcell_child_append(  slidex, slidex);
			slidex = liqcell_quickcreatevis("liqslideitem_cocreate1", "liqslideitem_cocreate", 0,0, 800, 384);
			liqcell_child_append(  slidex, slidex);
			slidex = liqcell_quickcreatevis("liqslideitem_opt1", "liqslideitem_opt", 0,0, 800, 384);
			liqcell_child_append(  slidex, slidex);
			slidex = liqcell_quickcreatevis("liqslideitem_what1", "liqslideitem_what", 0,0, 800, 384);
			liqcell_child_append(  slidex, slidex);
			//slidex = liqcell_quickcreatevis("liqflowmaemo1", "liqflowmaemo", 0,0, 800, 384);
			//liqcell_child_append(  slidex, slidex);
            liqcell_child_arrange_easyrow(  slidex);
		//liqcell_handleradd_withcontext(slidex, "mouse", liqcell_easyhandler_kinetic_mouse, self );
		liqcell_child_arrange_easyrow(  slidex);
		liqcell_child_append(  backplane, slidex);

 */
	liqcell_child_append(  self, backplane);


	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
//	liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/maemosummit2009/media/liqpages_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", liqpages_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", liqpages_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqpages_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", liqpages_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqpages_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqpages_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", liqpages_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", liqpages_click ,self);
	liqcell_handleradd_withcontext(self, "paint", liqpages_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqpages_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqpages_dialog_close ,self);
	return self;
}

