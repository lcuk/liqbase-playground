/**
 * @file	liqliqcells.c
 * @author  Zach Habersang, based on liqreader by Gary Birkett
 * @brief 	Output a tree of all of the liqcells and their children
 * 
 * Copyright (C) 2008 Gary Birkett
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easypaint.h>
#include <liqbase/liqcell_mk_star.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqbase.h>

// Simple structure for a string split
typedef struct {
	int token_c; // Token count
	char** tokenArr; // Array of strings (tokens)
} split_r;

// Prototypes, don't feel like making a .h
split_r* strsplit(char* buf, char* token);
void liqcell_printline(liqcell *self, int linenum, int ypos, int fonth, liqfont *font, char *color, char *msg);
liqcell *liqcell_tree_output(liqcell *node, int depth, liqfont *font);
static liqcell *uitoolbar_create(char *key, char *caption, ...);
static liqcell *uitoolitem_create(char *key, char *caption, char *imagefilename, void (*handler)());
static int toolitem_click(liqcell *self, liqcellclickeventargs *args, void *context);
static int liqliqcells_body_shown(liqcell *body, liqcelleventargs *args, void *context);
liqcell *liqcell_child_multiinsert(liqcell *self, ...);
liqcell *liqcell_child_multiappend(liqcell *self, ...);

// Get the universe, base of the linked list
extern liqcell *universe;
extern liqcell *mirror;

/**
 * Liqliqcells widget constructor.
 * @return liqcell The newly created fullscreen liqcell with liqliqcell's content
 * 
 */
liqcell *liqliqcells_create() {
	
	// Create the fullscreen widget
	liqcell *self = liqcell_quickcreatewidget("liqliqcells","form", 800, 480);

	// Only proceed if we have a liqcell
	if (self) {
		
		// Add meta data
		liqcell *meta = mkmeta_group(
						mkmeta_title(        "liqliqcells"),
						mkmeta_description(  "Display a visual tree of the liqcells"),
						mkmeta_author(       "zachhabersang@gmail.com"),
						mkmeta_version(      "0.2"),
						NULL);
		liqcell_child_append(self,meta);
		
		// Create toolbar, add toolitems
		liqcell *tbar = uitoolbar_create("tools","tools",
			uitoolitem_create("back", "back",     "media/quickicons/back.png",       toolitem_click),
			uitoolitem_create("up", "up",         "media/quickicons/up.png",         toolitem_click),
			uitoolitem_create("add", "add",       "media/quickicons/add.png",        toolitem_click),
			uitoolitem_create("delete", "delete", "media/quickicons/gtk-remove.png", toolitem_click),
			uitoolitem_create("search", "search", "media/quickicons/find.png",       toolitem_click),
			uitoolitem_create("close", "close",   "media/quickicons/gtk-close.png",  toolitem_click),
			NULL);

		// Determine the fontwidth and fontheight
		liqfont *font = liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0);
		char *caption = "test lorum ipsum lardy dardy";
		int fw = liqfont_textwidth(font, caption) * 1.2;
		int fh = liqfont_textheight(font);
		
		// Create the body of liqliqcells
		liqcell *body = liqcell_quickcreatevis("body", "grid", 0, 0, 800, 480 -  tbar->h);
		liqcell_handleradd(body, "shown", liqliqcells_body_shown);

		//! DON'T BUILD THE TREE YET! SHOWN HANDLER BUILDS THE TREE WHEN THIS IS FIRST SHOWN.

		// Add the content to liqliqcell
		//liqcell_child_append(self, thead);
		liqcell_child_append(self, tbar);
		liqcell_child_append(self, body);
		
		// Now stack them..
		liqcell_child_arrange_easycol(self);
		
	}
	return self;
}

/**	
 * Splitting a string at a given token.
 * @param char* The string to split
 * @param char* The token to split at
 * @return split_r The structure with the split strings and count
 */
split_r* strsplit(char* buf, char* token) {
	
	split_r *split = (split_r *)calloc(sizeof(split_r), 1);
	
	split->tokenArr = NULL; // Store each string in an array - return value
	split->token_c = 0; // Count of tokens
	char *tmp;

	// Get first split
	tmp = strtok(buf, token);
	
	// Get the rest of the splits
	while (tmp) {

		// Increase more space for another string
		char **chk = realloc(split->tokenArr, ++split->token_c * sizeof(*(split->tokenArr)));
		
		// Check for allocation failure
		if (chk == NULL) {
			fprintf(stderr, "realloc() failed: out of memory!");
			free(split->tokenArr);
			return NULL;
		}
		
		// Add string
		split->tokenArr = chk;
		split->tokenArr[split->token_c-1] = tmp;
		
		// Resplit string
		tmp = strtok(NULL, token);
	}
	return split;
} 

/**
 * Print a line by creating a liqcell that acts as a line of specified height and fullscreen width.
 * @param self The content liqcell to add a line to
 * @param linenum The line number
 * @param ypos Y-coordinate that the line will be located at
 * @param fonth Height of the font
 * @param msg The content to put on that line
 * 
 */
void liqcell_printline(liqcell *self, int linenum, int ypos, int fonth, liqfont *font, char *color, char *msg) {
	char ln[32];
	snprintf(ln, sizeof(ln), "line #%i", linenum);
	liqcell *tl = liqcell_quickcreatevis(ln, "label", 0, ypos, 800, fonth);
	liqcell_setcaption(tl, msg);
	liqcell_setfont(tl, liqfont_hold(font));
	liqcell_child_insert(self, tl);
	if (color) liqcell_propsets(tl, "textcolor", color);
}

/* OLD VERSION -- DEPRECATED!
 * ----------------------------------------------------------
 * Use recursion and a loop to generate a liqcell output tree.
 * @param self The base universe
 * @param depth The depth of the indent

void liqcell_tree_output(liqcell *self, int depth) {
	char indent[depth + 1];
	int i;
	for(i=0;i<depth;i++) indent[i]=' ';
	indent[depth]=0;
	
	char name[256];
	snprintf(name, 256, "%s%s  ->  %s\n", indent, (self->name?self->name:""), (self->classname?self->classname:""));
	strncat(output, name, 256);
	
	liqcell *c = self->linkchild;
	while(c) {
		liqcell_tree_output(c, depth+4);
		c = c->linknext;
	}
}
*/

/**
 * Use recursion and a loop to generate a liqcell output tree.
 * @param self The base universe
 * @param depth The depth of the indent
 * @return liqcell* The liqcell of the newly created line
 */
liqcell *liqcell_tree_output(liqcell *node, int depth, liqfont *font) {
	
	liqcell *opener;
	
	int margin = 0; // Will be used to determine the margin width
	int width = 800; // Calculated width based on the margin
	
	// Determine the margin, set the width
	if(depth < 8) margin = depth*50;
	else margin = 8*50;
	width = 800-margin;
	
	// Font height and width
	int fh = liqfont_textheight(font);
	int fw = liqfont_textwidth(font, "+"); // single character
	
	// Create the liqcell content line
	liqcell *self = liqcell_quickcreatevis(node->name, "liqcell_tree_output", 0, 0, width, fh);
	//liqcell_propsets(self, "backcolor", "rgb(255,255,255)");
	
	// Preview of the liqcell being displayed in the tree
	liqcell *preview = liqcell_quickcreatevis("preview", "preview_tree_line", 0, 0, 100, fh);

	// 
	// Determine liqcell preview image
	//
		
	// Has sub-liqcells
	if (liqcell_getlinkchild(node)) {
		
		// Live preview
		if(liqcell_getvisible(node)) {
			liqcell_setcontent(preview, node);
			liqcell_propseti(preview, "lockaspect", 1);
		}
		
		// Folder preview
		else { 
			liqcell_setimage(preview, liqimage_cache_getfile("media/quickicons/folder.png" ,0,0,1));
			liqcell_propseti(preview, "lockaspect", 1);
		}
		
		// The liqcell gets a "+" and "-"
		opener = liqcell_quickcreatevis("open", "label", 0, 0, fw, fh);
		liqcell_setcaption(opener, "+");
		liqcell_setfont(opener, liqfont_hold(font));
		// liqcell *closer liqcell_quickcreatevis("-", "close-", 0, 0, fw, fh);
	}
	
	// No sub-liqcells
	else {
		liqcell_setimage(preview, liqimage_cache_getfile("media/quickicons/txt.png",0,0,1));
		liqcell_propseti(preview, "lockaspect", 1);
		opener = NULL;
	}
	
	// Insert opener and closer if necessary
	if (opener) liqcell_child_insert(self, opener);
	
	// Insert the preview
	liqcell_child_insert(self, preview);

	// Create and insert the line of content
	liqcell *tl = liqcell_quickcreatevis(node->name, "label", 100, 0, width-100, fh);
	liqcell_setcaption(tl, node->name);
	liqcell_setfont(tl, liqfont_hold(font));
	liqcell_child_insert(self, tl);
	//liqcell_propsets(tl,	"textcolor", "rgb(0,0,0)"  );
	//liqcell_propsets(self, "bordercolor", "rgb(255,0,0)");
	
	//
	// Start the recursive tree builder
	//
	
	int yy = fh;
	liqcell *c;
	
	// Only go six levels deep
	if(depth < 6) {
		
		// If the node has content, recurse
		c = liqcell_getcontent(node);
		if(c) {
			liqcell *r = liqcell_tree_output(c, depth+1, font);
			r->x = 50;
			r->y = yy;
			
			yy += r->h;
			self->h += r->h;
			
			liqcell_child_append(self, r);
		}
		
		// Else, get the child node and recurse
		c = liqcell_getlinkchild(node);
		while(c) {
			liqcell *r = liqcell_tree_output(c, depth+1, font);
			r->x = 50;
			r->y = yy;
			
			yy += r->h;
			self->h += r->h;
			
			liqcell_child_append(self, r);
	
			c=liqcell_getlinknext(c);
		}
	}
	return self;
}

/**
 * Create a horizontal toolbar with many toolitems.
 * @param key The name of the toolbar
 * @param caption Caption name
 * @param ... va_args that hold liqcells of the toolitems
 */
static liqcell *uitoolbar_create(char *key, char *caption, ...) {

	// Create the toolbar liqcell with a height of 56px
	liqcell *self = liqcell_quickcreatewidget(key,"form", 800, 56);

	// Proceed if we have a liqcell
	if(self) {
	
		// Configure the toolbar
		if(caption && *caption) liqcell_setcaption(self, caption);
		liqcell_setimage(self, liqimage_cache_getfile( "media/toolbar_background.png",0,0,0));


		// Main background
		liqcell *back = liqcell_quickcreatevis("background", "background", 0, 0, 800, 56);

		// Init process of getting ... arguements
		int count = 0;
		va_list arg;
		va_start(arg, caption);
		
		// Add the toolitems to the toolbar
		while(1) {
			liqcell *c = va_arg(arg, liqcell *);
			if(!c) break;
			liqcell_child_append(back, c);
			count++;
		};
		va_end(arg);
			
		// Determine the cell width for each toolitem, based on the count
		int cw = self->w / count;
		if((cw*count) > self->w) cw--;		
			
		// Set the size of each toolitem, must be done here because we needed to calc cw
		liqcell *c=liqcell_getlinkchild(back);
		while(c) {
			if(liqcell_getvisible(c)) liqcell_setsize(c, cw, 56);
			c=liqcell_getlinknext(c);
		}
		
		// Arrange the toolitems into a row
		liqcell_child_arrange_easyrow(back);

		// Add the content to the liqcell
		liqcell_child_append(self,back);
		
		// Add the bottom border, height of 1px
		liqcell *sep = liqcell_quickcreatevis("sep", "sep", 0,0, 800, 1);
		liqcell_propsets(sep,	"backcolor", "rgb(191,217,56)");
		liqcell_child_append(self,sep);
		
		// Layout arrangement, column
		liqcell_child_arrange_easycol(self);

	}
	return self;
}

/**
 * Create a tool item that goes on a toolbar.
 * @param key The name of the toolitem
 * @param caption Caption of the toolitem
 * @param imagefilename The background image of the toolitem
 * @param handler The handler to run when the toolitem is clicked
 */
static liqcell *uitoolitem_create(char *key,char *caption,char *imagefilename,void (*handler)()) {

	// Create the toolitem liqcell
	liqcell *self = liqcell_quickcreatewidget(key,"form", 50,50);

	// Proceed if we made the liqcell
	if(self) {
		
		// -------------------------------
		// Configure the toolbar
		// -------------------------------
		
		// Set caption
		if (caption && *caption) liqcell_setcaption(self, caption);
		
		// Set image
		liqcell_setimage(self , liqimage_cache_getfile(imagefilename, 0, 0, 1));
		
		// Set lock aspect
		liqcell_propseti(self , "lockaspect", 1);
				
		// Set click handler
		liqcell_handleradd(self, "click", handler);
		
	}
	return self;
}

/**
 * Handler for the toolitems that are clicked.
 * @param self The liqcell toolitem that was clicked
 * @param args liqcell click event arguements
 * @return SUCCESS OR FAILURE
 * 
 */
static int toolitem_click(liqcell *self, liqcellclickeventargs *args, void *context) {
	return 0; // Does nothing yet o_o
}

/** 
 * Shown handler for liqliqcells that executes when liqliqcells is first shown.
 * This executes the tree builder which needs to be executed now because
 * all of the liqcells have been created at this point.
 * 
 * @param body The body to add content to
 * @param args liqcell event arguements
 * @return SUCCESS OR FAILURE
 * 
 */
static int liqliqcells_body_shown(liqcell *body, liqcelleventargs *args, void *context) {
	
	liqapp_log("--------------------------------tree shown start");

	//
	// Build tree
	//
	
	// Set font
	liqfont *font = liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", 24, 0);
	liqfont_setview(font, 1, 1); // ensure we are pointing at the correct default scaled version
			
	// Create tree 
	liqcell *tree = liqcell_tree_output(universe, 0, font);
	liqcell_handleradd(tree, "mouse", liqcell_easyhandler_kinetic_mouse);
			
	// Add the tree to body
	liqcell_child_append(body, tree);
		
	liqapp_log("--------------------------------tree shown end");
			
	return 1;
}

// ------------------------------------------------------
// EXTRA liqcell FUNCTIONS
// ------------------------------------------------------
//
//


/**
 * Insert a group of cells.
 * @param self The parent to insert into
 * @param ... Va-args, the liqcells to insert into parent
 *
 */
liqcell *liqcell_child_multiinsert(liqcell *self, ...) {
	va_list arg;
	va_start(arg, self);
	while(1) {
		liqcell *c = va_arg(arg, liqcell *);
		if(!c) break;
		liqcell_child_insert(self, c);
	};
	va_end(arg);
	return self;
}

/**
 * Append a group of cells.
 * @param self The parent to insert into
 * @param ... Va-args, the liqcells to insert into parent
 *
 */
liqcell *liqcell_child_multiappend(liqcell *self,...) {
	va_list arg;
	va_start(arg, self);
	while(1) {
		liqcell *c = va_arg(arg, liqcell *);
		if(!c) break;
		liqcell_child_append(self, c);
	};
	va_end(arg);
	return self;
}
