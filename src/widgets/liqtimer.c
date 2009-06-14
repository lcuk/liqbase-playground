#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

//#include "vscreen.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <pthread.h>
#include <sched.h>

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>


//#####################################################################
//#####################################################################
//##################################################################### liqtimer :: by gary birkett
//#####################################################################
//#####################################################################




static int thread_createwithpriority(pthread_t *tid,int threadpriority,void *(*func)(void *),void *arg)
{
//pthread_t 		tid;
pthread_attr_t 	tattr;
struct sched_param 	param;
int ret;
int newprio = threadpriority;//20;


	// initialized with default attributes
	ret = pthread_attr_init(&tattr);
	// safe to get existing scheduling param
	ret = pthread_attr_getschedparam(&tattr, &param);
	// set the priority; others are unchanged

	//liqapp_log("thread schedparam=%i (current)",param.sched_priority);

	param.sched_priority = newprio;
	// setting the new scheduling param
	ret = pthread_attr_setschedparam(&tattr, &param);
	// with new priority specified

	ret = pthread_create(tid, &tattr, func, arg);


//	ret = pthread_create(tid, NULL, func, arg);
	return ret;
}

static void *liqtimer_workthread(void* workthread_data)
{

	liqcell *self = (liqcell *)workthread_data;

	//liqapp_sleep(100 + (rand() % 4000));
	//liqapp_sleep(100 + (rand() % 2000));
	//liqapp_sleep(10 + (rand() % 100));
	
	//liqcell_setdirty(self);
	
	
	
	while(1)
	{
		//liqapp_log("looping..");
		if(liqcell_getenabled(self))
		{
			int dt =  liqcell_propgeti(self,"timerinterval",0);
			if(dt<=0)dt=1;
			liqapp_sleep(dt);
			//liqapp_log("ticking..");
			liqcell_handlerrun(self,"timertick",NULL);
		}
		else
		{
			liqapp_sleep(50);
			//liqcell_handlerrun(keyhit,"timertick",NULL);			
		}
	}
	
	return NULL;
}




liqcell *liqtimer_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqtimer","tool", 0,0);

	if(self)
	{
		
		// todo: should make sure we break out of duldrums if the user enables or disables us
		
		liqcell *meta = mkmeta_group(
							mkmeta_title(        "liqtimer"),
							mkmeta_description(  "a small control to send repeated liqtimer events"),
							mkmeta_author(       "liquid@gmail.com"),
							mkmeta_version(      "1.0"),
							NULL);



		liqcell_setvisible(self,0);	// not visible in the render window ever
		liqcell_setenabled(self,0);
		liqcell_propseti(self,"timerinterval",100);




				pthread_t 		*tid = malloc(sizeof(pthread_t));
				if(!tid)
				{
					liqapp_log("liqtimer, cannot alloc thread");
					return 0;					
				}

				//pthread_t 		tid;
				int tres=thread_createwithpriority(tid,0,liqtimer_workthread,self);
				if(tres)
				{
					liqapp_log("liqtimer, thread create fail");
					free(tid);
					return 0;
				}
				liqcell_setdata(self,tid);
				
				
				//liqcell_propseti(self,"timerenabled",0);
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
	if(liqapp_init(   argc,argv ,"liqtimer" ,"0.0.1") != 0)
	{
		{ return liqapp_errorandfail(-1,"liqtimer liqapp_init failed"); }
	}

	liqcell *self = liqtimer_create();
	liqcell_easyrun_internal(self);
	liqcell_release(self);
	liqapp_close();

	return 0;
}







