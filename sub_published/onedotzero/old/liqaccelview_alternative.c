// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqimage.h>
#include <liqbase/liq_xsurface.h>
#include <liqbase/liqcell_easyhandler.h>

#include "osc_onedotzero.h"


//    osc_onedotzero_send_();

/**	
 * create a new liqaccelview_alternative widget
 */	
liqcell *liqaccelview_alternative_dimension_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqaccelview_alternative_dimension", "form", 600, 100);
	if(!self) {liqapp_log("liqcell error not create 'liqaccelview_alternative_dimension'"); return NULL;  } 
	
	//############################# buttonchannels:commandbutton
	liqcell *knob = liqcell_quickcreatevis("knob", "label", 200,0, 200, 100);
	liqcell_setfont(	knob, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(knob, "90deg" );
	liqcell_propsets(  knob, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  knob, "backcolor", "rgb(0,200,0)" );
    liqcell_propseti(  knob, "textalign",  2 );
    //liqcell_propseti(  knob, "textaligny", 2 );
	liqcell_child_append(  self, knob);
    
    liqcell_propsets(  self, "backcolor", "rgb(100,100,100)" );


    liqcell_propseti(  self, "textalign",  2 );
    liqcell_propseti(  self, "textaligny", 2 );
    
    return self;
}




static int liqaccelview_alternative_nextstep(liqcell *liqaccelview_alternative)
{
    osc_onedotzero_send_menu_repeat_ping_if_required();
    
	//return 0;
	//while(1)
	{
		//liqapp_sleep(50);
		//char buff[256];
		//if(0 == accel_read(buff,sizeof(buff)-1) )
		{
			//liqapp_log("accel: ",buff);
		
			int aax=0;
			int aay=0;
			int aaz=0;
			
			liqaccel_read(&aax,&aay,&aaz);
            
            	
            osc_onedotzero_send_acc(aax,aay,aaz);
	
			
			//liqapp_log("accel: %i,%i,%i",aax,aay,aaz);
			
			
			
			
			// knob is 0..1799
			// knob2 is -1800..0
			
			void doknob(liqcell *dim,int accel,float range)
			{
				float f = ((float)accel) * 90 / 1100.0;
                if(f<-90)f=-90;
                if(f>90)f=90;
				//accel=accel/2;
				//accel=f;
				// accel=0 == 0 deg == knob.x=400 + 0  knob2.x=400+-1800
				
				liqcell *k = liqcell_child_lookup( dim,"knob");
				//liqcell *l = liqcell_child_lookup( dim,"knob2");
				
				liqcell_setpos(k, 200+(f*200/90),0);
                liqcell_forceinboundparent(k);

                
                //liqcell_setcaption_printf(k,"%-4i %-3.3f",accel,f);
                liqcell_setcaption_printf(k,"%3.0f deg",f);
				
			}
			//liqapp_log("%-04d %-04d %-04d",aax,aay,aaz);
			// -983 .. 0 .. 983

			liqcell *bx = liqcell_child_lookup( liqaccelview_alternative,"bx");
			doknob(bx,-aax    ,984);
		
			liqcell *by = liqcell_child_lookup( liqaccelview_alternative,"by");
			doknob(by,aay    ,984);
		
			liqcell *bz = liqcell_child_lookup( liqaccelview_alternative,"bz");
			doknob(bz,-aaz    ,984);
			
			liqcell_setdirty(  liqaccelview_alternative, 1);			
			

		}
		
	}
}




static int liqaccelview_alternative_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{

	//if( liqcell_propgeti(self,"dialog_running",0)==1 )
	{
		liqaccelview_alternative_nextstep((liqcell*)self);
	}
	//else
	{
		// nothing for now...  might show a picture or something..
	}
	//liqapp_log("drawing done");
	return 1;
}


	static int liqaccelview_alternative_mouse(liqcell *self, liqcellmouseeventargs *args, void *liqflow)
    {
		if(args->mcnt==1)
		{
			// starting, allocate and insert a new stroke		
			osc_onedotzero_send_touch(args->mex-args->ox,args->mey-args->oy);
		}
		else
		{
			osc_onedotzero_send_touch(args->mex-args->ox,args->mey-args->oy);

			if(args->mez!=0)
			{
				// carry on				
			}
			else
			{
				// finishing				
				osc_onedotzero_send_touchoff();
			}
		}
		// 20090421_232509 lcuk : make sure we mark ourselves as dirty
		liqcell_setdirty(self,1);
		return 1;
	}


/**	
 * liqaccelview_alternative dialog_close - the dialog was closed
 */	
static int liqaccelview_alternative_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    //osc_onedotzero_send_menufinished(0);
	return 0;
}


/**	
 * create a new liqaccelview_alternative widget
 */	
liqcell *liqaccelview_alternative_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqaccelview_alternative", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqaccelview_alternative'"); return NULL;  } 
	
	//############################# buttonchannels:commandbutton
	//liqcell *buttonchannels = liqcell_quickcreatevis("buttonchannels", "commandbutton", 328, 432, 178, 42);
	//liqcell_setfont(	buttonchannels, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	//liqcell_setcaption(buttonchannels, "list channels" );
	//liqcell_propsets(  buttonchannels, "backcolor", "rgb(235,233,237)" );
	//liqcell_child_append(  self, buttonchannels);
	//############################# buttonback:commandbutton
	//liqcell *buttonback = liqcell_quickcreatevis("buttonback", "commandbutton", 8, 432, 202, 42);
	//liqcell_setfont(	buttonback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	//liqcell_setcaption(buttonback, "Back" );
	//liqcell_propsets(  buttonback, "backcolor", "rgb(235,233,237)" );
	//liqcell_child_append(  self, buttonback);


	
/*
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 66, 8, 728, 40);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "accelerometer test" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 6, 8, 52, 40);
	liqcell_setfont(	icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(icon, "icon" );
	liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);

 */
	//############################# bx:picturebox
	liqcell *bx = liqcell_quickcreatevis("bx", "liqaccelview_alternative_dimension", 100, 60, 600, 100);
	liqcell_setfont(	bx, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
    liqcell_setcaption(bx, "left                              right" );
	//liqcell_propsets(  bx, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  bx, "backcolor", "rgb(200,0,0)" );
	//liqcell_propseti(  bx, "textalign", 2 );
	//liqcell_propseti(  bx, "textaligny",2 );
	//liqcell_propsets(  bx, "bordercolor", "rgb(200,100,100)" );
	liqcell_child_append(  self, bx);
	
	//############################# by:picturebox
	liqcell *by = liqcell_quickcreatevis("by", "liqaccelview_alternative_dimension", 100,190, 600, 100);
	liqcell_setfont(	by, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
    liqcell_setcaption(by, "towards                        away" );

	//liqcell_setfont(	by, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	//liqcell_propsets(  by, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  by, "backcolor", "rgb(0,200,0)" );
	//liqcell_propsets(  by, "bordercolor", "rgb(200,100,100)" );
	//liqcell_propseti(  by, "textalign", 2 );
	//liqcell_propseti(  by, "textaligny",2 );
	
	liqcell_child_append(  self, by);

	//############################# bz:picturebox
	liqcell *bz = liqcell_quickcreatevis("bz", "liqaccelview_alternative_dimension", 100, 320, 600, 100);
	liqcell_setfont(	bz, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
    liqcell_setcaption(bz, "face down                    face up" );
	//liqcell_setfont(	bz, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	//liqcell_propsets(  bz, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  bz, "backcolor", "rgb(0,0,200)" );
	//liqcell_propsets(  bz, "bordercolor", "rgb(200,100,100)" );
	//liqcell_propseti(  bz, "textalign", 2 );
	//liqcell_propseti(  bz, "textaligny",2 );
	liqcell_child_append(  self, bz);

	void colknob(liqcell *b,char *backcol,char *knobcol)
	{
        liqcell_propsets(b,"backcolor",backcol);
		liqcell *knob = liqcell_child_lookup(b,"knob");
		liqcell_propsets(knob,"backcolor",knobcol);
	}
	
	colknob(bx,"xrgba(40,0,0,255)","rgba(200,0,0,205)");
	colknob(by,"xrgba(0,40,0,255)","rgba(0,200,0,205)");
	colknob(bz,"xrgba(0,0,40,255)","rgba(0,0,200,205)");


	liqcell_handleradd_withcontext(self,    "paint",     liqaccelview_alternative_paint,self);
    liqcell_handleradd_withcontext(self,    "mouse",     liqaccelview_alternative_mouse,self);
    liqcell_handleradd_withcontext(self, "dialog_close", liqaccelview_alternative_dialog_close ,self);
	return self;
}



