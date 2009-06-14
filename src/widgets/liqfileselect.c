// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqcell_easyrun.h>
/**	
 * liqfileselect widget dynamic resizing
 */	
static int liqfileselect_resize(liqcell *self,liqcelleventargs *args)
{
	float sx=((float)self->w)/((float)self->innerw);
	float sy=((float)self->h)/((float)self->innerh);
	
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"buttonaccept"), 720,432, 74,42, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"label7"), 4,252, 54,64, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"label6"), 6,178, 52,68, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"label5"), 6,96, 52,76, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"icon"), 6,8, 52,40, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"title"), 66,6, 546,42, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"filelist"), 406,52, 392,422, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"label1"), 4,324, 54,64, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"foldertree"), 58,52, 344,422, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"folderbackplane"), 4,4, 336,136, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"folderitem"), 4,4, 326,114, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"folderplus"), 4,6, 18,22, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"foldersubfolder"), 50,32, 270,76, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"foldername"), 50,6, 186,22, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"foldersize"), 242,6, 78,22, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"folderico"), 28,6, 18,22, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"filebackplane"), 2,6, 386,64, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"fileitem"), 4,4, 378,34, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"fileico"), 4,6, 18,22, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"filedate"), 300,6, 74,22, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"filesize"), 226,6, 70,22, sx,sy);
	liqcell_setrect_autoscale( liqcell_child_lookup(self,"filename"), 24,6, 198,22, sx,sy);
	return 0;
}

/**	
 * create a new liqfileselect widget
 */	
liqcell *liqfileselect_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqfileselect", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqfileselect'"); return NULL;  } 
	
	//############################# foldertree:frame
	liqcell *foldertree = liqcell_quickcreatevis("foldertree", "frame", 58, 52, 344, 422);
	//liqcell_setfont(	foldertree, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(foldertree, "Frame1" );
	//liqcell_propsets(  foldertree, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  foldertree, "backcolor", "rgb(64,64,64)" );
		//############################# folderbackplane:frame
		liqcell *folderbackplane = liqcell_quickcreatevis("folderbackplane", "frame", 4, 4, 336, 136);
		//liqcell_setfont(	folderbackplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_setcaption(folderbackplane, "" );
		//liqcell_propsets(  folderbackplane, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  folderbackplane, "backcolor", "rgb(128,128,128)" );

		int d=0;
		for(d=0;d<200;d++)
		{
			//############################# folderitem:frame
			liqcell *folderitem = liqcell_quickcreatevis("folderitem", "frame", 4, 4, 326, 114);
			//liqcell_setfont(	folderitem, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
			//liqcell_setcaption(folderitem, "Frame1" );
			//liqcell_propsets(  folderitem, "textcolor", "rgb(0,0,0)" );
			//liqcell_propsets(  folderitem, "backcolor", "rgb(192,192,192)" );
				//############################# folderico:label
				liqcell *folderico = liqcell_quickcreatevis("folderico", "label", 28, 6, 18, 22);
				liqcell_setfont(	folderico, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				liqcell_setcaption(folderico, "ico" );
				liqcell_propsets(  folderico, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  folderico, "backcolor", "rgb(192,192,0)" );
				liqcell_propseti(  folderico, "textalign", 0 );
				liqcell_child_append(  folderitem, folderico);
				//############################# foldersize:label
				liqcell *foldersize = liqcell_quickcreatevis("foldersize", "label", 242, 6, 78, 22);
				liqcell_setfont(	foldersize, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				liqcell_setcaption(foldersize, "foldersize" );
				liqcell_propsets(  foldersize, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  foldersize, "backcolor", "rgb(224,224,224)" );
				liqcell_propseti(  foldersize, "textalign", 0 );
				liqcell_child_append(  folderitem, foldersize);
				//############################# foldername:label
				liqcell *foldername = liqcell_quickcreatevis("foldername", "label", 50, 6, 186, 22);
				liqcell_setfont(	foldername, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(foldername, "foldername" );
				liqcell_propsets(  foldername, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  foldername, "backcolor", "rgb(255,255,255)" );
				liqcell_propseti(  foldername, "textalign", 0 );
				liqcell_child_append(  folderitem, foldername);
				//############################# foldersubfolder:label
				liqcell *foldersubfolder = liqcell_quickcreatevis("foldersubfolder", "label", 50, 32, 270, 76);
				liqcell_setfont(	foldersubfolder, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				liqcell_setcaption(foldersubfolder, "foldersubfolder" );
				liqcell_propsets(  foldersubfolder, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  foldersubfolder, "backcolor", "rgb(224,224,224)" );
				liqcell_propseti(  foldersubfolder, "textalign", 0 );
				liqcell_child_append(  folderitem, foldersubfolder);
				//############################# folderplus:label
				liqcell *folderplus = liqcell_quickcreatevis("folderplus", "label", 4, 6, 18, 22);
				liqcell_setfont(	folderplus, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				liqcell_setcaption(folderplus, "ico" );
				liqcell_propsets(  folderplus, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  folderplus, "backcolor", "rgb(0,192,0)" );
				liqcell_propseti(  folderplus, "textalign", 0 );
				liqcell_child_append(  folderitem, folderplus);
			liqcell_child_append(  folderbackplane, folderitem);
			
		}
		
		liqcell_child_arrange_easycol(  folderbackplane );
		
		liqcell_handleradd(folderbackplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );
				
			
		liqcell_child_append(  foldertree, folderbackplane);
	liqcell_child_append(  self, foldertree);
	//############################# buttonaccept:commandbutton
	liqcell *buttonaccept = liqcell_quickcreatevis("buttonaccept", "commandbutton", 720, 432, 74, 42);
	liqcell_setfont(	buttonaccept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (22), 0) );
	liqcell_setcaption(buttonaccept, "OK" );
	liqcell_propsets(  buttonaccept, "backcolor", "rgb(0,255,0)" );
	liqcell_child_append(  self, buttonaccept);
	//############################# filelist:frame
	liqcell *filelist = liqcell_quickcreatevis("filelist", "frame", 406, 52, 392, 422);
	//liqcell_setfont(	filelist, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_setcaption(filelist, "Frame1" );
	//liqcell_propsets(  filelist, "textcolor", "rgb(255,255,255)" );
	//liqcell_propsets(  filelist, "backcolor", "rgb(64,64,64)" );
		//############################# filebackplane:frame
		liqcell *filebackplane = liqcell_quickcreatevis("filebackplane", "frame", 2, 6, 386, 64);
		//liqcell_setfont(	filebackplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_setcaption(filebackplane, "Frame1" );
		//liqcell_propsets(  filebackplane, "textcolor", "rgb(0,0,0)" );
		//liqcell_propsets(  filebackplane, "backcolor", "rgb(128,128,128)" );
		
		int f=0;
		for(f=0;f<200;f++)
		{
			//############################# fileitem:frame
			liqcell *fileitem = liqcell_quickcreatevis("fileitem", "frame", 4, 4, 378, 34);
			//liqcell_setfont(	fileitem, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
			//liqcell_setcaption(fileitem, "Frame1" );
			//liqcell_propsets(  fileitem, "textcolor", "rgb(0,0,0)" );
			//liqcell_propsets(  fileitem, "backcolor", "rgb(192,192,192)" );
				//############################# filename:label
				liqcell *filename = liqcell_quickcreatevis("filename", "label", 24, 6, 198, 22);
				liqcell_setfont(	filename, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (17), 0) );
				liqcell_setcaption(filename, "filename" );
				liqcell_propsets(  filename, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  filename, "backcolor", "rgb(255,255,255)" );
				liqcell_propseti(  filename, "textalign", 0 );
				liqcell_child_append(  fileitem, filename);
				//############################# filesize:label
				liqcell *filesize = liqcell_quickcreatevis("filesize", "label", 226, 6, 70, 22);
				liqcell_setfont(	filesize, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				liqcell_setcaption(filesize, "filesize" );
				liqcell_propsets(  filesize, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  filesize, "backcolor", "rgb(224,224,224)" );
				liqcell_propseti(  filesize, "textalign", 0 );
				liqcell_child_append(  fileitem, filesize);
				//############################# filedate:label
				liqcell *filedate = liqcell_quickcreatevis("filedate", "label", 300, 6, 74, 22);
				liqcell_setfont(	filedate, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				liqcell_setcaption(filedate, "filedate" );
				liqcell_propsets(  filedate, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  filedate, "backcolor", "rgb(224,224,224)" );
				liqcell_propseti(  filedate, "textalign", 0 );
				liqcell_child_append(  fileitem, filedate);
				//############################# fileico:label
				liqcell *fileico = liqcell_quickcreatevis("fileico", "label", 4, 6, 18, 22);
				liqcell_setfont(	fileico, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
				liqcell_setcaption(fileico, "ico" );
				liqcell_propsets(  fileico, "textcolor", "rgb(0,0,0)" );
				liqcell_propsets(  fileico, "backcolor", "rgb(192,192,0)" );
				liqcell_propseti(  fileico, "textalign", 0 );
				liqcell_child_append(  fileitem, fileico);
			liqcell_child_append(  filebackplane, fileitem);
		}
		
		liqcell_child_arrange_easycol(  filebackplane );
		
		liqcell_handleradd(filebackplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		
		
		
		liqcell_child_append(  filelist, filebackplane);
	liqcell_child_append(  self, filelist);
	//############################# label1:label
	liqcell *label1 = liqcell_quickcreatevis("label1", "label", 4, 324, 54, 64);
	liqcell_setfont(	label1, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label1, "root" );
	liqcell_propsets(  label1, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label1, "backcolor", "rgb(0,128,128)" );
	liqcell_propsets(  label1, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label1, "textalign", 2 );
	liqcell_child_append(  self, label1);
	//############################# label7:label
	liqcell *label7 = liqcell_quickcreatevis("label7", "label", 4, 252, 54, 64);
	liqcell_setfont(	label7, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label7, "mmc2" );
	liqcell_propsets(  label7, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label7, "backcolor", "rgb(0,128,128)" );
	liqcell_propsets(  label7, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label7, "textalign", 2 );
	liqcell_child_append(  self, label7);
	//############################# label6:label
	liqcell *label6 = liqcell_quickcreatevis("label6", "label", 6, 178, 52, 68);
	liqcell_setfont(	label6, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label6, "mmc1" );
	liqcell_propsets(  label6, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label6, "backcolor", "rgb(0,128,128)" );
	liqcell_propsets(  label6, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label6, "textalign", 2 );
	liqcell_child_append(  self, label6);
	//############################# label5:label
	liqcell *label5 = liqcell_quickcreatevis("label5", "label", 6, 96, 52, 76);
	liqcell_setfont(	label5, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(label5, "docs" );
	liqcell_propsets(  label5, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  label5, "backcolor", "rgb(0,128,128)" );
	liqcell_propsets(  label5, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  label5, "textalign", 2 );
	liqcell_child_append(  self, label5);
	//############################# icon:label
	liqcell *icon = liqcell_quickcreatevis("icon", "label", 6, 8, 52, 40);
	liqcell_setfont(	icon, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(icon, "icon" );
	liqcell_propsets(  icon, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  icon, "backcolor", "rgb(0,0,128)" );
	liqcell_propsets(  icon, "bordercolor", "rgb(200,100,100)" );
	liqcell_propseti(  icon, "textalign", 2 );
	liqcell_child_append(  self, icon);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 66, 6, 546, 42);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "file select" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "rgb(0,0,0)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_child_append(  self, title);
	liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	liqcell_handleradd(self, "resize", liqfileselect_resize );
	return self;
}

