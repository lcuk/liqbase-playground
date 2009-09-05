// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>


#include "osc_onedotzero.h"


//    osc_onedotzero_send_();
		
//#####################################################################
//#####################################################################
//##################################################################### onemove :: by gary birkett
//#####################################################################
//#####################################################################
		
	static int knob_mouse(liqcell *self, liqcellmouseeventargs *args, void *onemove)
	{
        osc_onedotzero_send_menu_repeat_ping_if_required();
        
		liqcell_adjustpos(self,args->mdx,args->mdy);
		
		
							osc_onedotzero_send_touch( liqcell_getx(self),liqcell_gety(self) );
							
		if(args->mez==0)	osc_onedotzero_send_touchoff();
		
		liqcell_child_arrange_nooverlap( liqcell_getlinkparent(self), self );
		
		if(args->mez==0) liqcell_forceinboundparent(self);

		return 1;
	}		
		
		
/**	
 * onemove widget refresh, all params set, present yourself to the user.
 */	
static int onemove_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * onemove dialog_open - the user zoomed into the dialog
 */	
static int onemove_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onemove dialog_close - the dialog was closed
 */	
static int onemove_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    osc_onedotzero_send_menufinished(2);
	return 0;
}
/**	
 * onemove widget shown - occurs once per lifetime
 */	
static int onemove_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onemove mouse - occurs all the time as you stroke the screen
 */	
static int onemove_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemove click - occurs when a short mouse stroke occured
 */	
static int onemove_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemove keypress - the user pressed a key
 */	
static int onemove_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemove keyrelease - the user released a key
 */	
static int onemove_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemove paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
static int onemove_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{
	// big heavy event, use sparingly
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
		liqcell *knob = liqcell_child_lookup(backplane, "knob");
		liqcell *c=liqcell_getlinkchild_visual(backplane);
		while(c)
		{
			if(c!=knob)
			{
				
			}
			c=liqcell_getlinknext_visual(c);
		}
	return 0;
}
/**	
 * onemove dynamic resizing
 */	
static int onemove_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
		liqcell *knob = liqcell_child_lookup(backplane, "knob");
	//liqcell *title = liqcell_child_lookup(self, "title");
	//liqcell *label2 = liqcell_child_lookup(self, "label2");
	//liqcell_setrect_autoscale( label2, 26,54, 762,40, sx,sy);
	//liqcell_setrect_autoscale( title, 0,0, 800,46, sx,sy);
	liqcell_setrect_autoscale( backplane, 0,0, 800,480, sx,sy);
	liqcell_setrect_autoscale( knob, 302,112, 170,118, sx,sy);
	return 0;
}

/**	
 * onemove_child_test_seek this function shows how to access members
 */	
	  
static void onemove_child_test_seek(liqcell *self)
{	  
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
		liqcell *knob = liqcell_child_lookup(backplane, "knob");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
}	  
/**	
 * create a new onemove widget
 */	
liqcell *onemove_create()
{
	liqcell *self = liqcell_quickcreatewidget("onemove", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'onemove'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# backplane:picturebox
	liqcell *backplane = liqcell_quickcreatevis("backplane", "picturebox", 0, 00, 800, 480);
	//liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  backplane, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  backplane, "backcolor", "rgb(64,64,64)" );
	//liqcell_propsets(  backplane, "bordercolor", "rgb(200,100,100)" );
		//############################# knob:label
		liqcell *knob = liqcell_quickcreatevis("knob", "label", 302, 112, 170, 118);
		liqcell_setfont(	knob, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(knob, "Move Me!" );
		liqcell_propsets(  knob, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  knob, "backcolor", "rgb(0,0,128)" );
		//liqcell_propsets(  knob, "bordercolor", "rgb(200,100,100)" );
		liqcell_propseti(  knob, "textalign", 2 );
		liqcell_propseti(  knob, "textaligny", 2 );
		
		liqcell_propsets(  knob, "imagefilename",  "/usr/share/liqbase/onedotzero/media/button_back.png" );
		liqcell_propseti(  knob,  "lockaspect",  0 );
		liqcell_handleradd_withcontext(knob, "mouse", knob_mouse,self );
		liqcell_child_append(  backplane, knob);
	/*	int x;
		for(x=0;x<50;x++)
		{
			//############################# label31:label
			liqcell *label31 = liqcell_quickcreatevis("label31", "label", rand() % 800, rand() % 480, 14, 14);
			//liqcell_setfont(	label31, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
			//liqcell_setcaption(label31, "X" );
			//liqcell_propsets(  label31, "textcolor", "rgb(0,0,0)" );
			liqcell_propsets(  label31, "backcolor", "rgb(255,255,0)" );
			//liqcell_propseti(  label31, "textalign", 2 );
			liqcell_child_append(  backplane, label31);
			
		}
		
		
		
		liqcell_child_arrange_nooverlap( backplane, NULL );
	*/
	
	
			
		
		
	liqcell_child_append(  self, backplane);
/*	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 46);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "onedotzero :: move" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
 */
	 /*
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 26, 54, 762, 40);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label2, "Move the icon around the screen" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,0)" );
	//liqcell_propsets(  label2, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  label2, "textalign", 0 );
	liqcell_child_append(  self, label2);
	*/

	//############################# label3:label
	liqcell *lbllastmessage = liqcell_quickcreatevis("label3", "label", 12, 0, 772, 40);
	liqcell_setfont(	lbllastmessage, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_propsets(  lbllastmessage, "textcolor", "rgb(255,255,0)" );
	//liqcell_propsets(  label3, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  lbllastmessage, "textalign", 0 );
	liqcell_child_append(  self, lbllastmessage);
	
	if(get_osc_onedotzero_lastmsg())
		liqcell_setcaption_printf(lbllastmessage, "Message: %s",get_osc_onedotzero_lastmsg() );
	else
		liqcell_setcaption_printf(lbllastmessage, "No message" );
		
	 
	//############################# nokiapicture1:nokiapicture
	liqcell *nokiapicture1 = liqcell_quickcreatevis("nokiapicture1", "nokiapicture", 652, 438, 130, 24);
	liqcell_child_insert(  self, nokiapicture1);
	 
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", onemove_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", onemove_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", onemove_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", onemove_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", onemove_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", onemove_mouse,self );
	liqcell_handleradd_withcontext(self, "click", onemove_click ,self);
	liqcell_handleradd_withcontext(self, "paint", onemove_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", onemove_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", onemove_dialog_close ,self);
	return self;
}

