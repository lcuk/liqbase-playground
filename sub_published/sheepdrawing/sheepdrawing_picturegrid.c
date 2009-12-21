
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
#include <liqbase/liqapp_prefs.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>


#include  <stdio.h>
#include  <stdlib.h>
#include  <dlfcn.h>
#include <elf.h>

#define TRUE -1

//#####################################################################
//##################################################################### use glib and hildon to find correct thumbnail
//##################################################################### perhaps the most evil way to get these functions possible!
//##################################################################### breaks lots i know...
//#####################################################################

// use gobject and hildon to obtain a thumbnail filename...
// requires 5 dlsym functions

static char* (*g_filename_to_uri)()        = NULL;
static char* (*g_filename_from_uri)()      = NULL; 
static void  (*g_free)(void *)             = NULL;
static char* (*hildon_thumbnail_get_uri)() = NULL;
static char* (*hildon_thumbnail_factory_get_instance) ()=NULL;


int liqimage_find_thumbnail_for(char *resultbuffer,char *resultsize,char *bigimagefilename)
{
	// turbo mode!
	// no thumbnailing :o
	snprintf(resultbuffer,resultsize,"%s", bigimagefilename);
	return 0;


// todo - make this work.  albanc just went through this exact code with his amazing albanart patch

	int result=-1;
	if(!g_filename_to_uri || !g_filename_from_uri || !g_free || !hildon_thumbnail_get_uri)
	{
		liqapp_log("thumb dlloading");
		// add them via dlsym
		// evilness!
		void *handle;
		handle = dlopen ("/usr/lib/libglib-2.0.so.0", RTLD_LAZY);
		if(handle)
		{
			liqapp_log("thumb getting glib");
			g_filename_to_uri =   dlsym(handle, "g_filename_to_uri");
			g_filename_from_uri = dlsym(handle, "g_filename_from_uri");
			g_free =              dlsym(handle, "g_free");
			dlclose(handle);
		}
		else
			liqapp_log("thumb glib error %s",dlerror());
		
		handle = dlopen ("/usr/lib/libhildonthumbnail.so.0", RTLD_LAZY);
		if(handle)
		{
			liqapp_log("thumb getting hildon");
			hildon_thumbnail_get_uri = dlsym(handle, "hildon_thumbnail_get_uri");
			hildon_thumbnail_factory_get_instance = dlsym(handle, "hildon_thumbnail_factory_get_instance");
			if(hildon_thumbnail_factory_get_instance)
			{
				// just run this once to initialize
				// it will likely land me on my butt in future!
				hildon_thumbnail_factory_get_instance();
			}

			dlclose(handle);
		}		
		else
			liqapp_log("thumb hildon error %s",dlerror());
	}
	if(g_filename_to_uri && g_filename_from_uri && g_free && hildon_thumbnail_get_uri)
	{
		
		liqapp_log("thumb lookup 1 big.fil='%s'",bigimagefilename);
		
		char *bigimage_uri =   g_filename_to_uri(        bigimagefilename, NULL, NULL);

		liqapp_log("thumb lookup 1 big.uri='%s'",bigimage_uri);

		char *thumbnail_uri =  hildon_thumbnail_get_uri( bigimage_uri, 160, 96, TRUE);

		liqapp_log("thumb lookup 1 thu.uri='%s'",thumbnail_uri);

		char *thumbnail_file = g_filename_from_uri(      thumbnail_uri, NULL, NULL);

		liqapp_log("thumb lookup 1 thu.fil='%s'",thumbnail_file);


		if(thumbnail_file)
		{
			liqapp_log("thumb got");
		    snprintf(resultbuffer,resultsize,"%s", thumbnail_file);
		    result=0;
		}
		
		g_free((void*)thumbnail_file);
		g_free((void*)thumbnail_uri);
		g_free((void*)bigimage_uri);
	}
	return result;

}


//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################


    /**
     * get the first photograph listed.  does not have to be visible in the filter though
     */
	int sheepdrawing_picturegrid_getfirstphoto_filename(liqcell *self,char *buffer,int bufferlen)
    {
        if(!self)
        {
            snprintf(buffer,bufferlen,"");
            return -1;
        }
        liqcell *body= liqcell_child_lookup(self, "body");
        if(!body)
        {
            snprintf(buffer,bufferlen,"");
            return -2;
        }
        liqcell *c=liqcell_getlinkchild_visual(body);
        if(!c)
        {
            snprintf(buffer,bufferlen,"");
            return -1;
        }
		
        snprintf(buffer,bufferlen,"%s", liqcell_getcaption(c) );
        return 0;        
    }
    
    
    
    /**
     * get the photograph selected.  does not have to be visible in the filter though
     */
	int sheepdrawing_picturegrid_getselectedphoto_filename(liqcell *self,char *buffer,int bufferlen)
    {
        if(!self)
        {
            snprintf(buffer,bufferlen,"x1");
            return -1;
        }
        liqcell *body= liqcell_child_lookup(self, "body");
        if(!body)
        {
            liqapp_log("mmm '%s:%s'",self->name,self->classname?self->classname:"NULL");
            snprintf(buffer,bufferlen,"x2");
            return -2;
        }
        
        liqcell *c=liqcell_getlinkchild_visual(body);
        while(c)
        {
            if(liqcell_getselected(c))
            {
				char *s = liqcell_getcaption(c);
                if(s)
                {
                    snprintf(buffer,bufferlen,"%s",s);
                }
                return 0;
            }
            c=liqcell_getlinknext_visual(c);
        }
        snprintf(buffer,bufferlen,"x3");
        return -2;
    }





	
//#####################################################################
//#####################################################################
//##################################################################### sheepdrawing_picturegrid :: by gary birkett 
//#####################################################################
//#####################################################################


















	

	//##########################################################################
	//########################################################################## latest, click event
	//##########################################################################

	static int sheepdrawing_picturegrid_item_click(liqcell *self, liqcellclickeventargs *args, void *context)
	{
        liqcell *p=liqcell_getlinkparent(self);
        liqcell *c=liqcell_getlinkchild_visual(p);
        while(c)
        {
            if(liqcell_getselected(c)) liqcell_setselected(c,0);
            c=liqcell_getlinknext_visual(c);
        }
        liqcell_setselected(self,1);
        return 1;
	}
















		   
static int liqcell_scan_folder_for_images(liqcell *self,char *path)
{
	liqcell *body= liqcell_child_lookup(self, "body");
	
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
			if ( S_ISDIR(statbuf.st_mode) )
			{
				//printf(" DIR  ");
				liqcell_scan_folder_for_images(self,fn);	
			}
			else
			// got the information we need
			if ( S_ISREG(statbuf.st_mode) )
			{
				char *ext=liqapp_filename_walktoextension(ft);
				if(!ext || !*ext)
				{
					// nothing to see here..
				}

				
				else
				if(
					strcasecmp(ext,"png")==0  ||
					strcasecmp(ext,"jpg")==0  ||
					strcasecmp(ext,"jpeg")==0
				  )
				
				{
					// what i need to know is if this image has a thumbnail
					// ignore it if not
					char imagethumb[ FILENAME_MAX ];
					
					int liqimage_find_thumbnail_for(char *resultbuffer,char *resultsize,char *bigimagefilename);
					
					if( liqimage_find_thumbnail_for(imagethumb,sizeof(imagethumb),fn) == 0 )
					{
						// w00t!   (hello btw)
					
					
					
						struct tm     *pictm;
						pictm = localtime(&statbuf.st_mtime);
						char   picdate[64];
						
						strftime(picdate,sizeof(picdate), "%Y%m%d_%H%M%S",pictm);
						
						
						char pickey[FILENAME_MAX];
						
						snprintf(pickey,sizeof(pickey),"%s_%s",picdate,ft);
						


						liqcell *c = liqcell_quickcreatevis(pickey,   "picture",   1,1,1,1    );
						liqcell_propseti(c,"lockaspect",1);
						liqcell_propsets(c,"imagefilename",imagethumb);
						liqcell_setcaption(c,fn);
						
						liqcell_handleradd(c,    "click",         sheepdrawing_picturegrid_item_click);
						liqcell_child_insertsortedbyname( body, c, 0 );

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



	static int sheepdrawing_picturegrid_filter(liqcell *self, liqcellfiltereventargs *args, void *context)
	{
		// using the filter provided (which might be blank)
		
					int islike = 1;//liqcell_propgeti(  self, "filterlike", 1 );
		
		char *searchterm = NULL;
		
		if(args) args->resultoutof=0;
		if(args) args->resultshown=0;
		if(args) searchterm = args->searchterm;
		
		// examine each tag and if matches the search show it, otherwise dont..
		liqcell *body = liqcell_child_lookup(self,"body");
		
		liqcell *c = liqcell_getlinkchild_visual(body);
		while(c)
		{
			//if(liqcell_isclass(c,"picture"))
			{
				if(searchterm && *searchterm)
				{
					
					char *key = c->name;
                    char *ifn = liqcell_propgets(c,"imagefilename",NULL);
                    if(ifn && *ifn)key=ifn;


					
					int isok = (key!=NULL) && (*key |= 0);
					if(isok)
					{
						if(islike)
						{
							// anywhere in string
							isok = ( stristr(key,searchterm) != NULL );
						}
						else
						{
							// only from the start
							isok = ( c->name == stristr(key,searchterm) );
						}
					}
					
					if(!isok)
					{
						// see if we can show it anyway
						if(liqcell_getselected(c)) isok=1;
					}

					if( isok ) // strstr(c->name,searchterm) )
					{
						// found a match!
						liqcell_setvisible(c,1);
						if(args) args->resultshown++;
					}
					else
					{
						// no match :(
						liqcell_setvisible(c,0);
					}
					if(args) args->resultoutof++;
				}
				else
				{
					// nothing to search for, show it
					liqcell_setvisible(c,1);
					
					if(args) args->resultoutof++;
					if(args) args->resultshown++;
				}
			}
			c=liqcell_getlinknext_visual(c);
		}
		liqcell_setrect(body,   0,0,self->w,self->h);
		liqcell_child_arrange_makegrid(body,3,3);

		return 1;
		
	}















/**	
 * sheepdrawing_picturegrid layout - make any adjustments to fill the content as are required
 */	
static int sheepdrawing_picturegrid_layout(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	
	liqcell *title= liqcell_child_lookup(self, "title");
	liqcell *body= liqcell_child_lookup(self, "body");
		liqcell *headskip= liqcell_child_lookup(body, "__headskip");
	
		// make a normal grid
		liqcell_setrect( body, 0, 0, liqcell_getw(self),liqcell_geth(self) );
		liqcell_child_arrange_makegrid(body,3,3);

	return 0;
}

liqcell *sheepdrawing_picturegrid_create()
{
	liqcell *self = liqcell_quickcreatewidget("sheepdrawing_picturegrid","form", 800,480);

	if(self)
	{

		liqcell_handleradd_withcontext(self, "layout", sheepdrawing_picturegrid_layout ,self);

		liqcell *body = liqcell_quickcreatevis("body","frame",0 ,0,   self->w,self->h);
		liqcell_child_insert( self, body );

	

			char buf[FILENAME_MAX];		
										snprintf(buf,sizeof(buf),"%s/MyDocs/.images",app.homepath);
			liqcell_scan_folder_for_images(self,buf);
	
										snprintf(buf,sizeof(buf),"%s/MyDocs/.camera",app.homepath);
			liqcell_scan_folder_for_images(self,buf);


										snprintf(buf,sizeof(buf),"%s/MyDocs/DCIM",app.homepath);
			liqcell_scan_folder_for_images(self,buf);

	
										snprintf(buf,sizeof(buf),"/usr/share/liqbase/sheepgrawing/media");
			liqcell_scan_folder_for_images(self,buf);
	
	
			//							snprintf(buf,sizeof(buf),"/home/user/MyDocs/.camera");
			//liqcell_scan_folder_for_images(self,buf);
	
			//							snprintf(buf,sizeof(buf),"/home/user/MyDocs/.images");
			//liqcell_scan_folder_for_images(self,buf);
		
		
		
		liqcell_handlerrun(self,"layout",NULL);
		

		int cnt=0;
		liqcell *c=NULL;



		c=liqcell_getlinkchild_visual(body);
        if(c)liqcell_setselected(c,1);

		liqcell_handleradd(body,    "mouse",   liqcell_easyhandler_kinetic_mouse );


        liqcell_handleradd(self,    "filter",   sheepdrawing_picturegrid_filter);

	}
	
	return self;
}

