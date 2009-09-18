#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>

//#####################################################################
//#####################################################################
//##################################################################### liqcpuspeed :: by gary birkett
//#####################################################################
//#####################################################################


	static const char *cpufreq_filename = "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq";
	//static const char *cpufreq_filename = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq";
	static int cpufreq_read(int *freq)
	{
		FILE *fd;
		int rs;
		*freq=0;
		fd = fopen(cpufreq_filename, "r");
		if(fd==NULL){ liqapp_log("cpufreq, cannot open for reading"); return -1;}	
		rs=fscanf((FILE*) fd,"%i",freq);	
		fclose(fd);	
		if(rs != 1){ liqapp_log("cpufreq, cannot read information"); return -2;}
		return 0;
	}



static int timer_tick(liqcell *self, liqcellmouseeventargs *args, void *liqcpuspeed)
{

	int speedhz=0;
	if(cpufreq_read(&speedhz)==0)
	{
		liqcell_setcaption_printf(liqcpuspeed,"cpu: %imhz",speedhz/1000);
		liqcell_setdirty(self,1);
	}

	//liqapp_log("tick tock");
	
	return 0;
}


liqcell *liqcpuspeed_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqcpuspeed","form", 400,240);

	if(self)
	{
			liqcell_setfont(self, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (50), 0) );
			liqcell_propseti(  self, "textalign", 2 );
			liqcell_propseti(  self, "textaligny",2 );
		liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
		liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
		liqcell_propseti(timer1,"timerinterval", 500 );
		liqcell_setenabled(timer1,1);
		liqcell_child_insert( self,timer1);

		timer_tick(timer1,NULL,self);

	}
	return self;
}
