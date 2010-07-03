// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>

#include <liqbase/md5.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqpostcard_config :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqpostcard_config widget refresh, all params set, present yourself to the user.
 */	
static int liqpostcard_config_refresh(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_config)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
    
    
	liqcell *liqbasepassword = liqcell_child_lookup(liqpostcard_config, "liqbasepassword");
	liqcell *liqbaseusername = liqcell_child_lookup(liqpostcard_config, "liqbaseusername");
	liqcell *twitteruserpass = liqcell_child_lookup(liqpostcard_config, "twitteruserpass");
	liqcell *twitterusername = liqcell_child_lookup(liqpostcard_config, "twitterusername");
    
    

	liqcell_setcaption(liqbaseusername,       app.username );
	liqcell_setcaption(liqbasepassword,       liqapp_pref_getvalue_def("userpass",  "") );

	liqcell_setcaption(twitterusername,    liqapp_pref_getvalue_def("twitname",    "") );
	liqcell_setcaption(twitteruserpass,    liqapp_pref_getvalue_def("twitpass",  "") );
	
    
    


	return 0;
}
/**	
 * liqpostcard_config dialog_open - the user zoomed into the dialog
 */	
static int liqpostcard_config_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_config)
{
    liqcell_handlerrun(liqpostcard_config,"refresh",NULL);
	return 0;
}
/**	
 * liqpostcard_config dialog_close - the dialog was closed
 */	
static int liqpostcard_config_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_config)
{
    liqcell_handlerrun(liqpostcard_config,"refresh",NULL);
	return 0;
}
/**	
 * liqpostcard_config widget shown - occurs once per lifetime
 */	
static int liqpostcard_config_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_config mouse - occurs all the time as you stroke the screen
 */	
static int liqpostcard_config_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_config click - occurs when a short mouse stroke occured
 */	
static int liqpostcard_config_click(liqcell *self, liqcelleventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_config keypress - the user pressed a key
 */	
static int liqpostcard_config_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_config keyrelease - the user released a key
 */	
static int liqpostcard_config_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqpostcard_config paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqpostcard_config_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqpostcard_config dynamic resizing
 */	
static int liqpostcard_config_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *liqbasepassword = liqcell_child_lookup(self, "liqbasepassword");
	liqcell *liqbaseusername = liqcell_child_lookup(self, "liqbaseusername");
	liqcell *twitteruserpass = liqcell_child_lookup(self, "twitteruserpass");
	liqcell *twitterusername = liqcell_child_lookup(self, "twitterusername");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *liqbasepasswordtitle = liqcell_child_lookup(self, "liqbasepasswordtitle");
	liqcell *liqbaseusernametitle = liqcell_child_lookup(self, "liqbaseusernametitle");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
	liqcell_setrect_autoscale( liqbasepassword, 230,188, 552,50, sx,sy);
	liqcell_setrect_autoscale( liqbaseusername, 230,108, 552,50, sx,sy);
	liqcell_setrect_autoscale( twitteruserpass, 230,348, 552,50, sx,sy);
	liqcell_setrect_autoscale( twitterusername, 230,268, 552,50, sx,sy);
	liqcell_setrect_autoscale( label2, 0,56, 800,30, sx,sy);
	liqcell_setrect_autoscale( liqbasepasswordtitle, 16,196, 228,32, sx,sy);
	liqcell_setrect_autoscale( liqbaseusernametitle, 16,116, 228,32, sx,sy);
	liqcell_setrect_autoscale( label1, 16,356, 228,32, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
	liqcell_setrect_autoscale( cmdsend, 574,418, 226,62, sx,sy);
	liqcell_setrect_autoscale( label5, 16,276, 228,32, sx,sy);
	return 0;
}

/**	
 * liqpostcard_config.cmdsend clicked
 */	
static int cmdsend_click(liqcell *self,liqcelleventargs *args, liqcell *liqpostcard_config)
{

	liqcell *liqbasepassword = liqcell_child_lookup(liqpostcard_config, "liqbasepassword");
	liqcell *liqbaseusername = liqcell_child_lookup(liqpostcard_config, "liqbaseusername");
	liqcell *twitteruserpass = liqcell_child_lookup(liqpostcard_config, "twitteruserpass");
	liqcell *twitterusername = liqcell_child_lookup(liqpostcard_config, "twitterusername");
    
    
	char  userpassmd5[32+1]={0};
	char *userpassraw = liqcell_getcaption(liqbasepassword);

		struct cvs_MD5Context context;
		unsigned char checksum[16];
		cvs_MD5Init (&context);
		cvs_MD5Update (&context, (unsigned char *)userpassraw, strlen (userpassraw));
		cvs_MD5Final (checksum, &context);
		int i;
		for (i = 0; i < 16; i++)
		{
			snprintf (&userpassmd5[i*2],3, "%02x", (unsigned int) checksum[i]);
			//printf ("%02x  %i", (unsigned int) checksum[i],i);
		}
		userpassmd5[32]=0;
		
	liqapp_log("dialoguserpass: changing user pass to '%s' (after hashing), recommend logout",userpassmd5);

	
	liqapp_pref_setvalue("username",liqcell_getcaption(liqbaseusername) );
	liqapp_pref_setvalue("userpass",liqcell_getcaption(liqbasepassword) );
	liqapp_pref_setvalue("userpassmd5",userpassmd5 );

	liqapp_pref_setvalue("twitname", liqcell_getcaption(twitterusername) );
	liqapp_pref_setvalue("twitpass", liqcell_getcaption(twitteruserpass) );

	liqapp_prefs_save();


	liqcell_propseti(liqpostcard_config,"dialog_result",1);
	liqcell_setvisible(liqpostcard_config,0);
	return 0;
}
/**	
 * liqpostcard_config_child_test_seek this function shows how to access members
 */	
	  
static void liqpostcard_config_child_test_seek(liqcell *self)
{	  
	liqcell *liqbasepassword = liqcell_child_lookup(self, "liqbasepassword");
	liqcell *liqbaseusername = liqcell_child_lookup(self, "liqbaseusername");
	liqcell *twitteruserpass = liqcell_child_lookup(self, "twitteruserpass");
	liqcell *twitterusername = liqcell_child_lookup(self, "twitterusername");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell *liqbasepasswordtitle = liqcell_child_lookup(self, "liqbasepasswordtitle");
	liqcell *liqbaseusernametitle = liqcell_child_lookup(self, "liqbaseusernametitle");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdsend = liqcell_child_lookup(self, "cmdsend");
	liqcell *label5 = liqcell_child_lookup(self, "label5");
}	  
/**	
 * create a new liqpostcard_config widget
 */	
liqcell *liqpostcard_config_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqpostcard_config", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqpostcard_config'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
    
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "postcard :: configure options for upload services" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(64,64,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);

	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 0, 56, 800, 30);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
	liqcell_setcaption(label2, "to send postcards, you need a liqbase.net account and a twitter account." );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label2, "backcolor", "xrgb(0,64,0)" );
	liqcell_propseti(  label2, "textalign", 2 );
	liqcell_child_append(  self, label2);
    
    
	//############################# label5:label
	liqcell *label5 = liqcell_quickcreatevis("label5", "label", 16, 276, 228, 32);
	liqcell_setfont(	label5, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label5, "twitter username" );
	liqcell_propsets(  label5, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label5, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  label5, "textalign", 0 );
	liqcell_child_append(  self, label5);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 16, 356, 228, 32);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label1, "twitter password" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label1, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_child_append(  self, label1);
    
    
	//############################# liqbasepasswordtitle:label
	liqcell *liqbasepasswordtitle = liqcell_quickcreatevis("liqbasepasswordtitle", "label", 16, 196, 228, 32);
	liqcell_setfont(	liqbasepasswordtitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(liqbasepasswordtitle, "liqbase password" );
	liqcell_propsets(  liqbasepasswordtitle, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  liqbasepasswordtitle, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  liqbasepasswordtitle, "textalign", 0 );
	liqcell_child_append(  self, liqbasepasswordtitle);
	//############################# liqbaseusernametitle:label
	liqcell *liqbaseusernametitle = liqcell_quickcreatevis("liqbaseusernametitle", "label", 16, 116, 228, 32);
	liqcell_setfont(	liqbaseusernametitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(liqbaseusernametitle, "liqbase username" );
	liqcell_propsets(  liqbaseusernametitle, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  liqbaseusernametitle, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  liqbaseusernametitle, "textalign", 0 );
	liqcell_child_append(  self, liqbaseusernametitle);    
    
    
    
	//############################# liqbasepassword:textbox
	liqcell *liqbasepassword = liqcell_quickcreatevis("liqbasepassword", "textbox", 230, 188, 552, 50);
	liqcell_setfont(	liqbasepassword, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_setcaption(liqbasepassword, "" );
	liqcell_propsets(  liqbasepassword, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  liqbasepassword, "backcolor", "rgb(255,255,255)" );
	liqcell_propsets(  liqbasepassword, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  liqbasepassword, "textalign", 0 );
	liqcell_child_append(  self, liqbasepassword);
	//############################# liqbaseusername:textbox
	liqcell *liqbaseusername = liqcell_quickcreatevis("liqbaseusername", "textbox", 230, 108, 552, 50);
	liqcell_setfont(	liqbaseusername, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_setcaption(liqbaseusername, "" );
	liqcell_propsets(  liqbaseusername, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  liqbaseusername, "backcolor", "rgb(255,255,255)" );
	liqcell_propsets(  liqbaseusername, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  liqbaseusername, "textalign", 0 );
	liqcell_child_append(  self, liqbaseusername);
	//############################# twitteruserpass:textbox
	liqcell *twitteruserpass = liqcell_quickcreatevis("twitteruserpass", "textbox", 230, 348, 552, 50);
	liqcell_setfont(	twitteruserpass, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_setcaption(twitteruserpass, "" );
	liqcell_propsets(  twitteruserpass, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  twitteruserpass, "backcolor", "rgb(255,255,255)" );
	liqcell_propsets(  twitteruserpass, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  twitteruserpass, "textalign", 0 );
	liqcell_child_append(  self, twitteruserpass);
	//############################# twitterusername:textbox
	liqcell *twitterusername = liqcell_quickcreatevis("twitterusername", "textbox", 230, 268, 552, 50);
	liqcell_setfont(	twitterusername, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (32), 0) );
	liqcell_setcaption(twitterusername, "" );
	liqcell_propsets(  twitterusername, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  twitterusername, "backcolor", "rgb(255,255,255)" );
	liqcell_propsets(  twitterusername, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  twitterusername, "textalign", 0 );
	liqcell_child_append(  self, twitterusername);
    
    
	//############################# cmdsend:label
	liqcell *cmdsend = liqcell_quickcreatevis("cmdsend", "label", 574, 418, 226, 62);
	liqcell_setfont(	cmdsend, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsend, "Save" );
	liqcell_propsets(  cmdsend, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdsend, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdsend, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdsend, "textalign", 2 );
	liqcell_propseti(  cmdsend, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdsend, "click", cmdsend_click, self );
	liqcell_child_append(  self, cmdsend);


	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqpostcard_config_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqpostcard_config_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqpostcard_config_resize ,self);
	liqcell_handleradd_withcontext(self, "keypress", liqpostcard_config_keypress,self );
	liqcell_handleradd_withcontext(self, "keyrelease", liqpostcard_config_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqpostcard_config_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqpostcard_config_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqpostcard_config_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqpostcard_config_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqpostcard_config_dialog_close ,self);

    liqcell_propseti(liqbasepassword,"textispassword",1);
    liqcell_propseti(twitteruserpass,"textispassword",1);

    liqcell_handlerrun(self,"refresh",NULL);

	return self;
}

