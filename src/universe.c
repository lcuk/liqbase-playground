

// incomplete idea



// playground maintains a global universe



liqcell *universe = NULL;




//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
	
	static int layoutitem_mouse(liqcell *self, liqcellmouseeventargs *args, liqcell *context)
	{
        // if in editmode then cool, otherwise bail
        liqcell *par = liqcell_getlinkparent(self);
        if(!par)return -1;
        if(liqcell_propgeti(par,"editmode",0)==0) return 0;
		liqcell_adjustpos((self),args->mdx,args->mdy);
		int liqcell_child_arrange_nooverlap(liqcell *self,liqcell *currentselection);
		int liqcell_child_arrange_gapfill(liqcell *self,liqcell *currentselection);
		liqcell_child_arrange_nooverlap( liqcell_getlinkparent(self), self );
		return 1;
	}
    
	static int layoutitem_click(liqcell *self, liqcellclickeventargs *args, liqcell *context)
	{
        // autozoom on click :)
		args->newdialogtoopen = liqcell_getcontent( self );
		return 1;
	}
    

    
    
    liqcell *layoutitem_create()
    {
        //

        liqcell *self = liqcell_quickcreatewidget("layoutitem","form", 800,480);
        if(!self) {liqapp_log("liqcell error not create 'layoutitem'"); return NULL;  } 

		liqcell_propseti(  self,    "lockaspect",1);
		liqcell_handleradd_withcontext(self,    "click",   layoutitem_click,self );
		liqcell_handleradd_withcontext(self,    "mouse",   layoutitem_mouse,self );

        return self;
    }




//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################
//#####################################################################

























// universe contains children for an instance of every root level cell types
int universe_construct()
{

    if(!universe)
    {
        universe = liqcell_quickcreatevis("Universe","universe",0,0,800,800);
        if(!universe)
        {
            liqapp_log("universe:  could not create");
            return -1;
        }
    }
    return 0;

}


liqcell *universe_getcellinstance(char *cellclass)
{
    // look for a child of a specific class within the universe
    // do we already have one?
    if(!universe) universe_construct();
    
    liqcell *child = liqcell_child_lookup(universe,cellclass);
    if(child)
    {
        // found it!  do i need to inc ref count?
        return child;
    }
    
    // try to create directly
    
    liqcell *newx = liqcell_quickcreatevis(cellclass,cellclass,0,0,-1,-1);
    if(!newx)
    {
        liqapp_log("universe:  could not create instance of '%s'",cellclass);
        return -1;
    }
    
    // created ..
    if(newx->w>0 && newx->h>0)
    {
        // and its been assigned size, lets assume its working :)
        liqcell_child_append(universe,newx);
        return newx;
    }
    
    // was created, but it had no visual code behind it
    // 

    
char layfn[FILENAME_MAX];
	snprintf(layfn,sizeof(layfn),"%s/layouts/liq.%s.layout",classname);
    if(liqapp_fileexists(layfn))
    {
        // we can load this as a layout!
    }
    return NULL;
        
    
    
    
// look in children of universe for this class
// if not existing, create
//   if it exists as a "standard" class
//     create it
//   if it does not exist as a "standard" class
//     examine the list of ~/.liqbase/layouts/liq*.layout files
//     if we match, construct a cell which uses the .layout definitions for cell contents and background image
//       recurse as required.  but prior to recursing, add the loaded blank item to the list
//       self recursion is then possible :)
// return it
}













 /**
  * save the definition of a liqcell variation
  *
  */

int liqcell_variation_filesave(liqcell *self,char *filename)
{
    liqapp_log("liqcell_variation_filesave, saving to '%s'",filename);

    //if(self->filename) { free(self->filename); self->filename=NULL; }
    //self->filename = strdup(filename);

    FILE *fd;
    //int   ri;
    fd = fopen(filename, "w");
    if(fd==NULL){ liqapp_log("liqcell_variation_filesave, cannot open '%s' for writing",filename); return -1; }
    // actual file data

    liqapp_log("liqcell_variation_filesave, writing head");

    fprintf(fd,                                    "layout:%4i,%4i,%4i,%4i,'%s','%s'\n",
                                                                                                    self->x,
                                                                                                    self->y,
                                                                                                    self->w,
                                                                                                    self->h,
                                                                                                    self->name,
                                                                                                    self->classname
                                                                                                    );
    
    

    char *imfn = liqcell_propgets(self,"imagefilename",NULL);
    if(imfn && *imfn)
    {
        // we have an image filename!
        fprintf(fd,                                "\timagefilename='%s'\n",
                                                                                                    imfn
                                                                                                    );

    }

    liqcell *c = liqcell_getlinkchild_visual(self);
    while(c)
    {
        //
        fprintf(fd,                                "\tcell:%4i,%4i,%4i,%4i,'%s','%s'\n",
                                                                                                    c->x,
                                                                                                    c->y,
                                                                                                    c->w,
                                                                                                    c->h,
                                                                                                    c->name,
                                                                                                    c->classname
                                                                                                    );

        c=liqcell_getlinknext_visual(c);
    }
    

    liqapp_log("liqcell_variation_filesave, closing");           
    fclose(fd);
    liqapp_log("liqcell_variation_filesave, finished");
    //if(ri<0){ liqapp_log("filesave, cannot write to '%s'",filename); return -2; }
    return 0;
}


//####################################################


 /**
  * load the definition of a liqcell variation
  *
  */



liqcell * liqcell_variation_fileload(char *filename)
{
    liqapp_log("liqcell_variation_fileload, loading from '%s'",filename);

    liqcell *self=NULL;

	char *indat;
	int linenum=1;	



	FILE *fn=NULL;
	

    fn=fopen(filename,"r");
    if(!fn)
    {
        liqapp_log("liqcell_variation_fileload could not open '%s'",filename);
        return -1;
    }
		

	int srcpos=0;

	
	

	char lineraw[512];
	int linemax=511;
	//char *line=NULL;
	while(  (fn && !feof(fn)) || ( (!fn) && (srcpos<srcsize) && (srcdata[srcpos]) ) )
	{
		char * rc;
		

        rc=fgets(lineraw,linemax, (FILE*) fn);
        if(!rc)break;




		if(linenum==1)
		{
			if(strncmp(lineraw,"layout:",7) != 0)
			{
				// invalid header
				if(fn)fclose(fn);
                
				{
                    liqapp_warnandcontinue(-1,"liqcell_variation_fileload invalid file header");
                    return NULL;
                }
			}	
		}
		
		indat=lineraw;
		
		
		// proof of concept
		// load in the points first
		// should be MUCH faster
		
		
		int indentlevel=0;
		while(*indat==9)
		{
			indentlevel++;
			indat++;
		}
		int isdone=0;		// use this to save some time loading (skips the other scanf's after matching one)

		
		
		if((!isdone) && (!self))
		{
			int  px=0;
			int  py=0;
			int  pw=0;
			int  ph=0;
            char pname[64]={0};
            char pclassname[64]={0};
			int res = sscanf(indat,"layout: %i, %i, %i, %i, '%64s', '%64s'",&px,&py,&pw,&ph,&pname,&pclassname);
			if(res==6)
			{
                // create a header cell :)
                self = liqcell_quickcreatevis(pname,"layoutbody",px,py,pw,ph);
                //liqcell *c = universe_getcellinstance(classname);
                if(!self)
                {
                    // could not create instance!
                    liqapp_warnandcontinue(-1,"liqcell_variation_fileload could not create class of '%s'",pclassname);
                    if(fn)fclose(fn);
                    return NULL;
                }
                
                // assign the filename :)
                liqcell_propsets(self,"liqcell_variation_filename",filename);
                
                //liqcell_setrect(self,px,py,pw,ph);
				isdone=1;
			}
		}	
		if(!isdone)
		{
			int  px=0;
			int  py=0;
			int  pw=0;
			int  ph=0;
            char pname[64]={0};
            char pclassname[64]={0};
			int res = sscanf(indat,"cell: %i, %i, %i, %i, '%64s', '%64s'",&px,&py,&pw,&ph,&pname,&pclassname);
			if(res==6)
			{
                liqcell *c = liqcell_quickcreatevis(pname,"layoutitem",px,py,pw,ph);
                if(!c)
                {
                    // could not create instance!
                    liqapp_warnandcontinue(-1,"liqcell_variation_fileload could not create container for '%s'",pclassname);
                    liqcell_release(self);
                    if(fn)fclose(fn);
                    return NULL;
                }
                liqcell *inner = universe_getcellinstance(pclassname);
                if(!inner)
                {
                    liqapp_warnandcontinue(-1,"liqcell_variation_fileload could not create inner content for '%s'",pclassname);
                    liqcell_release(self);
                    if(fn)fclose(fn);
                    return NULL;                    
                }
                
                liqcell_setcontent(c,inner);
                
                liqcell_child_append(self,c);
				isdone=1;
			}
		}	




		
		// 20090422_194605 lcuk : todo load in the extratokens
		
		linenum++;
	}
	if(fn)fclose(fn);
	return self;
}


