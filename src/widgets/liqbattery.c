#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqimage.h>
#include <liqbase/liq_xsurface.h>

//		inline void xsurface_drawrectwash_uv(   liqimage *surface,int x,int y,int w,int h, unsigned char u,unsigned char v);

//#####################################################################
//#####################################################################
//##################################################################### liqbattery :: by gary birkett :)
//#####################################################################
//#####################################################################


// 20090526_022907 lcuk : this is a static image at this time
// 20090526_022916 lcuk : i have contacted the author of this demo but not
// http://vector.tutsplus.com/tutorials/illustration/how-to-create-a-transparent-battery-icon/

	static int widget_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
	{
		int xx = liqcell_propgeti(self,"batterycharge",0);
		
		liqimage *img = liqcell_getimage(self);
		if( img)
		{
			// color changing!
			xsurface_drawrectwash_uv(img,0,0,img->width,img->height, xx , 20);
		}
		
		xx = (xx+4) % 255;
		liqcell_propseti(self,"batterycharge",xx );
		

		return 1;
	}
		
liqcell *liqbattery_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqbattery","form", 800,480);

	if(self)
	{
		
	
		
		liqimage *img = liqimage_newfromfile( "media/liqbattery.png",0,0,1);		
		liqcell_propseti(self,"lockaspect",1);
		liqcell_setimage(  self,img );
		
		liqcell_propseti(self,"batterycharge",160 );
		
		liqcell_handleradd_withcontext(self,    "paint", widget_paint,self);
	}
	return self;
}

