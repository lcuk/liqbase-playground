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



liqcell *liqbase_playground_root=NULL;



	static int playground_item_mouse(liqcell *self, liqcellmouseeventargs *args, liqcell *playground);
	static int playground_item_click(liqcell *self, liqcellclickeventargs *args, liqcell *playground);
    static int playground_item_dirty(liqcell *self, liqcelleventargs *args, liqcell *playground);





		static liqcell *addone(liqcell *desktopmanage,liqcell *body,char *classname)
		{
			char buf[256];
			snprintf(buf,sizeof(buf),"%s",classname);
			liqcell *newx = liqcell_quickcreatevis(buf,classname,0,0,-1,-1);
            if(!newx)return NULL;
            if(newx->w<=0 || newx->h<=0)
            {
                liqcell_release(newx);
                return NULL;
            }
            
            
            
            liqcell_handleradd_withcontext(newx,    "dirty",   playground_item_dirty, desktopmanage );
			
			//liqcell *item = newx;
			
			liqcell *item = liqcell_quickcreatevis(buf,"item",0,0,newx->w,newx->h);
			liqcell_propseti(  item,    "lockaspect",1);
			liqcell_setcontent(item,    newx);
			liqcell_handleradd_withcontext(item,    "click",   playground_item_click,desktopmanage );
			liqcell_handleradd_withcontext(item,    "mouse",   playground_item_mouse,desktopmanage );
			liqcell_child_insertsortedbyname( body, item , 1);
			return item;
			
		}









        extern char * liqtwitter_message;



        static int playground_send_tweet(liqcell *button, liqcellclickeventargs *args, liqcell *playground)
        {
            liqcell *search = liqcell_child_lookup(playground,"search");
            liqapp_log("send a tweet :)");
            liqtwitter_message = liqcell_getcaption(search);
            
            liqcell * progress = liqcell_quickcreatevis("liqbase-playground.liqtwitter_sendprogress","liqbase-playground.liqtwitter_sendprogress",0,0,-1,-1);
            
            if(progress)
            {
                liqcell_easyrun(progress);
                int sentok = liqcell_propgeti(progress,"sentok",0);
                liqcell_release(progress);
                
                if(!sentok)
                {
                    //return 0;
                }
                
                if(sentok)
                {
                    liqcell_setcaption(search,"");
                }
            }            
            return 0;
        }



        static int playground_send_google(liqcell *button, liqcellclickeventargs *args, liqcell *playground)
        {
            liqapp_log("send to google :)");
        }




        static int playground_send_console(liqcell *button, liqcellclickeventargs *args, liqcell *playground)
        {
            liqapp_log("run a sh command :)");
        }





























int liqbase_playground_check_if_class_shown(char *classname)
{
    liqcell *body = liqcell_child_lookup(liqbase_playground_root,"body");    
    liqcell *c = liqcell_getlinkchild_visual(body);
    while(c)
    {
        //liqapp_log("liqbase_playground_check_if_class_shown: testing if '%s' == '%s'",classname,c->name);
        if( (strcasecmp(c->name,classname)==0) )
        {
            //liqapp_log("liqbase_playground_check_if_class_shown: YESSSSSSSSSSSSSSSSSSSS '%s'",classname);
            return 1;
        }
        c=liqcell_getlinknext_visual(c);
    }
    return 0;
 /*   
    char *listall = liqapp_pref_getvalue_def("liqbase_playground_contents",    "desktopmanage");
    char tokbuf[2048]={0};
    char *tok=NULL;
            int isok = 0;
			snprintf(tokbuf,sizeof(tokbuf),"desktopmanage,%s",listall);
			tok = strtok(tokbuf, ",");
			while (tok)
			{
				if( (strcasecmp(classname,tok)==0) )
				{
					// ok to stay on screen
					isok=1;
					break;
				}
				else
				{
					// no match yet
				}
				tok = strtok(NULL, ",");
			}
            return isok;
 */

}


int liqbase_playground_refresh_desktop_contents()
{
    
    
        
    
    char *listall = liqapp_pref_getvalue_def("liqbase_playground_contents",    "desktopmanage");


    //liqbase_playground_root

    
    char tokbuf[2048]={0};
    char *tok=NULL;
    
    liqcell *body = liqcell_child_lookup(liqbase_playground_root,"body");
    
    // first, run around and remove stuff we no longer need
    liqcell *c = liqcell_getlinkchild_visual(body);
    
   // // skip the first item...
   // if(c)c = liqcell_getlinknext_visual(c);
    
    while(c)
    {
        
            if( (strcasecmp(c->name,"desktopmanage")==0) ) continue;
        

            int isok = 0;
            // loop around the tokens
			snprintf(tokbuf,sizeof(tokbuf),"desktopmanage,%s",listall);
			tok = strtok(tokbuf, ",");
			while (tok)
			{
				if( (strcasecmp(c->name,tok)==0) )
				{
					// ok to stay on screen
					isok=1;
					break;
				}
				else
				{
					// no match yet
				}
				tok = strtok(NULL, ",");
			}
            
            // get hold of the next in the chain now
            // cos we might be removing it :)
            liqcell *d=liqcell_getlinknext_visual(c);
            
            if(isok)
            {
                // phew! this is listed
            }
            else
            {
                // this is NOT listed, and must be removed
                liqcell_child_remove(body,c);
                liqcell_release(c);
                
            }
        
        
            c=d;
    }   

    
	// now, rerun around the strings
    // and this time, try to find a matching cell
    // if not, create one
    
    snprintf(tokbuf,sizeof(tokbuf),"desktopmanage,%s",listall);
    tok = strtok(tokbuf, ",");
    while (tok)
    {
        // now,
        //
        liqcell *c = liqcell_getlinkchild_visual(body);
        // skip the first item...
        if(c)c = liqcell_getlinknext_visual(c);
        while(c)
        {
            if( (strcasecmp(c->name,tok)==0) ) break;
            c=liqcell_getlinknext_visual(c);
        }
        if(c)
        {
            // already exists!
        }
        else
        {
            // need to create and append it
            addone(liqbase_playground_root,body,tok);
        }
        tok = strtok(NULL, ",");
    }
    
    liqcell_child_arrange_easytile( body );

    
}







int liqcell_filter_run(liqcell *c,char *searchterm)
{
    liqcellfiltereventargs filterargs;
    filterargs.filterinuse= (searchterm ? 1 : 0);
    filterargs.searchterm = searchterm;
    filterargs.searchtags = NULL;
    filterargs.resultoutof= 1;
    filterargs.resultshown= 0;
    
    if(!filterargs.resultshown)
    {
        if(searchterm && *searchterm)
        {
        }
        else
        {
            filterargs.resultshown = 1;
        }
    }
    
    if(!filterargs.resultshown)
    {
        if(c->name)
            filterargs.resultshown = ( stristr(c->name,searchterm) != NULL );
    }

    if(!filterargs.resultshown)
    {
        if(c->classname)
            filterargs.resultshown = ( stristr(c->classname,searchterm) != NULL );
    }
    
    liqcell *ccontent = liqcell_getcontent( c );
    if(ccontent)
    {
        liqapp_log("searching in cont '%s', %i",c->name,filterargs.resultshown);
        liqcell_handlerrun( ccontent , "filter", &filterargs );
    }
    else
    {
        liqapp_log("searching in flat '%s', %i",c->name,filterargs.resultshown);
        liqcell_handlerrun( c , "filter", &filterargs );
    }

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
		
        liqcell *searchinprogress = liqcell_child_lookup(body,"searchinprogress");
        
		liqcell *c = liqcell_getlinkchild_visual(body);
		while(c)
		{
			liqcell_filter_run(c,searchterm);
			c=liqcell_getlinknext_visual(c);
		}

        liqcell_setvisible(searchinprogress,0);
            
        if(liqcell_child_countvisible(body)==0)
        {
            liqcell_setcaption_printf(searchinprogress,"No results found");
            liqcell_propsets(  searchinprogress, "backcolor",   "xrgb(40,0,0)" );
        }
        else
        {
            liqcell_setcaption_printf(searchinprogress,"Search results:",liqcell_child_countvisible(body) );
            liqcell_propsets(  searchinprogress, "backcolor",   "xrgb(0,40,0)" );
        }
        
        if(!searchterm || !*searchterm)
            liqcell_setvisible(searchinprogress,0);
        else
            liqcell_setvisible(searchinprogress,1);
            
        
		//liqcell_setrect(body,   0,40,playground->w,playground->h-40);
		liqcell_setrect(body,   0,0,playground->w,playground->h);
		liqcell_child_arrange_easytile( body );
		//liqcell_child_arrange_makegrid_fly(body,3,3);
		
        liqcell_child_arrange_easytile(searchinprogress);
        
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
	
	static int playground_item_mouse(liqcell *self, liqcellmouseeventargs *args, liqcell *playground)
	{
		//args->newdialogtoopen = liqcell_getcontent( self );
        

		liqcell_adjustpos((self),args->mdx,args->mdy);

		int liqcell_child_arrange_nooverlap(liqcell *self,liqcell *currentselection);
		int liqcell_child_arrange_gapfill(liqcell *self,liqcell *currentselection);

		liqcell_child_arrange_nooverlap( liqcell_getlinkparent(self), self );

    
		return 1;
	}	
	static int playground_item_click(liqcell *self, liqcellclickeventargs *args, liqcell *playground)
	{
		args->newdialogtoopen = liqcell_getcontent( self );

		return 1;
	}
    
    static int playground_item_dirty(liqcell *self, liqcelleventargs *args, liqcell *playground)
	{
		//args->newdialogtoopen = liqcell_getcontent( self );

		liqcell_setdirty(playground,1);
		return 1;
	}

    
    
	static int playground_refresh(liqcell *self, liqcelleventargs *args, void *context)
	{
	
		return 1;
	}
	
	
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################	
	

	
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
				//if(dif>5)dif=5;
				liqcell_setpos( search, liqcell_getx(search), liqcell_gety(search) - dif );
				liqcell_setdirty(playground,1);
			}
		}
    /*    
        if( liqcell_propgeti(self,"arrangecomplete",0) == 0 )
        {
                liqcell *body = liqcell_child_lookup(self,"body");
            	liqcell_setrect(body,   0,40,self->w,self->h-40);
                
                liqcell_setdirty(body,0);
                
                if( liqcell_child_arrange_makegrid(body,3,3) )
                {
					//liqcell_propseti(self,"arrangecomplete",1);
                }
                if( ! liqcell_getdirty(body) )
                {
					// the complete advance occured without a change :)
					//liqcell_propseti(self,"arrangecomplete",1);
                }
		}
    */	
		return 0;
	}


	static int playground_resize(liqcell *self, liqcelleventargs *args, liqcell *playground)
	{
		liqcell *search = liqcell_child_lookup(playground,"search");		
		liqcell_setrect(search, playground->w*0.2 ,playground->h-40,   playground->w*0.6, 60);
		//liqcell_setrect(search, self->w*0.2 ,0,   self->w*0.4, 40);
		
		
		liqcell *body = liqcell_child_lookup(playground,"body");
		//liqcell_setrect(body,   0,40,self->w,self->h-40);
        liqcell_setrect(body,   0,0,playground->w,playground->h);
		//liqcell_setsize(body,   self->w,self->h);
        
		liqcell_child_arrange_easytile( body );
		//liqcell_child_arrange_makegrid_fly(body,3,3);
		
		return 1;
	}
    
    
    
    
    
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
	

liqcell *playground_create()
{
	liqcell *self = liqcell_quickcreatewidget("playground","form", 800,480);

	if(self)
	{



	/*	//############################# title:label
		liqcell *title = liqcell_quickcreatevis("title", "label", 0,0, 400, 40);
		liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(title, "liqbase playground" );
		liqcell_propsets(  title, "textcolor", "rgb(255,0,0)" );
		liqcell_propsets(  title, "backcolor", "rgb(0,0,60)" );
		liqcell_propseti(  title, "textalign", 0 );
		liqcell_child_append(  self, title);
    */ 
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



        liqcell_propseti(body,"liqcell_child_arrange_nooverlap_minimumw",80);
        liqcell_propseti(body,"liqcell_child_arrange_nooverlap_minimumh",48);



		//############################# searchinprogress:label
		liqcell *searchinprogress = liqcell_quickcreatevis("searchinprogress", NULL, 600, 440, 200, 60);
		liqcell_setfont(	searchinprogress, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (35), 0) );
		liqcell_setcaption(searchinprogress, "searching:" );
		liqcell_propsets(  searchinprogress, "textcolor",   "rgb(0,255,0)" );
		liqcell_propsets(  searchinprogress, "backcolor",   "xrgb(0,40,0)" );
		//liqcell_propsets(  searchinprogress, "bordercolor", "rgb(0,150,0)" );
		liqcell_propseti(  searchinprogress, "textalign",   2 );
		liqcell_propseti(  searchinprogress, "textaligny",  2 );
		liqcell_child_append(  body, searchinprogress);
        liqcell_setvisible(searchinprogress,0);
 
 
 
 
 

 
 
		liqcell *addsearchkind(char *title,char *imgfilename,void *clickhandler)
		{
            
            
            
            
			
			//liqcell *item = newx;
			
			liqcell *item = liqcell_quickcreatevis(title,"item",0,0,100,100);
            
            liqcell_setimage(  item ,  liqimage_cache_getfile( imgfilename,0,0,1) );
			liqcell_propseti(  item,    "lockaspect",1);
			
			liqcell_handleradd_withcontext(item,    "click",   clickhandler ,self );
			liqcell_child_append( searchinprogress, item );
			return item;
			
		}
        
        addsearchkind( "google","/usr/share/liqbase/media/searchimg/google.jpg"   , playground_send_google );
        addsearchkind( "console","/usr/share/liqbase/media/searchimg/console.jpg" , playground_send_console );
        
        
 


        liqapp_log("liqtwit: looking up twituser credentials");
        char *twitname = liqapp_pref_getvalue("twitname");
        char *twitpass = liqapp_pref_getvalue("twitpass");
        if(twitname && *twitname  && twitpass && *twitpass)
        {
            // ok
            addsearchkind( "twitter","/usr/share/liqbase/media/searchimg/twitter.png" , playground_send_tweet );
        } 

        liqcell_child_arrange_easytile(searchinprogress);

		//liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_insert( self, body );
		

		
		
		liqcell *search = liqcell_quickcreatevis("search","textbox",self->w*0.2 ,self->h-40,   self->w*0.6, 60);
		liqcell_setfont(   search,  liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
		liqcell_setcaption(search, "" );
		liqcell_propsets(  search, "textcolor",   "rgb(255,255,255)" );
		liqcell_propsets(  search, "backcolor",   "xrgb(0,40,0)" );
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


        char fnbuf[FILENAME_MAX];  snprintf(fnbuf,sizeof(fnbuf),"%s/background.png",app.userdatapath);
        
        if(liqapp_fileexists(fnbuf))
        {
            liqcell_setimage(  self ,  liqimage_cache_getfile( fnbuf,0,0,0) );
        }
        else
        {
            liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/media/liqbase_back2.jpg",0,0,0) );
        }
        liqcell_propseti(  self ,  "lockaspect",0 );
		playground_resize(self,NULL,self);




        if(!liqbase_playground_root)
            liqbase_playground_root = self;
    
    
    
    
    
    
    
    
        char *listall = liqapp_pref_getvalue_def("liqbase_playground_contents",    NULL);
        if(!listall)
        {
    
    
            addone(self,body, "desktopmanage");
            
            
            
            //addone(self,body, "liqrecentsketches");
            // addone(self,body, "liqrecentphotos");
            addone(self,body, "liqcalendar");
            if(liqapp_hardware_product_ispowerful_get())
            {
                addone(self,body, "liqaccelview_alternative");
                addone(self,body, "liqflow");
            }
            
            //addone(self,body, "floatmap");
            
            addone(self,body, "onedotzero");
           // addone(self,body, "liqpostcard");
            addone(self,body, "liqtorch");
            addone(self,body, "liqsketchedit");
        }
        else
        {
            liqbase_playground_refresh_desktop_contents();
        }
        
        
		liqcell_child_arrange_easytile( body );


	}

    

	return self;
}









/*



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
 */




