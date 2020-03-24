#include "../include/signals.h"

void	on_destroy() 
{
		free_lines(&start,&end);
		free_lines(&history_start,&history_end);
		gtk_main_quit();
}

void on_marker_clicked(GtkWidget *b1)
{
	rounded=0;
}
void on_pencil_clicked(GtkWidget *b1)
{
	rounded=1;
}



void	on_clear_clicked(GtkWidget *b1) 
{
	
	free_lines(&start,&end);
	//set_surface(&cr);
	gtk_widget_queue_draw (canvas);
}


void on_undo_clicked(GtkWidget *b1) 
{
	 	
	Point* p1,*p2;
	if (start)
	{
		p1=start;
		p2=p1->next;
		size_t i=0;
		
		while (1)
		{
			
			if (!p2 || !(p2->draw))
			{
				addPoint(&p1,&history_start,&history_end);
				history_start=start;
				start=p2;
				if (!p2)
					end=NULL;
				p1 = p2 = NULL;
				
				goto REDRAW;
				
			}
			
			p1=p2;
			p2=p2->next;
		}
	}
	REDRAW: 
		gtk_widget_queue_draw (canvas);
		
	 	
}

void on_redo_clicked(GtkWidget *b1) 
{
	Point* p1,*p2;
	if (history_start)
	{
		p1=history_start;
		p2=p1->next;
		size_t i=0;
		
		while (1)
		{
			
			if (!p2 || !(p2->draw))
			{
				addPoint(&p1,&start,&end);
				start=history_start;
				history_start=p2;
				if (!p2)
					history_end=NULL;
				p1 = p2 = NULL;
				
				goto REDRAW;
				
			}
			
			p1=p2;
			p2=p2->next;
		}
	}
	REDRAW: 
		gtk_widget_queue_draw (canvas);
		 	
}

void	on_Red_clicked(GtkWidget *b1) { red = 1.0;  green = 0.0; blue = 0.0; }

void	on_Green_clicked(GtkWidget *b1) { red = 0.0;  green = 1.0; blue = 0.0; }

void	on_Blue_clicked(GtkWidget *b1) { red = 0.0;  green = 0.0; blue = 1.0; }

void	on_White_clicked(GtkWidget *b1) { red = 1.0;  green = 1.0; blue = 1.0; }

gboolean on_canvas_button_release_event (GtkWidget *widget, GdkEventButton *event) 
{
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
	
	
	// guint width, height;
	
	// width = gtk_widget_get_allocated_width (widget);
	// height = gtk_widget_get_allocated_height (widget);
	Point* p1,*p2;
	if (start == NULL) return FALSE;
	cairo_set_line_width(cr, 5.0);

	if (rounded)
		cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND);
	else
		cairo_set_line_cap  (cr, CAIRO_LINE_CAP_SQUARE);

	//set_surface(&cr);

    p2=end;
	p1 = end->pre;
    //if(p1) g_print("p1 start: %d\n",p1->draw);
	while ( p1 ) {
		//if(p1) g_print("%d",p1->draw);
		set_draw(cr, p1, p2);
        p2=p1;
		p1 = p1 ->pre;
        
		}
	p2=NULL;
	//g_print("\nloop out\n");
	return FALSE;
	}