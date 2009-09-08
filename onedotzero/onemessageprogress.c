// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
        
liqcell * liqpostcard_master=NULL;
        
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
        


        
        
int onemessageprogress_sendnow()//liqcell *liqpostcard, liqimage *postcardface, liqimage *postcardback, liqsketch *message,char *tweet)
{

    liqapp_log("onemessageprogress_sendnow starting");


    // loop retrying..
    int cnt;
    for(cnt=0;cnt<5;cnt++)
    {
        
        liqapp_log("onemessageprogress_sendnow waiting %i",cnt);
    
        liqapp_sleep_real(1000);
        

        
        if( get_osc_onedotzero_lastmsg_isok() )
        {
            liqapp_log("onemessageprogress_sendnow got response!");
            return 0;
        }
        char *msgorig=get_osc_onedotzero_lastmsg();
        if(!msgorig)
        {
            liqapp_log("onemessageprogress_sendnow no message?!");
            return -1;
        }
        
        char *msg = strdup(msgorig);
        if(!msg)
        {
            liqapp_log("onemessageprogress_sendnow could not malloc message!");
            return -1;
        }        
        osc_onedotzero_send_newmsg(msg);
        free(msg);
    }
        

    
    liqapp_log("onemessageprogress_sendnow timeout");
    



	return -1;
	
}

//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################

        
static void onemessageprogress_log(liqcell *onemessageprogress,char *time,char *msg)
{
    // now, add this to the log screen
    //printf("xlog %s :::: %s\n",time,msg);
    
    liqcell *title = liqcell_child_lookup(onemessageprogress, "title");
    liqcell *liqlist1 = liqcell_child_lookup(onemessageprogress, "liqlist1");
    liqcell *liqlistactual = liqcell_getcontent(liqlist1);

    liqlist_additem(liqlistactual,msg);
    
    //liqcell_setcaption_printf(title,"Progress: %s : %s",time,msg);
    
    liqcell_setdirty(onemessageprogress,1);
    
}

		
//#####################################################################
//#####################################################################
//##################################################################### onemessageprogress :: by gary birkett
//#####################################################################
//#####################################################################






//osc_msglastrecv = liqapp_GetTicks();

static int timer_tick(liqcell *self, liqcellmouseeventargs *args, liqcell *onemessageprogress)
{
    liqcell_setenabled(self,0);
    liqcell *liqlist1 = liqcell_child_lookup(onemessageprogress, "liqlist1");
    liqcell *liqlistactual = liqcell_getcontent(liqlist1);
	liqcell *title = liqcell_child_lookup(onemessageprogress, "title");
	liqcell *lblsentok = liqcell_child_lookup(onemessageprogress, "lblsentok");
	liqcell *lblfail = liqcell_child_lookup(onemessageprogress, "lblfail");
	liqcell *cmdaccept = liqcell_child_lookup(onemessageprogress, "cmdaccept");

    
        liqcell_setvisible(title,    1);
        liqcell_setvisible(liqlist1,1);
        liqcell_setvisible(lblsentok,0);
        liqcell_setvisible(lblfail,  0);
        liqcell_setvisible(cmdaccept,0);
        liqcell_setdirty(self,1);
        
        
    liqapp_log_setforwarding(onemessageprogress_log,onemessageprogress);
            
            
            
    int pcerr = onemessageprogress_sendnow();
    
            
    liqapp_log_setforwarding(NULL,NULL);

        
        
    if(pcerr)
    {

    
        liqcell_setvisible(title,    0);
        liqcell_setvisible(lblsentok,0);
        liqcell_setvisible(lblfail,  1);
        liqcell_setvisible(cmdaccept,1);
        liqcell_setdirty(self,1);
        
        liqcell_propsets(liqlistactual,"backcolor","rgb(50,0,0)" );
        
        
        liqcell_propseti(  onemessageprogress, "sentok", 0 );
        return 0;        
    }
    
    
    liqcell_setvisible(title,    0);
    liqcell_setvisible(lblsentok,1);
    liqcell_setvisible(lblfail,  0);
    liqcell_setvisible(cmdaccept,1);
    
    liqcell_propsets(liqlistactual,"backcolor","rgb(0,50,0)" );
    
    liqcell_setdirty(self,1);
    
    liqcell_propseti(  onemessageprogress, "sentok", 1 );
    
	return 0;
}

		
/**	
 * onemessageprogress widget refresh, all params set, present yourself to the user.
 */	
static int onemessageprogress_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * onemessageprogress dialog_open - the user zoomed into the dialog
 */	
static int onemessageprogress_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onemessageprogress dialog_close - the dialog was closed
 */	
static int onemessageprogress_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onemessageprogress widget shown - occurs once per lifetime
 */	
static int onemessageprogress_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * onemessageprogress mouse - occurs all the time as you stroke the screen
 */	
static int onemessageprogress_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemessageprogress click - occurs when a short mouse stroke occured
 */	
static int onemessageprogress_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemessageprogress keypress - the user pressed a key
 */	
static int onemessageprogress_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemessageprogress keyrelease - the user released a key
 */	
static int onemessageprogress_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * onemessageprogress paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int onemessageprogress_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * onemessageprogress dynamic resizing
 */	
static int onemessageprogress_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);


	liqcell *liqlist1 = liqcell_child_lookup(self, "liqlist1");
	liqcell *lblsentok = liqcell_child_lookup(self, "lblsentok");
	liqcell *lblfail = liqcell_child_lookup(self, "lblfail");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell_setrect_autoscale( lblfail, 110,302, 588,48, sx,sy);
	liqcell_setrect_autoscale( lblsentok, 146,302, 488,48, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 472,394, 328,86, sx,sy);
	liqcell_setrect_autoscale( title, 34,12, 652,48, sx,sy);
	liqcell_setrect_autoscale( liqlist1, 160,58, 480,238, sx,sy);
	return 0;

}



/**	
 * onemenu.cmdback clicked
 */	
static int cmdback_click(liqcell *self,liqcelleventargs *args, liqcell *onemenu)
{
    liqcell_setvisible(  onemenu,0 );
	return 0;
}


/**	
 * onemessageprogress.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcelleventargs *args, liqcell *onemessageprogress)
{
    //liqcell_propseti(  onemessageprogress, "sentok", 1 );
    liqcell_setvisible(  onemessageprogress,0 );
	return 0;
}
/**	
 * onemessageprogress_child_test_seek this function shows how to access members
 */	
	  
static void onemessageprogress_child_test_seek(liqcell *self)
{	  
	liqcell *liqlist1 = liqcell_child_lookup(self, "liqlist1");
	liqcell *lblsentok = liqcell_child_lookup(self, "lblsentok");
	liqcell *lblfail = liqcell_child_lookup(self, "lblfail");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *title = liqcell_child_lookup(self, "title");
}	  
/**	
 * create a new onemessageprogress widget
 */	
liqcell *onemessageprogress_create()
{
    

    
	liqcell *self = liqcell_quickcreatewidget("onemessageprogress", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'onemessageprogress'"); return NULL;  } 
	
    
    
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# liqlist1:liqlist
    
    liqcell *liqlistactual = liqcell_quickcreatevis("liqlistactual", "liqlist", 0,0,-1,-1);
    
	liqcell *liqlist1 = liqcell_quickcreatevis("liqlist1", NULL, 160, 58, 480, 238);
	liqcell_setcontent(  liqlist1,liqlistactual);
	liqcell_child_append(  self, liqlist1);
    
//    liqcell_handleradd_withcontext(liqlist1,    "click",   liqcell_easyhandler_content_zoom_click,self);
    
    
    
	//############################# lblsentok:label
	liqcell *lblsentok = liqcell_quickcreatevis("lblsentok", "label", 146, 302, 488, 48);
	liqcell_setfont(	lblsentok, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(lblsentok, "Sent ok, proceed." );
	liqcell_propsets(  lblsentok, "textcolor", "rgb(0,192,0)" );
	//liqcell_propsets(  lblsentok, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lblsentok, "textalign",  2 );
    liqcell_propseti(  lblsentok, "textaligny", 2 );
	liqcell_child_append(  self, lblsentok);
	//############################# lblfail:label
	liqcell *lblfail = liqcell_quickcreatevis("lblfail", "label", 110, 302, 588, 48);
	liqcell_setfont(	lblfail, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(lblfail, "Send Failed, please try again." );
	liqcell_propsets(  lblfail, "textcolor", "rgb(192,0,0)" );
	//liqcell_propsets(  lblfail, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lblfail, "textalign", 2);
	liqcell_child_append(  self, lblfail);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 472, 394, 228, 86);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Close" );
	//liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	//liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	//liqcell_propseti(  cmdaccept, "textalign", 2 );
    //liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
    
    
    

    
    
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(0,0,0)" );
	liqcell_setimage(  cmdaccept,  liqimage_cache_getfile("/usr/share/liqbase/onedotzero/media/button_back.png", 0,0,1) );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_propseti(  cmdaccept,  "lockaspect",  0 );
    
    
    
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 34, 12, 652, 48);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Sending message, please wait..." );
	liqcell_propsets(  title, "textcolor", "rgb(0,255,255)" );
	//liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" ); 


		liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
		liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
		liqcell_propseti(timer1,"timerinterval", 100 );
		liqcell_setenabled(timer1,1);
		liqcell_child_insert( self,timer1);


        liqcell_setvisible(title,    1);
        liqcell_setvisible(liqlist1,1);
        liqcell_setvisible(lblsentok,0);
        liqcell_setvisible(lblfail,  0);
        liqcell_setvisible(cmdaccept,0);


//	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", onemessageprogress_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", onemessageprogress_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", onemessageprogress_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", onemessageprogress_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", onemessageprogress_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", onemessageprogress_mouse,self );
	liqcell_handleradd_withcontext(self, "click", onemessageprogress_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", onemessageprogress_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", onemessageprogress_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", onemessageprogress_dialog_close ,self);
	return self;
}

