

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>




	
//#####################################################################
//#####################################################################
//##################################################################### liqimage :: by gary birkett :)
//#####################################################################
//#####################################################################


	static int liqimage_dialog_open(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqapp_log("dialog_open");
		return 1;
	}


	static int liqimage_dialog_close(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqapp_log("dialog_close");
		return 1;
	}

	//############################################################################################

	static int liqimage_undo_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("undo_click");
		return 1;
	}


	static int liqimage_clear_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("clear_click");
		return 1;
	}

	static int liqimage_del_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("del_click");
		return 1;
	}

	static int liqimage_save_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("save_click");
		return 1;
	}

	static int liqimage__cmdnull_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		// empty mouse handler so we dont draw behind the buttons..
		return 1;
	}
	

	
	//############################################################################################
			
		
		
	static int liqimage_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		liqapp_log("general mouse mex==%i, mey==%i, mez==%i",args->mex,args->mey,args->mez);
		return 1;
	}


	static int liqimage_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("general click");
		args->newdialogtoopen = self;
		return 1;
	}



	static int liqimage_keypress(liqcell *self, liqcellkeyeventargs *args, void *context)
	{
		liqapp_log("general key");
		return 1;
	}
	
	

	static int liqimage_resize(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqapp_log("general resize");
		
		liqcell *overlay = liqcell_child_lookup(self,"editoverlay");
		liqcell *undo = liqcell_child_lookup(overlay,"undo");
		liqcell *clear = liqcell_child_lookup(overlay,"clear");
		liqcell *save = liqcell_child_lookup(overlay,"save");
		liqcell *del = liqcell_child_lookup(overlay,"del");
		
		int ww=liqcell_getw(self);
		int hh=liqcell_geth(self);
		liqcell_setrect(overlay, 0,       0,        ww    ,hh);		
		liqcell_setrect(undo,    ww*0.9,  0,        ww*0.1,hh*0.3);
		liqcell_setrect(clear,   ww*0.9,  hh*0.3,   ww*0.1,hh*0.3);
		liqcell_setrect(save ,   ww*0.9,  hh*0.6,   ww*0.1,hh*0.3);
		liqcell_setrect(del ,    ww*0.9,  hh*0.9,   ww*0.1,hh*0.1);
		return 0;
	}
	

	//############################################################################################



liqcell *liqimage_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqimage","form", 800,480);

	if(self)
	{
		liqcell *overlay = liqcell_quickcreatewidget("editoverlay","overlay", 800,480);
	
			liqcell *b;
	
			b = liqcell_quickcreatevis("undo","button",  800-180,20,   160,160 );
			liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
			liqcell_propsets(  b,    	"backcolor", "rgb(100,0,100)" );
			liqcell_handleradd(b,    	"click",     liqimage_undo_click);
			liqcell_handleradd(b,    	"mouse",     liqimage__cmdnull_mouse);
			liqcell_child_insert( overlay, b );
	
			b = liqcell_quickcreatevis("clear","button",  800-180,20,   160,160 );
			liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
			liqcell_propsets(  b,    	"backcolor", "rgb(0,0,100)" );
			liqcell_handleradd(b,    	"click",     liqimage_clear_click);
			liqcell_handleradd(b,    	"mouse",     liqimage__cmdnull_mouse);
			liqcell_child_insert( overlay, b );
	
			b = liqcell_quickcreatevis("save","button",  800-180,200,   160,160 );
			liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
			liqcell_propsets(  b,    	"backcolor", "rgb(0,100,0)" );
			liqcell_handleradd(b,    	"click",     liqimage_save_click);
			liqcell_handleradd(b,    	"mouse",     liqimage__cmdnull_mouse);
			liqcell_child_insert( overlay, b );
	
			b = liqcell_quickcreatevis("del","button",  800-180,200,   160,160 );
			liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
			liqcell_propsets(  b,    	"backcolor", "rgb(100,0,0)" );
			liqcell_handleradd(b,    	"click",     liqimage_del_click);
			liqcell_handleradd(b,    	"mouse",     liqimage__cmdnull_mouse);
			liqcell_child_insert( overlay, b );
			
		liqcell_child_insert( self, overlay );

		liqimage_resize(self,NULL, NULL);

		liqcell_handleradd(self,    "keypress",      liqimage_keypress);
		liqcell_handleradd(self,    "mouse",         liqimage_mouse);
		liqcell_handleradd(self,    "click",         liqimage_click);
		liqcell_handleradd(self,    "resize",        liqimage_resize);

		liqcell_handleradd(self,    "dialog_open",   liqimage_dialog_open);
		liqcell_handleradd(self,    "dialog_close",  liqimage_dialog_close);
		
		
	}
	return self;

}
