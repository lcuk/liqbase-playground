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



extern int hotspot_matchu ;
extern int hotspot_matchv ;
extern int hotspot_matchrange ;

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

	liqimagescan_hotspot_detect(cam2);

	if(hotspot_hitsize>0)
	{
		liqcell *datamap = liqcell_child_lookup(self, "datamap");
		
		liqsketch *infosketch = liqcell_getsketch(datamap);
		
		
		float w = (float)(liqcell_getw(self)*3) * (float)hotspot_hitsize / 70.0;
		float h = (float)(liqcell_geth(self)*3) * (float)hotspot_hitsize / 70.0;
		
		float x = -((270.0 - (float)hotspot_hitx) / 140.0 * 1600.0);
		float y = -((170.0 - (float)hotspot_hity) / 120.0 * 960.0);
		
		//liqapp_log()
		
		
		liqcell_setpos(datamap,(int)x,(int)y);
		//liqcell_setrect(datamap,(int)(x-w/2),(int)(y-h/2),(int)w,(int)h);
		
		
		if(infosketch) infosketch->angle = ((float)hotspot_hitangledeg) *  3.141592654 / 180.0;

	}

		liqcliprect_drawimagecolor(cr, cam2,  0,0,cam2->width,cam2->height,0);
		
		if(0)
		{
			int gx=0,gy=0;
			for(gx=0;gx<=1600;gx+=100)
			{
				int px=gx;//+x;
				liqcliprect_drawlinecolor(cr, px,0,  0,1440,  255,128,128);
			}
			
			for(gy=0;gy<=1440;gy+=100)
			{
				int py=gy;//+y;
				liqcliprect_drawlinecolor(cr, 0,py,  2400,0,  255,128,128);
				
			}

		}












	
	
	liqcliprect_release(cr);
	
	liqcell_setdirty(self,1);
}


/**	
 * invar.refresh
 */	
static int invar_refresh(liqcell *self,liqcellclickeventargs *args, liqcell *liqcam)
{
	liqcell *datamap = liqcell_child_lookup(self, "datamap");
	
			char *t =  liqapp_pref_getvalue_def("invar_surface", "/usr/share/liqbase/invar/media/invar_config.imgsurface.png");
			if(t && *t)
				liqcell_propsets(  datamap, "imagefilename", t );
	liqcell_setimage(datamap,NULL);
	
	liqcell_setdirty(self,1);				

			
	//
	return 0;
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

/**	
 * invar mouse - occurs all the time as you stroke the screen
 */	
static int invar_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	float px = (float)args->mex / (float)liqcell_getw(self);
	float py = (float)args->mey / (float)liqcell_geth(self);
	
	hotspot_matchu = (unsigned char)(255.0*px);
	hotspot_matchv = (unsigned char)(255.0*py);
	
	liqapp_log("hotspot match %d,%d",hotspot_matchu,hotspot_matchv);
	
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
				
				
			if( atoi(liqapp_pref_getvalue_def("invarhidepicture","0")) == 1 )
				liqcell_setvisible(datamap,0);
		
		//	liqsketch *infosketch = liqsketch_newfromfile("/usr/share/liqbase/media/flowx.sketch");
		//	liqcell_setsketch(datamap,infosketch);
			

			
			
			liqcameraface_start(CAM_W,CAM_H,25,cam2,cam_picturetaken,self);

			liqcell_handleradd_withcontext(self, "destroy", invar_destroy ,self);
			liqcell_handleradd_withcontext(self, "refresh", invar_refresh ,self);
			liqcell_handleradd_withcontext(self, "mouse", invar_mouse,self);
		
	}
	return self;
}

