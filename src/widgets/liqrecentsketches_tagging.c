
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_dllcache.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqcell_arrange.h>
#include <liqbase/liqtag.h>
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################

// this is initial tag cloud reader

// it should scan/parse/generate a tagcloud
//

// returning a liqcell version saves on generating a whole classset
// however being latebound causes issues



//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################


static int liqcell_child_arrange_easytile_hero(liqcell *self)
{
	// arrange the contents of self like a hero would.
	int sgw = self->w;
	int sgh = self->h;
	liqcell *par = liqcell_getlinkparent(self);

	sgw = par->w;
	liqcell_setsize(self, par->w, par->h );	
	
	int res=0;
	int cnt = liqcell_child_countvisible(self);
	if(cnt<=1)
		{   res = liqcell_child_arrange_easytile(self);   }
	else if(cnt<=2)
		{   res = 
			liqcell_child_arrange_makegrid(self, 1,2);   }		
	else if(cnt<=3)
		{   res = liqcell_child_arrange_makegrid(self, 1,3);   }		
	else if(cnt<=4)
		{   res = liqcell_child_arrange_makegrid(self, 2,2);   }		
	else if(cnt<=5)
		{   res = liqcell_child_arrange_makegrid(self, 2,3);   }				
	else if(cnt<=8)
		{   res = liqcell_child_arrange_makegrid(self, 2,cnt-1);   }		
	else
		{   res = liqcell_child_arrange_makegrid(self, 2,8);   }		
		
//	res = liqcell_child_arrange_easytile(self);
	liqcell_setrect(self, 0,0, sgw, self->h );	

	return res;
}



// selection class to hold list of current selection
// slow basic model could simply recurse looking for the selected items
// list of tags
// for each file in selection, add all the tags
// each tag grows larger with the files contained ie the most used are higher in the list.
// if a tag is not used on a particular file, it becomes marked as a partial
// the remaining "default" tags are then made available marked, not in use.



static liqcell* current_selection=NULL;

static int monitor_run(liqcell *context);



void    liqcell_child_selectnone_recursive(liqcell *self,int autoremove)
{
	//liqcell_child_selectnone(self);

	liqcell *c = liqcell_getlinkchild_visual(self);
	while(c)
	{
		liqcell *d=liqcell_getlinknext_visual(c);
		liqcell_child_selectnone_recursive(c,autoremove);
		c=d;
	}

	if(liqcell_getselected(self))
	{
		liqcell_setselected(self,0);
		if(autoremove)
		{
			liqcell_setvisible(self,0);
			liqcell *par = liqcell_getlinkparent(self);
			if(par)
			{
				liqcell_child_remove(par,self);
				//liqcell_child_arrange_autoflow(par);
			}

		}
	}
	
}
//#####################################################################
//#####################################################################
//##################################################################### liqrecentsketches :: by gary birkett 
//#####################################################################
//#####################################################################

static int liqrecentsketches_clear_click(liqcell *self, liqcellclickeventargs *args, liqcell *liqrecentsketches)
{
	liqcell *backplane = liqcell_child_lookup( liqrecentsketches,"backplane");
	liqcell *body = liqcell_child_lookup( backplane,"body");
	liqcell *scroller = liqcell_child_lookup( liqrecentsketches,"scroller");
	liqcell *knob = liqcell_child_lookup( scroller,"knob");
	
	liqcell *selecttitle = liqcell_child_lookup( liqrecentsketches,"selecttitle");
	liqcell *selectgroup = liqcell_child_lookup( liqrecentsketches,"selectgroup");
	liqcell *selectbackplane = liqcell_child_lookup( selectgroup,"selectbackplane");
	liqcell *selectcount = liqcell_child_lookup( liqrecentsketches,"selectcount");
	int selectcnt = liqcell_child_countvisible(selectbackplane);

	// must clear all items


	liqcell_child_removeallvisual(selectbackplane);
	liqcell_child_selectnone_recursive(body,0);

	liqcell_setcaption(selecttitle,"");

	liqcell_setcaption_printf(selectcount, "%d items", 0);

}

static int liqrecentsketches_save_click(liqcell *self, liqcellclickeventargs *args, liqcell *liqrecentsketches)
{
	liqcell *backplane = liqcell_child_lookup( liqrecentsketches,"backplane");
	liqcell *body = liqcell_child_lookup( backplane,"body");
	liqcell *scroller = liqcell_child_lookup( liqrecentsketches,"scroller");
	liqcell *knob = liqcell_child_lookup( scroller,"knob");
	
	liqcell *selecttitle = liqcell_child_lookup( liqrecentsketches,"selecttitle");
	liqcell *selectgroup = liqcell_child_lookup( liqrecentsketches,"selectgroup");
	liqcell *selectbackplane = liqcell_child_lookup( selectgroup,"selectbackplane");
	liqcell *selectcount = liqcell_child_lookup( liqrecentsketches,"selectcount");
	int selectcnt = liqcell_child_countvisible(selectbackplane);


	char *tagtitle = selecttitle->caption;
	if(!tagtitle || !*tagtitle) tagtitle="notag";


	char filedate[256] = "";
	char filename[FILENAME_MAX] = "";
	liqapp_formatnow(filedate,sizeof(filedate),"yyyymmdd_hhmmss");
	snprintf(filename,sizeof(filename), "%s/tags/liq.%s.%s.tag.%s",    app.userdatapath,    filedate,    app.username,  tagtitle  );
		



	liqapp_log("liqrecentsketches tag filesave, saving to '%s'",filename);

	FILE *fd;
	//int   ri;
	fd = fopen(filename, "w");
	if(fd==NULL){ liqapp_log("filesave, cannot open '%s' for writing",filename); return -1; }
	// actual file data

	liqapp_log("filesave, writing head");

	fprintf(fd,									"tag:'%s'\n",
																						tagtitle
																						);
	liqapp_log("filesave, writing files");
	liqcell *fileitem = liqcell_getlinkchild_visual( selectbackplane );
	while(fileitem)
	{
		
		fprintf(fd,								"\tfile:'%s', '%s'\n",
																						liqapp_filename_walkoverpath(fileitem->name),
																						fileitem->name
																						);

		fileitem = liqcell_getlinknext_visual(fileitem);
	}
	liqapp_log("filesave, closing");			
	fclose(fd);
	liqapp_log("filesave, finished");



	liqcell_child_selectnone_recursive(body,1);


	liqrecentsketches_clear_click(self,args,liqrecentsketches);
	return 0;
}












	int liqrecentsketches_sketchitem_click(liqcell *self, liqcellclickeventargs *args, liqcell *liqrecentsketches)
	{
//liqapp_log("hello click edit!");
		//liqcell *mydialog = quickdialog_create();
		//liqcell_easyrun(mydialog);
		//liqcell_release(mydialog);

		char *sketchfilename  = liqcell_propgets(self,"sketchfilename",NULL);		
		if(!sketchfilename) return -1;
		
//liqapp_log("hello click edit!2 '%s'",sketchfilename);

		if(liqcell_getselected(self))
		{
//liqapp_log("hello click edit!3");
			liqcell *selectgroup = liqcell_child_lookup( liqrecentsketches,"selectgroup");
			liqcell *selectbackplane = liqcell_child_lookup( selectgroup,"selectbackplane");
			liqcell *selectitem = liqcell_child_lookup_simple( selectbackplane,sketchfilename);

			if(selectitem)
			{
//liqapp_log("hello click edit!4");
				liqcell_child_remove(selectbackplane,selectitem);
				liqcell_release(selectitem);


				liqcell_child_arrange_easytile_hero(	selectbackplane );		

			}	
			
			else
			{
				
				liqcell_print(selectgroup,"hello hmm 4.5: ",3);
			
			}
//liqapp_log("hello click edit!5");			



			liqcell *selectcount = liqcell_child_lookup( liqrecentsketches,"selectcount");
			int selectcnt = liqcell_child_countvisible(selectbackplane);
			liqcell_setcaption_printf(selectcount, "%d items", selectcnt);


			liqcell_setselected(self,0);
			current_selection=NULL;
			return 0;	

		}
//liqapp_log("hello click edit!6");
		liqcell_setselected(self,1);

//		if(current_selection && current_selection!=self)
//			liqcell_setselected(current_selection,0);
		
		
			liqcell *selectgroup = liqcell_child_lookup( liqrecentsketches,"selectgroup");
			liqcell *selectbackplane = liqcell_child_lookup( selectgroup,"selectbackplane");
			
				liqcell *c = liqcell_quickcreatevis(sketchfilename,   "sketch",   0,0,(selectgroup->w/5),(selectgroup->h/4)    );
				liqcell_propseti(c,"lockaspect",1);
				liqcell_propsets(c,"sketchfilename",sketchfilename);
				liqcell_child_insert( selectbackplane, c);
				liqcell_child_arrange_easytile_hero(	selectbackplane );


			liqcell *selectcount = liqcell_child_lookup( liqrecentsketches,"selectcount");
			int selectcnt = liqcell_child_countvisible(selectbackplane);
			liqcell_setcaption_printf(selectcount, "%d items", selectcnt);


		current_selection = self;
//liqapp_log("hello click edit!7");
		return 0;


		//char *sketchfilename  = liqcell_propgets(self,"sketchfilename",NULL);		
		//if(!sketchfilename) return -1;
		
		liqsketch *mysketch=liqsketch_newfromfile(sketchfilename);//   liqcell_getsketch(self);
		if(!mysketch)return -1;



		
		liqcell * top = liqcell_quickcreatevis("liqtop1", "liqtop", 0,0, 800,480);
		
		liqcell_setsketch(top, mysketch );
		
		//liqcell_propseti(top,"autorotate",1);
		
		
	//	args->newdialogtoopen = top;

		liqcell_release(top);
		

		return 1;
	}	
	


	static int liqrecentsketches_sketch_insert(liqcell *self,char *filenamebuffer)
	{
		liqcell *backplane = liqcell_child_lookup( self,"backplane");
		liqcell *body = liqcell_child_lookup( backplane,"body");

		//liqapp_log("gary: [[%s]]",filenamebuffer);

		struct pagefilename pfn;
	
		if(	(pagefilename_breakapart(&pfn,filenamebuffer) == 0) )
		{
		
			char buf[FILENAME_MAX];			snprintf(buf,sizeof(buf),"%s%s",pfn.filedate,pfn.filetitle);
		
			//liqapp_log("ins 1 %s",filenamebuffer);
			// valid file		
			char b[255]={0};
			snprintf(b,5,"%s",pfn.filedate); b[4]='\0';
			liqcell *xy=liqcell_child_lookup(body,b);
			if(!xy)
			{
				//liqapp_log("ins 2 %s",filenamebuffer);
				xy=liqcell_quickcreatevis(b,"year",  0,0, (backplane->w),backplane->h/15);
				liqcell_child_insertsortedbyname(body,xy,0);
				//snprintf(b,5,"%s",pfn.filedate); b[4]='\0';
				//brk=addframe(xy,b,(self->w),self->h/15);				// year break tile
				//brk->style=odd;
			}
		
			//liqapp_log("ins 3 %s",filenamebuffer);
		
		
				snprintf(b,3,"%s",&pfn.filedate[4]); b[2]='\0';
				liqcell *xm=liqcell_child_lookup(xy,b);
				if(!xm)
				{
					//liqapp_log("ins 4 %s",filenamebuffer);
					xm=liqcell_quickcreatevis(b,"month",  0,0, (backplane->w),backplane->h/15);
					liqcell_child_insertsortedbyname(xy,xm,0);
					//snprintf(b,7,"%s",pfn.filedate); b[6]='\0';
					//brk=addframe(xm,b,(self->w),self->h/15);			// month break tile
					//brk->style=odd;
				}
			
				//liqapp_log("ins 5 %s",filenamebuffer);
			
					snprintf(b,3,"%s",&pfn.filedate[6]); b[2]='\0';
					liqcell *xd=liqcell_child_lookup(xm,b);
					if(!xd)
					{
						//liqapp_log("ins 6 %s",filenamebuffer);
						xd=liqcell_quickcreatevis(b,"day",  0,0, (backplane->w),backplane->h/15);
						liqcell_child_insertsortedbyname(xm,xd,0);
					
						//liqapp_log("ins 7 %s",filenamebuffer);
						// add title header

						snprintf(b,10,"_%s",pfn.filedate); b[9]='\0';
						liqcell *brk=liqcell_quickcreatevis(b,"label",  0,0, (backplane->w),backplane->h/15);


						liqcell_setfont(	brk, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
					
						snprintf(b,9,"%s",pfn.filedate); b[8]='\0';
					
						liqcell_setcaption(brk, b );
						liqcell_propsets(  brk, "textcolor", "rgb(255,255,255)" );
						liqcell_propsets(  brk, "backcolor", "rgb(0,0,100)");
						liqcell_propseti(  brk, "textalign", 0 );

						liqcell_child_append(xd,brk);
					}
				
					//liqapp_log("ins 8 %s",filenamebuffer);
				

					liqcell *c = liqcell_quickcreatevis(buf,   "sketch",   0,0,(backplane->w/5),(backplane->h/4)    );
					liqcell_propseti(c,"lockaspect",1);
					liqcell_propsets(c,"sketchfilename",filenamebuffer);
					liqcell_handleradd_withcontext(c,"click",liqrecentsketches_sketchitem_click,self);
				
						//	liqcell_propseti(c,"autorotate",1);

				
				
					liqcell_child_insertsortedbyname( xd, c,0);
				
					//liqapp_log("ins 9 %s",filenamebuffer);
				
					liqcell_setsize(xd, backplane->w, backplane->h/15 );
					liqcell_child_arrange_autoflow(xd);
				liqcell_child_arrange_easycol(xm);			
			liqcell_child_arrange_easycol(xy);
				
			liqcell_child_arrange_easycol(body);
			//liqcell_setsize(body,body->w,body->h-700);	
			liqcell_setsize(body,body->w,body->h);			// hmm random offset needed only for huge number of sketches.
		
		}
	}



	





	static int liqrecentsketches_sketch_add(liqcell *self,char *filenamebuffer)
	{
		// 20090528_215559 lcuk : first attempt at runtime expansion
		// 20090528_215639 lcuk : its a hack because i should be using the filemonitor class elsewhere
		// 20090528_215654 lcuk : and it should be automatic
		// 20090528_215943 lcuk : class should be pre-tested or something here
		// 20090528_215951 lcuk : this runtime function would obviously be too slow for normal use

		liqapp_log("adding %s",filenamebuffer);

		struct pagefilename pfn;
	
		if(	(pagefilename_breakapart(&pfn,filenamebuffer) == 0) )
		{
			liqrecentsketches_sketch_insert(self,filenamebuffer);
			return 0;
		}
		return 0;
	}
















	static int widget_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		args->newdialogtoopen = liqcell_hold( self );//liqcell_child_lookup( self, "body" );
		return 1;
	}

	static liqcell *quickdialog_create()
	{
		liqcell *self = liqcell_quickcreatewidget("editoverlay","edit", 800,480);
		if(self)
		{
			liqcell *c;
						c = liqcell_quickcreatevis("sketching",   "picture",   0,0,   800,480    );
						liqcell_propseti(c,"lockaspect",1);					
						liqcell_propsets(c,"imagefilename","media/lcuk_sig_headshot.png");
						//liqcell_handleradd(c,    "mouse",   widget_mouse);
						//liqcell_handleradd(c,    "click",   edit_click);
						liqcell_child_append( self, c );
		}
		return self;
	}
	
		
	
	static int edit_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqapp_log("hello click edit!");
		liqcell *mydialog = quickdialog_create();
	//	liqcell_easyrun(mydialog);
		return 1;
	}	
	
	

	static int liqcell_scan_folder_for_images(liqcell *self,char *path)
	{
		liqtagnode *systemnode = liqtagcloud_findnode(system_tagcloud,   liqcell_propgets(  self, "monitortag","")    );

		

	
		liqcell *backplane = liqcell_child_lookup( self,"backplane");
		liqcell *body = liqcell_child_lookup( backplane,"body");
	
	
			char *widgetpath = path;
			DIR           *	dir_p;
			struct dirent *	dir_entry_p;
			char 			fn[FILENAME_MAX+1];
			char          * ft;
		
			struct pagefilename pfn;
		
			dir_p = opendir( widgetpath );			
			if(!dir_p)
			{
				liqapp_log("liqcell_scan_folder_for_images opendir failed: '%s'",widgetpath);
				return -1;			// heh thanks kot :)
			}				
			while( NULL != (dir_entry_p = readdir(dir_p)))
			{
				if( dir_entry_p->d_name[0]=='.' )
					continue;
			
				ft=dir_entry_p->d_name;
			
				snprintf(fn , FILENAME_MAX , "%s/%s", widgetpath , ft);
			
				struct stat     statbuf;
				if(stat(fn, &statbuf) == -1)
				{
					liqapp_log("liqcell_scan_folder_for_images stat failed: '%s'",fn);
					return -1;
				}
				// got the information we need
				if ( S_ISREG(statbuf.st_mode) )
				{
					char *ext=liqapp_filename_walktoextension(ft);
					if(!ext || !*ext)
					{
						// nothing to see here..
					}

					else
					//if(
					//	strcasecmp(ext,"page")==0 ||
					//	strcasecmp(ext,"sketch")==0 
					//  )
				
					if(	stristr(ft,"liq.") && (pagefilename_breakapart(&pfn,ft) == 0) )
					{
						int isok = 0;

						if(systemnode)
						{
							// system tag, show only items in this tag
							isok = (liqtagnode_findleaf( systemnode, ft ));
						}
						else
						{
							// no system tag, show all untagged items
							isok = liqtagcloud_containsleaf( system_tagcloud, ft ) == 0;
						}
					
						

						if(isok)
						{					
							liqrecentsketches_sketch_insert(self,fn);
						}
					}
				}
			}
			closedir(dir_p);
	}


//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################


	static int liqrecentsketches_body_move(liqcell *self, liqcelleventargs *args, void *liqrecentsketches)
	{
		liqcell *backplane = liqcell_child_lookup( liqrecentsketches,"backplane");
		liqcell *body = liqcell_child_lookup( backplane,"body");
		
		liqcell *scroller = liqcell_child_lookup( liqrecentsketches,"scroller");
		liqcell *knob = liqcell_child_lookup( scroller,"knob");

		

		double range = (double)( body->h - backplane->h );
		double pos   = (double)(-body->y);
		double frac = 0;
		if(range==0)
			frac = 0;
		else
			frac = pos / range ;


		liqcell_setpos(knob,  0, scroller->h * frac );
		liqcell_forceinboundparent(knob);
		

				
		
		return 1;
	}

	static int liqrecentsketches_edit_click(liqcell *self, liqcellclickeventargs *args, liqcell *liqrecentsketches)
	{


		if(current_selection)
		{
			char *fn = liqcell_propgets(current_selection,"sketchfilename",NULL);
			if(fn && *fn)
			{
				// do edit action, ala liqcalendar
				liqcell *editor = liqcell_quickcreatevis("editor", "liqsketchedit", 0,0 , 800, 480);
				liqcell_propsets(editor,"sketchfilename",fn);
				//liqcell_propsets(editor,"sketcheditfilename",fn);
				liqcell_easyrun(editor);
				liqcell_release(editor);
			}
		}
		//args->newdialogtoopen = liqcell_hold( self );//liqcell_child_lookup( self, "body" );
		return 1;
	}


	int liqrecentsketches_scroller_mouse(liqcell *self, liqcellmouseeventargs *args, void *liqrecentsketches)
	{


		liqapp_log("knob mouse!");



		


		liqcell *backplane = liqcell_child_lookup( liqrecentsketches,"backplane");
		liqcell *body = liqcell_child_lookup( backplane,"body");
		
		liqcell *scroller = liqcell_child_lookup( liqrecentsketches,"scroller");
		liqcell *knob = liqcell_child_lookup( scroller,"knob");


		int py = args->mey - scroller->y ;	
		if(py<0)py=0;
		if(py<knob->h/2)py=knob->h/2;
		if(py>scroller->h-knob->h/2)py=scroller->h-knob->h/2;

		//liqcell_setpos(knob, 0, py - (knob->h/2) );
		

		//liqcell_forceinboundparent(knob);

		double range = scroller->h - knob->h;
		double pos = py - (knob->h/2);
		double frac = 0;
		if(range==0)
			frac = 0;
		else
			frac = pos / range ;

		double outrange = body->h - backplane->h;
		if(outrange<0)outrange=0;


		liqapp_log("knob %d :: %3.3f %3.3f %3.3f  == %3.3f :: %3.3f",py, range,pos,frac, outrange, outrange * frac);


		liqcell_setpos( body,0, -outrange * frac );

		
		return 0;
	}





static int timer_tick(liqcell *self, liqcellmouseeventargs *args, liqcell *context)
{
	liqcell_propseti(self,"timerinterval", 32767 );
	liqcell_setenabled(self,0);
	// now, run the channel? :D
	//liqfilemonitor_run((liqcell*)self->tag);
	monitor_run(context);
	
	return 0;
}



static int widget_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{

	liqcell *backplane = liqcell_child_lookup( self,"backplane");
		liqcell *body = liqcell_child_lookup( backplane,"body");
	liqcell *timer1 = liqcell_child_lookup( self,"timer1");


	char buf[FILENAME_MAX];    snprintf(buf,sizeof(buf),"%s/sketches",app.userdatapath);
	if(liqapp_pathexists(buf))
	{
	
		liqcell_propsets(  self, "monitorpath" , buf);
		liqcell_scan_folder_for_images(self,buf);
		liqcell_setenabled(timer1,1);
		liqcell_setpos(body,0,-(body->h-backplane->h));


	}

	return 0;
}


//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################







liqcell *liqrecentsketches_tagging_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqrecentsketches_tagging","form", 800,480);

	if(self)
	{
	//	liqcell_propsets(  self, "backcolor", "rgb(255,255,255)" );

		//liqcell_propseti(self,"autorotate",1);



{
	
	
	liqcell *backplane = liqcell_quickcreatevis("backplane","frame",self->w*0.1 ,0,   self->w*0.7,self->h);
	liqcell_child_insert( self, backplane );
		liqcell *body = liqcell_quickcreatevis("body","frame",0 ,0,   backplane->w,self->h);
		liqcell_child_insert( backplane, body );
		
	//	liqcell_scan_folder_for_images(self,buf);
		
		//liqcell_propsets(  self, "monitorpath" , buf);
		//liqcell_propsets(  self, "watchpattern" , "liq.*");

	//	int cnt=0;
	//	liqcell *c=NULL;



		//liqcell_child_arrange_makegrid(body,3,3);

		//c=liqcell_lastchild(body);

		liqcell_handleradd_withcontext(body,    "mouse",   liqcell_easyhandler_kinetic_mouse, self );
		liqcell_handleradd_withcontext(body,    "move",    liqrecentsketches_body_move,       self );
		//liqcell_handleradd(self,    "click",   float_click);
		

	//############################# scroller:label
	liqcell *scroller = liqcell_quickcreatevis("scroller", "label", 0,56, self->w*0.1, self->h-56);
	//liqcell_setfont(	scroller, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	//liqcell_setcaption(scroller, "Scroller" );
	//liqcell_propsets(  scroller, "imagefilename", "media/titlebanner_left.png" );
	//liqcell_propsets(  scroller, "textcolor", "rgb(255,255,0)" );
	liqcell_propsets(  scroller, "backcolor", "rgb(0,0,60)" );
	liqcell_propseti(  scroller, "textalign", 0 );
	
	liqcell_handleradd_withcontext(scroller,    "mouse",   liqrecentsketches_scroller_mouse , self );

	liqcell_child_append(  self, scroller);

		//############################# knob:label
		liqcell *knob = liqcell_quickcreatevis("knob", "label", 0,0, 200, 50);
		//liqcell_setfont(	knob, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		//liqcell_setcaption(knob, "knob" );
		liqcell_propsets(  knob, "imagefilename", "media/blob.png" );
		liqcell_propsets(  knob, "textcolor", "rgb(255,255,0)" );
		liqcell_propsets(  knob, "backcolor", "rgb(0,60,0)" );
		liqcell_propseti(  knob, "textalign", 0 );

		
		liqcell_child_append(  scroller, knob);

		






// 20090619_221734 lcuk : VERY strange, if I compile with this block in place, when run from the console its ok
// 20090619_221809 lcuk : but when run from the icon the app closes and does not run
// 20090619_221830 lcuk : very curious


//#ifdef USE_INOTIFY
		//############################# timer1:liqtimer
		liqcell *timer1=liqcell_quickcreatevis("timer1",   "liqtimer",   0,0,   0,0 );
		// store ourselves on the tag for use later
		// this does feel like a workaround, but hell, it works!
		//liqcell_settag(timer1,liqcell_hold(self));
		liqcell_propseti(timer1,"timerinterval", 1 );
		liqcell_handleradd_withcontext(timer1,"timertick",timer_tick,self);
		liqcell_setenabled(timer1,0);
		liqcell_child_insert( self,timer1);
//#endif



		//############################# cmdselclear:button
		liqcell *cmdselclear = liqcell_quickcreatevis("cmdselclear", "button", self->w*0.8,self->h-56-56-244-56-28, self->w*0.05, 28);
		liqcell_setfont(	cmdselclear, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (15), 0) );
		liqcell_setcaption(cmdselclear, "Clear" );
		//liqcell_propsets(  cmdselclear, "imagefilename", "media/titlebanner_left.png" );
		liqcell_propsets(  cmdselclear, "textcolor", "rgb(255,255,0)" );
		liqcell_propsets(  cmdselclear, "backcolor", "xrgb(0,60,60)" );
		liqcell_propseti(  cmdselclear, "textalign", 2 );
		liqcell_propseti(  cmdselclear, "textaligny", 2 );
		liqcell_child_append(  self, cmdselclear);
		liqcell_handleradd_withcontext(cmdselclear,    "click",   liqrecentsketches_clear_click , self );

		//############################# cmdselinv:button
		liqcell *cmdselinv = liqcell_quickcreatevis("cmdselinv", "button", self->w*0.95,self->h-56-56-244-56-28, self->w*0.05, 28);
		liqcell_setfont(	cmdselinv, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (15), 0) );
		liqcell_setcaption(cmdselinv, "Inv" );
		//liqcell_propsets(  cmdselinv, "imagefilename", "media/titlebanner_left.png" );
		liqcell_propsets(  cmdselinv, "textcolor", "rgb(255,255,0)" );
		liqcell_propsets(  cmdselinv, "backcolor", "xrgb(60,0,60)" );
		liqcell_propseti(  cmdselinv, "textalign", 2 );
		liqcell_propseti(  cmdselinv, "textaligny", 2 );
		liqcell_child_append(  self, cmdselinv);
		//liqcell_handleradd_withcontext(cmdselinv,    "click",   liqrecentsketches_clear_click , self );


		liqcell_setvisible(cmdselinv,0);


		//############################# selecttitle:textbox
		liqcell *selecttitle = liqcell_quickcreatevis("selecttitle", "textbox", self->w*0.8,self->h-56-56-244-56, self->w*0.1, 56);
		liqcell_setfont(	selecttitle, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(selecttitle, "" );
		//liqcell_propsets(  selecttitle, "imagefilename", "media/titlebanner_left.png" );
		liqcell_propsets(  selecttitle, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  selecttitle, "backcolor", "rgb(0,60,0)" );
		liqcell_propsets(  selecttitle, "bordercolor", "xrgb(255,255,255)" );
		liqcell_propseti(  selecttitle, "textalign", 2 );
		liqcell_propseti(  selecttitle, "textaligny", 2 );
		liqcell_child_append(  self, selecttitle);


		//############################# selectgroup:box
		liqcell *selectgroup = liqcell_quickcreatevis("selectgroup", "box", self->w*0.8,self->h-56-56-244, self->w*0.1, 244);
		liqcell_propsets(  selectgroup, "backcolor", "xrgb(0,40,0)" );
		liqcell_propsets(  selectgroup, "bordercolor", "xrgb(255,255,255)" );
		liqcell_child_append(  self, selectgroup);
		
			//############################# selectbackplane:box
			liqcell *selectbackplane = liqcell_quickcreatevis("selectbackplane", "box", self->w*0.8,self->h-56-56-244, self->w*0.1, 244);
			//liqcell_propsets(  selectbackplane, "backcolor", "xrgb(0,40,0)" );
			//liqcell_propsets(  selectbackplane, "bordercolor", "xrgb(255,255,255)" );
			liqcell_child_append(  selectgroup, selectbackplane);

			liqcell_handleradd_withcontext(selectbackplane,    "mouse",   liqcell_easyhandler_kinetic_mouse, self );


		//############################# selectcount:label
		liqcell *selectcount = liqcell_quickcreatevis("selectcount", "label", self->w*0.8,self->h-56-56, self->w*0.1, 56);
		liqcell_setfont(	selectcount, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (20), 0) );
		liqcell_setcaption(selectcount, "0 items" );
		//liqcell_propsets(  selectcount, "imagefilename", "media/titlebanner_left.png" );
		liqcell_propsets(  selectcount, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  selectcount, "backcolor", "rgb(0,0,0)" );
		liqcell_propsets(  selectcount, "bordercolor", "xrgb(255,255,255)" );
		liqcell_propseti(  selectcount, "textalign", 2 );
		liqcell_propseti(  selectcount, "textaligny", 2 );
		liqcell_child_append(  self, selectcount);

		//############################# cmdedit:button
		liqcell *cmdedit = liqcell_quickcreatevis("cmdedit", "button", self->w*0.8,self->h-56, self->w*0.1, 56);
		liqcell_setfont(	cmdedit, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (20), 0) );
		liqcell_setcaption(cmdedit, "Save" );
		//liqcell_propsets(  cmdedit, "imagefilename", "media/titlebanner_left.png" );
		liqcell_propsets(  cmdedit, "textcolor", "rgb(255,255,0)" );
		liqcell_propsets(  cmdedit, "backcolor", "xrgb(0,0,60)" );
		liqcell_propseti(  cmdedit, "textalign", 2 );
		liqcell_propseti(  cmdedit, "textaligny", 2 );
		liqcell_child_append(  self, cmdedit);
		liqcell_handleradd_withcontext(cmdedit,    "click",   liqrecentsketches_save_click , self );




}



		liqcell_handleradd_withcontext(self, "shown", widget_shown ,self);


	}
	
	return self;
}




//http://darkeside.blogspot.com/2007/12/linux-inotify-example.html




























#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/inotify.h>





// 20090620_215315 lcuk : this was defined as 1024 units, WAY over the top

#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*32)


static void monitor_get_event(int fd, const char * target,liqcell *context)
{
   ssize_t len=0, i = 0;
   char action[81+FILENAME_MAX] = {0};
   char buff[BUFF_SIZE] = {0};
	//liqapp_log("inotify_getevent reading from '%s'",target);
   len = read (fd, buff, BUFF_SIZE);
   
   while (i < len)
   {
		liqapp_log("inotify_getevent '%s', %i %i",target,i,len);
      struct inotify_event *pevent = (struct inotify_event *)&buff[i];
      char action[81+FILENAME_MAX] = {0};
	  
	  if ( (pevent->len) )
	  {
		snprintf(action,sizeof(action),"%s/%s",target,pevent->name);	
		// dealing with a file
		  if(pevent->mask & IN_CLOSE_WRITE)
			liqrecentsketches_sketch_add(context,action);
	  }
      i += sizeof(struct inotify_event) + pevent->len;
   }
} 





static int monitor_run(liqcell *context)
{
   char *target;//[FILENAME_MAX];
   int result;
   int fd;
   int wd;   /* watch descriptor */

	char * folder = liqcell_propgets(context,"monitorpath",".");

	if( (!folder) || (!*folder) || (!liqapp_pathexists(folder)) )
	{
      liqapp_log( "inotify monitor path does not exist\n");
      return -1;		
	}

   //strcpy (target, folder);
   target=strdup(folder);
   if(!target)
   {
      liqapp_log( "inotify could not alloc target\n");
      return -1;	
   }
   
   liqapp_log("inotify about to init() for '%s'",target);
   fd = inotify_init();
   liqapp_log("inotify init() returned %i",fd);
   if (fd < 0)
   {
      liqapp_log( "monitor error init: %s\n", strerror(errno));
	  free(target);
      return 1;
   }
   liqapp_log("inotify about to add_watch for '%s'",target);
   wd = inotify_add_watch(fd, target, IN_CLOSE_WRITE);//IN_ALL_EVENTS);
   liqapp_log("inotify add_watch returned %i",wd);
   if (wd < 0)
   {
      liqapp_log( "monitor error add: %s\n", strerror(errno));
	  free(target);
      return -1;
   }
   
   liqapp_log("inotify looping for '%s'",target);

         //monitor_get_event(fd, target,context);
  
   while (1)
   {
		liqapp_sleep(25);
        monitor_get_event(fd, target,context);
   }
   
   free(target);

   return 0;
}
