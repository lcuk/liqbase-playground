// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
/**	
 * liqwelcome widget refresh, all params set, present yourself to the user.
 */	
static int liqwelcome_refresh(liqcell *self,liqcelleventargs *args, void *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
}
/**	
 * liqwelcome.command1 clicked
 */

extern liqcell *mirror;

static int command1_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqwelcome)
{
	
	liqcell *c=liqcell_getlinkchild(liqwelcome);
	//while(c)
	//{
	//	if(liqcell_getvisible(c)) liqcell_setvisible(c,0);
	//	c=liqcell_getlinknext(c);
	//}
	
	liqcell *loading = liqcell_child_lookup(liqwelcome,"loading");
	
	liqcell_setvisible(loading,1);
	
	args->newdialogtoopen = mirror;
	liqcell_setvisible(loading,0);
	//superrun();
}

	static int widget_click(liqcell *self, liqcellclickeventargs *args)
	{
		args->newdialogtoopen = liqcell_getcontent( self );

		return 1;
	}


/**	
 * create a new liqwelcome widget
 */	
liqcell *liqwelcome_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqwelcome", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqwelcome'"); return NULL;  } 
	
	//############################# command1:commandbutton
	//liqcell *command1 = liqcell_quickcreatevis("command1", "commandbutton", 620, 422, 172, 50);
	//liqcell_setfont(	command1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (28), 0) );
	//liqcell_setcaption(command1, "run liqbase" );
	//liqcell_propsets(  command1, "backcolor", "rgb(0,100,0)" );
	//liqcell_propseti(  command1, "textalign", 2 );
	//liqcell_handleradd_withcontext(command1, "click", command1_click, self );
	//liqcell_child_append(  self, command1);
	//############################# picture2:picturebox
	liqcell *picture2 = liqcell_quickcreatevis("picture2", "picturebox", 588, 236, 138, 120);
	liqcell_setcontent(	picture2,  liqcell_quickcreatevis("content", "liqrecentusers", 0,0, 0,0) );
	
	liqcell_handleradd_withcontext(picture2, "click", widget_click, self );
	
	//liqcell_setfont(	picture2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  picture2, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  picture2, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  picture2, "bordercolor", "rgb(200,100,100)" );
	liqcell_child_append(  self, picture2);

	//############################# label3:label
	liqcell *label3 = liqcell_quickcreatevis("label3", "label", 100, 278, 266, 36);
	liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (28), 0) );
	liqcell_setcaption(label3, "maemo linux" );
	liqcell_propsets(  label3, "textcolor", "rgb(200,200,200)" );
	//liqcell_propsets(  label3, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  label3, "textalign", 2 );
	liqcell_child_append(  self, label3);



	//############################# label7:label
	liqcell *label7 = liqcell_quickcreatevis("label7", "label", 330, 198, 166, 40);
	liqcell_setfont(	label7, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label7, "open source" );
	liqcell_propsets(  label7, "textcolor", "rgb(0,255,0)" );
	//liqcell_propsets(  label7, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  label7, "textalign", 0 );
	liqcell_child_append(  self, label7);

	//############################# picture1:picturebox
	liqcell *picture1 = liqcell_quickcreatevis("picture1", "picturebox", 330, 240, 134, 118);
	//liqcell_setcontent(	picture1,  liqcell_quickcreatevis("content", "liqrecentapps", 0,0, 0,0) );
	liqcell_setcontent(	picture1,  liqcell_quickcreatevis("content", "liqappman", 0,0, 0,0) );

	liqcell_handleradd_withcontext(picture1, "click", widget_click, self );
	
	//liqcell_setfont(	picture1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  picture1, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  picture1, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  picture1, "bordercolor", "rgb(200,100,100)" );
	liqcell_child_append(  self, picture1);
	
	
	
	
	//############################# label6:label
	liqcell *label6 = liqcell_quickcreatevis("label6", "label", 104, 148, 294, 40);
	liqcell_setfont(	label6, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(label6, "written by Gary Birkett" );
	liqcell_propsets(  label6, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  label6, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label6, "textalign", 0 );
	liqcell_child_append(  self, label6);
	//############################# label4:label
	liqcell *label4 = liqcell_quickcreatevis("label4", "label", 100, 110, 422, 52);
	liqcell_setfont(	label4, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label4, "for the maemo linux platform" );
	liqcell_propsets(  label4, "textcolor", "rgb(255,255,192)" );
	//liqcell_propsets(  label4, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  label4, "textalign", 0 );
	liqcell_child_append(  self, label4);
	//############################# nokialogo:label
	liqcell *nokialogo = liqcell_quickcreatevis("nokialogo", "label", 618, 16, 168, 112);
	liqcell_propsets(nokialogo,"imagefilename","media/nokiaconnectingpeople.jpg");
	//liqcell_setfont(	nokialogo, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(nokialogo, "nokia" );
	//liqcell_propsets(  nokialogo, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  nokialogo, "backcolor", "rgb(255,255,255)" );
	//liqcell_propseti(  nokialogo, "textalign", 0 );
	liqcell_child_append(  self, nokialogo);

	//############################# label2:label
	liqcell *label2 = liqcell_quickcreatevis("label2", "label", 40, 422, 576, 50);
	liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (33), 0) );
	liqcell_setcaption(label2, "please donate to all projects" );
	liqcell_propsets(  label2, "textcolor", "rgb(0,255,0)" );
	//liqcell_propsets(  label2, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  label2, "textalign", 2 );
	liqcell_child_append(  self, label2);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 558, 192, 234, 50);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label1, "open community" );
	liqcell_propsets(  label1, "textcolor", "rgb(0,255,255)" );
	//liqcell_propsets(  label1, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  label1, "textalign", 0 );
	liqcell_child_append(  self, label1);

	//############################# label5:label
	liqcell *label5 = liqcell_quickcreatevis("label5", "label", 102, 76, 422, 52);
	liqcell_setfont(	label5, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	liqcell_setcaption(label5, "liqbase is a graphical playground" );
	liqcell_propsets(  label5, "textcolor", "rgb(255,255,192)" );
	//liqcell_propsets(  label5, "backcolor", "rgb(235,233,237)" );
	liqcell_propseti(  label5, "textalign", 0 );
	liqcell_child_append(  self, label5);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 36, 20, 546, 58);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (43), 0) );
	liqcell_setcaption(title, "welcome to liqbase" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,128)" );
	//liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd(self, "refresh", liqwelcome_refresh );

	//############################# loading:label
	//liqcell *loading = liqcell_quickcreatevis("loading", "label", 0,0, 800,480);
	//liqcell_setfont(	loading, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (64), 0) );
	//liqcell_setcaption(loading, "please wait, loading liqbase..." );
	//liqcell_propsets(  loading, "textcolor", "rgb(255,255,192)" );
	////liqcell_propsets(  loading, "backcolor", "rgb(235,233,237)" );
	//liqcell_propseti(  loading, "textalign", 2 );
	//liqcell_propseti(  loading, "textaligny",2 );
	//liqcell_setvisible(  loading,  0 );
	//liqcell_child_append(  self, loading);
		
	return self;
}

