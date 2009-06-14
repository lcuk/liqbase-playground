
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easypaint.h>
#include <liqbase/liqcell_mk_star.h>

//#####################################################################
//#####################################################################
//##################################################################### liqbase
//#####################################################################
//#####################################################################


extern liqcell *mirror;


/**
 * just a silly idea to create and render to a super large image and save it
 */

static void idea()
{
	liqapp_log("...creating image");
	liqimage *img = liqimage_newatsize(4000,2400,0);
	
	liqapp_log("...creating cliprect");
	
	liqcliprect *cr = liqcliprect_newfromimage(img);
	
	liqapp_log("...painting mirror");
	liqcell_easypaint(mirror,cr,0,0,4000,2400);
	
	liqapp_log("...building filename");

				char 		fmtnow[255];
	 			liqapp_formatnow(fmtnow,255,"yyyymmdd_hhmmss");
				char buf[FILENAME_MAX+1];
				snprintf(buf,FILENAME_MAX,"liq.%s.%s.holymoly.png",fmtnow,"lib"  );
	
	liqapp_log("...saving image as '%s'",buf);

				liqimage_pagesavepng(img,buf);
				
	
	liqapp_log("...releasing cr");
	liqcliprect_release(cr);
	
	liqapp_log("...releasing image");
	liqimage_release(img);
	
	liqapp_log("...done");
	
}

static int saveholymoly_click(liqcell *self, liqcellclickeventargs *args, void *context)
{
	idea();
	return 0;
}


static int options_click(liqcell *self, liqcellclickeventargs *args, void *context)
{
	liqcell_easyrun( liqcell_quickcreatevis("liqcontrolpanel", "liqcontrolpanel", 0,0, 0,0) );
	return 0;
}
static int playground_click(liqcell *self, liqcellclickeventargs *args, void *context)
{
	liqcell_easyrun( liqcell_quickcreatevis("playground", "playground", 0,0, 0,0) );
	return 0;
}
static int desktop_click(liqcell *self, liqcellclickeventargs *args, void *context)
{
	liqcell_easyrun( liqcell_quickcreatevis("desktopmanage", "desktopmanage", 0,0, 0,0) );
	return 0;
}

static int hello_click(liqcell *self, liqcellclickeventargs *args, void *context)
{
	liqcell_easyrun( liqcell_quickcreatevis("liqwelcome", "liqwelcome", 0,0, 0,0) );
	return 0;
}

static int widget_click(liqcell *self, liqcellclickeventargs *args, void *context)
{
	//idea();
	return 0;
}


// it is this function which is used by the system to construct an instance
// when you call liqcell_quickcreatevis or liqcell_quickcreatewidget
// a search of the known library is undertaken
// if the class is identified then its constructor is called
// and the result is passed back
// if not, a blank cell is created
// ancestor is defunct as of this moment.

liqcell *liqbase_create()
{

	liqcell *self = liqcell_quickcreatewidget("liqbase","form", 800,480);

	if(self)
	{
		liqcell *meta = mkmeta_group(
							mkmeta_title(        "liqbase"),
							mkmeta_description(  "this is a test description"),
							mkmeta_author(       "liquid@gmail.com"),
							mkmeta_version(      "1.0"),
							NULL);
		liqcell_child_append(self,meta);
		//liqcell_print2(meta);
	


		liqcell_setimage(  self ,  liqimage_cache_getfile( "media/liqbase_back2.jpg",0,0,1) );
		liqcell *thead = uititlebar_create("thead","liqbase","Main liqbase menu screen.");
		liqcell *tbody = liqcell_quickcreatevis("tbody",   "grid",    0,0,   800,480-40-thead->h );


			liqcell * grid_button_insert(liqcell *grid,char *key,char *caption,void (*handler)())
			{

				liqcell *item = liqcell_quickcreatevis(key,   "label",   0,0,  1,1 );

				if(caption && *caption)         liqcell_setcaption(   item, caption);
				//if(description && *description) liqcell_propsets(     item, "description", description);
				liqcell_propseti(     item,	"textalign",2);
				liqcell_propsets(     item,	"fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
				liqcell_propseti(     item,	"fontsize", 24 );
				liqcell_propsets(     item,	"textcolor", "rgb(0,0,0)"  );
				liqcell_propsets(     item,	"backcolor", "rgb(100,200,100)"  );
				
				if(handler) liqcell_handleradd_withcontext(   item,   "click",   handler,self);

				liqcell_child_append(grid,item);

				return item;
			}

			grid_button_insert(tbody, "Hello!",NULL,hello_click);
			grid_button_insert(tbody, "playground (slow!)",NULL,playground_click);
			grid_button_insert(tbody, "desktopmanage",NULL,desktop_click);
			//grid_button_insert(tbody, "Take some pictures",NULL,NULL);
			grid_button_insert(tbody, "Options",NULL,options_click);
			//grid_button_insert(tbody, "Zach Netmon",NULL,NULL);
			
			//liqcell *x=grid_button_insert(tbody, "Save holymoly!",NULL,saveholymoly_click);
			//liqcell_propsets(     x,	"backcolor", "rgb(100,100,200)"  );
			
			//grid_button_insert(tbody, "Quit now",NULL,NULL);
			
			
			//liqcell_child_append( tbody, liqcell_quickcreatevis("liqcontrolpanel", "liqcontrolpanel", 0,0, 0,0) );

			liqcell_child_arrange_easytile(tbody);



		liqcell *tfoot = liqcell_quickcreatevis("tfoot",   "label",   0,0,   800,40 );
		liqcell_setcaption(   tfoot, "contact liquid@gmail.com, lcuk on #maemo");
		liqcell_propseti(     tfoot, "textalign",1);
		liqcell_propsets(     tfoot, "fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
		liqcell_propseti(     tfoot, "fontsize", 22 );
		liqcell_propsets(     tfoot, "textcolor", "rgb(0,0,0)"  );
		liqcell_propsets(     tfoot, "backcolor", "rgb(100,100,150");


		liqcell_child_append( self, thead    );
		liqcell_child_append( self, tbody    );
		liqcell_child_append( self, tfoot    );



		// now stack them..
		liqcell_child_arrange_easycol(self);
	}

	return self;
}


// this is only used when liqbase is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

int main (int argc, char* argv[])
{
	if(liqapp_init(   argc,argv ,"liqbase" ,"0.0.1") != 0)
	{
		{ return liqapp_errorandfail(-1,"liqbase liqapp_init failed"); }
	}

	liqcell *self = liqbase_create();
	liqcell_easyrun(self);

	liqapp_close();

	return 0;
}
