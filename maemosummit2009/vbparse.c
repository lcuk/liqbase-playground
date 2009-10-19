// this file is part of liqbase by Gary Birkett

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>

#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>            
#include <fcntl.h>                                                                             
#include <unistd.h>
#include <errno.h>

#include <time.h>			// req for sleep
#include <sys/time.h>		// req for getticks

		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		



// this is a quick/dirty parser for vb files
// it reads the VBP and then reads a list of forms and user controls
// it produces the basic layouts required as liqcells


int vbstring_removequotes(char *res_noquote,int res_noquote_size,char *data);
liqcell * vbparse_vbp_load(char *filename);
liqcell * vbparse_frm_load(char *filename);


//###########################################################################


char *str_rtrim(char *str)
{
						char *rtrim=str;
						while(*rtrim)rtrim++;
						if(rtrim>str && *rtrim==0)rtrim--;
					
						while(rtrim>str)
						{
							if(*rtrim=='\n' || *rtrim=='\r' || *rtrim==10 || *rtrim==13 || *rtrim==' ' || *rtrim=='\t')
							{
								//liqapp_log("rtrim cut '%c':%i",*rtrim,*rtrim);
								*rtrim-- = 0;
							}
							else
							{
								//liqapp_log("rtrim fin '%c':%i",*rtrim,*rtrim);
								break;
							}
						}    
}

/**
 * remove the quotes from a vb data field
 * they are mainly "......"   but if there is a single quote wanted in the middle, "" is placed
 */

int vbstring_removequotes(char *res_noquote,int res_noquote_size,char *data)
{
    if(*data=='"')
    {
        // quoted string constant
        data++;
        char *res=res_noquote;
        int siz=0;
        while(*data && siz<(res_noquote_size-1))
        {
            if(*data=='"')
            {
                if(data[1]=='"')
                {
                    *res++ = '"';
                }
                else
                {
                    // final terminator
                    *res=0;
                    return 0;
                }
            }
            else
            {
                *res++ = *data++;
            }
        }
        *res=0;
    }
    else
    {
        // not a string
        snprintf(res_noquote,res_noquote_size,"%s",data);
    }
    
    return 0;
}


//###########################################################################

/**
 * quickly read in a vb project file
 * 
 */

liqcell * vbparse_vbp_load(char *filename)
{

	// ok, now we load user preferences
	
	liqapp_log("vbparse_vbp_load :: %s",filename);
	
    
    
	char filepath[ FILENAME_MAX ] = {0};
    char *filetitle = liqapp_filename_walkoverpath(filename);
    if(filetitle && *filetitle)
    {
        strncpy(filepath,filename,FILENAME_MAX);
        filepath[ strlen(filepath) - strlen(filetitle) - 1 ] = 0;
    }
    liqcell *root = liqcell_quickcreatenameclass(filetitle,"vbproject");
    

// lines will be something like:
// todo: build proper parser for prefs trees or use some other library


//Type=Exe
//Reference=*\G{00020430-0000-0000-C000-000000000046}#2.0#0#..\..\..\..\WINDOWS\system32\STDOLE2.TLB#OLE Automation
//Form=liqslidehost.frm
//UserControl=liqslideitem_what.ctl
//UserControl=liqslideitem_opt.ctl
//UserControl=liqslideitem_cocreate.ctl
//Startup="Sub Main"
//Command32=""
//Name="maemosummit2009"
//HelpContextID="0"
//CompatibleMode="0"
//MajorVer=1
//MinorVer=0
//RevisionVer=0
//AutoIncrementVer=0
//ServerSupportFiles=0
//CompilationType=0
//OptimizationType=0
//FavorPentiumPro(tm)=0
//CodeViewDebugInfo=0
//NoAliasing=0
//BoundsCheck=0
//OverflowCheck=0
//FlPointCheck=0
//FDIVCheck=0
//UnroundedFP=0
//StartMode=0
//Unattended=0
//Retained=0
//ThreadPerObject=0
//MaxNumberOfThreads=1

	
	
		
	FILE *fn;
	
	//char buf[FILENAME_MAX+1];
	//snprintf(buf,FILENAME_MAX,"%s/%s.prefs",app.userdatapath,"liqbase");
	
    
	fn=fopen(filename,"r");
	if(fn)
	{
		char lineraw[512];
		int linemax=512;
		char *line=NULL;
		while(!feof(fn))
		{
			char * rc;
			rc=fgets(lineraw,linemax, (FILE*) fn);
			if(!rc)break;

			line=lineraw;
			if(*line)
			{
				while(*line==' ' || *line=='\t')line++;
				
				if(*line=='#')
				{
					// comment line
				}
				else
				{
					
					//char *data=instr(line,"=");
					
					char *data=strchr(line,'=');
					if(data && data>line)
					{
						
						//liqapp_log("Test '%c' '%s'",*data,data);
						*data=' ';
						// rtrimming
						char *t=data;
						while(t>line && (*t==' ' || *t=='\t'))
						{
							*t-- = 0;
						}
						
						data++;
						// ltrimming to avoid the spaces
						while(*data==' ' || *data=='\t') data++;
						
						// do some rtrimming :)
                        str_rtrim(data);

                        
                        char data_noquote[1024]={0};
                        vbstring_removequotes(data_noquote,sizeof(data_noquote),data);
                        
                        liqcell *i = liqcell_quickcreatecaption(line,"vbpprop",data_noquote);
						liqcell_child_insertsorted( root, i );
						

					}
				}
			}
		}
		
		fclose(fn);
		
		liqapp_log("vbparse_vbp_load read '%s'",filename);
		//return 0;
	}
	else
	{
		liqapp_log("vbparse_vbp_load could not open '%s'",filename);
        liqcell_release(root);
		return NULL;
	}
    
    // now, I should enumerate root and find all "Form" or "UserControl" items
    // and parse those too
    
    liqcell *c = liqcell_getlinkchild(root);
    while(c)
    {
        char *cdata = liqcell_getcaption(c);
        if(cdata)
        {
            char datafilename[ FILENAME_MAX ];
            liqapp_log("vbparse_vbp_load: '%s' = '%s'",c->name,cdata);
            if( (strcmp(c->name,"Form")==0) )
            {
                snprintf(datafilename,sizeof(datafilename),"%s/%s",filepath,cdata);
                liqcell *x = vbparse_frm_load(datafilename);
                if(x) liqcell_child_insertsorted( root, x );
                
            }
            else
            if( (strcmp(c->name,"UserControl")==0) )
            {
                snprintf(datafilename,sizeof(datafilename),"%s/%s",filepath,cdata);
                liqcell *x = vbparse_frm_load(datafilename);
                if(x) liqcell_child_insertsorted( root, x );
                
            }        
        }
        c=liqcell_getlinknext(c);
    }
    

	return root;
	
}



//###########################################################################

/**
 * quickly read in a vb form/usercontrol layout file
 * 
 */

liqcell * vbparse_frm_load(char *filename)
{

	// ok, now we load user preferences
	
	liqapp_log("vbparse_frm_load :: %s",filename);

	char filepath[ FILENAME_MAX ] = {0};
    char *filetitle = liqapp_filename_walkoverpath(filename);
    if(filetitle && *filetitle)
    {
        strncpy(filepath,filename,FILENAME_MAX);
        filepath[ strlen(filepath) - strlen(filetitle) - 1 ] = 0;
    }
    
	
    
    liqcell *root = liqcell_quickcreatenameclass(filetitle,"vbform");    
    liqcell *par = root;
	
	

// lines will be something like:
// todo: build proper parser for prefs trees or use some other library


//VERSION 5.00
//Begin VB.Form liqslidehost 
//   BackColor       =   &H00000000&
//   BorderStyle     =   1  'Fixed Single
//   Caption         =   "Base Form"
//   ClientHeight    =   7200
//   ClientLeft      =   45
//   ClientTop       =   360
//   ClientWidth     =   12015
//   BeginProperty Font 
//      Name            =   "Trebuchet MS"
//      Size            =   9.75
//      Charset         =   0
//      Weight          =   400
//      Underline       =   0   'False
//      Italic          =   0   'False
//      Strikethrough   =   0   'False
//   EndProperty
//   Begin VB.Label Label2 
//      Alignment       =   2  'Center
//      BackColor       =   &H00004040&
//      BorderStyle     =   1  'Fixed Single
//      Caption         =   "<"
//      BeginProperty Font 
//         Name            =   "Trebuchet MS"
//         Size            =   24
//         Charset         =   0
//         Weight          =   400	
//  ...

		
	FILE *fn;
	
	//char buf[FILENAME_MAX+1];
	//snprintf(buf,FILENAME_MAX,"%s/%s.prefs",app.userdatapath,"liqbase");
	
    
	fn=fopen(filename,"r");
	if(fn)
	{
		char lineraw[512];
		int linemax=512;
		char *line=NULL;
		while(!feof(fn))
		{
			char * rc;
			rc=fgets(lineraw,linemax, (FILE*) fn);
			if(!rc)break;

			line=lineraw;
			if(*line)
			{
				while(*line==' ' || *line=='\t')line++;
				
				if(*line=='#')
				{
					// comment line
				}
                
				else
				if(stristr(line,"Attribute ")==line)
				{
					// Attribute line..  end of the layout
                    goto quickfin;
				}                
                
				else
				if(stristr(line,"VERSION ")==line)
				{
					// version line..

				}
				else
				if(stristr(line,"BEGINPROPERTY ")==line)
				{
					// create a new parent branch
                    
                    str_rtrim(line);

                    char *a=&line[14];

                        liqcell *i = liqcell_quickcreatenameclass(a,"group");
						liqcell_child_insertsorted( par, i );
                        par=i;
						
				}
				else
				if(stristr(line,"ENDPROPERTY")==line)
				{
					// time to step back out of our parent
                    par = liqcell_getlinkparent(par);
				}
                else
				if((stristr(line,"BEGIN ")==line))
				{
					// create a new parent branch
                    
                    str_rtrim(line);
                    
                    char *a=&line[6];
                    char *b=stristr(a," ");  if(b){*b=0; b++;}

                        liqcell *i = liqcell_quickcreatenameclass(b,a);
						liqcell_child_insertsorted( par, i );
                        par=i;
				}

				else
				if((stristr(line,"END")==line))
				{
					// time to step back out of our parent
                    par = liqcell_getlinkparent(par);
				}
                else
				{
					
					//char *data=instr(line,"=");
					
					char *data=strchr(line,'=');
					if(data && data>line)
					{
						
						//liqapp_log("Test '%c' '%s'",*data,data);
						*data=' ';
						// rtrimming
						char *t=data;
						while(t>line && (*t==' ' || *t=='\t'))
						{
							*t-- = 0;
						}
						
						data++;
						// ltrimming to avoid the spaces
						while(*data==' ' || *data=='\t') data++;
						
						// do some rtrimming :)
						char *rtrim=data;
						while(*rtrim)rtrim++;
						if(rtrim>data && *rtrim==0)rtrim--;
					
						while(rtrim>=data)
						{
							if(*rtrim=='\n' || *rtrim=='\r' || *rtrim==10 || *rtrim==13 || *rtrim==' ' || *rtrim=='\t')
							{
								//liqapp_log("rtrim cut '%c':%i",*rtrim,*rtrim);
								*rtrim-- = 0;
							}
							else
							{
								//liqapp_log("rtrim fin '%c':%i",*rtrim,*rtrim);
								break;
							}
						}
						//liqapp_log("pref: '%s'='%s'  %i,%i,%i",line,data,data[0],data[1],data[2]);
						
						//char blankstr[4]={0,0,0,0};
                        if(isdigit(*data))
                        {
                            char *tick=strchr(data,'\'');
                            if(tick)
                            {
                                *tick=0;
                                str_rtrim(data);
                            }
                            
                        }
                        
                        
                        char data_noquote[1024]={0};
                        vbstring_removequotes(data_noquote,sizeof(data_noquote),data);
                        
                        liqcell *i = liqcell_quickcreatecaption(line,"frmprop",data_noquote);
						liqcell_child_insertsorted( par, i );
						

					}
				}
			}
		}
quickfin:		
		fclose(fn);
		
		liqapp_log("vbparse_frm_load read '%s'",filename);
		//return 0;
	}
	else
	{
		liqapp_log("vbparse_frm_load could not open '%s'",filename);
        liqcell_release(root);
		return NULL;
	}
    

    
 
    
    

	return root;
	
}





//###########################################################################

/**
 * create a real form from the parsed details
 * 
 */

liqcell * liqpages_addpages_from_vbproject(liqcell *liqpages,liqcell *domproj)
{

    liqcell *res = liqpages;

	
	//liqapp_log("vbcreate_project");

    // now, I should enumerate root and build a visual tree..
    
    //##################################################
    char *quickcaps(liqcell *self,char *name)
    {
        liqcell *c = liqcell_child_lookup(self,name);
        if(c)
        {
            return liqcell_getcaption(c);
        }
        return NULL;
    }
    int quickcapi(liqcell *self,char *name)
    {
        char *s =quickcaps(self,name);
        if(s) return atoi(s);
        return 0;
    }    
    float quickcapf(liqcell *self,char *name)
    {
        char *s =quickcaps(self,name);
        if(s) return atof(s);
        return 0;
    }
    
    
    char *vbcolortorgb(char *buf,int bufsize,char *incol)
    {
        
        
        int h1=0;
        int h2=0;
        int h3=0;
        int h4=0;
        
        sscanf(&incol[2],"%2x%2x%2x%2x",&h1,&h2,&h3,&h4);
        if(h1) return NULL;
        snprintf(buf,bufsize,"rgb(%i,%i,%i)",h4,h3,h2);
        liqapp_log(" col %s,   %i,%i,%i,%i",incol,h1,h2,h3,h4);
        return buf;
        
        //int hex=0;
        //sscanf(&incol[2],"%x",&hex);       
        //liqapp_log("col %s,%i,   %i,%i,%i,%i",incol,hex,h1,h2,h3,h4);
    }
    char *vbcolortoxrgb(char *buf,int bufsize,char *incol)
    {
        
        
        int h1=0;
        int h2=0;
        int h3=0;
        int h4=0;
        
        sscanf(&incol[2],"%2x%2x%2x%2x",&h1,&h2,&h3,&h4);
        if(h1) return NULL;
        snprintf(buf,bufsize,"xrgb(%i,%i,%i)",h4,h3,h2);
        liqapp_log("xcol %s,   %i,%i,%i,%i",incol,h1,h2,h3,h4);
        return buf;
        
        //int hex=0;
        //sscanf(&incol[2],"%x",&hex);       
    }    
    //##################################################
    liqcell *makelevel(liqcell *code)
    {
        int l = quickcapi(code,"Left")   / 15;
        int t = quickcapi(code,"Top")    / 15;
        int w = quickcapi(code,"Width")  / 15;
        int h = quickcapi(code,"Height") / 15;
        
        liqcell *res = liqcell_quickcreatevis(code->name,code->classname, l,t, w,h);
        
        //liqapp_log("zzz.f.c.f.l %s:%s|",code->name,code->classname);
        
        char *cap = quickcaps(code,"Caption");
        if(cap)
        {
            liqcell_setcaption(res,cap);
        }
        
        
        if( (strcmp(code->name,"slidepreview")==0) )
        {
            liqapp_log("slidepreview found");
            liqcell *liqcell_easyrunstack_topself();
            char *tag = quickcaps(code,"Tag");
            if( tag && *tag )
            {
                liqapp_log("slidepreview has tag: %s",quickcaps(code,"Tag"));
                
                
                liqcell *x = NULL;
                
                if(stristr(tag,"http:")==tag)
                {
                        liqcell_propseti(res,"lockaspect",1);
                        liqcell_propsets(res,"imagefilename",tag);                    
                }
                else
                {
                
                    if(*tag=='*')
                    {
                        x = liqcell_easyrunstack_topself();
                    }
                    else
                    {
                        x = liqcell_quickcreatevis(quickcaps(code,"Tag"), quickcaps(code,"Tag") , 0,0,-1,-1);
                    }
                    if(x)
                    {
                        liqcell_propseti(res,"lockaspect",1);
                        liqcell_setcontent(res,x);
                    }
                }
                
                
                liqcell_handleradd_withcontext(res, "click", liqcell_easyhandler_content_zoom_click, res );
            }
            liqapp_log("slidepreview complete");
        }
        
        
        liqcell *font = liqcell_child_lookup(code,"Font");
        if(font)
        {
            liqcell_setfont(	res, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (quickcapi(font,"Size")*1.4), 0) );
        }
        //liqcell_propsets(  res, "textcolor",   "rgb(255,255,255)" );
        //liqcell_propsets(  res, "backcolor",   "rgb(0,0,0)" );
        //liqcell_propsets(  res, "bordercolor", "rgb(255,255,0)" );
        
        char colorbuf[32];


        if(quickcaps(code,"ForeColor"))
        {
            liqcell_propsets(  res, "textcolor", vbcolortorgb( colorbuf,sizeof(colorbuf), quickcaps(code,"ForeColor") )); //    "rgb(255,255,255)" );
        }
        if(quickcaps(code,"BackColor"))
        {
            if( (strcmp(code->classname,"VB.Label")==0) && (strcmp(quickcaps(code,"BackColor"),"&H00000000&")==0) )
            {
                // skip black on black for now
            }
            else
            {
                liqcell_propsets(  res, "backcolor", vbcolortorgb( colorbuf,sizeof(colorbuf), quickcaps(code,"BackColor") )); //   "rgb(0,0,0)" );
            }
        }        
        if(quickcapi(code,"BorderStyle"))
        {
            liqcell_propsets(  res, "bordercolor", "rgb(255,255,255)" );
        }
        
        if( (strcmp(code->classname,"VB.CommandButton")==0) || (stristr(code->name,"cmd")==code->name) )
        {
            // reassert the backcolor as an X color
            liqcell_propsets(  res, "backcolor", vbcolortoxrgb( colorbuf,sizeof(colorbuf), quickcaps(code,"BackColor") )); //   "rgb(0,0,0)" );
            // make sure there is a border
            liqcell_propsets(  res, "bordercolor", "rgb(255,255,255)" );
            // align self
            liqcell_propseti(  res, "textalign",  2);
            liqcell_propseti(  res, "textaligny", 2);
           
        }
        else
        if( (strcmp(code->classname,"VB.Label")==0) )
        {
            //liqcell_propsets(  res, "textcolor",   "rgb(255,255,255)" );
            //liqcell_propsets(  res, "backcolor",   "rgb(0,0,0)" );
        }


        
        liqcell *c=liqcell_getlinkchild(code);
        while(c)
        {
            //liqapp_log("zzz.f.c.f.l.c %s:%s|",c->name,c->classname);
            
            if( (strcmp(c->classname,"frmprop")==0) )
            {
                //...
            }
            else
            if( (strcmp(c->classname,"group")==0) )
            {
                //...
            }
            else
            {
                liqcell_child_insertsorted( res, makelevel(c) );
            }
            c=liqcell_getlinknext(c);
        }
        return res;
    }

    //##################################################
    liqcell *makeform(liqcell *code)
    {
        char *nam = quickcaps(code,"Name");
        int l = quickcapi(code,"ClientLeft")   / 15;
        int t = quickcapi(code,"ClientTop")    / 15;
        int w = quickcapi(code,"ClientWidth")  / 15;
        int h = quickcapi(code,"ClientHeight") / 15;

        
        liqcell *res = liqcell_quickcreatewidget(code->name,code->classname, w,h);
        
        
        //liqapp_log("zzz.f.c.f %s:%s|",code->name,code->classname);
        
        //liqcell_propsets(  res, "textcolor",   "rgb(255,255,255)" );
    	//liqcell_propsets(  res, "backcolor",   "rgb(0,0,0)" );
    	//liqcell_propsets(  res, "bordercolor", "rgb(255,255,0)" );
        
        //liqcell *res = liqcell_quickcreatevis(code->name,code->classname, l,t, w,h);
        char *cap = quickcaps(code,"Caption");
        if(cap)
        {
            liqcell_setcaption(res,cap);
        }
        liqcell *c=liqcell_getlinkchild(code);
        while(c)
        {
            if( (strcmp(c->classname,"frmprop")==0) )
            {
                //...
            }
            else
            if( (strcmp(c->classname,"group")==0) )
            {
                //...
            }
            else
            {
                liqcell_child_insertsorted( res, makelevel(c) );
            }
            c=liqcell_getlinknext(c);
        }
        return res;
    }
    //##################################################
    //liqcell *res = liqcell_quickcreatevis(domproj->name,"liqpages", 0,0,800,480);



    liqcell *f = liqcell_getlinkchild(domproj);
    while(f)
    {
        
        if( (strcmp(f->classname,"vbform")==0) )
        {        
            //liqapp_log("zzz.f %s:%s",f->name,f->classname);

        
            liqcell *c = liqcell_getlinkchild(f);
            while(c)
            {
                
                //liqapp_log("zzz.f.c %s:%s",c->name,c->classname);
        
                if( (strcmp(c->classname,"VB.Form")==0) || (strcmp(c->classname,"VB.UserControl")==0))
                {

                    liqcell *x = makeform(c);
                    if(x) liqpages_addpage( res, x );
                    //if(x)
                    //{
                    //  liqcell *y = liqcell_quickcreatevis(c->name,"mid", 0,0,800,480);
                    //  liqcell_setcontent(y,x);
                    //  liqpages_addpage( res, y );
                    //}
                    
                    
                }
        
                c=liqcell_getlinknext(c);
            }
        }
        f=liqcell_getlinknext(f);
       
    }
    
    return res;

}


