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
    
    
    

int desktopmanage3_updateticks(liqcell *desktopmanage3)
{
    liqapp_log("desktopmanage3: updating ticks");


	liqcell *list1 = liqcell_child_lookup( desktopmanage3,"list1");
		//############################# backplane:picturebox
		liqcell *backplane =liqcell_child_lookup( list1,"backplane");
			//############################# listitem:picturebox
			liqcell *listitem = liqcell_getlinkchild_visual(backplane);
			while(listitem)
			{
				//if(liqcell_getflagvisual(listitem))
				{
                    char *key=listitem->name;
                    //liqcell *listitemicon = liqcell_child_lookup( listitem,"listitemtick");
 					//char *cap = liqcell_getcaption(listitemicon);
                    
                    
                    if( !liqbase_playground_check_if_class_shown(key) )
                    {
                        liqcell_setselected(listitem,1);
                    }
                    else
                    {
                        liqcell_setselected(listitem,0);
                    }

                }
                listitem=liqcell_getlinknext_visual(listitem);
            }
    liqapp_log("desktopmanage3: updated ticks");
}



/**   
 * buttonaccept was clicked
 */   
static int buttonaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *desktopmanage3)
{
	// save the selections and make sure the main playground knows :)
	//args->newdialogtoopen = desktopmanage3item_create();
	
    char resultset[2048]={0};
    
    liqapp_log("desktopmanage3: accepting");
    
	
	// 20090421_191821 lcuk : enumerate the listitems and store the results
	// 20090421_193449 lcuk : not finished yet
	liqcell *base = desktopmanage3;//liqcell_getbasewidget(self);
	
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
                    //liqcell *listitemicon = liqcell_child_lookup( listitem,"listitemtick");
					//char *cap = liqcell_getcaption(listitemicon);
					
					if( liqcell_getselected(listitem) ) // (strcasecmp(cap,"Y")==0) )
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
    liqapp_log("desktopmanage3: saving '%s'",resultset);
	liqapp_pref_setvalue( "liqbase_playground_contents", resultset );
	liqapp_prefs_save();
    
    

    liqbase_playground_refresh_desktop_contents();



	liqcell_propseti(desktopmanage3,"dialog_running",0);
	
	return 1;
}




/**   
 * listitem was clicked
 */   
static int listitem_click(liqcell *self,liqcellclickeventargs *args, void *context)
{
	// code required
	// 20090421_191821 lcuk : switch between yes and no, eventually make into icons
	
    
    if(liqcell_getselected(self))
    {
        liqcell_setselected(self,0);
    }
    else
    {
        liqcell_setselected(self,1);
    }
	return 1;
}







	static int desktopmanage3_filter(liqcell *self, liqcellfiltereventargs *args, liqcell *desktopmanage3)
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
        liqcell *list1 = liqcell_child_lookup( desktopmanage3,"list1");
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
						isok = ( key == stristr(key,searchterm) );
					}
				}
				
				if(!isok)
				{
					// see if we can show it anyway
					//if(liqcell_getselected(c)) isok=1;
                    //liqcell *listitemicon = liqcell_child_lookup( c,"listitemicon");
 					//char *cap = liqcell_getcaption(listitemicon);
                    //if( (strcasecmp(cap,"Y")==0) ) isok=1;
                    if(liqcell_getselected(c)) isok=1;

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
 * desktopmanage3 dialog_open - the user zoomed into the dialog
 */	
static int desktopmanage3_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    desktopmanage3_updateticks(self);
	return 0;
}
/**	
 * desktopmanage3 dialog_close - the dialog was closed
 */	
static int desktopmanage3_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    desktopmanage3_updateticks(self);
	return 0;
}


/**	
 * desktopmanage3 shown - first time on screen
 */	
static int desktopmanage3_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
    desktopmanage3_updateticks(self);
	return 0;
}


/**   
 * create a new desktopmanage3 widget
 */   
liqcell *desktopmanage3_create()
{
	

	liqcell *self = liqcell_quickcreatewidget("desktopmanage3", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'desktopmanage3'"); return NULL;  } 


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
                if( strcasecmp(dllcacheitem->key,"desktopmanage2")==0) continue;
                if( strcasecmp(dllcacheitem->key,"desktopmanage3")==0) continue;
                if( strcasecmp(dllcacheitem->key,"liqbase-playground")==0) continue;
               

				//############################# listitem:picturebox
				liqcell *listitem = liqcell_quickcreatevis(dllcacheitem->key, NULL, 0, 0, list1->w, 100);
                
					//char buf[FILENAME_MAX];
					//liqcell_historystore_historythumb_getfilename(buf,sizeof(buf), dllcacheitem->key);
					//liqcell_propsets(  listitem, "imagefilename", buf );
					//liqcell_propseti(  listitem, "aspectlock", 1 );
                    

					

					liqcell *xrun = liqcell_quickcreatevis(dllcacheitem->key, dllcacheitem->key, 0,0,-1,-1);
					liqcell_setcontent(  listitem, xrun );
					liqcell_propseti(  listitem, "aspectlock", 1 );

                    
                    liqcell_handleradd_withcontext(listitem, "click", listitem_click ,self);
                
                
				

					
					
				liqcell_child_insertsorted(  backplane, listitem);
			}
           

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

	liqcell_handleradd_withcontext(self, "dialog_open", desktopmanage3_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", desktopmanage3_dialog_close ,self);
    liqcell_handleradd_withcontext(self, "shown", desktopmanage3_dialog_close ,self);

	liqcell_handleradd_withcontext(self,    "filter",   desktopmanage3_filter,self);
	return self;
}

