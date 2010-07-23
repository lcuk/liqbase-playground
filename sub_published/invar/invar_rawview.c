// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
#include <liqbase/liqcameraface.h>
		


//int  liqcamera_start(int argCAMW,int argCAMH,int argCAMFPS,liqimage * argCAMdestimage,void (*argCAMUpdateCallback)() );
//void liqcamera_stop();

//liqimage * liqcamera_getimage(); // return the current image of this camera, if NULL camera is switched off




//#####################################################################
//#####################################################################
//##################################################################### invar_rawview :)
//#####################################################################
//#####################################################################




extern int hotspot_hitx ;
extern int hotspot_hity ;
extern int hotspot_hitsize ;
extern int hotspot_hitangledeg ;

int liqimagescan_hotspot_detect(liqimage *self);






static void cam_picturetaken(void *CAMtag)
{

	liqcell *self = (liqcell *)CAMtag;
	liqcell *camholder= liqcell_child_lookup( self,"camholder");
	
	// new, copy quickly and store
	liqimage *cam = liqcell_getimage(self);
	liqimage *cam2 = liqcell_getimage(camholder);

	liqcliprect *cr = liqcliprect_newfromimage(cam);
	

//	liqimage_find_shapes(cam2);	// hold breath

	liqimagescan_hotspot_detect(cam);

	if(hotspot_hitsize>0)
	{
		liqcell *datamap = liqcell_child_lookup(self, "datamap");
		
		float x = -((270.0 - (float)hotspot_hitx) / 140.0 * 1600.0);
		float y = -((170.0 - (float)hotspot_hity) / 120.0 * 960.0);
		//float w = (float)(liqimage_getwidth(datamap)) * (float)hotspot_hitsize / 20.0;
		//float h = (float)(liqimage_getheight(datamap)) * (float)hotspot_hitsize / 20.0;
		
		
		liqcell_setpos(datamap,(int)x,(int)y);
	}









	liqcliprect_drawimagecolor(cr, cam2,  0,0,cam2->width,cam2->height,0);
	
	liqcliprect_release(cr);
	
	liqcell_setdirty(self,1);
}




/**	
 * invar.destroy
 */	
static int invar_destroy(liqcell *self,liqcellclickeventargs *args, liqcell *liqcam)
{
	// we must stop the camera!
	// technically we could change this to:
	// we should decrement the counter of users of this camera source
	// that way, multiple apps can see the same data
	liqapp_log("invar_destroy hmm1");
	liqcameraface_stop();
	liqapp_log("invar_destroy hmm2");
	return 0;
}
	

liqcell *invar_rawview_create()
{

//int  liqcamera_start(int argCAMW,int argCAMH,int argCAMFPS,liqimage * argCAMdestimage,void (*argCAMUpdateCallback)() );
//void liqcamera_stop();



	liqcell *self = liqcell_quickcreatewidget("invar_rawview","form", 800,480);
	
	if(self)
	{

		const int CAM_W = 320;
		const int CAM_H = 240;
		
		//liqcell *c = self;//liqsketchedit_create("content",  0,120,  CAM_W,CAM_H);// 800,380 );
			

			liqimage *cam = liqimage_new();
			liqimage_pagedefine(cam,CAM_W,CAM_H,225,225,0);
			
			liqcell_setimage(self,cam);
			
			liqcell_propseti(self,"lockaspect",0);
	
			liqimage *cam2 = liqimage_new();
			liqimage_pagedefine(cam2,CAM_W,CAM_H,225,225,0);
	
			liqcell *camholder = liqcell_quickcreatevis("camholder","image",  0,0,10,10 );
			liqcell_setimage(camholder,cam2);
			liqcell_setvisible(camholder,0);
			liqcell_child_append( self, camholder );


			liqcell *datamap = liqcell_quickcreatevis("datamap","image",  0,0,800*3,480*3 );
			liqcell_propseti(datamap,"lockaspect",0);
			liqcell_child_append( self, datamap );
			char *t =  liqapp_pref_getvalue_def("invar_surface", "/usr/share/liqbase/invar/media/invar_config.imgsurface.png");
			if(t && *t)
				liqcell_propsets(  datamap, "imagefilename", t );

			
			
			liqcameraface_start(CAM_W,CAM_H,25,cam2,cam_picturetaken,self);

			liqcell_handleradd_withcontext(self, "destroy", invar_destroy ,self);
		
	}
	return self;
}

