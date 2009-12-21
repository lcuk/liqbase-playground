// this file is part of liqbase by Gary Birkett
		
		
		
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>

#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>            
#include <fcntl.h>                                                                             
#include <unistd.h>
#include <errno.h>


#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
#include "sheepdrawing_editor.h"		
	int sheepdrawing_editor_clear(liqcell *editor);
	int sheepdrawing_editor_undo(liqcell *editor);
	int sheepdrawing_editor_save(liqcell *editor);
	
		static int liqapp_trymakepath_int(char *path,char *upto)
		{
			char *bit=strchr(upto,'/');
			if(bit)
			{
				*bit=0;
				liqapp_trymakepath_int(path,upto);
				*bit='/';
				upto=bit+1;
				liqapp_trymakepath_int(path,upto);
				return 0;
			}	
			if(!liqapp_pathexists(path))
			{
				int status;
				status = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
				if(status)
				{
					liqapp_log("liqapp error: could not mkdir '%s'",path);
					return -1;			
				}
			}
			return 0;
		}
		
		static int liqapp_trymakepath(char *path)
		{
			return liqapp_trymakepath_int(path,path);
		}


	//snprintf(buf,FILENAME_MAX,"%s",app.userdatapath);
	//trymakepath(buf);		
		
//#####################################################################
//#####################################################################
//##################################################################### sheepdrawing_run :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * sheepdrawing_run widget filter, the system is asking you to filter to the specified .
 */	
static int sheepdrawing_run_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
{
	// system is indicating the user has typed into the search box
	// you are expected to filter your content based upon this searchterm.
	// show or hide details and rearrange contents to apply this filter.
	char *searchterm = NULL;
	args->resultoutof=0;  // total number of searchable contents
	args->resultshown=0;  // count of options remaining after filtering.
	searchterm = args->searchterm;
	if(searchterm && *searchterm)
	{
		 // check the name property
		 args->resultoutof++;
		 if( stristr(self->name,searchterm) != NULL )
		 {
			  args->resultshown++;
		 }
		 // check the classname property
		 args->resultoutof++;
		 if( stristr(self->classname,searchterm) != NULL )
		 {
			  args->resultshown++;
		 }
		 // check any other properties or children and increment counters
		 // filter out list items recursively
	}
	return 0;
}
/**	
 * sheepdrawing_run widget refresh, all params set, present yourself to the user.
 */	
static int sheepdrawing_run_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run dialog_open - the user zoomed into the dialog
 */	
static int sheepdrawing_run_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdrawing_run dialog_close - the dialog was closed
 */	
static int sheepdrawing_run_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * sheepdrawing_run widget shown - occurs once per lifetime
 */	
static int sheepdrawing_run_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run mouse - occurs all the time as you stroke the screen
 */	
static int sheepdrawing_run_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run click - occurs when a short mouse stroke occured
 */	
static int sheepdrawing_run_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run keypress - the user pressed a key
 */	
static int sheepdrawing_run_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run keyrelease - the user released a key
 */	
static int sheepdrawing_run_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * sheepdrawing_run paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int sheepdrawing_run_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * sheepdrawing_run dynamic resizing
 */	
static int sheepdrawing_run_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
/*	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *cmdundo = liqcell_child_lookup(self, "cmdundo");
	liqcell *cmdclear = liqcell_child_lookup(self, "cmdclear");
	liqcell *cmdselect = liqcell_child_lookup(self, "cmdselect");
	liqcell *cmdcolor = liqcell_child_lookup(self, "cmdcolor");
	liqcell_setrect_autoscale( backplane, 0,58, 800,422, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,58, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 594,434, 206,48, sx,sy);
	liqcell_setrect_autoscale( cmdundo, 728,60, 72,72, sx,sy);
	liqcell_setrect_autoscale( cmdclear, 728,132, 72,86, sx,sy);
	liqcell_setrect_autoscale( cmdselect, 728,344, 72,90, sx,sy);
	liqcell_setrect_autoscale( cmdcolor, 728,218, 72,124, sx,sy);
 */	return 0;
}

/**	
 * sheepdrawing_run.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_run)
{
	// GO GO GO!
	
	//
	liqcell *backplane = liqcell_child_lookup(sheepdrawing_run, "backplane");
	liqcell *cmdcolor = liqcell_child_lookup(sheepdrawing_run, "cmdcolor");
	liqcell *title = liqcell_child_lookup(sheepdrawing_run, "title");
	
	liqsketch *sketch = liqcell_getsketch(backplane);


		if(!sketch)
		{
			// no sketch!
			return 0;
		}

		if(!sketch->strokelast)
		{
			// nothing drawn
			return 0;
		}

	liqcell_setcaption(title, "preparing to save.." );

	char fileday[256];	
	liqapp_formatnow(fileday,sizeof(fileday),"yyyy/mm/dd");
	
	char filedate[256];	
	liqapp_formatnow(filedate,sizeof(filedate),"yyyymmdd_hhmmss");
	
	char path[ FILENAME_MAX ];	
	snprintf(path,sizeof(path),"%s/MyDocs/sheepdrawing/%s",app.homepath,fileday);
	
	char sketchfn[ FILENAME_MAX ];	
	snprintf(sketchfn,sizeof(sketchfn),"%s/liq.%s.%s.page",path,filedate,app.username,"sheepdrawing");

	char imgfn[ FILENAME_MAX ];	
	snprintf(imgfn,sizeof(imgfn),      "%s/liq.%s.%s.png",path,filedate,app.username,"sheepdrawing");

	liqcell_setcaption(title, "creating folders.." );

	
	liqapp_trymakepath(path);
	
	
	liqcell_setcaption(title, "saving sketch.." );

	
	liqsketch_filesave(sketch , sketchfn );


	liqcell_setcaption(title, "creating image.." );
	
	liqapp_log("...creating image");	
	liqimage *img = liqimage_newatsize(backplane->w,backplane->h,0);
	
	liqapp_log("...creating cliprect");
	liqcliprect *cr = liqcliprect_newfromimage(img);

	liqcell_setcaption(title, "rendering image.." );
	
	liqcell_easypaint(backplane,cr,0,0,backplane->w,backplane->h);

	liqcell_setcaption(title, "saving image.." );


	liqimage_pagesavepng(img,imgfn);
	
	
	liqcell_setcaption(title, "releasing image.." );

	liqapp_log("...releasing cr");
	liqcliprect_release(cr);
	
	liqapp_log("...releasing image");
	liqimage_release(img);
	
	liqapp_log("...done");
		
	liqcell_setcaption(title, "preparing to send ..");

		
	// so, now i have saved a sketch :D
	// and i have also saved a png!
	
	char cmd[FILENAME_MAX*4];


	char *txtusername=       liqapp_pref_getvalue_def("sheepdrawing_username",  "");
	char *txtpassword=       liqapp_pref_getvalue_def("sheepdrawing_password",  "");
	char *txtthread=         liqapp_pref_getvalue_def("sheepdrawing_thread",  "");

	// todo make this safe for sending

	snprintf(cmd,sizeof(cmd),"sheepdrawing-upload.sh --sketchfn '%s' --imgfn '%s' --username '%s' --password '%s' --thread '%s'",sketchfn,imgfn,txtusername,txtpassword,txtthread);
	
	liqcell_setcaption_printf(title, "sending to http://talk.maemo.org/showthread.php?t=%s FIXME!.." ,txtthread);

	
	system(cmd);

	liqcell_setcaption(title, "clearing .." );

	sheepdrawing_editor_clear(backplane);

	liqcell_setcaption(title, "Draw your sheep" );
	
	return 0;
}
/**	
 * sheepdrawing_run.cmdundo clicked
 */	
static int cmdundo_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_run)
{
	liqcell *backplane = liqcell_child_lookup(sheepdrawing_run, "backplane");
	sheepdrawing_editor_undo(backplane);
	return 0;
}
/**	
 * sheepdrawing_run.cmdclear clicked
 */	
static int cmdclear_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_run)
{
	liqcell *backplane = liqcell_child_lookup(sheepdrawing_run, "backplane");
	sheepdrawing_editor_clear(backplane);
	return 0;
}
/**	
 * sheepdrawing_run.cmdselect clicked
 */	
static int cmdselect_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_run)
{
//	liqcell *backplane = liqcell_child_lookup(sheepdrawing_run, "backplane");
//	sheepdrawing_editor_clear(backplane);
	liqcell *backplane = liqcell_child_lookup(sheepdrawing_run, "backplane");
	liqcell *cmdcolor = liqcell_child_lookup(sheepdrawing_run, "cmdcolor");


	 liqcell *dialog = liqcell_quickcreatevis("sheepdrawing_run", "sheepdrawing.sheepdrawing_pictureselect", 0,0, -1,-1);
	 liqcell_easyrun(dialog);


            // process dialog results      
            char *selfn=liqcell_propgets(  dialog, "imagefilenameselected",NULL );
            if( selfn && *selfn )
            {
                //

				liqapp_pref_setvalue("sheepdrawing_background", selfn );
				liqapp_prefs_save();
				
				// refresh the actual contents..
				liqcell_handlerrun(backplane,"refresh",NULL);                

            }
 

	 liqcell_release(dialog);
	return 0;
}
/**	
 * sheepdrawing_run.cmdcolor clicked
 */	
static int cmdcolor_click(liqcell *self,liqcellclickeventargs *args, liqcell *sheepdrawing_run)
{
	
	liqcell *backplane = liqcell_child_lookup(sheepdrawing_run, "backplane");
	liqcell *cmdcolor = liqcell_child_lookup(sheepdrawing_run, "cmdcolor");


	liqcell *dialog = liqcell_quickcreatevis("colorpicker", "sheepdrawing.colorpicker", 0,0, -1,-1);
	liqcell_easyrun(dialog);
	
	
            char *selcol=liqcell_propgets(  dialog, "colorselected",NULL );
            if( selcol && *selcol )
            {	
				liqcell_propsets(  cmdcolor, "backcolor", selcol );
				
				liqapp_pref_setvalue("sheepdrawing_pencolor", selcol );
				liqapp_prefs_save();
				
				// refresh the actual contents..
				liqcell_handlerrun(backplane,"refresh",NULL);
			}

	liqcell_release(dialog);

	return 0;

}
/**	
 * sheepdrawing_run_child_test_seek this function shows how to access members
 */	
	  
static void sheepdrawing_run_child_test_seek(liqcell *sheepdrawing_run)
{	  
	liqcell *backplane = liqcell_child_lookup(sheepdrawing_run, "backplane");
	liqcell *title = liqcell_child_lookup(sheepdrawing_run, "title");
	liqcell *cmdaccept = liqcell_child_lookup(sheepdrawing_run, "cmdaccept");
	liqcell *cmdundo = liqcell_child_lookup(sheepdrawing_run, "cmdundo");
	liqcell *cmdclear = liqcell_child_lookup(sheepdrawing_run, "cmdclear");
	liqcell *cmdselect = liqcell_child_lookup(sheepdrawing_run, "cmdselect");
	liqcell *cmdcolor = liqcell_child_lookup(sheepdrawing_run, "cmdcolor");
}	  
/**	
 * create a new sheepdrawing_run widget
 */	
liqcell *sheepdrawing_run_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdrawing_run", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'sheepdrawing_run'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# backplane:label
	liqcell *backplane = liqcell_quickcreatevis("backplane", "sheepdrawing_editor", 0, 58, 800, 422);
	//liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(backplane, "backplane" );
	//liqcell_propsets(  backplane, "textcolor", "rgb(255,0,0)" );
	//liqcell_propsets(  backplane, "backcolor", "rgb(0,64,64)" );
	//liqcell_propseti(  backplane, "textalign", 2 );
	//liqcell_propseti(  backplane, "textaligny", 2 );
	liqcell_child_append(  self, backplane);
	
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Draw your sheep - todo, finish upload script sheepdog-upload.sh" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);

	//############################# cmdundo:label
	liqcell *cmdundo = liqcell_quickcreatevis("cmdundo", "label", 728, 56, 72, 96);
	liqcell_setfont(	cmdundo, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdundo, "undo" );
	liqcell_propsets(  cmdundo, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdundo, "backcolor", "xrgb(64,0,64)" );
	liqcell_propsets(  cmdundo, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdundo, "textalign", 2 );
	liqcell_propseti(  cmdundo, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdundo, "click", cmdundo_click, self );
	liqcell_child_append(  self, cmdundo);
	
	//############################# cmdclear:label
	liqcell *cmdclear = liqcell_quickcreatevis("cmdclear", "label", 728, 152, 72, 96);
	liqcell_setfont(	cmdclear, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdclear, "clear" );
	liqcell_propsets(  cmdclear, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdclear, "backcolor", "xrgb(64,0,0)" );
	liqcell_propsets(  cmdclear, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdclear, "textalign", 2 );
	liqcell_propseti(  cmdclear, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdclear, "click", cmdclear_click, self );
	liqcell_child_append(  self, cmdclear);
	
	//############################# cmdcolor:label
	liqcell *cmdcolor = liqcell_quickcreatevis("cmdcolor", "label", 728, 248, 72, 96);
	liqcell_setfont(	cmdcolor, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdcolor, "color" );
	liqcell_propsets(  cmdcolor, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdcolor, "backcolor", "xrgb(255,255,255)" );
	liqcell_propsets(  cmdcolor, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdcolor, "textalign", 2 );
	liqcell_propseti(  cmdcolor, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdcolor, "click", cmdcolor_click, self );
	liqcell_child_append(  self, cmdcolor);
	
	//############################# cmdselect:label
	liqcell *cmdselect = liqcell_quickcreatevis("cmdselect", "label", 728, 344, 72, 96);
	liqcell_setfont(	cmdselect, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdselect, "select" );
	liqcell_propsets(  cmdselect, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdselect, "backcolor", "xrgb(0,0,64)" );
	liqcell_propsets(  cmdselect, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdselect, "textalign", 2 );
	liqcell_propseti(  cmdselect, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdselect, "click", cmdselect_click, self );
	liqcell_child_append(  self, cmdselect);


	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 594, 440, 206, 40);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Upload" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	
    char *t =  liqapp_pref_getvalue_def("sheepdrawing_pencolor", "xrgb(255,255,255)");
    if(t && *t)
		liqcell_propsets(  cmdcolor, "backcolor", t );
	
	
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/sheepdrawing/media/sheepdrawing_run_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter", sheepdrawing_run_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh", sheepdrawing_run_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", sheepdrawing_run_shown ,self);
	//liqcell_handleradd_withcontext(self, "resize", sheepdrawing_run_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", sheepdrawing_run_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", sheepdrawing_run_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse", sheepdrawing_run_mouse,self );
	//liqcell_handleradd_withcontext(self, "click", sheepdrawing_run_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", sheepdrawing_run_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", sheepdrawing_run_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", sheepdrawing_run_dialog_close ,self);
	return self;
}

