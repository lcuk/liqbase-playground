// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqapp_prefs.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>

static void zoomto(liqcell *backplane,float scale);
static void mapzoom_setknob(liqcell *liqmapzoom,float scale);


		

int liqmapzoom_settings_load(liqcell *liqmapzoom)
{

	liqcell *zoom = liqcell_child_lookup(liqmapzoom, "zoom");
		liqcell *knob = liqcell_child_lookup(zoom, "knob");
	liqcell *backplane = liqcell_child_lookup(liqmapzoom, "backplane");
    
    // load the global settings

    int mapzoom = atoi( liqapp_pref_getvalue_def("liqmap_zoom",     "100" ) );
    char *mapfn =       liqapp_pref_getvalue_def("liqmap_filename", "http://liqbase.net/papermaps/liqmap_instructions.png" );
    
    int mapposx = atoi( liqapp_pref_getvalue_def("liqmap_posx",     "0" ) );
    int mapposy = atoi( liqapp_pref_getvalue_def("liqmap_posy",     "0" ) );
    
    if(mapzoom<=0)mapzoom=100;
    
    
    liqapp_log("liqmapzoom_settings_load %i,'%s',%i,%i",mapzoom,mapfn,mapposx,mapposy);

	liqcell_propsets(backplane,"imagefilename",mapfn);
    liqcell_setimage(backplane,NULL);
    liqcell_setrect(backplane,0,0,liqmapzoom->w,liqmapzoom->h);
    liqcell_setdirty(backplane,1);
    
    liqcell_setpos(knob,0,0);
   // zoomto(backplane,100);//((float)mapzoom)/100.0);
   
   float scale = ((float)mapzoom)*0.01;
   
    zoomto(backplane,scale);
    
    mapzoom_setknob(liqmapzoom,scale);
    
    
    liqcell_setpos(backplane,mapposx,mapposy);
    
    // no image present
    // we must ensure it is shown at least once
    // if its offscreen and out of spec, we must ensure its still usable
    // hence this silly hack to ensure its big enough to be seen...,
    if( (mapposx+liqcell_getw(backplane)) < 0) backplane->w= (-mapposx)+liqcell_getw(liqmapzoom);
    if( (mapposy+liqcell_geth(backplane)) < 0) backplane->h= (-mapposy)+liqcell_geth(liqmapzoom);
    
    return 0;	
}




int liqmapzoom_settings_save(liqcell *liqmapzoom)
{

	liqcell *zoom = liqcell_child_lookup(liqmapzoom, "zoom");
		liqcell *knob = liqcell_child_lookup(zoom, "knob");
	liqcell *backplane = liqcell_child_lookup(liqmapzoom, "backplane");
    
    // store the global settings


			float upto = ((float)knob->y) / ((float)(zoom->h-knob->h));
			float scale = 0.2 + (upto * 3.8);
    
	liqapp_pref_setvalue_printf( "liqmap_zoom",     "%i", (int)(scale * 100) );
	liqapp_pref_setvalue_printf( "liqmap_filename", "%s", liqcell_propgets(backplane,"imagefilename", "http://liqbase.net/papermaps/liqmap_instructions.png") );
	liqapp_pref_setvalue_printf( "liqmap_posx",     "%i", liqcell_getx(backplane) );
	liqapp_pref_setvalue_printf( "liqmap_posy",     "%i", liqcell_gety(backplane) );

	liqapp_prefs_save();
	
	//liqcell_propseti(liqmapzoom,"dialog_running",0);

    return 0;	
}

        
int liqmapzoom_changeimagefilename(liqcell *liqmapzoom,char *imagefilename)
{

	liqcell *zoom = liqcell_child_lookup(liqmapzoom, "zoom");
		liqcell *knob = liqcell_child_lookup(zoom, "knob");
        
	liqcell *backplane = liqcell_child_lookup(liqmapzoom, "backplane");
        
	liqcell_propsets(backplane,"imagefilename",imagefilename);
    liqcell_setimage(backplane,NULL);
    liqcell_setrect(backplane,0,0,liqmapzoom->w,liqmapzoom->h);
    liqcell_setdirty(backplane,1);
    
    liqcell_setpos(knob,0,0);
    zoomto(backplane,1);
    mapzoom_setknob(liqmapzoom,1);
    
    liqmapzoom_settings_save(liqmapzoom);
    
    return 0;	
}



//#####################################################################
//#####################################################################
//##################################################################### liqmapzoom :: by gary birkett
//#####################################################################
//#####################################################################



	static int mapzoom_backplane_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *liqmapzoom)
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
					// now replase p2 with the previous one again
						p2 = p2->linkprev;
				}
				if(p1 && p2 && p1->x==p2->x && p1->y==p2->y)
				{
					// now replase p2 with the previous one again
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

	static void mapzoom_setknob(liqcell *liqmapzoom,float scale)
	{
        
        liqcell *zoom = liqcell_child_lookup(liqmapzoom, "zoom");
            liqcell *knob = liqcell_child_lookup(zoom, "knob");
        liqcell *backplane = liqcell_child_lookup(liqmapzoom, "backplane");
        
        
        float r = (scale - 0.2)/3.8;
        if(r<0)r=0;
        if(r>1)r=1;
        
        float avail = ((float)(zoom->h-knob->h));


		liqcell_setpos( knob, liqcell_getx(knob), r * (avail) );
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


	static int mapzoom_zoom_mouse(liqcell *zoom, liqcellmouseeventargs *args, liqcell *liqmapzoom)
	{
		liqcell *floatmap = liqcell_getbasewidget(zoom);
		if(!floatmap) return 0;
        
        
        int yy = args->mey - args->oy;
		
		
		//liqapp_log("test: '%s'",floatmap->name);
		
		liqcell *backplane = liqcell_child_lookup( floatmap,"backplane");
		if(!backplane) return 0;
		
		//liqapp_log("mouse d %3i,%3i  e %3i,%3i   ez=%3i",args->mdx,args->mdy,args->mex,args->mey,args->mez);
		liqcell *knob = liqcell_child_lookup( zoom,"knob");
		if(knob)
		{
			liqcell_setpos( knob, liqcell_getx(knob), yy - liqcell_geth(knob)/2 );
			liqcell_forceinboundparent(knob);
			
			float upto = ((float)knob->y) / ((float)(zoom->h-knob->h));
			
			
			float scale = 0.2 + (upto * 3.8);
			
			
			zoomto(backplane,scale);
            
            mapzoom_setknob(liqmapzoom,scale);


			
		}
		return 1;
	}
    
    static int mapzoom_imageloaded(liqcell *self, liqcelleventargs *args, void *liqmapzoom)
	{

        liqcell *zoom = liqcell_child_lookup(liqmapzoom, "zoom");
            liqcell *knob = liqcell_child_lookup(zoom, "knob");
        liqcell *backplane = liqcell_child_lookup(liqmapzoom, "backplane");

		// this occurs when the lazy loader has finished loading the image for this item
		liqapp_log("item loaded");
		liqimage *myimg = liqcell_getimage(self);
		if( myimg )
		{
            // now, we have loaded and been resized
            //
			float upto = ((float)knob->y) / ((float)(zoom->h-knob->h));
			float scale = 0.2 + (upto * 3.8);
			zoomto(backplane,scale);
            
            mapzoom_setknob(liqmapzoom,scale);
            
            
            int mapposx = atoi( liqapp_pref_getvalue_def("liqmap_posx",     "0" ) );
            int mapposy = atoi( liqapp_pref_getvalue_def("liqmap_posy",     "0" ) );
            liqcell_setpos(backplane,mapposx,mapposy);
            
            liqcell_setdirty(backplane,1);
            
            


        }
    }
			

		
/**	
 * liqmapzoom widget filter, the system is asking you to filter to the specified .
 */	
static int liqmapzoom_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *liqmapzoom)
{
	// system is indicating the user has typed into the search box
	// you are expected to filter your content based upon this searchterm.
	// show or hide details and rearrange contents to apply this filter.
	char *searchterm = NULL;
	args->resultoutof=0;  // total number of searchable contents
	args->resultshown=0;  // count of options remaining after filtering.
	searchterm = args->searchterm;
	if(searchterm && *searchterm)
	{
		 // check the name property
		 args->resultoutof++;
		 if( stristr(self->name,searchterm) != NULL )
		 {
			  args->resultshown++;
		 }
		 // check the classname property
		 args->resultoutof++;
		 if( stristr(self->classname,searchterm) != NULL )
		 {
			  args->resultshown++;
		 }
		 // check any other properties or children and increment counters
		 // filter out list items recursively
	}
	return 0;
}
/**	
 * liqmapzoom widget refresh, all params set, present yourself to the user.
 */	
static int liqmapzoom_refresh(liqcell *self,liqcelleventargs *args, liqcell *liqmapzoom)
{
	return 0;
}
/**	
 * liqmapzoom dialog_open - the user zoomed into the dialog
 */	
static int liqmapzoom_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *liqmapzoom)
{
	return 0;
}
/**	
 * liqmapzoom dialog_close - the dialog was closed
 */	
static int liqmapzoom_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *liqmapzoom)
{
	return 0;
}
/**	
 * liqmapzoom widget shown - occurs once per lifetime
 */	
static int liqmapzoom_shown(liqcell *self,liqcelleventargs *args, liqcell *liqmapzoom)
{
	return 0;
}
/**	
 * liqmapzoom mouse - occurs all the time as you stroke the screen
 */	
static int liqmapmapzoom_zoom_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *liqmapzoom)
{
	return 0;
}
/**	
 * liqmapzoom click - occurs when a short mouse stroke occured
 */	
static int liqmapzoom_click(liqcell *self, liqcellclickeventargs *args,liqcell *liqmapzoom)
{
	return 0;
}
/**	
 * liqmapzoom keypress - the user pressed a key
 */	
static int liqmapzoom_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *liqmapzoom)
{
	return 0;
}
/**	
 * liqmapzoom keyrelease - the user released a key
 */	
static int liqmapzoom_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *liqmapzoom)
{
	return 0;
}
/**	
 * liqmapzoom paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqmapzoom_paint(liqcell *self, liqcellpainteventargs *args,liqcell *liqmapzoom)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqmapzoom dynamic resizing
 */	
static int liqmapzoom_resize(liqcell *self,liqcelleventargs *args, liqcell *liqmapzoom)
{
	//float sx=((float)self->w)/((float)self->innerw);
	//float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *zoom = liqcell_child_lookup(liqmapzoom, "zoom");
		liqcell *knob = liqcell_child_lookup(zoom, "knob");
        
    liqcell *backplane = liqcell_child_lookup(liqmapzoom, "backplane");
        
    liqcell_setrect(zoom,0,0,50,self->h-64);
        liqcell_setrect(knob,0,0,50,50);
        
    if(liqcell_getimage(backplane)==NULL)
    {
        liqcell_setrect(backplane,0,0,self->w,self->h);
    }
        
        
	//liqcell *backplane = liqcell_child_lookup(self, "backplane");
	//liqcell_setrect_autoscale( zoom, 0,0, 36,450, sx,sy);
	//liqcell_setrect_autoscale( knob, 0,0, 36,32, sx,sy);
	//liqcell_setrect_autoscale( backplane, 0,0, 798,478, sx,sy);
	return 0;
}

/**	
 * liqmapzoom_child_test_seek this function shows how to access members
 */	
	  
static void liqmapzoom_child_test_seek(liqcell *liqmapzoom)
{	  
	liqcell *zoom = liqcell_child_lookup(liqmapzoom, "zoom");
		liqcell *knob = liqcell_child_lookup(zoom, "knob");
	liqcell *backplane = liqcell_child_lookup(liqmapzoom, "backplane");
}	  
/**	
 * create a new liqmapzoom widget
 */	
liqcell *liqmapzoom_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqmapzoom", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqmapzoom'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
    
	//############################# backplane:picturebox
	liqcell *backplane = liqcell_quickcreatevis("backplane", "picturebox", 0, 0, 800, 480);
	//liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	//liqcell_propsets(  backplane, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  backplane, "backcolor", "rgb(0,0,64)" );

    liqcell_handleradd_withcontext(backplane,    "imageloaded",   mapzoom_imageloaded,self);
	liqcell_propseti(backplane,"lockaspect",0);
	liqcell_propseti(backplane,"autosize",1);
	liqcell_propseti(backplane,"imageallowalpha",0);    
	liqcell_handleradd_withcontext(backplane,    "mouse",   mapzoom_backplane_mouse,self );
    



    //char *mapfn = liqapp_pref_getvalue_def("liqmapzoom_imagefilename","http://liqbase.net/papermaps/liqmap_instructions.png");
	//liqcell_propsets(backplane,"imagefilename",mapfn);



	liqcell_child_append(  self, backplane);
    
        
	//############################# zoom:picturebox
	liqcell *zoom = liqcell_quickcreatevis("zoom", "picturebox", 0, 0, 50, 480);
	//liqcell_setfont(	zoom, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	//liqcell_propsets(  zoom, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  zoom, "backcolor", "rgba(0,255,0,50)" );
    
    liqcell_handleradd_withcontext(zoom,    "mouse",   mapzoom_zoom_mouse,self);
    
		//############################# knob:picturebox
		liqcell *knob = liqcell_quickcreatevis("knob", "picturebox", 0, 0, 50,50);
		//liqcell_setfont(	knob, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
		//liqcell_propsets(  knob, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  knob, "backcolor", "rgb(0,255,0)" );
        liqcell_propseti(knob,"lockaspect",0);
        liqcell_propsets(knob,"imagefilename","/usr/share/liqbase/liqmap/media/zoom.png");
		liqcell_child_append(  zoom, knob);
	liqcell_child_append(  self, zoom);
    
    


	//liqcell_propsets(  self, "backcolor", "rgb(0,64,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/liqmap/media/liqmapzoom_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", liqmapzoom_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", liqmapzoom_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqmapzoom_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqmapzoom_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqmapzoom_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqmapzoom_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", liqmapmapzoom_zoom_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", liqmapzoom_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqmapzoom_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqmapzoom_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqmapzoom_dialog_close ,self);
    
    
    
    //liqmapzoom_settings_load(self);
    
    
	return self;
}

