// this file is part of liqbase by Gary Birkett
      
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>
/**   
 * textbox widget dynamic resizing
 */   
static int textbox_resize(liqcell *self,liqcelleventargs *args, void *context)
{
   float sx=((float)self->w)/((float)self->innerw);
   float sy=((float)self->h)/((float)self->innerh);
   
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label4"), 242,2, 74,20, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label3"), 156,4, 74,18, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label2"), 80,4, 64,18, sx,sy);
   liqcell_setrect_autoscale( liqcell_child_lookup(self,"label1"), 8,6, 60,14, sx,sy);
}

/**   
 * create a new textbox widget
 */   
liqcell *textbox_create()
{
   liqcell *self = liqcell_quickcreatewidget("textbox", "form", 324, 26);
   if(!self) {liqapp_log("liqcell error not create 'textbox'"); return NULL;  } 
   
   //############################# label4:label
   liqcell *label4 = liqcell_quickcreatevis("label4", "label", 242, 2, 74, 20);
   liqcell_setfont(   label4, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
   liqcell_setcaption(label4, "Label4" );
   liqcell_propsets(  label4, "textcolor", "rgb(0,0,0)" );
   liqcell_propsets(  label4, "backcolor", "rgb(235,233,237)" );
   liqcell_propseti(  label4, "textalign", 0 );
   liqcell_child_append(  self, label4);
   //############################# label3:label
   liqcell *label3 = liqcell_quickcreatevis("label3", "label", 156, 4, 74, 18);
   liqcell_setfont(   label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
   liqcell_setcaption(label3, "Label3" );
   liqcell_propsets(  label3, "textcolor", "rgb(0,0,0)" );
   liqcell_propsets(  label3, "backcolor", "rgb(235,233,237)" );
   liqcell_propseti(  label3, "textalign", 0 );
   liqcell_child_append(  self, label3);
   //############################# label2:label
   liqcell *label2 = liqcell_quickcreatevis("label2", "label", 80, 4, 64, 18);
   liqcell_setfont(   label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
   liqcell_setcaption(label2, "Label2" );
   liqcell_propsets(  label2, "textcolor", "rgb(0,0,0)" );
   liqcell_propsets(  label2, "backcolor", "rgb(235,233,237)" );
   liqcell_propseti(  label2, "textalign", 0 );
   liqcell_child_append(  self, label2);
   //############################# label1:label
   liqcell *label1 = liqcell_quickcreatevis("label1", "label", 8, 6, 60, 14);
   liqcell_setfont(   label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (10), 0) );
   liqcell_setcaption(label1, "Label1" );
   liqcell_propsets(  label1, "textcolor", "rgb(0,0,0)" );
   liqcell_propsets(  label1, "backcolor", "rgb(235,233,237)" );
   liqcell_propseti(  label1, "textalign", 0 );
   liqcell_child_append(  self, label1);
   liqcell_propsets(  self, "backcolor", "rgb(255,255,0)" );
   liqcell_handleradd(self, "resize", textbox_resize );
   return self;
}

