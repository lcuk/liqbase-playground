#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqapp_prefs.h>

#include "liqdoc.h"

#include "liqbookprogress.h"

//#####################################################################
//#####################################################################
//##################################################################### liqbookreader :: by gary birkett
//#####################################################################
//#####################################################################

int liqbookreader_run(char *bookfilename)
{
	liqcell *self = liqcell_quickcreatewidget("liqbookreader","form", 800,480);

	if(self)
	{
		int err=0;
		
		//char *bookfilename = liqcell_propgets(self,"bookfilename",NULL);
		
		//================================================== get and process the fontsize
		int edfontsize;
		char * t=NULL;
		if((t=liqapp_pref_getvalue("book_fontsize")))
		{
			edfontsize=atoi(t);
		}
		else
		{
			edfontsize=24;
		}
		
		if(edfontsize<8)edfontsize=8;
		if(edfontsize>72)edfontsize=72;
		
		
		//=================================================== now, open the font
		
		liqfont *font = liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (edfontsize), 0);


		if(!font)
		{
			{ return liqapp_warnandcontinue(-1,"liqbookreader_run couldnt open font"); }						
		}			




		//=================================================== initialize the bookprogress

		liqbookprogress_shutdown();
		liqbookprogress_startup();






		//=================================================== open the book now 

		// grab the file and process it :)
		struct doc doc;
		doc.renderfont=NULL;
		
		
		doc.renderfont=font;
		doc.rendermarginright=800;
		//doc.rendermarginbottom=99999999;
	


		err=doc_initfromfilename(&doc,bookfilename);
		
		
		if(err)
		{
			{ return liqapp_warnandcontinue(-1,"liqbookreader_run couldnt open doc"); }						
		}
			
		
		
		
		
		liqcell *body = liqcell_quickcreatevis("body",NULL,0 ,0,   800,doc.rendertoth  );
		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_insert( self, body );
		
		
		//liqcell_handleradd_withcontext(body,    "paint", widget_paint,self);
		
		
		int sfl=0;
		int sfu=0;
		if(liqbookprogress_startreading_lookupposition(bookfilename,&sfl,&sfu))
		{
			//
		}
		
		
		struct docline *dline = doc.linefirst;
		
		int y=0;
		while(dline)
		{
			liqcell *scrline = liqcell_quickcreatevis(dline->linedata,NULL,0 ,y,   800,dline->formath);
			liqcell_setfont(scrline,liqfont_hold(font));
			liqcell_child_insert( body, scrline );
			
			y+=dline->formath;
			dline=dline->linknext;
			
		}

		liqcell_easyrun(self);
	}
	
	
	liqcell_release(self);
	return 0;
	//return self;
}
