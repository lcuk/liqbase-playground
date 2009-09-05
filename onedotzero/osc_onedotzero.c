
// osc connection and principle manager for communication



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>


#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>


//  http://liblo.sourceforge.net/docs/group__liblo.html

#include "lo/lo.h"


#include "osc_onedotzero.h"



char *osc_onedotzero_lastmsg = NULL;


//    osc_onedotzero_send_();

//#########################################################################
//#########################################################################
//######################################################################### osc globals
//#########################################################################
//#########################################################################



lo_address          osc_addr = NULL;                // sendind address record: for use with lo_send(osc_addr, "path", "struct", args.... );
lo_server_thread    osc_st   = NULL;                // listening server thread

char *              osc_send_ip     = NULL;         // address we are going to send data to.  this is the address osc_addr is linked with
char *              osc_send_port   = NULL;         // port    we are going to send data to.  this is the address osc_addr is linked with

char *              osc_listen_port = NULL;         // port that our listening thread will bind itself to


int osc_running =0;

int osc_modeinprogress = -1;

unsigned long osc_modelastsent_ticks = 0;

//#########################################################################
//#########################################################################
//#########################################################################
//#########################################################################
//#########################################################################

unsigned long osc_msglastsent = 0;
unsigned long osc_msglastrecv = 0;

int get_osc_onedotzero_lastmsg_isok()
{
	return (osc_msglastrecv-osc_msglastsent)>0;
}


char *get_osc_onedotzero_lastmsg()
{
	return osc_onedotzero_lastmsg;
}


    
int osc_onedotzero_send_menu_repeat_ping_if_required()
{
    unsigned long 	ft1=liqapp_GetTicks();
    
    if(osc_modeinprogress==-1)return -1;
    
    if((ft1-osc_modelastsent_ticks)>5000)
    {
        liqapp_log("osc: sending /menu %i  RT: !",osc_modeinprogress);
        osc_modelastsent_ticks=ft1;
        lo_send(osc_addr, "/menu", "i",  osc_modeinprogress);
    }
}
//#########################################################################
int osc_onedotzero_send_closeapp()
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send closeapp");
        return -1;
    }
    liqapp_log("osc: sending /closeapp");
    
    //usage: user closed the app
    //address path: /closeapp
    //param: int (mode number 1,2,3)
	lo_send(osc_addr, "/closeapp", "i",  0);
    return 0;
}

//#########################################################################
int osc_onedotzero_send_entermsg()
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send entermsg");
        return -1;
    }
    liqapp_log("osc: sending /entermsg");
    
    //usage: user clicked on the cover screen and entered the application
    //address path: /entermsg
    //param: int (mode number 1,2,3)
	lo_send(osc_addr, "/entermsg", "i",  0);
    return 0;
}

//#########################################################################
int osc_onedotzero_send_menuscreen()
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send menuscreen");
        return -1;
    }
    liqapp_log("osc: sending /menuscreen");
    
    //usage: user clicked on the cover screen and entered the application
    //address path: /entermsg
    //param: int (mode number 1,2,3)
	lo_send(osc_addr, "/menuscreen", "i",  0);
    return 0;
}

//#########################################################################
int osc_onedotzero_send_menu(int modenum)
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send menu");
        return -1;
    }
    liqapp_log("osc: sending /menu %i",modenum);
    
    osc_modeinprogress=modenum;
    osc_modelastsent_ticks = liqapp_GetTicks();
    //usage: user clicks on one of the frontend menus
    //address path: /mode
    //param: int (mode number 1,2,3)
	lo_send(osc_addr, "/menu", "i",  modenum);
    return 0;
}
//#########################################################################

int osc_onedotzero_send_menufinished(int modenum)
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send menufinished");
        return -1;
    }
    liqapp_log("osc: sending /menufinished %i",modenum);
    osc_modeinprogress=-1;
    //usage: user closes one of the interactions
    //address path: /modefinished
    //param: int (mode number 1,2,3)
	lo_send(osc_addr, "/menufinished", "i",  modenum);
    
    
    // now interally call the menuscreen fn
    osc_onedotzero_send_menuscreen();
    
    return 0;
}

//#########################################################################

int osc_onedotzero_send_zoom(char *zoomname,float zoom)
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send zoom");
        return -1;
    }
    liqapp_log("osc: sending /zoom '%s',%f",zoomname,zoom);

    //usage: user closes one of the interactions
    //address path: /modefinished
    //param: int (mode number 1,2,3)
	lo_send(osc_addr, "/zoom", "sf",  zoomname,zoom);
    
    
    // now interally call the menuscreen fn
    osc_onedotzero_send_menuscreen();
    
    return 0;
}


//#########################################################################

int osc_onedotzero_send_newmsg(char *msg)
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send newmsg");
        return -1;
    }
	
	if(osc_onedotzero_lastmsg)free(osc_onedotzero_lastmsg);
	
	osc_onedotzero_lastmsg=strdup(msg);


    liqapp_log("osc: sending /newmsg %s",msg);


    osc_msglastsent = liqapp_GetTicks();
    osc_msglastrecv = liqapp_GetTicks();


	
    //usage: User submits a new message to be displayed
    //address path: /newmsg
    //param: string (new message submission, max. 140 chars)
	lo_send(osc_addr, "/newmsg", "s", msg);
    return 0;
}

//#########################################################################

int osc_onedotzero_send_acc(float x,float y,float z)
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send acc");
        return -1;
    }
    
    liqapp_log("osc: sending /acc %f,%f,%f",x,y,z);

    //usage: sending accelerometer data
    //address path: /acc
    //param: 3 floats (pitch, heading, roll - XYZ accelerometer values)	
        
	lo_send(osc_addr, "/acc", "fff", x,y,z);
    return 0;
}

//#########################################################################

int osc_onedotzero_send_shake(float x,float y,float z,float rumble)
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send rumble");
        return -1;
    }
    liqapp_log("osc: sending /rumble %f,%f,%f,%f",x,y,z,rumble);

    //usage: sending accelerometer data
    //address path: /acc
    //param: 3 floats (pitch, heading, roll - XYZ accelerometer values)	
        
	lo_send(osc_addr, "/rumble", "ffff", x,y,z,rumble);
    return 0;
}


//#########################################################################

int osc_onedotzero_send_touch(float x,float y)
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send touch");
        return -1;
    }
    liqapp_log("osc: sending /touch %f,%f",x,y);
    //usage: user touches screen to "distort"/disrupt the currently projected message
    //address path: /touch
    //param: 2 floats (XY coord of touch position)

	lo_send(osc_addr, "/touch", "ff", x,y);
    return 0;
}

//#########################################################################

int osc_onedotzero_send_touchoff()
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send touchoff");
        return -1;
    }
    liqapp_log("osc: sending /touchoff");
    //usage: user released screen
    //address path: /touchoff
    //param: none
	
//liqapp_log("sending touchoff");
	lo_send(osc_addr, "/touchoff", "");
//liqapp_log("sent touchoff");
    return 0;
}

//#########################################################################

int osc_onedotzero_send_panic()
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send panic");
        return -1;
    }
	
    liqapp_log("osc: sending /panic");
    //usage: panic mode - kills the currently displayed message
    //address path: /panic
    //param: none
	lo_send(osc_addr, "/panic", "");
    return 0;
}

//#########################################################################
//#########################################################################
//######################################################################### osc tests
//#########################################################################
//#########################################################################


int osc_onedotzero_send_runtests()
{

	osc_onedotzero_send_menu(1);
    osc_onedotzero_send_newmsg("hello world!");
    osc_onedotzero_send_acc(5.55,8.88,5.55);
    osc_onedotzero_send_touch(123,456);
    osc_onedotzero_send_touchoff();
    osc_onedotzero_send_panic();
    
    return 0;
	
}
//#########################################################################
//#########################################################################
//#########################################################################
//#########################################################################
//#########################################################################








//#########################################################################
//#########################################################################
//######################################################################### osc recv event handlers
//#########################################################################
//#########################################################################



void osc_onedotzero_error(int num, const char *msg, const char *path)
{
    liqapp_log("osc: liblo server error %d in path '%s': '%s'", num, path, msg);
}


int osc_onedotzero_handler_ping(const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data)
{
    liqapp_log("osc: ping handler, we should respond with pong.");
    lo_send(osc_addr, "/pong", "");
    return 0;
}

int osc_onedotzero_handler_msgok(const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data)
{
    liqapp_log("osc: msgok, mark recv flag");
    osc_msglastrecv = liqapp_GetTicks();
    
    return 0;
}


//#########################################################################
//#########################################################################
//######################################################################### principle initialization
//#########################################################################
//#########################################################################



int osc_onedotzero_init()
{

    liqapp_log("osc: init start");
    
    
    liqapp_log("osc: init reading preferences from ~/.liqbase/liqbase.prefs");
    
 	osc_send_ip   = liqapp_pref_getvalue("osc_send_ip");   
    if((!osc_send_ip) || (!*osc_send_ip))
    {
        liqapp_log("osc: init liqbase.prefs: osc_send_ip not valid, using default (224.0.0.1)");
        osc_send_ip = "224.0.0.1";
    }

	osc_send_port = liqapp_pref_getvalue("osc_send_port");
    if((!osc_send_port) || (!*osc_send_port))
    {
        liqapp_log("osc: init liqbase.prefs: osc_send_port not valid, using default (7770)");
        osc_send_port = "7770";
    }
    

	osc_listen_port = liqapp_pref_getvalue("osc_listen_port");
    if((!osc_listen_port) || (!*osc_listen_port))
    {
        liqapp_log("osc: liqbase.prefs: osc_listen_port not valid, using default (7771)");
        osc_listen_port = "7771";
    }
    
    osc_send_ip     = strdup(osc_send_ip);
    osc_send_port   = strdup(osc_send_port);
    osc_listen_port = strdup(osc_listen_port);
    
    liqapp_log("osc: init : osc_send_ip     '%s'",osc_send_ip);
    liqapp_log("osc: init : osc_send_port   '%s'",osc_send_port);
    liqapp_log("osc: init : osc_listen_port '%s'",osc_listen_port);
   
    
    
	//#####################################
    liqapp_log("osc: init creating send address");
	osc_addr = lo_address_new((osc_send_ip), (osc_send_port) );
	if(osc_addr==NULL)
	{
        liqapp_log("osc: init ERROR, could not create send address");
        return -1;
	}
    
    
    //#####################################
    liqapp_log("osc: init creating recv thread");
    osc_st = lo_server_thread_new( (osc_listen_port), osc_onedotzero_error);
	if(osc_st==NULL)
	{
        liqapp_log("osc: init ERROR, could not create recv thread");
        return -1;
	}
    
    //#####################################
    liqapp_log("osc: init binding methods to recv thread");
   
    //lo_server_thread_add_method(osc_st, NULL, NULL, generic_handler, NULL);
    //lo_server_thread_add_method(osc_st, "/foo/bar", "fi", foo_handler, NULL);
    //lo_server_thread_add_method(osc_st, "/quit", "", quit_handler, NULL);
    lo_server_thread_add_method(osc_st, "/ping", "", osc_onedotzero_handler_ping, NULL);
	
    lo_server_thread_add_method(osc_st, "/msgok", "", osc_onedotzero_handler_msgok, NULL);
	
    //#####################################
    liqapp_log("osc: init recv thread starting");

    lo_server_thread_start(osc_st);

    liqapp_log("osc: init ready now");
 
    osc_running=1;
    return 0;
}



//#########################################################################
//#########################################################################
//#########################################################################
//#########################################################################
//#########################################################################

int osc_onedotzero_close()
{
    liqapp_log("osc: closing");
    osc_running=0;
    //
    if(osc_st)
    {
        lo_server_thread_stop(osc_st);
        lo_server_thread_free(osc_st);
        osc_st=NULL;
    }
    if(osc_addr)
    {
        lo_address_free(osc_addr);
        osc_addr=NULL;
    }
    liqapp_log("osc: closed");
}












