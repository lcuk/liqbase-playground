/**
 * @file	textbox.c
 * @author  Gary Birkett, Zach Habersang
 * @brief 	Textbox UI Component
 * 
 * Copyright (C) 2008 Gary Birkett
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include <string.h>
#include <stdlib.h>


#include <liqbase/liqui.h>



char *liqclip=NULL;



#define XK_MISCELLANY

#include "X11/keysymdef.h"

// colors
#define  BLACK    "rgb(0,0,0)"
#define  WHITE    "rgb(255,255,255)"
#define  RED      "rgb(210,0,0)"
#define  GREEN    "rgb(0,173,0)"
#define  BLUE     "rgb(0,0,255)"
#define  YELLOW   "rgb(225,225,0)"
#define  CYAN     "rgb(0,175,175)"
#define  MAGENTA  "rgb(255,0,255)"




	static int textbox_mouse(liqcell *self, liqcellmouseeventargs *args,void *context)
	{
		// if i have a font on my cell, surely it will have been rendered correctly first..
		// infact, thats right i think
		//liqcell *base = liqcell_getbasewidget(self);
		//liqcell *body = self;

		liqfont *font = liqcell_getfont(	self);
		if(!font)return 0;

		char *cap = liqcell_getcaption(self);
		if(!cap)return 0;
		
				// 20090814_184437 lcuk : if password, replace cap with string("*",len(cap)) for selection purposes
				char passbuff[1024];				
				if(liqcell_propgeti(self,"textispassword",0))
				{
					int clen = strlen(cap);
					if(clen>=sizeof(passbuff)-1)clen=sizeof(passbuff)-1;
					int x;
					for(x=0;x<clen;x++)passbuff[x]='*';
					passbuff[x]=0;
					cap=passbuff;
				}
		
		//int caplen = strlen(cap);
		
		
		
		
		//##########################
		// this tells me where abouts I am on a single line
		int mx = args->mex - liqcell_getx(self) - 8;		// available space per line
		int my = args->mey - liqcell_gety(self) - 4;
		int chpos = liqfont_textfitinside(font,cap,mx);		// char pos of selection
		
		
		//##########################
		// count all the lines	
		#define linemax 128
		char *linestarts[linemax];
		int lineheight = liqfont_textheight(font);
		int lineoffsets[linemax];
		int linelengths[linemax];
		int linecount=0;	
		char *c = cap;
		while(c && *c)
		{
			int tl = strlen(c);		// total length remaining
			int lc = liqfont_textfitinside(font, c, liqcell_getw(self)-4 );
					if(lc<tl)
					{
						int le = lc;
						while(le>0)
						{
							switch(c[le-1])
							{
								case ' ':
								case ',':
								case ';':
								case ':':
								case '.':
									le--;
									break;
								default:
									goto fin;
							}
						}
						fin:
						if(le>0)lc=le;
						while(c[lc]==' ')lc++;
					}	
			linestarts[linecount] = c;
			lineoffsets[linecount] = c-cap;
			linelengths[linecount] = lc;
			linecount++;
			c=&c[lc];
		}
		
		
		
		
		//##########################
		// work out which line the mouse has hit
		int lx=mx;
		int ly=0;
		
		ly = my / lineheight;
		//liqapp_log("mx=%3i, my=%3i, chpos=%3i   lx=%3i, ly=%3i",mx,my,chpos, lx,ly);
		
		if(ly>=linecount)ly=linecount-1;
		
		if(ly>=0)
		{
			// adjust chpos to make sure now we are selecting from the correct line
			chpos = lineoffsets[ly] + liqfont_textfitinside(font, linestarts[ly] ,mx);
		}
		
		
		
		
		
		
										  
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
		
		char *key =strdup( args->keystring ? args->keystring : "");
		//if(!key)key="";
		if(*key && *key<32)
		{
			if(*key==10)
			{
				// Wed Aug 19 00:17:53 2009 lcuk : change this now to send a different event :)
				// Wed Aug 19 00:18:00 2009 lcuk : easier to get a special "keypress_enter" message and know what to do
				// Wed Aug 19 00:23:07 2009 lcuk : lots of things do stuff when you press enter
				// Wed Aug 19 00:23:17 2009 lcuk : alternative is a default button as in visual basic
				// Wed Aug 19 00:23:41 2009 lcuk : how do i find the related default button though within the system
				liqcell_handlerrun(self,"keypress_enter",NULL);
				free(key);	key=strdup("");
			}
			if(*key==8 || *key==9)
			{
				// bs and tab
			}
			else
			{
				// ack! ignore these in single line textbox!
				free(key);	key=strdup("");
			}
		}

		
		int keylen = strlen(key);
		
		if(selstart>captionlen){ selstart=captionlen;sellength=0; }
		
		if(selstart+sellength>captionlen)
		{
			sellength = captionlen-selstart;
		}

		
		
		if(selstart>=0)// && (keylen>0))
		{
			liqapp_log("keypress: %3i '%c' %i %i",(int)(*key),*key,args->keycode,args->keymodifierstate);
			
			if(cursorpos<0)cursorpos=0;
			if(keylen==0)
			{
				// special keys


				if(args->keycode==XK_Left)
				{
					selstart--;
					if(selstart<0)selstart=0;
					if(args->keymodifierstate==0)
						sellength=0;
					else
						sellength++;
						
					cursorpos=selstart;
					liqcell_propseti(  self,  "selstart",  selstart);
					liqcell_propseti(  self,  "sellength", sellength);
					liqcell_propseti(  self,  "cursorpos", cursorpos);
				}
				else
				if(args->keycode==XK_Right)
				{
					if(args->keymodifierstate==0)
					{
						selstart+=sellength+1;
						if(selstart>captionlen)selstart=captionlen;
						sellength=0;
						//cursorpos=selstart;
					}
					else
					{
						sellength++;
						//cursorpos=selstart+sellength;
						//if(cursorpos>captionlen)cursorpos=captionlen;
					}
					
					if(selstart+sellength>captionlen)
					{
						sellength = captionlen-selstart;
					}
					

					cursorpos=selstart+sellength;
					liqcell_propseti(  self,  "selstart",  selstart);
					liqcell_propseti(  self,  "sellength", sellength);
					liqcell_propseti(  self,  "cursorpos", cursorpos);
				}
				else
				{
				

					if(args->keycode==120 && (args->keymodifierstate&4))
					{
						liqapp_log("key CTRL X :: CUT");
						if(liqclip){free(liqclip);liqclip=NULL;}
						liqclip = strndup(&caption[selstart],sellength);
						free(key);	key=strdup(""); keylen = strlen(key);
						goto selch;
					}
					if(args->keycode==99 && (args->keymodifierstate&4))
					{
						liqapp_log("key CTRL C :: COPY");
						if(liqclip){free(liqclip);liqclip=NULL;}
						liqclip = strndup(&caption[selstart],sellength);
						free(key);
						return 0;
					}
	
					if(args->keycode==118 && (args->keymodifierstate&4))
					{
						liqapp_log("key CTRL V :: PASTE");
						free(key); key=strdup(liqclip?liqclip:"");
						keylen = strlen(key);
						goto selch;
					}
				}

			}
			else
			{
				// regular keypress 
				if(*key==8)
				{
					// delete ;)
					free(key);	key=strdup(""); keylen = strlen(key);
					if(selstart>0 && sellength==0)
					{
						selstart--;
						sellength++;
					}
				}

selch:	{ }		
				//
				//liqcell_setcaption(self,args->keystring);
				char *aftersel=&caption[selstart+sellength];
				int aftersellen = strlen(aftersel);
				
				// then the result is start..selstart
				// newbit
				// selstart+sellen..end
				
				
				int maxlen = liqcell_propgeti(  self,"maxlength",0);
				if(maxlen>0)
				{
					if( (selstart + keylen + aftersellen)>maxlen ) keylen = maxlen-(selstart+aftersellen);
					if(keylen<0)keylen=0;
				}
				
				
				// !-- BUG FIX BY ZACH HABERSANG -- !
				// ----------------------------------
				// Program would segfault when 25 or so characters were entered
				// Fix: + 1 fix to reqd! :D
				// note: used gdb with backtrace to find this bug
				
				// 20090615_210659 lcuk : and me to explain why it was wrong ;) damn those +1 adjustments..
				
				int reqd = selstart  +  keylen  +  aftersellen + 1;
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
			}
			
		}
		
		if(key)free(key);
		return 0;

	}
	
	
	
	
	
static int textbox_keyrelease(liqcell *self, liqcellkeyeventargs *args)
{
	return 0;
}



static int widget_click(liqcell *self, liqcellclickeventargs *args)
{
	liqcell *dialog=liqcell_getcontent(self);
	liqcell_easyrun(dialog);
	liqcell_setvisible(dialog,1);
	//args->newdialogtoopen = liqcell_getcontent(self);
	return 1;
}

static int keyboard_show_button_click(liqcell *self,liqcellclickeventargs *args, liqcell *textbox)
{
	liqcell *vkbd = liqcell_quickcreatevis("vkbd", "liqkeyboard", 0, 0, -1, -1);
	liqcell *vkbd_textbox = liqcell_child_lookup(vkbd, "liqkeyboard_textbox");
	
	if(vkbd)
	{
		// 20090814_203451 lcuk : make sure the * follow into the vkb :)
		liqcell_propseti(vkbd_textbox,"textispassword",  liqcell_propgeti(textbox,"textispassword",0)  );
		
		char *caption = liqcell_getcaption(textbox);
		liqcell_setcaption(vkbd_textbox, caption);
		liqcell_setdata(vkbd, textbox);
		liqcell_easyrun(vkbd);
		liqcell_release(vkbd);
	}
	return 1;
}

static int textbox_resize(liqcell *self, liqcelleventargs *args, void *textbox)
{
	#define IW 32 // icon width
	#define IH 32 // icon height
	
	liqcell *kb_show = liqcell_child_lookup(self, "vkbd_command");
	int ww = liqcell_getw(self);
	int hh = liqcell_geth(self);
	liqcell_setrect(kb_show,  ((ww-IW)-8),  ((hh - IH)/2),        IW,IH);   // right hand side, leaving 10 pixels X, and filling 80% of the height
	return 0;
}

/*
void liqcell_setrect(liqcell *self,int x,int y,int w,int h)
{
	if(self->x==x && self->y==y && self->w==w && self->h==h)return;
	self->x=x;
	self->y=y;
	self->w=w;
	self->h=h;
	liqcell_handlerrun(self,"move",NULL);
	liqcell_handlerrun(self,"resize",NULL);
}
*/

/**
 * Create a textbox ui component
 * @return liqcell* The new textbox
 */
liqcell *textbox_create()
{
	
	liqcell *self = liqcell_quickcreatewidget("textbox","form", 600,50);
	
	if(self)
	{
			
		liqcell_setfont(   self,  liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		//liqcell_propsets(  self,  "backcolor", "rgb(100,255,150)" );
		//liqcell_propsets(  self,  "textcolor", "rgb(20,30,40)" );
		//liqcell_propsets(  self,  "bordercolor", "rgb(255,255,255)" );

        liqcell_propsets(  self,  "textcolor", "rgb(0,0,0)" );
		//liqcell_setimage(  self,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/2_text_back.png", 0,0,1) );
        liqcell_setimage(  self,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/2.message/message_input_field.png", 0,0,1) );
		liqcell_propseti(  self,  "lockaspect",  0 );
		//liqcell_propremoves(  self,  "bordercolor" );
		//liqcell_propremoves(  self,  "backcolor" );
				
		liqcell_propseti(  self,  "maxlength",  140 );

		liqcell_propseti(  self,  "selstart",  0 );
		liqcell_propseti(  self,  "sellength", 0 );
		liqcell_propseti(  self,  "cursorpos", 0 );
			
		liqcell_handleradd(self,    "mouse",      textbox_mouse);
		liqcell_handleradd(self,    "keypress",   textbox_keypress);
		liqcell_handleradd(self,    "keyrelease", textbox_keyrelease);
		
		liqcell_handleradd(self,    "resize",   textbox_resize);
	
			
		// add vkbd
		liqcell *vkbd_command = liqcell_quickcreatevis("vkbd_command" , "commandbutton", 0, 0, 0, 0);
		liqcell_handleradd_withcontext(vkbd_command, "click", keyboard_show_button_click, self);
		liqcell_setfont(vkbd_command, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0));
		liqcell_setcaption(vkbd_command, "ABC");
		liqcell_propsets(vkbd_command, "backcolor", CYAN);
		liqcell_propsets(vkbd_command, "textcolor", BLACK);
		liqcell_propseti(vkbd_command, "textalign", 2);
		liqcell_propseti(vkbd_command, "textaligny", 2);
		liqcell_propseti(vkbd_command, "lockaspect", 1);
		
		liqcell_setvisible(vkbd_command,0);		// Wed Aug 19 19:08:20 2009 lcuk : proper way would be checking for no keyboard..
		
		liqcell_child_insert(self, vkbd_command);
	}
	return self;
}
