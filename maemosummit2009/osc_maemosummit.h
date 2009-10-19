#ifndef OSC_ONEDOTZERO_H
#define OSC_ONEDOTZERO_H


#include "lo/lo.h"

//#########################################################################
//#########################################################################
//######################################################################### principle initialization
//#########################################################################
//#########################################################################



int osc_onedotzero_init();
int osc_onedotzero_close();



//#########################################################################
//#########################################################################
//######################################################################### osc recv event handlers
//#########################################################################
//#########################################################################



void osc_onedotzero_error(int num, const char *msg, const char *path);
int  osc_onedotzero_handler_ping(const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data);



//#########################################################################
//#########################################################################
//######################################################################### osc onedotzero specific send methods
//#########################################################################
//#########################################################################

char *get_osc_onedotzero_lastmsg();

int get_osc_onedotzero_server_playstate();

int osc_onedotzero_send_entermsg();
int osc_onedotzero_send_menu_repeat_ping_if_required();
int osc_onedotzero_send_menu(int modenum);
int osc_onedotzero_send_menufinished(int modenum);
int osc_onedotzero_send_playstatecmd(int playing);
int osc_onedotzero_send_newmsg(char *msg);
int osc_onedotzero_send_menuscreen();
int osc_onedotzero_send_acc(float x,float y,float z);
int osc_onedotzero_send_zoom(char *zoomname,float zoom);

int osc_onedotzero_send_shake(float x,float y,float z,float rumble);
int osc_onedotzero_send_touch(float x,float y);
int osc_onedotzero_send_touchoff();
int osc_onedotzero_send_panic();
int osc_onedotzero_send_runtests();


//#########################################################################
//#########################################################################
//#########################################################################
//#########################################################################
//#########################################################################


#endif

