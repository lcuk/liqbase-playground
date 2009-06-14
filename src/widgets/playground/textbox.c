

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqbase.h>

//#####################################################################
//#####################################################################
//##################################################################### textbox :: by gary birkett
//#####################################################################
//#####################################################################


	// damn, this should be taken care of by the OS itself
	// this is because the hitpoint will not always match with where I think it will be
	// this is bad and good in practice
	static int textbox_mouse(liqcell *self, liqcellmouseeventargs *args,void *context)
	{
		// if i have a font on my cell, surely it will have been rendered correctly first..
		// infact, thats right i think
		//liqcell *base = liqcell_getbasewidget(self);
		liqcell *body = self;

		liqfont *font = liqcell_getfont(	self);
		if(!font)return 0;

		char *cap = liqcell_getcaption(self);
		if(!cap)return 0;
		
		int caplen = strlen(cap);
		
		
		int mx = args->mex - liqcell_getx(self);
		
		int chpos = liqfont_textfitinside(font,cap,mx);
										  
		// neat :) i know where the mouse clicked (left aligned text only...)
		// todo: handle other alignments
		
		if(args->mcnt==1)
		{
			// start of selection..
			liqcell_propseti(  self,  "selfirst",  chpos );
			liqcell_propseti(  self,  "selstart",  chpos );
			liqcell_propseti(  self,  "sellength", 0 );
			liqcell_propseti(  self,  "cursorpos", chpos );
		}
		else
		{
			// extending selection
			
			int selfirst = liqcell_propgeti(  self,"selfirst",chpos);
			int selstart;
			int sellength;
			
			if(chpos<selfirst)
			{
				// got to invert
				selstart=chpos;
				sellength=selfirst-chpos;
			}
			else
			{
				selstart=selfirst;
				sellength=chpos-selfirst;				
			}

			
			liqcell_propseti(  self,  "selstart",  selstart );
			liqcell_propseti(  self,  "sellength", sellength );
			liqcell_propseti(  self,  "cursorpos", chpos );
		}
		
		liqcell_handlerrun(self,"selchange",NULL);
		
		return 1;

	}

	static int textbox_keypress(liqcell *self, liqcellkeyeventargs *args,void *context)
	{
		//liqcell *base = liqcell_getbasewidget(self);
		// i can then use my base to access members as defined by the widget itself
		//liqcell_setcaption(self,args->keystring);
	
		int selstart = liqcell_propgeti(  self,"selstart",-1);
		int sellength = liqcell_propgeti(  self,"sellength",0);
		int cursorpos = liqcell_propgeti(  self,"cursorpos",-1);
		
		char *caption = liqcell_getcaption(self);
		int captionlen = strlen(caption);
		
		char *key = args->keystring;
		int keylen = strlen(key);
		
		if(selstart>captionlen){ selstart=captionlen;sellength=0; }
		
		if(selstart+sellength>captionlen)
		{
			sellength = captionlen-selstart;
		}
		
		
		if(selstart>=0 && (keylen>0))
		{
			liqapp_log("keypress: %3i '%c'",(int)(*key),*key,args->keycode);
			
			if(*key==8)
			{
				// delete ;)
				key="";
				keylen=0;
				if(selstart>0 && sellength==0)
				{
					selstart--;
					sellength++;
				}
			}

			if(*key==13)
			{
				// click event!
				liqapp_log("keypress return! click event firing!");
				key="";
				keylen=0;
				liqcell_handlerrun(self,"click",NULL);
				return 1;
			}
						
			//
			//liqcell_setcaption(self,args->keystring);
			char *aftersel=&caption[selstart+sellength];
			int aftersellen = strlen(aftersel);
			
			// then the result is start..selstart
			// newbit
			// selstart+sellen..end
			
			int reqd = selstart  +  keylen  +  aftersellen;
			char *buff=malloc(reqd);
			char *block=buff;
			if(buff)
			{
				if(selstart>0)
				{
					strncpy(block,caption,selstart);
					block+=selstart;
				}
				if(keylen>0)
				{
					strncpy(block,key,keylen);
					block+=keylen;
				}
				
				if(aftersellen>0)
				{
					strncpy(block,aftersel,aftersellen);
					block+=aftersellen;
				}
				*block=0;
				liqcell_setcaption(self,buff);
				




				
				free(buff);
			}

			liqcell_propseti(  self,  "selstart",  selstart + keylen);
			liqcell_propseti(  self,  "sellength", 0 );
			liqcell_propseti(  self,  "cursorpos", selstart + keylen);
			liqcell_handlerrun(self,"selchange",NULL);
			
		}

	}
	
	static int textbox_keyrelease(liqcell *self, liqcellkeyeventargs *args)
	{
		//liqcell *base = liqcell_getbasewidget(self);
		// i can then use my base to access members as defined by the widget itself
		//liqcell_setcaption(self,args->keystring);
	}
	







liqcell *textbox_create(char *caption,char *datadefault)
{
	
	liqcell *self = liqcell_quickcreatewidget("textbox","textbox", 800,50);
	
	if(self)
	{

		
			liqcell *data = liqcell_quickcreatevis("data","frame", 210,0,   580,40);
			liqcell_setfont(   self,  liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
			liqcell_propsets(  self,  "backcolor", "rgb(100,255,150)" );
			liqcell_propsets(  self,  "textcolor", "rgb(20,30,40)" );
			liqcell_propsets(  self,  "bordercolor", "rgb(255,255,255)" );
			//liqcell_setcaption(data,  datadefault );
		//liqcell_child_insert( self, data );

			liqcell_propseti(  self,  "selstart",  0 );
			liqcell_propseti(  self,  "sellength", 0 );
			liqcell_propseti(  self,  "cursorpos", 0 );


			//liqcell_propseti(  data,  "selstart",  5 );
			//liqcell_propseti(  data,  "sellength", 12 );
			//liqcell_propseti(  data,  "cursorpos", 17 );
			
			liqcell_handleradd(self,    "mouse",      textbox_mouse);
			liqcell_handleradd(self,    "keypress",   textbox_keypress);
			liqcell_handleradd(self,    "keyrelease", textbox_keyrelease);



//liqcell *liqkeyboard_create();

	//		liqcell *kb = liqcell_quickcreatevis("data","liqkeyboard", 500,0,   60,20);
			//liqcell_setfont(   kb,  liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (36), 0) );
			//liqcell_propsets(  kb,  "backcolor", "rgb(220,255,220)" );
			//liqcell_propsets(  kb,  "textcolor", "rgb(0,0,0)" );
			//liqcell_setcaption(kb,  datadefault );

	//	liqcell_child_insert( self, kb );



		
		
	}
	return self;
}

