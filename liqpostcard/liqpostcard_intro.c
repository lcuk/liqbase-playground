// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqpostcard_intro :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqpostcard_intro widget refresh, all params set, present yourself to the user.
 */	
static int liqpostcard_intro_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqpostcard_intro dialog_open - the user zoomed into the dialog
 */	
static int liqpostcard_intro_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_intro dialog_close - the dialog was closed
 */	
static int liqpostcard_intro_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_intro widget shown - occurs once per lifetime
 */	
static int liqpostcard_intro_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_intro mouse - occurs all the time as you stroke the screen
 */	
static int liqpostcard_intro_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_intro click - occurs when a short mouse stroke occured
 */	
static int liqpostcard_intro_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_intro keypress - the user pressed a key
 */	
static int liqpostcard_intro_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_intro keyrelease - the user released a key
 */	
static int liqpostcard_intro_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_intro paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqpostcard_intro_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqpostcard_intro dynamic resizing
 */	
static int liqpostcard_intro_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *recipient = liqcell_child_lookup(self, "recipient");
	liqcell *picfront = liqcell_child_lookup(self, "picfront");
	liqcell *messageback = liqcell_child_lookup(self, "messageback");
	//liqcell *cmdmessagewrite = liqcell_child_lookup(self, "cmdmessagewrite");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *cmdmessagedraw = liqcell_child_lookup(self, "cmdmessagedraw");
	liqcell *cmdpicchoose = liqcell_child_lookup(self, "cmdpicchoose");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");
	liqcell *pichead = liqcell_child_lookup(self, "pichead");
	liqcell *messagehead = liqcell_child_lookup(self, "messagehead");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( recipient, 56,424, 502,50, sx,sy);
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
	return 0;
}

/**	
 * liqpostcard_intro.cmdmessagewrite clicked
 */	
static int cmdmessagewrite_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_intro)
{
	return 0;
}
/**	
 * liqpostcard_intro.cmdmessagedraw clicked
 */	
static int cmdmessagedraw_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_intro)
{
    //
	liqcell *messageback = liqcell_child_lookup(liqpostcard_intro, "messageback");


		liqcell * oneedit = liqcell_quickcreatevis("liqpostcard_intro.draw","liqsketchedit",0,0,-1,-1);
		
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
 * liqpostcard_intro.cmdpicchoose clicked
 */	
static int cmdpicchoose_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_intro)
{
    //
	liqcell *picfront = liqcell_child_lookup(liqpostcard_intro, "picfront");


		liqcell * oneedit = liqcell_quickcreatevis("liqpostcard_intro.choose","liqpostcard.liqpostcard_selectimage",0,0,-1,-1);
		
		if(oneedit)
		{
            // copy the sketch and background image to the editor
            //liqcell_setsketch( oneedit, liqcell_getsketch(messageback) );
            //liqcell_setimage( oneedit, liqcell_getimage(messageback) );
            
            //liqcell_propsets(  oneedit, "imagefilenameselected",  );

            //int liqrecentphotos_setselectedphoto_filename(liqcell *self,char *buffer,int bufferlen);

            liqcell_setimage( picfront,NULL );
            
			liqcell_easyrun(oneedit);
            
            

   
     
            
            char *selfn=liqcell_propgets(  oneedit, "imagefilenameselected",NULL );
            
            if( selfn && *selfn )
            {     
                liqcell_propsets(  picfront, "imagefilename", selfn  );               
            }           
                
			liqcell_release(oneedit);
		}
        
        
	return 0;
}
/**	
 * liqpostcard_intro.cmdsend clicked
 */	
static int cmdsend_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_intro)
{
	return 0;
}
/**	
 * liqpostcard_intro_child_test_seek this function shows how to access members
 */	
	  
static void liqpostcard_intro_child_test_seek(liqcell *self)
{	  
	liqcell *recipient = liqcell_child_lookup(self, "recipient");
	liqcell *picfront = liqcell_child_lookup(self, "picfront");
	liqcell *messageback = liqcell_child_lookup(self, "messageback");
	liqcell *cmdmessagewrite = liqcell_child_lookup(self, "cmdmessagewrite");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell *cmdmessagedraw = liqcell_child_lookup(self, "cmdmessagedraw");
	liqcell *cmdpicchoose = liqcell_child_lookup(self, "cmdpicchoose");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");
	liqcell *pichead = liqcell_child_lookup(self, "pichead");
	liqcell *messagehead = liqcell_child_lookup(self, "messagehead");
	liqcell *title = liqcell_child_lookup(self, "title");
}	  
/**	
 * create a new liqpostcard_intro widget
 */	
liqcell *liqpostcard_intro_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqpostcard_intro", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqpostcard_intro'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# recipient:textbox
	liqcell *recipient = liqcell_quickcreatevis("recipient", "textbox", 56, 424, 502, 50);
	liqcell_setfont(	recipient, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_setcaption(recipient, "" );
	liqcell_propsets(  recipient, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  recipient, "backcolor", "rgb(255,255,255)" );
	liqcell_propsets(  recipient, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  recipient, "textalign", 0 );
	liqcell_child_append(  self, recipient);
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
	liqcell_setcaption(label5, "Recipient" );
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
	liqcell_setcaption(messagehead, "Message" );
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
	liqcell_handleradd_withcontext(self, "refresh", liqpostcard_intro_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqpostcard_intro_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqpostcard_intro_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqpostcard_intro_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqpostcard_intro_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqpostcard_intro_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqpostcard_intro_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqpostcard_intro_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqpostcard_intro_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqpostcard_intro_dialog_close ,self);
    
    
    //########## major sideways hack.  classes need declarations and header files.
    int liqrecentphotoselect_getfirstphoto(liqcell *self,char *buffer,int bufferlen);
    char selfn[FILENAME_MAX]={0};
    liqcell *liqrecentphotoselect = liqcell_quickcreatevis("liqrecentphotoselect1", "liqpostcard.liqrecentphotoselect", 0, 0, -1,-1);
    liqrecentphotoselect_getfirstphoto_filename(liqrecentphotoselect,selfn,sizeof(selfn) );
    if(selfn && *selfn)
    {
        liqcell_propsets(  picfront, "imagefilename", selfn  );
    }
    liqcell_release(liqrecentphotoselect);
    
	return self;
}

