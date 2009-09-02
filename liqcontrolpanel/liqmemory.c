#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>

//#####################################################################
//#####################################################################
//##################################################################### liqmemory :: by gary birkett :)
//#####################################################################
//#####################################################################


liqcell *liqmemory_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqmemory","form", 800,480);

	if(self)
	{
		
		liqcell_propsets(self,"imagefilename","/usr/share/liqbase/liqcontrolpanel/media/liqmemory.jpg");
		liqcell_propseti(self,"lockaspect",1);
	}
	return self;
}
