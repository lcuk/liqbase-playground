

// home: http://mt3.google.com/mt/v=w2.92&hl=en&x=4047&y=2648&z=13&s=Galil


// 20090502_155804 lcuk : ooops banned from google maps lol
// 20090502_214211 lcuk : kot says adjust the galil portion of the url  - drop or increase letters

#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>

//#####################################################################
//#####################################################################
//##################################################################### liqmap2 :: by gary birkett
//#####################################################################
//#####################################################################

liqcell *onetile(liqcell *backplane,int x,int y)
{
	char buff[1024];
	snprintf(buff,sizeof(buff),"http://mt3.google.com/mt/v=w2.92&hl=en&x=%i&y=%i&z=13&s=Galile",x+4045,y+2649 );




	
		//############################# tile:tile
		liqcell *tile = liqcell_quickcreatevis("tile", "tile", x*256,y*256,256,256);
		//liqcell_setfont(   tile, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_setcaption(tile, "icon" );
		//liqcell_propsets(  tile, "textcolor", "rgb(255,255,255)" );
		//liqcell_propsets(  tile, "backcolor", "rgb(0,0,0)" );
		liqcell_propsets(  tile, "bordercolor", "rgb(200,100,100)" );
		//liqcell_propseti(  tile, "autosize", 1 );
		//liqcell_propseti(  tile, "textalign", 2 );
		
		
		
		// 20090502_155817 lcuk : banned from google maps..
		// 20090502_155826 lcuk : blocking the assigning of filename for now..
		//liqcell_propsets(  tile, "imagefilename", buff );

		liqcell_child_append(  backplane, tile);

	return tile;
}



liqcell *liqmap2_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqmap2","form", 800,480);

	if(self)
	{
		
		liqcell_propsets(  self, "bordercolor", "rgb(100,255,100)" );
		
		//liqcell *backplane = liqcell_quickcreatevis("backplane", "label", 0,0,268435456,268435456);		// 2^28
		liqcell *backplane = liqcell_quickcreatevis("backplane", "label", 0,0,5000,5000);		// 2^28
		liqcell_child_append(  self, backplane);
		
		
		int x=0;
		int y=0;
		for(x=4045;x<4049;x++)
		{
			for(y=2646;y<2649;y++)
			{
		//		onetile(backplane,x,y);
			}
		}
		for(x=0;x<20;x++)
		{
			for(y=0;y<20;y++)
			{
				onetile(backplane,x,y);
			}
		}
		
		//liqcell_setpos(backplane, -4045*256,-2649*256);
		
		liqcell_handleradd(backplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );

		
	}
	return self;
}
