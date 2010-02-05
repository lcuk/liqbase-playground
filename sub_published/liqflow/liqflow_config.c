

#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks


#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <string.h>
#include <sys/sysinfo.h>

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqimage.h>
#include <liqbase/liqsketch.h>
#include <liqbase/liq_xsurface.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqapp_prefs.h>


/**	
 * liqflow_config_cmdaccept clicked
 */	
static int liqflow_config_cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqflow_config)
{

    liqcell_propseti(liqflow_config,"dialog_running",0);
	return 0;
}




liqcell *liqflow_config_create()
{
	
	liqcell *self = liqcell_quickcreatewidget("liqflow_config","form", 800,480);
	
	if(self)
	{


			liqcell *body = liqcell_quickcreatewidget("body","frame", 800,480);
			
			liqcell_child_append( body,  uititlebar_create(   "config", "liqflow config", "Make a customised liqflow" ) );	
			liqcell_child_append( body,  uiinfobar_create(    "Fill in the required details") );

			liqcell_child_append( body,  uitextbox_create(    "title", "Fluid motion" ) );
			//liqcell_child_append( body,  uitextbox_create(    "nickname", "lcuk" ) );
			//liqcell_child_append( body,  uitextbox_create(    "author", "Gary Birkett" ) );
			//liqcell_child_append( body,  uitextbox_create(    "email", "liquid@gmail.com" ) );
			
			liqcell_child_append( body,  uicolorbox_create(   "pencolor", "rgb(32,32,32)" ) );
			liqcell_child_append( body,  uienumbox_create(    "pentrail", "Short", "Off;Short;Medium;Long" ) );
			
			liqcell_child_append( body,  uienumbox_create(    "backstyle", "Colored", "Blank;Colored;Textured" ) );
			liqcell_child_append( body,  uicolorbox_create(   "backcolor", "rgb(0,0,20)" ) );
			liqcell_child_append( body,  uipicturebox_create( "backimage", "/usr/share/liqbase/liqflow/media/stars800x480.png" ) );
															 // stars800x480 comes from
															 // http://www.spacetelescope.org/images/html/heic0720d.html
															 // unsure on status
															 // todo confirm, nasa shots are released to public domain
															 // if not, remove this image and use a pd one


			liqcell_child_append( body,  uienumbox_create(    "starcount", "200", "50;100;150;200;300;400;500" ) );
			liqcell_child_append( body,  uienumbox_create(    "starsize", "Medium", "Small;Medium;Large;Auto" ) );
			liqcell_child_append( body,  uipicturebox_create( "starimage", "/usr/share/liqbase/liqflow/media/star.png" ) );
															 // http://www.clker.com/clipart-23538.html
															 // star comes from here
															 // license says CC public domain in order that they can be uploaded
															 // reasonable :)

			//liqcell_child_append( body,  uisketchbox_create(  "starsketch", "/usr/share/liqbase/liqflow/media/star.sketch" ) );
			liqcell_child_append( body,  uienumbox_create(    "staredgewrap", "Yes", "No;Yes" ) );
			
			liqcell_child_append( body,  uienumbox_create(    "gravity", "Medium", "None;Light;Medium;Strong" ) );
				
			liqcell_child_arrange_autoflow(body);
			
			body->h += 60 + 10;	// make sure it can extend enough to fit the accept button
			
			liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse);
			
		
		liqcell_child_append( self, body );


		//############################# cmdaccept:label
		liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 580, 420, 210, 60);
		liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(cmdaccept, "Save" );
		liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
		liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
		liqcell_propseti(  cmdaccept, "textalign", 2 );
		liqcell_propseti(  cmdaccept, "textaligny", 2 );
		liqcell_handleradd_withcontext(cmdaccept, "click", liqflow_config_cmdaccept_click, self );
		liqcell_child_append(  self, cmdaccept);
		
		
	}


	return self;
}
