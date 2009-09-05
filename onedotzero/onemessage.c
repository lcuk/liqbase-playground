// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>


#include "osc_onedotzero.h"


//    osc_onedotzero_send_();


int textbox_clear(liqcell *textbox)
{
	// clear

	liqcell_setcaption(textbox,"");


	liqcell_propseti(  textbox,  "selstart",  0 );
	liqcell_propseti(  textbox,  "sellength", 0 );
	liqcell_propseti(  textbox,  "cursorpos", 0 );
       
	
}



int onemessage_checkforbadwords(char *msg)
{
    liqapp_log("onemessage_checkforbadwords checking '%s'",msg);

    char *filename = "/usr/share/liqbase/onedotzero/media/swear_list.txt";
    
    if( !liqapp_fileexists(filename) )
    {
        liqapp_log("onemessage_checkforbadwords could not find swearlist, allowing through");
        return 0;       
    }

    FILE *file = fopen(filename, "r");
    if( !file )
    {
        liqapp_log("onemessage_checkforbadwords could not open swearlist");
        return -1;       
    }

    char line[ 512 ]={0};
	while ( fgets(line, sizeof line, file) )
    {
        line[511]=0;
        if(*line) line[strlen(line)-1]=0;
        if(*line)
        {
            
           // liqapp_log("checking '%s'",line);
            if(stristr(msg,line))
            {
                // found a bad word
                liqapp_log("onemessage_checkforbadwords bad word found '%s'",line);
                return -1;
            }
        }
    }
    fclose(file);
    
    liqapp_log("onemessage_checkforbadwords is ok :)");
    
    return 0;
    

}
    
		
		
//#####################################################################
//#####################################################################
//##################################################################### onemessage :: by gary birkett
//#####################################################################
//#####################################################################
		
		
        
/**	
 * onemessage widget refresh, all params set, present yourself to the user.
 */	
static int onemessage_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * onemessage dialog_open - the user zoomed into the dialog
 */	
static int onemessage_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{

	liqcell *messagetext = liqcell_child_lookup(self, "messagetext");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdclear = liqcell_child_lookup(self, "cmdclear");
	liqcell *logo = liqcell_child_lookup(self, "logo");
	liqcell *messagetitle = liqcell_child_lookup(self, "messagetitle");
	liqcell *cmdsubmit = liqcell_child_lookup(self, "cmdsubmit");
	
	
	liqcell_setcaption_printf(messagetitle,"Type your message, then press send");
    
	return 0;
}
/**	
 * onemessage dialog_close - the dialog was closed
 */	
static int onemessage_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	liqcell *messagetext = liqcell_child_lookup(self, "messagetext");
	liqcell *messagetitle = liqcell_child_lookup(self, "messagetitle");
	return 0;
}
/**	
 * onemessage widget shown - occurs once per lifetime
 */	
static int onemessage_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onemessage mouse - occurs all the time as you stroke the screen
 */	
static int onemessage_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemessage click - occurs when a short mouse stroke occured
 */	
static int onemessage_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemessage keypress - the user pressed a key
 */	
static int onemessage_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemessage keyrelease - the user released a key
 */	
static int onemessage_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemessage paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int onemessage_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * onemessage dynamic resizing
 */	
static int onemessage_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
}
/**	
 * messagetext.captionchange clicked
 */	
static int messagetext_captionchange(liqcell *self,liqcelleventargs *args, liqcell *onemessage)
{
	
	
	liqcell *cmdsubmit = liqcell_child_lookup(onemessage, "cmdsubmit");
	if(!cmdsubmit)return -1;// Thu Aug 20 00:54:20 2009 lcuk : not yet created

    liqcell *swearfilter = liqcell_child_lookup(onemessage, "swearfilter");





	int tl = strlen(liqcell_getcaption(self));
    
    
    
    
    int isbad=0;
    
    if(tl>0)
    {
        isbad=onemessage_checkforbadwords( liqcell_getcaption(self) );
    }
    if(isbad)
    {
        liqcell_setvisible(  swearfilter, 1 );
    }
	else
    {
        liqcell_setvisible(  swearfilter, 0 );
    }
    
	liqcell_setenabled(cmdsubmit,  (  (tl>0)  && (isbad==0) )?1:0  );	
    liqcell *messageremain = liqcell_child_lookup(onemessage, "messageremain");
    liqcell_setcaption_printf(messageremain,"%i",140-tl);
	
	if(tl>100)
	{
		liqcell_setfont(	self, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	}
	else
	if(tl>80)
	{
		liqcell_setfont(	self, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (34), 0) );
	}
	else
	if(tl>60)
	{
		liqcell_setfont(	self, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (40), 0) );
	}
	else
	if(tl>40)
	{
		liqcell_setfont(	self, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (48), 0) );
	}
	else
	if(tl>20)
	{
		liqcell_setfont(	self, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (56), 0) );
	}
	else
	{
		liqcell_setfont(	self, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (64), 0) );
	}
    
    

	return 0;
}
/**	
 * onemessage.cmdclear clicked
 */	
static int cmdclear_click(liqcell *self,liqcelleventargs *args, liqcell *onemessage)
{
	liqcell *messagetext = liqcell_child_lookup(onemessage, "messagetext");
	textbox_clear(messagetext);
	return 0;
}
/**	
 * onemessage.cmdsubmit clicked
 */	
static int cmdsubmit_click(liqcell *self,liqcelleventargs *args, liqcell *onemessage)
{
	liqcell *messagetext = liqcell_child_lookup(onemessage, "messagetext");
	
	
	
	
	char *tweet = liqcell_getcaption(messagetext);
	if(tweet && *tweet)
	{
		osc_onedotzero_send_newmsg(tweet);
		//
		//liqtwit_sendtweet(tweet);
        
        
        if((strcmp( tweet, "testmsg" )==0))
        {
            // shortcut
        }
        else
        {

    
            liqcell * onemessageprogress = liqcell_quickcreatevis("onedotzero.onemessageprogress","onedotzero.onemessageprogress",0,0,-1,-1);
            
            if(onemessageprogress)
            {
                liqcell_hold(onemessageprogress);
                liqcell_easyrun(onemessageprogress);
                int sentok = liqcell_propgeti(onemessageprogress,"sentok",0);
                liqcell_release(onemessageprogress);
                
                if(!sentok)
                {
                    return 0;
                }
            }
        }

		
		
		liqcell * onemenu = NULL;
		
		if(!onemenu) onemenu = liqcell_quickcreatevis("onedotzero.onemenu","onedotzero.onemenu",0,0,-1,-1);
		
		if(onemenu)
		{
			liqcell_hold(onemenu);
			liqcell_easyrun(onemenu);
			liqcell_release(onemenu);
		}
		
		
		// ready to start again now
		textbox_clear(messagetext);
        osc_onedotzero_send_entermsg();
	}
	
	
	return 0;
}
/**	
 * onemessage_child_test_seek this function shows how to access members
 */	
	  
static void onemessage_child_test_seek(liqcell *self)
{	  
	liqcell *messageremain = liqcell_child_lookup(self, "messageremain");
	liqcell *messagetext = liqcell_child_lookup(self, "messagetext");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdclear = liqcell_child_lookup(self, "cmdclear");
	liqcell *logo = liqcell_child_lookup(self, "logo");
	liqcell *messagetitle = liqcell_child_lookup(self, "messagetitle");
	liqcell *cmdsubmit = liqcell_child_lookup(self, "cmdsubmit");
}


/**	
 * create a new onemessage widget
 */	
liqcell *onemessage_create()
{
	liqcell *self = liqcell_quickcreatewidget("onemessage", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'onemessage'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering


	//############################# cmdsubmit:label
	liqcell *cmdsubmit = liqcell_quickcreatevis("cmdsubmit", "label", 250, 380, 300, 80);
	liqcell_setfont(	cmdsubmit, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (34), 0) );
	liqcell_setcaption(cmdsubmit, "Send" );
	liqcell_propsets(  cmdsubmit, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  cmdsubmit, "backcolor", "rgb(0,128,0)" );
	//liqcell_propsets(  cmdsubmit, "bordercolor", "rgb(200,100,100)" );
	liqcell_setimage(  cmdsubmit,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/button_back.png", 0,0,1) );
	liqcell_propseti(  cmdsubmit, "textalign", 2 );
	liqcell_propseti(  cmdsubmit, "textaligny", 2 );
	liqcell_propseti(  cmdsubmit,  "lockaspect",  0 );
	liqcell_handleradd_withcontext(cmdsubmit, "click", cmdsubmit_click, self );
	liqcell_child_append(  self, cmdsubmit);



	//############################# messageremain:label
	liqcell *messageremain = liqcell_quickcreatevis("messageremain", "label", 582, 100, 200, 60);
	liqcell_setfont(	messageremain, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(messageremain, "140" );
	liqcell_propsets(  messageremain, "textcolor", "rgb(128,128,128)" );
	liqcell_propseti(  messageremain, "textalign", 1 );
	liqcell_propseti(  messageremain, "textaligny", 2 );
	liqcell_child_append(  self, messageremain);


	//############################# messageremain:label
	liqcell *swearfilter = liqcell_quickcreatevis("swearfilter", "label", 0, 30, 800, 60);
	liqcell_setfont(	swearfilter, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(swearfilter, "profanity filter engaged" );
	liqcell_propsets(  swearfilter, "textcolor", "rgb(255,0,0)" );
	liqcell_propseti(  swearfilter, "textalign", 2 );
	liqcell_propseti(  swearfilter, "textaligny", 2 );
    liqcell_setvisible(  swearfilter, 0 );
	liqcell_child_append(  self, swearfilter);






	//############################# messagetitle:label
	liqcell *messagetitle = liqcell_quickcreatevis("messagetitle", "label", 18, 100, 526, 60);
	liqcell_setfont(	messagetitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(messagetitle, "Type your message, then press send" );

	
	liqcell_propsets(  messagetitle, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  messagetitle, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  messagetitle, "textalign", 0 );
	liqcell_child_append(  self, messagetitle);
    
    
    
	//############################# messagetext:textbox
	liqcell *messagetext = liqcell_quickcreatevis("messagetext", "textbox", 18, 150, 764, 200);
	liqcell_setfont(	messagetext, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	//liqcell_propsets(  messagetext, "textcolor", "rgb(0,40,0)" );
	//liqcell_propsets(  messagetext, "backcolor", "rgba(0,0,64,128)" );
	//liqcell_propsets(  messagetext, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  messagetext, "textalign", 0 );
	liqcell_child_append(  self, messagetext);
	
		liqcell_setimage(  messagetext,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/2_text_back.png", 0,0,1) );
		liqcell_propseti(  messagetext,  "maxlength",  140 );
		liqcell_propseti(  messagetext,  "lockaspect",  0 );
		liqcell_propremoves(  messagetext,  "bordercolor" );
		liqcell_propremoves(  messagetext,  "backcolor" );
		
		liqcell_propseti(  messagetext,  "wordwrap",1 );
		
		liqcell_handleradd_withcontext(messagetext, "captionchange", messagetext_captionchange ,self);
	

	char dd[141];
	int x;
	for(x=0;x<sizeof(dd);x++) dd[x]= 65+x%26;
	dd[140]=0;

	//liqcell_setcaption(messagetext, dd );
	
	
	liqcell_setcaption(messagetext, "" );	

	//liqcell_setenabled(cmdsubmit,0);



	//############################# nokiapicture1:nokiapicture
	liqcell *nokiapicture1 = liqcell_quickcreatevis("nokiapicture1", "nokiapicture", 652, 438, 130, 24);
	liqcell_child_insert(  self, nokiapicture1);

	
//	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", onemessage_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", onemessage_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", onemessage_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", onemessage_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", onemessage_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", onemessage_mouse,self );
	liqcell_handleradd_withcontext(self, "click", onemessage_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", onemessage_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", onemessage_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", onemessage_dialog_close ,self);
	
	
	
	return self;
}

