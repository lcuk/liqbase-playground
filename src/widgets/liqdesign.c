

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>










//------------------------------------------------------------------------------------------

#define ABS(X) ((X)<0?-(X):(X))

int liqcell_rect_gethitpad(liqcell *self,int x,int y,int *hitx,int *hity,    int bx,int by)
{
	// set a pair of numeric indicators indicating which segment the x,y relate to
	// return a flag indicating if infact the x,y hit within the boundary
int ishit=0;
	*hitx=-2;
	*hity=-2;
	if(!self->visible)return 0;
		 if(x<self->x-bx)
			{*hitx=-2;          }
	else if(x<self->x+bx)
			{*hitx=-1;	ishit=1;}
	else if(x<self->x+self->w-bx)
			{*hitx=0;	ishit=1;}
	else if(x<self->x+self->w+bx)
			{*hitx=1;   ishit=1;}
	else
			{*hitx=2;           }

		 if(y<self->y-by)
			{*hity=-2;          }
	else if(y<self->y+by)
			{*hity=-1; ishit=1; }	
	else if(y<self->y+self->h-by)
			{*hity=0; ishit=1;  }		
	else if(y<self->y+self->h+by)
			{*hity=1; ishit=1;  }
	else
			{*hity=2;           }	
	if(ABS(*hitx)<=1 && ABS(*hity)<=1)
		ishit=1;
	else
		ishit=0;

	liqapp_log("hitpad: mxy(%i,%i)    sxy(%i,%i)-step(%i,%i)           %i,%i,  %i",x,y, self->x,self->y,self->w,self->h,         *hitx,*hity,ishit);
	return ishit;
}


int liqcell_rect_gethitcode(liqcell *self,int x,int y,int borderx,int bordery)
{
	// return a numeric indicator about what segment the x,y relates to has clicked in
	// clockwise spiral from top left
	// 123
	// 894
	// 765
	
	int hitx=0;
	int hity=0;
	int hitok = liqcell_rect_gethitpad(self,   x,y,    &hitx,&hity,   borderx,bordery);
	if(!hitok) return 0;
	if(hitx==-2 || hitx==2) return 0;
	if(hitx==-1)
	{
		if(hity==-2 || hity==2) return 0;
		if(hity==-1) return 1;
		if(hity== 0) return 8;
		if(hity== 1) return 7;
		return 0;
	}

	if(hitx==0)
	{
		if(hity==-2 || hity==2) return 0;
		if(hity==-1) return 2;
		if(hity== 0) return 9;
		if(hity== 1) return 6;
		return 0;
	}

	if(hitx==1)
	{
		if(hity==-2 || hity==2) return 0;
		if(hity==-1) return 3;
		if(hity== 0) return 4;
		if(hity== 1) return 5;
		return 0;
	}
	return 0;
}




void liqcell_rect_adjust_hitcode(liqcell *self, int hitcode, int dx, int dy)
{
int l=self->x;
int t=self->y;
int r=self->x+self->w;
int b=self->y+self->h;
    switch( hitcode )
	{
        case 1:
            l = l + dx; t = t + dy;
            r = r - 0 ; b = b - 0;
			break;
        
        case 2:
            l = l + 0; t = t + dy;
            r = r - 0; b = b - 0;
			break;
        case 3:
            l = l + 0;  t = t + dy;
            r = r + dx; b = b - 0;
            break;
        case 4:
            l = l + 0;  t = t + 0;
            r = r + dx; b = b + 0;
			break;
        case 5:
            l = l + 0;  t = t + 0;
            r = r + dx; b = b + dy;
			break;
        case 6:
            l = l + 0;  t = t + 0;
            r = r + 0;  b = b + dy;
			break;
        case 7:
            l = l + dx; t = t + 0;
            r = r - 0; b = b + dy;
			break;
        case 8:
            l = l + dx; t = t + 0;
            r = r - 0; b = b + 0;
            break;
        case 9:
            l = l + dx; t = t + dy;
            r = r + dx; b = b + dy;
			break;
	}
	
	liqcell_setrect(self,l,t,r-l,b-t);
    
  //'  EnsurePositive
}




	static void liqcell_rect_ensurepositive(liqcell *self)
	{
		int w=self->w;
		int h=self->h;
		if(w>=0 && h>=0)return;
		int x=self->x;
		int y=self->y;
		if(w<0){ w=-w; x-=w; }
		if(h<0){ h=-h; y-=h; }
		liqcell_setrect(self,x,y,w,h);
	}
	
	
//#####################################################################
//#####################################################################
//##################################################################### liqdesign :: by gary birkett :)
//#####################################################################
//#####################################################################


	static int liqdesign_dialog_open(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqapp_log("dialog_open");
		return 1;
	}


	static int liqdesign_dialog_close(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqapp_log("dialog_close");
		return 1;
	}

	//############################################################################################

	static int liqdesign_undo_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("undo_click");
		return 1;
	}


	static int liqdesign_clear_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("clear_click");
		return 1;
	}

	static int liqdesign_del_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("del_click");
		return 1;
	}

	static int liqdesign_save_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("save_click");
		return 1;
	}

	static int liqdesign__cmdnull_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		// empty mouse handler so we dont draw behind the buttons..
		return 1;
	}
	
	//############################################################################################
	static int liqdesign_surface_item_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		

		//
		if(args->mcnt==1)
		{
			// starting
			// find out where and how we were hit
			
			//int hitx=0;
			//int hity=0;
			int hitcode = liqcell_rect_gethitcode(self,   args->msx-args->ox + self->x,args->msy-args->oy + self->y  ,self->w/8,self->h/8);
			liqcell_propseti(self,"hitcode",hitcode);
			liqapp_log("item mouse (%i,%i),  hc=%i", args->msx-args->ox,args->msy-args->oy,   hitcode );
		}
		else
		{
			// now, we must adjust ourselves according to the hit location identified
			int hitcode = liqcell_propgeti(self,"hitcode",0);
			liqcell_rect_adjust_hitcode(self,hitcode,args->mdx,args->mdy);
		}
		//liqcell_adjustpos(self,args->mdx,args->mdy);
		return 1;
	}
	
	
	
	static int liqdesign_surface_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		//liqapp_log("surface mouse mcnt=%i, mex==%i, mey==%i, mez==%i",args->mcnt, args->ox+args->mex,args->oy+args->mey,   args->mez);
		// on the surface there might be 0..N items
		// if I hit any of those items the item itself will have recvd the mouse event
		// if i hit directly on the surface, the intention will be to create a drag box
		
		liqcell *grabbox = liqcell_child_lookup(self,"grabbox");
		if(!grabbox)
		{
			grabbox = liqcell_quickcreatevis("grabbox","grabbox",  args->msx-args->ox,args->msy-args->oy,      0,0 );
			liqcell_setfont(   grabbox, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
			liqcell_propsets(  grabbox,    	"bordercolor", "rgb(255,255,255)" );
			liqcell_setvisible(grabbox ,0);
			liqcell_child_insert( self, grabbox );		
		}

		
		if(args->mcnt==1)
		{
			// starting
			liqcell_setrect(   grabbox ,   args->msx-args->ox,args->msy-args->oy   , 0,0);
			liqcell_setvisible(grabbox ,1);

		}
		else
		{
			if(args->mez!=0)
			{
				// continuing
				liqcell_setrect(   grabbox ,    args->msx-args->ox,args->msy-args->oy,     args->mex-args->msx,args->mey-args->msy);
				liqcell_rect_ensurepositive(grabbox);
				liqcell_setvisible(grabbox ,1);
			}
			else
			{
				// finished, create
				liqcell_setrect(   grabbox ,     args->msx-args->ox,args->msy-args->oy,             args->mex-args->msx,args->mey-args->msy);
				liqcell_rect_ensurepositive(grabbox);
				liqcell_setvisible(grabbox ,0);


				liqcell *b = liqcell_quickcreatevis("contentx","liqbase",  0,0,0,0 );
				//liqcell_child_insert( self, b );
				
				
				
				
				liqcell *c = liqcell_quickcreatevis("item1","item",  args->msx-args->ox,args->msy-args->oy,   args->mex-args->msx,args->mey-args->msy );
				liqcell_rect_ensurepositive(c);
				//liqcell_propseti(c,     "lockaspect",  1);
				//liqcell_setfont( c,     liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
				liqcell_propsets(c,    	"bordercolor", "rgb(255,0,0)" );
				liqcell_handleradd(c,   "mouse",       liqdesign_surface_item_mouse);
				
				// 20090513_000454 lcuk : set this to make an IFS fractal :)
				//liqcell_setcontent( c,liqcell_getbasewidget(self) );
				
				liqcell_setcontent( c,b );
				
				liqcell_child_insert( self, c );

			}
		}
		
		return 1;
	}

	static int liqdesign_surface_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("surface click");
		return 1;
	}

	static int liqdesign_surface_keypress(liqcell *self, liqcellkeyeventargs *args, void *context)
	{
		liqapp_log("surface key");
		return 1;
	}
	
	
	//############################################################################################
			
		
		
	static int liqdesign_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		liqapp_log("general mouse mex==%i, mey==%i, mez==%i",args->mex,args->mey,args->mez);
		return 1;
	}


	static int liqdesign_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("general click");
		return 1;
	}



	static int liqdesign_keypress(liqcell *self, liqcellkeyeventargs *args, void *context)
	{
		liqapp_log("general key");
		return 1;
	}
	
	

	static int liqdesign_resize(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqapp_log("general resize");
		
		//liqcell *base = liqcell_getbasewidget(self);
		liqcell *undo = liqcell_child_lookup(self,"undo");
		liqcell *clear = liqcell_child_lookup(self,"clear");
		liqcell *save = liqcell_child_lookup(self,"save");
		liqcell *del = liqcell_child_lookup(self,"del");
		liqcell *surface = liqcell_child_lookup(self,"surface");
		
		int ww=liqcell_getw(self);
		int hh=liqcell_geth(self);
		
		liqcell_setrect(undo,    ww*0.9,  0,        ww*0.1,hh*0.3);
		liqcell_setrect(clear,   ww*0.9,  hh*0.3,   ww*0.1,hh*0.3);
		liqcell_setrect(save ,   ww*0.9,  hh*0.6,   ww*0.1,hh*0.3);
		liqcell_setrect(del ,    ww*0.9,  hh*0.9,   ww*0.1,hh*0.1);
		liqcell_setrect(surface ,0,       0,        ww*0.9,hh);
		return 1;
	}
	

	//############################################################################################



liqcell *liqdesign_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqdesign","form", 800,480);

	if(self)
	{

		liqcell *b;

		b = liqcell_quickcreatevis("undo","button",  800-180,20,   160,160 );
		liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_propsets(  b,    	"backcolor", "rgb(100,0,100)" );
		liqcell_handleradd(b,    	"click",     liqdesign_undo_click);
		liqcell_handleradd(b,    	"mouse",     liqdesign__cmdnull_mouse);
		liqcell_child_insert( self, b );

		b = liqcell_quickcreatevis("clear","button",  800-180,20,   160,160 );
		liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_propsets(  b,    	"backcolor", "rgb(0,0,100)" );
		liqcell_handleradd(b,    	"click",     liqdesign_clear_click);
		liqcell_handleradd(b,    	"mouse",     liqdesign__cmdnull_mouse);
		liqcell_child_insert( self, b );

		b = liqcell_quickcreatevis("save","button",  800-180,200,   160,160 );
		liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_propsets(  b,    	"backcolor", "rgb(0,100,0)" );
		liqcell_handleradd(b,    	"click",     liqdesign_save_click);
		liqcell_handleradd(b,    	"mouse",     liqdesign__cmdnull_mouse);
		liqcell_child_insert( self, b );

		b = liqcell_quickcreatevis("del","button",  800-180,200,   160,160 );
		liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_propsets(  b,    	"backcolor", "rgb(100,0,0)" );
		liqcell_handleradd(b,    	"click",     liqdesign_del_click);
		liqcell_handleradd(b,    	"mouse",     liqdesign__cmdnull_mouse);
		liqcell_child_insert( self, b );

		b = liqcell_quickcreatevis("surface","designer",  0,0 ,   640,480 );
		liqcell_setcaption(b,       "liqsurface");  	
		liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
		//liqcell_propsets(  b,    	"backcolor", "rgb(40,40,40)" );
		liqcell_handleradd(b,    	"keypress",  liqdesign_surface_keypress);
		liqcell_handleradd(b,    	"click",     liqdesign_surface_click);
		liqcell_handleradd(b,    	"mouse",     liqdesign_surface_mouse);
		liqcell_child_insert( self, b );




		liqdesign_resize(self,NULL, NULL);

		liqcell_handleradd(self,    "keypress",      liqdesign_keypress);
		liqcell_handleradd(self,    "mouse",         liqdesign_mouse);
		liqcell_handleradd(self,    "click",         liqdesign_click);
		liqcell_handleradd(self,    "resize",        liqdesign_resize);

		liqcell_handleradd(self,    "dialog_open",   liqdesign_dialog_open);
		liqcell_handleradd(self,    "dialog_close",  liqdesign_dialog_close);
		
		
	}
	return self;

}
