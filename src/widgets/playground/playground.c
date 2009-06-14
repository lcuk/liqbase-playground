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

int liqcell_filter_run(liqcell *c,char *searchterm)
{
				liqcellfiltereventargs filterargs;
				filterargs.filterinuse= (searchterm ? 1 : 0);
				filterargs.searchterm = searchterm;
				filterargs.searchtags = NULL;
				filterargs.resultoutof= 1;
				filterargs.resultshown= 1;
				
				liqcell_handlerrun( c , "filter", &filterargs );
				
				if(filterargs.resultshown)
				{
					liqcell_setvisible(c,1);
					return 1;
				}
				else
				{
					liqcell_setvisible(c,0);
					return 0;
				}
}

//#####################################################################
//#####################################################################
//##################################################################### playground :: by gary birkett
//#####################################################################
//#####################################################################






//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
	static int search_click(liqcell *self, liqcelleventargs *args, liqcell *playground)
	{
		// try to add this tag :)
		liqcell *body = liqcell_child_lookup(playground,"body");
		char *searchterm = liqcell_getcaption(self);
		if(!searchterm || !*searchterm) return 1;
		//liqcell *body = liqcell_child_lookup(playground,"body");
	    //playground_insert(body,searchterm, 45);
		
		liqcell_setcaption(self,"");
		return 1;
	}
	static int search_change(liqcell *self, liqcelleventargs *args, liqcell *playground)
	{
		// examine each tag and if matches the search show it, otherwise dont..
		liqcell *body = liqcell_child_lookup(playground,"body");
		char *searchterm = liqcell_getcaption(self);
		
		liqcell *c = liqcell_getlinkchild(body);
		while(c)
		{
			if(liqcell_getflagvisual(c))
			{
				liqcell_filter_run(c,searchterm);
			}
			c=liqcell_getlinknext(c);
		}
		liqcell_setrect(body,   0,40,playground->w,playground->h-40);
		//liqcell_child_arrange_easytile( body );
		liqcell_child_arrange_makegrid_fly(body,3,3);
		
		liqcell_propseti(self,"arrangecomplete",0);
		
		//liqcell_setpos(body,0,40);
		
		if(!searchterm || !*searchterm)
		{
			// bit of magic here..
			liqcell_setvisible(self,0);
		}
		
		return 1;
		
	}
	
	
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
	
	
	static int playground_refresh(liqcell *self, liqcelleventargs *args, void *context)
	{
	
		return 1;
	}
	
	
	
	

	
	static int playground_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *playground)
	{
		liqapp_log("tc.kp");
		// if we are getting this keypress, we shouldnt be
		// it should be the search button
		liqcell *search = liqcell_child_lookup(playground,"search");
		if(liqcell_getvisible(search)==0)
		{
			// start it just off screen
			liqcell_setpos( search, liqcell_getx(search), liqcell_geth(playground) );
			liqcell_setvisible(search,1);
		}
		return liqcell_handlerrun(search,"keypress",args);
	}
	static int playground_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *playground)
	{
		liqapp_log("tc.kr");
		// if we are getting this keypress, we shouldnt be
		// it should be the search button
		liqcell *search = liqcell_child_lookup(playground,"search");
		//liqcell_setvisible(search,1);
		return liqcell_handlerrun(search,"keyrelease",args);
	}


	static int playground_paint(liqcell *self, liqcellpainteventargs *args,liqcell *playground)
	{
		liqcell *search = liqcell_child_lookup(playground,"search");
		if(liqcell_getvisible(search))
		{
			if( liqcell_gety(search) > ( liqcell_geth(playground) - liqcell_geth(search) )  )
			{
				// move it a bit more onscreen
				int dif = liqcell_gety(search) - ( liqcell_geth(playground) - liqcell_geth(search) );
				if(dif>5)dif=5;
				liqcell_setpos( search, liqcell_getx(search), liqcell_gety(search) - dif );
				liqcell_setdirty(playground,1);
			}
		}
        
        if( liqcell_propgeti(self,"arrangecomplete",0) == 0 )
        {
                liqcell *body = liqcell_child_lookup(self,"body");
            	liqcell_setrect(body,   0,40,self->w,self->h-40);
                
                liqcell_setdirty(body,0);
                
                if( liqcell_child_arrange_makegrid_fly(body,3,3) )
                {
					//liqcell_propseti(self,"arrangecomplete",1);
                }
                if( ! liqcell_getdirty(body) )
                {
					// the complete advance occured without a change :)
					//liqcell_propseti(self,"arrangecomplete",1);
                }
		}
		
		return 0;
	}


	static int playground_resize(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqcell *search = liqcell_child_lookup(self,"search");		
		liqcell_setrect(search, self->w*0.2 ,self->h-40,   self->w*0.4, 40);
		//liqcell_setrect(search, self->w*0.2 ,0,   self->w*0.4, 40);
		
		
		liqcell *body = liqcell_child_lookup(self,"body");
		liqcell_setrect(body,   0,40,self->w,self->h-40);
		//liqcell_setsize(body,   self->w,self->h);
		//liqcell_child_arrange_easytile( body );
		liqcell_child_arrange_makegrid_fly(body,3,3);
		
		return 1;
	}
	

liqcell *playground_create()
{
	liqcell *self = liqcell_quickcreatewidget("playground","form", 800,480);

	if(self)
	{
		//############################# title:label
		liqcell *title = liqcell_quickcreatevis("title", "label", 0,0, 400, 40);
		liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(title, "liqbase playground" );
		liqcell_propsets(  title, "textcolor", "rgb(255,0,0)" );
		liqcell_propsets(  title, "backcolor", "rgb(0,0,60)" );
		liqcell_propseti(  title, "textalign", 0 );
		liqcell_child_append(  self, title);
	 
/*		//############################# accept:label
		liqcell *accept = liqcell_quickcreatevis("accept", "label", 600, 440, 200, 40);
		liqcell_setfont(	accept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (35), 0) );
		liqcell_setcaption(accept, "save" );
		liqcell_propsets(  accept, "textcolor",   "rgb(0,255,0)" );
		liqcell_propsets(  accept, "backcolor",   "rgb(0,40,0)" );
		liqcell_propsets(  accept, "bordercolor", "rgb(0,150,0)" );
		liqcell_propseti(  accept, "textalign",   2 );
		liqcell_propseti(  accept, "textaligny",  2 );
		liqcell_child_append(  self, accept);
 
 */

	
	
	
		liqcell *body = liqcell_quickcreatevis("body",NULL,0 ,0,   self->w,self->h);
		//playground_fillup_test( body );
		
			//

			liqcell *recentpictures1 = liqcell_quickcreatevis("recentpictures1","playground.recentpictures",0,0,0,0);
			liqcell_child_append( body, recentpictures1 );

			liqcell *recentsketches1 = liqcell_quickcreatevis("recentsketches1","playground.recentsketches",0,0,0,0);
			liqcell_child_append( body, recentsketches1 );

			//liqcell *codelist1 = liqcell_quickcreatevis("codelist1","playground.codelist",0,0,0,0);
			//liqcell_child_append( body, codelist1 );

			liqcell *songlist1 = liqcell_quickcreatevis("songlist1","playground.songlist",0,0,0,0);
			liqcell_child_append( body, songlist1 );


			//liqcell *tagcloud1 = liqcell_quickcreatevis("tagcloud1","playground.tagcloud",0,0,0,0);
			//liqcell_child_append( body, tagcloud1 );
            
            
            
			//liqcell_propseti(  tagcloud1, "filterlike", 0 );

		


			liqcell *booklist1 = liqcell_quickcreatevis("booklist1","playground.booklist",0,0,0,0);
			liqcell_child_append( body, booklist1 );

 /*

		liqcell *addone(liqcell *body,char *classname)
		{
			char buf[256];
			snprintf(buf,sizeof(buf),"%s1",classname);
			liqcell *newx = liqcell_quickcreatevis(buf,classname,0,0,0,0);
			
			//liqcell *item = newx;
			
			liqcell *item = liqcell_quickcreatevis(buf,"item",0,0,newx->w,newx->h);
			liqcell_propseti(  item,    "lockaspect",1);
			liqcell_setcontent(item,    newx);
			liqcell_handleradd(item,    "click",   widget_click);
			liqcell_child_append( body, item );
			return item;
			
		}

		addone(body, "recentpictures");
		addone(body, "recentsketches");
		addone(body, "songlist");
		addone(body, "widgetlist");
 */
		
		liqcell_child_arrange_easytile( body );
		//liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_insert( self, body );
		

		
		
		liqcell *search = liqcell_quickcreatevis("search","playground.textbox",self->w*0.2 ,self->h-40,   self->w*0.4, 40);
		liqcell_setfont(   search,  liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_setcaption(search, "" );
		liqcell_handleradd_withcontext( search,    "click",           search_click,  self );
		liqcell_handleradd_withcontext( search,    "captionchange",   search_change, self );
		liqcell_setvisible(search,0);		// watch this!

		liqcell_child_append( self, search );
		
		
		
		liqcell_handleradd_withcontext(body,    "keypress",   playground_keypress,  self);
		liqcell_handleradd_withcontext(body,    "keyrelease", playground_keyrelease,self);
		
		liqcell_handleradd_withcontext(self,    "keypress",   playground_keypress,  self);
		liqcell_handleradd_withcontext(self,    "keyrelease", playground_keyrelease,self);
		
		
		liqcell_handleradd_withcontext(self,    "resize",     playground_resize,    self);
		liqcell_handleradd_withcontext(self,    "refresh",    playground_refresh,   self);
		liqcell_handleradd_withcontext(self,    "paint",      playground_paint,  	self);

		playground_resize(self,NULL,NULL);

	// 9.4fps bust rendering loop on here on my system WITH the image
	//	liqcell_setimage(  self ,  liqimage_cache_getfile( "media/liqbase_back2.jpg",0,0,1) );
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
		  liqapp_errorandfail(-1,"project1 canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}

int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"playground" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"playground liqapp_init failed"); }
	 }
	 liqcell *self = playground_create();
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}
