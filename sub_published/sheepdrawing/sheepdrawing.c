// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when sheepdrawing is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"sheepdrawing canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}

int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"sheepdrawing" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"sheepdrawing liqapp_init failed"); }
	 }
	 liqcell *self = liqcell_quickcreatevis("sheepdrawing_cover1", "sheepdrawing_cover", 0,0, -1,-1);
	 // remove tools button :)
	 liqcell_propseti(self,"easyrun_hidetools",1);
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}
