// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqbase_about :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqbase_about widget filter, the system is asking you to filter to the specified .
 */	
static int liqbase_about_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * liqbase_about widget refresh, all params set, present yourself to the user.
 */	
static int liqbase_about_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqbase_about dialog_open - the user zoomed into the dialog
 */	
static int liqbase_about_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqbase_about dialog_close - the dialog was closed
 */	
static int liqbase_about_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqbase_about widget shown - occurs once per lifetime
 */	
static int liqbase_about_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqbase_about mouse - occurs all the time as you stroke the screen
 */	
static int liqbase_about_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqbase_about click - occurs when a short mouse stroke occured
 */	
static int liqbase_about_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqbase_about keypress - the user pressed a key
 */	
static int liqbase_about_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqbase_about keyrelease - the user released a key
 */	
static int liqbase_about_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqbase_about paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqbase_about_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqbase_about dynamic resizing
 */	
static int liqbase_about_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *label4 = liqcell_child_lookup(self, "label4");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *avatar = liqcell_child_lookup(self, "avatar");
	liqcell *label6 = liqcell_child_lookup(self, "label6");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *appicon = liqcell_child_lookup(self, "appicon");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *label7 = liqcell_child_lookup(self, "label7");
	liqcell *label8 = liqcell_child_lookup(self, "label8");
	liqcell_setrect_autoscale( label8, 18,518, 446,28, sx,sy);
	liqcell_setrect_autoscale( label7, 24,566, 388,24, sx,sy);
	liqcell_setrect_autoscale( label5, 22,448, 404,24, sx,sy);
	liqcell_setrect_autoscale( appicon, 14,62, 170,160, sx,sy);
	liqcell_setrect_autoscale( label3, 24,392, 388,24, sx,sy);
	liqcell_setrect_autoscale( label2, 14,770, 458,22, sx,sy);
	liqcell_setrect_autoscale( label6, 192,144, 248,40, sx,sy);
	liqcell_setrect_autoscale( avatar, 18,242, 74,92, sx,sy);
	liqcell_setrect_autoscale( label1, 22,358, 428,26, sx,sy);
	liqcell_setrect_autoscale( label4, 190,90, 218,54, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 480,56, sx,sy);
	return 0;
}

/**	
 * liqbase_about_child_test_seek this function shows how to access members
 */	
	  
static void liqbase_about_child_test_seek(liqcell *liqbase_about)
{	  
	liqcell *label1 = liqcell_child_lookup(liqbase_about, "label1");
	liqcell *label4 = liqcell_child_lookup(liqbase_about, "label4");
	liqcell *title = liqcell_child_lookup(liqbase_about, "title");
	liqcell *avatar = liqcell_child_lookup(liqbase_about, "avatar");
	liqcell *label6 = liqcell_child_lookup(liqbase_about, "label6");
	liqcell *label2 = liqcell_child_lookup(liqbase_about, "label2");
	liqcell *label3 = liqcell_child_lookup(liqbase_about, "label3");
	liqcell *appicon = liqcell_child_lookup(liqbase_about, "appicon");
	liqcell *label5 = liqcell_child_lookup(liqbase_about, "label5");
	liqcell *label7 = liqcell_child_lookup(liqbase_about, "label7");
	liqcell *label8 = liqcell_child_lookup(liqbase_about, "label8");
}	  
/**	
 * create a new liqbase_about widget
 */	
liqcell *liqbase_about_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqbase_about", "form", 480, 800);
	if(!self) {liqapp_log("liqcell error not create 'liqbase_about'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 22, 358, 428, 26);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
	liqcell_setcaption(label1, "Created by Gary Birkett (liquid@gmail.com)" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_propseti(  label1, "textaligny", 0 );
	liqcell_child_append(  self, label1);
	//############################# label4:label
	liqcell *label4 = liqcell_quickcreatevis("label4", "label", 190, 90, 218, 54);
	liqcell_setfont(	label4, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(label4, "liqbase" );
	liqcell_propsets(  label4, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label4, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label4, "textalign", 0 );
	liqcell_propseti(  label4, "textaligny", 0 );
	liqcell_child_append(  self, label4);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 480, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_setcaption(title, "liqbase about" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(0,64,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# avatar:image
	liqcell *avatar = liqcell_quickcreatevis("avatar", "image", 18, 242, 74, 92);
	liqcell_propsets(  avatar, "imagefilename", "/usr/share/liqbase/invar/media/liqbase_about.avatar.png" );
	liqcell_child_append(  self, avatar);
	//############################# label6:label
	liqcell *label6 = liqcell_quickcreatevis("label6", "label", 192, 144, 248, 40);
	liqcell_setfont(	label6, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (26), 0) );
	liqcell_setcaption(label6, "faster than paper" );
	liqcell_propsets(  label6, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label6, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label6, "textalign", 0 );
	liqcell_propseti(  label6, "textaligny", 0 );
	liqcell_child_append(  self, label6);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 14, 770, 458, 22);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label2, "Like what you see?  Donate to the developers, everything is open source." );
	liqcell_propsets(  label2, "textcolor", "rgb(192,255,192)" );
	liqcell_propsets(  label2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label2, "textalign", 0 );
	liqcell_propseti(  label2, "textaligny", 0 );
	liqcell_child_append(  self, label2);
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 24, 392, 388, 24);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
	liqcell_setcaption(label3, "http://liqbase.net" );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label3, "textalign", 0 );
	liqcell_propseti(  label3, "textaligny", 0 );
	liqcell_child_append(  self, label3);
	//############################# appicon:image
	liqcell *appicon = liqcell_quickcreatevis("appicon", "image", 14, 62, 170, 160);
	liqcell_propsets(  appicon, "imagefilename", "/usr/share/liqbase/invar/media/liqbase_about.appicon.png" );
	liqcell_child_append(  self, appicon);
	//############################# label5:label
	liqcell *label5 = liqcell_quickcreatevis("label5", "label", 22, 448, 404, 24);
	liqcell_setfont(	label5, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label5, "" );
	liqcell_propsets(  label5, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label5, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label5, "textalign", 0 );
	liqcell_propseti(  label5, "textaligny", 0 );
	liqcell_child_append(  self, label5);
	//############################# label7:label
	liqcell *label7 = liqcell_quickcreatevis("label7", "label", 24, 566, 388, 24);
	liqcell_setfont(	label7, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
	liqcell_setcaption(label7, "http://collabora.co.uk" );
	liqcell_propsets(  label7, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label7, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label7, "textalign", 0 );
	liqcell_propseti(  label7, "textaligny", 0 );
	liqcell_child_append(  self, label7);
	//############################# label8:label
	liqcell *label8 = liqcell_quickcreatevis("label8", "label", 18, 518, 446, 28);
	liqcell_setfont(	label8, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
	liqcell_setcaption(label8, "" );
	liqcell_propsets(  label8, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label8, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label8, "textalign", 0 );
	liqcell_propseti(  label8, "textaligny", 0 );
	liqcell_child_append(  self, label8);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/invar/media/liqbase_about_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter",		 (void*)liqbase_about_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh",		(void*)liqbase_about_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown",		  (void*)liqbase_about_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize",	  (void*)liqbase_about_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress",	(void*)liqbase_about_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", (void*)liqbase_about_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse",		(void*)liqbase_about_mouse,self );
	//liqcell_handleradd_withcontext(self, "click",		(void*)liqbase_about_click ,self);
	//liqcell_handleradd_withcontext(self, "paint",		(void*)liqbase_about_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open",  (void*)liqbase_about_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", (void*)liqbase_about_dialog_close ,self);
	return self;
}

