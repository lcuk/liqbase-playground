// this file is part of liqbase by Gary Birkett
      
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqbase.h>
      
      
/**   
 * create a new frmbase800x480 widget
 */
static int frmbase800x480_resize(liqcell *self,liqcelleventargs *args, void *context)
{
   float sx=self->w/self->innerw;
   float sy=self->h/self->innerh;

   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label8"), 374,246, 90,18 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label7"), 64,4, 338,32 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label6"), 4,50, 356,422 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"icon"), 6,6, 52,32 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label4"), 374,172, 88,16 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label3"), 374,210, 90,18 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label2"), 374,134, 90,16 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label1"), 374,96, 90,16 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"clientlocation"), 470,204, 320,34 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"clientmap"), 470,244, 320,222 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"clientos"), 470,166, 320,32 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"clientip"), 472,126, 318,34 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"clientname"), 472,88, 318,32 ,sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label5"), 366,50, 430,422 ,sx,sy);
}

/**   
 * create a new frmbase800x480 widget
 */   
liqcell *frmbase800x480_create()
{
   liqcell *self = liqcell_quickcreatewidget("frmbase800x480", "form", 800, 480);
   if(!self) {liqapp_log("liqcell error not create 'frmbase800x480'"); return NULL;  } 
   
   liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
   //############################# label8:label
   liqcell *label8 = liqcell_quickcreatevis("label8", "label", 374, 246, 90, 18);
   liqcell_setfont(   label8, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   liqcell_setcaption(label8, "History:" );
   liqcell_propsets(  label8, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  label8, "backcolor", "rgb(0,0,0)" );
   liqcell_propseti(  label8, "textalign", 1 );
   liqcell_child_append(  self, label8);
   //############################# label7:label
   liqcell *label7 = liqcell_quickcreatevis("label7", "label", 64, 4, 338, 32);
   liqcell_setfont(   label7, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
   liqcell_setcaption(label7, "Zacks Net monitor" );
   liqcell_propsets(  label7, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  label7, "backcolor", "rgb(0,0,0)" );
   liqcell_child_append(  self, label7);
   //############################# label6:label
   liqcell *label6 = liqcell_quickcreatevis("label6", "liqtreebrowse", 4, 50, 356, 422);
   //liqcell_setfont(   label6, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   //liqcell_setcaption(label6, "map goes here" );
   //liqcell_propsets(  label6, "textcolor", "rgb(255,255,255)" );
   //liqcell_propsets(  label6, "backcolor", "rgb(0,64,0)" );
   //liqcell_propseti(  label6, "textalign", 2 );
   liqcell_child_append(  self, label6);
   //############################# icon:label
   liqcell *icon = liqcell_quickcreatevis("icon", "label", 6, 6, 52, 32);
   liqcell_setfont(   icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   liqcell_setcaption(icon, "icon" );
   liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
   liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
   liqcell_propseti(  icon, "textalign", 2 );
   liqcell_child_append(  self, icon);
   //############################# label4:label
   liqcell *label4 = liqcell_quickcreatevis("label4", "label", 374, 172, 88, 16);
   liqcell_setfont(   label4, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   liqcell_setcaption(label4, "OS:" );
   liqcell_propsets(  label4, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  label4, "backcolor", "rgb(0,0,0)" );
   liqcell_propseti(  label4, "textalign", 1 );
   liqcell_child_append(  self, label4);
   //############################# label3:label
   liqcell *label3 = liqcell_quickcreatevis("label3", "label", 374, 210, 90, 18);
   liqcell_setfont(   label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   liqcell_setcaption(label3, "Location:" );
   liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  label3, "backcolor", "rgb(0,0,0)" );
   liqcell_propseti(  label3, "textalign", 1 );
   liqcell_child_append(  self, label3);
   //############################# label2:label
   liqcell *label2 = liqcell_quickcreatevis("label2", "label", 374, 134, 90, 16);
   liqcell_setfont(   label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   liqcell_setcaption(label2, "IP Address:" );
   liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  label2, "backcolor", "rgb(0,0,0)" );
   liqcell_propseti(  label2, "textalign", 1 );
   liqcell_child_append(  self, label2);
   //############################# label1:label
   liqcell *label1 = liqcell_quickcreatevis("label1", "label", 374, 96, 90, 16);
   liqcell_setfont(   label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   liqcell_setcaption(label1, "client host name:" );
   liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
   liqcell_propseti(  label1, "textalign", 1 );
   liqcell_child_append(  self, label1);
   //############################# clientlocation:label
   liqcell *clientlocation = liqcell_quickcreatevis("clientlocation", "label", 470, 204, 320, 34);
   liqcell_setfont(   clientlocation, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
   liqcell_setcaption(clientlocation, "location" );
   liqcell_propsets(  clientlocation, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  clientlocation, "backcolor", "rgb(64,0,64)" );
   liqcell_child_append(  self, clientlocation);
   //############################# clientmap:label
   liqcell *clientmap = liqcell_quickcreatevis("clientmap", "liqreader", 470, 244, 320, 222);
   liqcell_setfont(   clientmap, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   liqcell_setcaption(clientmap, "map goes here" );
   liqcell_propsets(  clientmap, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  clientmap, "backcolor", "rgb(0,64,0)" );
   liqcell_propseti(  clientmap, "textalign", 2 );
   liqcell_child_append(  self, clientmap);
   //############################# clientos:label
   liqcell *clientos = liqcell_quickcreatevis("clientos", "label", 470, 166, 320, 32);
   liqcell_setfont(   clientos, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
   liqcell_setcaption(clientos, "operating system" );
   liqcell_propsets(  clientos, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  clientos, "backcolor", "rgb(0,0,64)" );
   liqcell_child_append(  self, clientos);
   //############################# clientip:label
   liqcell *clientip = liqcell_quickcreatevis("clientip", "label", 472, 126, 318, 34);
   liqcell_setfont(   clientip, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
   liqcell_setcaption(clientip, "123.123.123.123" );
   liqcell_propsets(  clientip, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  clientip, "backcolor", "rgb(64,0,0)" );
   liqcell_child_append(  self, clientip);
   //############################# clientname:label
   liqcell *clientname = liqcell_quickcreatevis("clientname", "label", 472, 88, 318, 32);
   liqcell_setfont(   clientname, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
   liqcell_setcaption(clientname, "clientname" );
   liqcell_propsets(  clientname, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  clientname, "backcolor", "rgb(128,64,64)" );
   liqcell_child_append(  self, clientname);
   //############################# label5:label
   liqcell *label5 = liqcell_quickcreatevis("label5", "label", 366, 50, 430, 422);
   liqcell_setfont(   label5, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (19), 0) );
   liqcell_setcaption(label5, "Client View" );
   liqcell_propsets(  label5, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  label5, "backcolor", "rgb(32,32,32)" );
   liqcell_child_append(  self, label5);
   liqcell_handleradd(self, "resize", frmbase800x480_resize );
   
   //liqcell_propseti(  self, "universeliveview", 1 );
   return self;
}

