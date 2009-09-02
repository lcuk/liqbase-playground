// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### angleruler :: by gary birkett
//#####################################################################
//#####################################################################



		

/**	
 * angleruler dialog_open - the user zoomed into the dialog
 */	
static int angleruler_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * angleruler dialog_close - the dialog was closed
 */	
static int angleruler_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * angleruler widget shown - occurs once per lifetime
 */	
static int angleruler_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	liqcell_handlerrun(self,"refresh",NULL);
	return 0;
}

/**	
 * angleruler mouse - occurs all the time as you stroke the screen
 */	
static int angleruler_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	liqcell *knob = liqcell_child_lookup(self, "knob");

	liqcell_setpos( knob, args->mex - args->ox - (knob->w/2), liqcell_gety(knob) );
	liqcell_forceinboundparent(knob);
	
	liqcell_handlerrun(self,"refresh",NULL);
	
	return 0;
}
/**	
 * angleruler click - occurs when a short mouse stroke occured
 */	
static int angleruler_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * angleruler keypress - the user pressed a key
 */	
static int angleruler_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * angleruler keyrelease - the user released a key
 */	
static int angleruler_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}



/**	
 * angleruler paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
static int angleruler_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
{
//	// big heavy event, use sparingly
//	liqcliprect *cr=args->graph->cliprect;

	//liqcliprect_drawboxfillcolor(cr, 299 ,0 ,2,100 , 128,255,255);
 //   liqcliprect_drawlinecolor(cr, 300,10 ,300,90 ,  0,128,128);

	return 0;
}
/**	
 * angleruler dynamic resizing
 */	
static int angleruler_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
//	float sx=((float)self->w)/((float)self->innerw);
//	float sy=((float)self->h)/((float)self->innerh);
	
//	liqcell *knob = liqcell_child_lookup(self, "knob");
//	liqcell_setrect_autoscale( knob, 178,2, 150,30, sx,sy);
	return 0;
}



static liqimage *ruler_create()
{
liqimage *img   = liqimage_newatsize( 1800, 100, 0 );
liqcliprect *cr = liqcliprect_newfromimage( img );

int deg;
int x;

char tit[32]={0};
int  titw=0;
int tith=0;

liqfont *titfont = liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (20), 0);


    liqcliprect_drawclear(cr,0,128,128);
	

    //                        liqcliprect_drawboxfillcolor(cr, 0   ,0 ,2,100 , 128,255,255);
    //                        liqcliprect_drawboxfillcolor(cr, 1798,0 ,2,100 , 128,255,255);
    for(deg=0;deg<=360;deg++)
    {
        x=deg*5;
        //if(deg==360) deg=0;
        
        
 							
							
							
							
                            liqcliprect_drawlinecolor(cr, x,0 ,x,10 ,  255,128,128);
                            liqcliprect_drawlinecolor(cr, x,90,x,100,  255,128,128);
       
        
        if((deg % 5)==0)
        {
                            liqcliprect_drawlinecolor(cr, x,0 ,x,20 ,  255,128,128);
                            liqcliprect_drawlinecolor(cr, x,80,x,100,  255,128,128);
        }
        
        if((deg % 10)==0)
        {
            if( (deg<=180) || (deg==360) )
                snprintf(tit,sizeof(tit),"%i",(deg % 360));
            else
                snprintf(tit,sizeof(tit),"%i",(deg % 360)-360);
            titw = liqfont_textwidth(titfont,tit);
			tith = liqfont_textheight(titfont);
        
                            liqcliprect_drawtext_color(cr,titfont,x-titw/2,(100-tith)/2,tit,  255,128,128);
        }
    }
    
    liqfont_release(titfont);

    return img;

}







/**	
 * create a new angleruler widget
 */	
liqcell *angleruler_create()
{
	liqcell *self = liqcell_quickcreatewidget("angleruler", "form", 600, 100);
	if(!self) {liqapp_log("liqcell error not create 'angleruler'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	
	

	liqimage *ruler = ruler_create();
	
	//############################# knob:label
	liqcell *knob = liqcell_quickcreatevis("knob", "label", 0, 0, 1800, 100);
    liqcell_setimage(knob, liqimage_hold(ruler) );
	liqcell_propseti(knob,"lockaspect",0);
	liqcell_child_append(  self, knob);
 
 
 	//############################# knob:label
	liqcell *knob2 = liqcell_quickcreatevis("knob2", "label", -1800, 0, 1800, 100);
    liqcell_setimage(knob2, liqimage_hold(ruler) );
	liqcell_propseti(knob2,"lockaspect",0);
	liqcell_child_append(  self, knob2);
 
 
 	//############################# bar:label
	liqcell *bar = liqcell_quickcreatevis("bar", "label", 298, 10, 4, 80);
	liqcell_propsets(  bar, "backcolor", "rgba(255,0,0,255)" );
	liqcell_child_append(  self, bar);
    
 	//############################# bar:label
	liqcell *shad = liqcell_quickcreatevis("bar", "label", 292, 10, 4, 80);
	liqcell_propsets(shad, "backcolor", "rgba(0,0,0,128)" );
	liqcell_child_append(  self, shad);
    

    
	liqcell_propsets(  self, "backcolor", "rgba(0,0,64,128)" );
	//liqcell_handleradd_withcontext(self, "refresh", angleruler_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", angleruler_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", angleruler_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", angleruler_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", angleruler_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", angleruler_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", angleruler_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", angleruler_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", angleruler_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", angleruler_dialog_close ,self);
	return self;
}

