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
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <sys/mman.h>

GtkWidget		*window;
GtkWidget		*box;
GtkWidget		*canvas;
GtkWidget		*undo;
GtkWidget		*redo;
GtkWidget		*clear;
GtkWidget		*Red;
GtkWidget		*Green;
GtkWidget		*Blue;
GtkWidget		*White;
GtkBuilder		*builder; 
GError          *err;

typedef struct point {
	int x;
	int y;
	double red, green, blue;
    char draw;
	struct point *next;
	struct point *pre;
} Point;

Point *start, *end, *history_start, *history_end;


double red, green, blue;
char rounded;

#endif