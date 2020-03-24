#include "../include/helpers.h"

void set_draw(cairo_t *cr, Point* p1, Point* p2)
{
	//g_print("set_draw\n");
	cairo_set_source_rgb(cr, p2->red, p2->green, p2->blue);
		switch (p2->draw)
		{
		case 0://dont draw

			break;
		case 1://line
			cairo_move_to (cr, (double) p2->x, (double) p2->y);
			cairo_line_to (cr, (double) p1->x, (double) p1->y);
			cairo_stroke (cr);
			break;
		case 2://dot
			cairo_move_to (cr, (double) p1->x, (double) p1->y);
			cairo_line_to (cr, (double) p1->x+1, (double) p1->y);
			cairo_stroke (cr);
			break;

		default:
			perror("Error: ");
			break;
		}
}

void draw_brush (GtkWidget *widget, gdouble x, gdouble y, char draw) 
{
	Point* p1,*p2;
	
	p1 = malloc (sizeof(Point));
	if (p1 == NULL) { g_print("out of memory\n"); abort(); }
	p1->pre=NULL;
	p1->next=NULL;
	p1->draw=draw;
    p1->x = x;
	p1->y = y;
	p1->red = red;
	p1->green = green;
	p1->blue = blue;

    addPoint(&p1,&start,&end);
	
	gtk_widget_queue_draw (canvas);
	}

void free_lines(Point** start, Point** end)
{
    Point* curr1 = (*start), * curr2;

	while (curr1) 
	{ 
		curr2 = curr1 -> next; 
		free(curr1); 
		//g_print("%d",p1->draw);
		curr1 = curr2; 
	}
	(*start) = NULL;
	(*end)=NULL;
}

void set_surface(cairo_t **cr)
{

	cairo_set_source_rgb (*cr, 0, 0, 0);
  	cairo_paint (*cr);

}

void addPoint(Point** p, Point** start, Point** end)
{
    if ((*p)->next)
		(*p)->next->pre=NULL;
	(*p)->next = (*start);
	(*start) = (*p);
	if (!(*end))
		(*end)=(*start);
	else
		(*start)->next->pre=(*start);
	
}

void debug2()
{
    Point* curr1 = start, *curr2;

	while (curr1) 
	{ 
		curr2 = curr1 -> next;  
		g_print("%d",curr1->draw);
		if(curr1==end) g_print("end");
		curr1 = curr2; 
	}
	g_print("\n");
}

void debug2_pre()
{
    Point* curr1 = end, *curr2;

	while (curr1) 
	{ 
		curr2 = curr1 -> pre;  
		g_print("%d",curr1->draw);
		if(curr1==start) g_print("start");
		curr1 = curr2; 
	}
	g_print("\n");
}

void debug3()
{
    Point* curr1 = history_start, *curr2;

	while (curr1) 
	{ 
		curr2 = curr1 -> next;  
		g_print("%d",curr1->draw);
		if(curr1==history_end) g_print("end");
		curr1 = curr2; 
	}
	g_print("\n");
}

void debug3_pre()
{
    Point* curr1 = history_end, *curr2;

	while (curr1) 
	{ 
		curr2 = curr1 -> pre;  
		g_print("%d",curr1->draw);
		if(curr1==history_end) g_print("end");
		curr1 = curr2; 
	}
	g_print("\n");
}