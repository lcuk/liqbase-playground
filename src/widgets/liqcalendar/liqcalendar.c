#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

//#include "vscreen.h>



#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>

// 20090701_234724 lcuk :
// 20090701_234725 lcuk :
// 20090701_234725 lcuk :
// 20090701_234725 lcuk :
// 20090701_234725 lcuk :
// 20090701_234726 lcuk :
// 20090701_234726 lcuk :
// 20090701_234726 lcuk :
// 20090701_234726 lcuk :
// 20090701_234727 lcuk :
// 20090701_234727 lcuk :
// 20090701_234727 lcuk : todo replace plus/minus with function to show users or show my event 



//#####################################################################
//#####################################################################
//##################################################################### liqcalendar :: by gary birkett
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


		liqcell *dayview = liqcalendar_dayview_create();   //liqcell_quickcreatevis("dayview", "liqcalendar_dayview", 0,0, 800,480);
		
		// ponder if this is the right way to do this
		liqcell_setname(dayview,sketchfilename);
		


		liqcell_easyrun(dayview);
		liqcell_release(dayview);
		
		
		
		// make sure we refresh this ;)
		liqcell_setsketch(preview,NULL);

		

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
	
	
	
	static liqcell *calday_create(time_t *dayptr, int x,int y,int w,int h)
	{
	
		// know what NOW is
		time_t      now;     time(&now);
		struct tm * nowts  = localtime(&now);
		int         nowday = nowts->tm_wday;
		time_t      nowmidnight=(now - (now%86400));

		int dayw=w;
		int dayh=h;
		
		//time_t      day     = wks + (d * 86400);
		struct tm * dayts   = localtime(dayptr);//&day);
		int         dayday  = dayts->tm_wday;
		time_t      daymidnight=(*dayptr - (*dayptr%86400));
		
		//int istoday = ((nowts->tm_mon==dayts->tm_mon)); // && (nowts->tm_mday==dayts->tm_mday));
		int istoday = (nowmidnight==daymidnight);

		//liqapp_log("test1.now %i,%i,%i,%i",nowts->tm_year,nowts->tm_mon,nowts->tm_mday,istoday);
		//liqapp_log("test2.day %i,%i,%i,%i",dayts->tm_year,dayts->tm_mon,dayts->tm_mday,istoday);
		
		char daybuf[64];
		strftime(daybuf, sizeof(daybuf), "%Y%m%d", dayts);
		
		char daykey[64];
		snprintf(daykey, sizeof(daykey), "day%s", daybuf);
		
		// daybody
		// daybody.head
		// daybody.head.tit
		// daybody.view

		//
		liqcell *body = liqcell_quickcreatevis(daykey,NULL,        x,y,w,h);
		
		
		liqcell_handleradd_withcontext(body,    "click",   caldayhead_click,body);

			liqcell_propsets(body,"calendardate",daykey);
			


			//###############################################################
			// build up a string showing the day
			char buff[64];
			//if(dayts->tm_mday==1)
			//	strftime(buff, 64, "%B %e", dayts);
			//else
				strftime(buff, 64, "%e", dayts);

			//###############################################################
			// init the head font

			liqfont *font = liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (16), 0);
			char *caption = buff;
			int fw = liqfont_textwidth(font,caption) * 1.2;
			int fh = liqfont_textheight(font);


			//###############################################################
			// now, make sure we add a header to the day
			
			liqcell *head = liqcell_quickcreatevis("head",NULL,        0,0,       dayw*0.95,fh);
			//liqcell_propseti(    head,"textalign",1);
			liqcell_setfont(     head, font  );  //liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
			liqcell_setcaption(  head,caption);
			
			
			//liqcell_handleradd_withcontext(head,    "click",   caldayhead_click,body);


			if(istoday)
			{
				liqcell_propsets(         head, "backcolor", "rgb(100,50,50)" );
			}
			else
			{
				liqcell_propsets_printf(  head, "backcolor", "rgb(50,50,%i)" , 50 + (31-dayts->tm_mday) * 100 / 31);
			}


			liqcell_child_append( body,head );

			//###############################################################
			// maybe add another label indicating the month

			if(dayts->tm_mday==1)
			{
				// first day of the month has an additional label

				liqcell *tit = liqcell_quickcreatevis("monthname",NULL,        dayw*0.1,0,       dayw*0.85,fh);

				strftime(buff, 64, "%B", dayts);
				liqcell_propseti(  tit,"textalign",0);
				liqcell_setfont(   tit, liqfont_hold(font)  );  //liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
				liqcell_setcaption(  tit,buff);
				liqcell_propsets(  tit, "textcolor", "rgb(0,255,0)" );
				liqcell_propseti(    tit,"textalign",2);

				liqcell_child_append( head,tit );
			}



			//###############################################################
			// now, add the entry cell (and setup to load in a sketch related..)
			liqcell *view = liqcell_quickcreatevis("view",NULL,        0,fh,       dayw * 0.95,(dayh-fh)*0.95);

			if(istoday)
			{
				liqcell_propsets(         view, "backcolor", "rgb(100,0,0)" );
			}
			else
			{
				liqcell_propsets_printf(  view, "backcolor", "rgb(0,0,%i)" , (31-dayts->tm_mday) * 100 / 31);
			}

			//if( (day >= val) && (day<(val+86400)) )
			//{
			//	liqcell_setsketch(   view,    liqsketch_newfromfile("media/rose.sketch"));
			//}
			//	liqcell_setsketch(   view,    liqsketch_newfromfile("media/rose.sketch"));

			// set this as editable
			
			
			char buf[FILENAME_MAX];    snprintf(buf,sizeof(buf),"%s/cal",app.userdatapath);
			
			
			char fnbuf[FILENAME_MAX];
			
			snprintf(fnbuf,sizeof(fnbuf),"%s/%s.sketch",  buf  ,  daykey);
			
			liqcell_propsets(         view, "sketchfilename", fnbuf );
			
			
			//liqcell_setsketch(   view,    liqsketch_newfromfile("media/rose.sketch"));



			liqcell_child_append( body,view );


			//liqcell_handleradd(body,    "click",   calday_click);
			
			
		return body;

	}
	
















































static liqcell *calweek_create(time_t *weekptr, int totw,int toth)
{
	// find out when we are
	time_t      week = *weekptr;
	struct tm * weekts  = localtime(&week);
	int         weekday = weekts->tm_wday;


	// know what NOW is
	time_t      now;     time(&now);
	struct tm * nowts  = localtime(&now);
	int         nowday = nowts->tm_wday;

	// now, find out what the start of the week is
	time_t      wks     = week - (86400 * (nowts->tm_wday-1));
	struct tm * wksts   = localtime(&wks);
	int         wksday  = wksts->tm_wday;



	// know what NOW is

	struct tm t;

	t.tm_year = 2009-1900;
	t.tm_mon = 1;
	t.tm_mday = 14;
	t.tm_hour = 0;  /* hour, min, sec don't matter */
	t.tm_min = 0;   /* as long as they don't cause a */
	t.tm_sec = 0;   /* new day to occur */
	t.tm_isdst = 0;

	time_t      val;
	val = mktime(&t);
	struct tm * valts   = localtime(&val);




			char buff[64];

				strftime(buff, 64, "%B %e", valts);



	//liqapp_log("val: %s",buff);
	



	liqcell *self = liqcell_quickcreatewidget("weekbody","form", totw,toth);


	int dayw=totw/7;
	int dayh=toth;

	// now, for each day of the week, create a day entry and show it correctly
	int d;
	for(d=0;d<7;d++)
	{
		time_t      day     = wks + (d * 86400);
		struct tm * dayts   = localtime(&day);
		int         dayday  = dayts->tm_wday;
		
		
		liqcell *body = calday_create(&day,       dayw*d,0,       dayw,dayh);
		liqcell_child_append( self, body );
	}
	return self;
}



	static int toolitem_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		//args->newdialogtoopen = self;//liqcell_child_lookup( self, "body" );
		//args->newdialogtoopen = liqcell_child_lookup( self, "body" );
		
		//liqcell *dayview = liqcalendar_dayview_create();   //liqcell_quickcreatevis("dayview", "liqcalendar_dayview", 0,0, 800,480);


		//liqcell_easyrun(dayview);
		//liqcell_release(dayview);
		
		
		//liqapp_log("tool click1");
		
		liqcell *liqcalendar = context;
		//liqapp_log("tool click2 context==null?%i",context==NULL);
		
		liqcell *scroller_backplane = liqcell_child_lookup(liqcalendar,"scroller.backplane");
		
		//liqapp_log("tool click3");
		if(scroller_backplane)
		{
			//liqapp_log("tool click4");
			int origy = liqcell_propgeti(         liqcalendar, "calendar_original_offset", scroller_backplane->y);
			
			//liqapp_log("tool click5");			
			
			liqcell_setpos(scroller_backplane,scroller_backplane->x,origy);
		}
		
		return 1;
	}




liqcell *liqcalendar_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqcalendar","form", 800,480);

	if(self)
	{

		liqcell *meta = mkmeta_group(
							mkmeta_title(        "liqcalendar"),
							mkmeta_description(  "a dynamic hand drawn wall calander"),
							mkmeta_author(       "liquid@gmail.com"),
							mkmeta_version(      "1.0"),
							NULL);


		//! create toolbar
		liqcell *tbar = uitoolcol_create("tools","tools",
				uitoolitem_create( "reset",     "reset",         "media/quickicons/stock_refresh.png",    toolitem_click,self),
				//uitoolitem_create( "delete", "delete",     "media/quickicons/gtk-remove.png",           toolitem_click,self),
				//uitoolitem_create( "add",    "add",        "media/quickicons/add.png",              toolitem_click,self),
				//uitoolitem_create( "edit", "edit",     "media/quickicons/package_graphics.png",           toolitem_click,self),
				//uitoolitem_create( "close",  "close",      "media/quickicons/gtk-close.png",    toolitem_click),
				//uitoolitem_create( "back",   "back",       "media/quickicons/back.png",              toolitem_click,self),
				NULL);
		
		
		liqcell_setrect(tbar, 0,56-56,56,480-56-56+56);

		liqcell_child_append( self, tbar );






		// know what NOW is
		time_t      now;     time(&now);
		struct tm * nowts  = localtime(&now);
		int         nowday = nowts->tm_wday;
		int         nowwk = nowday / 7;

		// work out how big each day should be
		int dw=((self->w - tbar->w)/7);
		int dh=(self->h/5);



		int ww=(dw*7);
		int wh=(dh*5);

		liqcell *scrollarea = liqcell_quickcreatevis("scroller",NULL,        tbar->w,0,       ww,self->h);


			liqcell *backplane = liqcell_quickcreatevis("backplane",NULL,        0,-dh * 12,       ww,self->h);
	
				// start sometime in the past
				time_t      run = now - (86400 * 7 * 14);
				struct tm * runts  = localtime(&run);
	
				// loop around the weeks
				int cw;
				for(cw=0;cw<260;cw++)
				{
					liqcell *cwk = calweek_create( &run,  ww,dh      );
	
					liqcell_child_append( backplane, cwk );
	
					run += 86400 * 7;
					runts  = localtime(&run);
				}
	
				liqcell_child_arrange_easycol(backplane);
	
				liqcell_handleradd(backplane,    "move",    backplane_move);
				liqcell_handleradd(backplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );
				
				
				
				liqcell_propseti(         self, "calendar_original_offset", backplane->y );



			liqcell_child_append( scrollarea, backplane );
			
			
	
		liqcell_child_append( self, scrollarea );
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
	if(liqapp_init(   argc,argv ,"liqcalendar" ,"0.0.1") != 0)
	{
		{ return liqapp_errorandfail(-1,"liqcalendar liqapp_init failed"); }
	}

	liqcell *self = liqcalendar_create();
	liqcell_easyrun_internal(self);
	liqcell_release(self);
	liqapp_close();

	return 0;
}







