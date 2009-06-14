// this file is part of liqbase by Gary Birkett
      
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
/**   
 * desktopmanageitem widget dynamic resizing
 */   
static int desktopmanageitem_resize(liqcell *self,liqcelleventargs *args, void *context)
{
   float sx=((float)self->w)/((float)self->innerw);
   float sy=((float)self->h)/((float)self->innerh);
   
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"picture1"), 6,54, 392,366, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"buttonback"), 8,432, 202,42, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"frame1"), 404,54, 388,366, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"item1"), 106,36, 274,36, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"detailstitle"), 8,0, 228,32, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label8"), 6,202, 90,18, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label4"), 6,128, 88,16, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label3"), 6,166, 90,18, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label2"), 6,88, 90,16, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label1"), 6,46, 90,16, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"item4"), 102,160, 278,34, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"clientmap"), 102,200, 274,158, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"item2"), 104,80, 276,34, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"item3"), 104,120, 276,34, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"buttonaccept"), 616,432, 178,42, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"icon"), 6,8, 52,40, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"title"), 66,8, 396,40, sx,sy);
}

/**   
 * create a new desktopmanageitem widget
 */   
liqcell *desktopmanageitem_create()
{
   liqcell *self = liqcell_quickcreatewidget("desktopmanageitem", "form", 800, 480);
   if(!self) {liqapp_log("liqcell error not create 'desktopmanageitem'"); return NULL;  } 
   
   //############################# picture1:picturebox
   liqcell *picture1 = liqcell_quickcreatevis("picture1", "picturebox", 6, 54, 392, 366);
   liqcell_setfont(   picture1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   liqcell_propsets(  picture1, "textcolor", "rgb(0,0,0)" );
   liqcell_propsets(  picture1, "backcolor", "rgb(0,64,64)" );
   liqcell_propsets(  picture1, "bordercolor", "rgb(200,100,100)" );
   liqcell_child_append(  self, picture1);
   //############################# buttonback:commandbutton
   liqcell *buttonback = liqcell_quickcreatevis("buttonback", "commandbutton", 8, 432, 202, 42);
   liqcell_setfont(   buttonback, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
   liqcell_setcaption(buttonback, "Back" );
   liqcell_propsets(  buttonback, "backcolor", "rgb(235,233,237)" );
   liqcell_child_append(  self, buttonback);
   //############################# frame1:frame
   liqcell *frame1 = liqcell_quickcreatevis("frame1", "frame", 404, 54, 388, 366);
   liqcell_setfont(   frame1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   liqcell_setcaption(frame1, "Frame1" );
   liqcell_propsets(  frame1, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  frame1, "backcolor", "rgb(64,64,64)" );
	   //############################# item1:textbox
	   liqcell *item1 = liqcell_quickcreatevis("item1", "textbox", 106, 36, 274, 36);
	   liqcell_setfont(   item1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	   liqcell_setcaption(item1, "liqbase manager" );
	   liqcell_propsets(  item1, "textcolor", "rgb(255,255,255)" );
	   liqcell_propsets(  item1, "backcolor", "rgb(0,0,0)" );
	   liqcell_propsets(  item1, "bordercolor", "rgb(200,100,100)" );
	   liqcell_propseti(  item1, "textalign", 0 );
	   liqcell_child_append(  frame1, item1);
	   //############################# detailstitle:label
	   liqcell *detailstitle = liqcell_quickcreatevis("detailstitle", "label", 8, 0, 228, 32);
	   liqcell_setfont(   detailstitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
	   liqcell_setcaption(detailstitle, "application details" );
	   liqcell_propsets(  detailstitle, "textcolor", "rgb(255,255,192)" );
	   liqcell_propsets(  detailstitle, "backcolor", "rgb(235,233,237)" );
	   liqcell_propseti(  detailstitle, "textalign", 0 );
	   liqcell_child_append(  frame1, detailstitle);
	   //############################# label8:label
	   liqcell *label8 = liqcell_quickcreatevis("label8", "label", 6, 202, 90, 18);
	   liqcell_setfont(   label8, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	   liqcell_setcaption(label8, "description" );
	   liqcell_propsets(  label8, "textcolor", "rgb(255,255,255)" );
	   liqcell_propsets(  label8, "backcolor", "rgb(0,0,0)" );
	   liqcell_propseti(  label8, "textalign", 1 );
	   liqcell_child_append(  frame1, label8);
	   //############################# label4:label
	   liqcell *label4 = liqcell_quickcreatevis("label4", "label", 6, 128, 88, 16);
	   liqcell_setfont(   label4, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	   liqcell_setcaption(label4, "version:" );
	   liqcell_propsets(  label4, "textcolor", "rgb(255,255,255)" );
	   liqcell_propsets(  label4, "backcolor", "rgb(0,0,0)" );
	   liqcell_propseti(  label4, "textalign", 1 );
	   liqcell_child_append(  frame1, label4);
	   //############################# label3:label
	   liqcell *label3 = liqcell_quickcreatevis("label3", "label", 6, 166, 90, 18);
	   liqcell_setfont(   label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	   liqcell_setcaption(label3, "categories:" );
	   liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
	   liqcell_propsets(  label3, "backcolor", "rgb(0,0,0)" );
	   liqcell_propseti(  label3, "textalign", 1 );
	   liqcell_child_append(  frame1, label3);
	   //############################# label2:label
	   liqcell *label2 = liqcell_quickcreatevis("label2", "label", 6, 88, 90, 16);
	   liqcell_setfont(   label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	   liqcell_setcaption(label2, "Author:" );
	   liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
	   liqcell_propsets(  label2, "backcolor", "rgb(0,0,0)" );
	   liqcell_propseti(  label2, "textalign", 1 );
	   liqcell_child_append(  frame1, label2);
	   //############################# label1:label
	   liqcell *label1 = liqcell_quickcreatevis("label1", "label", 6, 46, 90, 16);
	   liqcell_setfont(   label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	   liqcell_setcaption(label1, "Title:" );
	   liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	   liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
	   liqcell_propseti(  label1, "textalign", 1 );
	   liqcell_child_append(  frame1, label1);
	   //############################# item4:label
	   liqcell *item4 = liqcell_quickcreatevis("item4", "label", 102, 160, 278, 34);
	   liqcell_setfont(   item4, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	   liqcell_setcaption(item4, "Desktop,UI,PIM,Book" );
	   liqcell_propsets(  item4, "textcolor", "rgb(255,255,255)" );
	   liqcell_propsets(  item4, "backcolor", "rgb(64,0,64)" );
	   liqcell_propseti(  item4, "textalign", 0 );
	   liqcell_child_append(  frame1, item4);
	   //############################# clientmap:label
	   liqcell *clientmap = liqcell_quickcreatevis("clientmap", "label", 102, 200, 274, 158);
	   liqcell_setfont(   clientmap, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	   liqcell_setcaption(clientmap, "place detailed notes here" );
	   liqcell_propsets(  clientmap, "textcolor", "rgb(255,255,255)" );
	   liqcell_propsets(  clientmap, "backcolor", "rgb(0,64,0)" );
	   liqcell_propseti(  clientmap, "textalign", 2 );
	   liqcell_child_append(  frame1, clientmap);
	   //############################# item2:label
	   liqcell *item2 = liqcell_quickcreatevis("item2", "label", 104, 80, 276, 34);
	   liqcell_setfont(   item2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	   liqcell_setcaption(item2, "Gary Birkett" );
	   liqcell_propsets(  item2, "textcolor", "rgb(255,255,255)" );
	   liqcell_propsets(  item2, "backcolor", "rgb(64,0,0)" );
	   liqcell_propseti(  item2, "textalign", 0 );
	   liqcell_child_append(  frame1, item2);
	   //############################# item3:label
	   liqcell *item3 = liqcell_quickcreatevis("item3", "label", 104, 120, 276, 34);
	   liqcell_setfont(   item3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	   liqcell_setcaption(item3, "1.0 beta" );
	   liqcell_propsets(  item3, "textcolor", "rgb(255,255,255)" );
	   liqcell_propsets(  item3, "backcolor", "rgb(64,0,0)" );
	   liqcell_propseti(  item3, "textalign", 0 );
	   liqcell_child_append(  frame1, item3);
   liqcell_child_append(  self, frame1);
   //############################# buttonaccept:commandbutton
   liqcell *buttonaccept = liqcell_quickcreatevis("buttonaccept", "commandbutton", 616, 432, 178, 42);
   liqcell_setfont(   buttonaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
   liqcell_setcaption(buttonaccept, "Accept" );
   liqcell_propsets(  buttonaccept, "backcolor", "rgb(235,233,237)" );
   liqcell_child_append(  self, buttonaccept);
   //############################# icon:label
   liqcell *icon = liqcell_quickcreatevis("icon", "label", 6, 8, 52, 40);
   liqcell_setfont(   icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
   liqcell_setcaption(icon, "icon" );
   liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
   liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
   liqcell_propseti(  icon, "textalign", 2 );
   liqcell_child_append(  self, icon);
   //############################# title:label
   liqcell *title = liqcell_quickcreatevis("title", "label", 66, 8, 396, 40);
   liqcell_setfont(   title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
   liqcell_setcaption(title, "liqbase manager details" );
   liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
   liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
   liqcell_propseti(  title, "textalign", 0 );
   liqcell_child_append(  self, title);
   liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
   liqcell_handleradd(self, "resize", desktopmanageitem_resize );
   return self;
}

