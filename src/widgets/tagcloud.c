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

//#####################################################################
//#####################################################################
//##################################################################### tagcloud :: by gary birkett
//#####################################################################
//#####################################################################


int tagitem_autosave(char *tagname)
{
/*
	char filename[FILENAME_MAX];
	snprintf(filename,sizeof(filename),"/media/mmc1/_tag/liq.%s.tag",tagname);
	
	if(liqapp_fileexists(filename))
	{
		// file already exists
		return 0;
	}
	
	liqapp_log("tagitem filesave, saving to '%s'",filename);


	FILE *fd;
	//int   ri;
	fd = fopen(filename, "w");
	if(fd==NULL){ liqapp_log("tagitem filesave, cannot open '%s' for writing",filename); return -1; }
	// actual file data

	liqapp_log("tagitem filesave, writing head");

	fprintf(fd,									"tag:%s\n",
																									tagname
																									);

	liqapp_log("tagitem filesave, writing matching files");

	// loop through the tagitem's contents and list all matching files

	liqapp_log("tagitem filesave, closing");			
	fclose(fd);
	liqapp_log("tagitem filesave, finished");
	
	// should also now update the tagmaster with the stats
	// the tagmaster contains a list of the tags and the number of links they contain
 */	
	return 0;
}











	static int tagitem_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
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
					int ttw = liqfont_textwidth(font,tagname);
					int tth = liqfont_textheight(font);
					
					
					
					liqcell *c = liqcell_quickcreatevis(tagname,   "tagitem",   0,0,ttw*1.2,tth    );
					liqcell_setfont(	c, font );
					
					liqcell_propseti(c,"autosize",1);
					liqcell_propseti(c,"textalign",2);
					//liqcell_propseti(c,"lockaspect",1);
					//liqcell_propsets(c,"imagefilename",fn);
					//liqcell_handleradd(c,    "mouse",   widget_mouse);
					liqcell_handleradd(c,    "click",   tagitem_click);


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
    tagcloud_insert(tagcloud,"animals", 15);
    tagcloud_insert(tagcloud,"architecture", 20);
    tagcloud_insert(tagcloud,"art", 29);
    tagcloud_insert(tagcloud,"asia", 12);
    tagcloud_insert(tagcloud,"australia", 23);
    tagcloud_insert(tagcloud,"autumn", 12);
    tagcloud_insert(tagcloud,"baby", 20);
    tagcloud_insert(tagcloud,"band", 14);
    tagcloud_insert(tagcloud,"barcelona", 15);
    tagcloud_insert(tagcloud,"beach", 29);
    tagcloud_insert(tagcloud,"berlin", 15);
    tagcloud_insert(tagcloud,"bike", 12);
    tagcloud_insert(tagcloud,"bird", 14);
    tagcloud_insert(tagcloud,"birthday", 26);
    tagcloud_insert(tagcloud,"black", 18);
    tagcloud_insert(tagcloud,"blackandwhite", 15);
    tagcloud_insert(tagcloud,"blue", 23);
    tagcloud_insert(tagcloud,"bw", 22);
    tagcloud_insert(tagcloud,"california", 29);
    tagcloud_insert(tagcloud,"cameraphone", 12);
    tagcloud_insert(tagcloud,"canada", 23);
    tagcloud_insert(tagcloud,"canon", 29);
    tagcloud_insert(tagcloud,"car", 17);
    tagcloud_insert(tagcloud,"cat", 21);
    tagcloud_insert(tagcloud,"chicago", 20);
    tagcloud_insert(tagcloud,"china", 25);
    tagcloud_insert(tagcloud,"christmas", 25);
    tagcloud_insert(tagcloud,"church", 16);
    tagcloud_insert(tagcloud,"city", 24);
    tagcloud_insert(tagcloud,"clouds", 17);
    tagcloud_insert(tagcloud,"color", 14);
    tagcloud_insert(tagcloud,"concert", 21);
    tagcloud_insert(tagcloud,"cute", 12);
    tagcloud_insert(tagcloud,"dance", 14);
    tagcloud_insert(tagcloud,"day", 16);
    tagcloud_insert(tagcloud,"de", 18);
    tagcloud_insert(tagcloud,"dog", 21);
    tagcloud_insert(tagcloud,"england", 21);
    tagcloud_insert(tagcloud,"europe", 25);
    tagcloud_insert(tagcloud,"fall", 14);
    tagcloud_insert(tagcloud,"family", 30);
    tagcloud_insert(tagcloud,"fashion", 13);
    tagcloud_insert(tagcloud,"festival", 21);
    tagcloud_insert(tagcloud,"film", 17);
    tagcloud_insert(tagcloud,"florida", 19);
    tagcloud_insert(tagcloud,"flower", 25);
    tagcloud_insert(tagcloud,"flowers", 25);
    tagcloud_insert(tagcloud,"food", 22);
    tagcloud_insert(tagcloud,"football", 13);
    tagcloud_insert(tagcloud,"france", 26);
    tagcloud_insert(tagcloud,"friends", 27);
    tagcloud_insert(tagcloud,"fun", 22);
    tagcloud_insert(tagcloud,"garden", 19);
    tagcloud_insert(tagcloud,"geotagged", 18);
    tagcloud_insert(tagcloud,"germany", 22);
    tagcloud_insert(tagcloud,"girl", 19);
    tagcloud_insert(tagcloud,"girls", 12);
    tagcloud_insert(tagcloud,"graffiti", 16);
    tagcloud_insert(tagcloud,"green", 21);
    tagcloud_insert(tagcloud,"halloween", 17);
    tagcloud_insert(tagcloud,"hawaii", 16);
    tagcloud_insert(tagcloud,"hiking", 12);
    tagcloud_insert(tagcloud,"holiday", 22);
    tagcloud_insert(tagcloud,"home", 14);
    tagcloud_insert(tagcloud,"house", 17);
    tagcloud_insert(tagcloud,"india", 19);
    tagcloud_insert(tagcloud,"ireland", 14);
    tagcloud_insert(tagcloud,"island", 14);
    tagcloud_insert(tagcloud,"italia", 13);
    tagcloud_insert(tagcloud,"italy", 27);
    tagcloud_insert(tagcloud,"japan", 31);
    tagcloud_insert(tagcloud,"july", 13);
    tagcloud_insert(tagcloud,"kids", 16);
    tagcloud_insert(tagcloud,"la", 13);
    tagcloud_insert(tagcloud,"lake", 18);
    tagcloud_insert(tagcloud,"landscape", 19);
    tagcloud_insert(tagcloud,"light", 17);
    tagcloud_insert(tagcloud,"live", 19);
    tagcloud_insert(tagcloud,"london", 29);
    tagcloud_insert(tagcloud,"love", 12);
    tagcloud_insert(tagcloud,"macro", 20);
    tagcloud_insert(tagcloud,"me", 21);
    tagcloud_insert(tagcloud,"mexico", 20);
    tagcloud_insert(tagcloud,"mountain", 13);
    tagcloud_insert(tagcloud,"mountains", 13);
    tagcloud_insert(tagcloud,"museum", 15);
    tagcloud_insert(tagcloud,"music", 27);
    tagcloud_insert(tagcloud,"nature", 29);
    tagcloud_insert(tagcloud,"new", 24);
    tagcloud_insert(tagcloud,"newyork", 24);
    tagcloud_insert(tagcloud,"newyorkcity", 13);
    tagcloud_insert(tagcloud,"night", 23);
    tagcloud_insert(tagcloud,"nikon", 30);
    tagcloud_insert(tagcloud,"nyc", 25);
    tagcloud_insert(tagcloud,"ocean", 15);
    tagcloud_insert(tagcloud,"old", 13);
    tagcloud_insert(tagcloud,"paris", 26);
    tagcloud_insert(tagcloud,"park", 25);
    tagcloud_insert(tagcloud,"party", 32);
    tagcloud_insert(tagcloud,"people", 24);
    tagcloud_insert(tagcloud,"photo", 16);
    tagcloud_insert(tagcloud,"photography", 17);
    tagcloud_insert(tagcloud,"photos", 13);
    tagcloud_insert(tagcloud,"portrait", 24);
    tagcloud_insert(tagcloud,"red", 22);
    tagcloud_insert(tagcloud,"river", 16);
    tagcloud_insert(tagcloud,"rock", 18);
    tagcloud_insert(tagcloud,"san", 16);
    tagcloud_insert(tagcloud,"sanfrancisco", 23);
    tagcloud_insert(tagcloud,"scotland", 15);
    tagcloud_insert(tagcloud,"sea", 19);
    tagcloud_insert(tagcloud,"seattle", 18);
    tagcloud_insert(tagcloud,"show", 19);
    tagcloud_insert(tagcloud,"sky", 24);
    tagcloud_insert(tagcloud,"snow", 24);
    tagcloud_insert(tagcloud,"spain", 22);
    tagcloud_insert(tagcloud,"spring", 19);
    tagcloud_insert(tagcloud,"street", 20);
    tagcloud_insert(tagcloud,"summer", 25);
    tagcloud_insert(tagcloud,"sun", 15);
    tagcloud_insert(tagcloud,"sunset", 23);
    tagcloud_insert(tagcloud,"taiwan", 21);
    tagcloud_insert(tagcloud,"texas", 18);
    tagcloud_insert(tagcloud,"thailand", 18);
    tagcloud_insert(tagcloud,"tokyo", 20);
    tagcloud_insert(tagcloud,"toronto", 14);
    tagcloud_insert(tagcloud,"tour", 12);
    tagcloud_insert(tagcloud,"travel", 32);
    tagcloud_insert(tagcloud,"tree", 18);
    tagcloud_insert(tagcloud,"trees", 17);
    tagcloud_insert(tagcloud,"trip", 27);
    tagcloud_insert(tagcloud,"uk", 21);
    tagcloud_insert(tagcloud,"urban", 15);
    tagcloud_insert(tagcloud,"usa", 27);
    tagcloud_insert(tagcloud,"vacation", 28);
    tagcloud_insert(tagcloud,"vancouver", 12);
    tagcloud_insert(tagcloud,"washington", 16);
    tagcloud_insert(tagcloud,"water", 26);
    tagcloud_insert(tagcloud,"wedding", 36);
    tagcloud_insert(tagcloud,"white", 20);
    tagcloud_insert(tagcloud,"winter", 23);
    tagcloud_insert(tagcloud,"yellow", 14);
    tagcloud_insert(tagcloud,"york", 13);
    tagcloud_insert(tagcloud,"zoo", 17);
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
	    tagcloud_insert(body,searchterm, 45);
		
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
		liqcell_setrect(search, self->w*0.2 ,self->h-40,   self->w*0.4, 40);
		//liqcell_setrect(search, self->w*0.2 ,0,   self->w*0.4, 40);
		
		
		liqcell *body = liqcell_child_lookup(self,"body");
		liqcell_setrect(body,   0,40,self->w,self->h-40);
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

liqcell *tagcloud_create()
{
	liqcell *self = liqcell_quickcreatewidget("tagcloud","form", 800,480);

	if(self)
	{
		//############################# title:label
		liqcell *title = liqcell_quickcreatevis("title", "label", 0,0, 400, 40);
		liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
		liqcell_setcaption(title, "Select tags:" );
		liqcell_propsets(  title, "textcolor", "rgb(255,0,0)" );
		liqcell_propsets(  title, "backcolor", "rgb(0,0,60)" );
		liqcell_propseti(  title, "textalign", 0 );
		liqcell_child_append(  self, title);
	 
		//############################# accept:label
		liqcell *accept = liqcell_quickcreatevis("accept", "label", 600, 440, 200, 40);
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

