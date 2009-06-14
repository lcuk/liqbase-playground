
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqbase.h>

//#####################################################################
//#####################################################################
//##################################################################### opensource :: by gary birkett
//#####################################################################
//#####################################################################


	static int widget_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		liqcell_adjustpos(self,0,args->mdy);
	}

















liqcell *opensource_create()
{

	liqcell *self = liqcell_quickcreatewidget("opensource","form", 800,480);

	if(self)
	{
			liqcell *body = liqcell_quickcreatewidget("body","frame", 800,480);

			liqcell_child_append( body,  uititlebar_create(   "ui", "User Interface test1", "The very first UI example I've tried" ) );
			liqcell_child_append( body,  uiinfobar_create(    "this is a user interface test for the new liqbase") );
			liqcell_child_append( body,  uitextbox_create(    "Nickname", "lcuk" ) );
			liqcell_child_append( body,  uitextbox_create(    "Full Name", "Gary Birkett" ) );
			liqcell_child_append( body,  uitextbox_create(    "Email", "liquid@gmail.com" ) );
			liqcell_child_append( body,  uinumberbox_create(  "Karma Bonus", "35" ) );
			liqcell_child_append( body,  uitextbox_create(    "Karma Rating", "Excellent" ) );
			liqcell_child_append( body,  uitextbox_create(    "homepage", "http://liqbase.net" ) );
			liqcell_child_append( body,  uitextbox_create(    "gender", "male" ) );
			liqcell_child_append( body,  uipicturebox_create( "avatar", "smile" ) );
			//liqcell_child_append( body,  uibuttonstrip_create("options", "help,cancel,save" ) );

			liqcell_child_arrange_autoflow(body);

			liqcell_handleradd(body,    "mouse",   widget_mouse);

		liqcell_child_append( self, body );


	}


	return self;
}
