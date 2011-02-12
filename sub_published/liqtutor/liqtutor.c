#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks



#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>

#include <liqbase/liqsketchfont.h>



// 20090701_234727 lcuk : todo replace plus/minus with function to show users or show my event 


liqcell *liqtutor_dayview_create();
liqcell *uitoolcol_create(char *key,char *caption, ...);
liqcell *uitoolbar_create(char *key,char *caption, ...);
liqcell *uitoolitem_create(char *key,char *caption,char *imagefilename,void (*handler)(),void *context);

//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################



	static void bbh_find(liqcell *c,int *bbt,int *bbb)
	{
		//int bbb=0;
		while(c)
		{
			if( (c->classname) && (strcmp(c->classname,"glyphview")==0) )
			{
			//	liqapp_log("sketchfont fnd upto: %s IS GLYPH!",c->name);
				liqcell_sketch_autoload(c);
				liqsketch *sk =	liqcell_getsketch(c);
				if(sk)
				{
					liqapp_log("liqtutor_heightscan item '%s' %d,%d",liqcell_propgets(c,"sketchfilename",""),sk->boundingbox.yt,sk->boundingbox.yb);
					
					if(sk->boundingbox.yt<*bbt) *bbt = sk->boundingbox.yt;
					if(sk->boundingbox.yb>*bbb) *bbb = sk->boundingbox.yb;
				}
			}
			if(liqcell_getlinkchild(c))
			{
				bbh_find(liqcell_getlinkchild(c),bbt,bbb);
				//if(x>bbb)bbb=x;
			}
			
			c=liqcell_getlinknext(c);
		}
	}					

	static int bbh_set(liqcell *c,int *bbt,int *bbb)
	{
		while(c)
		{
			if( (c->classname) && (strcmp(c->classname,"glyphview")==0) )
			{
			//	liqapp_log("sketchfont set upto: %s IS GLYPH!",c->name);
				liqcell_sketch_autoload(c);
				liqsketch *sk =	liqcell_getsketch(c);
				if(sk)
				{
					sk->boundingbox.yt=*bbt;
					sk->boundingbox.yb=*bbb;
					
					
				}
			}
			if(liqcell_getlinkchild(c))
			{
				int x = bbh_set(liqcell_getlinkchild(c),bbt,bbb);
			}
			
			c=liqcell_getlinknext(c);
		}
		return bbb;
	}
	
	static void liqtutor_heightscan(liqcell *self)
	{
		liqcell *ui = self;
		while(ui)
		{
			//liqapp_log("test: %s:%s",ui->name,ui->classname);
			if(liqcell_isclass(ui,"liqtutor")) break;
			ui = liqcell_getlinkparent(ui);
		}
		if(ui)
		{	
			int bbt=2000;
			int bbb=0;
			bbh_find(ui,&bbt,&bbb);
			
			liqapp_log("liqtutor_heightscan %d,%d",bbt,bbb);
			bbh_set(ui,&bbt,&bbb);
		}
	}




	static void liqsketch_adjust(liqsketch *sk, int ox,int oy)
	{
					// now, we must adjust each stroke and point by an amount..
					// then after deep recursion need to adjust it back again
					liqstroke *st = sk->strokefirst;
					while(st)
					{
						liqpoint *pt = st->pointfirst;
						while(pt)
						{
							pt->x-=ox;
							pt->y-=oy;
							pt=pt->linknext;
						}
						st->boundingbox.xl-=ox;
						st->boundingbox.xr-=ox;
						st->boundingbox.yt-=oy;
						st->boundingbox.yb-=oy;
						st=st->linknext;
					}
					sk->boundingbox.xl-=ox;
					sk->boundingbox.xr-=ox;
					sk->boundingbox.yt-=oy;
					sk->boundingbox.yb-=oy;
	}
	
	static void rec(liqsketchfont *sketchfont,liqcell *c, int ox,int oy)
	{
		while(c)
		{
			//liqapp_log("sketchfont rec upto: %s",c->name);
			
			if( (c->classname) && (strcmp(c->classname,"glyphview")==0) )
			{
				//liqapp_log("sketchfont rec upto: %s IS GLYPH!",c->name);
				liqcell_sketch_autoload(c);
				liqsketch *sk =	liqcell_getsketch(c);
				if(sk)
				{
					liqsketch_hold(sk);
					int origxl=sk->boundingbox.xl;
					int origxr=sk->boundingbox.xr;
					int origw=sk->boundingbox.xr - sk->boundingbox.xl;
					int origh=sk->boundingbox.yb - sk->boundingbox.yt;
					
					
					liqsketch_adjust(sk,origxl-4,oy);
					
					int idx = (int)liqcell_gettag(c);
					if(sketchfont)
					{
						//..
						liqapp_log("sketchfont rec adding %d",idx);
						//liqsketchfont_addglyph(sketchfont,(char)idx,sk);
						
						liqsketchfont_addglyph_size(sketchfont,(char)idx,sk, origw+8,origh     );
					}
					
				//	liqsketch_adjust(sk,-oy,-oy);
					liqcell_setsketch(c,NULL);
					liqsketch_release(sk);
				}
				
			}
			if(liqcell_getlinkchild(c)) rec(sketchfont,liqcell_getlinkchild(c),ox,oy);
			
			c=liqcell_getlinknext(c);
		}
	}

void liqsketchfont_saveall(liqcell *ui)
{

	liqapp_log("sketchfont save start");

	liqsketchfont fontcore;
	liqsketchfont *font=&fontcore;
	liqsketchfont_configure(font,canvas.dpix,canvas.dpiy);
	
	liqapp_log("sketchfont recursing:");
	
	rec( font, ui,  340, 128 );

	font->glyphwidths[9 ] = font->avgw * 4;
	font->glyphwidths[32] = font->avgw;
	
	
	liqapp_log("sketchfont saving");
	liqsketchfont_filesave(font,"/home/user/.liqbase/generalfont.liqsketchfont");	
	
	liqapp_log("sketchfont finished");
	
}	
	
//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################









//#####################################################################
//#####################################################################
//##################################################################### liqtutor :: by gary birkett
//#####################################################################
//#####################################################################



	static int backplane_move(liqcell *self, liqcelleventargs *args, void *context)
	{
		//liqapp_log("backplane_move %i,%i",self->x,self->y);
		// todo create new cal weeks depending on what is being brought into view :)

		return 1;
	}
	
	
	static int calday_shown(liqcell *self, liqcelleventargs *args, void *context)
	{
		// 20090417_020706 lcuk : this calendar day entry was displayed for the first time
		
		// lazy load the sketch
		
		

		return 1;
	}
	
	
	static int caldayhead_click(liqcell *self, liqcellclickeventargs *args, void *daybody)
	{
		// 20090413_155053 lcuk : disabling zoom into a day for now
		// it should select the day - like the original liqgraffiti did
		// its too fidgety as it stands
		
		
		//args->newdialogtoopen = self;//liqcell_child_lookup( self, "body" );
		//args->newdialogtoopen = liqcell_child_lookup( self, "body" );

		liqcell *day = daybody;//liqcell_getlinkparent(self);
		
		if(!day)return -1;
		
		
		liqcell *preview = liqcell_child_lookup( day, "view" );
		if(!preview) return -1;
		{
		}
		char *sketchfilename  = liqcell_propgets(preview,"sketchfilename",NULL);
		
		if(!sketchfilename) return -1;


		liqcell *dayview = liqtutor_dayview_create();   //liqcell_quickcreatevis("dayview", "liqtutor_dayview", 0,0, 800,480);
		
		// ponder if this is the right way to do this
		liqcell_setname(dayview,sketchfilename);
		


		liqcell_easyrun(dayview);
		liqcell_release(dayview);
		
		
		
		// make sure we refresh this ;)
		liqcell_setsketch(preview,NULL);
		
		
		
		liqtutor_heightscan(self);


		

		return 1;
	}
	
	static int calday_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		// 20090413_155053 lcuk : disabling zoom into a day for now
		// it should select the day - like the original liqgraffiti did
		// its too fidgety as it stands
		
		
		//args->newdialogtoopen = self;//liqcell_child_lookup( self, "body" );
		//args->newdialogtoopen = liqcell_child_lookup( self, "body" );

		return 1;
	}
	
	
	
	static liqcell *calday_create(int choffset, int x,int y,int w,int h)
	{
	

		int dayw=w;
		int dayh=h;


		char daykey[64];
		snprintf(daykey, sizeof(daykey), "ch%d-%c", choffset,(char)choffset);
		
		// daybody
		// daybody.head
		// daybody.head.tit
		// daybody.view

		//
		liqcell *body = liqcell_quickcreatevis(daykey,NULL,        x,y,w,h);
		
		
		liqcell_handleradd_withcontext(body,    "click",   caldayhead_click,body);

			liqcell_propsets(body,"calendardate",daykey);
			




			//###############################################################
			// init the head font

			liqfont *font = liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0);
			char *caption = daykey;
			int fw = liqfont_textwidth(font,caption) * 1.2;
			int fh = liqfont_textheight(font);


			//###############################################################
			// now, make sure we add a header to the day
			
			liqcell *head = liqcell_quickcreatevis("head",NULL,        0,0,       dayw*0.95,fh);
			//liqcell_propseti(    head,"textalign",1);
			liqcell_setfont(     head, font  );  //liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
			liqcell_setcaption(  head,caption);
			
			
			//liqcell_handleradd_withcontext(head,    "click",   caldayhead_click,body);



			{
				liqcell_propsets_printf(  head, "backcolor", "rgb(50,50,%i)" , choffset % 64);
			}


			liqcell_child_append( body,head );




			//###############################################################
			// now, add the entry cell (and setup to load in a sketch related..)
			liqcell *view = liqcell_quickcreatevis("view","glyphview",        0,fh,       dayw * 0.95,(dayh-fh)*0.95);

			liqcell_propsets_printf(  view, "backcolor", "rgb(0,0,%i)" , choffset % 64);
			
			liqcell_settag(view,(void*)choffset);


			
			
			char buf[FILENAME_MAX];    snprintf(buf,sizeof(buf),"%s/glyph",app.userdatapath);
			
			
			char fnbuf[FILENAME_MAX];
			
			snprintf(fnbuf,sizeof(fnbuf),"%s/%s.sketch",  buf  ,  daykey);
			
			liqcell_propsets(         view, "sketchfilename", fnbuf );

			liqcell_child_append( body,view );
			
			
		//	liqcell_propseti(view,"sketchediting",1);


			//liqcell_handleradd(body,    "click",   calday_click);
			
			
		return body;

	}
	
















































static liqcell *calweek_create(int choffset, int totw,int toth)
{





	liqcell *self = liqcell_quickcreatewidget("weekbody","form", totw,toth);


	int dayw=totw/8;
	int dayh=toth;

	// now, for each day of the week, create a day entry and show it correctly
	int d;
	for(d=0;d<8;d++)
	{
		if(choffset+d>0)
		{
			liqcell *body = calday_create(choffset+d,       dayw*d,0,       dayw,dayh);
			liqcell_child_append( self, body );
		}
	}
	return self;
}



	static int toolitem_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		//args->newdialogtoopen = self;//liqcell_child_lookup( self, "body" );
		//args->newdialogtoopen = liqcell_child_lookup( self, "body" );
		
		//liqcell *dayview = liqtutor_dayview_create();   //liqcell_quickcreatevis("dayview", "liqtutor_dayview", 0,0, 800,480);


		//liqcell_easyrun(dayview);
		//liqcell_release(dayview);
		
		
		//liqapp_log("tool click1");
		
		liqcell *liqtutor = context;
		//liqapp_log("tool click2 context==null?%i",context==NULL);
		
		liqcell *scroller_backplane = liqcell_child_lookup(liqtutor,"scroller.backplane");
		
		//liqapp_log("tool click3");
		if(scroller_backplane)
		{
			//liqapp_log("tool click4");
			int origy = liqcell_propgeti(         liqtutor, "calendar_original_offset", scroller_backplane->y);
			
			//liqapp_log("tool click5");			
			
			liqcell_setpos(scroller_backplane,scroller_backplane->x,origy);
		}
		
		return 1;
	}




liqcell *liqtutor_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqtutor","form", 800,480);

	if(self)
	{


	



		//! create toolbar
		liqcell *tbar = uitoolcol_create("tools","tools",
				uitoolitem_create( "reset",     "reset",         "/usr/share/liqbase/liqtutor/media/quickicons/stock_refresh.png",   (void *) toolitem_click,(void *)self),
				//uitoolitem_create( "delete", "delete",     "/usr/share/liqbase/liqtutor/media/quickicons/gtk-remove.png",           toolitem_click,self),
				//uitoolitem_create( "add",    "add",        "/usr/share/liqbase/liqtutor/media/quickicons/add.png",              toolitem_click,self),
				//uitoolitem_create( "edit", "edit",     "/usr/share/liqbase/liqtutor/media/quickicons/package_graphics.png",           toolitem_click,self),
				//uitoolitem_create( "close",  "close",      "/usr/share/liqbase/liqtutor/media/quickicons/gtk-close.png",    toolitem_click),
				//uitoolitem_create( "back",   "back",       "/usr/share/liqbase/liqtutor/media/quickicons/back.png",              toolitem_click,self),
				NULL);
		
		
		liqcell_setrect(tbar, 0,56-56,56,480-56-56+56);

		liqcell_child_append( self, tbar );



	





		// work out how big each day should be
		int dw=((self->w - tbar->w)/8);
		int dh=(self->h/5);



		int ww=(dw*8);
		int wh=(dh*5);

		liqcell *scrollarea = liqcell_quickcreatevis("scroller",NULL,        tbar->w,0,       ww,self->h);


			liqcell *backplane = liqcell_quickcreatevis("backplane",NULL,        0,0,       ww,self->h);
	

	
				// loop around the weeks
				int cw;
				for(cw=0;cw<32;cw++)
				{
					int chupto = 8 * cw;
					liqcell *cwk = calweek_create( chupto,  ww,dh      );
					liqcell_child_append( backplane, cwk );
				}
	
				liqcell_child_arrange_easycol(backplane);
	
				liqcell_handleradd(backplane,    "move",    backplane_move);
				liqcell_handleradd(backplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );
				
				liqcell_setsize(backplane,backplane->w,backplane->h+56);
				
				liqcell_propseti(         self, "calendar_original_offset", backplane->y );



			liqcell_child_append( scrollarea, backplane );
			


			liqcell *testfont = liqcell_quickcreatevis("testfont",NULL,        0,480-56,       800,56);
			liqcell_setfont(	testfont, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (36), 0) );
			liqcell_setcaption(  testfont,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
			liqcell_propsets(  testfont, "backcolor", "rgb(0,0,0)" );
			liqcell_child_append( scrollarea, testfont );
			

	
		liqcell_child_append( self, scrollarea );
		
		
			liqtutor_heightscan(self);
	 
	}
	
	
	

	return self;
}




//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when liqtreebrowse is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	// 20090414_210111 lcuk : very simple test of an easyrun automaticl opening wrapper
	// 20090414_210124 lcuk : it is clear to me now that easyrun itself should maintain a stack of the items it is currently
	// 20090414_210144 lcuk : showing and in that it willalso be able to list them and show them properly
	
	if(0!=liqcanvas_init( 800,480, 1))
	{
		liqapp_errorandfail(-1,"canvas Init");
		//closeall();
		return -1;
	}
		
	liqcell_easyrun( dialog );
		
	liqcanvas_close();

}

int main (int argc, char* argv[])
{
	if(liqapp_init(   argc,argv ,"liqtutor" ,"0.0.1") != 0)
	{
		{ return liqapp_errorandfail(-1,"liqtutor liqapp_init failed"); }
	}

	liqcell *self = liqtutor_create();
     // remove tools button :)
     liqcell_propseti(self,"easyrun_hidetools",1);
	 

	liqcell_easyrun_internal(self);
	
	liqsketchfont_saveall(self);		// auto generate on shutdown *eek*
	
	liqcell_release(self);
	liqapp_close();

	return 0;
}







