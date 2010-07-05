
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

#include <liqbase/liqaccel.h>

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
#define starcount 200
//#define starcount 10000
#define starmaxz 20
#define starmaxspeed 0.1
//STAR stars[starcount];


#define ABS(X) ((X)<0?-(X):(X))




//#########################################################################################
//######################################################################################### touch
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

static void star_calc(STAR *stars,vgraph *graph,liqsketch *sketch, int drawwidth,int drawheight)
{
	
	// pseudostarcount is the count of actual stars, between 0..starscount,  based on the size of the box
	int pseudostarcount = starcount * drawwidth / 800;
	if(pseudostarcount>starcount)pseudostarcount=starcount;
	//liqapp_log("stardraw %i,%i :: %i",drawwidth,drawheight,pseudostarcount);
	int aax=0;
	int aay=0;
	int aaz=0;
	
	liqaccel_read(&aax,&aay,&aaz);
	
	#define ff 0.08
	float fax=ff * (float)aax;
	float fay=ff * (float)aay;
	float faz=ff * (float)aaz;
	

	// 10000 == vigerous shake
    //     0 == still
    
	int accel_fat=liqaccel_getfat();
	float r=   0.01 * ((float)accel_fat);
	//liqapp_log("af %5i %3.2f",accel_fat,r);

	int size = 4 + (accel_fat/(1000/8));
	
	if(size>24)size=24;
	
	
	
	
	
	//liqapp_log("%-4i %-4i %-4i",aax,aay,aaz);
	
	//liqapp_log("%-4.2f %-4.2f %-4.2f",fax,fay,faz);
	
	
		//liqapp_log("stars calc");
	int a;
	STAR *sa;

	for(a=0;a<pseudostarcount;a++)
	{
		sa=&stars[a];

		sa->a.x = -fax;	// start with no acceleration
		sa->a.y = -fay;

		//sa->a.x = 0;	// start with no acceleration
		//sa->a.y = 0;
		//sa->a.z = 0;
		
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
/*
		for(b=a+1;starcount;b++)
		{
			float dx = sb->p.x - sa->p.x;
			float dy = sb->p.y - sa->p.y;
			//float dz = sb->p.z - sa->p.z;
			
			float dd = sqrt(dx*dx+dy*dy);
			if(dd>1)
			{
				float ddi = 1/dd;
			}
			
			sb=&stars[b];
			sb->a.x = 0;	// start with no acceleration
			sb->a.y = 0;
			//sb->a.z = 0;			
		}
*/

		//#define fr 0.5
		//#define dt 0.15
	
		#define fr 0.5
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

		if(sa->p.x<0)
			sa->p.x+=800;
		else
		if(sa->p.x>=800)
			sa->p.x-=800;


		if(sa->p.y<0)
			sa->p.y+=480;
		else
		if(sa->p.y>=480)
			sa->p.y-=480;
			
			
			

		sa->scrx = sa->p.x;
		sa->scry = sa->p.y;
		sa->scrcol= 255;
		//sa->scrcol=255;//-(50 * (sa->p.z / starmaxz));
		
	/*	
		if(sa->scrx<0 || sa->scry<0 || sa->scrx>=800 || sa->scry>=480) 
		{
			star_init_one(sa);
			goto moo;
		}
	*/	
		
	
		
		
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
		
			
		vgraph_drawrect(graph, sa->scrx,sa->scry,size,size);
		
	}
    
	//float r=   0.01 * ((float)accel_fat);
	//liqapp_log("af %5i %3.2f",accel_fat,r);
}












//		inline void xsurface_drawrectwash_uv(   liqimage *surface,int x,int y,int w,int h, unsigned char u,unsigned char v);

//#####################################################################
//#####################################################################
//##################################################################### liqflow_run :: by gary birkett :)
//#####################################################################
//#####################################################################




	static int sketchedit_mouse(liqcell *self, liqcellmouseeventargs *args, void *liqflow_run)
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
		
		//liqapp_log("starpaint %4i,%4i :: '%s'::'%s'",args->mx,args->my,self->name,self->classname);
		
		//liqapp_log("drawing args==NULL==%i args->graph==NULL==%i",args==NULL,  args->graph==NULL);
		// vgraph *graph;
		// args->graph;
		
		//vgraph_setbackcolor(args->graph, vcolor_YUV( (127+(rand()%128)) , (rand()%255) , (rand()%255) ) );
		
		
		
		//vgraph_drawbox(args->graph, 10, 40,   300, 400 );
		
		//vgraph_setpencolor(args->graph, vcolor_YUV(255,128,128) );


		
		if( liqcell_propgeti(self,"dialog_running",0)==1 )
		{
		
			star_calc((STAR *)self->tag, args->graph, liqcell_getsketch(self), args->mx,args->my );
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
static int cmdclear_click(liqcell *self,liqcelleventargs *args, liqcell *liqflow_run)
{
		liqsketch *sketch = liqcell_getsketch(liqflow_run);
		if(sketch)
		{
			liqsketch_clear(sketch);
		}
		star_init_all( (STAR *)liqflow_run->tag  );
		
	

	return 0;
}






/*
	static int widget_dialog_open(liqcell *self, liqcelleventargs *args,liqcell *context)
	{
		liqsketch *sketch = liqcell_getsketch(self);
		if(sketch)
		{
			//liqsketch_clear(sketch);
		}
		
		star_init_all( (STAR *)self->tag  );
		return 1;
	}

 */

/**	
 * widget dialog_open - the user zoomed into the dialog
 */	
static int widget_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{

		liqcell *ainvite = liqcell_child_lookup(self, "ainvite");
		liqcell *aname = liqcell_child_lookup(self, "aname");		
		
			liqcell_setvisible(aname,0);
			liqcell_setvisible(ainvite,0);

		liqcell *cmdclear = liqcell_child_lookup(self, "cmdclear");		
			liqcell_setvisible(cmdclear,1);

	star_init_all( (STAR *)self->tag  );

	return 0;
}
/**	
 * widget dialog_close - the dialog was closed
 */	
static int widget_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
		liqcell *ainvite = liqcell_child_lookup(self, "ainvite");
		liqcell *aname = liqcell_child_lookup(self, "aname");		
		
			liqcell_setvisible(aname,1);
			liqcell_setvisible(ainvite,1);
			
		liqcell *cmdclear = liqcell_child_lookup(self, "cmdclear");		
			liqcell_setvisible(cmdclear,0);

	return 0;
}



		
liqcell *liqflow_run_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqflow_run","form", 800,480);

	if(self)
	{
		STAR *stars = (STAR *)malloc(sizeof(STAR) * (starcount+1));
		if(stars)
		{
			star_init_all(stars);
			self->tag = (unsigned int)stars;
		}
		
	//	liqcell_propsets(  self, "bordercolor", "rgb(0,150,0)" );
	
	
		liqsketch *sketch = liqsketch_new();
		liqcell_setsketch(self,sketch);
		

		//############################# cmdclear:label
		liqcell *cmdclear = liqcell_quickcreatevis("cmdclear", "label", 720,400, 80,80);
		liqcell_setfont(	cmdclear, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(cmdclear, "clr" );
		//liqcell_propsets(  cmdclear, "textcolor", "rgb(255,255,255)" );
		//liqcell_propsets(  cmdclear, "backcolor", "rgb(64,0,0)" );
		//liqcell_propsets(  cmdclear, "bordercolor", "rgb(200,100,100)" );
		//liqcell_propseti(  cmdclear, "textalign", 2 );
		liqcell_handleradd_withcontext(cmdclear, "click", cmdclear_click, self );
		liqcell_child_append(  self, cmdclear);
		
		
	liqcell_propsets(  cmdclear, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  cmdclear, "backcolor", "rgb(0,128,0)" );
	//liqcell_propsets(  cmdclear, "bordercolor", "rgb(200,100,100)" );
	liqcell_setimage(  cmdclear,  liqimage_cache_getfile("/usr/share/liqbase/liqflow/media/button_back.png", 0,0,1) );
	liqcell_propseti(  cmdclear, "textalign", 2 );
	liqcell_propseti(  cmdclear, "textaligny", 2 );
	liqcell_propseti(  cmdclear,  "lockaspect",  0 );
		
			

	//############################# aname:label
	liqcell *aname = liqcell_quickcreatevis("aname", "label", 196, 82, 396, 100);
	liqcell_setfont(	aname, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (68), 0) );
	liqcell_setcaption(aname, "liqflow_run" );
	liqcell_propsets(  aname, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  aname, "backcolor", "rgb(128,128,128)" );
	liqcell_propseti(  aname, "textalign",  2 );
	liqcell_propseti(  aname, "textaligny", 2 );
	liqcell_child_append(  self, aname);		
		
	//############################# ainvite:label
	liqcell *ainvite = liqcell_quickcreatevis("ainvite", "label", 196, 266, 396, 90);
	liqcell_setfont(	ainvite, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (50), 0) );
	liqcell_setcaption(ainvite, "step inside." );
	//liqcell_propsets(  ainvite, "textcolor", "rgb(0,255,0)" );
	//liqcell_propsets(  ainvite, "backcolor", "rgb(0,64,0)" );
	//liqcell_propsets(  ainvite, "bordercolor", "rgb(200,100,100)" );
	//liqcell_propseti(  ainvite, "textalign",  2 );
	//liqcell_propseti(  ainvite, "textaligny", 2 );
	
	
	liqcell_propsets(  ainvite, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  ainvite, "backcolor", "rgb(0,128,0)" );
	//liqcell_propsets(  ainvite, "bordercolor", "rgb(200,100,100)" );
	liqcell_setimage(  ainvite,  liqimage_cache_getfile("/usr/share/liqbase/liqflow/media/button_back.png", 0,0,1) );
	liqcell_propseti(  ainvite, "textalign", 2 );
	liqcell_propseti(  ainvite, "textaligny", 2 );
	liqcell_propseti(  ainvite,  "lockaspect",  0 );



	liqcell_child_append(  self, ainvite);

		
		
		
		liqcell_handleradd_withcontext(self, "dialog_open", widget_dialog_open ,self);
		liqcell_handleradd_withcontext(self, "dialog_close", widget_dialog_close ,self);
		
		liqcell_handleradd_withcontext(self,    "mouse",   sketchedit_mouse,self);
		liqcell_handleradd_withcontext(self,    "paint", widget_paint,self);
		
		liqcell_propseti(self,"sketchediting",1);		// mark it as editing :)
		
		
		liqcell_handlerrun(self,"dialog_close",NULL);
		
	}
	return self;
}

