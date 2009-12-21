#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>

#include "sheepdrawing_editor.h"

//#####################################################################
//#####################################################################
//##################################################################### sheepdrawing_editor :: by gary birkett :)
//#####################################################################
//#####################################################################

	int sheepdrawing_editor_clear(liqcell *editor)
	{

		liqsketch *sketch = liqcell_getsketch(editor);
		if(!sketch)
		{
			return 0;
		}

		liqsketch_clear(sketch);

        
		char *fn=liqcell_propgets(editor,"sketcheditfilename",NULL);        // fixed name bug would not reload, thanks javispedro
		if(fn)
		{
			// 20090421_233231 lcuk : saved it now with the special assigned name, reset to that name
			liqsketch_fileload(sketch, fn );

			return 1;
		}
		
		liqcell_handlerrun(editor,"cleared",NULL);
		
		liqcell_settag(editor,0);

		return 1;
	}


	int sheepdrawing_editor_undo(liqcell *editor)
	{

		liqsketch *sketch = liqcell_getsketch(editor);
		if(!sketch)
		{
			return 0;
		}
		
		//if(!liqcell_gettag(editor)) return 0;
		
		if(!sketch->strokelast) return 0;
		
		liqsketch_strokeremove(sketch,sketch->strokelast);

		liqcell_settag(editor,1);
		
		liqcell_handlerrun(editor,"undo",NULL);

		return 1;
	}



	int sheepdrawing_editor_save(liqcell *editor)
	{
	
		liqapp_log("moo");
		
		
		char *fn=liqcell_propgets(editor,"sketcheditfilename",NULL);
		if(fn)
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


			// 20090421_233231 lcuk : save it now with the special assigned name

			
			liqsketch_filesave(liqcell_getsketch(editor), fn  );
			liqcell_settag(editor,0);
			return 1;
		}
		
		liqcell *notes = liqcell_child_lookup(editor,"notes");

		

		char filedate[256];

		liqapp_formatnow(filedate,sizeof(filedate),"yyyymmdd_hhmmss");

		char filenamebuffer[FILENAME_MAX];



		snprintf(filenamebuffer,sizeof(filenamebuffer), "%s/sketches/liq.%s.%s.page.%s",    app.userdatapath,    filedate,    app.username,  "sheepdrawing_editor" );


		liqsketch_filesave(liqcell_getsketch(editor), filenamebuffer );


		liqcell_propsets(editor,"sketchfilenamelast",filenamebuffer);
			
		liqcell_settag(editor,0);
		
	

		return 1;
	}
	
	
	
	
	static int sheepdrawing_editor_refresh(liqcell *self, liqcelleventargs *args, void *context)
	{
        // refresh data:)
		char *background =  liqapp_pref_getvalue_def("sheepdrawing_background",  "");
		if(background && *background)
		{
			liqcell_setimage(  self ,  liqimage_cache_getfile( background,0,0,0) );
		}
		return 0;
    }



	static int sheepdrawing_editor_shown(liqcell *self, liqcelleventargs *args, void *context)
	{
        // shown for the first time :)
		liqcell_handlerrun(self,"refresh",NULL);
		return 0;
    }

	static int sheepdrawing_editor_dialog_open(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqcell_handlerrun(self,"refresh",NULL);
		return 0;
    }




	static int sheepdrawing_editor_dialog_close(liqcell *self, liqcelleventargs *args, void *sheepdrawing_editor)
	{
		//sheepdrawing_editor_save(sheepdrawing_editor);
		return 1;
	}

/*

	static int sheepdrawing_editor_undo_click(liqcell *self, liqcellclickeventargs *args, void *sheepdrawing_editor)
	{
		sheepdrawing_editor_undo(sheepdrawing_editor);
		return 1;
	}

	static int sheepdrawing_editor_clear_click(liqcell *self, liqcellclickeventargs *args, void *sheepdrawing_editor)
	{
		sheepdrawing_editor_undo(sheepdrawing_editor);
		return 1;
	}

	static int sheepdrawing_editor_save_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		sheepdrawing_editor_save(sheepdrawing_editor);
		sheepdrawing_editor_clear(sheepdrawing_editor);
		return 1;
	}
 */	
	

	static int sheepdrawing_editor__cmdnull_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		return 1;
	}
		
	static int sheepdrawing_editor_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		liqsketch *sketch = liqcell_getsketch(self);
		if(!sketch)
		{
			// 20090421_215728 lcuk : make the sketch now - very late bound :)
			//return 0;
			// mmm dont know about using this
			liqsketch *s = liqsketch_new();

					s->pixelwidth =liqcanvas_getwidth(self);
					s->pixelheight=liqcanvas_getheight(self);
					
					s->dpix=225;	// damn, dont like using this here
					s->dpiy=225;
			liqcell_setsketch( self, s );
			sketch=s;
		}
		liqstroke *stroke;
		// this was only to see high intensity quickly
		//args->mez/=2;
		
		//liqapp_log("sss me %i,%i   o %i,%i   ss %i,%i",args->mex,args->mey,    args->ox,args->oy,   args->mex-args->ox,args->mey-args->oy);

		if(args->mcnt==1)
		{
			// starting, allocate and insert a new stroke
            
            
			stroke = liqstroke_new();
			stroke->pen_y = 255;
			stroke->pen_u = 128;
			stroke->pen_v = 128;
            
            {
                char *t=NULL;
                unsigned char bcy=255;
                unsigned char bcu=128;
                unsigned char bcv=128;
                unsigned char bca=255;
                unsigned char bcc=0;
                    t = liqapp_pref_getvalue_def("sheepdrawing_pencolor",NULL);
                    if(t && *t)
                    {
                        liqapp_log("pencolor :: '%s'",t);
                        if(decodecolor(t, &bcy, &bcu, &bcv, &bca, &bcc ))
                        {
                            stroke->pen_y = bcy;
                            stroke->pen_u = bcu;
                            stroke->pen_v = bcv;
                        }
                    }
            }
            
			// ewww yellow experiment looks bad in non aa
			//stroke->pen_y = 255;
			//stroke->pen_u = 255;
			//stroke->pen_v = 1;

			liqstroke_start(stroke,args->mex-args->ox,args->mey-args->oy,args->mez,args->met);

			liqsketch_strokeinsert(sketch,stroke);
		}
		else
		{
			// continuing, get hold of the last stroke
			stroke = sketch->strokelast;
			liqstroke_extend(stroke,args->mex-args->ox,args->mey-args->oy,args->mez,args->met);
			liqsketch_strokeupdate(sketch,stroke);

			if(args->mez!=0)
			{
				// carry on
			}
			else
			{
				// finishing	
			}
		}
		// 20090421_232509 lcuk : make sure we mark ourselves as dirty
		liqcell_settag(self,1);

		return 1;
	}


liqcell *sheepdrawing_editor_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdrawing_editor","form", 800,480);

	if(self)
	{
		
		liqcell_propseti(self,"sketchediting",1);		// mark it as editing :)

		//liqcell_handleradd_withcontext(self,    "keypress",      sheepdrawing_editor_keypress,    self);
        liqcell_handleradd_withcontext(self,    "refresh",       sheepdrawing_editor_refresh,       self);
        liqcell_handleradd_withcontext(self,    "shown",         sheepdrawing_editor_shown,       self);
		liqcell_handleradd_withcontext(self,    "dialog_open",   sheepdrawing_editor_dialog_open, self);
		liqcell_handleradd_withcontext(self,    "dialog_close",  sheepdrawing_editor_dialog_close,self);
		liqcell_handleradd_withcontext(self,    "mouse",         sheepdrawing_editor_mouse,       self);
		//liqcell_handleradd_withcontext(self,    "resize",        sheepdrawing_editor_resize,      self);
		//liqcell_handleradd_withcontext(self,    "paint",         sheepdrawing_editor_paint,       self);
	}
	return self;

}
