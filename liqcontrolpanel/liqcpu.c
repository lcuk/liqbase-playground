#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>

//#####################################################################
//#####################################################################
//##################################################################### liqcpu :: by gary birkett :)
//#####################################################################
//#####################################################################


liqcell *liqcpu_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqcpu","form", 800,480);

	if(self)
	{
		
		liqcell_propsets(self,"imagefilename","/usr/share/liqbase/liqcontrolpanel/media/liqcpu.jpg");
		liqcell_propseti(self,"lockaspect",1);
	}
	return self;
}
