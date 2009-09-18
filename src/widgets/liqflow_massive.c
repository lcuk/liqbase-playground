#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqimage.h>
#include <liqbase/liq_xsurface.h>


// Tue Sep 01 01:29:25 2009 lcuk : removed the battery lookup code, i couldnt get it working and i felt wrong leaving it in
// Tue Sep 01 01:29:52 2009 lcuk : battery is just asthetic for now



static int framecount=0;




static void saveframe(liqcell *cell,int framecount)
{
	liqcell_hold(cell);
	// 20090528_231040 lcuk : this locks up dunno why
	// 20090624_005139 lcuk : trying it as a widget itself, to see if it was initializers at fault
	
	
	char cellname[1024];
	
	snprintf(cellname,sizeof(cellname),"%s",cell->name);
	
	liqapp_ensurecleanusername(cellname);
	
	liqapp_log("...creating image %s",cellname);
	liqimage *img = liqimage_newatsize(1600,960,0);
	
	liqapp_log("...creating cliprect");
	
	liqcliprect *cr = liqcliprect_newfromimage(img);
	
	liqapp_log("...painting cell %s",cellname);
	liqcell_easypaint(cell,cr,0,0,1600,960);
	
	liqapp_log("...building filename");

				char 		fmtnow[255];
	 			liqapp_formatnow(fmtnow,255,"yyyymmdd_hhmmss");
				char buf[FILENAME_MAX+1];
				snprintf(buf,FILENAME_MAX,"%s/sketches/flowx.%i.%s.%s.scr.png",app.userdatapath,framecount,fmtnow,cellname  );




	
	liqapp_log("...saving image as '%s'",buf);

				liqimage_pagesavepng(img,buf);
                
                
                //void post_to_liqbase_net(char *filename,char *datakey);
                
                //post_to_liqbase_net(buf,"screenshot");


//01:49:32 png writing png
//01:49:32 png cleaning up
//01:49:32 ...releasing cr
//01:49:32 liqcliprect free
//01:49:32 liqimage free
//01:49:32 liqimage pagereset
//01:49:32 ...releasing image
//01:49:32 ...done
// 20090624_015023 lcuk : a bug is occuring, the liqimage instance is being freed too early
// 20090624_015040 lcuk : that means something is releasing it within the middle of something else
// 20090624_015052 lcuk : but did not get hold of it first
	
				
	
	liqapp_log("...releasing cr");
	liqcliprect_release(cr);
	
	liqapp_log("...releasing image");
	liqimage_release(img);
	
	liqapp_log("...done");
	
	liqcell_release(cell);
	
}


//#####################################################################
//#####################################################################
//##################################################################### liqflowmassive :: by gary birkett :)
//#####################################################################
//#####################################################################



/**	
 * create a new liqflowsmall widget
 */	
		
liqcell *liqflowsmall_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqflowsmall","form", 800,480);

	if(!self) {liqapp_log("liqcell error not create 'liqflowsmall'"); return NULL;  } 
	



	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
    
    liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/media/n900_crapback.png",0,0,1) );
    liqcell_propseti(self,"lockaspect",0);



	return self;
}



	static int widget_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
	{
		
		//liqapp_log("starpaint %4i,%4i :: '%s'::'%s'",args->mx,args->my,self->name,self->classname);
		
		//liqapp_log("drawing args==NULL==%i args->graph==NULL==%i",args==NULL,  args->graph==NULL);
		// vgraph *graph;
		// args->graph;
		
		//vgraph_setbackcolor(args->graph, vcolor_YUV( (127+(rand()%128)) , (rand()%255) , (rand()%255) ) );
		
		
		
		//vgraph_drawbox(args->graph, 10, 40,   300, 400 );
		
		//vgraph_setpencolor(args->graph, vcolor_YUV(255,128,128) );


		
		//if( liqcell_propgeti(self,"dialog_running",0)==1 )
		{
		
		//	star_calc((STAR *)self->tag, args->graph, liqcell_getsketch(self), args->mx,args->my );
			liqcell_setdirty(self,1);
		}
		//else
		{
			// nothing for now...  should show a picture or something..
		}
		
		
		//liqapp_log("drawing done");
		return 1;
	}
	

	static int sketchedit_mouse(liqcell *self, liqcellmouseeventargs *args, void *liqflow)
	{
        liqcell *c = liqcell_getcontent(self);
        
        
    }


/**	
 * create a new liqflow_massive widget
 */	
		
liqcell *liqflow_massive_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqflow_massive","form", 800*5,480*5);

	if(!self) {liqapp_log("liqcell error not create 'liqflow_massive'"); return NULL;  } 
	

	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering


    //############################# liqflow:label
    liqcell *liqflow_tiny = liqcell_quickcreatevis("liqflow_tiny", "liqflow_tiny", 0,0,800,480);

    liqcell *backer = liqcell_quickcreatevis("backer", NULL, 0,0,self->w,self->h);
    liqcell_setcontent(backer,liqflow_tiny);
    liqcell_child_append(  self, backer);
    
    liqcell_handleradd_withcontext(backer,    "paint", sketchedit_mouse,self);

    
    int x,y;
    
    for(y=0;y<5;y++)
    {
        for(x=0;x<5;x++)
        {
            //############################# piece4:label
            liqcell *piece4 = liqcell_quickcreatevis("liqflowx", "liqflowsmall", x*800,y*480,800,480);
            //liqcell_propsets(  piece4, "imagefilename", "/usr/share/liqbase/liqcontrolpanel/media/liqflowmassive_4.png" );
            //liqcell_propseti( piece4 ,  "lockaspect", 0 );
            liqcell_child_append(  self, piece4);
        }
    }
    
    
   /* 
    
    for(framecount=0;framecount<10;framecount++)
    {
        saveframe(self,framecount);

    }
    
   */
    liqcell_handleradd_withcontext(self,    "paint", widget_paint,self);
    
    
	return self;
}

