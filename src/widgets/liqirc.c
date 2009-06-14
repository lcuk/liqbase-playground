// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_dllcache.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqcell_arrange.h>


int liqirc_runchannel(liqcell *liqirc);


	static int timer_tick(liqcell *self, liqcellmouseeventargs *args, void *context)
	{
		liqcell_propseti(self,"timerinterval", 32767 );
		liqcell_setenabled(self,0);
		// now, run the channel? :D
		liqirc_runchannel((liqcell*)self->tag);
		
		return 0;
	}



/**	
 * liqirc widget dynamic resizing
 */	
static int liqirc_resize(liqcell *self,liqcelleventargs *args, void *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"list1"), 4,56, 790,368, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"listback"), -2,12, 790,228, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"listitem"), -2,18, 790,40, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"listitemicon"), 56,2, 34,32, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"listitemtime"), 4,4, 50,28, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"listitemnick"), 94,4, 106,28, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"listitemmessage"), 202,4, 582,28, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"buttonback"), 8,432, 202,42, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"buttonchannels"), 328,432, 178,42, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"icon"), 6,8, 52,40, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"title"), 66,8, 728,40, sx,sy);
	return 0;
}

/**	
 * create a new liqirc widget
 */	
liqcell *liqirc_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqirc", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqirc'"); return NULL;  } 
	
	//############################# buttonchannels:commandbutton
	liqcell *buttonchannels = liqcell_quickcreatevis("buttonchannels", "commandbutton", 328, 432, 178, 42);
	liqcell_setfont(	buttonchannels, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(buttonchannels, "list channels" );
	//liqcell_propsets(  buttonchannels, "backcolor", "rgb(235,233,237)" );
	liqcell_child_append(  self, buttonchannels);
	//############################# buttonback:commandbutton
	liqcell *buttonback = liqcell_quickcreatevis("buttonback", "commandbutton", 8, 432, 202, 42);
	liqcell_setfont(	buttonback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(buttonback, "Back" );
	//liqcell_propsets(  buttonback, "backcolor", "rgb(235,233,237)" );
	liqcell_child_append(  self, buttonback);
	//############################# list1:picturebox
	liqcell *list1 = liqcell_quickcreatevis("list1", "picturebox", 4, 56, 790, 368);
	liqcell_setfont(	list1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_propsets(  list1, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  list1, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  list1, "bordercolor", "rgb(200,100,100)" );
		//############################# listback:picturebox
		liqcell *listback = liqcell_quickcreatevis("listback", "picturebox", -2, 12, 790, 228);
		liqcell_setfont(	listback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_propsets(  listback, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  listback, "backcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  listback, "bordercolor", "rgb(200,100,100)" );


/*			//############################# listitem:picturebox
			liqcell *listitem = liqcell_quickcreatevis("listitem", "picturebox", -2, 18, 790, 40);
			liqcell_setfont(	listitem, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
			liqcell_propsets(  listitem, "textcolor", "rgb(0,0,0)" );
			liqcell_propsets(  listitem, "backcolor", "rgb(0,0,0)" );
			liqcell_propsets(  listitem, "bordercolor", "rgb(200,100,100)" );
				//############################# listitemicon:picturebox
				liqcell *listitemicon = liqcell_quickcreatevis("listitemicon", "picturebox", 56, 2, 34, 32);
				liqcell_setfont(	listitemicon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				liqcell_propsets(  listitemicon, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  listitemicon, "backcolor", "rgb(192,255,192)" );
				liqcell_propsets(  listitemicon, "bordercolor", "rgb(200,100,100)" );
				liqcell_child_append(  listitem, listitemicon);
				//############################# listitemmessage:label
				liqcell *listitemmessage = liqcell_quickcreatevis("listitemmessage", "label", 202, 4, 582, 28);
				liqcell_setfont(	listitemmessage, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(listitemmessage, "message" );
				liqcell_propsets(  listitemmessage, "textcolor", "rgb(255,255,255)" );
				liqcell_propsets(  listitemmessage, "backcolor", "rgb(0,64,64)" );
				liqcell_propseti(  listitemmessage, "textalign", 0 );
				liqcell_child_append(  listitem, listitemmessage);
				//############################# listitemnick:label
				liqcell *listitemnick = liqcell_quickcreatevis("listitemnick", "label", 94, 4, 106, 28);
				liqcell_setfont(	listitemnick, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(listitemnick, "nick" );
				liqcell_propsets(  listitemnick, "textcolor", "rgb(255,255,255)" );
				liqcell_propsets(  listitemnick, "backcolor", "rgb(0,64,0)" );
				liqcell_propseti(  listitemnick, "textalign", 0 );
				liqcell_child_append(  listitem, listitemnick);
				//############################# listitemtime:label
				liqcell *listitemtime = liqcell_quickcreatevis("listitemtime", "label", 4, 4, 50, 28);
				liqcell_setfont(	listitemtime, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(listitemtime, "00:00" );
				liqcell_propsets(  listitemtime, "textcolor", "rgb(255,255,255)" );
				liqcell_propsets(  listitemtime, "backcolor", "rgb(0,64,0)" );
				liqcell_propseti(  listitemtime, "textalign", 0 );
				liqcell_child_append(  listitem, listitemtime);
			liqcell_child_append(  listback, listitem);
 */



			liqcell_child_arrange_easycol(  listback );
			
			liqcell_handleradd(listback,    "mouse",   liqcell_easyhandler_kinetic_mouse );

		liqcell_child_append(  list1, listback);
	liqcell_child_append(  self, list1);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 66, 8, 728, 40);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "freenode.net :: lcuk_bot on #liqbase" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 6, 8, 52, 40);
	liqcell_setfont(	icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(icon, "icon" );
	liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);
	//############################# timer1:liqtimer
	liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
	// store ourselves on the tag for use later
	// this does feel like a workaround, but hell, it works!
	liqcell_settag(timer1,liqcell_hold(self));
	liqcell_propseti(timer1,"timerinterval", 1 );
	liqcell_handleradd(timer1,"timertick",timer_tick);
	liqcell_setenabled(timer1,1);
	liqcell_child_insert( self,timer1);
	

	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd(self, "resize", liqirc_resize );
	return self;
}


void liqirc_showmsg(liqcell *self,char *time,char *nick,char *message)
{
	// add a new listitem into the flow
	// reflow
	// adjust the top position of the backport to compensate

	//liqapp_log("irc showmsg == %s",self->name);

	//############################# list1:picturebox
	liqcell *list1 = liqcell_child_lookup( self,"list1");
		//############################# listback:picturebox
		liqcell *listback =liqcell_child_lookup( list1,"listback");
			//############################# listitem:picturebox
			liqcell *listitem = liqcell_quickcreatevis("listitem", "picturebox", 0, 0, 790, 28);
			//liqcell_setfont(	listitem, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
			//liqcell_propsets(  listitem, "textcolor", "rgb(0,0,0)" );
			//liqcell_propsets(  listitem, "backcolor", "rgb(0,0,0)" );
			//liqcell_propsets(  listitem, "bordercolor", "rgb(200,100,100)" );
				//############################# listitemicon:picturebox
				//liqcell *listitemicon = liqcell_quickcreatevis("listitemicon", "picturebox", 56, 2, 34, 32);
				//liqcell_setfont(	listitemicon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				//liqcell_propsets(  listitemicon, "textcolor", "rgb(0,0,0)" );
				//liqcell_propsets(  listitemicon, "backcolor", "rgb(192,255,192)" );
				//liqcell_propsets(  listitemicon, "bordercolor", "rgb(200,100,100)" );
				//liqcell_child_append(  listitem, listitemicon);
				//############################# listitemmessage:label
				liqcell *listitemmessage = liqcell_quickcreatevis("listitemmessage", "label", 202, 0, 582, 28);
				liqcell_setfont(	listitemmessage, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(listitemmessage, message );
				//liqcell_propsets(  listitemmessage, "textcolor", "rgb(255,255,255)" );
				//liqcell_propsets(  listitemmessage, "backcolor", "rgb(0,64,64)" );
				//liqcell_propseti(  listitemmessage, "textalign", 0 );
				liqcell_child_append(  listitem, listitemmessage);
				//############################# listitemnick:label
				liqcell *listitemnick = liqcell_quickcreatevis("listitemnick", "label", 94, 0, 106, 28);
				liqcell_setfont(	listitemnick, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(listitemnick, nick );
				//liqcell_propsets(  listitemnick, "textcolor", "rgb(255,255,255)" );
				//liqcell_propsets(  listitemnick, "backcolor", "rgb(0,64,0)" );
				//liqcell_propseti(  listitemnick, "textalign", 0 );
				liqcell_child_append(  listitem, listitemnick);
				//############################# listitemtime:label
				liqcell *listitemtime = liqcell_quickcreatevis("listitemtime", "label", 4, 0, 50, 28);
				liqcell_setfont(	listitemtime, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(listitemtime, time );
				//liqcell_propsets(  listitemtime, "textcolor", "rgb(255,255,255)" );
				//liqcell_propsets(  listitemtime, "backcolor", "rgb(0,64,0)" );
				//liqcell_propseti(  listitemtime, "textalign", 0 );
				liqcell_child_append(  listitem, listitemtime);
			liqcell_child_append(  listback, listitem);
			liqcell_child_arrange_easycol(  listback );
			if(listback->h <= list1->h)
			{
				listback->y=0;
			}
			else
			{
				listback->y=-(listback->h - list1->h);
			}
			
			//liqcell_child_append(  listback, listitem);
		//liqcell_child_append(  list1, listback);
	//liqcell_child_append(  self, list1);
	liqcell_setdirty(  self, 1);
}





//http://www.codersnet.org/dev/ircbot.c

//http://www.google.co.uk/search?hl=en&q=c+irc+ping+define+socket&btnG=Search&meta=


/*    
    IRC-Bot by CodersNet dev-com
    
    IRC-Bot is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    IRC-Bot is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with IRC-Bot; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA    02111-1307    USA
*/

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <string.h>
#include <sys/sysinfo.h>

// Configuration
#define server "irc.freenode.net"
#define port 6667
//#define nick "lcuk_bot"
char nick[64];
#define realname "lcuk_bot"
#define afterconnectstring "join #liqbase-test"
#define debug 1
// list of commands after connection..
#define performfile "connect.irc.script"
// Configuration end

// Some global things

void splitline();
void parseline();
void handle_privmsg();
void ircbot_shutdown();
void sendserv(char *str, ...);
char *instr(char *string,char *match);

char linebuf[1024];
char largs[30][1024];
char linesendernick[256];


int sock=0,argc,connected;
FILE *in, *out;

// Our main routine
int liqirc_runchannel(liqcell *liqirc)
{
	srand ( time(NULL) );

	snprintf(nick,sizeof(nick),"lcuk_bot_%i",rand() % 32767);
	
	
    struct sockaddr_in 		sck;
    struct hostent *		hent;
    
    printf("IRC-Bot by CodersNet dev-com started successfully.\n");
    printf("Trying to connect to %s on port %d,\n",server,port);
    printf("using %s as my nick and %s as my realname.\n\n",nick,realname);
    
    connected = 0;
    
    memset((char *)&sck, 0, sizeof(sck));
    hent=gethostbyname(server);
	
    if(hent == NULL)
    {
        printf("ERROR: Unable to reach this host!\n");
        exit(0);
    }
	
    if(debug)
    {
        printf("Host reached sucessfully!\n");
    }
    
    memcpy((char *)&sck.sin_addr,hent->h_addr,hent->h_length);
    sck.sin_family=hent->h_addrtype;
    sck.sin_port=htons(port);
    sock=socket(PF_INET,SOCK_STREAM,0);
	
    if (sock < 0)
    {
        printf("ERROR: Couldn't create socket!\n");
        exit(0);
    }
	
    if (debug)
	{
        printf("Socket created sucessfully!\n");
    }
	
	
	
    
    if (connect(sock,(struct sockaddr *)&sck,sizeof(sck)) < 0)
    {
        printf("ERROR: Couldn't connect!\n");
        exit(0);
    }
	
    printf("Connected successfully!\n");

    in=fdopen(sock,"r");
    out=fdopen(sock,"w");

    sendserv("NICK %s",nick);
    sendserv("USER %s \"\" \"%s\" :%s",nick,server,realname);
    if (debug)
    {
        printf("Sent identification data!\n");
    }
    
    do
    {
        fgets(linebuf,512,in);
        splitline(liqirc);
        parseline(liqirc);
    }
    while(linebuf[0]!='\0');
    
    printf("For some reason I got disconnected. Shutting down.\n");
    printf("Last line received was: %s\n",linebuf);
    ircbot_shutdown();
    return 0;
}

// Close the socket and terminate
void ircbot_shutdown()
{
    fclose(in);
    fclose(out);
    close(sock);
    exit(0);
}

// Split a received line to be able to parse it through parseline();
void splitline(liqcell *liqirc)
{
    char *p; int i=0,c=0;
    p=&linebuf[0]; argc=0;
    for(;((*p!='\n') && (*p!='\0') && (*p!='\r') && (argc<28));p++)
    {
        if (c==0 && *p==' ')
		{
            largs[argc][i]='\0';
            argc++; i=0;
            while(*(p+1)==' ') { c++; }
        }
		else
		{
            if (c==0 && *p==':' && i==0 && argc>1)
		    {
                c=1;
            }
		    else
		    {
                largs[argc][i]=*p;
                i++;
            }
        }
    }
    largs[argc][i]='\0';
    argc++;
	
	
	char *n0 = largs[0];
	if(*n0==':')n0++;
	
		memset(linesendernick, 0, sizeof(linesendernick));
	
		strncpy(linesendernick, n0,sizeof(linesendernick)-1);
		
		
		char *t=linesendernick;
		while(*t)
		{
			if(*t=='!'){ *t=0; break; }
			t++;
		}
	
}

// largs[1] => command name only
// largs[X] => parameter X of this command
// linebuf => whole data line
void parseline(liqcell *liqirc)
{
    if (debug)
    {
        printf("Got data: %s",linebuf);
    }

	//void liqirc_showmsg(liqcell *liqirc,char *time,char *nick,char *message);
	
	
	liqirc_showmsg(liqirc,"00:00","msg",linebuf);
	
    /* NOTICE AUTH :*** Looking up your hostname */
    if (!strcmp(largs[0],"NOTICE") && !strcmp(largs[1],"AUTH"))
    {
        // Normally nothing to do here!
        return;
    }
    /* PING :1541680430 */
    else if (!strcmp(largs[0],"PING"))
    {
        sendserv("PONG %s",largs[1]);
        printf("Ping Pong!\n");
        return;
    }
    /* ERROR :Your host is trying to (re)connect too fast -- throttled */
    else if (!strcmp(largs[0],"ERROR"))
    {
        printf("!!! RECEIVED AN IRC-ERROR, SHUTTING DOWN !!!\n");
	    printf("Last line received was: %s\n",linebuf);
        ircbot_shutdown();
    }
    /* Gerrit!Gerrit@CodersNet PRIVMSG #ircbot :hello IRC-Bot :) */
    else if (!strcmp(largs[1],"PRIVMSG"))
    {

		
        handle_privmsg();
    }
	
	
	// command is broken down
	// "[Command] [args]"
	// ":[server] [commandindex] [args]
	
	
	
	
	
    /* :irc.de.eu.codersnet.org 376 IRC-Bot :End of /MOTD command. */
    else if (!strcmp(largs[1],"376"))
    {
        // We got the end of the MOTD, assume we're connected now
        printf("Got MOTD, connection successful!\n");
        connected = 1;
		
		sendserv(afterconnectstring);
		
        //run_perform();
    }
    else
    {
        if (debug)
		{
        //    printf("WARNING: Unable to parse command '%s' : %s",largs[1],linebuf);
        }
        return;
    }
}



// Send a command through our socket to the IRC-Server
void sendserv(char *str, ...)
{
	if(!sock)return;
	
	
	
    va_list tmpl;
    char tmp[1024];

    va_start(tmpl,str);
    vsprintf(tmp,str,tmpl);
    strcat(tmp,"\r\n");
    send(sock,tmp,strlen(tmp),0);
    if (debug)
    {
        printf("Sending data: %s\n",tmp);
    }
    va_end(tmpl);
}



// largs[0] => mask of the user
// largs[2] => channel name
// largs[3] => privmsg text
void handle_privmsg()
{
    struct sysinfo s_info;
    int error;

	//return;
	
	char *replyto;
	
	if(largs[2][0]=='#')
	{
		// channel message
		replyto = largs[2];
	}
	else
	{
		// private message
		replyto = linesendernick;
	}
	
	
    if(strcmp(replyto,nick)==0)
    {
		// this is my own message bouncing..!
		return;
    }
		

    if (debug)
    {
        printf("Got privmsg for command handling: '%s',   '%s',   '%s',   '%s'\n", largs[0], largs[1], largs[2], largs[3]);
    }
	
    /* Handle my commands here */    
    //if (!strncmp(largs[3], "wtf", 3))
	
    if(strcmp(largs[3], "marco")==0)
    {
		// i should be sending this back to the person who asked..
        sendserv("PRIVMSG %s :Polo!",replyto);// largs[0]);
    }
	
    if( instr(largs[3], "bacon") )
    {
		// i should be sending this back to the person who asked..
        sendserv("PRIVMSG %s :mmmmm bacon!",replyto);// largs[0]);
    }
}











































//#########################################################
//lcuk: instr, standard string handling, should find real home for this
//#########################################################
char *instr(char *string,char *match)
{
	if(!string) return NULL;
	if(!match) return string;
	// return pointer to the match or NULL
	while(*string)
	{
		char *indat = string;
		char *inpat = match;
		while(*indat && *inpat && *indat==*inpat)
		{
			indat++;
			inpat++;
		}
		if(*inpat==0)
		{
			// we found a match at this location
			return string;
		}
		// no match, advance string and loop
		string++;
	}
	return NULL;
}
