
#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks


#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <string.h>
#include <sys/sysinfo.h>

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqimage.h>
#include <liqbase/liqsketch.h>
#include <liqbase/liq_xsurface.h>

#include <liqbase/liqapp_prefs.h>



typedef struct
{
	float x;
	float y;
	float z;
} STARPOINT;

typedef struct
{
	int id;
	int r;
	STARPOINT p;
	STARPOINT a;
	STARPOINT v;
	int scrcol;
	int scrx;
	int scry;
	
	int fat;
	
} STAR;
#define starcount 10
//#define starcount 10000
#define starmaxz 20
#define starmaxspeed 0.1
//STAR stars[starcount];


#define ABS(X) ((X)<0?-(X):(X))



#define pw 16
#define ph 16



//#########################################################################################
//######################################################################################### touch
//#########################################################################################
static int ocnt=0;
static int oax=0;
static int oay=0;
static int oaz=0;

static int accel_fat=0;


static const char *accel_filename = "/sys/class/i2c-adapter/i2c-3/3-001d/coord";
static int accel_read(int *ax,int *ay,int *az)
{
	FILE *fd;
	int rs;
	fd = fopen(accel_filename, "r");
	if(fd==NULL){ liqapp_log("accel, cannot open for reading"); return -1;}	
	rs=fscanf((FILE*) fd,"%i %i %i",ax,ay,az);	
	//rc=fgets(result, resultmaxlength, (FILE*) fd);
	fclose(fd);	
	if(rs != 3){ liqapp_log("accel, cannot read information"); return -2;}



	
	
	if(ocnt>0)
	{
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



//#########################################################################################
//#########################################################################################
//#########################################################################################


static void star_init_one(STAR *sa)
{

STARPOINT dude;
		dude.x=(rand() % 800);
		dude.y=(rand() % 480);
		dude.z=0;


		sa->r  =100;
		sa->p.x=dude.x;
		sa->p.y=dude.y;
		sa->p.z=dude.z;
		
		sa->a.x=0;
		sa->a.y=0;
		sa->a.z=0;
		
		sa->v.x=0;
		sa->v.y=0;
		sa->v.z=0;
		
		sa->scrcol=0;
		sa->scrx=0;
		sa->scry=0;

}



static void star_init_all(STAR *stars)
{
	//liqapp_log("stars init all");
	int a;
	STAR *sa;
	for(a=0;a<starcount;a++)
	{
		sa=&stars[a];
		star_init_one(sa);
		//sa->p.z=(float)a * (float)starmaxz / (float)starcount;
		//sa->p.z=10;
	}
	//canvas_clear(0);
}

static void star_calc(liqcell *sheepdog_flow,STAR *stars,vgraph *graph,liqsketch *sketch, int drawwidth,int drawheight)
{
	
	// pseudostarcount is the count of actual stars, between 0..starscount,  based on the size of the box
	int pseudostarcount = starcount * drawwidth / 800;
	if(pseudostarcount>starcount)pseudostarcount=starcount;
	//liqapp_log("stardraw %i,%i :: %i",drawwidth,drawheight,pseudostarcount);
	int aax=0;
	int aay=0;
	int aaz=0;
	
	accel_read(&aax,&aay,&aaz);
	
	#define ff 0.08
	float fax=ff * (float)aax;
	float fay=ff * (float)aay;
	float faz=ff * (float)aaz;
	
	

	// 10000 == vigerous shake
    //     0 == still
    
	float r=   0.01 * ((float)accel_fat);
	//liqapp_log("af %5i %3.2f",accel_fat,r);

	int size = 4 + (accel_fat/(1000/8));
	
	if(size>24)size=24;
	
	

	liqcell *backplane = liqcell_child_lookup(sheepdog_flow,"backplane");

	liqimage *img = liqcell_getimage(backplane);		// grab the background
	
	//liqapp_log("...creating cliprect");
	
	liqcliprect *cr = (img?liqcliprect_newfromimage(img):NULL);
	
	
	if(cr)
	{
		vgraph_drawimage(graph,0,0,800,480,img);
	}	
	
	
	//liqapp_log("%-4i %-4i %-4i",aax,aay,aaz);
	
	//liqapp_log("%-4.2f %-4.2f %-4.2f",fax,fay,faz);
	
	
		//liqapp_log("stars calc");
	int a;
	STAR *sa;

	for(a=0;a<pseudostarcount;a++)
	{
		sa=&stars[a];
		
		//sa->a.x *= 0.3;
		//sa->a.y *= 0.3;

		sa->a.x = -fax;	// start with gravity
		sa->a.y = -fay;

		//sa->a.x = 0;	// start with no acceleration
		//sa->a.y = 0;
		//sa->a.z = 0;


		if(cr)
		{
				// need to get a sample of points from the ground below
				// this is achieved with:
				inline void liqcliprect_drawpgetcolor(      	liqcliprect *self,int x, int y, unsigned char *grey,unsigned char *u,unsigned char *v);
				
				unsigned char gcy[9]={128};
				unsigned char gcu=128;
				unsigned char gcv=128;
				
				int gx=sa->p.x;
				int gy=sa->p.y;
				
				if(gy>0)
				{
					if(gx>0)  liqcliprect_drawpgetcolor( cr, gx-1, gy-1, &gcy[0], &gcu, &gcv );
					          liqcliprect_drawpgetcolor( cr, gx  , gy-1, &gcy[1], &gcu, &gcv );
					if(gx<799)liqcliprect_drawpgetcolor( cr, gx+1, gy-1, &gcy[2], &gcu, &gcv );
				}
				
				{
					if(gx>0)  liqcliprect_drawpgetcolor( cr, gx-1, gy  , &gcy[3], &gcu, &gcv );
					          liqcliprect_drawpgetcolor( cr, gx  , gy  , &gcy[4], &gcu, &gcv );
					if(gx<799)liqcliprect_drawpgetcolor( cr, gx+1, gy  , &gcy[5], &gcu, &gcv );
				}
				
				if(gy<479)
				{
					if(gx>0)  liqcliprect_drawpgetcolor( cr, gx-1, gy+1, &gcy[6], &gcu, &gcv );
					          liqcliprect_drawpgetcolor( cr, gx  , gy+1, &gcy[7], &gcu, &gcv );
					if(gx<799)liqcliprect_drawpgetcolor( cr, gx+1, gy+1, &gcy[8], &gcu, &gcv );
				}
				// now we look for gradients
				// relative to 4
				
				//the size of the gradient represents a vector in that other direction
				
				float gax=0;
				float gay=0;
				
				void checkvec(int idx,int ox,int oy)
				{
					int vidx = gcy[idx];
					int v4 = gcy[4];
					
					gax += (float)ox * (float)(vidx-v4) ;
					gay += (float)oy * (float)(vidx-v4) ;
				}
				
				#define rx 1
				#define ry 1
				
				checkvec(0, -rx,-ry);
				checkvec(1,  0, -ry);
				checkvec(2,  rx,-ry);
				
				checkvec(3, -rx,0);
				//checkvec(0,  0, 0);
				checkvec(5,  rx,0);
				
				checkvec(6, -rx,ry);
				checkvec(7,  0, ry);
				checkvec(8,  rx,ry);
								
				liqapp_log("g? %i %3.3f,%3.3f %i",a,gax,gay,gcy[4]);

				sa->a.x += gax;	// start with no acceleration
				sa->a.y += gay;


	}
	
	
	
	
	}


/*
		// loop around and -- brightness
		if(sketch)
		{
			int scnt=0;
			liqstroke *s = sketch->strokelast;
			while(s)
			{
				liqpoint *p = s->pointfirst;
				while(p)
				{
					if(p->z>0)
					{
						p->z-=5;
						if(p->z<0)p->z=0;
					}
					
					p=p->linknext;
				}
				s=s->linkprev;
				scnt++;
				//if(scnt>=4) break;
				
			}
		}
 */

	
	
	for(a=0;a<pseudostarcount;a++)
	{
		sa=&stars[a];
		



		if(sketch)
		{
			int scnt=0;
			liqstroke *s = sketch->strokelast;
			while(s)
			{


				//int skip=s->pointcount / 10;
				
				liqpoint *p = s->pointfirst;
				while(p)
				{
					if(p->linknext)// && p->z>0)
					{
						//### calculate the difference between the star and the stroke point
						float dx = p->x - sa->p.x;
						float dy = p->y - sa->p.y;
						//float dz = p->z - sa->p.z;
						float dd = sqrt(dx*dx+dy*dy);
						if(dd>1)
						{
							float ddi = 100/dd;
							float pmx = p->linknext->x - p->x;
							float pmy = p->linknext->y - p->y;
							
							//if(p->z>0)
							//{
							//	ddi /= (255 / (float)p->z);
							//}
							//else
							//{
							//	ddi=0;
							//}
							
							sa->a.x += ddi * pmx;
							sa->a.y += ddi * pmy;
	
						}
					}
					p=p->linknext;
					if(p)p=p->linknext;
					//if(p)p=p->linknext;
					//if(p)p=p->linknext;
					//if(p)p=p->linknext;

				}
				s=s->linkprev;
				scnt++;
				if(scnt>=4) break;
				
			}
		}

		#define fr 0.4
		#define dt 0.16
		
		sa->v.x *= fr;
		sa->v.y *= fr;

		//sa->v.x *= 0.9;
		//sa->v.y *= 0.9;
		//sa->v.z *= 0.9;
		
		sa->v.x += dt * sa->a.x;
		sa->v.y += dt * sa->a.y;
		//sa->v.z += dt * sa->a.z;

		sa->p.x += dt * sa->v.x;
		sa->p.y += dt * sa->v.y;
		//sa->p.z += dt * sa->v.z;		
moo:

			

		if(sa->p.x<pw)
		{
			sa->p.x=pw;
			sa->a.x=-sa->a.x;
		}
		else
		if(sa->p.x>=(800-pw))
		{
			sa->p.x=800-pw;
			sa->a.x=-sa->a.x;
		}

		if(sa->p.y<ph)
		{
			sa->p.y=ph;
			sa->a.y=-sa->a.y;
		}
		else
		if(sa->p.y>=(480-ph))
		{
			sa->p.y=480-ph;
			sa->a.y=-sa->a.y;
		}


		sa->scrx = sa->p.x;
		sa->scry = sa->p.y;
		sa->scrcol= 255;
		//sa->scrcol=255;//-(50 * (sa->p.z / starmaxz));

		
	
		
		
		unsigned char lim(int x)
		{
            //x=x*accel_fat/10000;
            
			if(x<-128)x=-128;
			if(x>127)x=127;
			return (unsigned char) (x+128);
		}
		
		int magmag=150;
		
		
		
		//int magmag = 50 + (float)( (float)sqrt( (float)((sa->v.x * sa->v.x) + (sa->v.y * sa->v.y)) ) * 10 );
		//if(magmag>128) magmag=128;
		//if(magmag<-128)magmag=-128;
		//if(magmag>255) magmag=255;
		
		//vgraph_setpencolor(graph, vcolor_YUV(magmag,  lim((int)sa->v.x),lim((int)sa->v.y)    ) );
		//vgraph_drawpoint(  graph, sa->scrx,sa->scry);
		//vgraph_drawpoint(  graph, sa->scrx+1,sa->scry);
		//vgraph_drawpoint(  graph, sa->scrx,sa->scry+1);
		//vgraph_drawpoint(  graph, sa->scrx+1,sa->scry+1);
		
		vgraph_setbackcolor(graph, vcolor_YUV(magmag,  lim((int)sa->v.x),lim((int)sa->v.y)    ) );
		
		size=16;
			
		vgraph_drawrect(graph, sa->scrx,sa->scry,size,size);
		
	}
	
	if(cr) liqcliprect_release(cr);
	
    
	//float r=   0.01 * ((float)accel_fat);
	//liqapp_log("af %5i %3.2f",accel_fat,r);
}












//		inline void xsurface_drawrectwash_uv(   liqimage *surface,int x,int y,int w,int h, unsigned char u,unsigned char v);

//#####################################################################
//#####################################################################
//##################################################################### sheepdog_flow :: by gary birkett :)
//#####################################################################
//#####################################################################




	static int sketchedit_mouse(liqcell *self, liqcellmouseeventargs *args, void *sheepdog_flow)
	{
		liqsketch *sketch = liqcell_getsketch(self);
		if(!sketch)
		{
			return -1;
			// 20090421_215728 lcuk : make the sketch now - very late bound :)
			//return 0;
			// mmm dont know about using this
			liqsketch *s = liqsketch_new();
					s->pixelwidth =liqcell_getw(self);
					s->pixelheight=liqcell_geth(self);
					s->dpix=225;	// damn, dont like using this here
					s->dpiy=225;
			liqcell_setsketch( self, s );
			sketch=s;
		}
		liqstroke *stroke;
		if(args->mcnt==1)
		{
			// starting, allocate and insert a new stroke
			stroke = liqstroke_new();
			stroke->pen_y = 60;
			stroke->pen_u = 128;
			stroke->pen_v = 128;
			liqstroke_start(stroke,args->mex-args->ox,args->mey-args->oy, (args->mez?255:0) ,args->met);
			liqsketch_strokeinsert(sketch,stroke);
		}
		else
		{
			// continuing, get hold of the last stroke
			stroke = sketch->strokelast;
			
			
			liqpoint *p=stroke->pointlast;
			if(p)
			{
				
				int sx = (p->x) * 480 / 800;
				int sy = (p->y) * 240 / 480;
				int ex = (args->mex-args->ox) * 480 / 800;
				int ey = (args->mey-args->oy) * 240 / 480;
				
				char msg[1024];
				snprintf(msg,sizeof(msg),"%i %i %i %i\n",sx,sy,   ex,ey );

			}
			
			
			
			liqstroke_extend(stroke,args->mex-args->ox,args->mey-args->oy,(args->mez?255:0),args->met);
			liqsketch_strokeupdate(sketch,stroke);

			if(args->mez!=0)
			{
				// carry on
			}
			else
			{
				// finishing
			}
		}
		// 20090421_232509 lcuk : make sure we mark ourselves as dirty
		liqcell_setdirty(self,1);

		return 1;
	}



	static int widget_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
	{
		if( liqcell_propgeti(self,"dialog_running",0)==1 )
		{
		
			star_calc(self,(STAR *)self->tag, args->graph, liqcell_getsketch(self), args->mx,args->my );
			liqcell_setdirty(self,1);
		}
		else
		{
			// nothing for now...  should show a picture or something..
		}
		//liqapp_log("drawing done");
		return 1;
	}
	


/**	
 *  cmdclear clicked
 */	
static int cmdclear_click(liqcell *self,liqcelleventargs *args, liqcell *sheepdog_flow)
{
		liqsketch *sketch = liqcell_getsketch(sheepdog_flow);
		if(sketch)
		{
			liqsketch_clear(sketch);
		}
		star_init_all( (STAR *)sheepdog_flow->tag  );
		
	

	return 0;
}




/**	
 * widget dialog_open - the user zoomed into the dialog
 */	
static int widget_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{


	star_init_all( (STAR *)self->tag  );

	return 0;
}
/**	
 * widget dialog_close - the dialog was closed
 */	
static int widget_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{

	return 0;
}



		
liqcell *sheepdog_flow_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdog_flow","form", 800,480);

	if(self)
	{

		// load the grass
	liqcell *backplane = liqcell_quickcreatevis("backplane", "label", 0, 0, 800, 480);
	liqcell_setimage(  backplane,  liqimage_cache_getfile("/usr/share/liqbase/sheepdog/media/sheepdog_grass1.png", 0,0,0) );
	liqcell_propseti( backplane ,  "lockaspect", 0 );
	liqcell_child_append(  self, backplane);
	liqcell_setvisible(backplane,0);	
		
		// allocate the players
		STAR *stars = (STAR *)malloc(sizeof(STAR) * (starcount+1));
		if(stars)
		{
			star_init_all(stars);
			self->tag = (unsigned int)stars;
		}
		
		
	//	liqcell_propsets(  self, "bordercolor", "rgb(0,150,0)" );
		liqsketch *sketch = liqsketch_new();
		liqcell_setsketch(self,sketch);
		

		
		liqcell_handleradd_withcontext(self, "dialog_open", widget_dialog_open ,self);
		liqcell_handleradd_withcontext(self, "dialog_close", widget_dialog_close ,self);
		
		liqcell_handleradd_withcontext(self,    "mouse",   sketchedit_mouse,self);
		liqcell_handleradd_withcontext(self,    "paint", widget_paint,self);
		
		liqcell_propseti(self,"sketchediting",1);		// mark it as editing :)
		
		
		liqcell_handlerrun(self,"dialog_close",NULL);
		
	}
	return self;
}

