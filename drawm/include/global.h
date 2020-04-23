#ifndef GLOBAL
#define GLOBAL 

#define _GNU_SOURCE

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <gdk/gdk.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <sys/mman.h>

#define INITIAL_SIZE 5
#define CONFIG_PAGE app.pages[app.curr].start = app.pages[app.curr].end = app.pages[app.curr].history_start = app.pages[app.curr].history_end = NULL

// GtkWidget		*Hbox;
// GtkWidget		*canvasFrame;
// GtkWidget		*toolbar;
// GtkWidget		*statusbar;
// GtkWidget		*toolbarFrame;
// GtkWidget		*statusbarFrame;
// GtkWidget		*undo;
// GtkWidget		*redo;
// GtkWidget		*clear;
// GtkWidget		*Red;
// GtkWidget		*Green;
// GtkWidget		*Blue;
// GtkWidget		*White;
// GtkWidget		*VboxL;
// GtkWidget		*VboxR;


GError *err;
typedef struct point {
	int x;
	int y;
	double red, green, blue, size, alpha;
    char draw;
	struct point *next;
	struct point *pre;
} Point;

typedef struct _page
{
	Point *start, *end, *history_start, *history_end, *curr;
	GtkWidget		*canvas;
	GtkWidget		*canvasFrame;
} Page;

typedef struct _app
{
	size_t num_of_pages, curr;
	Page* pages;

	GtkWidget		*window_stack;
	GtkBuilder		*builder, *builder_tmp; 
	GtkCssProvider  *cssProvider;
	GtkWidget		*size_adjustment;
	GtkWidget		*window;
	GtkWidget		*colorsel;
	
} App;

typedef struct properties {
	double red, green, blue, size, alpha;
	char rounded;
} Prop;


Prop prop;
App app;
GdkRGBA rgba;

static cairo_surface_t *surface = NULL;

#endif