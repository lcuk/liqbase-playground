#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqbase.h>

//#####################################################################
//#####################################################################
//##################################################################### liqbookreader :: by gary birkett
//#####################################################################
//#####################################################################


// 20090607_190234 lcuk : yes, i know its fixed to one location and has not yet had the goodness i added to original, time constraints etc

liqcell *liqbookreader_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqbookreader","form", 800,480);

	if(self)
	{

		liqfont *font = liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0);
		char *caption = "test lorum ipsum lardy dardy";
		int fw = liqfont_textwidth(font,caption) * 1.2;
		int fh = liqfont_textheight(font);

		int y=0;
		int linenum=0;


		liqcell *body = liqcell_quickcreatewidget("body","frame", 800,480);

			FILE *fn;
			fn=fopen("media/liqbook.example.txt","r");
			if(fn)
			{
				char lineraw[1024];
				int linemax=1024;
				char *line=NULL;

				while(!feof(fn))
				{
					char * rc;
					rc=fgets(lineraw,linemax, (FILE*) fn);
					if(!rc)break;


					char *stripper=lineraw;

					while(*stripper)
					{
						if(*stripper==10 || *stripper==13)
						{
							*stripper=0;
						}
						stripper++;
					}

					line=lineraw;
					//if(*line)
					{
						while(*line==' ' || *line=='\t')line++;



						char nam[32];
						snprintf(nam,sizeof(nam),"line%i",linenum);

						liqcell *tl = liqcell_quickcreatevis(nam,   "label",   0 ,y,   800, fh );
						liqcell_setcaption(   tl , lineraw );
						liqcell_setfont(   tl , liqfont_hold(font) );
						liqcell_child_insert( body, tl );

						if(line[0]=='/' && line[1]=='/')
						{
							// is comment :)
							liqcell_propsets(  tl,  "textcolor", "rgb(0,255,255)" );
						}

						linenum++;
						y+=fh;

						// only read the first few lines...
						//if(y>=liqcell_geth(self)) break;
					}
				}
				if(y>0) body->h=y+fh;
			}


			//liqcell_handleradd(self,    "mouse",   widget_mouse);
			liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );



		liqcell_child_append( self, body );

	}
	return self;
}
