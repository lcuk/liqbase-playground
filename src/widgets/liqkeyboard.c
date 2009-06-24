#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>

//#####################################################################
//#####################################################################
//##################################################################### liqkeyboard :: by Gary Birkett
//#####################################################################
//#####################################################################




//######################################################################
//######################################################################
//######################################################################
static liqcell *mkframe(liqcell *self,char *title,int w,int h)
{
	liqcell *ch= liqcell_quickcreatevis(title,NULL,0,0,w,h);
	//liqcell_pageautoloadbytitle_apg(ch);
	liqcell_child_append(self,ch);
	return ch;
}


//######################################################################
//######################################################################
//######################################################################

	static int key_click(liqcell *self, liqcelleventargs *args,liqcell *keyboard)
	{
		// 20090624_005355 lcuk : key was clicked, raise a keyboard event and send the click letter itself through as eventargs

		liqcellkeyeventargs keyargs={0};
		
		keyargs.keycode = (int)liqcell_gettag(self);
		snprintf(keyargs.keystring,sizeof(keyargs.keystring),liqcell_getcaption(self));
		keyargs.ispress = 1;
		liqcell_handlerrun(keyboard,"keypress",&keyargs);
		
		keyargs.ispress = 0;
		liqcell_handlerrun(keyboard,"keyrelease",&keyargs);
		return 0;
	}


	static int key_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *keyboard)
	{
		// whilst the button is pressed, the button should change color		
		if(args->mez!=0)
		{
			liqcell_propsets(  self, "textcolor", "rgb(0,0,0)" );
			liqcell_propsets(  self, "backcolor", "rgb(150,100,150)" );
			
		}
		else
		{
			liqcell_propsets(  self, "textcolor", "rgb(255,255,255)" );
			liqcell_propsets(  self, "backcolor", "rgb(100,150,100)" );
			
		}
		return 0;
	}



liqcell *liqkeyboard_create()
{

	//keyrowstart("data");
	//keyrowend();

liqcell *keyboard;

	keyboard = liqcell_quickcreatewidget("liqkeyboard","form",800,480); //mkframe(liqcellroot,"keyboard",800,480);

	//######################################################################
	//######################################################################
	//######################################################################
	//static liqcell *keyboard=NULL;
	liqcell *keyrow=NULL;
	
	void keyrowstart(char *title)
	{
		keyrow = mkframe(keyboard,title,800,480/6);
		//keyrow->handlermouse=key_mouse;


	}
	
	liqcell *keystd(int keysize,char *keycode,char *normal,char *caps)
	{
		float sizes[9] = { 1.0,      1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 6.0, 20.0};
		// width/15
		if(keysize<0 || keysize>7) keysize=0;
		int w=(int)   ((float)(800/16) * sizes[keysize]);
		liqcell *key;
		
		int keycodenumeric=1;
		if(*keycode)
		{
			keycodenumeric=atoi(keycode);
		}

		if(keycodenumeric==0)
		{
			key = mkframe(keyrow,keycode,w,480/7);
			liqcell_setcaption(key,normal);

			//liqcell_propsets(     key,"fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
			//liqcell_propseti(     key,"fontsize", 24 );
			//liqcell_propsets(     key,"backcolor", "rgb(100,100,150)" );
			//liqcell_propseti(     key,"textalign", 2 );
			//liqcell_propseti(     key,"textaligny",2 );

			//key->style=NULL;
		}
		else
		{
			key = mkframe(keyrow,normal,w,480/7);
			//key->style=stylekeycap;
			//key->handlermouse=key_mouse;

			liqcell_propseti(     key,"textalign",1);
			liqcell_propsets(     key,"fontname", "/usr/share/fonts/nokia/nosnb.ttf" );
			liqcell_propseti(     key,"fontsize", 32 );
			liqcell_propsets(     key,"textcolor", "rgb(255,255,255)" );
			liqcell_propsets(     key,"backcolor", "rgb(100,150,100)" );
			liqcell_propseti(     key,"textalign", 2 );
			liqcell_propseti(     key,"textaligny",2 );
			
			liqcell_handleradd_withcontext(   key,"mouse", key_mouse, keyboard );
			liqcell_settag(       key,(void*)keycodenumeric);

		}
		return key;

	}
	void keyrowend()
	{
		//liqcell_child_arrange_easyrow(keyrow);
		liqcell_child_arrange_autoflow(keyrow);
		keyrow=NULL;
	}



	keyrowstart("num");
//		keystd(1,"ESC","","");
		keystd(1,"",   "`" ,"¬");
		keystd(1,"",   "1" ,"!");
		keystd(1,"",   "2" ,"\"");
		keystd(1,"",   "3" ,"£");
		keystd(1,"",   "4" ,"$");
		keystd(1,"",   "5" ,"%");
		keystd(1,"",   "6" ,"^");
		keystd(1,"",   "7" ,"&");
		keystd(1,"",   "8" ,"*");
		keystd(1,"",   "9" ,"(");
		keystd(1,"",   "0" ,")");
		keystd(1,"",   "-" ,"_");
		keystd(1,"",   "=" ,"+");
		//keystd(2,"BSP","","");
	keyrowend();

	keyrowstart("qwerty");
		keystd(3,"","\t","");
		keystd(1,"",   "q" ,"Q");
		keystd(1,"",   "w" ,"W");
		keystd(1,"",   "e" ,"E");
		keystd(1,"",   "r" ,"R");
		keystd(1,"",   "t" ,"T");
		keystd(1,"",   "y" ,"Y");
		keystd(1,"",   "u" ,"U");
		keystd(1,"",   "i" ,"I");
		keystd(1,"",   "o" ,"O");
		keystd(1,"",   "p" ,"P");
		keystd(1,"",   "[" ,"{");
		keystd(1,"",   "]" ,"}");
		//keystd(2,"CR","","");
	keyrowend();

	keyrowstart("asdf");
		keystd(4,"CLK","","");
		keystd(1,"",   "a" ,"A");
		keystd(1,"",   "s" ,"S");
		keystd(1,"",   "d" ,"D");
		keystd(1,"",   "f" ,"F");
		keystd(1,"",   "g" ,"G");
		keystd(1,"",   "h" ,"H");
		keystd(1,"",   "j" ,"J");
		keystd(1,"",   "k" ,"K");
		keystd(1,"",   "l" ,"L");
		keystd(1,"",   ";" ,":");
		keystd(1,"",   "'" ,"@");
		keystd(1,"",   "#" ,"~");
		//keystd(2,"CR","","");
	keyrowend();

	keyrowstart("zxcv");
		keystd(5,"SHL","","");
		//keystd(1,"",   "\\","|");
		keystd(1,"",   "z" ,"Z");
		keystd(1,"",   "x" ,"X");
		keystd(1,"",   "c" ,"C");
		keystd(1,"",   "v" ,"V");
		keystd(1,"",   "b" ,"B");
		keystd(1,"",   "n" ,"N");
		keystd(1,"",   "m" ,"M");
		keystd(1,"",   "," ,"<");
		keystd(1,"",   "." ,">");
		keystd(1,"",   "/" ,"?");
		keystd(1,"",   "@" ,"@");
		//keystd(6,"SHR","","");
	keyrowend();

	keyrowstart("bottom");
		keystd(3,"CTL","","");
		keystd(3,"WN1","","");
		keystd(3,"ALT","","");
		keystd(7,""," ","");
		//keystd(3,"ALG","","");
		//keystd(3,"WN2","","");
		//keystd(3,"CNT","","");
		//keystd(3,"CTR","","");
	keyrowend();


	//liqcell_child_arrange_easycol(keyboard);
	liqcell_child_arrange_autoflow(keyboard);
	return keyboard;
}
