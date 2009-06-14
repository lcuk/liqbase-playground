#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>



// based on http://talk.maemo.org/showthread.php?p=290762#post290762



//#####################################################################
//#####################################################################
//##################################################################### jumptoconclusions :: by gary birkett
//#####################################################################
//#####################################################################



	
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
	

	static int widget_mouse(liqcell *self, liqcellmouseeventargs *args,void *context)
	{
		// this is the mouse event for a single conclusion
		
		// whilst the button is pressed, the button should change color
		
		if(args->mez!=0)
		{
			liqcell_propsets(  self, "textcolor", "rgb(0,200,200)" );
			liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
			
		}
		else
		{
			liqcell_propsets(  self, "textcolor", "rgb(0,0,0)" );
			liqcell_propsets(  self, "backcolor", "rgb(0,200,200)" );
			
		}

	}

	

liqcell *jumptoconclusions_create()
{
	liqcell *self = liqcell_quickcreatewidget("jumptoconclusions","form", 800,480);//480,800);

	if(self)
	{
		//############################# title:label
		liqcell *title = liqcell_quickcreatevis("title", "label", 0,0, self->w, 50);
		liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (39), 0) );
		liqcell_setcaption(title, "jump to conclusions" );
		liqcell_propsets(  title, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  title, "backcolor", "rgb(255,255,255)" );
		liqcell_propseti(  title, "textalign", 2 );
		liqcell_child_append(  self, title);
	 
		//############################# start:label
		liqcell *start = liqcell_quickcreatevis("start", "label", 0, self->h-50, self->w, 50);
		liqcell_setfont(	start, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (35), 0) );
		liqcell_setcaption(start, "start" );
		liqcell_propsets(  start, "textcolor",   "rgb(0,0,0)" );
		//liqcell_propsets(  start, "backcolor",   "rgb(0,40,0)" );
		//liqcell_propsets(  start, "bordercolor", "rgb(0,150,0)" );
		liqcell_propseti(  start, "textalign",   2 );
		liqcell_propseti(  start, "textaligny",  2 );
		liqcell_child_append(  self, start);
 
 

	
	
	
		liqcell *body = liqcell_quickcreatevis("body",NULL, 0 ,50,   self->w,self->h-100);


		liqcell *addoneconclusion(liqcell *body,char *caption)
		{
			char buf[256];
			snprintf(buf,sizeof(buf),"%s1",caption);
			liqcell *newx = liqcell_quickcreatevis(buf,"label",0,0,0,0);
			
			liqcell *item = newx;
			liqcell_setcaption(item, caption );
			liqcell_setfont(item, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
			liqcell_propsets(  item, "textcolor", "rgb(0,0,0)" );
			liqcell_propsets(  item, "backcolor", "rgb(0,200,200)" );
			liqcell_propseti(  item, "textalign", 2 );
			liqcell_propseti(  item, "textaligny",2 );
			
			//liqcell *item = liqcell_quickcreatevis(buf,"item",0,0,newx->w,newx->h);
			//liqcell_propseti(  item,    "lockaspect",1);
			//liqcell_setcontent(item,    newx);
			liqcell_handleradd_withcontext(item,    "mouse",   widget_mouse, self);
			liqcell_child_append( body, item );
			return item;
			
		}
		
		addoneconclusion(body,"???");
		addoneconclusion(body,"JUMP AGAIN");
		addoneconclusion(body,"STRIKE OUT");
		addoneconclusion(body,"COULD BE");
		addoneconclusion(body,"LOSE ONE TURN");
		addoneconclusion(body,"YES");
		addoneconclusion(body,"NO!");
		addoneconclusion(body,"ACCEPT IT");
		addoneconclusion(body,"GO WILD");
		addoneconclusion(body,"ONE STEP BACK");
		addoneconclusion(body,"THINK AGAIN");
		addoneconclusion(body,"MOOT!");


		
		liqcell_child_arrange_easytile( body );
		//liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_insert( self, body );
		
		
		liqcell_propsets(  self, "backcolor", "rgb(255,255,255)" );

	}

	return self;
}













//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when project1 is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"jumptoconclusions canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}

int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"jumptoconclusions" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"project1 liqapp_init failed"); }
	 }
	 liqcell *self = jumptoconclusions_create();
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}
