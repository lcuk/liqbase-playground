// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
extern liqcell * liqpostcard_master;
//#####################################################################
//#####################################################################
//##################################################################### liqpostcard :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqpostcard widget refresh, all params set, present yourself to the user.
 */	
static int liqpostcard_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit

    liqcell *cmdconfigure = liqcell_child_lookup(self, "cmdconfigure");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");

    
	char *username = app.username;
	char *userpassmd5 = liqapp_pref_getvalue("userpass",NULL);
    
	char *twitname = liqapp_pref_getvalue_def("twitname",NULL);
	char *twitpass = liqapp_pref_getvalue_def("twitpass",NULL);

	if(!username || !*username || !userpassmd5 || !*userpassmd5 || !twitname || !*twitname)
	{
        liqcell_setenabled(cmdsend,0);
		liqapp_log("liqpostcard not allowed, no username/userpass/twitname/twitpass configured");
		return -1;
	}
    
    // everything ok :)
    liqcell_setenabled(cmdsend,1);
    
	return 0;
}


/**	
 * liqpostcard dialog_open - the user zoomed into the dialog
 */	
static int liqpostcard_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{

    liqcell_handlerrun(self,"refresh",NULL);
    
	return 0;
}


/**	
 * liqpostcard dialog_close - the dialog was closed
 */	
static int liqpostcard_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard widget shown - occurs once per lifetime
 */	
static int liqpostcard_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard mouse - occurs all the time as you stroke the screen
 */	
static int liqpostcard_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard click - occurs when a short mouse stroke occured
 */	
static int liqpostcard_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard keypress - the user pressed a key
 */	
static int liqpostcard_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard keyrelease - the user released a key
 */	
static int liqpostcard_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqpostcard_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqpostcard dynamic resizing
 */	
static int liqpostcard_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *tweetmessage = liqcell_child_lookup(self, "tweetmessage");
	liqcell *picfront = liqcell_child_lookup(self, "picfront");
	liqcell *messageback = liqcell_child_lookup(self, "messageback");
	//liqcell *cmdmessagewrite = liqcell_child_lookup(self, "cmdmessagewrite");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *cmdmessagedraw = liqcell_child_lookup(self, "cmdmessagedraw");
	liqcell *cmdpicchoose = liqcell_child_lookup(self, "cmdpicchoose");
    liqcell *cmdconfigure = liqcell_child_lookup(self, "cmdconfigure");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");
	liqcell *pichead = liqcell_child_lookup(self, "pichead");
	liqcell *messagehead = liqcell_child_lookup(self, "messagehead");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( tweetmessage, 56,424, 502,50, sx,sy);
	liqcell_setrect_autoscale( picfront, 20,112, 368,186, sx,sy);
	liqcell_setrect_autoscale( messageback, 418,112, 368,186, sx,sy);
	//liqcell_setrect_autoscale( cmdmessagewrite, 418,300, 176,52, sx,sy);
	liqcell_setrect_autoscale( label5, 56,390, 368,32, sx,sy);
	liqcell_setrect_autoscale( cmdmessagedraw, 514,300, 176,52, sx,sy);
	liqcell_setrect_autoscale( cmdpicchoose, 112,300, 176,52, sx,sy);
	liqcell_setrect_autoscale( cmdsend, 574,418, 226,62, sx,sy);
	liqcell_setrect_autoscale( pichead, 20,74, 368,36, sx,sy);
	liqcell_setrect_autoscale( messagehead, 418,74, 368,36, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
    liqcell_setrect_autoscale( cmdconfigure, 508,0, 226,56, sx,sy);
	return 0;
}

/**	
 * liqpostcard.cmdmessagewrite clicked
 */	
static int cmdmessagewrite_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard)
{
	return 0;
}
/**	
 * liqpostcard.cmdmessagedraw clicked
 */	
static int cmdmessagedraw_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard)
{
    //
	liqcell *messageback = liqcell_child_lookup(liqpostcard, "messageback");


		liqcell * oneedit = liqcell_quickcreatevis("liqpostcard.draw","liqsketchedit",0,0,-1,-1);
		
		if(oneedit)
		{
            // copy the sketch and background image to the editor
            liqcell_setsketch( oneedit, liqcell_getsketch(messageback) );
            liqcell_setimage( oneedit, liqcell_getimage(messageback) );
            
            liqcell_propsets(  oneedit, "pencolor", "rgb(0,0,50)" );
            
			liqcell_easyrun(oneedit);
            // now, make sure the messageback sketch is updated
            if( (liqcell_getsketch(messageback)==NULL) && (liqcell_getsketch(oneedit)!=NULL) )
                liqcell_setsketch( messageback, liqcell_getsketch(oneedit) );
                
            if( liqcell_getsketch(messageback) )
            {
                    liqsketch_boundwholearea( liqcell_getsketch(messageback) );
            }
            
                
			liqcell_release(oneedit);
		}
    
	return 0;
}
/**	
 * liqpostcard.cmdpicchoose clicked
 */	
static int cmdpicchoose_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard)
{
    //
	liqcell *picfront = liqcell_child_lookup(liqpostcard, "picfront");


		liqcell * oneedit = liqcell_quickcreatevis("liqpostcard.choose","dialog_selectimage",0,0,-1,-1);
		
		if(oneedit)
		{
            // copy the sketch and background image to the editor
            //liqcell_setsketch( oneedit, liqcell_getsketch(messageback) );
            //liqcell_setimage( oneedit, liqcell_getimage(messageback) );
            
            //liqcell_propsets(  oneedit, "imagefilenameselected",  );

            //int liqrecentphotos_setselectedphoto_filename(liqcell *self,char *buffer,int bufferlen);

            
			
		
			liqcell_easyrun(oneedit);
			//liqapp_log("eep?");
            
            char *selfn=liqcell_propgets(  oneedit, "imagefilenameselected",NULL );
            
			
			//liqapp_log("hmm %s",selfn);
            if( selfn && *selfn )
            {
	            liqcell_setimage( picfront,NULL );
				//liqapp_log("hmm2 %s",selfn);
                liqcell_propsets(  picfront, "imagefilename", selfn  );               
            }           
                
			liqcell_release(oneedit);
			
			liqcell_setdirty(self,1);
		}
        
        
	return 0;
}



















void liqpostcard_sendnow(liqcell *liqpostcard, liqimage *postcardface, liqimage *postcardback, liqsketch *message,char *tweet);





/**	
 * liqpostcard.cmdsend clicked
 */	
static int cmdsend_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard)
{

	liqcell *picfront = liqcell_child_lookup(liqpostcard, "picfront");
	liqcell *messageback = liqcell_child_lookup(liqpostcard, "messageback");
	liqcell *tweetmessage = liqcell_child_lookup(liqpostcard, "tweetmessage");
    
    
    liqimage *imgfront = liqcell_getimage(picfront);
    liqimage *imgback = liqcell_getimage(messageback);
    liqsketch *sketch = liqcell_getsketch(messageback);
    char *tweet = liqcell_getcaption(tweetmessage);
    
    if(!imgfront)
    {
        liqapp_log("cmdsend_click need imgfront");
        return -1;
    }
    if(!imgback)
    {
        liqapp_log("cmdsend_click need imgback");
        return -1;
    }
    if(!sketch)
    {
        liqapp_log("cmdsend_click need sketch");
        return -1;
    }
    if(!tweet || !*tweet)
    {
        liqapp_log("cmdsend_click need tweet");
        return -1;
    }
    
    //liqpostcard_sendnow(liqpostcard,imgfront,imgback,sketch, tweet);
    
    liqpostcard_master = liqpostcard;

		liqcell * progress = liqcell_quickcreatevis("liqpostcard.liqpostcard_sendprogress","liqpostcard.liqpostcard_sendprogress",0,0,-1,-1);
		
		if(progress)
		{
			liqcell_easyrun(progress);
            int sentok = liqcell_propgeti(progress,"sentok",0);
			liqcell_release(progress);
            
            if(!sentok)
            {
                //return 0;
            }
            
            if(sentok)
            {
                liqcell_setcaption(tweetmessage,"");
                liqsketch_clear(sketch);
            }
		}
        
    liqpostcard_master = NULL;
    

	return 0;
}

/**	
 * liqpostcard.cmdconfigure clicked
 */	
static int cmdconfigure_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard)
{

     //if(args->keycode==111 && args->keymodifierstate==4)
     {
		liqcell * conf = liqcell_quickcreatevis("liqpostcard_config","liqpostcard.liqpostcard_config",0,0,-1,-1);

	    liqcell_easyrun(conf);
        liqcell_release(conf);
        
        liqcell_handlerrun(liqpostcard,"refresh",NULL);
     }
	 return 0;
    
	return 0;
}
/**	
 * liqpostcard_child_test_seek this function shows how to access members
 */	
	  
static void liqpostcard_child_test_seek(liqcell *self)
{	  
	liqcell *tweetmessage = liqcell_child_lookup(self, "tweetmessage");
	liqcell *picfront = liqcell_child_lookup(self, "picfront");
	liqcell *messageback = liqcell_child_lookup(self, "messageback");
	liqcell *cmdmessagewrite = liqcell_child_lookup(self, "cmdmessagewrite");
    liqcell *cmdconfigure = liqcell_child_lookup(self, "cmdconfigure");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *cmdmessagedraw = liqcell_child_lookup(self, "cmdmessagedraw");
	liqcell *cmdpicchoose = liqcell_child_lookup(self, "cmdpicchoose");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");
	liqcell *pichead = liqcell_child_lookup(self, "pichead");
	liqcell *messagehead = liqcell_child_lookup(self, "messagehead");
	liqcell *title = liqcell_child_lookup(self, "title");
}	  
/**	
 * create a new liqpostcard widget
 */	
liqcell *liqpostcard_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqpostcard", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqpostcard'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# tweetmessage:textbox
	liqcell *tweetmessage = liqcell_quickcreatevis("tweetmessage", "textbox", 56, 424, 502, 50);
	liqcell_setfont(	tweetmessage, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_setcaption(tweetmessage, "" );
	liqcell_propsets(  tweetmessage, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  tweetmessage, "backcolor", "rgb(255,255,255)" );
	liqcell_propsets(  tweetmessage, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  tweetmessage, "textalign", 0 );
	liqcell_child_append(  self, tweetmessage);
	//############################# picfront:picturebox
	liqcell *picfront = liqcell_quickcreatevis("picfront", "picturebox", 20, 112, 368, 186);
	//liqcell_setfont(	picfront, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  picfront, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  picfront, "backcolor", "rgb(64,0,0)" );
	liqcell_propsets(  picfront, "bordercolor", "rgb(200,100,100)" );
    liqcell_handleradd_withcontext(picfront, "click", cmdpicchoose_click, self );
	liqcell_child_append(  self, picfront);
	//############################# messageback:picturebox
	liqcell *messageback = liqcell_quickcreatevis("messageback", "picturebox", 418, 112, 368, 186);
	//liqcell_setfont(	messageback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
    liqcell_propsets(  messageback, "imagefilename",  "/usr/share/liqbase/liqpostcard/media/liqpostcard_template.png" );
	//liqcell_propsets(  messageback, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  messageback, "backcolor", "rgb(64,0,0)" );
	liqcell_propsets(  messageback, "bordercolor", "rgb(200,100,100)" );
    liqcell_handleradd_withcontext(messageback, "click", cmdmessagedraw_click, self );
	liqcell_child_append(  self, messageback);
 /*   
	//############################# cmdmessagewrite:label
	liqcell *cmdmessagewrite = liqcell_quickcreatevis("cmdmessagewrite", "label", 418, 300, 176, 52);
	liqcell_setfont(	cmdmessagewrite, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdmessagewrite, "Write" );
	liqcell_propsets(  cmdmessagewrite, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdmessagewrite, "backcolor", "xrgb(0,0,64)" );
	liqcell_propsets(  cmdmessagewrite, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdmessagewrite, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdmessagewrite, "click", cmdmessagewrite_click, self );
	liqcell_child_append(  self, cmdmessagewrite);
 */  
	//############################# label5:label
	liqcell *label5 = liqcell_quickcreatevis("label5", "label", 56, 390, 368, 32);
	liqcell_setfont(	label5, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label5, "Message" );
	liqcell_propsets(  label5, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label5, "backcolor", "xrgb(0,64,64)" );
	liqcell_propseti(  label5, "textalign", 0 );
	liqcell_child_append(  self, label5);
    
	//############################# cmdmessagedraw:label
	liqcell *cmdmessagedraw = liqcell_quickcreatevis("cmdmessagedraw", "label", 514, 300, 176, 52);
	liqcell_setfont(	cmdmessagedraw, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdmessagedraw, "Draw" );
	liqcell_propsets(  cmdmessagedraw, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdmessagedraw, "backcolor", "xrgb(0,0,64)" );
	liqcell_propsets(  cmdmessagedraw, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdmessagedraw, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdmessagedraw, "click", cmdmessagedraw_click, self );
	liqcell_child_append(  self, cmdmessagedraw);
    
	//############################# cmdpicchoose:label
	liqcell *cmdpicchoose = liqcell_quickcreatevis("cmdpicchoose", "label", 112, 300, 176, 52);
	liqcell_setfont(	cmdpicchoose, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdpicchoose, "Choose" );
	liqcell_propsets(  cmdpicchoose, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdpicchoose, "backcolor", "xrgb(0,0,64)" );
	liqcell_propsets(  cmdpicchoose, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdpicchoose, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdpicchoose, "click", cmdpicchoose_click, self );
	liqcell_child_append(  self, cmdpicchoose);
    
	//############################# cmdsend:label
	liqcell *cmdsend = liqcell_quickcreatevis("cmdsend", "label", 574, 418, 226, 62);
	liqcell_setfont(	cmdsend, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsend, "Send" );
	liqcell_propsets(  cmdsend, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdsend, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdsend, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdsend, "textalign", 2 );
    liqcell_setenabled(  cmdsend, 0 );
	liqcell_handleradd_withcontext(cmdsend, "click", cmdsend_click, self );
	liqcell_child_append(  self, cmdsend);
    
	//############################# pichead:label
	liqcell *pichead = liqcell_quickcreatevis("pichead", "label", 20, 74, 368, 36);
	liqcell_setfont(	pichead, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(pichead, "Picture" );
	liqcell_propsets(  pichead, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  pichead, "backcolor", "xrgb(0,64,64)" );
	liqcell_propseti(  pichead, "textalign", 0 );
	liqcell_child_append(  self, pichead);
    
	//############################# messagehead:label
	liqcell *messagehead = liqcell_quickcreatevis("messagehead", "label", 418, 74, 368, 36);
	liqcell_setfont(	messagehead, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(messagehead, "Sketch" );
	liqcell_propsets(  messagehead, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  messagehead, "backcolor", "xrgb(0,64,64)" );
	liqcell_propseti(  messagehead, "textalign", 0 );
	liqcell_child_append(  self, messagehead);
    
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "postcard :: say hello." );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
    
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqpostcard_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqpostcard_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqpostcard_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqpostcard_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqpostcard_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqpostcard_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqpostcard_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqpostcard_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqpostcard_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqpostcard_dialog_close ,self);


	//############################# cmdconfigure:label
	liqcell *cmdconfigure = liqcell_quickcreatevis("cmdconfigure", "label", 508, 0, 226, 56);
	liqcell_setfont(	cmdconfigure, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdconfigure, "configure" );
	liqcell_propsets(  cmdconfigure, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdconfigure, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdconfigure, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdconfigure, "textalign", 2 );
	liqcell_handleradd_withcontext(cmdconfigure, "click", cmdconfigure_click, self );
	liqcell_child_append(  self, cmdconfigure);

    
    
    //########## major sideways hack.  classes need declarations and header files.
    int dialog_selectimage_getfirstphoto_filename(liqcell *self,char *buffer,int bufferlen);
    char selfn[FILENAME_MAX]={0};
    liqcell *dialog_selectimage = liqcell_quickcreatevis("liqpostcard.choose","dialog_selectimage",0,0,-1,-1);
    dialog_selectimage_getfirstphoto_filename(dialog_selectimage,selfn,sizeof(selfn) );
    if(selfn && *selfn)
    {
        liqcell_propsets(  picfront, "imagefilename", selfn  );
    }
    liqcell_release(dialog_selectimage);
    
    
    
    liqcell_handlerrun(self,"refresh",NULL);
    
	return self;
}




//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when liqpostcard is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"liqpostcard canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}


int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"liqpostcard" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"liqpostcard liqapp_init failed"); }
	 }
	 liqcell *self = liqpostcard_create();
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}

