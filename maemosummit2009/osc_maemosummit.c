
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


#include "osc_maemosummit.h"



liqcell *osc_userlist=NULL;




// osc command spec
// first thing a machine should do on wakeup is shout
// "/hello/n900-1/gary"
// this shows that the n900-1 machine woke up and has gary as the active user

// the MASTER machine should respond at that point
// "/master/home-gb/jacob
// other clients should ignore this signal

// if no response obtained, try again 5 sec later
// if no response after 3 attempts then this machine becomes the master
// a new master machine will call 
// "/newmaster

// all clients are meant to respond to this and to reset their knowledge of who the master is
//

// the master is in charge of clients then
// there are a number of users who are registered with the master

// every 5 seconds machines wakeup and say "/hey/n900-1/gary"
// which indicates that it has woken up.









static liqcell *oscuser_find(char *username)
{
	if(osc_userlist==NULL)  osc_userlist = liqcell_quickcreatevis("osc_userlist",NULL,0,0,800,480);
	
	liqcell *u = liqcell_child_lookup(osc_userlist,username);
	
    return u;

}











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

//#########################################################################
int osc_maemosummit_send_menuscreen()
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

int osc_maemosummit_send_newmsg(char *msg)
{
    if((!osc_addr) || (osc_running==0))
    {
        liqapp_log("osc: no addr, cannot send newmsg");
        return -1;
    }
	
    liqapp_log("osc: sending /newmsg %s",msg);

	
    //usage: User submits a new message to be displayed
    //address path: /newmsg
    //param: string (new message submission, max. 140 chars)
	lo_send(osc_addr, "/newmsg", "s", msg);
    return 0;
}



//#########################################################################

int osc_maemosummit_send_touch(float x,float y)
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

	lo_send(osc_addr, "/touch", "sff",app.username, x,y);
    return 0;
}

//#########################################################################

int osc_maemosummit_send_touchoff()
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
	lo_send(osc_addr, "/touchoff", "s",app.username);
//liqapp_log("sent touchoff");
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



void osc_maemosummit_error(int num, const char *msg, const char *path)
{
    liqapp_log("osc: liblo server error %d in path '%s': '%s'", num, path, msg);
}


int osc_maemosummit_handler_ping(const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data)
{
    liqapp_log("osc: ping handler, we should respond with pong.");
    lo_send(osc_addr, "/pong", "");
    return 0;
}


int osc_maemosummit_handler_sketchdrawnew(const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data)
{
    liqapp_log("osc: got sketchdrawnew");

char *arguser = argv[0]->s; 
int   argw = argv[1]->i;
int   argh = argv[2]->i;       
    return 0;
}


int osc_maemosummit_handler_sketchdrawmove(const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data)
{
    liqapp_log("osc: got sketchdrawmove");

char *arguser = argv[0]->s;
int   argx = argv[1]->i;
int   argy = argv[2]->i;    
    
    return 0;
}

int osc_maemosummit_handler_sketchdrawup(const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data)
{
    liqapp_log("osc: got sketchdrawup");

char *arguser = argv[0]->s;
int   argx = argv[1]->i;
int   argy = argv[2]->i;    
    
    return 0;
}
//#########################################################################
//#########################################################################
//######################################################################### principle initialization
//#########################################################################
//#########################################################################



int osc_maemosummit_init()
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
    osc_st = lo_server_thread_new( (osc_listen_port), osc_maemosummit_error);
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
    lo_server_thread_add_method(osc_st, "/ping", "", osc_maemosummit_handler_ping, NULL);
	
   // lo_server_thread_add_method(osc_st, "/msgok", "", osc_maemosummit_handler_msgok, NULL);

    lo_server_thread_add_method(osc_st, "/sketchdrawnew", "", osc_maemosummit_handler_sketchdrawnew, NULL);
    lo_server_thread_add_method(osc_st, "/sketchdrawmove", "", osc_maemosummit_handler_sketchdrawmove, NULL);
    lo_server_thread_add_method(osc_st, "/sketchdrawup", "", osc_maemosummit_handler_sketchdrawup, NULL);	
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

int osc_maemosummit_close()
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
    return 0;
}












