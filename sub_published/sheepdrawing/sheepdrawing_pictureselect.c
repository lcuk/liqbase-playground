






// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqapp_prefs.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>



    // todo, move this into the lib at earliest opportunity
    // Tue Oct 20 15:44:27 2009 lcuk : done
    
    
    static int liqcell_filter_run(liqcell *c,char *searchterm)
    {
        liqcellfiltereventargs filterargs;
        filterargs.filterinuse= (searchterm ? 1 : 0);
        filterargs.searchterm = searchterm;
        filterargs.searchtags = NULL;
        filterargs.resultoutof= 1;
        filterargs.resultshown= 0;
        
        if(!filterargs.resultshown)
        {
            if(searchterm && *searchterm)
            {
            }
            else
            {
                filterargs.resultshown = 1;
            }
        }
        
        if(!filterargs.resultshown)
        {
            if(c->name)
                filterargs.resultshown = ( stristr(c->name,searchterm) != NULL );
        }
    
        if(!filterargs.resultshown)
        {
            if(c->classname)
                filterargs.resultshown = ( stristr(c->classname,searchterm) != NULL );
        }
        
        liqcell *ccontent = liqcell_getcontent( c );
        if(ccontent)
        {
            liqapp_log("searching in cont '%s', %i",c->name,filterargs.resultshown);
            liqcell_handlerrun( ccontent , "filter", &filterargs );
        }
        else
        {
            liqapp_log("searching in flat '%s', %i",c->name,filterargs.resultshown);
            liqcell_handlerrun( c , "filter", &filterargs );
        }
    
        if(filterargs.resultshown)
        {
            liqcell_setvisible(c,1);
            return 1;
        }
        else
        {
            liqcell_setvisible(c,0);
            return 0;
        }
    }
    
    
		
		
//#####################################################################
//#####################################################################
//##################################################################### sheepdrawing_pictureselect :: by gary birkett
//#####################################################################
//#####################################################################

		
/**	
 * sheepdrawing_pictureselect widget refresh, all params set, present yourself to the user.
 */	
static int sheepdrawing_pictureselect_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * sheepdrawing_pictureselect dialog_open - the user zoomed into the dialog
 */	
static int sheepdrawing_pictureselect_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *sheepdrawing_pictureselect)
{
    liqcell_propremoves(  sheepdrawing_pictureselect, "imagefilenameselected"  );
	return 0;
}
/**	
 * sheepdrawing_pictureselect dialog_close - the dialog was closed
 */	
static int sheepdrawing_pictureselect_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_pictureselect widget shown - occurs once per lifetime
 */	
static int sheepdrawing_pictureselect_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_pictureselect mouse - occurs all the time as you stroke the screen
 */	
static int sheepdrawing_pictureselect_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_pictureselect click - occurs when a short mouse stroke occured
 */	
static int sheepdrawing_pictureselect_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_pictureselect keypress - the user pressed a key
 */	
//static int sheepdrawing_pictureselect_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
//{
//	return 0;
//}
/**	
 * sheepdrawing_pictureselect keyrelease - the user released a key
 */	
//static int sheepdrawing_pictureselect_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
//{
//	return 0;
//}
/**	
 * sheepdrawing_pictureselect paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int sheepdrawing_pictureselect_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * sheepdrawing_pictureselect dynamic resizing
 */	
static int sheepdrawing_pictureselect_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *cmdselect = liqcell_child_lookup(self, "cmdselect");
	liqcell *sheepdrawing_picturegrid = liqcell_child_lookup(self, "sheepdrawing_picturegrid");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( cmdselect, 580,420, 220,60, sx,sy);
	liqcell_setrect_autoscale( sheepdrawing_picturegrid, 0,58, 800,420, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
	return 0;
}

/**	
 * sheepdrawing_pictureselect.cmdselect clicked
 */	
static int cmdselect_click(liqcell *self,liqcelleventargs *args, liqcell *sheepdrawing_pictureselect)
{
    // we are done here.

    liqcell *sheepdrawing_picturegrid = liqcell_child_lookup(sheepdrawing_pictureselect, "sheepdrawing_picturegrid");
    
           //########## major sideways hack.  classes need declarations and header files.
            int liqrecentphotoselect_getselectedphoto_filename(liqcell *self,char *buffer,int bufferlen);
            char selfn[FILENAME_MAX]={0};
            liqrecentphotoselect_getselectedphoto_filename(sheepdrawing_picturegrid,selfn,sizeof(selfn) );

            //liqapp_log("selimg a %s",selfn);
            
            //char *selfn=liqcell_propgets(  oneedit, "imagefilenameselected",NULL );
            
            if( selfn && *selfn )
            {
                liqapp_log("selimg got sel %s",selfn);
                liqcell_propsets(  sheepdrawing_pictureselect, "imagefilenameselected", selfn  );               
            }           

    
    liqcell_setvisible(sheepdrawing_pictureselect,0);
	return 0;
}
/**	
 * sheepdrawing_pictureselect_child_test_seek this function shows how to access members
 */	
	  
static void sheepdrawing_pictureselect_child_test_seek(liqcell *self)
{	  
	liqcell *cmdselect = liqcell_child_lookup(self, "cmdselect");
	liqcell *sheepdrawing_picturegrid = liqcell_child_lookup(self, "sheepdrawing_picturegrid");
	liqcell *title = liqcell_child_lookup(self, "title");
}


	
    
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################








	static int search_click(liqcell *self, liqcelleventargs *args, liqcell *sheepdrawing_pictureselect)
	{
		// try to add this tag :)
		//liqcell *body = liqcell_child_lookup(sheepdrawing_pictureselect,"body");
		char *searchterm = liqcell_getcaption(self);
		if(!searchterm || !*searchterm) return 1;
		liqcell_setcaption(self,"");
		return 1;
	}
	static int search_change(liqcell *self, liqcelleventargs *args, liqcell *sheepdrawing_pictureselect)
	{
		// examine each tag and if matches the search show it, otherwise dont..
		char *searchterm = liqcell_getcaption(self);

        liqcell *sheepdrawing_picturegrid=liqcell_child_lookup(sheepdrawing_pictureselect,"sheepdrawing_picturegrid");
        liqcell_filter_run(sheepdrawing_picturegrid,searchterm);
        
		return 1;
		
	}
	    
    
    
	static int sheepdrawing_pictureselect_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *sheepdrawing_pictureselect)
	{
		liqcell *search = liqcell_child_lookup(sheepdrawing_pictureselect,"search");
		if(liqcell_getvisible(search)==0)
		{
			// start it just off screen
			liqcell_setpos( search, liqcell_getx(search), liqcell_geth(sheepdrawing_pictureselect) );
			liqcell_setvisible(search,1);
		}
		return liqcell_handlerrun(search,"keypress",args);
	}
	static int sheepdrawing_pictureselect_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *sheepdrawing_pictureselect)
	{
		liqcell *search = liqcell_child_lookup(sheepdrawing_pictureselect,"search");
		return liqcell_handlerrun(search,"keyrelease",args);
	}
    
	static int sheepdrawing_pictureselect_paint(liqcell *self, liqcellpainteventargs *args,liqcell *sheepdrawing_pictureselect)
	{
		liqcell *search = liqcell_child_lookup(sheepdrawing_pictureselect,"search");
		if(liqcell_getvisible(search))
		{
			if( liqcell_gety(search) > ( liqcell_geth(sheepdrawing_pictureselect) - liqcell_geth(search) )  )
			{
				// move it a bit more onscreen
				int dif = liqcell_gety(search) - ( liqcell_geth(sheepdrawing_pictureselect) - liqcell_geth(search) );
				//if(dif>5)dif=5;
				liqcell_setpos( search, liqcell_getx(search), liqcell_gety(search) - dif );
				liqcell_setdirty(sheepdrawing_pictureselect,1);
			}
		}
        return 0;
    }

/**	
 * create a new sheepdrawing_pictureselect widget
 */	
liqcell *sheepdrawing_pictureselect_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdrawing_pictureselect", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'sheepdrawing_pictureselect'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering


	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "select image   - todo: use hildon thumbs. hey albanc.." );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# sheepdrawing_picturegrid:liqrecentphotos
	liqcell *sheepdrawing_picturegrid = liqcell_quickcreatevis("sheepdrawing_picturegrid", "sheepdrawing_picturegrid", 0, 58, 800, 420);
	liqcell_child_append(  self, sheepdrawing_picturegrid);
    //############################# cmdselect:commandbutton
	liqcell *cmdselect = liqcell_quickcreatevis("cmdselect", "commandbutton", 580, 420, 220, 60);
	liqcell_setfont(	cmdselect, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdselect, "Select" );
	liqcell_propsets(  cmdselect, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdselect, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdselect, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdselect, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdselect, "click", cmdselect_click, self );
    //liqcell_setenabled(cmdselect,0);
	liqcell_child_append(  self, cmdselect);
    
    
		liqcell *search = liqcell_quickcreatevis("search","textbox",200 ,self->h-40,   350, 60);
		liqcell_setfont(   search,  liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
		liqcell_setcaption(search, "" );
		liqcell_propsets(  search, "textcolor",   "rgb(255,255,255)" );
		liqcell_propsets(  search, "backcolor",   "xrgb(100,140,100)" );
		liqcell_handleradd_withcontext( search,    "click",           search_click,  self );
		liqcell_handleradd_withcontext( search,    "captionchange",   search_change, self );
		liqcell_setvisible(search,0);		// watch this!
		liqcell_child_append( self, search );
		
		//liqcell_handleradd_withcontext(body,    "keypress",   sheepdrawing_pictureselect_keypress,  self);
		//liqcell_handleradd_withcontext(body,    "keyrelease", sheepdrawing_pictureselect_keyrelease,self);
		liqcell_handleradd_withcontext(self,    "keypress",   sheepdrawing_pictureselect_keypress,  self);
		liqcell_handleradd_withcontext(self,    "keyrelease", sheepdrawing_pictureselect_keyrelease,self);
 		liqcell_handleradd_withcontext(self,    "paint",      sheepdrawing_pictureselect_paint,  	self);
        
    
    //liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", sheepdrawing_pictureselect_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", sheepdrawing_pictureselect_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", sheepdrawing_pictureselect_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", sheepdrawing_pictureselect_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", sheepdrawing_pictureselect_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", sheepdrawing_pictureselect_mouse,self );
	liqcell_handleradd_withcontext(self, "click", sheepdrawing_pictureselect_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", sheepdrawing_pictureselect_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", sheepdrawing_pictureselect_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", sheepdrawing_pictureselect_dialog_close ,self);
	return self;
}



