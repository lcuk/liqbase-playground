#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>

//#####################################################################
//#####################################################################
//##################################################################### ciroclock :: for ciroip :)
//#####################################################################
//#####################################################################

// not ready yet, needs the timer widget
// 20090420_022637 lcuk : its got one now :)

static int timer_tick(liqcell *self, liqcellmouseeventargs *args, void *context)
{
	liqapp_log("tick tock '%s' %i", self->name,self->usagecount);
	liqcell_setdirty(self,1);
	// should also now adjust the timer so that we refresh without wasting anything :)
	// thanks jaffa :)
	unsigned long ticks = liqapp_GetTicks();
	ticks = ticks % 1000;
	liqcell_propseti(self,"timerinterval", (1000-ticks)+10 );
	//liqapp_log("ticks %i, togo %i",(int)ticks, (int)((1000-ticks)) );
    
    
    
    
	return 0;
}


liqcell *ciroclock_create()
{
	liqcell *self = liqcell_quickcreatewidget("ciroclock","form", 400,100);

	if(self)
	{

		liqcell_child_insert( self, liqcell_quickcreatevis("clock",   "time",   0,0,   400,100 )    );

		liqcell_propsets(     liqcell_child_lookup( self,"clock"),"timeformat","%H:%M:%S");
		liqcell_propseti(     liqcell_child_lookup( self,"clock"),"textalign",2);
		liqcell_propsets(     liqcell_child_lookup( self,"clock"),"fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
		liqcell_propseti(     liqcell_child_lookup( self,"clock"),"fontsize", 72 );



 //   liqcell_hold(self); // Sun Aug 30 20:21:12 2009 lcuk : crap, i hate this, but if i release and the timer fires it crashes
    // Sun Aug 30 20:21:30 2009 lcuk : this is a memory leak in waiting
    // Sun Aug 30 20:21:41 2009 lcuk : timers need to be handlable and cancelable on demand
    // Sun Aug 30 20:21:54 2009 lcuk : at the moment the handle is lost and it must be retained and killed
    // Mon Aug 31 21:51:27 2009 lcuk : SORTED.  threads created in timers are killed along with the instance.
    // Mon Aug 31 21:51:41 2009 lcuk : still need to handle real cleanup, but that bridge will come later.
    
		liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
		liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
		liqcell_propseti(timer1,"timerinterval", 250 );
		liqcell_setenabled(timer1,1);
		liqcell_child_insert( self,timer1);

	}
	return self;
}
