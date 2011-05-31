#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>

//#####################################################################
//#####################################################################
//##################################################################### ciroclock_minutes :: for ciroip :)
//#####################################################################
//#####################################################################

// not ready yet, needs the timer widget
// 20090420_022637 lcuk : its got one now :)

static int timer_tick(liqcell *self, liqcellmouseeventargs *args, void *context)
{
	//liqapp_log("tick tock");
	liqcell_setdirty(self,1);
	// should also now adjust the timer so that we refresh without wasting anything :)
	// thanks jaffa :)
	unsigned long ticks = liqapp_GetTicks();
	ticks = ticks % 60000;
	liqcell_propseti(self,"timerinterval", (60000-ticks)+10 );
	//liqapp_log("ticks %i, togo %i",(int)ticks, (int)((1000-ticks)) );			
	return 0;
}


static int analog_dirty(liqcell *self, liqcellmouseeventargs *args, liqcell *context)
{
	liqcell_setdirty(context,1);
	return 0;
}


liqcell *ciroclock_minutes_12h_create()
{
	liqcell *self = liqcell_quickcreatewidget("ciroclock_minutes_12h","form", 400,240);

	if(self)
	{

		
		liqcell *analog = liqcell_quickcreatevis("analog",   "myclock",   0,0,   -1,-1 ); 
		liqcell *analoghost = liqcell_quickcreatevis("analoghost",   "host",   0,70,   100,100 );
		
		liqcell_setcontent(analoghost,analog); 
		liqcell_handleradd_withcontext(analog,"dirty",analog_dirty,self);
		liqcell_propseti(     analoghost,"lockaspect",1);
		liqcell_handleradd_withcontext(analoghost,"click",liqcell_easyhandler_content_zoom_click,self);
		
		liqcell_child_insert( self, analoghost    );

		liqcell_child_insert( self, liqcell_quickcreatevis("clock",   "time",   100,0,   300,240 )    );

		liqcell_propsets(     liqcell_child_lookup( self,"clock"),"timeformat","%l:%M%P");
		liqcell_propseti(     liqcell_child_lookup( self,"clock"),"textalign", 2);
		liqcell_propseti(     liqcell_child_lookup( self,"clock"),"textaligny",2);
		liqcell_propsets(     liqcell_child_lookup( self,"clock"),"fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
		liqcell_propseti(     liqcell_child_lookup( self,"clock"),"fontsize", 74 );

		liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
		liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
		liqcell_propseti(timer1,"timerinterval", 250 );
		liqcell_setenabled(timer1,1);
		liqcell_child_insert( self,timer1);
	}
	return self;
}
