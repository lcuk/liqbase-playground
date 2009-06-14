// this file is part of liqbase by Gary Birkett
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_dllcache.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqcell_arrange.h>



	



/**   
 * buttonaccept was clicked
 */   
static int buttonaccept_click(liqcell *self,liqcellclickeventargs *args, void *context)
{
	// code required
	//args->newdialogtoopen = desktopmanageitem_create();
	
	
	// 20090421_191821 lcuk : enumerate the listitems and store the results
	// 20090421_193449 lcuk : not finished yet
	liqcell *base = liqcell_getbasewidget(self);
	
	liqcell *list1 = liqcell_child_lookup( base,"list1");
		//############################# listback:picturebox
		liqcell *listback =liqcell_child_lookup( list1,"listback");
			//############################# listitem:picturebox
			liqcell *listitem = liqcell_getlinkchild(listback);
			while(listitem)
			{
				if(liqcell_getvisible(listitem))
				{
					
					char *cap = liqcell_getcaption(self);
					
					if( (strcasecmp(cap,"Y")==0) )
					{
						// mark this as wanted next time
					}
					else
					{
						// mark this as explicitly removed
						
					}
				}
				listitem=liqcell_getlinknext(listitem);
			}

	
	return 1;
}


/**   
 * listitemname was clicked
 */   
static int listitemname_click(liqcell *self,liqcellclickeventargs *args, void *context)
{
	// code required
	//args->newdialogtoopen = desktopmanageitem_create();
	
	liqcell *c = liqcell_quickcreatevis("c",liqcell_getcaption(self),0,0,-1,-1);
	if(c)
	{
		if(liqcell_getvisible(c))
		{
			liqcell_easyrun(c);
		}
		liqcell_release(c);
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

void food(char *name,char *cooker,char *temp,char *duration,char *units,char *notes)
{
	//
}

/**   
 * create a new desktopmanage widget
 */   
liqcell *desktopmanage_create()
{
	
	
	food("chicken (roast)  ", "oven",      "200ish","2","hours",   "depending on weight");
	food("roast potatoes   ", "oven",      "200ish","50","minutes","");
	food("parsnips         ", "oven",      "200ish","50","minutes","");
	food("carrots          ", "boiled",    "high",  "10","minutes","boiling water");
	food("peas             ", "microwave", "high",  "3", "minutes","");
	food("gravy            ", "kettle",    "high",  "2", "minutes","");
	
	
	liqcell *self = liqcell_quickcreatewidget("desktopmanage", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'desktopmanage'"); return NULL;  } 
	
	//############################# buttonback:commandbutton
	liqcell *buttonback = liqcell_quickcreatevis("buttonback", "commandbutton", 0, 480-56, 56, 56);
	liqcell_setfont(   buttonback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(buttonback, "Back" );
	//liqcell_propsets(  buttonback, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  buttonback, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  buttonback, "textalign", 2 );
	liqcell_child_append(  self, buttonback);
	
	//############################# buttonaccept:commandbutton
/*	liqcell *buttonaccept = liqcell_quickcreatevis("buttonaccept", "commandbutton", 0, 480-56-56, 56, 56);
	liqcell_setfont(   buttonaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(buttonaccept, "Accept" );
	//liqcell_propsets(  buttonaccept, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  buttonaccept, "textalign", 2 );
	liqcell_handleradd(buttonaccept, "click", buttonaccept_click );
	liqcell_child_append(  self, buttonaccept);
	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 56, 0, 56, 56);
	liqcell_setfont(   icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(icon, "icon" );
	liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);
 */	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 120, 8, 396, 40);
	liqcell_setfont(   title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Desktop manager" );
	//liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	
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
	liqcell *list1 = liqcell_quickcreatevis("list1", "picturebox", 56, 56, 800-56, 480-56);
	//liqcell_setfont(	list1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  list1, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  list1, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  list1, "bordercolor", "rgb(200,100,100)" );
	
	
		//############################# list1:picturebox
		liqcell *listback = liqcell_quickcreatevis("listback", "picturebox", 0, 0, list1->w, list1->h);
		//liqcell_setfont(	listback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_propsets(  listback, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  listback, "backcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  listback, "bordercolor", "rgb(200,100,100)" );			
	
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

				//############################# listitem:picturebox
				liqcell *listitem = liqcell_quickcreatevis(dllcacheitem->key, "listitem", 0, 0, list1->w, 100);

				//liqcell_setfont(	listitem, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				//liqcell_propsets(  listitem, "textcolor", "rgb(0,0,0)" );
				//liqcell_propsets(  listitem, "backcolor", "rgb(0,0,0)" );
				//liqcell_propsets(  listitem, "bordercolor", "rgb(200,100,100)" );
					//############################# listitemtick:checkbox
					liqcell *listitemtick = liqcell_quickcreatevis("listitemtick", "checkbox", 120, 5, 40, 40);
					liqcell_setfont(	listitemtick, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
					liqcell_setcaption(listitemtick, "Y" );
					liqcell_propsets(  listitemtick, "textcolor", "rgb(0,255,0)" );
					//liqcell_propsets(  listitemtick, "backcolor", "rgb(235,233,237)" );
					liqcell_propseti(  listitemtick, "textalign", 2 );
					liqcell_handleradd(listitemtick, "click", listitemtick_click );
					liqcell_child_append(  listitem, listitemtick);
					
					
					//############################# listitemicon:picturebox
					liqcell *listitemicon = liqcell_quickcreatevis("listitemicon", "icon", 10, 5, 150, 100);
					//liqcell_setfont(	listitemicon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
					//liqcell_propsets(  listitemicon, "textcolor", "rgb(0,0,0)" );
					//liqcell_propsets(  listitemicon, "backcolor", "rgb(192,255,192)" );
					liqcell_propsets(  listitemicon, "bordercolor", "rgb(200,100,100)" );
					liqcell_child_append(  listitem, listitemicon);
					
					//############################# listitemname:label
					liqcell *listitemname = liqcell_quickcreatevis("listitemname", "label", 170, 5, 630, 40);
					liqcell_setfont(	listitemname, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (30), 0) );
					liqcell_setcaption(listitemname, dllcacheitem->key );
					liqcell_propsets(  listitemname, "textcolor", "rgb(255,255,100)" );
					//liqcell_propsets(  listitemname, "backcolor", "rgb(0,64,0)" );
					liqcell_handleradd(listitemname, "click", listitemname_click );
					liqcell_propseti(  listitemname, "textalign", 0 );
					liqcell_child_append(  listitem, listitemname);
				// 20090503_232751 lcuk : move this here
				//liqcell_handleradd(listitem, "click", listitemname_click );	
				// 20090503_233423 lcuk : moved it back again
					//############################# listitemfilename:label
					liqcell *listitemfilename = liqcell_quickcreatevis("listitemfilename", "label", 180, 40, 620, 30);
					liqcell_setfont(	listitemfilename, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
					liqcell_setcaption(listitemfilename, dllcacheitem->filename );
					//liqcell_propsets(  listitemfilename, "textcolor", "rgb(255,255,255)" );
					//liqcell_propsets(  listitemfilename, "backcolor", "rgb(0,64,0)" );
					liqcell_propseti(  listitemfilename, "textalign", 0 );
					liqcell_child_append(  listitem, listitemfilename);
										
					//############################# listitemversion:label
					liqcell *listitemversion = liqcell_quickcreatevis("listitemversion", "label", 190, 80,610,30);
					liqcell_setfont(	listitemversion, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (18), 0) );
					liqcell_setcaption(listitemversion, "1.0" );
					//liqcell_propsets(  listitemversion, "textcolor", "rgb(255,255,255)" );
					//liqcell_propsets(  listitemversion, "backcolor", "rgb(0,64,0)" );
					//liqcell_propseti(  listitemversion, "textalign", 1 );
					liqcell_child_append(  listitem, listitemversion);

					

					

					
					
				liqcell_child_insertsorted(  listback, listitem);
			}
			//liqcell_child_arrange_easycol(  listback );
			
			liqcell_child_arrange_autoflow( listback );
			
			
			liqcell_handleradd(listback,    "mouse",   liqcell_easyhandler_kinetic_mouse );
			liqcell_child_append(  list1, listback);
		
		liqcell_child_append(  self, list1);
	
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	return self;
}

