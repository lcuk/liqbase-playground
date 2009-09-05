// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
        
char * liqtwitter_message=NULL;
        
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
        







        
        
int liqtwitter_sendnow()//liqcell *liqtwitter, liqimage *postcardface, liqimage *postcardback, liqsketch *message,char *tweet)
{


    char *tweet = liqtwitter_message;

    if(!tweet || !*tweet)
    {
        liqapp_log("liqtwitter_send need tweet");
        return -1;
    }
    
    liqapp_log("liqtwitter_send sending '%s'",tweet);
    
    int iserr = liqtwit_sendtweet(tweet);

    liqapp_log("liqtwitter_send sent result %i",iserr);
    return iserr;

}

//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################

        
static void liqtwitter_sendprogress_log(liqcell *liqtwitter_sendprogress,char *time,char *msg)
{
    // now, add this to the log screen
    printf("xlog %s :::: %s\n",time,msg);
    
    liqcell *title = liqcell_child_lookup(liqtwitter_sendprogress, "title");
    
    liqcell_setcaption_printf(title,"Progress: %s : %s",time,msg);
    
    liqcell_setdirty(liqtwitter_sendprogress,1);
    
}

		
//#####################################################################
//#####################################################################
//##################################################################### liqtwitter_sendprogress :: by gary birkett
//#####################################################################
//#####################################################################






//osc_msglastrecv = liqapp_GetTicks();

static int timer_tick(liqcell *self, liqcellmouseeventargs *args, liqcell *liqtwitter_sendprogress)
{
    liqcell_setenabled(self,0);

	liqcell *title = liqcell_child_lookup(liqtwitter_sendprogress, "title");
	liqcell *lblsentok = liqcell_child_lookup(liqtwitter_sendprogress, "lblsentok");
	liqcell *lblfail = liqcell_child_lookup(liqtwitter_sendprogress, "lblfail");
	liqcell *cmdaccept = liqcell_child_lookup(liqtwitter_sendprogress, "cmdaccept");

    
        liqcell_setvisible(title,    1);
        liqcell_setvisible(lblsentok,0);
        liqcell_setvisible(lblfail,  0);
        liqcell_setvisible(cmdaccept,0);
        liqcell_setdirty(self,1);
        
        
    liqapp_log_setforwarding(liqtwitter_sendprogress_log,liqtwitter_sendprogress);
            
            
            
    int pcerr = liqtwitter_sendnow();
    
            
    liqapp_log_setforwarding(NULL,NULL);

        
        
    if(pcerr)
    {

    
        liqcell_setvisible(title,    0);
        liqcell_setvisible(lblsentok,0);
        liqcell_setvisible(lblfail,  1);
        liqcell_setvisible(cmdaccept,1);
        liqcell_setdirty(self,1);
        
        liqcell_propseti(  liqtwitter_sendprogress, "sentok", 0 );
        return 0;        
    }
    
    
    liqcell_setvisible(title,    0);
    liqcell_setvisible(lblsentok,1);
    liqcell_setvisible(lblfail,  0);
    liqcell_setvisible(cmdaccept,1);
    liqcell_setdirty(self,1);
    
    liqcell_propseti(  liqtwitter_sendprogress, "sentok", 1 );
    
	return 0;
}

		
/**	
 * liqtwitter_sendprogress widget refresh, all params set, present yourself to the user.
 */	
static int liqtwitter_sendprogress_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqtwitter_sendprogress dialog_open - the user zoomed into the dialog
 */	
static int liqtwitter_sendprogress_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtwitter_sendprogress dialog_close - the dialog was closed
 */	
static int liqtwitter_sendprogress_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtwitter_sendprogress widget shown - occurs once per lifetime
 */	
static int liqtwitter_sendprogress_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtwitter_sendprogress mouse - occurs all the time as you stroke the screen
 */	
static int liqtwitter_sendprogress_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtwitter_sendprogress click - occurs when a short mouse stroke occured
 */	
static int liqtwitter_sendprogress_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtwitter_sendprogress keypress - the user pressed a key
 */	
static int liqtwitter_sendprogress_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtwitter_sendprogress keyrelease - the user released a key
 */	
static int liqtwitter_sendprogress_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtwitter_sendprogress paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqtwitter_sendprogress_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqtwitter_sendprogress dynamic resizing
 */	
static int liqtwitter_sendprogress_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *lblfail = liqcell_child_lookup(self, "lblfail");
	liqcell *lblsentok = liqcell_child_lookup(self, "lblsentok");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( cmdaccept, 472,394, 328,86, sx,sy);
	liqcell_setrect_autoscale( title, 36,46, 652,48, sx,sy);
	liqcell_setrect_autoscale( lblsentok, 150,196, 510,48, sx,sy);
	liqcell_setrect_autoscale( lblfail, 116,250, 588,48, sx,sy);
	return 0;
}

/**	
 * liqtwitter_sendprogress.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcelleventargs *args, liqcell *liqtwitter_sendprogress)
{
    //liqcell_propseti(  liqtwitter_sendprogress, "sentok", 1 );
    liqcell_setvisible(  liqtwitter_sendprogress,0 );
	return 0;
}
/**	
 * liqtwitter_sendprogress_child_test_seek this function shows how to access members
 */	
	  
static void liqtwitter_sendprogress_child_test_seek(liqcell *self)
{	  
	liqcell *lblfail = liqcell_child_lookup(self, "lblfail");
	liqcell *lblsentok = liqcell_child_lookup(self, "lblsentok");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *title = liqcell_child_lookup(self, "title");
}	  
/**	
 * create a new liqtwitter_sendprogress widget
 */	
liqcell *liqtwitter_sendprogress_create()
{
    

    
	liqcell *self = liqcell_quickcreatewidget("liqtwitter_sendprogress", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqtwitter_sendprogress'"); return NULL;  } 
	
    
    
    
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 36, 46, 652, 48);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Sending, please wait..." );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
    liqcell_setvisible(  title, 0 );
	liqcell_child_append(  self, title);
    //############################# lblfail:label
	liqcell *lblfail = liqcell_quickcreatevis("lblfail", "label", 116, 250, 588, 48);
	liqcell_setfont(	lblfail, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(lblfail, "Send Failed, please try again." );
	liqcell_propsets(  lblfail, "textcolor", "rgb(192,0,0)" );
	liqcell_propsets(  lblfail, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lblfail, "textalign", 0 );
    liqcell_setvisible(  lblfail, 0 );
	liqcell_child_append(  self, lblfail);
	//############################# lblsentok:label
	liqcell *lblsentok = liqcell_quickcreatevis("lblsentok", "label", 150, 196, 510, 48);
	liqcell_setfont(	lblsentok, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(lblsentok, "Sent ok, proceed." );
	liqcell_propsets(  lblsentok, "textcolor", "rgb(0,192,0)" );
	liqcell_propsets(  lblsentok, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lblsentok, "textalign", 0 );
    liqcell_setvisible(  lblsentok, 0 );
	liqcell_child_append(  self, lblsentok);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 472, 394, 328, 86);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Close" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "rgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
    liqcell_setvisible(  cmdaccept, 0 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);

		liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
		liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
		liqcell_propseti(timer1,"timerinterval", 100 );
		liqcell_setenabled(timer1,1);
		liqcell_child_insert( self,timer1);

	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqtwitter_sendprogress_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqtwitter_sendprogress_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqtwitter_sendprogress_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqtwitter_sendprogress_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqtwitter_sendprogress_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqtwitter_sendprogress_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqtwitter_sendprogress_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqtwitter_sendprogress_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqtwitter_sendprogress_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqtwitter_sendprogress_dialog_close ,self);
	return self;
}

