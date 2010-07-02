
//int  liqcamera_start(int argCAMW,int argCAMH,int argCAMFPS,liqimage * argCAMdestimage,void (*argCAMUpdateCallback)() );
//void liqcamera_stop();

//liqimage * liqcamera_getimage(); // return the current image of this camera, if NULL camera is switched off

#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>


// /usr/share/icons/hicolor/40x40/hildon/qgn_stat_battery_full100.png
// /usr/share/icons/hicolor/40x40/hildon/qgn_stat_battery_full75.png
// /usr/share/icons/hicolor/40x40/hildon/qgn_stat_battery_full50.png
// /usr/share/icons/hicolor/40x40/hildon/qgn_stat_battery_full25.png

// /usr/share/icons/hicolor/40x40/hildon/qgn_stat_displaybright1.png


//#####################################################################
//#####################################################################
//##################################################################### liqcam :: for ciroip :)
//#####################################################################
//#####################################################################


/*
	static int widget_mouse(liqcell *self, liqcellmouseeventargs *args)
	{
		
		char buf[80];
		fmt_time(buf,80);
		liqcell *c=liqcell_local_lookup( self,"time");
		if(c)
		{
			liqcell_setpos(c,args->mex,args->mey);
			liqcell_setcaption(  c , buf);
		}
		if(args->mcnt>1)return;
		return 0;
	}

 */







	
	
	static liqcell *uititlebar_create(char *key,char *title,char *description)
	{
		
		liqcell *self = liqcell_quickcreatewidget(key,"section", 800,100);
		
		if(self)
		{
			liqcell_propsets(  self,  "backcolor", "rgb(0,0,0)" );
			
			//texturestrip_blu.jpg
			liqcell_setimage(  self,  liqimage_cache_getfile( "../media/texturestrip_dark.jpg",0,0,0) );
			
			liqcell_child_append( self, liqcell_quickcreatevis("app_icon",   "icon",    5   ,10  ,    90, 80 )    );
			liqcell_child_append( self, liqcell_quickcreatevis("app_title",  "label",   100 ,0  ,   700, 55 )    );
			liqcell_child_append( self, liqcell_quickcreatevis("app_desc",   "label",   100 ,55 ,   700, 40 )    );
	
			liqcell_setimage(  liqcell_child_lookup( self,"app_icon"),  liqimage_cache_getfile( "../media/sun.png",0,0,1) );
			liqcell_setfont(   liqcell_child_lookup( self,"app_title"), liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (40), 0) );
			liqcell_setfont(   liqcell_child_lookup( self,"app_desc"),  liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (18), 0) );
	
	
			liqcell_propsets(  liqcell_child_lookup( self,"app_title"), "textcolor", "rgb(255,255,255)" );
			liqcell_propsets(  liqcell_child_lookup( self,"app_desc"),  "textcolor", "rgb(0,100,0)" );
	
			liqcell_setcaption(liqcell_child_lookup( self,"app_title"), title );
			liqcell_setcaption(liqcell_child_lookup( self,"app_desc"), description );
			
			
			
			
			liqcell *clock = liqcell_quickcreatevis("clock",   "time",   600,0,   200,100 );
			//char buf[80];
			//liqapp_format_strftime(buf,80,"%H:%M:%S");
			//liqcell_setcaption(   clock, buf);
			liqcell_propsets(     clock,"timeformat","%H:%M:%S");
			liqcell_propseti(     clock,"textalign",2);
			liqcell_propsets(     clock,"fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
			liqcell_propseti(     clock,"fontsize", 32 );
			liqcell_propsets(     clock, "textcolor", "rgb(255,255,255)" );
		//	liqcell_handleradd(self,    "mouse",   widget_mouse);
			liqcell_child_append( self, clock    );
	
		}
		return self;
	}
	
	



	static int sketchedit_mouse(liqcell *self, liqcellmouseeventargs *args,void *context)
	{
		liqsketch *sketch = liqcell_getsketch(self);
		if(!sketch)
		{
			return 0;
			// mmm dont know about using this
			liqsketch *s = liqsketch_new();
					s->pixelwidth =liqcell_getw(self);
					s->pixelheight=liqcell_geth(self);
					s->dpix=225;	// damn, dont like using this here
					s->dpiy=225;
			liqcell_setsketch( self, s );
			sketch=s;
		}
		liqstroke *stroke;

		if(args->mcnt==1)
		{
			// starting, allocate and insert a new stroke
			stroke = liqstroke_new();
			stroke->pen_y = 255;
			stroke->pen_u = 128;
			stroke->pen_v = 128;
			liqstroke_start(stroke,args->mex,args->mey,args->mez,args->met);
			
			liqsketch_strokeinsert(sketch,stroke);
		}
		else
		{
			// continuing, get hold of the last stroke
			stroke = sketch->strokelast;	
			liqstroke_extend(stroke,args->mex,args->mey,args->mez,args->met);
			liqsketch_strokeupdate(sketch,stroke);

			if(args->mez!=0)
			{
				// carry on
			}
			else
			{
				// finishing
			}
		}

		return 1;
	}


liqcell *liqsketchedit_create(char *name,int l,int t,int w,int h)
{
		
		liqcell *c = liqcell_quickcreatevis(name,  NULL,   l,t,w,h );
		
		liqcell_propseti(c,"sketchediting",1);		// mark it as editing :)
		
			// give us something to draw onto
			liqsketch *s = liqsketch_new();
					s->pixelwidth =liqcell_getw(c);
					s->pixelheight=liqcell_geth(c);
					s->dpix=225;	// damn, dont like using this here
					s->dpiy=225;
			liqcell_setsketch( c, s );
			
			
		liqcell_handleradd(c,    "mouse",   sketchedit_mouse);
	return c;	
}


	static void cam_picturetaken(void *CAMtag)
	{
		liqcell *c = (liqcell *)CAMtag;
		liqcell_setdirty(c,1);
	}
	
/**	
 * liqcam.destroy
 */	
static int liqcam_destroy(liqcell *self,liqcellclickeventargs *args, liqcell *liqcam)
{
	// we must stop the camera!
	// technically we could change this to:
	// we should decrement the counter of users of this camera source
	// that way, multiple apps can see the same data
	liqapp_log("liqcam_destroy hmm1");
	liqcamera_stop();
	liqapp_log("liqcam_destroy hmm2");
	return 0;
}
	



liqcell *liqcam_create()
{

//int  liqcamera_start(int argCAMW,int argCAMH,int argCAMFPS,liqimage * argCAMdestimage,void (*argCAMUpdateCallback)() );
//void liqcamera_stop();


	liqcell *self = liqcell_quickcreatewidget("liqcam","form", 800,480);
	
	if(self)
	{
		
		// need a top bar
		
		liqcell_child_insert( self, uititlebar_create("top","Smile please","I'm about to take your picture") );
		
		
		liqcell *c = liqsketchedit_create("content",  40,120,  320,240);// 800,380 );
		
		
		liqimage *cam = liqimage_new();
		liqimage_pagedefine(cam,320,240,225,225,0);
		
		liqcell_setimage(c,cam);
		
		liqcamera_start(320,240,25,cam,cam_picturetaken,c);
		
		
		
		liqcell_child_insert( self, c );
		
		//liqcell_child_arrange_autoflow(self);
		
		//liqcell_propsets(  self, "backcolor", "rgb(0,0,100)" );

		//liqcell_setimage(  self, liqimage_newfromfile( "../liqbrain/mer_9.jpg",0,0,0) );
		
		
		liqcell *r = liqcell_quickcreatevis("recent", "liqrecentpics", 400,120,  400,240);// 800,380 );
		
		liqcell_child_insert( self, r );

		liqcell_handleradd_withcontext(self, "destroy", liqcam_destroy ,self);
			

		
	}
	return self;
}

