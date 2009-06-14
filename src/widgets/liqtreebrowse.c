#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easypaint.h>
#include <liqbase/liqcell_mk_star.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqbase.h>

//#####################################################################
//#####################################################################
//##################################################################### test helpers
//#####################################################################
//#####################################################################
/**
 * insert a group of cells based on va_list
 *
 */

liqcell *liqcell_child_multiinserta(liqcell *self,va_list arg)
{
	while(1)
	{
		liqcell *c = va_arg(arg, liqcell *);
		if(!c)break;
		liqcell_child_insert(self,c);
	};
	return self;
}


/**
 * insert a group of cells based on ...
 *
 */

liqcell *liqcell_child_multiinsert(liqcell *self,...)
{
	va_list arg;
	va_start(arg, self);
	liqcell_child_multiinserta(self,arg);
	va_end(arg);
	return self;
}



/**
 * insert a group of cells based on ...
 *
 */

liqcell *liqcell_child_multiappend(liqcell *self,...)
{
	va_list arg;
	va_start(arg, self);
	while(1)
	{
		liqcell *c = va_arg(arg, liqcell *);
		if(!c)break;
		liqcell_child_append(self,c);
	};
	//liqcell_child_multiinserta(self,arg);
	va_end(arg);
	return self;
}








//#####################################################################
//#####################################################################
//##################################################################### uitoolbar - dynamically splits items along width
//#####################################################################
//#####################################################################
/**
 * define a tool column  (not tested, just an idea)
 *
 */
static liqcell *uitoolcol_create(char *key,char *caption, ...)
{
	

	liqcell *self = liqcell_quickcreatewidget(key,"form", 56,480);

	if(self)
	{


		if(caption && *caption) liqcell_setcaption(   self, caption );
		//liqcell_setimage(  self,  liqimage_cache_getfile( "media/texturestrip_dark.jpg",0,0,0) );
		liqcell_setimage(  self,  liqimage_cache_getfile( "media/toolcol_background.png",0,0,0) );


		// main background
		liqcell *back = liqcell_quickcreatevis("background",   "background",   0,0,   800,56 );

			int cnt=0;
			va_list arg;
			va_start(arg, caption);
			while(1)
			{
				liqcell *c = va_arg(arg, liqcell *);
				if(!c)break;
				liqcell_child_append(back,c);
				cnt++;
			};
			//liqcell_child_multiinserta(self,arg);
			va_end(arg);
			
			
			int ch = self->h / cnt;
			// extra validation
			if((ch*cnt)>self->h)ch--;		
			
			liqcell *c=liqcell_getlinkchild(back);
			while(c)
			{
				//...
				if(liqcell_getvisible(c))
				{
					liqcell_setsize(c,56,ch);
				}
				c=liqcell_getlinknext(c);
			}
			liqcell_child_arrange_easycol(back);

			liqcell_child_append(self,back);
		
		
		// divider
		liqcell *sep = liqcell_quickcreatevis("sep",   "sep",   0,0,  1,480 );
			liqcell_propsets(     sep,	"backcolor", "rgb(191,217,56)"  );
			liqcell_child_append(self,sep);
		
		// layout
		
		liqcell_child_arrange_easyrow(self);
		
		
	}
	return self;
}


/**
 * define a toolbar
 *
 */

static liqcell *uitoolbar_create(char *key,char *caption, ...)
{

	liqcell *self = liqcell_quickcreatewidget(key,"form", 800,56);

	if(self)
	{

		if(caption && *caption) liqcell_setcaption(   self, caption );
		//liqcell_setimage(  self,  liqimage_cache_getfile( "media/texturestrip_dark.jpg",0,0,0) );
		liqcell_setimage(  self,  liqimage_cache_getfile( "media/toolbar_background.png",0,0,0) );


		// main background
		liqcell *back = liqcell_quickcreatevis("background",   "background",   0,0,   800,56 );

			int cnt=0;
			va_list arg;
			va_start(arg, caption);
			while(1)
			{
				liqcell *c = va_arg(arg, liqcell *);
				if(!c)break;
				liqcell_child_append(back,c);
				cnt++;
			};
			//liqcell_child_multiinserta(self,arg);
			va_end(arg);
			
			
			int cw = self->w / cnt;
			// extra validation
			if((cw*cnt)>self->w)cw--;		
			
			liqcell *c=liqcell_getlinkchild(back);
			while(c)
			{
				//...
				if(liqcell_getvisible(c))
				{
					liqcell_setsize(c,cw,56);
				}
				c=liqcell_getlinknext(c);
			}
			liqcell_child_arrange_easyrow(back);

			liqcell_child_append(self,back);
		
		
		// divider
		liqcell *sep = liqcell_quickcreatevis("sep",   "sep",   0,0,   800,1 );
			liqcell_propsets(     sep,	"backcolor", "rgb(191,217,56)"  );
			liqcell_child_append(self,sep);
		
		// layout
		
		liqcell_child_arrange_easycol(self);
		
		
	}
	return self;
}



static liqcell *uitoolitem_create(char *key,char *caption,char *imagefilename,void (*handler)())
{

	liqcell *self = liqcell_quickcreatewidget(key,"form", 50,50);

	if(self)
	{
		if(caption && *caption) liqcell_setcaption(   self, caption );
		
		liqcell_setimage(     self ,  liqimage_cache_getfile( imagefilename,0,0,1) );
		
		liqcell_propseti(     self ,  "lockaspect",1);
		
		//liqcell_propsets(     self,	"bordercolor", "rgb(100,0,0)"  );
		
		
		
		liqcell_handleradd(   self,   "click",   handler);
		
	}
	return self;
}


//#####################################################################
//#####################################################################
//##################################################################### liqtreebrowse
//#####################################################################
//#####################################################################

extern liqcell *universe;
extern liqcell *mirror;






static int deepview_nobble_click(liqcell *self, liqcellclickeventargs *args, void *context)
{
	liqapp_log("nobble");
	
	liqcell *deepview = liqcell_getbasewidget(self);
	liqapp_log("nobble1");
	if(!deepview)return -1;
	
	liqapp_log("nobble2");
	liqcell *head = liqcell_local_lookup(deepview,"head");
	if(!head)return -2;
	
	liqcell *preview = liqcell_local_lookup(head,"preview");
	
	
	
	liqapp_log("nobble3");
	liqcell *childmat = liqcell_local_lookup(deepview,"childmat");
	liqapp_log("nobble4");
	
	if(!childmat)
	{
		// we MUST be clicking open
		// lets get hold of our context and create the whole branch
		liqapp_log("nobble5");
	}
	else
	{
		liqapp_log("nobble6");
		if(liqcell_getvisible(childmat))
		{
			// already visible, we MUST be hiding it
			liqapp_log("nobble7");
			liqcell_setvisible(childmat,0);
		}
		else
		{
			// not visible, we must be showing it
			liqapp_log("nobble8");
			liqcell_setvisible(childmat,1);
		}
	}
	
	while(deepview && childmat)
	{
		liqapp_log("nobble9 %s",deepview->name);
		liqcell_child_arrange_easycol(childmat);
		liqcell_child_arrange_easycol(deepview);
		childmat->x=50;
		
		liqapp_log("nobble10");
		
		// walk backwards for as long as we have
		liqcell *par = liqcell_getlinkparent(deepview);
		
		liqapp_log("nobble11");
		childmat=NULL;
		deepview=NULL;
		if(par && liqcell_isclass(par,"childmat"))
		{
			liqapp_log("nobble12");
			childmat = par;
			deepview = liqcell_getbasewidget(par);			
		}
		
	}
	
	liqapp_log("nobble13");
	return 0;
}





static liqcell *deepview(liqcell *node,int recdep,liqfont *font)
{
	int xl=0;
	int ww=800;
	
	if(recdep<8)
	{
		xl=recdep*50;
	}
	else
	{
		xl=8*50;
	}
	ww=800-xl;
	
	int fh = liqfont_textheight(font);
	
	// deepview
	// deepview.head
	// deepview.head.plusminus
	// deepview.head.preview
	// deepview.head.title
	// deepview.childmat
	
	liqcell *self = liqcell_quickcreatewidget(node->name, "deepview", ww, fh);
	
	
		//liqcell_propsets(     self,	"backcolor", "rgb(255,255,255)"  );
		liqcell *head = liqcell_quickcreatevis("head", "panel", 0, 0, self->w, self->h);


			//########################################## create the nobble
			liqcell *nobble = liqcell_quickcreatevis("plusminus", "button", 0, 0, 50, fh);
			liqcell_handleradd(   nobble,   "click",   deepview_nobble_click);
			if(recdep<4)
			{
				// already expanded..
						liqcell_setimage(  nobble, liqimage_cache_getfile( "media/quickicons/gtk-remove.png" ,0,0,1) );
						liqcell_propseti(  nobble,"lockaspect",1);
			}
			else
			{
				// not yet open
				if(liqcell_getlinkchild(node) || liqcell_getcontent(node))
				{
					// there are children to recurse later
						liqcell_setimage(  nobble, liqimage_cache_getfile( "media/quickicons/add.png" ,0,0,1) );
						liqcell_propseti(  nobble,"lockaspect",1);
				}
				else
				{
					// no children of any sort under neath us..
					// leave it blank, no need to have anything shown here
					liqcell_setvisible(nobble,0);
				}
				
			}
			liqcell_child_insert(head, nobble);
			

		
		
		
			//########################################## create the preview
			liqcell *preview = liqcell_quickcreatevis("preview", "icon", 50, 0, 50, fh);
			// if its a visible cell we add the preview
			// if not, we can add an icon based on its classname
			
			// 20090414_012255 lcuk : set the content NO MATTER WHAT KIND OF ITEM IT IS!
			// 20090414_012306 lcuk : this is important becase we will be using it later
			liqcell_setcontent(preview, node);
			
			if(liqcell_getvisible(node))
			{
				// live preview
				liqcell_propseti(  preview,"lockaspect",1);
			}
			else
			{
				if(liqcell_getlinkchild(node))
				{
					// has contents underneath
					liqcell_setimage(  preview, liqimage_cache_getfile( "media/quickicons/folder.png" ,0,0,1) );
					liqcell_propseti(  preview,"lockaspect",1);
				}
				else
				{
					// is terminal node
					liqcell_setimage(  preview, liqimage_cache_getfile( "media/quickicons/txt.png" ,0,0,1) );
					liqcell_propseti(  preview,"lockaspect",1);
				}
			}
			liqcell_child_insert(head, preview);
			
			
			//########################################## create the caption itself
			liqcell *tl = liqcell_quickcreatevis(node->name, "label", 100, 0, ww-100, fh);
			liqcell_setfont(tl, liqfont_hold(font));
			
			//liqcell_propsets(tl,	"textcolor", "rgb(0,0,0)"  );
			liqcell_child_insert(head, tl);
			
		
		liqcell_child_insert(self, head);
		
		
		
		//liqcell_propsets(self, "bordercolor", "rgb(255,0,0)");
	
	
		int yy=0;
		
		
		liqcell *c;
		if(recdep<4)
		{
			
			// 20090414_012420 lcuk : create a mat for the children to sit on
			liqcell *childmat = liqcell_quickcreatevis("childmat", "childmat", 50, self->h, self->w-50, 0);
			
				c = liqcell_getcontent(node);
				if(c)
				{
					liqcell *r = deepview(c,recdep+1,font);
					r->x=00;
					r->y=yy;
					
					yy+=r->h;
					childmat->h+=r->h;
					self->h+=r->h;
					
					liqcell_child_append(childmat, r);
				}
				
				c = liqcell_getlinkchild(node);
				while(c)
				{
			
					liqcell *r = deepview(c,recdep+1,font);
					r->x=00;
					r->y=yy;
					
					yy+=r->h;
					childmat->h+=r->h;
					self->h+=r->h;
					
					liqcell_child_append(childmat, r);
			
					c=liqcell_getlinknext(c);
				}
				
			liqcell_child_append(self, childmat);
			
			
		}
	return self;
}





static int toolitem_click(liqcell *self, liqcellclickeventargs *args, void *context)
{
	return 0;
}


static int liqtreebrowse_tbody_shown(liqcell *tbody, liqcelleventargs *args, void *context)
{
	// this is a test function
	
	liqapp_log("--------------------------------tree shown start");
		//liqcell_propsets(     tbody,	"backcolor", "rgb(255,255,255)"  );
	
	
			liqfont *font = liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0);
			// ensure we are pointing at the correct default scaled version
			liqfont_setview(font,1,1);
			
			liqcell *dv=deepview(universe,0,font);
			liqcell_handleradd(dv, "mouse", liqcell_easyhandler_kinetic_mouse);
			
			liqcell_child_append(tbody,dv);
			
			
			//liqcell_print(tbody,"shown",0);
		
	liqapp_log("--------------------------------tree shown end");
			
		return 1;
}


liqcell *liqtreebrowse_create()
{

	liqcell *self = liqcell_quickcreatewidget("liqtreebrowse","form", 800,480);

	if(self)
	{
		liqcell *meta = mkmeta_group(
							mkmeta_title(        "liqtreebrowse"),
							mkmeta_description(  "this is a test description"),
							mkmeta_author(       "liquid@gmail.com"),
							mkmeta_version(      "1.0"),
							NULL);
		liqcell_child_append(self,meta);

		//! create header
		//liqcell *thead = uititlebar_create("thead","liqtreebrowse","Main liqtreebrowse menu screen.");
		
		//! create toolbar
		liqcell *tbar = uitoolbar_create("tools","tools",
				uitoolitem_create( "back",   "back",       "media/quickicons/back.png",              toolitem_click),
				uitoolitem_create( "up",     "up",         "media/quickicons/up.png",    toolitem_click),
				uitoolitem_create( "add",    "add",        "media/quickicons/add.png",              toolitem_click),
				uitoolitem_create( "delete", "delete",     "media/quickicons/gtk-remove.png",           toolitem_click),
				uitoolitem_create( "search", "search",     "media/quickicons/find.png",           toolitem_click),
				uitoolitem_create( "close",  "close",      "media/quickicons/gtk-close.png",    toolitem_click),
				NULL);
		
		//! create body
		liqcell *tbody = liqcell_quickcreatevis("tbody",   "grid",    0,0,   800, 480 -  tbar->h );
		liqcell_handleradd(   tbody,   "shown",   liqtreebrowse_tbody_shown);



		//liqcell_child_append( self, thead    );
		liqcell_child_append( self, tbar     );
		liqcell_child_append( self, tbody    );


		// now stack them..
		liqcell_child_arrange_easycol(self);
	}

	return self;
}


// this is only used when liqtreebrowse is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

int main (int argc, char* argv[])
{
	if(liqapp_init(   argc,argv ,"liqtreebrowse" ,"0.0.1") != 0)
	{
		{ return liqapp_errorandfail(-1,"liqtreebrowse liqapp_init failed"); }
	}

	liqcell *self = liqtreebrowse_create();
	liqcell_easyrun(self);

	liqapp_close();

	return 0;
}














