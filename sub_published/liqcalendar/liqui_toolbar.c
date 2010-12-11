

#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easypaint.h>
//#include <liqbase/liqcell_mk_star.h>
#include <liqbase/liqcell_easyhandler.h>


//#####################################################################
//#####################################################################
//##################################################################### uitoolbar - dynamically splits items along width
//#####################################################################
//#####################################################################

	static int uitoolcol_resize(liqcell *self, liqcelleventargs *args, void *context)
	{
		
		liqcell *background = liqcell_child_lookup(self,"background");
		
		liqcell_setsize(background,self->w,self->h);
		
		liqcell_child_arrange_makegrid(background, 1, liqcell_child_countvisible(background) );
		
	}

/**
 * define a tool column  (not tested, just an idea)
 *
 */
liqcell *uitoolcol_create(char *key,char *caption, ...)
{
	

	liqcell *self = liqcell_quickcreatewidget(key,"form", 56,480);

	if(self)
	{


		if(caption && *caption) liqcell_setcaption(   self, caption );
		//liqcell_setimage(  self,  liqimage_cache_getfile( "/usr/share/liqbase/liqcalendar/media/texturestrip_dark.jpg",0,0,0) );
		liqcell_setimage(  self,  liqimage_cache_getfile( "/usr/share/liqbase/liqcalendar/media/toolcol_background.png",0,0,0) );
		liqcell_propseti(  self ,  "lockaspect",0 );


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
		//liqcell *sep = liqcell_quickcreatevis("sep",   "sep",   0,0,  1,480 );
		//	liqcell_propsets(     sep,	"backcolor", "rgb(191,217,56)"  );
		//	liqcell_child_append(self,sep);
		
		// layout
		
		liqcell_child_arrange_easyrow(self);
		
		liqcell_handleradd(   self,   "resize",   uitoolcol_resize);
		
		
	}
	return self;
}


/**
 * define a toolbar
 *
 */

liqcell *uitoolbar_create(char *key,char *caption, ...)
{

	liqcell *self = liqcell_quickcreatewidget(key,"form", 800,56);

	if(self)
	{

		if(caption && *caption) liqcell_setcaption(   self, caption );
		//liqcell_setimage(  self,  liqimage_cache_getfile( "/usr/share/liqbase/liqcalendar/media/texturestrip_dark.jpg",0,0,0) );
		liqcell_setimage(  self,  liqimage_cache_getfile( "/usr/share/liqbase/liqcalendar/media/toolbar_background.png",0,0,0) );
		liqcell_propseti(  self ,  "lockaspect",0 );


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



liqcell *uitoolitem_create(char *key,char *caption,char *imagefilename,void (*handler)(),void *context)
{

	liqcell *self = liqcell_quickcreatewidget(key,"form", 50,50);

	if(self)
	{
		if(caption && *caption) liqcell_setcaption(   self, caption );
		
		liqcell_setimage(     self ,  liqimage_cache_getfile( imagefilename,0,0,1) );
		
		liqcell_propseti(     self ,  "lockaspect",1);
		
		//liqcell_propsets(     self,	"bordercolor", "rgb(100,0,0)"  );

		
		liqcell_handleradd_withcontext(   self,   "click",   handler, context);
		
	}
	return self;
}
