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

#include "../include/helpers.h"
#include "../include/signals.h"



// void    css_set(GtkCssProvider *, GtkWidget *);

void config_page(Page* page)
{
	page -> start = page -> end = page -> history_start = page -> history_end = NULL;
}

int main(int argc, char **argv) 
{

	Point* p1,*p2;
	cairo_t *cr;

	app.pages = malloc(sizeof(Page));
	app.num_of_pages=1;
	app.curr=0;

	prop.rounded = 1;
	prop.red = prop.green = prop.blue = 0.0;
	prop.size=INITIAL_SIZE;
	err = NULL;
	CONFIG_PAGE;

  	/* Paint to the surface, where we store our state */
  	cr = cairo_create (surface);
	set_surface(&cr);
	cairo_destroy(cr);

	gtk_init(&argc, &argv); // init Gtk
	
	app.builder = gtk_builder_new_from_resource("/ui/window.ui");

	app.window = GTK_WIDGET(gtk_builder_get_object(app.builder, "window"));

	// g_signal_connect(app.pages[app.curr].canvas, "realize", G_CALLBACK(on_realize), NULL);


    gtk_builder_connect_signals(app.builder, NULL);

	
	app.pages[app.curr].canvas		= GTK_WIDGET(gtk_builder_get_object(app.builder, "canvas"));
	app.pages[app.curr].canvasFrame		= GTK_WIDGET(gtk_builder_get_object(app.builder, "canvasFrame"));
	app.window_stack = 	  GTK_WIDGET(gtk_builder_get_object(app.builder, "window_stack"));
	app.colorsel		= GTK_WIDGET(gtk_builder_get_object(app.builder, "colorsel"));

	app.cssProvider = gtk_css_provider_new();
  	gtk_css_provider_load_from_resource(app.cssProvider, "/ui/theme.css");
  	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(app.cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
	

	

	gtk_widget_set_events(app.pages[app.curr].canvas, GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);

	gtk_window_set_keep_above (GTK_WINDOW(app.window), TRUE);

	gtk_widget_show(app.window);

	gtk_main();

	//free_app();

	return EXIT_SUCCESS;
}