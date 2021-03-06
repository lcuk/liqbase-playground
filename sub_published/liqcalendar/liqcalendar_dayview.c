// this file is part of liqbase by Gary Birkett
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>


#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqcell_arrange.h>

//#include <curl/curl.h>






/**	
 * liqcalendar_dayview shown event
 */ 
static int liqcalendar_dayview_dialog_open(liqcell *self,liqcelleventargs *args, void *context)
{
	//
	
	liqapp_log("dialog open 1");
	
	liqcell *editor = liqcell_child_lookup( self,"editor");
	if(!editor)return 0;


	liqcell *titlebox = liqcell_child_lookup( self,"titlebox");
	if(!titlebox)return 0;
	
	
	//########################################################################
	//########################################################################
	//########################################################################
	//########################################################################
	//########################################################################

	liqcell *daybar = liqcell_child_lookup(self,"daybar");
//	if(0)
	{
		liqcell *daystrips = liqcell_child_lookup(daybar,"daystrips");

		liqcell_child_removeallvisual( daystrips );

		int daynum;
		for(daynum=1;daynum<=30;daynum++)
		{		
		
					char filedate[256] = "201105";	
					//liqapp_formatnow(filedate,sizeof(filedate),"yyyymmdd");
					
					char buf[FILENAME_MAX];    snprintf(buf,sizeof(buf),"%s/cal/day%s%02d.sketch",app.userdatapath,filedate,daynum);


			liqcell *dayitem = liqcell_quickcreatevis(buf, "sketch", 0, daynum * 56, 80, 56);
			
			//liqapp_log("eep %s",buf);
			liqcell_propsets(dayitem, "sketchfilename",buf);


			liqcell_propsets(  dayitem, "backcolor", "rgb(0,60,0)" );
			liqcell_propsets(  dayitem, "bordercolor", "rgb(255,255,255)" );
			liqcell_child_append(  daystrips,dayitem);				
		}
		liqcell_child_arrange_easycol(daystrips);
		
		
	}
	
	//########################################################################
	//########################################################################
	//########################################################################
	//########################################################################
	//########################################################################
	
	
	
	liqapp_log("dialog open 2");
	
	char *fn = liqcell_getname(self);
		
	if(fn)
	{
		
		liqcell_propsets(editor,"sketcheditfilename",fn);
		
		liqcell_setcaption(titlebox,fn);
		
		if(liqapp_fileexists(fn))
		{
			
			liqapp_log("dialog open 3");
			liqcell_setsketch( editor, liqsketch_newfromfile(fn) );
		}
	}
	
	liqcell_setdirty(editor,0);
		  
	return 1;
}

static int liqcalendar_dayview_dialog_close(liqcell *self,liqcelleventargs *args, void *context)
{
	//
	
	liqapp_log("dialog close 1");
	liqcell *editor = liqcell_child_lookup( self,"editor");
	if(!editor)return 0;

	liqapp_log("dialog close 2");

		char *fn = liqcell_getname(self);
		if(fn)
		{
			liqapp_log("dialog close 3");
	
			liqsketch *sketch = liqcell_getsketch(editor);
			
			if(sketch && liqcell_gettag(editor) && sketch && sketch->strokecount>0)
			{

				// 20090422_000423 lcuk : make sure we do not overwrite the file
				if(liqapp_fileexists(fn))
				{
					char filedate[256];	
					liqapp_formatnow(filedate,sizeof(filedate),"yyyymmdd_hhmmss");
					char *filetitle =liqapp_filename_walkoverpath(fn);
					// got a file
					char s[FILENAME_MAX*3];
					snprintf(s,sizeof(s),"mv %s %s.old.%s",fn,fn,filedate);
					system(s);
					liqapp_log("sketch aging cmd: %s",s);
				}

				
				liqapp_log("dialog close 4");
				liqsketch_filesave( sketch, fn );


			liqcell *notes = liqcell_child_lookup(editor,"notes");
			char *key = liqcell_getcaption(notes);

				
				// hijack this from liqtop
				//post_to_liqbase_net(fn,key,0);
			}
			
		}
}




/**	
 * create a new liqcalendar_dayview widget
 */	
liqcell *liqcalendar_dayview_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqcalendar_dayview", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqcalendar_dayview'"); return NULL;  }
	
	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 2, 2, 52, 40);
	//liqcell_setfont(	icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	//liqcell_setcaption(icon, "icon" );
	//liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);
	

	
	//############################# label7:label
	liqcell *titlebox = liqcell_quickcreatevis("titlebox", "label", 60, 0, 740, 32);
	liqcell_setfont(	titlebox, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(titlebox, "Calendar Day view" );
	liqcell_propsets(  titlebox, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  titlebox, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  titlebox, "textalign", 0 );
	liqcell_setvisible(  titlebox,  0 );
	liqcell_child_append(  self, titlebox);
	
	
	//############################# daybar:label
	liqcell *daybar = liqcell_quickcreatevis("daybar", "label", 0, 0, 80, 480);
	liqcell_propsets(  daybar, "backcolor", "rgb(0,0,0)" );
	liqcell_child_append(  self, daybar);	

		liqcell *daystrips = liqcell_quickcreatevis("daystrips", "label", 0, 0, 80, 480);
	    liqcell_propsets(  daystrips, "backcolor", "rgb(0,0,0)" );
		liqcell_child_append(  daybar, daystrips);	
		
		
	
					liqcell_handleradd(daystrips,    "mouse",   liqcell_easyhandler_kinetic_mouse );

	
	//############################# editor:liqtop
	liqcell *editor = liqcell_quickcreatevis("editor", "liqsketchedit", 80 ,0 , 720, 480); //0, 46, 800, 434);
	//liqcell_propsets(  editor, "bordercolor", "rgb(200,100,100)" );
	//liqcell_setfont(	label6, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	//liqcell_setcaption(label6, "appointments list" );
	//liqcell_propsets(  label6, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label6, "backcolor", "rgb(0,64,0)" );
	//liqcell_propseti(  editor, "lockaspect", 1 );
	liqcell_child_append(  self, editor);
	
/*
	//############################# tags:tagcloud
	liqcell *tags = liqcell_quickcreatevis("tags", "tagcloud", 402, 46, 398, 366);
	liqcell_setfont(	tags, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	liqcell_setcaption(tags, "tags" );
	liqcell_propsets(  tags, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  tags, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  tags, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  tags, "textalign", 2 );
	liqcell_child_append(  self, tags);	

 */

/*
	//############################# label15:label
	liqcell *label15 = liqcell_quickcreatevis("label15", "label", 296, 426, 52, 40);
	liqcell_setfont(	label15, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	liqcell_setcaption(label15, "icon" );
	liqcell_propsets(  label15, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label15, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  label15, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label15, "textalign", 2 );
	liqcell_child_append(  self, label15);

	//############################# label14:label
	liqcell *label14 = liqcell_quickcreatevis("label14", "label", 222, 426, 52, 40);
	liqcell_setfont(	label14, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	liqcell_setcaption(label14, "icon" );
	liqcell_propsets(  label14, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label14, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  label14, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label14, "textalign", 2 );
	liqcell_child_append(  self, label14);
	//############################# label13:label
	liqcell *label13 = liqcell_quickcreatevis("label13", "label", 152, 426, 52, 40);
	liqcell_setfont(	label13, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	liqcell_setcaption(label13, "icon" );
	liqcell_propsets(  label13, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label13, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  label13, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label13, "textalign", 2 );
	liqcell_child_append(  self, label13);
	//############################# label12:label
	liqcell *label12 = liqcell_quickcreatevis("label12", "label", 82, 426, 52, 40);
	liqcell_setfont(	label12, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	liqcell_setcaption(label12, "icon" );
	liqcell_propsets(  label12, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label12, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  label12, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label12, "textalign", 2 );
	liqcell_child_append(  self, label12);
	//############################# label11:label
	liqcell *label11 = liqcell_quickcreatevis("label11", "label", 12, 426, 52, 40);
	liqcell_setfont(	label11, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
	liqcell_setcaption(label11, "icon" );
	liqcell_propsets(  label11, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label11, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  label11, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label11, "textalign", 2 );
	liqcell_child_append(  self, label11);
 */
	
	liqcell_handleradd(self, "dialog_open", liqcalendar_dayview_dialog_open );
	liqcell_handleradd(self, "dialog_close", liqcalendar_dayview_dialog_close );
	return self;
}

