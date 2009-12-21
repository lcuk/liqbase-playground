// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### colorpicker :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * colorpicker widget refresh, all params set, present yourself to the user.
 */	
static int colorpicker_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * colorpicker dialog_open - the user zoomed into the dialog
 */	
static int colorpicker_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * colorpicker dialog_close - the dialog was closed
 */	
static int colorpicker_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * colorpicker widget shown - occurs once per lifetime
 */	
static int colorpicker_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * colorpicker mouse - occurs all the time as you stroke the screen
 */	
static int colorpicker_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * colorpicker click - occurs when a short mouse stroke occured
 */	
static int colorpicker_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * colorpicker keypress - the user pressed a key
 */	
static int colorpicker_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * colorpicker keyrelease - the user released a key
 */	
static int colorpicker_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * colorpicker paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int colorpicker_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * colorpicker dynamic resizing
 */	
static int colorpicker_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *greycube1 = liqcell_child_lookup(self, "greycube1");
	liqcell *colorcube1 = liqcell_child_lookup(self, "colorcube1");
	liqcell *picture1 = liqcell_child_lookup(self, "picture1");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *colorhead = liqcell_child_lookup(self, "colorhead");
	liqcell_setrect_autoscale( colorcube1, 10,104, 366,322, sx,sy);
	liqcell_setrect_autoscale( picture1, 504,104, 290,322, sx,sy);
	liqcell_setrect_autoscale( label2, 504,66, 292,36, sx,sy);
	liqcell_setrect_autoscale( label1, 382,66, 116,36, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 556,432, 206,48, sx,sy);
	liqcell_setrect_autoscale( colorhead, 8,66, 368,36, sx,sy);
	liqcell_setrect_autoscale( greycube1, 382,104, 116,322, sx,sy);
	return 0;
}


/**	
 * colorcube mouse - occurs all the time as you stroke the screen
 */	
static int colorcube_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *colorpicker)
{
	liqcell *greycube1 = liqcell_child_lookup(colorpicker, "greycube1");
	liqcell *colorcube1 = liqcell_child_lookup(colorpicker, "colorcube1");
	liqcell *picture1 = liqcell_child_lookup(colorpicker, "picture1");
	// the grey cube has been touched
	// we must ensure the colorcube shine is set to the grey value we hit
	
//int		vgraph_pget(       				vgraph *self, int x, int y, unsigned char *grey,unsigned char *u,unsigned char *v);

	int px = args->mex;// - args->ox;
	int py = args->mey;// - args->oy;

	unsigned char cy=0;
	unsigned char cu=0;
	unsigned char cv=0;
	
	vgraph_pget( args->graph, px,py, &cy,&cu,&cv );
	
	//liqcell_propseti(colorcube1,"colorcube_brightness",cy);
	liqcell_setdirty(colorcube1,1);
	
	char buf[64];
	snprintf(buf,sizeof(buf),"yuv(%i,%i,%i)",cy,cu,cv);
	
	liqcell_propsets(  picture1, "backcolor",buf);

	return 0;
}

/**	
 * greycube mouse - occurs all the time as you stroke the screen
 */	
static int greycube_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *colorpicker)
{
	liqcell *greycube1 = liqcell_child_lookup(colorpicker, "greycube1");
	liqcell *colorcube1 = liqcell_child_lookup(colorpicker, "colorcube1");
	liqcell *picture1 = liqcell_child_lookup(colorpicker, "picture1");
	// the grey cube has been touched
	// we must ensure the colorcube shine is set to the grey value we hit
	
//int		vgraph_pget(       				vgraph *self, int x, int y, unsigned char *grey,unsigned char *u,unsigned char *v);

	int px = args->mex;// - args->ox;
	int py = args->mey;// - args->oy;

	unsigned char cy=0;
	unsigned char cu=0;
	unsigned char cv=0;
	
	vgraph_pget( args->graph, px,py, &cy,&cu,&cv );
	
	liqcell_propseti(colorcube1,"colorcube_brightness",cy);
	liqcell_setdirty(colorcube1,1);
	
	char buf[64];
	snprintf(buf,sizeof(buf),"yuv(%i,128,128)",cy);
	liqcell_propsets(  picture1, "backcolor",buf);
	return 0;
}

/**	
 * colorpicker.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *colorpicker)
{
	liqcell *greycube1 = liqcell_child_lookup(colorpicker, "greycube1");
	liqcell *colorcube1 = liqcell_child_lookup(colorpicker, "colorcube1");
	liqcell *picture1 = liqcell_child_lookup(colorpicker, "picture1");

	char *t = liqcell_propgets(picture1,"backcolor",NULL);
	if(t && *t)
	{
		liqcell_propsets(colorpicker,"colorselected",t);
	}
	

    liqcell_propseti(colorpicker,"dialog_running",0);

	return 0;
}
/**	
 * colorpicker_child_test_seek this function shows how to access members
 */	
	  
static void colorpicker_child_test_seek(liqcell *colorpicker)
{	  
	liqcell *greycube1 = liqcell_child_lookup(colorpicker, "greycube1");
	liqcell *colorcube1 = liqcell_child_lookup(colorpicker, "colorcube1");
	liqcell *picture1 = liqcell_child_lookup(colorpicker, "picture1");
	liqcell *label2 = liqcell_child_lookup(colorpicker, "label2");
	liqcell *label1 = liqcell_child_lookup(colorpicker, "label1");
	liqcell *title = liqcell_child_lookup(colorpicker, "title");
	liqcell *cmdaccept = liqcell_child_lookup(colorpicker, "cmdaccept");
	liqcell *colorhead = liqcell_child_lookup(colorpicker, "colorhead");
}	  
/**	
 * create a new colorpicker widget
 */	
liqcell *colorpicker_create()
{
	liqcell *self = liqcell_quickcreatewidget("colorpicker", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'colorpicker'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# greycube1:greycube
	liqcell *greycube1 = liqcell_quickcreatevis("greycube1", "greycube", 382, 104, 116, 322);
	liqcell_handleradd_withcontext(greycube1, "mouse", greycube_mouse,self );

	liqcell_child_append(  self, greycube1);
	//############################# colorcube1:colorcube
	liqcell *colorcube1 = liqcell_quickcreatevis("colorcube1", "colorcube", 10, 104, 366, 322);
	liqcell_handleradd_withcontext(colorcube1, "mouse", colorcube_mouse,self );
	liqcell_child_append(  self, colorcube1);
	//############################# picture1:picturebox
	liqcell *picture1 = liqcell_quickcreatevis("picture1", "picturebox", 504, 104, 290, 322);
	liqcell_setfont(	picture1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  picture1, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  picture1, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  picture1, "bordercolor", "rgb(255,255,255)" );
	liqcell_child_append(  self, picture1);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 504, 66, 292, 36);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label2, "Selected" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label2, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  label2, "textalign", 0 );
	liqcell_propseti(  label2, "textaligny", 0 );
	liqcell_child_append(  self, label2);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 382, 66, 116, 36);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label1, "Brightness" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_propseti(  label1, "textaligny", 0 );
	liqcell_child_append(  self, label1);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Colour selection" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 556, 432, 206, 48);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Select" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# colorhead:label
	liqcell *colorhead = liqcell_quickcreatevis("colorhead", "label", 8, 66, 368, 36);
	liqcell_setfont(	colorhead, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(colorhead, "Colour" );
	liqcell_propsets(  colorhead, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  colorhead, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  colorhead, "textalign", 0 );
	liqcell_propseti(  colorhead, "textaligny", 0 );
	liqcell_child_append(  self, colorhead);
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", colorpicker_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", colorpicker_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", colorpicker_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", colorpicker_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", colorpicker_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", colorpicker_mouse,self );
	liqcell_handleradd_withcontext(self, "click", colorpicker_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", colorpicker_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", colorpicker_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", colorpicker_dialog_close ,self);
	return self;
}

