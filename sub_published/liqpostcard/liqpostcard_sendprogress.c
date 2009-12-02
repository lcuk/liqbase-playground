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
        


        
        
int liqpostcard_sendnow()//liqcell *liqpostcard, liqimage *postcardface, liqimage *postcardback, liqsketch *message,char *tweet)
{

    liqapp_log("liqpostcard_send starting");

    liqcell *liqpostcard = liqpostcard_master;


	liqcell *postcardface = liqcell_child_lookup(liqpostcard, "picfront");
	liqcell *postcardback = liqcell_child_lookup(liqpostcard, "messageback");
	liqcell *tweetmessage = liqcell_child_lookup(liqpostcard, "tweetmessage");
    
    
    liqimage *imgfront = liqcell_getimage(postcardface);
    liqimage *imgback = liqcell_getimage(postcardback);
    liqsketch *sketch = liqcell_getsketch(postcardback);
    char *tweet = liqcell_getcaption(tweetmessage);
    
    if(!imgfront)
    {
        liqapp_log("liqpostcard_send need imgfront");
        return -1;
    }
    if(!imgback)
    {
        liqapp_log("liqpostcard_send need imgback");
        return -1;
    }
    if(!sketch)
    {
        liqapp_log("liqpostcard_send need sketch");
        return -1;
    }
    if(!tweet || !*tweet)
    {
        liqapp_log("liqpostcard_send need tweet");
        return -1;
    }


    if(!sketch->filename)
    {
        // shit!
        liqapp_log("liqpostcard_send sketch has no filename");
        return -1;
    }

    //liqapp_log("liqpostcard_send test progress");
    //return -2;

        
        liqapp_log("liqpostcard_send creating image");
        liqimage *img = liqimage_newatsize(800,960,0);
        if(!img)
        {
            liqapp_log("liqpostcard_send could not alloc image");
            return -1;
        }
        
        liqapp_log("liqpostcard_send creating cliprect");
        liqcliprect *cr = liqcliprect_newfromimage(img);
        if(!cr)
        {
            liqapp_log("liqpostcard_send could not alloc cr");
            
            liqimage_release(img);
            return -1;
        }
    
        
        liqapp_log("liqpostcard_send clearing");
        liqcliprect_drawclear(cr,0,128,128);
        
        liqapp_log("liqpostcard_send drawing");
        
        liqcliprect_drawimagecolor(cr,imgfront,0,0  ,800,480,1);
        
        liqcliprect_drawimagecolor(cr,imgback,0,480,800,480,1);
        
        liqcliprect_drawsketch(cr,sketch, 0,480,800,480,2);
        




    
        liqapp_log("liqpostcard_send building filename class");


				char 		fmtnow[255];
	 			liqapp_formatnow(fmtnow,255,"yyyymmdd_hhmmss");
				char buf[FILENAME_MAX+1];
				snprintf(buf,FILENAME_MAX,"%s/sketches/liq.%s.%s.postcard.png",app.userdatapath,fmtnow,tweet  );

    
       /// char buf[FILENAME_MAX]={0};
        
       /// liqcell_historystore_historythumb_getfilename(buf,sizeof(buf),self->classname);
        
        //snprintf(buf,FILENAME_MAX,"%s/historythumb/liq.%s.historythumb.png",app.userdatapath,self->classname);
        
        
        
     
        liqapp_log("liqpostcard_send saving image as '%s'",buf);
    
        liqimage_pagesavepng(img,buf);
        
        int mainid = post_to_liqbase_net(buf,tweet,0);
        
        if(mainid)
        {

            int subid = post_to_liqbase_net(sketch->filename,tweet,0);
           
            
        }
    
        
        liqapp_log("liqpostcard_send releasing cr");
        liqcliprect_release(cr);
        
        liqapp_log("liqpostcard_send releasing image");
        liqimage_release(img);
	
    
        liqapp_log("liqpostcard_send done");
    



	return 0;
	
}

//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################

        
static void liqpostcard_sendprogress_log(liqcell *liqpostcard_sendprogress,char *time,char *msg)
{
    // now, add this to the log screen
    printf("xlog %s :::: %s\n",time,msg);
    
    liqcell *title = liqcell_child_lookup(liqpostcard_sendprogress, "title");
    liqcell *liqlist1 = liqcell_child_lookup(liqpostcard_sendprogress, "liqlist1");
    liqcell *liqlistactual = liqcell_getcontent(liqlist1);

    liqlist_additem(liqlistactual,msg);
    
    //liqcell_setcaption_printf(title,"Progress: %s : %s",time,msg);
    
    liqcell_setdirty(liqpostcard_sendprogress,1);
    
}

		
//#####################################################################
//#####################################################################
//##################################################################### liqpostcard_sendprogress :: by gary birkett
//#####################################################################
//#####################################################################






//osc_msglastrecv = liqapp_GetTicks();

static int timer_tick(liqcell *self, liqcellmouseeventargs *args, liqcell *liqpostcard_sendprogress)
{
    liqcell_setenabled(self,0);
    liqcell *liqlist1 = liqcell_child_lookup(liqpostcard_sendprogress, "liqlist1");
    liqcell *liqlistactual = liqcell_getcontent(liqlist1);
	liqcell *title = liqcell_child_lookup(liqpostcard_sendprogress, "title");
	liqcell *lblsentok = liqcell_child_lookup(liqpostcard_sendprogress, "lblsentok");
	liqcell *lblfail = liqcell_child_lookup(liqpostcard_sendprogress, "lblfail");
	liqcell *cmdaccept = liqcell_child_lookup(liqpostcard_sendprogress, "cmdaccept");

    
        liqcell_setvisible(title,    1);
        liqcell_setvisible(lblsentok,0);
        liqcell_setvisible(lblfail,  0);
        liqcell_setvisible(cmdaccept,0);
        liqcell_setdirty(self,1);
        
        
    liqapp_log_setforwarding(liqpostcard_sendprogress_log,liqpostcard_sendprogress);
            
            
            
    int pcerr = liqpostcard_sendnow();
    
            
    liqapp_log_setforwarding(NULL,NULL);

        
        
    if(pcerr)
    {

    
        liqcell_setvisible(title,    0);
        liqcell_setvisible(lblsentok,0);
        liqcell_setvisible(lblfail,  1);
        liqcell_setvisible(cmdaccept,1);
        liqcell_setdirty(self,1);
        
        liqcell_propsets(liqlistactual,"backcolor","rgb(50,0,0)" );
        
        liqcell_propseti(  liqpostcard_sendprogress, "sentok", 0 );
        return 0;        
    }
    
    
    liqcell_setvisible(title,    0);
    liqcell_setvisible(lblsentok,1);
    liqcell_setvisible(lblfail,  0);
    liqcell_setvisible(cmdaccept,1);
    
    liqcell_propsets(liqlistactual,"backcolor","rgb(0,50,0)" );
    
    liqcell_setdirty(self,1);
    
    liqcell_propseti(  liqpostcard_sendprogress, "sentok", 1 );
    
	return 0;
}

		
/**	
 * liqpostcard_sendprogress widget refresh, all params set, present yourself to the user.
 */	
static int liqpostcard_sendprogress_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
	return 0;
}
/**	
 * liqpostcard_sendprogress dialog_open - the user zoomed into the dialog
 */	
static int liqpostcard_sendprogress_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_sendprogress dialog_close - the dialog was closed
 */	
static int liqpostcard_sendprogress_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_sendprogress widget shown - occurs once per lifetime
 */	
static int liqpostcard_sendprogress_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_sendprogress mouse - occurs all the time as you stroke the screen
 */	
static int liqpostcard_sendprogress_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_sendprogress click - occurs when a short mouse stroke occured
 */	
static int liqpostcard_sendprogress_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_sendprogress keypress - the user pressed a key
 */	
static int liqpostcard_sendprogress_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_sendprogress keyrelease - the user released a key
 */	
static int liqpostcard_sendprogress_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_sendprogress paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqpostcard_sendprogress_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqpostcard_sendprogress dynamic resizing
 */	
static int liqpostcard_sendprogress_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
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
	liqcell_setrect_autoscale( liqlist1, 160,58, 432,238, sx,sy);
	return 0;

}

/**	
 * liqpostcard_sendprogress.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_sendprogress)
{
    //liqcell_propseti(  liqpostcard_sendprogress, "sentok", 1 );
    liqcell_setvisible(  liqpostcard_sendprogress,0 );
	return 0;
}
/**	
 * liqpostcard_sendprogress_child_test_seek this function shows how to access members
 */	
	  
static void liqpostcard_sendprogress_child_test_seek(liqcell *self)
{	  
	liqcell *liqlist1 = liqcell_child_lookup(self, "liqlist1");
	liqcell *lblsentok = liqcell_child_lookup(self, "lblsentok");
	liqcell *lblfail = liqcell_child_lookup(self, "lblfail");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *title = liqcell_child_lookup(self, "title");
}	  
/**	
 * create a new liqpostcard_sendprogress widget
 */	
liqcell *liqpostcard_sendprogress_create()
{
    

    
	liqcell *self = liqcell_quickcreatewidget("liqpostcard_sendprogress", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqpostcard_sendprogress'"); return NULL;  } 
	
    
    
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# liqlist1:liqlist
    
    liqcell *liqlistactual = liqcell_quickcreatevis("liqlistactual", "liqlist", 0,0,-1,-1);
    
	liqcell *liqlist1 = liqcell_quickcreatevis("liqlist1", NULL, 160, 58, 432, 238);
	liqcell_setcontent(  liqlist1,liqlistactual);
	liqcell_child_append(  self, liqlist1);
    
    liqcell_handleradd_withcontext(liqlist1,    "click",   liqcell_easyhandler_content_zoom_click,self);
    
    
    
	//############################# lblsentok:label
	liqcell *lblsentok = liqcell_quickcreatevis("lblsentok", "label", 146, 302, 488, 48);
	liqcell_setfont(	lblsentok, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(lblsentok, "Sent ok, proceed." );
	liqcell_propsets(  lblsentok, "textcolor", "rgb(0,192,0)" );
	liqcell_propsets(  lblsentok, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lblsentok, "textalign",  2 );
    liqcell_propseti(  lblsentok, "textaligny", 2 );
	liqcell_child_append(  self, lblsentok);
	//############################# lblfail:label
	liqcell *lblfail = liqcell_quickcreatevis("lblfail", "label", 110, 302, 588, 48);
	liqcell_setfont(	lblfail, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(lblfail, "Send Failed, please try again." );
	liqcell_propsets(  lblfail, "textcolor", "rgb(192,0,0)" );
	liqcell_propsets(  lblfail, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  lblfail, "textalign", 2 );
	liqcell_child_append(  self, lblfail);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 472, 394, 328, 86);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Close" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
    liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 34, 12, 652, 48);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Sending message, please wait..." );
	liqcell_propsets(  title, "textcolor", "rgb(0,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
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


	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqpostcard_sendprogress_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqpostcard_sendprogress_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqpostcard_sendprogress_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqpostcard_sendprogress_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqpostcard_sendprogress_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqpostcard_sendprogress_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqpostcard_sendprogress_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqpostcard_sendprogress_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqpostcard_sendprogress_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqpostcard_sendprogress_dialog_close ,self);
	return self;
}

