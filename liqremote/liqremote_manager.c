

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <string.h>
#include <sys/sysinfo.h>



#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_dllcache.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqcell_arrange.h>


#define server "10.0.0.1"
#define port 17585


#define liqsocket_state_closed     0
#define liqsocket_state_connecting 1
#define liqsocket_state_connected  2
#define liqsocket_state_closing    3
#define liqsocket_state_error     -1

void liqremote_sendserv(liqcell *liqremote,char *str, ...)
{
	
	int socket_state = liqcell_propgeti(liqremote,"socket_state",0);	
	if(socket_state != liqsocket_state_connected)
	{
		liqapp_log("liqremote_sendserv: cannot send, not connected");
		return;
	}
	int socket_sock = liqcell_propgeti(liqremote,"socket_sock",0);	
	if(!socket_sock)
	{
		liqapp_log("liqremote_sendserv: cannot send, no sock");
		return;
	}
	
	
	
    va_list tmpl;
    char tmp[1024];

    va_start(tmpl,str);
    vsnprintf(tmp,1020,str,tmpl);
    liqapp_log("liqremote_connect: sending data: '%s'",tmp);
    strcat(tmp,"\r\n");
    send(socket_sock,tmp,strlen(tmp),0);
    va_end(tmpl);
}



int liqremote_close(liqcell *liqremote)
{
int sock=0,argc,connected;
	//srand ( time(NULL) );
	//snprintf(nick,sizeof(nick),"lcuk_bot_%i",rand() % 32767);
	
	
	int socket_state = liqcell_propgeti(liqremote,"socket_state",0);
	

	if(socket_state == liqsocket_state_closed)
	{
		liqapp_log("liqremote_close: cannot close, already closed");
		return 0;
	}
	socket_state = liqcell_propseti(liqremote,"socket_state", liqsocket_state_closing);

	int socket_sock = liqcell_propgeti(liqremote,"socket_sock",0);	
	if(!socket_sock)return;


    close(socket_sock);

	socket_state = liqcell_propseti(liqremote,"socket_state", liqsocket_state_closed );
	
	liqcell_propseti(liqremote,"socket_sock",0);

}


// Our main routine
int liqremote_connect(liqcell *liqremote)
{
int sock=0;
	//srand ( time(NULL) );
	//snprintf(nick,sizeof(nick),"lcuk_bot_%i",rand() % 32767);
	
	//#############################################################
	liqapp_log("liqremote_connect: starting");
	
	int socket_state = liqcell_propgeti(liqremote,"socket_state",0);
	if(socket_state == liqsocket_state_error)
	{
		// just clear error for now, and try again
		socket_state = liqcell_propseti(liqremote,"socket_state", liqsocket_state_closed );
	}
	if(socket_state != liqsocket_state_closed)
	{
		liqapp_log("liqremote_connect: cannot open, socket not closed: %i",socket_state);
		return -1;
	}
		
	
	
	
	//#############################################################
	liqapp_log("liqremote_connect: getting properties");
		
char *argserver = liqcell_propgets(liqremote,"server","");
	if(!argserver || !*argserver)
	{
		liqapp_log("liqremote_connect: cannot open, expecting 'server' prop.s");
		return 0;
	}

int   argport = liqcell_propgeti(liqremote,"port",0);
	if(!argport)
	{
		liqapp_log("liqremote_connect: cannot open, expecting'port' prop.i");
		return 0;
	}
	
	
	
	

	//#############################################################

	liqapp_log("liqremote_connect: connecting");
	
	socket_state = liqcell_propseti(liqremote,"socket_state", liqsocket_state_connecting );
	liqcell_propseti(liqremote,"socket_sock",0);
	
    struct sockaddr_in 		sck;
    struct hostent *		hent;
     
    memset((char *)&sck, 0, sizeof(sck));
    hent=gethostbyname(argserver);
	
    if(hent == NULL)
    {
		socket_state = liqcell_propseti(liqremote,"socket_state", liqsocket_state_error );
        liqapp_log("liqremote_connect: cannot open, Unable to reach host: '%s'",argserver);
        return -1;
    }
	

	//#############################################################
    liqapp_log("liqremote_connect: got host: '%s'",server);

    
    memcpy((char *)&sck.sin_addr,hent->h_addr,hent->h_length);
    sck.sin_family=hent->h_addrtype;
    sck.sin_port=htons(argport);
    sock=socket(PF_INET,SOCK_STREAM,0);
	
    if (sock < 0)
    {
		socket_state = liqcell_propseti(liqremote,"socket_state", liqsocket_state_error );
        liqapp_log("liqremote_connect: cannot open, Couldn't create socket!");
        return -1;
    }
	

	//#############################################################
    liqapp_log("liqremote_connect: socket created sucessfully!");
    
    if (connect(sock,(struct sockaddr *)&sck,sizeof(sck)) < 0)
    {
		socket_state = liqcell_propseti(liqremote,"socket_state", liqsocket_state_error );
        liqapp_log("liqremote_connect: cannot open, Couldn't connect!");
        exit(0);
    }
	
    liqapp_log("liqremote_connect: Connected successfully!");
	socket_state = liqcell_propseti(liqremote,"socket_state", liqsocket_state_connected );
	liqcell_propseti(liqremote,"socket_sock",sock);

	
 	//#############################################################
    liqapp_log("liqremote_connect: Linked all connections!");
	
	
	//liqremote_sendserv(liqremote,"hello world!");
	
	
	char linebuf[1024]={0};
    do
    {
		

		linebuf[0]=0;
        int recv_size = recv(sock,linebuf,512,0);
		if(recv_size==0)
		{
			liqapp_log("liqremote_connect: invalid recv");
			
		}
		else
		{
			liqapp_log("liqremote_connect: got data: %i:'%s'",recv_size,linebuf);
		}

    }
    while(linebuf[0]!='\0');
    
	
	
 	//#############################################################
    liqapp_log("liqremote_connect: closing");


	
    //fclose(in);
    //fclose(out);
	
	
	liqremote_close(liqremote);
    //close(sock);
    return 0;
}
