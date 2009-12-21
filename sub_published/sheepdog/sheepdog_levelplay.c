// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### sheepdog_levelplay :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * sheepdog_levelplay widget filter, the system is asking you to filter to the specified .
 */	
static int sheepdog_levelplay_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * sheepdog_levelplay widget refresh, all params set, present yourself to the user.
 */	
static int sheepdog_levelplay_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelplay dialog_open - the user zoomed into the dialog
 */	
static int sheepdog_levelplay_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdog_levelplay dialog_close - the dialog was closed
 */	
static int sheepdog_levelplay_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdog_levelplay widget shown - occurs once per lifetime
 */	
static int sheepdog_levelplay_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelplay mouse - occurs all the time as you stroke the screen
 */	
static int sheepdog_levelplay_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelplay click - occurs when a short mouse stroke occured
 */	
static int sheepdog_levelplay_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelplay keypress - the user pressed a key
 */	
static int sheepdog_levelplay_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelplay keyrelease - the user released a key
 */	
static int sheepdog_levelplay_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdog_levelplay paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int sheepdog_levelplay_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * sheepdog_levelplay dynamic resizing
 */	
static int sheepdog_levelplay_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	liqcell *countdown = liqcell_child_lookup(self, "countdown");
	liqcell *gameover = liqcell_child_lookup(self, "gameover");
	liqcell *score = liqcell_child_lookup(self, "score");
	liqcell_setrect_autoscale( backplane, 0,0, 800,480, sx,sy);
	liqcell_setrect_autoscale( countdown, 278,2, 176,34, sx,sy);
	liqcell_setrect_autoscale( gameover, 178,238, 424,46, sx,sy);
	liqcell_setrect_autoscale( score, 622,2, 176,34, sx,sy);
	return 0;
}

/**	
 * sheepdog_levelplay_child_test_seek this function shows how to access members
 */	
	  
static void sheepdog_levelplay_child_test_seek(liqcell *sheepdog_levelplay)
{	  
	liqcell *backplane = liqcell_child_lookup(sheepdog_levelplay, "backplane");
	liqcell *countdown = liqcell_child_lookup(sheepdog_levelplay, "countdown");
	liqcell *gameover = liqcell_child_lookup(sheepdog_levelplay, "gameover");
	liqcell *score = liqcell_child_lookup(sheepdog_levelplay, "score");
}	  
/**	
 * create a new sheepdog_levelplay widget
 */	
liqcell *sheepdog_levelplay_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdog_levelplay", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'sheepdog_levelplay'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# backplane:label
	liqcell *backplane = liqcell_quickcreatevis("backplane", "label", 0, 0, 800, 480);
	liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(backplane, "backplane" );
	liqcell_propsets(  backplane, "textcolor", "rgb(255,0,0)" );
	liqcell_propsets(  backplane, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  backplane, "textalign", 2 );
	liqcell_propseti(  backplane, "textaligny", 2 );
	liqcell_child_append(  self, backplane);
	//############################# countdown:label
	liqcell *countdown = liqcell_quickcreatevis("countdown", "label", 278, 2, 176, 34);
	liqcell_setfont(	countdown, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(countdown, "30 seconds left" );
	liqcell_propsets(  countdown, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  countdown, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  countdown, "textalign", 0 );
	liqcell_propseti(  countdown, "textaligny", 0 );
	liqcell_child_append(  self, countdown);
	//############################# gameover:label
	liqcell *gameover = liqcell_quickcreatevis("gameover", "label", 178, 238, 424, 46);
	liqcell_setfont(	gameover, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(gameover, "Game Over" );
	liqcell_propsets(  gameover, "textcolor", "rgb(255,0,0)" );
	liqcell_propsets(  gameover, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  gameover, "textalign", 2 );
	liqcell_propseti(  gameover, "textaligny", 2 );
	liqcell_setvisible(  gameover, 0 );
	liqcell_child_append(  self, gameover);
	//############################# score:label
	liqcell *score = liqcell_quickcreatevis("score", "label", 622, 2, 176, 34);
	liqcell_setfont(	score, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(score, "80 points" );
	liqcell_propsets(  score, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  score, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  score, "textalign", 0 );
	liqcell_propseti(  score, "textaligny", 0 );
	liqcell_child_append(  self, score);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/sheepdog/media/sheepdog_levelplay_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", sheepdog_levelplay_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", sheepdog_levelplay_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", sheepdog_levelplay_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", sheepdog_levelplay_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", sheepdog_levelplay_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", sheepdog_levelplay_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", sheepdog_levelplay_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", sheepdog_levelplay_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", sheepdog_levelplay_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", sheepdog_levelplay_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", sheepdog_levelplay_dialog_close ,self);
	return self;
}

