#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqimage.h>
#include <liqbase/liq_xsurface.h>

// battery includes
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//
// battery info 
// --------------------------
// based on kcbatt by KotCzarny
//

// user_retu_tahvo.h stuff

#define u32 unsigned int
#define u16 unsigned short
#define u8 unsigned char

// Chip IDs
#define CHIP_RETU	1
#define CHIP_TAHVO	2

// Register access type bits 
#define READ_ONLY		1
#define WRITE_ONLY		2
#define READ_WRITE		3
#define TOGGLE			4

#define MASK(field)		((u16)(field & 0xFFFF))
#define REG(field)		((u16)((field >> 16) & 0x3F))

//
// IOCTL definitions. These should be kept in sync with user space 
//

#define URT_IOC_MAGIC '`'

/*
 * IOCTL function naming conventions:
 * ==================================
 *  0 -- No argument and return value
 *  S -- Set through a pointer
 *  T -- Tell directly with the argument value
 *  G -- Reply by setting through a pointer
 *  Q -- response is on the return value
 *  X -- S and G atomically
 *  H -- T and Q atomically
 */

// General
#define URT_IOCT_IRQ_SUBSCR		_IO(URT_IOC_MAGIC, 0)

// RETU
#define RETU_IOCH_READ			_IO(URT_IOC_MAGIC, 1)
#define RETU_IOCX_WRITE			_IO(URT_IOC_MAGIC, 2)
#define RETU_IOCH_ADC_READ		_IO(URT_IOC_MAGIC, 3)

// TAHVO
#define TAHVO_IOCH_READ			_IO(URT_IOC_MAGIC, 4)
#define TAHVO_IOCX_WRITE		_IO(URT_IOC_MAGIC, 5)

// This structure is used for writing RETU/TAHVO registers
struct retu_tahvo_write_parms {
    u32	field;
    u16	value;
    u8	result;
};

// kcbatt stuff

#define BATT_DEVICE "/dev/retu"

#define FULL_BATT_EST 550
#define EMPTY_BATT_EST 340



// ##############################################################################################
// ############################################################################################## battery info
// ##############################################################################################


/**
 * Return linear battery percentage left
 */
static int adc2per(int a) 
{ 
	// full battery
	if (a > FULL_BATT_EST) 
		return 100;
		
	return ((a - EMPTY_BATT_EST) * 100 / (FULL_BATT_EST - EMPTY_BATT_EST));
}


/**
 * Get the current battery percentage left, based on kcbatt
 * @return -1 Failure...0 success
 */
static int get_battery_perct(int *result_percent)
{
	liqapp_log("get_battery_perct: starting");

	*result_percent=0;
	
	int retval = 0;
	
	int s = 8, i, f;
	int v = 0, vc = 10, vch = 0, vi = 0;

	// open /dev/retu
	if ((f = open(BATT_DEVICE, O_RDONLY)) < 0)
	{
		liqapp_log("get_battery_perct: couldn't open BATT_DEVICE : '%s'",BATT_DEVICE);
		retval = -1;
		return retval;
	}
		
	// calculate voltage
	for(vi = 0; vi < vc; vi++) 
	{ 
		//usleep(100000);
		v += ioctl(f, RETU_IOCH_ADC_READ, s);
		vch = ioctl(f, RETU_IOCH_ADC_READ, 3);
   
		if(vch > 50 && vch < 300) 
			v -= 35;
	} 
	
	v /= vc;
	
	*result_percent = adc2per(v);
	
	close(f);
	liqapp_log("get_battery_perct: completed");
	
	return retval;
}


//#####################################################################
//#####################################################################
//##################################################################### liqbattery :: by gary birkett :)
//#####################################################################
//#####################################################################


// 20090526_022907 lcuk : this is a static image at this time
// 20090526_022916 lcuk : i have contacted the author of this demo but not
// http://vector.tutsplus.com/tutorials/illustration/how-to-create-a-transparent-battery-icon/

/**	
 * liqbattery paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
static int liqbattery_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{

	liqcell *piece4 = liqcell_child_lookup(self, "piece4");
	liqcell *piece3 = liqcell_child_lookup(self, "piece3");
	liqcell *piece2 = liqcell_child_lookup(self, "piece2");
	liqcell *piece1 = liqcell_child_lookup(self, "piece1");
	liqcell *piece1g = liqcell_child_lookup(self, "piece1g");


/*
	// 20090709_191846 lcuk : slow, but its just a test
	int pc=0;
	if(get_battery_perct(&pc)==0)
	{
		liqapp_log("BATTERY PERC: %d", pc);
		int battery_ind_val = (int)(((float)pc / 100.0) * 255.0); // battery indicator value 0 - 255
		liqapp_log("BATTERY PERC (CONVERTED): %d", battery_ind_val);
		liqcell_propseti(self,"batterycharge", battery_ind_val);
	}
	else
	{
		liqapp_log("BATTERY PERC: ERROR");
	}
 */


	void colorizeimg(liqimage *img,int u,int v)
	{
		if(!img) return;
		xsurface_drawrectwash_uv(img,0,0,img->width,img->height, u,v);
	}
	int xx = liqcell_propgeti(self,"batterycharge",0);
	int u=255-xx;
	int v=20;
	//colorizeimg( liqcell_getimage(piece4), u,v);
	//colorizeimg( liqcell_getimage(piece3), u,v);
	colorizeimg( liqcell_getimage(piece2), u,v);
	colorizeimg( liqcell_getimage(piece1g), u,v);
	
	int ys = liqcell_gety(piece1);
	int yh = liqcell_geth(piece1);
	
	int xs = liqcell_getx(piece1)+liqcell_getw(piece1);
	int xw = liqcell_getx(piece4) - xs;
	
	liqcell_setrect( piece2, xs,                   ys,  (xx * xw) / 256        ,yh);
	
	liqcell_setrect( piece3, xs + (xx * xw) / 256, ys,  xw-((xx * xw) / 256)   ,yh);
	
	// 20090709_192648 lcuk : no need for this now, we expect live proper values
	xx = (xx+4) % 255;
	liqcell_propseti(self,"batterycharge",xx );
	

	return 1;
}





static int liqbattery_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *liqbrightness)
{		
	if(args->mez!=0)
	{
		unsigned char grey,u,v;
		vgraph_pget(args->graph,args->mex,args->mey, &grey,&u,&v);
		liqapp_log("grey level at %3i,%3i :: %3i",args->mex,args->mey,grey );
	}
	return 0;
}


/**	
 * liqbattery dynamic resizing
 */	
static int liqbattery_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *piece4 = liqcell_child_lookup(self, "piece4");
	liqcell *piece3 = liqcell_child_lookup(self, "piece3");
	liqcell *piece2 = liqcell_child_lookup(self, "piece2");
	liqcell *piece1 = liqcell_child_lookup(self, "piece1");
	liqcell *piece1g = liqcell_child_lookup(self, "piece1g");
	liqcell_setrect_autoscale( piece4, 646,110, 96, 254, sx,sy);
	liqcell_setrect_autoscale( piece3, 490,110, 160,254, sx,sy);
	liqcell_setrect_autoscale( piece2, 140,110, 354,254, sx,sy);
	liqcell_setrect_autoscale( piece1, 44,110,  96, 254, sx,sy);
	liqcell_setrect_autoscale( piece1g, 44,110,  96, 254, sx,sy);
	return 0;
}


/**	
 * liqbattery_child_test_seek this function shows how to access members
 */	
	  
static void liqbattery_child_test_seek(liqcell *self)
{	  
	liqcell *piece4 = liqcell_child_lookup(self, "piece4");
	liqcell *piece3 = liqcell_child_lookup(self, "piece3");
	liqcell *piece2 = liqcell_child_lookup(self, "piece2");
	liqcell *piece1 = liqcell_child_lookup(self, "piece1");
	liqcell *piece1g = liqcell_child_lookup(self, "piece1g");
}


/**	
 * create a new liqbattery widget
 */	
		
liqcell *liqbattery_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqbattery","form", 800,480);

	if(!self) {liqapp_log("liqcell error not create 'liqbattery'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# piece4:label
	liqcell *piece4 = liqcell_quickcreatevis("piece4", "label", 646, 110, 96, 254);
	liqcell_propsets(  piece4, "imagefilename", "media/liqbattery_4.png" );
	liqcell_child_append(  self, piece4);
	//############################# piece3:label
	liqcell *piece3 = liqcell_quickcreatevis("piece3", "label", 490, 110, 160, 254);
	liqcell_propsets(  piece3, "imagefilename", "media/liqbattery_3.png" );
	liqcell_child_append(  self, piece3);
	//############################# piece2:label
	liqcell *piece2 = liqcell_quickcreatevis("piece2", "label", 140, 110, 354, 254);
	liqcell_propsets(  piece2, "imagefilename", "media/liqbattery_2.png" );
	liqcell_child_append(  self, piece2);
	//############################# piece1:label
	liqcell *piece1 = liqcell_quickcreatevis("piece1", "label", 44, 110, 96, 254);
	liqcell_propsets(  piece1, "imagefilename", "media/liqbattery_1.png" );
	liqcell_child_append(  self, piece1);
	//############################# piece1:label
	liqcell *piece1g = liqcell_quickcreatevis("piece1g", "label", 44, 110, 96, 254);
	liqcell_propsets(  piece1g, "imagefilename", "media/liqbattery_1_glow.png" );
	liqcell_child_append(  self, piece1g);
	
		
	//liqimage *img = liqimage_newfromfile( "media/liqbattery.png",0,0,1);		
	//liqcell_propseti(self,"lockaspect",1);
	//liqcell_setimage(  self,img );
	
	int pc=0;
	if (get_battery_perct(&pc))
	{
		liqapp_log("BATTERY PERC: %d", pc);
		int battery_ind_val = (int)(((float)pc / 100.0) * 255.0); // battery indicator value 0 - 255
		liqapp_log("BATTERY PERC (CONVERTED): %d", battery_ind_val);
		liqcell_propseti(self,"batterycharge", battery_ind_val);
	}
	
	liqcell_handleradd_withcontext(self, "resize", liqbattery_resize ,self);
	liqcell_handleradd_withcontext(   self,"mouse", liqbattery_mouse, self );
	liqcell_handleradd_withcontext(self,    "paint", liqbattery_paint,self);

	return self;
}

