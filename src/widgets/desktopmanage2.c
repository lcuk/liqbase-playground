// this file is part of liqbase by Gary Birkett
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_dllcache.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqcell_arrange.h>



#include <liqbase/liqcell_historystore.h>
//int liqcell_historystore_historythumb_getfilename(liqcell *self,char *buffer,int buffersize);



    int liqbase_playground_check_if_class_shown(char *classname);
    int liqbase_playground_refresh_desktop_contents();
    
    
    

int desktopmanage2_updateticks(liqcell *desktopmanage2)
{
    liqapp_log("desktopmanage2: updating ticks");


	liqcell *list1 = liqcell_child_lookup( desktopmanage2,"list1");
		//############################# backplane:picturebox
		liqcell *backplane =liqcell_child_lookup( list1,"backplane");
			//############################# listitem:picturebox
			liqcell *listitem = liqcell_getlinkchild_visual(backplane);
			while(listitem)
			{
				//if(liqcell_getflagvisual(listitem))
				{
                   char *key=listitem->name;
                    liqcell *listitemicon = liqcell_child_lookup( listitem,"listitemtick");
 					char *cap = liqcell_getcaption(listitemicon);
                    
                    
                    if( !liqbase_playground_check_if_class_shown(key) )
                    {

                        liqcell_setcaption(listitemicon,"N");
                        liqcell_propsets(  listitemicon, "textcolor", "rgb(255,0,0)" );
                    }
                    else
                    {
                        //liqapp_log("desktopmanage2: tick yes '%s'",key);
                        liqcell_setcaption(listitemicon,"Y");
                        liqcell_propsets(  listitemicon, "textcolor", "rgb(0,255,0)" );
                    }

                }
                listitem=liqcell_getlinknext_visual(listitem);
            }
    liqapp_log("desktopmanage2: updated ticks");
}



/**   
 * buttonaccept was clicked
 */   
static int buttonaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *desktopmanage2)
{
	// save the selections and make sure the main playground knows :)
	//args->newdialogtoopen = desktopmanage2item_create();
	
    char resultset[2048]={0};
    
    liqapp_log("desktopmanage2: accepting");
    
	
	// 20090421_191821 lcuk : enumerate the listitems and store the results
	// 20090421_193449 lcuk : not finished yet
	liqcell *base = desktopmanage2;//liqcell_getbasewidget(self);
	
	liqcell *list1 = liqcell_child_lookup( base,"list1");
		//############################# backplane:picturebox
		liqcell *backplane =liqcell_child_lookup( list1,"backplane");
			//############################# listitem:picturebox
			liqcell *listitem = liqcell_getlinkchild(backplane);
			while(listitem)
			{
				if(liqcell_getflagvisual(listitem))
				{
                    char *key=listitem->name;
                    liqcell *listitemicon = liqcell_child_lookup( listitem,"listitemtick");
					char *cap = liqcell_getcaption(listitemicon);
					
					if( (strcasecmp(cap,"Y")==0) )
					{
						// mark this as wanted next time
                        if(strlen(resultset)+1+strlen(key) < sizeof(resultset))
                        {
                            if(strlen(resultset)>0) strcat(resultset,",");
                            strcat(resultset,key);
                        }
					}
					else
					{
						// mark this as explicitly removed
						
					}
				}
				listitem=liqcell_getlinknext(listitem);
			}
    liqapp_log("desktopmanage2: saving '%s'",resultset);
	liqapp_pref_setvalue( "liqbase_playground_contents", resultset );
	liqapp_prefs_save();
    
    

    liqbase_playground_refresh_desktop_contents();



	liqcell_propseti(desktopmanage2,"dialog_running",0);
	
	return 1;
}



/**   
 * listitemicon was clicked
 */   
static int listitemicon_click(liqcell *self,liqcellclickeventargs *args, void *context)
{
	liqcell *c = liqcell_quickcreatevis(liqcell_getcaption(self),liqcell_getcaption(self),0,0,-1,-1);
	if(c)
	{
		if(liqcell_getvisible(c))
		{
			liqcell_easyrun(c);
		}
		liqcell_release(c);
		
		liqcell_setimage(self,NULL);
	}
	return 1;
}

/**   
 * listitemtick was clicked
 */   
static int listitemtick_click(liqcell *self,liqcellclickeventargs *args, void *context)
{
	// code required
	// 20090421_191821 lcuk : switch between yes and no, eventually make into icons
	
	char *cap = liqcell_getcaption(self);
	
	if( (strcasecmp(cap,"Y")==0) )
	{
		liqcell_setcaption(self,"N");
		liqcell_propsets(  self, "textcolor", "rgb(255,0,0)" );
	}
	else
	{
		liqcell_setcaption(self,"Y");
		liqcell_propsets(  self, "textcolor", "rgb(0,255,0)" );
	}

	return 1;
}







	static int desktopmanage2_filter(liqcell *self, liqcellfiltereventargs *args, liqcell *desktopmanage2)
	{
		// using the filter provided (which might be blank)
		
        //liqapp_log("deep filter");
        
					int islike = 1;//liqcell_propgeti(  self, "filterlike", 1 );
		
		char *searchterm = NULL;
		
		if(args) args->resultoutof=0;
		if(args) args->resultshown=0;
		if(args) searchterm = args->searchterm;
        
        //liqapp_log("deep filter2");
		
		// examine each tag and if matches the search show it, otherwise dont..
        liqcell *list1 = liqcell_child_lookup( desktopmanage2,"list1");
            //############################# backplane:picturebox
            liqcell *backplane =liqcell_child_lookup( list1,"backplane");
       
        //liqapp_log("deep filter3 %i",backplane==NULL);
		
		liqcell *c = liqcell_getlinkchild_visual(backplane);
		while(c)
		{
			if(searchterm && *searchterm)
			{

				//struct pagefilename pfn;
				//pagefilename_breakapart(&pfn,c->name);
				char *key = c->name;
              
                
               // liqapp_log("checking '%s' in '%s'",searchterm,key);

				int isok = (key!=NULL) && (*key |= 0);
				if(isok)
				{
					if(islike)
					{
						// anywhere in string
						isok = ( stristr(key,searchterm) != NULL );
					}
					else
					{
						// only from the start
						isok = ( c->name == stristr(key,searchterm) );
					}
				}
				
				if(!isok)
				{
					// see if we can show it anyway
					//if(liqcell_getselected(c)) isok=1;
                    liqcell *listitemicon = liqcell_child_lookup( c,"listitemicon");
 					char *cap = liqcell_getcaption(listitemicon);
                    if( (strcasecmp(cap,"Y")==0) ) isok=1;

				}

				if( isok ) // strstr(c->name,searchterm) )
				{
					// found a match!
					liqcell_setvisible(c,1);
					if(args) args->resultshown++;
				}
				else
				{
					// no match :(
					liqcell_setvisible(c,0);
				}
				if(args) args->resultoutof++;
			}
			else
			{
				// nothing to search for, show it
				liqcell_setvisible(c,1);
				if(args) args->resultoutof++;
				if(args) args->resultshown++;
			}

			c=liqcell_getlinknext_visual(c);
		}
		liqcell_setrect(backplane,   0,0,self->w,self->h);
		//liqcell_child_arrange_autoflow( backplane );
        liqcell_child_arrange_makegrid( backplane,4,4 );
        backplane->h+=40;
		return 1;
	}

/**	
 * desktopmanage2 dialog_open - the user zoomed into the dialog
 */	
static int desktopmanage2_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    desktopmanage2_updateticks(self);
	return 0;
}
/**	
 * desktopmanage2 dialog_close - the dialog was closed
 */	
static int desktopmanage2_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    desktopmanage2_updateticks(self);
	return 0;
}


/**	
 * desktopmanage2 shown - first time on screen
 */	
static int desktopmanage2_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    desktopmanage2_updateticks(self);
	return 0;
}


/**   
 * create a new desktopmanage2 widget
 */   
liqcell *desktopmanage2_create()
{
	

	liqcell *self = liqcell_quickcreatewidget("desktopmanage2", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'desktopmanage2'"); return NULL;  } 
/*	
	//############################# buttonback:commandbutton
	liqcell *buttonback = liqcell_quickcreatevis("buttonback", "commandbutton", 0, 480-56, 56, 56);
	liqcell_setfont(   buttonback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(buttonback, "Back" );
	//liqcell_propsets(  buttonback, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  buttonback, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  buttonback, "textalign", 2 );
	liqcell_child_append(  self, buttonback);
 */	

/*	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 56, 0, 56, 56);
	liqcell_setfont(   icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(icon, "icon" );
	liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);
 */

/*
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 120, 8, 396, 40);
	liqcell_setfont(   title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Available items" );
	//liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
 

 */
	/*	liqcell *tbar = uitoolcol_create("tools","tools",
				uitoolitem_create( "reset",     "reset",         "../media/quickicons/stock_refresh.png",    toolitem_click),
				uitoolitem_create( "delete", "delete",     "../media/quickicons/gtk-remove.png",           toolitem_click),
				uitoolitem_create( "add",    "add",        "../media/quickicons/add.png",              toolitem_click),
				uitoolitem_create( "edit", "edit",     "../media/quickicons/package_graphics.png",           toolitem_click),
				//uitoolitem_create( "close",  "close",      "../media/quickicons/gtk-close.png",    toolitem_click),
				uitoolitem_create( "back",   "back",       "../media/quickicons/back.png",              toolitem_click),
				NULL);

		liqcell_child_append( self, tbar );
	*/
	

	//############################# list1:picturebox
	liqcell *list1 = liqcell_quickcreatevis("list1", "picturebox", 0,0, 800, 480);
	//liqcell_setfont(	list1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  list1, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  list1, "backcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  list1, "bordercolor", "rgb(200,100,100)" );
	
	
		//############################# backplane:picturebox
		liqcell *backplane = liqcell_quickcreatevis("backplane", "picturebox", 0, 0, list1->w, list1->h);
		//liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_propsets(  backplane, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  backplane, "backcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  backplane, "bordercolor", "rgb(200,100,100)" );			
	
			// now, we fill the list
			dllcacheitem *dllcache = NULL;
			int           dllcache_used = 0;
			
			dllcache = dllcache_getbase();
			if(!dllcache)
			{
				liqapp_log("could not init dllcache");
				return NULL;
			}
			
			
			dllcache_used = dllcache_getused();
			
			int idx=0;
			for(idx=0;idx<dllcache_used;idx++)
			{
				dllcacheitem * dllcacheitem = &dllcache[ idx ];
                
                
                if( strcasecmp(dllcacheitem->key,"liqtimer")==0) continue;
                if( strcasecmp(dllcacheitem->key,"textbox")==0) continue;
                if( strcasecmp(dllcacheitem->key,"desktopmanage")==0) continue;
                if( strcasecmp(dllcacheitem->key,"liqbase-playground")==0) continue;
               

				//############################# listitem:picturebox
				liqcell *listitem = liqcell_quickcreatevis(dllcacheitem->key, NULL, 0, 0, list1->w, 100);

				//liqcell_setfont(	listitem, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				//liqcell_propsets(  listitem, "textcolor", "rgb(0,0,0)" );
                

				//liqcell_propsets(  listitem, "bordercolor", "rgb(200,100,100)" );
					//############################# listitemtick:checkbox
					liqcell *listitemtick = liqcell_quickcreatevis("listitemtick", "checkbox", 0, 20, 60, 60);
					liqcell_setfont(	listitemtick, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (34), 0) );
					
					// set to YN depending on if this is directly on the playground
                    
                    
				//	liqcell_setcaption(listitemtick, "Y" );
				//	liqcell_propsets(  listitemtick, "textcolor", "rgb(0,255,0)" );
                    
					liqcell_setcaption(listitemtick, "N" );
					liqcell_propsets(  listitemtick, "textcolor", "rgb(255,0,0)" );
                    
					liqcell_propsets(  listitemtick, "backcolor", "rgb(40,40,40)" );
					liqcell_propseti(  listitemtick, "textalign",  2 );
					liqcell_propseti(  listitemtick, "textaligny", 2 );
					liqcell_handleradd(listitemtick, "click", listitemtick_click );
					liqcell_child_append(  listitem, listitemtick);
					
					
					//############################# listitemicon:picturebox
					char buf[FILENAME_MAX];
					liqcell_historystore_historythumb_getfilename(buf,sizeof(buf), dllcacheitem->key);

					liqcell *listitemicon = liqcell_quickcreatevis("listitemicon", "icon", 60, 5, 130, 90);
					liqcell_setcaption(listitemicon, dllcacheitem->key );
					liqcell_propsets(  listitemicon, "imagefilename", buf );
					liqcell_propseti(  listitemicon, "aspectlock", 1 );
					//liqcell_setfont(	listitemicon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
					//liqcell_propsets(  listitemicon, "textcolor", "rgb(0,0,0)" );
					liqcell_propsets(  listitemicon, "backcolor", "rgb(100,150,200)" );
					liqcell_propsets(  listitemicon, "bordercolor", "rgb(200,100,100)" );
					liqcell_handleradd_withcontext(listitemicon, "click", listitemicon_click ,self);
					liqcell_child_append(  listitem, listitemicon);
					
					//############################# listitemname:label
					liqcell *listitemname = liqcell_quickcreatevis("listitemname", "label", 200, 0, 400, 60);
					liqcell_setfont(	listitemname, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (35), 0) );
					liqcell_setcaption(listitemname, dllcacheitem->key );
					liqcell_propsets(  listitemname, "textcolor", "rgb(255,255,100)" );
					//liqcell_propsets(  listitemname, "backcolor", "rgb(0,64,0)" );
					//liqcell_handleradd(listitemname, "click", listitemname_click );
					liqcell_propseti(  listitemname, "textalign", 0 );
					liqcell_child_append(  listitem, listitemname);
				// 20090503_232751 lcuk : move this here
				//liqcell_handleradd(listitem, "click", listitemname_click );	
				// 20090503_233423 lcuk : moved it back again
				
					//############################# listitemfilename:label
					liqcell *listitemfilename = liqcell_quickcreatevis("listitemfilename", "label", 210, 60, 590, 40);
					liqcell_setfont(	listitemfilename, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
					liqcell_setcaption(listitemfilename, dllcacheitem->filename );
					//liqcell_propsets(  listitemfilename, "textcolor", "rgb(255,255,255)" );
					//liqcell_propsets(  listitemfilename, "backcolor", "rgb(0,64,0)" );
					liqcell_propseti(  listitemfilename, "textalign", 0 );
					liqcell_child_append(  listitem, listitemfilename);
										
					//############################# listitemversion:label
					liqcell *listitemversion = liqcell_quickcreatevis("listitemversion", "label", 600, 0,200,30);
					liqcell_setfont(	listitemversion, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (18), 0) );
					liqcell_setcaption(listitemversion, "1.0" );
					//liqcell_propsets(  listitemversion, "textcolor", "rgb(255,255,255)" );
					//liqcell_propsets(  listitemversion, "backcolor", "rgb(0,64,0)" );
					liqcell_propseti(  listitemversion, "textalign", 1 );
					liqcell_child_append(  listitem, listitemversion);

					

					

					
					
				liqcell_child_insertsorted(  backplane, listitem);
			}
			//liqcell_child_arrange_easycol(  backplane );
            
            
        /*    
            // now add the backcolorization in order
            {
                liqcell *c=liqcell_getlinkchild_visual(backplane);
                int idx=0;
                while(c)
                {
                    if(idx & 1)
                    {
                        liqcell_propsets(  c, "backcolor", "rgb(0,0,0)" );
                    }
                    else
                    {
                        liqcell_propsets(  c, "backcolor", "rgb(30,0,30)" );
                    }
                    c=liqcell_getlinknext_visual(c);
                    idx++;
                }
            }
        */    
            

			//liqcell_child_arrange_autoflow( backplane );
			liqcell_child_arrange_makegrid( backplane,4,4 );
            backplane->h+=40;
			
			
			liqcell_handleradd(backplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );
			liqcell_child_append(  list1, backplane);
		
		liqcell_child_append(  self, list1);


	//############################# buttonaccept:commandbutton
	liqcell *buttonaccept = liqcell_quickcreatevis("buttonaccept", "commandbutton", 574, 418, 226, 62);
	liqcell_setfont(   buttonaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(buttonaccept, "Update" );
	liqcell_propsets(  buttonaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  buttonaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  buttonaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  buttonaccept, "textalign", 2 );
    liqcell_propseti(  buttonaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(buttonaccept, "click", buttonaccept_click,self );
	liqcell_child_append(  self, buttonaccept);
	
//	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );

	liqcell_handleradd_withcontext(self, "dialog_open", desktopmanage2_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", desktopmanage2_dialog_close ,self);
    liqcell_handleradd_withcontext(self, "shown", desktopmanage2_dialog_close ,self);

	liqcell_handleradd_withcontext(self,    "filter",   desktopmanage2_filter,self);
	return self;
}

