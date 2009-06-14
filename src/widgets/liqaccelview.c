// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqimage.h>
#include <liqbase/liq_xsurface.h>
#include <liqbase/liqcell_easyhandler.h>


static int liqaccelview_runchannel(liqcell *liqaccelview);








	static int timer_tick(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		liqcell_propseti(self,"timerinterval", 32767 );
		liqcell_setenabled(self,0);
		// now, run the channel? :D
		liqaccelview_runchannel((liqcell*)self->tag);
		
		return 0;
	}



/**	
 * create a new liqaccelview widget
 */	
liqcell *liqaccelview_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqaccelview", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqaccelview'"); return NULL;  } 
	
	//############################# buttonchannels:commandbutton
	//liqcell *buttonchannels = liqcell_quickcreatevis("buttonchannels", "commandbutton", 328, 432, 178, 42);
	//liqcell_setfont(	buttonchannels, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	//liqcell_setcaption(buttonchannels, "list channels" );
	//liqcell_propsets(  buttonchannels, "backcolor", "rgb(235,233,237)" );
	//liqcell_child_append(  self, buttonchannels);
	//############################# buttonback:commandbutton
	//liqcell *buttonback = liqcell_quickcreatevis("buttonback", "commandbutton", 8, 432, 202, 42);
	//liqcell_setfont(	buttonback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	//liqcell_setcaption(buttonback, "Back" );
	//liqcell_propsets(  buttonback, "backcolor", "rgb(235,233,237)" );
	//liqcell_child_append(  self, buttonback);


	

	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 66, 8, 728, 40);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "accelerometer test" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 6, 8, 52, 40);
	liqcell_setfont(	icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(icon, "icon" );
	liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);


	//############################# bx:picturebox
	liqcell *bx = liqcell_quickcreatevis("bx", "picturebox", 100, 100, 600, 100);
	liqcell_setfont(	bx, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_propsets(  bx, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  bx, "backcolor", "rgb(200,0,0)" );
	liqcell_propseti(  bx, "textalign", 2 );
	liqcell_propseti(  bx, "textaligny",2 );
	//liqcell_propsets(  bx, "bordercolor", "rgb(200,100,100)" );
	liqcell_child_append(  self, bx);
	
	//############################# by:picturebox
	liqcell *by = liqcell_quickcreatevis("by", "picturebox", 100, 220, 600, 100);
	liqcell_setfont(	by, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_propsets(  by, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  by, "backcolor", "rgb(0,200,0)" );
	//liqcell_propsets(  by, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  by, "textalign", 2 );
	liqcell_propseti(  by, "textaligny",2 );
	
	liqcell_child_append(  self, by);

	//############################# bz:picturebox
	liqcell *bz = liqcell_quickcreatevis("bz", "picturebox", 100, 340, 600, 100);
	liqcell_setfont(	bz, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_propsets(  bz, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  bz, "backcolor", "rgb(0,0,200)" );
	//liqcell_propsets(  bz, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  bz, "textalign", 2 );
	liqcell_propseti(  bz, "textaligny",2 );
	liqcell_child_append(  self, bz);


	//############################# timer1:liqtimer
	liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
	// store ourselves on the tag for use later
	// this does feel like a workaround, but hell, it works!
	liqcell_settag(timer1,liqcell_hold(self));
	liqcell_propseti(timer1,"timerinterval", 25 );
	liqcell_handleradd(timer1,"timertick",timer_tick);
	liqcell_setenabled(timer1,1);
	liqcell_child_insert( self,timer1);
	

	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	return self;
}


void liqaccelview_showmsg(liqcell *self,char *time,char *nick,char *message)//char *message)//,int rx,int ry,int rz)
{
	// add a new listitem into the flow
	// reflow
	// adjust the top position of the backport to compensate

	//liqapp_log("irc showmsg == %s",self->name);

	int calcsize(char *buf,int ww)
	{
		int ii=atoi(buf);
		if(ii<-1000)ii=-1000;
		if(ii>1000)ii=1000;
		
		int res = ((ii+1000) * ww) / 2000;

		if(res<0)res=0;
		if(res>ww)res=ww;
		return res;

	}
	
	


	liqcell *bx = liqcell_child_lookup( self,"bx");
	liqcell_setcaption(bx, time);	
	liqcell_setsize(bx, calcsize(time,600) , bx->h);

	liqcell *by = liqcell_child_lookup( self,"by");
	liqcell_setcaption(by, nick);
	liqcell_setsize(by, calcsize(nick,600) , by->h);

	liqcell *bz = liqcell_child_lookup( self,"bz");
	liqcell_setcaption(bz, message);
	liqcell_setsize(bz, calcsize(message,600) , bz->h);
	
	liqcell_setdirty(  self, 1);

}


static const char *accel_filename = "/sys/class/i2c-adapter/i2c-3/3-001d/coord";
static int accel_read(char *result,int resultmaxlength)
{
	FILE *fd;
	char *rc;
	fd = fopen(accel_filename, "r");
	if(fd==NULL){ liqapp_log("accel, cannot open for reading\n"); return -1;}
	rc=fgets(result, resultmaxlength, (FILE*) fd);
	fclose(fd);
	if(rc==NULL){ liqapp_log("accel, cannot read information\n"); return -2;}
	//lcuk: cleaning off any trailing \n
	char *b=result;	while(*b){  if(*b=='\n'){ *b=0;break; } b++; };
	return 0;
}


static int liqaccelview_runchannel(liqcell *liqaccelview)
{
	while(1)
	{
		liqapp_sleep(50);
		char buff[256];
		if(0 == accel_read(buff,sizeof(buff)) )
		{
			int p[3]={0,0,0};
			char * t[3]={0,0,0};
			char * tok = strtok(buff, " ");
			int    idx = 0;
			while (tok && idx<3)
			{
				p[idx] = atoi(tok);
				t[idx] = (tok);
				tok = strtok(NULL," ");
				idx++;
			}
			
			char fmt[256];
			snprintf(fmt,sizeof(fmt),"%-4i %-4i %-4i",p[0],p[1],p[2]);


			
			liqaccelview_showmsg(liqaccelview,t[0],t[1],t[2]);
		}
		
	}
}
