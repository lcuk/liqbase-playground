#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>

//#####################################################################
//#####################################################################
//##################################################################### liqdesktop :: by gary birkett :)
//#####################################################################
//#####################################################################

extern liqcell *universe;


	static int widget_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		args->newdialogtoopen = liqcell_getcontent( self );

		return 1;
	}


	

liqcell *liqdesktop_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqdesktop","form", 800,480);

	if(self)
	{

		// need a top bar

		liqcell_child_insert( self, uititlebar_create("top","liqbase playground","welcome to your world") );

		liqcell *mirror=NULL;
		if(universe)mirror = liqcell_child_lookup(universe,"mirror");
		


		liqcell *c = liqcell_quickcreatevis("content", NULL, 0,100,   800,380 );
		liqcell_setcontent( c, mirror );
		liqcell_handleradd( c,    "click",   widget_click);
		liqcell_child_insert( self, c );

	}
	return self;
}
