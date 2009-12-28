// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqapp_prefs.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>



static liqimage *buttonback = NULL;

/**	
 * button paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
static int button_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{
	// big heavy event, use sparingly
	//if(!buttonback) buttonback = liqimage_cache_getfile("/usr/share/liqbase/sheepdrawing/media/greybox.png",0,0,0);
	//if(buttonback)
	{
		// ok, we have the image
		// we must do 9 blits (gulp!)
		// the old method uses 1 blit
		
		
	}
	return 0;
}

		
//#####################################################################
//#####################################################################
//##################################################################### sheepdrawing_configure :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * sheepdrawing_configure widget filter, the system is asking you to filter to the specified .
 */	
static int sheepdrawing_configure_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * sheepdrawing_configure widget refresh, all params set, present yourself to the user.
 */	
static int sheepdrawing_configure_refresh(liqcell *self,liqcelleventargs *args, liqcell *sheepdrawing_configure)
{
	liqcell *txtpassword = liqcell_child_lookup(sheepdrawing_configure, "txtpassword");
	liqcell *txtusername = liqcell_child_lookup(sheepdrawing_configure, "txtusername");
	liqcell *txtthread   = liqcell_child_lookup(sheepdrawing_configure, "txtthread");
    
    

	liqcell_setcaption(txtusername,       liqapp_pref_getvalue_def("sheepdrawing_username",  "") );
	liqcell_setcaption(txtpassword,       liqapp_pref_getvalue_def("sheepdrawing_password",  "") );
	liqcell_setcaption(txtthread,         liqapp_pref_getvalue_def("sheepdrawing_thread",  "") );

    

	return 0;
}
/**	
 * sheepdrawing_configure dialog_open - the user zoomed into the dialog
 */	
static int sheepdrawing_configure_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 liqcell_handlerrun(self,"refresh",NULL);
	 return 0;
}
/**	
 * sheepdrawing_configure dialog_close - the dialog was closed
 */	
static int sheepdrawing_configure_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 liqcell_handlerrun(self,"refresh",NULL);
	 return 0;
}
/**	
 * sheepdrawing_configure widget shown - occurs once per lifetime
 */	
static int sheepdrawing_configure_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	liqcell_handlerrun(self,"refresh",NULL);
	return 0;
}
/**	
 * sheepdrawing_configure mouse - occurs all the time as you stroke the screen
 */	
static int sheepdrawing_configure_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_configure click - occurs when a short mouse stroke occured
 */	
static int sheepdrawing_configure_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_configure keypress - the user pressed a key
 */	
static int sheepdrawing_configure_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_configure keyrelease - the user released a key
 */	
static int sheepdrawing_configure_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}

/**	
 * sheepdrawing_configure.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_configure)
{
    
	liqcell *txtpassword = liqcell_child_lookup(sheepdrawing_configure, "txtpassword");
	liqcell *txtusername = liqcell_child_lookup(sheepdrawing_configure, "txtusername");
	liqcell *txtthread   = liqcell_child_lookup(sheepdrawing_configure, "txtthread");
    
	liqapp_pref_setvalue("sheepdrawing_username",liqcell_getcaption(txtusername) );
	liqapp_pref_setvalue("sheepdrawing_password",liqcell_getcaption(txtpassword) );
	liqapp_pref_setvalue("sheepdrawing_thread",  liqcell_getcaption(txtthread) );
 
	liqapp_prefs_save();

    liqcell_propseti(sheepdrawing_configure,"dialog_running",0);
	return 0;
}

/**	
 * sheepdrawing_configure paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int sheepdrawing_configure_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * sheepdrawing_configure dynamic resizing
 */	
static int sheepdrawing_configure_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *label3 = liqcell_child_lookup(self, "label3");
	liqcell *head = liqcell_child_lookup(self, "head");
	liqcell *author = liqcell_child_lookup(self, "author");
	liqcell *slidetext3 = liqcell_child_lookup(self, "slidetext3");
	liqcell *slidetext2 = liqcell_child_lookup(self, "slidetext2");
	liqcell *slidetext1 = liqcell_child_lookup(self, "slidetext1");
	liqcell *txtusername = liqcell_child_lookup(self, "txtusername");
	liqcell *txtpassword = liqcell_child_lookup(self, "txtpassword");
	liqcell *txtthread = liqcell_child_lookup(self, "txtthread");
	liqcell_setrect_autoscale( label3, 14,446, 764,30, sx,sy);
	liqcell_setrect_autoscale( head, 18,0, 780,80, sx,sy);
	liqcell_setrect_autoscale( author, 24,84, 696,48, sx,sy);
	liqcell_setrect_autoscale( slidetext3, 32,352, 250,30, sx,sy);
	liqcell_setrect_autoscale( slidetext2, 26,266, 256,30, sx,sy);
	liqcell_setrect_autoscale( slidetext1, 24,174, 258,30, sx,sy);
	liqcell_setrect_autoscale( txtusername, 308,160, 466,52, sx,sy);
	liqcell_setrect_autoscale( txtpassword, 308,254, 466,52, sx,sy);
	liqcell_setrect_autoscale( txtthread, 308,346, 466,52, sx,sy);
	return 0;
}

/**	
 * sheepdrawing_configure_child_test_seek this function shows how to access members
 */	
	  
static void sheepdrawing_configure_child_test_seek(liqcell *sheepdrawing_configure)
{	  
	liqcell *label3 = liqcell_child_lookup(sheepdrawing_configure, "label3");
	liqcell *head = liqcell_child_lookup(sheepdrawing_configure, "head");
	liqcell *author = liqcell_child_lookup(sheepdrawing_configure, "author");
	liqcell *slidetext3 = liqcell_child_lookup(sheepdrawing_configure, "slidetext3");
	liqcell *slidetext2 = liqcell_child_lookup(sheepdrawing_configure, "slidetext2");
	liqcell *slidetext1 = liqcell_child_lookup(sheepdrawing_configure, "slidetext1");
	liqcell *txtusername = liqcell_child_lookup(sheepdrawing_configure, "txtusername");
	liqcell *txtpassword = liqcell_child_lookup(sheepdrawing_configure, "txtpassword");
	liqcell *txtthread = liqcell_child_lookup(sheepdrawing_configure, "txtthread");
	liqcell *cmdaccept = liqcell_child_lookup(sheepdrawing_configure, "cmdaccept");
}	  
/**	
 * create a new sheepdrawing_configure widget
 */	
liqcell *sheepdrawing_configure_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdrawing_configure", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'sheepdrawing_configure'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering

/*
	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 14, 446, 764, 30);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label3, "open source comes from the heart.  please donate to all projects." );
	liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label3, "textalign", 2 );
	liqcell_propseti(  label3, "textaligny", 2 );
	liqcell_child_append(  self, label3);
 */

	//############################# head:label
	liqcell *head = liqcell_quickcreatevis("head", "label", 18, 0, 780, 80);
	liqcell_setfont(	head, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (58), 0) );
	liqcell_setcaption(head, "sheepdrawing configure" );
	liqcell_propsets(  head, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  head, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  head, "textalign", 0 );
	liqcell_propseti(  head, "textaligny", 0 );
	liqcell_child_append(  self, head);
	//############################# author:label
	liqcell *author = liqcell_quickcreatevis("author", "label", 24, 84, 696, 48);
	liqcell_setfont(	author, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(author, "configure your sheep!" );
	liqcell_propsets(  author, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  author, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  author, "textalign", 0 );
	liqcell_propseti(  author, "textaligny", 0 );
	liqcell_child_append(  self, author);
	//############################# slidetext3:label
	liqcell *slidetext3 = liqcell_quickcreatevis("slidetext3", "label", 32, 352, 250, 30);
	liqcell_setfont(	slidetext3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext3, "thread id" );
	liqcell_propsets(  slidetext3, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext3, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext3, "textalign", 0 );
	liqcell_propseti(  slidetext3, "textaligny", 0 );
	liqcell_child_append(  self, slidetext3);
	//############################# slidetext2:label
	liqcell *slidetext2 = liqcell_quickcreatevis("slidetext2", "label", 26, 266, 256, 30);
	liqcell_setfont(	slidetext2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext2, "talk.maemo.org password" );
	liqcell_propsets(  slidetext2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext2, "textalign", 0 );
	liqcell_propseti(  slidetext2, "textaligny", 0 );
	liqcell_child_append(  self, slidetext2);
	//############################# slidetext1:label
	liqcell *slidetext1 = liqcell_quickcreatevis("slidetext1", "label", 24, 174, 258, 30);
	liqcell_setfont(	slidetext1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(slidetext1, "talk.maemo.org username" );
	liqcell_propsets(  slidetext1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  slidetext1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  slidetext1, "textalign", 0 );
	liqcell_propseti(  slidetext1, "textaligny", 0 );
	liqcell_child_append(  self, slidetext1);
	//############################# txtusername:textbox
	liqcell *txtusername = liqcell_quickcreatevis("txtusername", "textbox", 308, 160, 466, 52);
	liqcell_setfont(	txtusername, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(txtusername, "username" );
	liqcell_propsets(  txtusername, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  txtusername, "backcolor", "rgb(0,0,64)" );
	liqcell_propsets(  txtusername, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  txtusername, "textalign", 0 );
	liqcell_propseti(  txtusername, "textaligny", 0 );
	liqcell_child_append(  self, txtusername);
	//############################# txtpassword:textbox
	liqcell *txtpassword = liqcell_quickcreatevis("txtpassword", "textbox", 308, 254, 466, 52);
	liqcell_setfont(	txtpassword, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(txtpassword, "password" );
	liqcell_propsets(  txtpassword, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  txtpassword, "backcolor", "rgb(0,0,64)" );
	liqcell_propsets(  txtpassword, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  txtpassword, "textalign", 0 );
	liqcell_propseti(  txtpassword, "textaligny", 0 );
    liqcell_propseti(  txtpassword, "textispassword",1);
	liqcell_child_append(  self, txtpassword);
	//############################# txtthread:textbox
	liqcell *txtthread = liqcell_quickcreatevis("txtthread", "textbox", 308, 346, 466, 52);
	liqcell_setfont(	txtthread, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(txtthread, "threadid" );
	liqcell_propsets(  txtthread, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  txtthread, "backcolor", "rgb(0,0,64)" );
	liqcell_propsets(  txtthread, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  txtthread, "textalign", 0 );
	liqcell_propseti(  txtthread, "textaligny", 0 );
	liqcell_child_append(  self, txtthread);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 594, 420, 206, 60);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Save" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);	
	
	
	
	
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/sheepdrawing/media/sheepdrawing_configure_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", sheepdrawing_configure_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", sheepdrawing_configure_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", sheepdrawing_configure_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", sheepdrawing_configure_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", sheepdrawing_configure_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", sheepdrawing_configure_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", sheepdrawing_configure_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", sheepdrawing_configure_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", sheepdrawing_configure_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", sheepdrawing_configure_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", sheepdrawing_configure_dialog_close ,self);
	return self;
}

