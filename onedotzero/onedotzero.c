// this file is part of liqbase by Gary Birkett

#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>

	static int widget_close_click(liqcell *self, liqcellclickeventargs *args, liqcell *item)
	{
		 //liqcell_setvisible(item,0);
		 if( liqcell_getcontent(item)==NULL)
		 {
			  // put it back
			  liqcell_setcontent(item,item->tag);
		 }
		 else
		 {
			  // hide it
			  item->tag = liqcell_getcontent(item);
			  liqcell_setcontent(item,NULL);
		 }
		 liqcell_child_arrange_easytile(self);
		 return 1;
	}
    
    
    
	static int widget_dirty(liqcell *self, liqcelleventargs *args,liqcell *context)
	{
		//args->newdialogtoopen = liqcell_getcontent( self );

		liqcell_setdirty(context,1);
		return 1;
	}
 
	static int widget_addclosebutton(liqcell *self)
	{
		 //liqcell *cimg = liqcell_quickcreatevis("closebutton", "button", 0,0,20,20);
		 //liqcell_setimage(cimg, liqimage_cache_getfile( "../media/quickicons/gtk-close.png" ,0,0,1)  );
		 //liqcell_handleradd_withcontext(cimg, "click", widget_close_click,self );
		 //liqcell_child_append(self, cimg);
         
         //liqcell *c=liqcell_getcontent(self);
         //if(c)
         //{        
         //    liqcell_handleradd_withcontext(c,    "dirty",   widget_dirty,self);
         //}
         
		 return 1;
	}
	static int widget_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		 args->newdialogtoopen = liqcell_getcontent( self );
		 return 1;
	}
    
    /**	
     * piccover click - occurs when a short mouse stroke occured
     */	
    static int piccover_click(liqcell *self, liqcelleventargs *args,liqcell *context)
    {
        
        osc_onedotzero_send_entermsg();
        
          liqcell_propseti(self,"clicked",1);
          liqcell_setdirty(self,1);
        return 0;
    }
    
    
/**	
 * onedotzero paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
static int onedotzero_paint(liqcell *self, liqcellpainteventargs *args,liqcell *onedotzero)
{

		liqcell *piccover = liqcell_child_lookup(onedotzero,"piccover");
		if( liqcell_propgeti(piccover,"clicked",0) )
		{
			if( liqcell_gety(piccover) != liqcell_geth(onedotzero) )
			{
				int dif = liqcell_geth(onedotzero) - liqcell_gety(piccover);
				if(dif>5)dif=50;				
				liqcell_setpos(piccover, liqcell_getx(piccover),liqcell_gety(piccover) + dif);
				liqcell_setdirty(piccover,1);
			}
            else
            {
               liqcell_setvisible(piccover,0);
            }
		}
        
	return 0;
}


/**	
 * onemessage dialog_close - the dialog was closed
 */	
static int onedotzero_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    osc_onedotzero_send_closeapp();
	return 0;
}

/**	
 * create a new onedotzero widget
 */	
liqcell *onedotzero_create()
{
	liqcell *self = liqcell_quickcreatewidget("onedotzero", "form", 800,480);
	if(!self) {liqapp_log("liqcell error not create 'onedotzero'"); return NULL;  } 
	
 

     





	//############################# canvas:label
	liqcell *backplane = liqcell_quickcreatevis("canvas", "label", 0, 0, 800, 480);
	//liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(backplane, "canvas" );
	//liqcell_propsets(  backplane, "textcolor", "rgb(255,0,0)" );
	//liqcell_propsets(  backplane, "backcolor", "rgb(64,64,64)" );
	//liqcell_propseti(  backplane, "textalign", 2 );
	liqcell_child_append(  self, backplane);
    
    //liqcell_setenabled(backplane,0);


	
    void one(char *classname)
   	{
	//	 liqcell *ctrl = liqcell_quickcreatevis(classname, classname, 0,0,-1,-1);
     //    //liqcell_propseti(  ctrl, "rowid", 1 );
	//	 liqcell *item = liqcell_quickcreatevis(classname, NULL, 0,0,1,1);
	//	 liqcell_propseti(item,"lockaspect",1);
	//	 liqcell_setcontent(item,	 ctrl);
	//	 //widget_addclosebutton(item);
	//	 liqcell_handleradd(item,	 "click",	widget_click);


		 liqcell *item = liqcell_quickcreatevis(classname, classname, 0,0,800,480);

		 liqcell_child_append( backplane, item );
	}
    
    one("onedotzero.onemessage");
    
    
  //  one("liqstarspull");
  //  one("onemenu");
   // one("onetouch");
   
   
  //  one("onetouchslide");
   
   
   // one("liqaccelview");
    //one("oneinteractshapes");
    //one("onetouch");
   // one("oneinteract");
   
   // one("liqaccelview_angle");
    
   // one("oneread");

   // one("oneconfigure");
   
   

	//############################# piccover:picturebox
	liqcell *piccover = liqcell_quickcreatevis("piccover", "picturebox", 0,0, 800,480);
    liqcell_setimage(  piccover,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/1.jpg", 0,0,1) );
    
    liqcell_propseti( piccover ,  "lockaspect", 0 );
    
	//liqcell_setfont(	piccover, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  piccover, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  piccover, "backcolor", "rgb(235,233,237)" );
	//liqcell_propsets(  piccover, "bordercolor", "rgb(200,100,100)" );
    liqcell_handleradd_withcontext(piccover, "click", piccover_click ,self);
    
	liqcell_child_append(  self, piccover);   


    
		
	//liqapp_log("app codepath = '%s'",app.codepath);
	//char fnbuf[FILENAME_MAX];  snprintf(fnbuf,sizeof(fnbuf),"%s/onedotzero/media/onedotzero_background_fade_blur.png",app.codepath);
	//liqcell_propsets( self ,  "imagefilename", fnbuf );
	////liqcell_setimage(  self ,  liqimage_cache_getfile( fnbuf ,0,0,0) );
	//liqcell_propseti( self ,  "lockaspect", 0 );
    //liqcell_propsets( self ,  "imagefloat", "0,0,0,0" );	// a bit of magic if it works..
	
    
    
    
//	liqcell_child_arrange_easytile(backplane);
    
    
    
	//liqcell_child_arrange_easytile(self);
 
	//############################# nokiapicture1:nokiapicture
	liqcell *nokiapicture1 = liqcell_quickcreatevis("nokiapicture1", "nokiapicture", 652, 438, 130, 24);
	liqcell_child_insert(  self, nokiapicture1); 
    
    
    liqcell_handleradd_withcontext(self, "paint", onedotzero_paint ,self);
    
    
    //liqcell_handleradd_withcontext(self, "keypress", onedotzero_keypress,self );
    
    // onedotzero do not need tools
    liqcell_propseti(self,"easyrun_hidetools",1);
    
    
    liqcell_handleradd_withcontext(self, "dialog_close", onedotzero_dialog_close ,self);
    
	return self;
}


//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when onedotzero is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"onedotzero canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}

int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"onedotzero" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"onedotzero liqapp_init failed"); }
	 }
     
     osc_onedotzero_init();
     
   //  osc_onedotzero_send_runtests();
          
          liqcell *self = onedotzero_create();
          liqcell_easyrun_internal(self);
          liqcell_release(self);
          
     osc_onedotzero_close();
     
	 liqapp_close();
	 return 0;
}
