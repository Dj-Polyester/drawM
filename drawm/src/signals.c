#include "../include/signals.h"

void	on_destroy() 
{
		free_app();
		gtk_main_quit();
}

void on_marker_clicked(GtkWidget *b1)
{
	prop.rounded=0;
}
void on_pencil_clicked(GtkWidget *b1)
{
	prop.rounded=1;
}

void	on_clear_clicked(GtkWidget *b1) 
{
	free_lines(&(app.pages[app.curr].start),&(app.pages[app.curr].end));
	////set_surface(&cr);
	gtk_widget_queue_draw (app.pages[app.curr].canvas);
}

void on_undo_clicked(GtkWidget *b1) 
{
	Point ** h_start_tmp = &(app.pages[app.curr].history_start)
	,** h_end_tmp = &(app.pages[app.curr].history_end)
	,** start_tmp = &(app.pages[app.curr].start)
	,** end_tmp = &(app.pages[app.curr].end)
	,* p1,*p2;

	if (*start_tmp)
	{
		p1=*start_tmp;
		p2=p1->next;
		size_t i=0;
		
		while (1)
		{
			
			if (!p2 || !(p2->draw))
			{
				addPoint(&p1,h_start_tmp,h_end_tmp);
				*h_start_tmp=*start_tmp;
				*start_tmp=p2;
				if (!p2)
					*end_tmp=NULL;
				p1 = p2 = NULL;
				
				goto REDRAW;
				
			}
			
			p1=p2;
			p2=p2->next;
		}
	}
	REDRAW: 
		gtk_widget_queue_draw (app.pages[app.curr].canvas);
		
	 	
}

void on_redo_clicked(GtkWidget *b1) 
{
	Point ** h_start_tmp = &(app.pages[app.curr].history_start)
	,** h_end_tmp = &(app.pages[app.curr].history_end)
	,** start_tmp = &(app.pages[app.curr].start)
	,** end_tmp = &(app.pages[app.curr].end)
	,* p1,*p2;

	if (*h_start_tmp)
	{
		p1=*h_start_tmp;
		p2=p1->next;
		size_t i=0;
		
		while (1)
		{
			
			if (!p2 || !(p2->draw))
			{
				addPoint(&p1,start_tmp,end_tmp);
				*start_tmp=*h_start_tmp;
				*h_start_tmp=p2;
				if (!p2)
					*h_end_tmp=NULL;
				p1 = p2 = NULL;
				
				goto REDRAW;
				
			}
			
			p1=p2;
			p2=p2->next;
		}
	}
	REDRAW: 
		gtk_widget_queue_draw (app.pages[app.curr].canvas);
		 	
}

void on_color_changed (GtkColorSelection *colorsel, gpointer user_data)
{
	gtk_color_selection_get_current_rgba (colorsel, &rgba);
	prop.red = rgba.red;
	prop.green = rgba.green;
	prop.blue = rgba.blue;
}
void on_size_changed(GtkAdjustment *adj, gpointer user_data)
{
	prop.size=gtk_adjustment_get_value (adj);
}

gboolean
on_switch_page (GtkNotebook *notebook,
               GtkWidget   *page,
               guint        page_num,
               gpointer     user_data)
{
	app.curr = (size_t) page_num;
}


// void on_switch_page(GtkWidget *w, gpointer user_data)
// {
// 	// app.curr = (int) gtk_notebook_get_current_page (app.window_stack);
// 	// g_print("curr %d",app.curr);
// 	//g_print("heyman");
// 	//gtk_widget_queue_draw (app.pages[app.curr].canvas);

// }

gboolean
on_focused (GtkNotebook   *notebook,
               GtkNotebookTab arg1,
               gpointer       user_data)
{
	g_print("focused");
}

void
on_realize (GtkWidget *widget,
               gpointer   user_data)
{
	g_print("yoboiiiiiii");
	g_signal_connect(user_data, "draw", G_CALLBACK(on_canvas_draw), NULL);
	g_signal_connect(user_data, "motion-notify-event", G_CALLBACK(on_canvas_motion_notify_event), NULL);
	g_signal_connect(user_data, "button-press-event", G_CALLBACK(on_canvas_button_press_event), NULL);
	g_signal_connect(user_data, "button-release-event", G_CALLBACK(on_canvas_button_release_event), NULL);
}

GObject *
g_object_clone(GObject *src)
{
    GObject *dst;
    GParameter *params;
    GParamSpec **specs;
    guint n, n_specs, n_params;

    specs = g_object_class_list_properties(G_OBJECT_GET_CLASS(src), &n_specs);
    params = g_new0(GParameter, n_specs);
    n_params = 0;

    for (n = 0; n < n_specs; ++n)
        if (strcmp(specs[n]->name, "parent") &&
            (specs[n]->flags & G_PARAM_READWRITE) == G_PARAM_READWRITE) {
            params[n_params].name = g_intern_string(specs[n]->name);
            g_value_init(&params[n_params].value, specs[n]->value_type);
            g_object_get_property(src, specs[n]->name, &params[n_params].value);
            ++ n_params;
        }

    dst = g_object_newv(G_TYPE_FROM_INSTANCE(src), n_params, params);
    g_free(specs);
    g_free(params);

    return dst;
}

void on_add_clicked(GtkWidget *w, gpointer user_data)
{
	
	Page* tmp_page=NULL;
	char*  newPageTitle=NULL;
	GtkLabel* tmp_label=NULL;
	app.curr = app.num_of_pages++;
	
	
	tmp_page = realloc(app.pages,(app.num_of_pages)*sizeof(Page));
	
	if ( !tmp_page )
	{
		g_print("Could not allocate memory");
		exit(1);
	}
	
	app.pages = tmp_page;
	tmp_page = NULL;
	
	app.builder_tmp = gtk_builder_new_from_resource("/ui/canvas.ui");
	gtk_builder_connect_signals(app.builder_tmp, NULL);
	
	app.pages[app.curr].canvasFrame = GTK_WIDGET(gtk_builder_get_object(app.builder_tmp, "canvasFrame"));
	app.pages[app.curr].canvas = GTK_WIDGET(gtk_builder_get_object(app.builder_tmp, "canvas"));
	//gtk_widget_unparent(app.pages[app.curr].canvasFrame);
	

	newPageTitle = set_newPage_title();
	
	tmp_label = gtk_label_new("newPageTitle");
	
	//gtk_widget_realize (app.pages[app.curr].canvas);
	
	gtk_notebook_append_page (GTK_NOTEBOOK(app.window_stack), app.pages[app.curr].canvasFrame, tmp_label);
	gtk_notebook_set_tab_reorderable (GTK_NOTEBOOK(app.window_stack), app.pages[app.curr].canvasFrame, TRUE);
	gtk_notebook_set_current_page (GTK_NOTEBOOK(app.window_stack), app.curr);
	gtk_widget_show_all(GTK_WIDGET(app.window_stack));
	

	
	
	
	free(newPageTitle);
	//g_object_unref(app.builder_tmp);
	//free(app.pages);
	CONFIG_PAGE;
}


gboolean on_canvas_button_release_event (GtkWidget *widget, GdkEventButton *event) 
{
	g_print("release");
	draw_brush (widget, event->x, event->y,0);

	return TRUE;
}

gboolean on_canvas_motion_notify_event (GtkWidget *widget, GdkEventMotion *event, gpointer data) 
{
	if (event->state & GDK_BUTTON1_MASK ) 
	draw_brush (widget, event->x, event->y,1);
	return TRUE;
}
gboolean on_canvas_button_press_event (GtkWidget *widget, GdkEventButton *event) 
{
	draw_brush (widget, event->x, event->y,2);
	return TRUE;
}

gboolean on_canvas_draw (GtkWidget *widget, cairo_t *cr, gpointer data) 
{
	Point** start_tmp = &(app.pages[app.curr].start)
	,** end_tmp = &(app.pages[app.curr].end)
	,* p1,*p2;
	
	// g_print("sex1");
	if (*start_tmp == NULL) 
	{
		//g_print("sex1.5");
		return FALSE;
	}
	
	// g_print("sex2");
	if (prop.rounded)
		cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND);
	else
		cairo_set_line_cap  (cr, CAIRO_LINE_CAP_SQUARE);
	// g_print("sex3");
	//set_surface(&cr);

    p2=*end_tmp;
	p1 =(*end_tmp)->pre;
    // g_print("sex4");
	while ( p1 ) {
		// g_print("sex5");
		set_draw(cr, p1, p2);
        p2=p1;
		p1 = p1 ->pre;
        
		}
	p2=NULL;
	// g_print("sex6");
	
	return TRUE;
	}

// static void
// gcolor3_window_save_button_clicked (UNUSED GtkButton *button, gpointer user_data)
// {
// 	Gcolor3WindowPrivate *priv;

// 	priv = gcolor3_window_get_instance_private (GCOLOR3_WINDOW (user_data));
// 	save_color (priv);
// }