#ifndef SIGNALS
#define SIGNALS 

#include "global.h"
#include "helpers.h"

void	on_destroy();
void on_marker_clicked(GtkWidget *b1);
void on_pencil_clicked(GtkWidget *b1);
void	on_clear_clicked(GtkWidget *b1);
void on_undo_clicked(GtkWidget *b1);
void on_redo_clicked(GtkWidget *b1);
void	on_Red_clicked(GtkWidget *b1);
void	on_Green_clicked(GtkWidget *b1);
void	on_Blue_clicked(GtkWidget *b1);
void	on_White_clicked(GtkWidget *b1);
void color_changed (GtkColorSelection *colorsel, gpointer user_data);
gboolean on_canvas_button_release_event (GtkWidget *widget, GdkEventButton *event);
gboolean on_canvas_motion_notify_event (GtkWidget *widget, GdkEventMotion *event, gpointer data);
gboolean on_canvas_button_press_event (GtkWidget *widget, GdkEventButton *event);
gboolean on_canvas_draw (GtkWidget *widget, cairo_t *cr, gpointer data);

#endif