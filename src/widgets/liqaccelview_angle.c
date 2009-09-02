// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqimage.h>
#include <liqbase/liq_xsurface.h>
#include <liqbase/liqcell_easyhandler.h>





static int liqaccelview_angle_nextstep(liqcell *liqaccelview_angle)
{
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
			
			//liqapp_log("accel: %i,%i,%i",aax,aay,aaz);
			
			
			
			
			// knob is 0..1799
			// knob2 is -1800..0
			
			void doknob(liqcell *dim,int accel,float range)
			{
				float f = ((float)accel) * 450.0 / 983.0;
				//accel=accel/2;
				accel=f;
				// accel=0 == 0 deg == knob.x=400 + 0  knob2.x=400+-1800
				
				liqcell *k = liqcell_child_lookup( dim,"knob");
				liqcell *l = liqcell_child_lookup( dim,"knob2");
				
				liqcell_setpos(k, 300+0    +accel,0);
				liqcell_setpos(l, 300+-1800+accel,0);
				
			}
			//liqapp_log("%-04d %-04d %-04d",aax,aay,aaz);
			// -983 .. 0 .. 983

			liqcell *bx = liqcell_child_lookup( liqaccelview_angle,"bx");
			doknob(bx,aax    ,984);
		
			liqcell *by = liqcell_child_lookup( liqaccelview_angle,"by");
			doknob(by,aay    ,984);
		
			liqcell *bz = liqcell_child_lookup( liqaccelview_angle,"bz");
			doknob(bz,-aaz-100-984,984);
			
			liqcell_setdirty(  liqaccelview_angle, 1);			
			

		}
		
	}
}




static int liqaccelview_angle_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{

	if( liqcell_propgeti(self,"dialog_running",0)==1 )
	{
		liqaccelview_angle_nextstep((liqcell*)self);
	}
	else
	{
		// nothing for now...  might show a picture or something..
	}
	//liqapp_log("drawing done");
	return 1;
}


/**	
 * create a new liqaccelview_angle widget
 */	
liqcell *liqaccelview_angle_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqaccelview_angle", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqaccelview_angle'"); return NULL;  } 
	
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
	liqcell *bx = liqcell_quickcreatevis("bx", "angleruler", 100, 60, 600, 100);
	//liqcell_setfont(	bx, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	//liqcell_propsets(  bx, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  bx, "backcolor", "rgb(200,0,0)" );
	//liqcell_propseti(  bx, "textalign", 2 );
	//liqcell_propseti(  bx, "textaligny",2 );
	//liqcell_propsets(  bx, "bordercolor", "rgb(200,100,100)" );
	liqcell_child_append(  self, bx);
	
	//############################# by:picturebox
	liqcell *by = liqcell_quickcreatevis("by", "angleruler", 100,190, 600, 100);
	//liqcell_setfont(	by, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	//liqcell_propsets(  by, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  by, "backcolor", "rgb(0,200,0)" );
	//liqcell_propsets(  by, "bordercolor", "rgb(200,100,100)" );
	//liqcell_propseti(  by, "textalign", 2 );
	//liqcell_propseti(  by, "textaligny",2 );
	
	liqcell_child_append(  self, by);

	//############################# bz:picturebox
	liqcell *bz = liqcell_quickcreatevis("bz", "angleruler", 100, 320, 600, 100);
	//liqcell_setfont(	bz, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	//liqcell_propsets(  bz, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  bz, "backcolor", "rgb(0,0,200)" );
	//liqcell_propsets(  bz, "bordercolor", "rgb(200,100,100)" );
	//liqcell_propseti(  bz, "textalign", 2 );
	//liqcell_propseti(  bz, "textaligny",2 );
	liqcell_child_append(  self, bz);


	liqcell *overlay=liqcell_quickcreatevis("overlay",   "image",   0,0,   800,480 );
	liqcell_setimage(  overlay,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/liqaccelview_angle.overlay.png", 0,0,1) );
	liqcell_propseti(overlay,"lockaspect",0);
	liqcell_child_append( self,overlay);

	void colbar(liqcell *b,char *col)
	{
		liqcell *bar = liqcell_child_lookup(b,"bar");
		liqcell_propsets(bar,"backcolor",col);
	}
	
	colbar(bx,"rgba(255,0,0,255)");
	colbar(by,"rgba(0,255,0,255)");
	colbar(bz,"rgba(0,0,255,255)");



	liqcell_handleradd_withcontext(self,    "paint", liqaccelview_angle_paint,self);
	return self;
}



