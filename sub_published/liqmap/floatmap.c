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


	static int widget_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
	{
        //liqapp_log("mouse a %i,%i    ez=%i",args->mdx,args->mdy,args->mez);
		liqcell *body = self;//liqcell_child_lookup( self,"backplane");
		liqcell *par = liqcell_getlinkparent(self);
		if(body && par && par->h)
        {
            
			if( (args->mcnt == 1) )
			{
				// make sure we stop kinetic scrolling when we get a mouse event
				liqcell_setkinetic(body, 0,0 );
			}
			int mdx=0;
			int mdy=0;
			if(body->w>par->w || body->x!=0)mdx=args->mdx;
			if(body->h>par->h || body->y!=0)mdy=args->mdy;

			liqcell_adjustpos(body,mdx,mdy);
			if(body->w>par->w || body->x!=0)
			{
				if(body->x>0) body->x=0;
				int bb=body->x+body->w;
				if(body->w>par->w && bb < par->w) body->x=par->w-body->w;
			}
			if(body->h>par->h || body->y!=0)
			{
				if(body->y>0) body->y=0;
				int bb=body->y+body->h;

				if(body->h>par->h && bb < par->h) body->y=par->h-body->h;
			}
			//liqapp_log("kinetic mouse d %i,%i    ez=%i    %i,%i",args->mdx,args->mdy,args->mez    ,args->stroke->pointlast->x,args->stroke->pointlast->y  );
			if( (args->mez == 0) )
			{
				// x11 lets me know motion in a different event to mouseup
				// so i always have a stroke that finishes moving and then indicates release
				// so i have to examine the stroke from the end
				// if the last point and its neighbour are identical i can try one further back
				liqstroke *stroke = args->stroke;
				liqpoint *p1=NULL;
				liqpoint *p2=NULL;
				
						p1 = stroke->pointlast;
				if(p1)	p2 = p1->linkprev;
				
				
				if(p1 && p2 && p1->x==p2->x && p1->y==p2->y)
				{
					// now replease p2 with the previous one again
						p2 = p2->linkprev;
				}
				if(p1 && p2 && p1->x==p2->x && p1->y==p2->y)
				{
					// now replease p2 with the previous one again
						p2 = p2->linkprev;
				}
				
				if(p1 && p2)
				{
					// now finally obtain the delta
					mdx=0;
					mdy=0;
					if(body->w>par->w || body->x!=0) mdx = p1->x-p2->x;
					if(body->h>par->h || body->y!=0) mdy = p1->y-p2->y;
					liqcell_setkinetic(body, mdx, mdy );
				}
			}
		}
		

		return 1;
	}



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
        
        
        char *mapfn = liqapp_pref_getvalue_def("floatmap.url","http://liqbase.net/manchestermap.png");
                
        
		liqcell_propsets(c,"imagefilename",mapfn);
		
		//liqcell_propsets(c,"imagefilename","media/fish.jpg");
		// Mon Apr 06 01:59:19 2009 lcuk : first test of the automatic kinetics :)
		//liqcell_handleradd(c,    "mouse",   liqcell_easyhandler_kinetic_mouse );
        
        // Mon Aug 31 16:37:09 2009 lcuk : removed again for a mo, cos its doing silly things
		liqcell_handleradd(c,    "mouse",   widget_mouse );
		liqcell_child_append( self, c );

		//################################################ create the zoom slider
		liqcell *z = liqcell_quickcreatevis("zoom",   "picture",   0,0,100,480    );
		liqcell_propseti(z,"lockaspect",0);
		liqcell_handleradd(z,    "mouse",   zoom_mouse);
		liqcell_child_append( self, z );

			//################################################ create the zoom knob
			liqcell *zi = liqcell_quickcreatevis("knob",   "picture",   0,0,100,48    );
			liqcell_propseti(zi,"lockaspect",0);
			liqcell_propsets(zi,"imagefilename","/usr/share/liqbase/media/zoom.png");
			liqcell_child_append( z, zi );

	}

	return self;
}

