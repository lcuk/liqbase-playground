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
		addone(self, "ciroclock_minutes");
		addone(self, "liqbase");
		
		liqcell_child_arrange_easytile( self );

	}
	return self;
}
