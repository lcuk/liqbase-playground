// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyrun.h>


liqcell *liqbookreader_create();
liqcell *liqbooklist_create();
/**	
 * liqbook widget refresh, all params set, present yourself to the user.
 */	
static int liqbook_refresh(liqcell *self,liqcelleventargs *args, void *context)
{
	// there might be an OS level variable called filter
	// it should be set and adjusted correctly prior to calling this routine
	// you should do your best to account for this filter in any way you see fit
}
/**	
 * liqbook.book_continuereading clicked
 */	
static int book_continuereading_click(liqcell *self,liqcelleventargs *args, liqcell *liqbook)
{
	//liqcell *bookreader = liqbookreader_create();//liqcell_quickcreatevis("bookreader", "liqbookreader", 0,0, 0,0);
	//liqcell_easyrun(bookreader);
	//liqcell_release(bookreader);
	
	int liqbookreader_run(char *bookfilename);
	liqbookreader_run("/usr/share/liqbase/media/liqbook.example.txt");
}
/**	
 * liqbook.book_chooseanother clicked
 */	
static int book_chooseanother_click(liqcell *self,liqcelleventargs *args, liqcell *liqbook)
{
	//liqcell *booklist = liqbooklist_create();//liqcell_quickcreatevis("booklist", "liqbooklist", 0,0, 0,0);
	liqcell *booklist = liqcell_quickcreatevis("booklist", "dialogfileselect", 0,0, 0,0);
	liqcell_easyrun(booklist);
	liqcell_release(booklist);
}
/**	
 * create a new liqbook widget
 */	
liqcell *liqbook_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqbook", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqbook'"); return NULL;  } 
	
	//############################# book_chooseanother:commandbutton
	liqcell *book_chooseanother = liqcell_quickcreatevis("book_chooseanother", "commandbutton", 92, 432, 282, 42);
	liqcell_setfont(	book_chooseanother, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (20), 0) );
	liqcell_setcaption(book_chooseanother, "Choose another book" );
	liqcell_propsets(  book_chooseanother, "backcolor", "rgb(15,15,15)" );
	liqcell_handleradd_withcontext(book_chooseanother, "click", book_chooseanother_click, self );
	liqcell_child_append(  self, book_chooseanother);

	//############################# book_continuereading:commandbutton
	liqcell *book_continuereading = liqcell_quickcreatevis("book_continuereading", "commandbutton", 404, 432, 390, 42);
	liqcell_setfont(	book_continuereading, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (20), 0) );
	liqcell_setcaption(book_continuereading, "Continue reading" );
	liqcell_propsets(  book_continuereading, "backcolor", "rgb(30,60,30)" );
	liqcell_handleradd_withcontext(book_continuereading, "click", book_continuereading_click, self );
	liqcell_child_append(  self, book_continuereading);
	
	//############################# bookinfo:frame
	liqcell *bookinfo = liqcell_quickcreatevis("bookinfo", "frame", 404, 54, 388, 368);
	//liqcell_setfont(	bookinfo, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(bookinfo, "Frame1" );
	//liqcell_propsets(  bookinfo, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  bookinfo, "backcolor", "rgb(64,64,64)" );
		//############################# booktitle:textbox
		liqcell *booktitle = liqcell_quickcreatevis("booktitle", "textbox", 106, 58, 274, 36);
		liqcell_setfont(	booktitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
		liqcell_setcaption(booktitle, "Ringworld" );
		liqcell_propsets(  booktitle, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  booktitle, "backcolor", "rgb(0,0,0)" );
		liqcell_propsets(  booktitle, "bordercolor", "rgb(200,100,100)" );
		liqcell_propseti(  booktitle, "textalign", 0 );
		liqcell_child_append(  bookinfo, booktitle);
		//############################# label11:label
		liqcell *label11 = liqcell_quickcreatevis("label11", "label", 6, 324, 90, 18);
		liqcell_setfont(	label11, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		liqcell_setcaption(label11, "options" );
		liqcell_propsets(  label11, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  label11, "backcolor", "rgb(0,0,0)" );
		liqcell_propseti(  label11, "textalign", 1 );
		liqcell_child_append(  bookinfo, label11);
		//############################# bookoptions:label
		liqcell *bookoptions = liqcell_quickcreatevis("bookoptions", "label", 102, 316, 274, 34);
		liqcell_setfont(	bookoptions, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
		liqcell_setcaption(bookoptions, "Standard" );
		liqcell_propsets(  bookoptions, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  bookoptions, "backcolor", "rgb(64,0,64)" );
		liqcell_propseti(  bookoptions, "textalign", 0 );
		liqcell_child_append(  bookinfo, bookoptions);
		//############################# label9:label
		liqcell *label9 = liqcell_quickcreatevis("label9", "label", 6, 280, 90, 18);
		liqcell_setfont(	label9, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		liqcell_setcaption(label9, "tags" );
		liqcell_propsets(  label9, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  label9, "backcolor", "rgb(0,0,0)" );
		liqcell_propseti(  label9, "textalign", 1 );
		liqcell_child_append(  bookinfo, label9);
		//############################# booktags:label
		liqcell *booktags = liqcell_quickcreatevis("booktags", "label", 102, 272, 274, 34);
		liqcell_setfont(	booktags, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
		liqcell_setcaption(booktags, "scifi,knownspace,niven" );
		liqcell_propsets(  booktags, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  booktags, "backcolor", "rgb(0,64,0)" );
		liqcell_propseti(  booktags, "textalign", 0 );
		liqcell_child_append(  bookinfo, booktags);
		//############################# bookisbn:label
		liqcell *bookisbn = liqcell_quickcreatevis("bookisbn", "label", 102, 226, 274, 34);
		liqcell_setfont(	bookisbn, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
		liqcell_setcaption(bookisbn, "3240234234" );
		liqcell_propsets(  bookisbn, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  bookisbn, "backcolor", "rgb(64,0,64)" );
		liqcell_propseti(  bookisbn, "textalign", 0 );
		liqcell_child_append(  bookinfo, bookisbn);
		//############################# detailstitle:label
		liqcell *detailstitle = liqcell_quickcreatevis("detailstitle", "label", 8, 0, 316, 32);
		liqcell_setfont(	detailstitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_setcaption(detailstitle, "current book details" );
		liqcell_propsets(  detailstitle, "textcolor", "rgb(255,255,192)" );
		liqcell_propsets(  detailstitle, "backcolor", "rgb(235,233,237)" );
		liqcell_propseti(  detailstitle, "textalign", 0 );
		liqcell_child_append(  bookinfo, detailstitle);
		//############################# label8:label
		liqcell *label8 = liqcell_quickcreatevis("label8", "label", 6, 234, 90, 18);
		liqcell_setfont(	label8, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		liqcell_setcaption(label8, "ISBN" );
		liqcell_propsets(  label8, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  label8, "backcolor", "rgb(0,0,0)" );
		liqcell_propseti(  label8, "textalign", 1 );
		liqcell_child_append(  bookinfo, label8);
		//############################# label4:label
		liqcell *label4 = liqcell_quickcreatevis("label4", "label", 6, 150, 88, 16);
		liqcell_setfont(	label4, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		liqcell_setcaption(label4, "size" );
		liqcell_propsets(  label4, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  label4, "backcolor", "rgb(0,0,0)" );
		liqcell_propseti(  label4, "textalign", 1 );
		liqcell_child_append(  bookinfo, label4);
		//############################# label3:label
		liqcell *label3 = liqcell_quickcreatevis("label3", "label", 6, 188, 90, 18);
		liqcell_setfont(	label3, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		liqcell_setcaption(label3, "format" );
		liqcell_propsets(  label3, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  label3, "backcolor", "rgb(0,0,0)" );
		liqcell_propseti(  label3, "textalign", 1 );
		liqcell_child_append(  bookinfo, label3);
		//############################# label2:label
		liqcell *label2 = liqcell_quickcreatevis("label2", "label", 6, 110, 90, 16);
		liqcell_setfont(	label2, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		liqcell_setcaption(label2, "author" );
		liqcell_propsets(  label2, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  label2, "backcolor", "rgb(0,0,0)" );
		liqcell_propseti(  label2, "textalign", 1 );
		liqcell_child_append(  bookinfo, label2);
		//############################# label1:label
		liqcell *label1 = liqcell_quickcreatevis("label1", "label", 6, 68, 90, 16);
		liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		liqcell_setcaption(label1, "title" );
		liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  label1, "backcolor", "rgb(0,0,0)" );
		liqcell_propseti(  label1, "textalign", 1 );
		liqcell_child_append(  bookinfo, label1);
		//############################# bookformat:label
		liqcell *bookformat = liqcell_quickcreatevis("bookformat", "label", 102, 182, 274, 34);
		liqcell_setfont(	bookformat, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
		liqcell_setcaption(bookformat, "Text" );
		liqcell_propsets(  bookformat, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  bookformat, "backcolor", "rgb(64,0,64)" );
		liqcell_propseti(  bookformat, "textalign", 0 );
		liqcell_child_append(  bookinfo, bookformat);
		//############################# bookauthor:label
		liqcell *bookauthor = liqcell_quickcreatevis("bookauthor", "label", 104, 102, 276, 34);
		liqcell_setfont(	bookauthor, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
		liqcell_setcaption(bookauthor, "Larry Niven" );
		liqcell_propsets(  bookauthor, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  bookauthor, "backcolor", "rgb(64,0,0)" );
		liqcell_propseti(  bookauthor, "textalign", 0 );
		liqcell_child_append(  bookinfo, bookauthor);
		//############################# booksize:label
		liqcell *booksize = liqcell_quickcreatevis("booksize", "label", 104, 142, 172, 34);
		liqcell_setfont(	booksize, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
		liqcell_setcaption(booksize, "294 Pages" );
		liqcell_propsets(  booksize, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  booksize, "backcolor", "rgb(64,0,0)" );
		liqcell_propseti(  booksize, "textalign", 0 );
		liqcell_child_append(  bookinfo, booksize);
	liqcell_child_append(  self, bookinfo);

	//############################# bookcover:label
	liqcell *bookcover = liqcell_quickcreatevis("bookcover", "label", 20, 54, 356, 368);
	//liqcell_setfont(	bookcover, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(bookcover, "book cover" );
	//liqcell_propsets(  bookcover, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  bookcover, "backcolor", "rgb(0,64,0)" );
	//liqcell_propseti(  bookcover, "textalign", 2 );
	liqcell_setimage(  bookcover ,  liqimage_cache_getfile( "media/niven.ringworld.jpg",0,0,1) );
	liqcell_child_append(  self, bookcover);
	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 6, 8, 52, 40);
	liqcell_setfont(	icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(icon, "icon" );
	liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  icon, "backcolor", "rgb(0,0,0)" );
	liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 66, 8, 724, 40);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "Larry Niven :: Ringworld" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd(self, "refresh", liqbook_refresh );
	return self;
}








//#####################################################################
//#####################################################################
//##################################################################### main :)
//#####################################################################
//#####################################################################

// this is only used when liqbook is compiled as a standalone binary
// otherwise it can be constructed as a widget and exist with exactly the same lifespan

static void liqcell_easyrun_internal(liqcell *dialog)
{
	 if(0!=liqcanvas_init( 800,480, 1))
	 {
		  liqapp_errorandfail(-1,"liqbook canvas Init");
		  //closeall();
		  return -1;
	 }
	 liqcell_easyrun( dialog );
	 liqcanvas_close();
}

int main (int argc, char* argv[])
{
	 if(liqapp_init(	argc,argv ,"liqbook" ,"0.0.1") != 0)
	 {
		  { return liqapp_errorandfail(-1,"liqbook liqapp_init failed"); }
	 }
	 liqcell *self = liqbook_create();
	 liqcell_easyrun_internal(self);
	 liqcell_release(self);
	 liqapp_close();
	 return 0;
}

