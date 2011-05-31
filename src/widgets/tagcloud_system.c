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
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqtag.h>
//#####################################################################
//#####################################################################
//##################################################################### tagcloud :: by gary birkett
//#####################################################################
//#####################################################################


int tagitem_autosave(char *tagname)
{
	return 0;
}











	static int tagitem_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
		liqcell *mydialog = liqcell_quickcreatevis("mytags", "liqrecentsketches_tagging", 0,0, -1,-1);
		liqcell_propsets(mydialog, "monitortag",   liqcell_getcaption(self) );
		liqcell_easyrun(mydialog);
		liqcell_release(mydialog);
		return 0;
	


		//liqapp_log("general click");
		//args->newdialogtoopen = self;
		if(liqcell_getselected(self))
		{
				liqcell_setselected(self,0);
				liqcell_propremoves(self, "textcolor"   );
				liqcell_propremoves(self, "backcolor"   );
				//liqcell_propremoves(self, "bordercolor" );
		}
		else
		{
				liqcell_setselected(self,1);
				liqcell_propsets(self, "textcolor",   "rgb(0,255,0)" );
				liqcell_propsets(self, "backcolor",   "rgb(0,0,40)" );
				//liqcell_propsets(self, "bordercolor", "rgb(255,255,255)" );
		}
		return 1;
	}

liqcell *tagcloud_insert(liqcell *tagcloud,char *tagname, int tagpopularity)
{
	
	tagitem_autosave(tagname);
	
	
	liqcell *old = liqcell_local_lookup_nameclass(tagcloud,tagname,"tagitem");
	if(old)
	{
		// just bail politely :)
		if(!liqcell_getselected(old))
		{
			// select it :)
			tagitem_click(old,NULL,NULL);
		}
		return old;
	}
					
					
					liqfont *font = liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (tagpopularity * 2), 0);
					liqfont_setview(font,1,1);
					int ttw = liqfont_textwidth(font,tagname);
					int tth = liqfont_textheight(font);
					
					
					
					liqcell *c = liqcell_quickcreatevis(tagname,   "tagitem",   0,0,ttw*1.2,tth*1.4    );
					liqcell_setfont(	c, font );
					
				//	liqcell_propseti(c,"autosize",1);
					liqcell_propseti(c,"textaligny",1);
					//liqcell_propseti(c,"lockaspect",1);
					//liqcell_propsets(c,"imagefilename",fn);
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					liqcell_handleradd(c,    "click",   tagitem_click);
					
				//	liqcell_propsets(  c, "bordercolor", "rgb(0,150,50)" );


					liqcell_child_insertsorted( tagcloud, c );


		if(liqcell_propgeti(tagcloud,"autoselectnew",0))
		{
			// select it automatically :)
			tagitem_click(c,NULL,NULL);
		}
					
					return c;


}



void tagcloud_fillup_test(liqcell *tagcloud)
{


	liqtagnode *node = system_tagcloud->nodefirst;
	while(node)
	{

		tagcloud_insert(tagcloud, node->key, 15 + node->leafcount/8);

		node = node->linknext;
	}



    
}


//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
	static int search_click(liqcell *self, liqcelleventargs *args, liqcell *tagcloud)
	{
		// try to add this tag :)
		liqcell *body = liqcell_child_lookup(tagcloud,"body");
		char *searchterm = liqcell_getcaption(self);
		if(!searchterm || !*searchterm) return 1;
		//liqcell *body = liqcell_child_lookup(tagcloud,"body");
	    tagcloud_insert(body,searchterm, 26);
		
		liqcell_setcaption(self,"");
		return 1;
	}
	static int search_change(liqcell *self, liqcelleventargs *args, liqcell *tagcloud)
	{
		// examine each tag and if matches the search show it, otherwise dont..
		liqcell *body = liqcell_child_lookup(tagcloud,"body");
		char *searchterm = liqcell_getcaption(self);
		
		liqcell *c = liqcell_getlinkchild(body);
		while(c)
		{
			if(liqcell_isclass(c,"tagitem"))
			{
				if(searchterm && *searchterm)
				{
					if( strstr(c->name,searchterm) )
					{
						// found a match!
						liqcell_setvisible(c,1);
					}
					else
					{
						// no match :(
						liqcell_setvisible(c,0);
					}
				}
				else
				{
					// nothing to search for
					liqcell_setvisible(c,1);
				}
			}
			c=liqcell_getlinknext(c);
		}
		liqcell_setrect(body,   0,40,tagcloud->w,tagcloud->h-40);
		liqcell_child_arrange_autoflow( body );
		liqcell_setpos(body,0,40);
		
		if(!searchterm || !*searchterm)
		{
			// bit of magic here..
			liqcell_setvisible(self,0);
			
		}
		
		return 1;
		
	}
	static int tagcloud_resize(liqcell *self, liqcelleventargs *args, void *context)
	{
		liqcell *search = liqcell_child_lookup(self,"search");		
		liqcell_setrect(search, self->w*0.2 ,self->h-56,   self->w*0.4, 56);
		//liqcell_setrect(search, self->w*0.2 ,0,   self->w*0.4, 40);
		
		
		liqcell *body = liqcell_child_lookup(self,"body");
		liqcell_setrect(body,   0,56,self->w,self->h-56);
		//liqcell_setsize(body,   self->w,self->h);
		liqcell_child_arrange_autoflow( body );
		
		return 1;
	}
	
	
	static int tagcloud_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *tagcloud)
	{
		liqapp_log("tc.kp");
		// if we are getting this keypress, we shouldnt be
		// it should be the search button
		liqcell *search = liqcell_child_lookup(tagcloud,"search");
		liqcell_setvisible(search,1);
		liqcell_zorder_totop(search);
		return liqcell_handlerrun(search,"keypress",args);
	}
	static int tagcloud_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *tagcloud)
	{
		liqapp_log("tc.kr");
		// if we are getting this keypress, we shouldnt be
		// it should be the search button
		liqcell *search = liqcell_child_lookup(tagcloud,"search");
		//liqcell_setvisible(search,1);
		return liqcell_handlerrun(search,"keyrelease",args);
	}

liqcell *tagcloud_system_create()
{
	liqcell *self = liqcell_quickcreatewidget("tagcloud_system","form", 800,480);

	if(self)
	{
		//############################# title:label
		liqcell *title = liqcell_quickcreatevis("title", "label", 0,0, 800, 56);
		liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(title, "Select tags:" );
		liqcell_propsets(  title, "textcolor", "rgb(255,0,0)" );
		//liqcell_propsets(  title, "backcolor", "xrgb(0,0,60)" );
		liqcell_propseti(  title, "textalign", 0 );
		liqcell_child_append(  self, title);
	 
		//############################# accept:label
		liqcell *accept = liqcell_quickcreatevis("accept", "label", 600, 440, 200, 56);
		liqcell_setfont(	accept, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (35), 0) );
		liqcell_setcaption(accept, "save" );
		liqcell_propsets(  accept, "textcolor",   "rgb(0,255,0)" );
		liqcell_propsets(  accept, "backcolor",   "rgb(0,40,0)" );
		liqcell_propsets(  accept, "bordercolor", "rgb(0,150,0)" );
		liqcell_propseti(  accept, "textalign",   2 );
		liqcell_propseti(  accept, "textaligny",  2 );
		liqcell_child_append(  self, accept);
		
/*	
		liqcell *showall = liqcell_quickcreatevis("showall", "label", 350, 440, 200, 40);
		liqcell_setfont(	showall, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (35), 0) );
		liqcell_setcaption(showall, "clear search" );
		liqcell_propsets(  showall, "textcolor",   "rgb(0,100,100)" );
		liqcell_propsets(  showall, "backcolor",   "rgb(0,40,20)" );
		liqcell_propsets(  showall, "bordercolor", "rgb(0,150,50)" );
		liqcell_propseti(  showall, "textalign",   2 );
		liqcell_propseti(  showall, "textaligny",  2 );
		liqcell_child_append(  self, showall);
 */	

	
	
	
	
		liqcell *body = liqcell_quickcreatevis("body",NULL,0 ,0,   self->w,self->h);
		tagcloud_fillup_test( body );
		liqcell_child_arrange_autoflow( body );
		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );
		liqcell_child_insert( self, body );
		
		
		
		liqcell *search = liqcell_quickcreatevis("search","textbox",self->w*0.2 ,self->h-40,   self->w*0.4, 40);
		liqcell_setfont(   search,  liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_setcaption(search, "" );
		
		liqcell_propsets(  search, "textcolor",   "rgb(255,255,100)" );
		liqcell_handleradd_withcontext( search,    "click",           search_click,  self );
		liqcell_handleradd_withcontext( search,    "captionchange",   search_change, self );
		liqcell_setvisible(search,0);		// watch this!
		liqcell_child_insert( self, search );
		
		liqcell_handleradd_withcontext(body,    "keypress",   tagcloud_keypress,  self);
		liqcell_handleradd_withcontext(body,    "keyrelease", tagcloud_keyrelease,self);
		
		liqcell_handleradd_withcontext(self,    "keypress",   tagcloud_keypress,  self);
		liqcell_handleradd_withcontext(self,    "keyrelease", tagcloud_keyrelease,self);
		
		
		liqcell_handleradd(self,    "resize",   tagcloud_resize);


		tagcloud_resize(self,NULL,NULL);


		liqcell_propseti(  self, "autoselectnew",  2 );


	}

	return self;
}

