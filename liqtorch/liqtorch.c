// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqtorch :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqtorch widget refresh, all params set, present yourself to the user.
 */	
static int liqtorch_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqtorch dialog_open - the user zoomed into the dialog
 */	
static int liqtorch_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtorch dialog_close - the dialog was closed
 */	
static int liqtorch_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtorch widget shown - occurs once per lifetime
 */	
static int liqtorch_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtorch mouse - occurs all the time as you stroke the screen
 */	
static int liqtorch_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtorch click - occurs when a short mouse stroke occured
 */	
static int liqtorch_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtorch keypress - the user pressed a key
 */	
static int liqtorch_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtorch keyrelease - the user released a key
 */	
static int liqtorch_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtorch paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqtorch_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqtorch dynamic resizing
 */	
static int liqtorch_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *cmdturnon = liqcell_child_lookup(self, "cmdturnon");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	//liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( cmdturnon, 174,222, 446,162, sx,sy);
	liqcell_setrect_autoscale( label1, 0,74, 800,106, sx,sy);
	//liqcell_setrect_autoscale( title, 0,0, 800,38, sx,sy);
	return 0;
}


/**	
 * liqtorch.cmdturnon clicked
 */	
static int cmdturnon_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqtorch)
{
	liqcell *c = liqcell_quickcreatevis("torch","liqtorch.liqtorch_run",0,0,-1,-1);
	args->newdialogtoopen= c ;
	//liqcell_easyrun(c);
	//liqcell_release(c);
	return 1;
}
/**	
 * liqtorch_child_test_seek this function shows how to access members
 */	
	  
static void liqtorch_child_test_seek(liqcell *self)
{	  
	liqcell *cmdturnon = liqcell_child_lookup(self, "cmdturnon");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *title = liqcell_child_lookup(self, "title");
}	  
/**	
 * create a new liqtorch widget
 */	
liqcell *liqtorch_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqtorch", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqtorch'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# cmdturnon:label
	liqcell *cmdturnon = liqcell_quickcreatevis("cmdturnon", "label", 174, 222, 446, 162);
	liqcell_setfont(	cmdturnon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (43), 0) );
	liqcell_setcaption(cmdturnon, "ON" );
	liqcell_propsets(  cmdturnon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdturnon, "backcolor", "xrgb(0,64,0)" );
    liqcell_propsets(  cmdturnon, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdturnon, "textalign", 2 );
	liqcell_propseti(  cmdturnon, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdturnon, "click", cmdturnon_click, self );
	liqcell_child_append(  self, cmdturnon);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 0, 74, 800, 106);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(label1, "liqtorch will guide you in the dark." );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label1, "textalign", 2 );
	liqcell_child_append(  self, label1);
/*    
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 38);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "liqtorch" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
 */   
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqtorch_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqtorch_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqtorch_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqtorch_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqtorch_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqtorch_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqtorch_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqtorch_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqtorch_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqtorch_dialog_close ,self);
	return self;
}







//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when liqtorch is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"liqtorch canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}

int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"liqtorch" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"liqtorch liqapp_init failed"); }
	 }
	 liqcell *self = liqtorch_create();
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}
