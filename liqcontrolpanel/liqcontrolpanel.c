#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>

//#####################################################################
//#####################################################################
//##################################################################### liqcontrolpanel :: by gary birkett :)
//#####################################################################
//#####################################################################


	static int widget_click(liqcell *self, liqcellclickeventargs *args)
	{
		args->newdialogtoopen = liqcell_getcontent( self );

		return 1;
	}



liqcell *liqcontrolpanel_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqcontrolpanel","form", 800,480);

	if(self)
	{

		liqcell *addone(liqcell *body,char *classname)
		{
			char buf[256];
			snprintf(buf,sizeof(buf),"%s1",classname);
			liqcell *newx = liqcell_quickcreatevis(buf,classname,0,0,0,0);
			liqcell *item = liqcell_quickcreatevis(buf,"item",0,0,newx->w,newx->h);
			liqcell_propseti(  item,    "lockaspect",1);
			liqcell_setcontent(item,    newx);
			liqcell_handleradd(item,    "click",   widget_click);
			liqcell_child_append( body, item );
			return item;
			
		}

		addone(self, "liqbattery");
		addone(self, "liqcpu");
		addone(self, "liqbrightness");
		addone(self, "liqmemory");
		//addone(self, "ciroclock_minutes");
		//addone(self, "liqbase");
		
		liqcell_child_arrange_easytile( self );

	}
	return self;
}


//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when liqcontrolpanel is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"liqcontrolpanel canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}


int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"liqcontrolpanel" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"liqcontrolpanel liqapp_init failed"); }
	 }
	 liqcell *self = liqcontrolpanel_create();
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}
