// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
#include "osc_onedotzero.h"



extern int onemenu_moderunning;




static int sax=0;
static int say=0;
static int saz=0;
static int scnt=0;


static int running =0;
static int timerinprogress;


//#####################################################################
//#####################################################################
//##################################################################### 
//#####################################################################
//#####################################################################

#define ABS(X) ((X)<0?-(X):(X))


static int ocnt=0;
static int oax=0;
static int oay=0;
static int oaz=0;
static int accel_fat=0;


static int dax=0;
static int day=0;
static int daz=0;

	
static const char *accel_filename = "/sys/class/i2c-adapter/i2c-3/3-001d/coord";

static int liqaccel_read(int *ax,int *ay,int *az)
{
	FILE *fd;
	int rs;
	fd = fopen(accel_filename, "r");
	if(fd==NULL){ liqapp_log("liqaccel, cannot open for reading"); return -1;}	
	rs=fscanf((FILE*) fd,"%i %i %i",ax,ay,az);	
	fclose(fd);	
	if(rs != 3){ liqapp_log("liqaccel, cannot read information"); return -2;}
	int bx=*ax;
	int by=*ay;
	int bz=*az;
	if(ocnt>0)
	{

        
		*ax=oax+(bx-oax)*0.1;
		*ay=oay+(by-oay)*0.1;
		*az=oaz+(bz-oaz)*0.1;
        
        dax=*ax-oax;
        day=*ay-oay;
        daz=*az-oaz;

	}

	if(ocnt>0)
	{
        // calc rumble
		int dx = *ax-oax;
		int dy = *ay-oay;
		int dz = *az-oaz;
		int fat = ABS(dx)+ABS(dy)+ABS(dz);
		if(accel_fat>0)
		{
			accel_fat = accel_fat * 0.8;
		}
		if(accel_fat<0)accel_fat=0;
		accel_fat += fat;
	}

	oax=*ax;
	oay=*ay;
	oaz=*az;
	ocnt++;
	return 0;
}





//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################


static int tx=0;
static int ty=0;


	//static int timer_tick(liqcell *self, liqcellmouseeventargs *args, void *onetilt)
    int runx(liqcell *onetilt)
	{
        //if(running==0)return 0;
        
        timerinprogress=1;
        
        
        //liqapp_log("________________Timer.start");
        

 
        
        liqcell *sidebar = liqcell_child_lookup(onetilt, "sidebar");
            liqcell *cmdplaypause = liqcell_child_lookup(sidebar, "cmdplaypause");
            
           //if((rand() % 512)>256)
            
            if(get_osc_onedotzero_server_playstate() ==0)
            {
                // server is paused..
                liqcell_setimage(  cmdplaypause,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/play_button.png", 0,0,1) );
                
            }
            else
            {
                // server is playing
                liqcell_setimage(  cmdplaypause,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/pause_button.png", 0,0,1) );
            }    
        
            
        
        
        if(onemenu_moderunning==2)
        {
            timerinprogress=0;
           // liqapp_log("________________Timer.end1");
            return 0;
        }





        int aax=0;
        int aay=0;
        int aaz=0;
        liqaccel_read(&aax,&aay,&aaz);
        


        
           	
            osc_onedotzero_send_menu_repeat_ping_if_required();

if( onemenu_moderunning==0)
{
            
            osc_onedotzero_send_acc(aax,aay,aaz);
}

if( onemenu_moderunning==1)
{
            
            osc_onedotzero_send_acc(aax,aay,aaz);
            
            osc_onedotzero_send_shake(aax,aay,aaz,accel_fat);
}


        
        
        if(scnt++ ==0)
        {
            sax=aax;
            say=aay;
            saz=aaz;
        }
        else
        {
            aax=aax-sax;
            aay=aay-say;
            aaz=aaz-saz;
        }
        
        
        
        
        tx+=dax;
        ty+=day;
        
        
        liqcell *backplane = liqcell_child_lookup(onetilt, "backplane");
        
        
        liqcell *ball = liqcell_child_lookup(backplane, "knob");
        
      //  #define dt 0.3
      //  #define fr 0.5
      //  #define aa 1
      
      
        
        
        
        float dt;
        float fr;
        float aa;
        
if( onemenu_moderunning==0)
{
    dt=0.2;
    fr=0.3;
    aa=1;
}
else
{
    dt=0.3;
    fr=0.5;
    aa=5;    
}
        
        
        
        
        
        float bw = liqcell_getw(backplane);
        float bh = liqcell_geth(backplane);        
        
       // float px = liqcell_getx(ball);
       // float py = liqcell_gety(ball);

        float px = 0.01 * (float)liqcell_propgeti(ball,"px",40000);
        float py = 0.01 * (float)liqcell_propgeti(ball,"py",24000);
        
        float pw = liqcell_getw(ball);
        float ph = liqcell_geth(ball);

        
        float vx = 0.01 * (float)liqcell_propgeti(ball,"vx",0);
        float vy = 0.01 * (float)liqcell_propgeti(ball,"vy",0);
        
        float ax;
        float ay;

if( onemenu_moderunning==0)
{
        ax = aa * (float)(-aax);
        ay = aa * (float)(-aay);

}
else
{
        ax = aa * (float)(-dax);
        ay = aa * (float)(-day);
    
}








        vx = fr * vx;
        vy = fr * vy;

        
        vx += dt * ax;
        vy += dt * ay;
        
        px += dt * vx;
        py += dt * vy;
        
        

if( onemenu_moderunning==0)
{

        
// wrap        
        if(px+pw<0)px+=bw;
        if(px>bw)px-=bw;
       
        if(py+ph<0)py+=bh;
        if(py>bh)py-=bh;


}
else
{
// bounce   
        if(px<0){vx=-vx;   px=0;}
        if(px+pw>bw){vx=-vx;px=bw-pw;}
       
        if(py<0){vy=-vy;   py=0;}
        if(py+ph>bh){vy=-vy;py=bh-ph; }       
        
}
        
        
        
        liqcell_propseti(ball,"vx",vx*100);
        liqcell_propseti(ball,"vy",vy*100);
        
        

        liqcell_propseti(ball,"px",px*100);
        liqcell_propseti(ball,"py",py*100);
        
        
        liqcell_setpos(ball,px,py);
        
        liqcell_setdirty(ball,1);
        
    //    liqapp_log("ball p(% 03.3f,% 03.3f), v(% 03.3f,% 03.3f), a(% 03.3f,% 03.3f)  aa(% 4i,% 4i,% 4i)  dd(% 4i,% 4i)   % 2i,% 2i",px,py,vx,vy,ax,ay,aax,aay,aaz, dax,day,tx,ty);
        
        
        
        
       timerinprogress=0;
       
       //liqapp_log("________________Timer.end2");
        
		return 0;
	}



//#####################################################################
//#####################################################################
//##################################################################### onetilt :: by gary birkett
//#####################################################################
//#####################################################################
	

/*
    
    static int timer_tick(liqcell *self, liqcellmouseeventargs *args, void *onetilt)
    {
    
        liqcell *sidebar = liqcell_child_lookup(onetilt, "sidebar");
            liqcell *cmdplaypause = liqcell_child_lookup(sidebar, "cmdplaypause");
            
           //if((rand() % 512)>256)
            
            if(get_osc_onedotzero_server_playstate() ==0)
            {
                // server is paused..
                liqcell_setimage(  cmdplaypause,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/play_button.png", 0,0,1) );
                
            }
            else
            {
                // server is playing
                liqcell_setimage(  cmdplaypause,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/pause_button.png", 0,0,1) );
            }    
        
    
    
        return 0;
    }

 */
    
    
	static int knob_mouse(liqcell *self, liqcellmouseeventargs *args, void *onetilt)
	{
        osc_onedotzero_send_menu_repeat_ping_if_required();
        
		liqcell_adjustpos(self,args->mdx,args->mdy);
		
		
							osc_onedotzero_send_touch( liqcell_getx(self),liqcell_gety(self) );
							
		if(args->mez==0)	osc_onedotzero_send_touchoff();
		
		liqcell_child_arrange_nooverlap( liqcell_getlinkparent(self), self );
		
		if(args->mez==0) liqcell_forceinboundparent(self);

		return 1;
	}		
    
    
    
    


static int backplane_paint(liqcell *self, liqcellpainteventargs *args,liqcell *onetilt)
{
    // draw ghosts
    

		liqcell *backplane = self;//liqcell_child_lookup(self,"backplane");
        liqcell *knob = liqcell_child_lookup(backplane,"knob");
        if(knob->x<0) vgraph_drawimage( args->graph, backplane->w + (knob->x),    knob->y              ,   knob->w,knob->h,    liqcell_getimage(knob)   );
        if(knob->y<0) vgraph_drawimage( args->graph, knob->x                 ,    backplane->h+ knob->y,   knob->w,knob->h,    liqcell_getimage(knob)   );
        
        if(knob->x+knob->w>backplane->w) vgraph_drawimage( args->graph, (knob->x-backplane->w),    knob->y              ,   knob->w,knob->h,    liqcell_getimage(knob)   );
        if(knob->y+knob->h>backplane->h) vgraph_drawimage( args->graph,  knob->x              ,    knob->y-backplane->h ,   knob->w,knob->h,    liqcell_getimage(knob)   );
    
        
	return 0;
}
    
    
    
    
    
    
    
    	
		
/**	
 * onetilt widget refresh, all params set, present yourself to the user.
 */	
static int onetilt_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * onetilt dialog_open - the user zoomed into the dialog
 */	
static int onetilt_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    running=1;
	return 0;
}
/**	
 * onetilt dialog_close - the dialog was closed
 */	
static int onetilt_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    if(!running)return 0;
    while(timerinprogress)
    {
        liqapp_sleep(1);
    }
    running=0;
    
    osc_onedotzero_send_menufinished(onemenu_moderunning);
	return 0;
}
/**	
 * onetilt widget shown - occurs once per lifetime
 */	
static int onetilt_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onetilt mouse - occurs all the time as you stroke the screen
 */	
static int onetilt_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetilt click - occurs when a short mouse stroke occured
 */	
static int onetilt_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetilt keypress - the user pressed a key
 */	
static int onetilt_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetilt keyrelease - the user released a key
 */	
static int onetilt_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onetilt paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	


static int onetilt_paint(liqcell *self, liqcellpainteventargs *args,liqcell *onetilt)
{
	// big heavy event, use sparingly
    
if( onemenu_moderunning<2)
{
    runx(onetilt);
        
    liqcell_setdirty(onetilt,1);
}

        
	return 0;
}

 
/**	
 * onetilt dynamic resizing
 */	
static int onetilt_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
/*	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *cmdplaypause = liqcell_child_lookup(self, "cmdplaypause");
	liqcell *cmdback = liqcell_child_lookup(self, "cmdback");
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	liqcell *slider = liqcell_child_lookup(self, "slider");
	liqcell *sidebar = liqcell_child_lookup(self, "sidebar");
	liqcell_setrect_autoscale( cmdplaypause, 32,426, 66,28, sx,sy);
	liqcell_setrect_autoscale( cmdback, 10,20, 62,26, sx,sy);
	liqcell_setrect_autoscale( backplane, 144,0, 656,480, sx,sy);
	liqcell_setrect_autoscale( slider, 32,110, 66,270, sx,sy);
	liqcell_setrect_autoscale( sidebar, 0,0, 144,480, sx,sy);
 */	return 0;
}

/**	
 * onetilt.cmdplaypause clicked
 */	
static int cmdplaypause_click(liqcell *self,liqcelleventargs *args, liqcell *onetilt)
{
    if(get_osc_onedotzero_server_playstate()==0)
    {
        osc_onedotzero_send_playstatecmd(1);
    }
    else
    {
        osc_onedotzero_send_playstatecmd(0);
    }
	return 0;
}
/**	
 * onetilt.cmdback clicked
 */	
static int cmdback_click(liqcell *self,liqcelleventargs *args, liqcell *onetilt)
{
    liqcell_setvisible(onetilt,0);
	return 0;
}
/**	
 * onetilt_child_test_seek this function shows how to access members
 */	
	  
static void onetilt_child_test_seek(liqcell *self)
{	  
	liqcell *sidebar = liqcell_child_lookup(self, "sidebar");
        liqcell *cmdplaypause = liqcell_child_lookup(sidebar, "cmdplaypause");
        liqcell *cmdback = liqcell_child_lookup(sidebar, "cmdback");
        liqcell *slider = liqcell_child_lookup(sidebar, "slider");
        
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
}	  
/**	
 * create a new onetilt widget
 */	
liqcell *onetilt_create()
{
    
    scnt=0;
    
    
	liqcell *self = liqcell_quickcreatewidget("onetilt", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'onetilt'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering

	//############################# sidebar:label
	liqcell *sidebar = liqcell_quickcreatevis("sidebar", "label", 0, 0, 144, 480);
	//liqcell_setfont(	sidebar, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(sidebar, "sidebar" );
	//liqcell_propsets(  sidebar, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  sidebar, "backcolor", "rgb(224,224,224)" );
	//liqcell_propseti(  sidebar, "textalign", 0 );
	liqcell_child_append(  self, sidebar);


        
    
        //############################# slider:label
        liqcell *slider = liqcell_quickcreatevis("slider", "zoombox", 20, 104, 89, 290);
        //liqcell_setfont(	slider, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
        //liqcell_setcaption(slider, "slider" );
        //liqcell_propsets(  slider, "textcolor", "rgb(0,0,0)" );
        //liqcell_propsets(  slider, "backcolor", "rgb(128,128,128)" );
        //liqcell_propseti(  slider, "textalign", 0 );
        liqcell_child_append(  sidebar, slider);
        
        //############################# cmdplaypause:label
        liqcell *cmdplaypause = liqcell_quickcreatevis("cmdplaypause", "label", 22, 406, 101, 42);
        //liqcell *cmdplaypause = liqcell_quickcreatevis("cmdplaypause", "label", 22, 40, 101, 42);
        //liqcell_setfont(	cmdplaypause, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
        //liqcell_setcaption(cmdplaypause, "play/pause" );
        //liqcell_propsets(  cmdplaypause, "textcolor", "rgb(0,0,0)" );
        //liqcell_propsets(  cmdplaypause, "backcolor", "rgb(192,192,192)" );
        //liqcell_propseti(  cmdplaypause, "textalign", 0 );
    
        liqcell_setimage(  cmdplaypause,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/play_button.png", 0,0,1) );
    
        liqcell_handleradd_withcontext(cmdplaypause, "click", cmdplaypause_click, self );
        liqcell_child_append(  sidebar, cmdplaypause);

	//############################# backplane:label
	liqcell *backplane = liqcell_quickcreatevis("backplane", "label", 144, 0, 656, 480);
	//liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(backplane, "backplane" );
	//liqcell_propsets(  backplane, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  backplane, "backcolor", "rgb(0,128,0)" );
	//liqcell_propseti(  backplane, "textalign", 0 );
    


        //############################# cmdback:label
        liqcell *cmdback = liqcell_quickcreatevis("cmdback", "label", 670-144, 16, 101, 42);
        //liqcell_setfont(	cmdback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
        //liqcell_setcaption(cmdback, "back" );
        //liqcell_propsets(  cmdback, "textcolor", "rgb(0,0,0)" );
        //liqcell_propsets(  cmdback, "backcolor", "rgb(235,233,237)" );
        //liqcell_propseti(  cmdback, "textalign", 0 );
        liqcell_setimage(  cmdback,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/back_button.png", 0,0,1) );
        liqcell_handleradd_withcontext(cmdback, "click", cmdback_click, self );
        liqcell_child_append(  backplane, cmdback);
        
        //liqcell_setvisible(cmdback,0);
    

    
if(onemenu_moderunning==0)
{    
    liqcell_handleradd_withcontext(backplane, "paint", backplane_paint ,self);
}

	liqcell_child_append(  self, backplane);

		//############################# knob:label
		liqcell *knob = liqcell_quickcreatevis("knob", "label", 238, 150, 180, 180);
		//liqcell_setfont(	knob, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		//liqcell_setcaption(knob, "Move Me!" );
		//liqcell_propsets(  knob, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  knob, "backcolor", "rgb(0,0,128)" );
		//liqcell_propsets(  knob, "bordercolor", "rgb(200,100,100)" );
		//liqcell_propseti(  knob, "textalign", 2 );
		//liqcell_propseti(  knob, "textaligny", 2 );


switch(onemenu_moderunning)
{
    case 0:
        liqcell_setimage(  knob,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/tilt_me.png", 0,0,1) );
        break;
    case 1:
        liqcell_setimage(  knob,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/shake_me.png", 0,0,1) );
        break;        
    case 2:
        liqcell_setimage(  knob,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/move_me.png", 0,0,1) );
        break;        
        
        
}



		
		//liqcell_propsets(  knob, "imagefilename",  "/usr/share/liqbase/onedotzero/media/move_me.png" );
		//liqcell_propseti(  knob,  "lockaspect",  0 );

if(onemenu_moderunning==2)
{  
		liqcell_handleradd_withcontext(knob, "mouse", knob_mouse,self );
}

		liqcell_child_append(  backplane, knob);



/*


		liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
		liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
		liqcell_propseti(timer1,"timerinterval", onemenu_moderunning<2 ? 25 : 500 );
		liqcell_setenabled(timer1,1);
		liqcell_child_insert( self,timer1);

 */


//	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );

    liqcell_setimage(  self,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/background_with_slider.png", 0,0,0) );


	liqcell_handleradd_withcontext(self, "refresh", onetilt_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", onetilt_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", onetilt_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", onetilt_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", onetilt_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", onetilt_mouse,self );
	liqcell_handleradd_withcontext(self, "click", onetilt_click ,self);
	liqcell_handleradd_withcontext(self, "paint", onetilt_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", onetilt_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", onetilt_dialog_close ,self);
	return self;
}

