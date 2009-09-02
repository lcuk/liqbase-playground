
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>

//#####################################################################
//#####################################################################
//##################################################################### liqbase_net :: by Gary Birkett :)
//#####################################################################
//#####################################################################



liqcell *liqbase_net_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqbase_net","form", 800,480);

	if(self)
	{

		liqcell *item;
		
	
		item = liqcell_quickcreatevis("item",   "label",   0,0,   800,240 ) ;
		liqcell_setcaption(   item,"liqbase_net not enabled");
		liqcell_propseti(     item,"textalign", 2);
		liqcell_propseti(     item,"textaligny",2);
		liqcell_propsets(     item,"fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
		liqcell_propseti(     item,"fontsize", 170 );
		liqcell_child_insert( self, item);

		item = liqcell_quickcreatevis("item",   "label",   0,240,   800,120 ) ;
		liqcell_setcaption(   item,app.username );
		liqcell_propseti(     item,"textalign", 2);
		liqcell_propseti(     item,"textaligny",2);
		liqcell_propsets(     item,"fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
		liqcell_propseti(     item,"fontsize", 80 );
		liqcell_child_insert( self, item);

		item = liqcell_quickcreatevis("item",   "label",   0,360,   800,120 ) ;
		liqcell_setcaption(   item,"valid md5 password required" );
		liqcell_propseti(     item,"textalign", 2);
		liqcell_propseti(     item,"textaligny",2);
		liqcell_propsets(     item,"fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
		liqcell_propseti(     item,"fontsize", 80 );
		liqcell_child_insert( self, item);

	}
	return self;
}
