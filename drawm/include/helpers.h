#ifndef HELPERS
#define HELPERS

#include "global.h"

void set_draw(cairo_t *cr, Point* p1, Point* p2);
void draw_brush (GtkWidget *widget, gdouble x, gdouble y, char draw) ;
void free_lines(Point** start, Point** end);
void set_surface(cairo_t **cr);
void addPoint(Point** p, Point** start, Point** end);
void debug2();
void debug2_pre();
void debug3();
void debug3_pre();

#endif