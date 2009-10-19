// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqapp_prefs.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/md5.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqconfig_liqbasenet :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqconfig_liqbasenet widget refresh, all params set, present yourself to the user.
 */	
static int liqconfig_liqbasenet_refresh(liqcell *self,liqcelleventargs *args, liqcell *liqconfig_liqbasenet)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit


    
    
	liqcell *liqbasepassword = liqcell_child_lookup(liqconfig_liqbasenet, "liqbasepassword");
	liqcell *liqbaseusername = liqcell_child_lookup(liqconfig_liqbasenet, "liqbaseusername");
    
    

	liqcell_setcaption(liqbaseusername,       app.username );
	liqcell_setcaption(liqbasepassword,       liqapp_pref_getvalue_def("userpass",  "") );

    
	return 0;
}
/**	
 * liqconfig_liqbasenet dialog_open - the user zoomed into the dialog
 */	
static int liqconfig_liqbasenet_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *liqconfig_liqbasenet)
{
    liqcell_handlerrun(liqconfig_liqbasenet,"refresh",NULL);
	return 0;
}
/**	
 * liqconfig_liqbasenet dialog_close - the dialog was closed
 */	
static int liqconfig_liqbasenet_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *liqconfig_liqbasenet)
{
    liqcell_handlerrun(liqconfig_liqbasenet,"refresh",NULL);
	return 0;
}
/**	
 * liqconfig_liqbasenet widget shown - occurs once per lifetime
 */	
static int liqconfig_liqbasenet_shown(liqcell *self,liqcelleventargs *args, liqcell *liqconfig_liqbasenet)
{
    liqcell_handlerrun(liqconfig_liqbasenet,"refresh",NULL);
	return 0;
}
/**	
 * liqconfig_liqbasenet mouse - occurs all the time as you stroke the screen
 */	
static int liqconfig_liqbasenet_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *liqconfig_liqbasenet)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet click - occurs when a short mouse stroke occured
 */	
static int liqconfig_liqbasenet_click(liqcell *self, liqcellclickeventargs *args,liqcell *liqconfig_liqbasenet)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet keypress - the user pressed a key
 */	
static int liqconfig_liqbasenet_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *liqconfig_liqbasenet)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet keyrelease - the user released a key
 */	
static int liqconfig_liqbasenet_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *liqconfig_liqbasenet)
{
	return 0;
}
/**	
 * liqconfig_liqbasenet paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqconfig_liqbasenet_paint(liqcell *self, liqcellpainteventargs *args,liqcell *liqconfig_liqbasenet)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqconfig_liqbasenet dynamic resizing
 */	
static int liqconfig_liqbasenet_resize(liqcell *self,liqcelleventargs *args, liqcell *liqconfig_liqbasenet)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell *liqbasepassword = liqcell_child_lookup(self, "liqbasepassword");
	liqcell *liqbaseusername = liqcell_child_lookup(self, "liqbaseusername");
	//liqcell *cmdprivacy = liqcell_child_lookup(self, "cmdprivacy");
	liqcell *label1 = liqcell_child_lookup(self, "label1");
	liqcell *pichead = liqcell_child_lookup(self, "pichead");
	liqcell *cmdaccept = liqcell_child_lookup(self, "cmdaccept");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *label2 = liqcell_child_lookup(self, "label2");
	liqcell_setrect_autoscale( liqbasepassword, 170,312, 456,72, sx,sy);
	liqcell_setrect_autoscale( liqbaseusername, 172,178, 454,64, sx,sy);
	//liqcell_setrect_autoscale( cmdprivacy, 234,432, 272,48, sx,sy);
	liqcell_setrect_autoscale( label1, 170,272, 368,36, sx,sy);
	liqcell_setrect_autoscale( pichead, 172,138, 368,36, sx,sy);
	liqcell_setrect_autoscale( cmdaccept, 594,432, 206,48, sx,sy);
	liqcell_setrect_autoscale( title, 0,0, 800,56, sx,sy);
	liqcell_setrect_autoscale( label2, 30,56, 724,52, sx,sy);
	return 0;
}

/**	
 * liqconfig_liqbasenet.cmdaccept clicked
 */	
static int cmdaccept_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqconfig_liqbasenet)
{
    
	liqcell *liqbasepassword = liqcell_child_lookup(liqconfig_liqbasenet, "liqbasepassword");
	liqcell *liqbaseusername = liqcell_child_lookup(liqconfig_liqbasenet, "liqbaseusername");

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
		
	liqapp_log("liqconfig_liqbasenet: changing user pass to '%s' (after hashing), recommend logout",userpassmd5);

	
	liqapp_pref_setvalue("username",liqcell_getcaption(liqbaseusername) );
	liqapp_pref_setvalue("userpass",liqcell_getcaption(liqbasepassword) );
	liqapp_pref_setvalue("userpassmd5",userpassmd5 );


	liqapp_prefs_save();
    
    liqapp_usernamechange( liqcell_getcaption(liqbaseusername) );

    liqcell_propseti(liqconfig_liqbasenet,"dialog_running",0);
	return 0;
}

/**	
 * liqconfig_liqbasenet.cmdprivacy clicked
 */	
static int cmdprivacy_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqconfig_liqbasenet)
{
	return 0;
}

/**	
 * liqconfig_liqbasenet_child_test_seek this function shows how to access members
 */	
	  
static void liqconfig_liqbasenet_child_test_seek(liqcell *liqconfig_liqbasenet)
{	  
	liqcell *liqbasepassword = liqcell_child_lookup(liqconfig_liqbasenet, "liqbasepassword");
	liqcell *liqbaseusername = liqcell_child_lookup(liqconfig_liqbasenet, "liqbaseusername");
	liqcell *cmdprivacy = liqcell_child_lookup(liqconfig_liqbasenet, "cmdprivacy");
	liqcell *label1 = liqcell_child_lookup(liqconfig_liqbasenet, "label1");
	liqcell *pichead = liqcell_child_lookup(liqconfig_liqbasenet, "pichead");
	liqcell *cmdaccept = liqcell_child_lookup(liqconfig_liqbasenet, "cmdaccept");
	liqcell *title = liqcell_child_lookup(liqconfig_liqbasenet, "title");
	liqcell *label2 = liqcell_child_lookup(liqconfig_liqbasenet, "label2");
}	  
/**	
 * create a new liqconfig_liqbasenet widget
 */	
liqcell *liqconfig_liqbasenet_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqconfig_liqbasenet", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqconfig_liqbasenet'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# liqbasepassword:textbox
	liqcell *liqbasepassword = liqcell_quickcreatevis("liqbasepassword", "textbox", 170, 312, 456, 72);
	liqcell_setfont(	liqbasepassword, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(liqbasepassword, "password" );
	liqcell_propsets(  liqbasepassword, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  liqbasepassword, "backcolor", "rgb(255,255,255)" );
	liqcell_propsets(  liqbasepassword, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  liqbasepassword, "textalign", 0 );
	liqcell_propseti(  liqbasepassword, "textaligny", 0 );
    liqcell_propseti(liqbasepassword,"textispassword",1);
	liqcell_child_append(  self, liqbasepassword);
	//############################# liqbaseusername:textbox
	liqcell *liqbaseusername = liqcell_quickcreatevis("liqbaseusername", "textbox", 172, 178, 454, 64);
	liqcell_setfont(	liqbaseusername, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(liqbaseusername, "username" );
	liqcell_propsets(  liqbaseusername, "textcolor", "rgb(0,0,0)" );
	liqcell_propsets(  liqbaseusername, "backcolor", "rgb(255,255,255)" );
	liqcell_propsets(  liqbaseusername, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  liqbaseusername, "textalign", 0 );
	liqcell_propseti(  liqbaseusername, "textaligny", 0 );
	liqcell_child_append(  self, liqbaseusername);
/*

	//############################# cmdprivacy:label
	liqcell *cmdprivacy = liqcell_quickcreatevis("cmdprivacy", "label", 234, 432, 272, 48);
	liqcell_setfont(	cmdprivacy, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdprivacy, "Privacy settings" );
	liqcell_propsets(  cmdprivacy, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdprivacy, "backcolor", "rgb(64,64,0)" );
	liqcell_propsets(  cmdprivacy, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdprivacy, "textalign", 2 );
	liqcell_propseti(  cmdprivacy, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdprivacy, "click", cmdprivacy_click, self );
	liqcell_child_append(  self, cmdprivacy);
*/
    //############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 170, 272, 368, 36);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label1, "password" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_propseti(  label1, "textaligny", 0 );
	liqcell_child_append(  self, label1);
	//############################# pichead:label
	liqcell *pichead = liqcell_quickcreatevis("pichead", "label", 172, 138, 368, 36);
	liqcell_setfont(	pichead, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(pichead, "username" );
	liqcell_propsets(  pichead, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  pichead, "backcolor", "rgb(0,64,64)" );
	liqcell_propseti(  pichead, "textalign", 0 );
	liqcell_propseti(  pichead, "textaligny", 0 );
	liqcell_child_append(  self, pichead);
	//############################# cmdaccept:label
	liqcell *cmdaccept = liqcell_quickcreatevis("cmdaccept", "label", 594, 432, 206, 48);
	liqcell_setfont(	cmdaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdaccept, "Save" );
	liqcell_propsets(  cmdaccept, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdaccept, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdaccept, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdaccept, "textalign", 2 );
	liqcell_propseti(  cmdaccept, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdaccept, "click", cmdaccept_click, self );
	liqcell_child_append(  self, cmdaccept);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 56);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Configure liqbase.net settings" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 30, 56, 724, 52);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label2, "Select account details for liqbase.net uploading" );
	liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label2, "textalign", 2 );
	liqcell_propseti(  label2, "textaligny", 2 );
	liqcell_child_append(  self, label2);
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd_withcontext(self, "refresh", liqconfig_liqbasenet_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown", liqconfig_liqbasenet_shown ,self);
	liqcell_handleradd_withcontext(self, "resize", liqconfig_liqbasenet_resize ,self);
	//liqcell_handleradd_withcontext(self, "keypress", liqconfig_liqbasenet_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", liqconfig_liqbasenet_keyrelease ,self);
	liqcell_handleradd_withcontext(self, "mouse", liqconfig_liqbasenet_mouse,self );
	liqcell_handleradd_withcontext(self, "click", liqconfig_liqbasenet_click ,self);
	//liqcell_handleradd_withcontext(self, "paint", liqconfig_liqbasenet_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open", liqconfig_liqbasenet_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", liqconfig_liqbasenet_dialog_close ,self);
	return self;
}

