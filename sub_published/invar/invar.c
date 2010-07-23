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
	static int widget_addclosebutton(liqcell *self)
	{
		 //liqcell *cimg = liqcell_quickcreatevis("closebutton", "button", 0,0,20,20);
		 //liqcell_setimage(cimg, liqimage_cache_getfile( "../media/quickicons/gtk-close.png" ,0,0,1)  );
		 //liqcell_handleradd_withcontext(cimg, "click", (void*)widget_close_click,self );
		 //liqcell_child_append(self, cimg);
		 return 1;
	}
	static int widget_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		 args->newdialogtoopen = liqcell_getcontent( self );
		 return 1;
	}
/**	
 * create a new invar widget
 */	
liqcell *invar_create()
{
	liqcell *self = liqcell_quickcreatewidget("invar", "form", 800,480);
	if(!self) {liqapp_log("liqcell error not create 'invar'"); return NULL;  } 
	

	{
		 liqcell *ctrl = liqcell_quickcreatevis("ctrlinvar_config1", "invar.invar_config", 0,0,0,0);
		 liqcell *item = liqcell_quickcreatevis("iteminvar_config1", NULL, 0,0,1,1);
		 liqcell_propseti(item,"lockaspect",1);
		 liqcell_setcontent(item,	 ctrl);
		 widget_addclosebutton(item);
		 liqcell_handleradd(item,	 "click",  (void*) widget_click);
		 liqcell_child_append( self, item );
	}
/*	{
		 liqcell *ctrl = liqcell_quickcreatevis("ctrlinvar_calibrate1", "invar.invar_calibrate", 0,0,0,0);
		 liqcell *item = liqcell_quickcreatevis("iteminvar_calibrate1", NULL, 0,0,1,1);
		 liqcell_propseti(item,"lockaspect",1);
		 liqcell_setcontent(item,	 ctrl);
		 widget_addclosebutton(item);
		 liqcell_handleradd(item,	 "click",  (void*) widget_click);
		 liqcell_child_append( self, item );
	}
	{
		 liqcell *ctrl = liqcell_quickcreatevis("ctrlinvar_rawview1", "invar.invar_rawview", 0,0,0,0);
		 liqcell *item = liqcell_quickcreatevis("iteminvar_rawview1", NULL, 0,0,1,1);
		 liqcell_propseti(item,"lockaspect",1);
		 liqcell_setcontent(item,	 ctrl);
		 widget_addclosebutton(item);
		 liqcell_handleradd(item,	 "click",  (void*) widget_click);
		 liqcell_child_append( self, item );
	}
 */
	{
		 liqcell *ctrl = liqcell_quickcreatevis("ctrlliqbase_about1", "invar.liqbase_about", 0,0,0,0);
		 liqcell *item = liqcell_quickcreatevis("itemliqbase_about1", NULL, 0,0,1,1);
		 liqcell_propseti(item,"lockaspect",1);
		 liqcell_setcontent(item,	 ctrl);
		 widget_addclosebutton(item);
		 liqcell_handleradd(item,	 "click",  (void*) widget_click);
		 liqcell_child_append( self, item );
	}

	{
		 liqcell *ctrl = liqcell_quickcreatevis("ctrlinvar_host1", "invar.invar_host", 0,0,0,0);
		 liqcell *item = liqcell_quickcreatevis("iteminvar_host1", NULL, 0,0,1,1);
		 liqcell_propseti(item,"lockaspect",1);
		 liqcell_setcontent(item,	 ctrl);
		 widget_addclosebutton(item);
		 liqcell_handleradd(item,	 "click",  (void*) widget_click);
		 liqcell_child_append( self, item );
	}
 
	{
		 liqcell *ctrl = liqcell_quickcreatevis("ctrlinvar_run1", "invar.invar_run", 0,0,0,0);
		 liqcell *item = liqcell_quickcreatevis("iteminvar_run1", NULL, 0,0,1,1);
		 liqcell_propseti(item,"lockaspect",1);
		 liqcell_setcontent(item,	 ctrl);
		 widget_addclosebutton(item);
		 liqcell_handleradd(item,	 "click",  (void*) widget_click);
		 liqcell_child_append( self, item );
	}
	liqcell_child_arrange_easytile(self);
	return self;
}


//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when invar is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"invar canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}

int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"invar" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"invar liqapp_init failed"); }
	 }
	 liqcell *self = invar_create();
	 // remove tools button :)
	 liqcell_propseti(self,"easyrun_hidetools",1);
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}
