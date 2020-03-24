/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+
#+     Glade / Gtk Programming
#+
#+     Copyright (C) 2019 by Kevin C. O'Kane
#+
#+     Kevin C. O'Kane
#+     kc.okane@gmail.com
#+     https://www.cs.uni.edu/~okane
#+     http://threadsafebooks.com/
#+
#+ This program is free software; you can redistribute it and/or modify
#+ it under the terms of the GNU General Public License as published by
#+ the Free Software Foundation; either version 2 of the License, or
#+ (at your option) any later version.
#+
#+ This program is distributed in the hope that it will be useful,
#+ but WITHOUT ANY WARRANTY; without even the implied warranty of
#+ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#+ GNU General Public License for more details.
#+
#+ You should have received a copy of the GNU General Public License
#+ along with this program; if not, write to the Free Software
#+ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#+
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "../include/global.h"
#include "../include/helpers.h"
#include "../include/signals.h"

int main(int argc, char *argv[]) 
{

	Point* p1,*p2;

	rounded = 1;
	err = NULL;
	p1 = p2 = start = end = history_start = history_end = NULL;

	red = green = blue = 0.0;

	gtk_init(&argc, &argv); // init Gtk
	
	//builder = gtk_builder_new_from_file("canvas.glade");
	builder = gtk_builder_new_from_resource("/ui/canvas.glade");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);

    gtk_builder_connect_signals(builder, NULL);

	box		= GTK_WIDGET(gtk_builder_get_object(builder, "box"));
	canvas		= GTK_WIDGET(gtk_builder_get_object(builder, "canvas"));
	undo		= GTK_WIDGET(gtk_builder_get_object(builder, "undo"));
	clear		= GTK_WIDGET(gtk_builder_get_object(builder, "clear"));
	Red		= GTK_WIDGET(gtk_builder_get_object(builder, "Red"));
	Green		= GTK_WIDGET(gtk_builder_get_object(builder, "Green"));
	Blue		= GTK_WIDGET(gtk_builder_get_object(builder, "Blue"));
	White		= GTK_WIDGET(gtk_builder_get_object(builder, "White"));

	g_object_unref(builder);

	gtk_widget_set_events(canvas, GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);

	gtk_window_set_keep_above (GTK_WINDOW(window), TRUE);

	gtk_widget_show(window);

	gtk_main();

	return EXIT_SUCCESS;
}





