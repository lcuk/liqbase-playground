#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>

//#####################################################################
//#####################################################################
//##################################################################### liqbrightness :: by gary birkett :)
//#####################################################################
//#####################################################################


liqcell *liqbrightness_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqbrightness","form", 800,480);

	if(self)
	{
		
		liqcell_propsets(self,"imagefilename","media/liqbrightness.png");
		liqcell_propseti(self,"lockaspect",1);
	}
	return self;
}
