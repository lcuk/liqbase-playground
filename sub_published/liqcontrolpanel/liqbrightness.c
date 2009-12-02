#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>


#include <sys/socket.h>
#include <sys/un.h>
#include  <dlfcn.h>


//#####################################################################
//#####################################################################
//##################################################################### liqbrightness :: by gary birkett :)
//#####################################################################
//#####################################################################

// 20090706_190613 lcuk : todo this code needs the scaling factors setting correctly in the setbrightness functions
// 20090706_190712 lcuk : currently passing a scalar from 16..240


struct dsme_message_abl
{
  int len;
  int request;
  void *value;
};


//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################




static void *dsmesock_dl_handle=NULL;
static int (*dsmesock_connect)() = NULL;
static void (*dsmesock_send) (int, struct dsme_message_abl *) = NULL;
static void (*dsmesock_close)(int) = NULL;


	static int liqbrightness_setbrightness_dsme(liqcell *liqbrightness,int newbrightness)
	{
		// thanks to rm_you, jott, stskeeps and austin che for this code and zach habersang for reminding me it existed
		liqapp_log("liqbrightness_setbrightness_dsme setting to: %i",newbrightness);
		if(!dsmesock_dl_handle)
		{
			liqapp_log("liqbrightness_setbrightness_dsme initializing dl symbols for libdsme.so.0.1.0");
			char *error;
			dlerror(); // clear dlerror cache
			dsmesock_dl_handle = dlopen("libdsme.so.0.1.0", RTLD_LAZY);
			if((error = dlerror()) != NULL)
			{
				liqapp_log("liqbrightness_setbrightness_dsme error opening lib: %s",error);
				return -1;
			}
			*(void **)(&dsmesock_connect) = dlsym(dsmesock_dl_handle, "dsmesock_connect");
			if((error = dlerror()) != NULL)
			{
				liqapp_log("liqbrightness_setbrightness_dsme error getting dsmesock_connect: %s",error);
				dlclose(dsmesock_dl_handle);
				return -1;
			}
			*(void **)(&dsmesock_send) = dlsym(dsmesock_dl_handle, "dsmesock_send");
			if((error = dlerror()) != NULL)
			{
				liqapp_log("liqbrightness_setbrightness_dsme error getting dsmesock_send: %s",error);
				dlclose(dsmesock_dl_handle);
				return -1;
			}
			*(void **)(&dsmesock_close) = dlsym(dsmesock_dl_handle, "dsmesock_close");
			if((error = dlerror()) != NULL)
			{
				liqapp_log("liqbrightness_setbrightness_dsme error getting dsmesock_close: %s",error);
				dlclose(dsmesock_dl_handle);
				return -1;
			}
		}
		int conn = dsmesock_connect();
		if(!conn)
		{
			liqapp_log("liqbrightness_setbrightness_dsme could not connect");
			return -1;			
		}
		liqapp_log("liqbrightness_setbrightness_dsme setting up message");		
		// from the bowels of abl
		struct dsme_message_abl message;
		message.len = 0x0c;
		message.request = 0x289;
		message.value = (void *) (newbrightness);
		liqapp_log("liqbrightness_setbrightness_dsme sending message");
		dsmesock_send(conn, &message);
		liqapp_log("liqbrightness_setbrightness_dsme closing");
		dsmesock_close(conn);
	}
	
	
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################


	static int liqbrightness_setbrightness_fakedsme(liqcell *liqbrightness,int newbrightness)
	{
		// thanks to rm_you, jott, stskeeps and austin che for this code and zach habersang for reminding me it existed
		liqapp_log("liqbrightness_setbrightness_fakedsme setting to: %i",newbrightness);
		struct sockaddr_un addr;
		int dsmesock;
		dsmesock = socket(PF_UNIX, SOCK_STREAM, 0);
		if (dsmesock < 0)
		{
			liqapp_log("liqbrightness_setbrightness_fakedsme dsme socket failed");
			return -1;
		}
		liqapp_log("liqbrightness_setbrightness_fakedsme clearing socket");
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, "/tmp/dsmesock");
		 
		liqapp_log("liqbrightness_setbrightness_fakedsme connecting");
		if (connect(dsmesock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			close(dsmesock);
			liqapp_log("liqbrightness_setbrightness_fakedsme couldn't connect to dsme");
			return -2;
		}
		
		liqapp_log("liqbrightness_setbrightness_fakedsme setting up message");		
		// from the bowels of abl
		struct dsme_message_abl message;
		message.len = 0x0c;
		message.request = 0x289;
		message.value = (void *) newbrightness;
		liqapp_log("liqbrightness_setbrightness_fakedsme sending message");		
		send(dsmesock, (void *) &message, sizeof(message), 0);
		liqapp_log("liqbrightness_setbrightness_fakedsme closing");
		close(dsmesock);
	}

//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################

	#define SYSFS_BRIGHTNESS "/sys/devices/platform/omapfb/panel/backlight_level"

	static int liqbrightness_getbrightness_sys(liqcell *liqbrightness)
	{
		// thanks to rm_you, jott, stskeeps and austin che for this code and zach habersang for reminding me it existed
		//liqapp_log("liqbrightness_getbrightness_sys starting");
		FILE *f;
		f = fopen(SYSFS_BRIGHTNESS, "r");
		if(!f)
		{
			liqapp_log("liqbrightness_getbrightness failed to open");
			return -1;
		}
		//liqapp_log("liqbrightness_getbrightness_sys reading");
		int res=0;
		fscanf(f, "%d", &res);
		//liqapp_log("liqbrightness_getbrightness_sys closing");
		fclose(f);
		return res;
	}
	static int liqbrightness_setbrightness_sys(liqcell *liqbrightness,int newbrightness)
	{
		// thanks to rm_you, jott, stskeeps and austin che for this code and zach habersang for reminding me it existed
		liqapp_log("liqbrightness_setbrightness_sys setting to: %i",newbrightness);
		FILE *f;
		f = fopen(SYSFS_BRIGHTNESS, "w");
		if(!f)
		{
			liqapp_log("liqbrightness_setbrightness_sys failed to open");
			return -1;
		}
		liqapp_log("liqbrightness_setbrightness_sys writing");
		fprintf(f, "%d\n", newbrightness);
		liqapp_log("liqbrightness_setbrightness_sys closing");
		fclose(f);
	}
	



//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################



	static int liqbrightness_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *liqbrightness)
	{		
		if(args->mez!=0)
		{
			unsigned char grey,u,v;
			vgraph_pget(args->graph,args->mex,args->mey, &grey,&u,&v);
			liqapp_log("grey level at %3i,%3i :: %3i",args->mex,args->mey,grey );
			// 20090706_190909 lcuk : todo - choose a method of attack for knowing which model we are on and which variation function to use
			//liqbrightness_setbrightness_dsme(self,grey);
			//liqbrightness_setbrightness_fakedsme(self,grey);
			//liqbrightness_setbrightness_sys(self,grey);
		}
		return 0;
	}


liqcell *liqbrightness_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqbrightness","form", 800,480);

	if(self)
	{
		
		liqcell_handleradd_withcontext(   self,"mouse", liqbrightness_mouse, self );
		liqcell_propsets(self,"imagefilename","/usr/share/liqbase/liqcontrolpanel/media/liqbrightness.png");
		liqcell_propseti(self,"lockaspect",1);
	}
	return self;
}
