#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>



#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqbase.h>

//#####################################################################
//#####################################################################
//##################################################################### floatmap :: by gary birkett
//#####################################################################
//#####################################################################

// september 21 2008: 06:51.30 summatusmentis berlin metro map doesn't help me in rural MN :)




	static void zoomto(liqcell *backplane,float scale)
	{
		// using the central point specified p(xy)
		// zoom the backplane by the specified factor
		// zooming is relative to the original size of the image
		liqcell *par = liqcell_getlinkparent(backplane);
		if(!par) return;
		
		liqimage *img = liqcell_getimage(backplane);
		if(!img) return;

		int neww = img->width  * scale;
		int newh = img->height * scale;
		
		int newx = (backplane->x - (par->w/2))  * neww / backplane->w;
		int newy = (backplane->y - (par->h/2))  * newh / backplane->h;
		
		
		newx += par->w/2;
		newy += par->h/2;
		
		
		//liqcell_setsize(backplane,neww,newh);
		liqcell_setrect(backplane,newx,newy,   neww,newh);

	}


	static int zoom_mouse(liqcell *zoom, liqcellmouseeventargs *args, void *context)
	{
		liqcell *floatmap = liqcell_getbasewidget(zoom);
		if(!floatmap) return 0;
		
		
		//liqapp_log("test: '%s'",floatmap->name);
		
		liqcell *backplane = liqcell_child_lookup( floatmap,"backplane");
		if(!backplane) return 0;
		
		//liqapp_log("mouse d %3i,%3i  e %3i,%3i   ez=%3i",args->mdx,args->mdy,args->mex,args->mey,args->mez);
		liqcell *knob = liqcell_child_lookup( zoom,"knob");
		if(knob)
		{
			liqcell_setpos( knob, liqcell_getx(knob), args->mey );
			liqcell_forceinboundparent(knob);
			
			float upto = ((float)knob->y) / ((float)(zoom->h-knob->h));
			
			
			float scale = 1 + (upto * 3);
			
			
			zoomto(backplane,scale);
			
		}
		return 1;
	}

	static int floatmap_backplane_paint(liqcell *zoom, liqcellpainteventargs *args, void *context)
	{
		//
		
		
		return 0;
	}
liqcell *floatmap_create()
{
	liqcell *self = liqcell_quickcreatewidget("floatmap","form", 800,480);
	// floatmap
	// floatmap.backplane
	// floatmap.zoom
	// floatmap.zoom.knob
	
	if(self)
	{

		//################################################ create the map backplane
		liqcell *c = liqcell_quickcreatevis("backplane",   "picture",   0,0,800,480    );
		liqcell_propseti(c,"lockaspect",0);
		liqcell_propseti(c,"autosize",1);
		liqcell_propseti(c,"imageallowalpha",0);
		liqcell_propsets(c,"imagefilename","media/manchester map.png");
		
		//liqcell_propsets(c,"imagefilename","media/fish.jpg");
		// Mon Apr 06 01:59:19 2009 lcuk : first test of the automatic kinetics :)
		liqcell_handleradd(c,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_insert( self, c );

		//################################################ create the zoom slider
		liqcell *z = liqcell_quickcreatevis("zoom",   "picture",   0,0,100,480    );
		liqcell_propseti(z,"lockaspect",0);
		liqcell_handleradd(z,    "mouse",   zoom_mouse);
		liqcell_child_insert( self, z );

			//################################################ create the zoom knob
			liqcell *zi = liqcell_quickcreatevis("knob",   "picture",   0,0,100,48    );
			liqcell_propseti(zi,"lockaspect",0);
			liqcell_propsets(zi,"imagefilename","media/blob.png");
			liqcell_child_insert( z, zi );

	}

	return self;
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>



#include "liqcell.h"
#include "liqcell_easyrun.h"
#include "liqcell_easyhandler.h"
#include "liqbase.h"

//#####################################################################
//#####################################################################
//##################################################################### floatmap :: by gary birkett
//#####################################################################
//#####################################################################

// september 21 2008: 06:51.30 summatusmentis berlin metro map doesn't help me in rural MN :)




	static void zoomto(liqcell *backplane,float scale)
	{
		// using the central point specified p(xy)
		// zoom the backplane by the specified factor
		// zooming is relative to the original size of the image
		liqcell *par = liqcell_getlinkparent(backplane);
		if(!par) return;
		
		liqimage *img = liqcell_getimage(backplane);
		if(!img) return;

		int neww = img->width  * scale;
		int newh = img->height * scale;
		
		int newx = (backplane->x - (par->w/2))  * neww / backplane->w;
		int newy = (backplane->y - (par->h/2))  * newh / backplane->h;
		
		
		newx += par->w/2;
		newy += par->h/2;
		
		
		//liqcell_setsize(backplane,neww,newh);
		liqcell_setrect(backplane,newx,newy,   neww,newh);

	}


	static int zoom_mouse(liqcell *zoom, liqcellmouseeventargs *args, void *context)
	{
		liqcell *floatmap = liqcell_getbasewidget(zoom);
		if(!floatmap) return 0;
		
		
		//liqapp_log("test: '%s'",floatmap->name);
		
		liqcell *backplane = liqcell_child_lookup( floatmap,"backplane");
		if(!backplane) return 0;
		
		//liqapp_log("mouse d %3i,%3i  e %3i,%3i   ez=%3i",args->mdx,args->mdy,args->mex,args->mey,args->mez);
		liqcell *knob = liqcell_child_lookup( zoom,"knob");
		if(knob)
		{
			liqcell_setpos( knob, liqcell_getx(knob), args->mey );
			liqcell_forceinboundparent(knob);
			
			float upto = ((float)knob->y) / ((float)(zoom->h-knob->h));
			
			
			float scale = 1 + (upto * 3);
			
			
			zoomto(backplane,scale);
			
		}
		return 1;
	}


liqcell *floatmap_create()
{
	liqcell *self = liqcell_quickcreatewidget("floatmap","form", 800,480);
	// floatmap
	// floatmap.backplane
	// floatmap.zoom
	// floatmap.zoom.knob
	
	if(self)
	{

		//################################################ create the map backplane
		liqcell *c = liqcell_quickcreatevis("backplane",   "picture",   0,0,1919,1981    );
		liqcell_propseti(c,"lockaspect",0);
		liqcell_propseti(c,"autosize",1);
		liqcell_propseti(c,"imageallowalpha",0);
		liqcell_propsets(c,"imagefilename","media/manchester map.png");
		
		//liqcell_propsets(c,"imagefilename","media/fish.jpg");
		// Mon Apr 06 01:59:19 2009 lcuk : first test of the automatic kinetics :)
		liqcell_handleradd(c,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_insert( self, c );

		//################################################ create the zoom slider
		liqcell *z = liqcell_quickcreatevis("zoom",   "picture",   0,0,100,480    );
		liqcell_propseti(z,"lockaspect",0);
		liqcell_handleradd(z,    "mouse",   zoom_mouse);
		liqcell_child_insert( self, z );

			//################################################ create the zoom knob
			liqcell *zi = liqcell_quickcreatevis("knob",   "picture",   0,0,100,48    );
			liqcell_propseti(zi,"lockaspect",0);
			liqcell_propsets(zi,"imagefilename","/media/mmc1/svn/liqbase/libliqbase/media/blob.png");
			liqcell_child_insert( z, zi );

	}

	return self;
}
 */

