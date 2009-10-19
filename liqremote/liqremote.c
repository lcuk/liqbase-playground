// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>


static void liqremote_sendserv(liqcell *liqremote,char *str, ...);
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqremote :: by gary birkett
//#####################################################################
//#####################################################################

int liqremote_manager(liqcell *liqremote);

	static int timer_tick(liqcell *self, liqcellmouseeventargs *args, liqcell *liqremote)
	{
		liqcell_propseti(self,"timerinterval", 32767 );
		liqcell_setenabled(self,0);
		liqremote_connect(liqremote);
		
		return 0;
	}


/**	
 * liqremote widget shown
 */	
static int remote_button_click(liqcell *self,liqcelleventargs *args, liqcell *liqremote)
{
	liqremote_sendserv( liqremote, liqcell_getcaption(self) );
}
		
/**	
 * liqremote widget shown
 */	
static int liqremote_shown(liqcell *self,liqcelleventargs *args, void *context)
{
}
/**	
 * liqremote widget refresh, all params set, present yourself to the user.
 */	
static int liqremote_refresh(liqcell *self,liqcelleventargs *args, void *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
}
/**	
 * liqremote_child_test_seek this function shows how to access members
 */	
	  
void liqremote_child_test_seek(liqcell *self)
{	  
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdfastforward = liqcell_child_lookup(self, "cmdfastforward");
	liqcell *cmdrewind = liqcell_child_lookup(self, "cmdrewind");
	liqcell *cmdplay = liqcell_child_lookup(self, "cmdplay");
	liqcell *cmdvolumemute = liqcell_child_lookup(self, "cmdvolumemute");
	liqcell *cmdvolumeup = liqcell_child_lookup(self, "cmdvolumeup");
	liqcell *cmdvolumedown = liqcell_child_lookup(self, "cmdvolumedown");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
}	  
/**	
 * create a new liqremote widget
 */	
liqcell *liqremote_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqremote", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqremote'"); return NULL;  } 
	
	
	
	liqcell_propsets(self,"server","liquid.zapto.org");
	liqcell_propseti(self,"port",17585);
	
	
	
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 60);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "liqremote" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdfastforward:label
	liqcell *cmdfastforward = liqcell_quickcreatevis("cmdfastforward", "label", 554, 254, 236, 134);
	liqcell_setfont(	cmdfastforward, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdfastforward, ">> Advance 5 Sec" );
	liqcell_propsets(  cmdfastforward, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdfastforward, "backcolor", "xrgb(0,64,0)" );
	liqcell_propseti(  cmdfastforward, "textalign", 2 );
    liqcell_propseti(  cmdfastforward, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdfastforward,"click",remote_button_click,self);
	liqcell_child_append(  self, cmdfastforward);
	//############################# cmdrewind:label
	liqcell *cmdrewind = liqcell_quickcreatevis("cmdrewind", "label", 278, 254, 236, 134);
	liqcell_setfont(	cmdrewind, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdrewind, "<< Rewind 5 Sec" );
	liqcell_propsets(  cmdrewind, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdrewind, "backcolor", "xrgb(0,64,0)" );
	liqcell_propseti(  cmdrewind, "textalign", 2 );
    liqcell_propseti(  cmdrewind, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdrewind,"click",remote_button_click,self);
	liqcell_child_append(  self, cmdrewind);
	//############################# cmdplay:label
	liqcell *cmdplay = liqcell_quickcreatevis("cmdplay", "label", 4, 254, 236, 134);
	liqcell_setfont(	cmdplay, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdplay, "Play/Pause" );
	liqcell_propsets(  cmdplay, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdplay, "backcolor", "xrgb(0,64,64)" );
	liqcell_propseti(  cmdplay, "textalign", 2 );
    liqcell_propseti(  cmdplay, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdplay,"click",remote_button_click,self);
	liqcell_child_append(  self, cmdplay);
	//############################# cmdvolumemute:label
	liqcell *cmdvolumemute = liqcell_quickcreatevis("cmdvolumemute", "label", 554, 82, 236, 134);
	liqcell_setfont(	cmdvolumemute, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdvolumemute, "Volume Mute" );
	liqcell_propsets(  cmdvolumemute, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdvolumemute, "backcolor", "xrgb(0,64,0)" );
	liqcell_propseti(  cmdvolumemute, "textalign", 2 );
    liqcell_propseti(  cmdvolumemute, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdvolumemute,"click",remote_button_click,self);
	liqcell_child_append(  self, cmdvolumemute);
	//############################# cmdvolumeup:label
	liqcell *cmdvolumeup = liqcell_quickcreatevis("cmdvolumeup", "label", 278, 82, 236, 134);
	liqcell_setfont(	cmdvolumeup, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdvolumeup, "Volume Up" );
	liqcell_propsets(  cmdvolumeup, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdvolumeup, "backcolor", "xrgb(0,64,0)" );
	liqcell_propseti(  cmdvolumeup, "textalign", 2 );
    liqcell_propseti(  cmdvolumeup, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdvolumeup,"click",remote_button_click,self);
	liqcell_child_append(  self, cmdvolumeup);
	//############################# cmdvolumedown:label
	liqcell *cmdvolumedown = liqcell_quickcreatevis("cmdvolumedown", "label", 4, 82, 236, 134);
	liqcell_setfont(	cmdvolumedown, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(cmdvolumedown, "Volume Down" );
	liqcell_propsets(  cmdvolumedown, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdvolumedown, "backcolor", "xrgb(0,64,0)" );
	liqcell_propseti(  cmdvolumedown, "textalign", 2 );
    liqcell_propseti(  cmdvolumedown, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdvolumedown,"click",remote_button_click,self);
	liqcell_child_append(  self, cmdvolumedown);
	//############################# label5:label
	liqcell *label5 = liqcell_quickcreatevis("label5", "label", 66, 426, 722, 40);
	liqcell_setfont(	label5, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label5, "connection: ip 10.0.0.1 port 17585" );
	liqcell_propsets(  label5, "textcolor", "rgb(255,255,192)" );
	liqcell_propsets(  label5, "backcolor", "rgb(0,0,128)" );
	liqcell_propseti(  label5, "textalign", 2 );
	liqcell_child_append(  self, label5);


	//############################# timer1:liqtimer
	liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
	// store ourselves on the tag for use later
	// this does feel like a workaround, but hell, it works!
	liqcell_settag(timer1,liqcell_hold(self));
	liqcell_propseti(timer1,"timerinterval", 1 );
	liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
	liqcell_setenabled(timer1,1);
	liqcell_child_insert( self,timer1);


	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd(self, "refresh", liqremote_refresh );
	liqcell_handleradd(self, "shown", liqremote_shown );
	
	return self;
}




//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when liqremote is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"liqremote canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}

int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"liqremote" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"liqremote liqapp_init failed"); }
	 }
	 liqcell *self = liqremote_create();
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}
