
#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqimage.h>
#include <liqbase/liq_xsurface.h>


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
} STAR;
#define starcount 200
//#define starcount 10000
#define starmaxz 20
#define starmaxspeed 0.1
//STAR stars[starcount];














static void star_init_one(STAR *sa)
{
//int scrw=(canvas.pixelwidth );
//int scrh=(canvas.pixelheight);

	//liqapp_log("stars init one");
int cx=((800  )>>1) * starmaxz*0.8;
int cy=((480  )>>1) * starmaxz*0.8;


#define RNG 880

STARPOINT dude;
		dude.x=(rand() % 800) - (800>>1);
		dude.y=(rand() % 480) - (480>>1);
		dude.z=starmaxz;

		if(dude.x<-cx)dude.x=-cx;
		if(dude.y<-cy)dude.y=-cy;
		if(dude.x>cx)dude.x=cx;
		if(dude.y>cy)dude.y=cy;

		sa->r  =100;
		sa->p.x=dude.x;
		sa->p.y=dude.y;
		sa->p.z=dude.z;
		sa->scrcol=0;
		sa->scrx=0;
		sa->scry=0;

}
static void star_init_all(STAR *stars)
{
	liqapp_log("stars init all");
	int a;
	STAR *sa;
	for(a=0;a<starcount;a++)
	{
		sa=&stars[a];
		star_init_one(sa);
		sa->p.z=(float)a * (float)starmaxz / (float)starcount;
		//sa->p.z=10;
	}
	//canvas_clear(0);
}

static void star_calc(STAR *stars,vgraph *graph)
{
	//liqapp_log("stars calc");
	int a;
	STAR *sa;
	// weigh first, this does not effect the location
	//unsigned int tzn=liqapp_GetTicks();
	//unsigned int tzd=tzn-tzs;
//#define SPEED 0.1
	for(a=0;a<starcount;a++)
	{
		sa=&stars[a];
		// before we do ANYTHING with it
		// if it is Initialised we UNDRAW it
		if(sa->scrcol>0)
		{
			// we are on screen..
			//canvas_pset(sa->scrx,sa->scry,sa->scrcol);
			//canvas_pset(sa->scrx,sa->scry,0);
		}
		sa->p.z -= starmaxspeed;
		if(sa->p.z<=0) star_init_one(sa);
moo:
		sa->scrx = (sa->p.x / sa->p.z) + (800  >>1);
		sa->scry = (sa->p.y / sa->p.z) + (480  >>1);
		sa->scrcol=255-(100 * (sa->p.z / starmaxz));
		//sa->scrcol=255;//-(50 * (sa->p.z / starmaxz));
		if(sa->scrx<0 || sa->scry<0 || sa->scrx>=800 || sa->scry>=480) 
		{
			star_init_one(sa);
			goto moo;
		}
		
		//liqapp_log("star %i,%i",sa->scrx,sa->scry);
		
		//canvas_pset(sa->scrx,sa->scry,sa->scrcol);
		
		vgraph_setpencolor(graph, vcolor_YUV(sa->scrcol,128,128) );
		//vgraph_drawbox(  graph, sa->scrx,sa->scry,10,10);
		vgraph_drawpoint(  graph, sa->scrx,sa->scry);
		
	}
	//liqapp_log("stars calc done");
}












//		inline void xsurface_drawrectwash_uv(   liqimage *surface,int x,int y,int w,int h, unsigned char u,unsigned char v);

//#####################################################################
//#####################################################################
//##################################################################### liqstars :: by gary birkett :)
//#####################################################################
//#####################################################################



	static int widget_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
	{
		liqapp_log("drawing args==NULL==%i args->graph==NULL==%i",args==NULL,  args->graph==NULL);
		// vgraph *graph;
		// args->graph;
		
		//vgraph_setbackcolor(args->graph, vcolor_YUV( (127+(rand()%128)) , (rand()%255) , (rand()%255) ) );
		
		
		
		//vgraph_drawbox(args->graph, 10, 40,   300, 400 );
		
		//vgraph_setpencolor(args->graph, vcolor_YUV(255,128,128) ); 
		
		star_calc((STAR *)self->tag, args->graph);
		
		liqcell_setdirty(self,1);
		
		//liqapp_log("drawing done");
		return 1;
	}
	
		
liqcell *liqstars_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqstars","form", 800,480);

	if(self)
	{
		STAR *stars = (STAR *)malloc(sizeof(STAR) * (starcount+1));
		if(stars)
		{
			star_init_all(stars);
			self->tag = (unsigned int)stars;
		}
		
		liqcell_propsets(  self, "bordercolor", "rgb(0,150,0)" );
	

		liqcell_handleradd_withcontext(self,    "paint", widget_paint,self);
	}
	return self;
}

