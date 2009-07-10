#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqimage.h>
#include <liqbase/liq_xsurface.h>


//#####################################################################
//#####################################################################
//##################################################################### saveall :: by gary birkett :)
//#####################################################################
//#####################################################################

extern liqcell *mirror;				// mirror of the universe




			
static void savethumbs()
{
	// 20090528_231040 lcuk : this locks up dunno why
	// 20090624_005139 lcuk : trying it as a widget itself, to see if it was initializers at fault
	// 20090709_010456 lcuk : it doesnt now, i fixed it, it was a problem with freeing the image in the cliprect free
	liqapp_log("...creating image");
	liqimage *img = liqimage_newatsize(300,180,0);
	
	liqapp_log("...creating cliprect");
	
	liqcliprect *cr = liqcliprect_newfromimage(img);
	
	liqcell *c=liqcell_getlinkchild_visual(mirror);
	while(c)
	{
		liqcell *cell=c;
	
		liqapp_log("...clearing before cell %s",cell->name);
		liqcliprect_drawclear(cr,0,128,128);
		
		liqapp_log("...painting cell %s",cell->name);
		liqcell_easypaint(cell,cr,0,0,300,180);
	
		liqapp_log("...building filename");

				char 		fmtnow[255];
	 			liqapp_formatnow(fmtnow,255,"yyyymmdd_hhmmss");
				char buf[FILENAME_MAX+1];
				snprintf(buf,FILENAME_MAX,"/home/user/svn/liqbase-playground/src/media/liqbase_cell_thumbnails/%s.png",cell->name  );
	
		liqapp_log("...saving image as '%s'",buf);

				liqimage_pagesavepng(img,buf);
				
		c=liqcell_getlinknext_visual(c);
				
	}
	
	liqapp_log("...releasing cr");
	liqcliprect_release(cr);
	
	liqapp_log("...releasing image");
	liqimage_release(img);
	
	liqapp_log("...done");
	
}





/**	
 * saveall clicked
 */	
static int saveall_click(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// 20090624_011107 lcuk : no need to run anymore for now
	savethumbs();

}
		
liqcell *saveall_create()
{
	liqcell *self = liqcell_quickcreatewidget("saveall","form", 800,480);

	if(self)
	{
		
		liqcell *c;
		c=liqcell_quickcreatevis("saveall",   NULL,   0,0,   800,480 );		
		liqcell_setcaption(   c,"save all" );
		liqcell_propsets(     c,"fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
		liqcell_propseti(     c,"fontsize", 60 );	
		liqcell_propseti(     c,"textalign", 2);
		liqcell_propseti(     c,"textaligny",2);
		liqcell_child_insert( self, c    );

		liqcell_handleradd_withcontext(self,    "click", saveall_click, self );
	}
	return self;
}

