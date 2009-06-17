#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>


// /usr/share/icons/hicolor/40x40/hildon/qgn_stat_battery_full100.png
// /usr/share/icons/hicolor/40x40/hildon/qgn_stat_battery_full75.png
// /usr/share/icons/hicolor/40x40/hildon/qgn_stat_battery_full50.png
// /usr/share/icons/hicolor/40x40/hildon/qgn_stat_battery_full25.png

// /usr/share/icons/hicolor/40x40/hildon/qgn_stat_displaybright1.png
//#####################################################################
//#####################################################################
//##################################################################### liqtop :: by gary birkett :)
//#####################################################################
//#####################################################################







	static int sketchedit_save(liqcell *self)
	{
	
		liqapp_log("moo");
		
		
		char *fn=liqcell_propgets(self,"sketcheditfilename",NULL);
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
			liqsketch_filesave(liqcell_getsketch(self), fn );
			liqcell_setdirty(self,0);
			return 1;
		}
		
		

		char filedate[256];

		liqapp_formatnow(filedate,sizeof(filedate),"yyyymmdd_hhmmss");

		char filenamebuffer[FILENAME_MAX];

		snprintf(filenamebuffer,sizeof(filenamebuffer), "%s/sketches/liq.%s.%s.page",    app.userdatapath,    filedate,    app.username );

		liqsketch_filesave(liqcell_getsketch(self), filenamebuffer );
		
		liqcell_setdirty(self,0);
		
	

		return 1;
	}









	static int sketchedit_dialog_close(liqcell *self, liqcelleventargs *args, void *context)
	{
		// save the sketch?

		//liqcell *content = liqcell_child_lookup( self,"content");
		liqsketch *sketch = liqcell_getsketch(self);
		if(!sketch || sketch->strokecount==0)
		{
			return 0;
		}

		sketchedit_save(self);

		return 1;
	}



	static int sketchedit_undo_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqcell *editor = liqcell_getlinkparent(self);

		liqsketch *sketch = liqcell_getsketch(editor);
		if(!sketch)
		{
			return 0;
		}
		
		//if(!liqcell_getdirty(editor)) return 0;
		
		if(!sketch->strokelast) return 0;
		
		liqsketch_strokeremove(sketch,sketch->strokelast);

		liqcell_setdirty(editor,1);
		
		liqcell_handlerrun(editor,"undo",NULL);

		return 1;
	}



	static int sketchedit_clear_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqcell *editor = liqcell_getlinkparent(self);

		liqsketch *sketch = liqcell_getsketch(editor);
		if(!sketch)
		{
			return 0;
		}

		liqsketch_clear(sketch);


		char *fn=liqcell_propgets(editor,"sketcheditfilename",NULL);
		if(fn)
		{
			// 20090421_233231 lcuk : save it now with the special assigned name
			liqsketch_fileload(sketch, fn );

			return 1;
		}
		
		liqcell_handlerrun(editor,"cleared",NULL);

		return 1;
	}

	static int sketchedit_del_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		
		liqcell *editor = liqcell_getlinkparent(self);

		liqsketch *sketch = liqcell_getsketch(editor);
		if(!sketch)
		{
			
			return 0;
		}
		
		

		liqsketch_clear(sketch);

		char *fn=liqcell_propgets(editor,"sketcheditfilename",NULL);
		if(fn)
		{
			// 20090422_000423 lcuk : delete the actual file now
			if(liqapp_fileexists(fn))
			{
				char filedate[256];	
				liqapp_formatnow(filedate,sizeof(filedate),"yyyymmdd_hhmmss");
				char *filetitle =liqapp_filename_walkoverpath(fn);
				// got a file
				char s[FILENAME_MAX*3];
				snprintf(s,sizeof(s),"mv %s %s.del.%s",fn,fn,filedate);
				system(s);
				liqapp_log("sketch delete cmd: %s",s);
			}
		}
		
		liqcell_setsketch(editor,NULL);
		
		liqcell_setdirty(editor,1);


		liqcell_handlerrun(editor,"cleared",NULL);
		
		return 1;
	}

	static int sketchedit_save_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqcell *editor = liqcell_getlinkparent(self);

		liqsketch *sketch = liqcell_getsketch(editor);
		if(!sketch)
		{
			return 0;
		}

		sketchedit_save(editor);

		liqsketch_clear(sketch);
		
		liqcell_handlerrun(editor,"cleared",NULL);


		return 1;
	}

	static int sketchedit__cmdnull_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		return 1;
	}
		
	static int sketchedit_mouse(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		liqsketch *sketch = liqcell_getsketch(self);
		if(!sketch)
		{
			// 20090421_215728 lcuk : make the sketch now - very late bound :)
			//return 0;
			// mmm dont know about using this
			liqsketch *s = liqsketch_new();
					s->pixelwidth =liqcell_getw(self);
					s->pixelheight=liqcell_geth(self);
					s->dpix=225;	// damn, dont like using this here
					s->dpiy=225;
			liqcell_setsketch( self, s );
			sketch=s;
		}
		liqstroke *stroke;

		if(args->mcnt==1)
		{
			// starting, allocate and insert a new stroke
			stroke = liqstroke_new();
			stroke->pen_y = 255;
			stroke->pen_u = 128;
			stroke->pen_v = 128;
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
				
				
				// this will fail if we haven't installed liqirc
				
				//char *          liqstroke_quadchainbuild(liqstroke *self);
				
				
				//char *quad = liqstroke_quadchainbuild(stroke);
				//if(quad)
				{
					//char buf[1024];
					//snprintf(buf,sizeof(buf),"PRIVMSG #liqbase-test :stroke: %s", quad );
					//sendserv(buf);
				}
				
				
				
				
				
				
				//self->quadchain
				
				char mainbuf[1024];
				int mainused=0;
				char *mainupto=mainbuf;
				
				
				snprintf(mainbuf,sizeof(mainbuf),"PRIVMSG #liqbase-test :stroke: ");
				mainused=strlen(mainbuf);
				mainupto=mainbuf+mainused;
				
				liqpoint *point;
				point = stroke->pointfirst;
				while(point)
				{
					char minibuf[64];
					int miniused = 0;
					
					
					snprintf(minibuf,sizeof(minibuf),"(%i,%i,%i)",point->x,point->y,point->z);
					miniused = strlen(minibuf);
					
					
					if((mainused+miniused)>sizeof(mainbuf)) break;
					
					snprintf(mainupto,sizeof(mainbuf)-mainused,"%s",minibuf);
					
					
					
					mainused+=miniused;
					mainupto=mainbuf+mainused;
					
					
					
					
					
					
					




					point=point->linknext;
				}
				
				//sendserv(mainbuf);
				
			}
		}
		// 20090421_232509 lcuk : make sure we mark ourselves as dirty
		liqcell_setdirty(self,1);

		return 1;
	}




static int sketchedit_keypress(liqcell *self, liqcellkeyeventargs *args, void *context)
{
	liqcell *base = liqcell_getbasewidget(self);

}

static int sketchedit_resize(liqcell *self, liqcelleventargs *args, void *context)
{
	//liqcell *base = liqcell_getbasewidget(self);
	liqcell *undo = liqcell_child_lookup(self,"undo");
	liqcell *clear = liqcell_child_lookup(self,"clear");
	liqcell *save = liqcell_child_lookup(self,"save");
	liqcell *del = liqcell_child_lookup(self,"del");
	int ww=liqcell_getw(self);
	int hh=liqcell_geth(self);
	
	liqcell_setrect(undo,  ww*0.9,  0,        ww*0.1,hh*0.3);
	liqcell_setrect(clear, ww*0.9,  hh*0.3,   ww*0.1,hh*0.3);
	liqcell_setrect(save , ww*0.9,  hh*0.6,   ww*0.1,hh*0.3);
	liqcell_setrect(del ,  ww*0.9,  hh*0.9,   ww*0.1,hh*0.1);
}


liqcell *liqtop_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqtop","form", 800,480);

	if(self)
	{

		//liqcell *self = liqcell_quickcreatevis(name,  NULL,   l,t,w,h );

		liqcell_propseti(self,"sketchediting",1);		// mark it as editing :)

			// 20090421_215752 lcuk : dont make it now, leave it for ultra late binding
			//// give us something to draw onto
			//liqsketch *s = liqsketch_new();
			//		s->pixelwidth =liqcell_getw(self);
			//		s->pixelheight=liqcell_geth(self);
			//		s->dpix=225;	// damn, dont like using this here
			//		s->dpiy=225;
			//liqcell_setsketch( self, s );

		
		liqcell *b;

		b = liqcell_quickcreatevis("undo","button",  800-180,20,   160,160 );
		liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_handleradd(b,    "click",   sketchedit_undo_click);
		liqcell_propsets(  b,    "backcolor", "rgb(100,0,100)" );
		liqcell_handleradd(b,    "mouse",   sketchedit__cmdnull_mouse);
		liqcell_child_insert( self, b );


		b = liqcell_quickcreatevis("clear","button",  800-180,20,   160,160 );
		liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_handleradd(b,    "click",   sketchedit_clear_click);
		liqcell_propsets(  b,    "backcolor", "rgb(0,0,100)" );
		liqcell_handleradd(b,    "mouse",   sketchedit__cmdnull_mouse);
		liqcell_child_insert( self, b );
	
		
		


		b = liqcell_quickcreatevis("save","button",  800-180,200,   160,160 );
		liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_handleradd(b,    "click",   sketchedit_save_click);
		liqcell_propsets(  b,    "backcolor", "rgb(0,100,0)" );
		liqcell_handleradd(b,    "mouse",   sketchedit__cmdnull_mouse);
		liqcell_child_insert( self, b );


		b = liqcell_quickcreatevis("del","button",  800-180,200,   160,160 );
		liqcell_setfont(   b, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_handleradd(b,    "click",   sketchedit_del_click);
		liqcell_propsets(  b,    "backcolor", "rgb(100,0,0)" );
		liqcell_handleradd(b,    "mouse",   sketchedit__cmdnull_mouse);
		liqcell_child_insert( self, b );

		sketchedit_resize(self,NULL, NULL);

		liqcell_handleradd(self,    "keypress",   sketchedit_keypress);
		liqcell_handleradd(self,    "dialog_close",   sketchedit_dialog_close);
		liqcell_handleradd(self,    "mouse",   sketchedit_mouse);
		liqcell_handleradd(self,    "resize",   sketchedit_resize);
		
		
	}
	return self;

}
