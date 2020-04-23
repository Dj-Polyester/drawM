#include "../include/helpers.h"
#include <string.h>

void free_app()
{
	for (size_t i = 0; i < app.num_of_pages; i++)
	{
		free_lines(&(app.pages[i].start),&(app.pages[i].end));
		free_lines(&(app.pages[i].history_start),&(app.pages[i].history_end));
	}
	
	//free(app.pages);
	g_object_unref(app.builder);
}

void set_draw(cairo_t *cr, Point* p1, Point* p2)
{
	//g_print("set_draw\n");
	//g_print(p2->draw);
	//g_print("p2: %lf %lf %lf", p2->red, p2->green, p2->blue );
	cairo_set_source_rgb(cr, p2->red, p2->green, p2->blue);
	
		switch (p2->draw)
		{
		case 0://dont draw

			break;
		case 1://line
			cairo_set_line_width (cr, p2->size);
			cairo_move_to (cr, (double) p2->x, (double) p2->y);
			cairo_line_to (cr, (double) p1->x, (double) p1->y);
			cairo_stroke (cr);
			
			break;
		case 2://dot
			cairo_set_line_width (cr, p2->size);
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
	p1=NULL;
	p1 = malloc (sizeof(Point));
	if (p1 == NULL) { g_print("out of memory\n"); abort(); }
	p1->pre=NULL;
	p1->next=NULL;
	p1->draw=draw;
    p1->x = x;
	p1->y = y;
	p1->red = prop.red;
	p1->green = prop.green;
	p1->blue = prop.blue;
	p1->size = prop.size;

    addPoint(&p1,&(app.pages[app.curr].start),&(app.pages[app.curr].end));
	
	gtk_widget_queue_draw (app.pages[app.curr].canvas);
	}

void free_lines(Point** start, Point** end)
{
    Point* curr1 = (*start), * curr2;
	(*start) = NULL;
	(*end)=NULL;
	while (curr1) 
	{ 
		curr2 = curr1 -> next; 
		free(curr1); 
		//g_print("%d",p1->draw);
		curr1 = curr2; 
	}
	
}

void set_surface(cairo_t **cr)
{

	cairo_set_source_rgb (*cr, 1, 1, 1);
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

char* itos(int a)
{
	char *digitlist=NULL, *tmp=NULL;
	int digit,i=0,decimal=10,count=1;
	
	if(a)
	{
		while(a/decimal)
		{
			decimal*=10;
			++count;
		}
	}
	
	if(!(digitlist=calloc(count+1,sizeof(char))))
	{
		printf("Could not allocate.");
		exit(1);
	}
	
	for(i=0;i<count;++i)
	{
		
		digit=a%decimal/(decimal/10);
		digitlist[i]=digit+48;
		decimal/=10;
	}
	
	return digitlist;
}

char* set_page_title(const char* new_title, size_t n)
{
	char* char_tmp = calloc(sizeof(char),n+1), *p1 = char_tmp, *p2 = new_title;

	
	while (*p2)
	{
		
		//g_print("sex7");
		*p1 = *p2;
		++p1;
		++p2;
	}

	return char_tmp;
}

char * set_newPage_title()
{

	char* nth = itos(app.num_of_pages);
	size_t lennth = strlen(nth);

	char* newPageTitle = set_page_title("Untitled",8+lennth);

	for (size_t i = 0; i < lennth; i++)
	{
		newPageTitle[8+i] = nth[i]; 
	}

	free(nth);
	return newPageTitle;
}

void debug2()
{
    Point* curr1 = app.pages[app.curr].start, *curr2;

	while (curr1) 
	{ 
		curr2 = curr1 -> next;  
		g_print("%d",curr1->draw);
		if(curr1==app.pages[app.curr].end) g_print("end");
		curr1 = curr2; 
	}
	g_print("\n");
}

void debug2_pre()
{
    Point* curr1 = app.pages[app.curr].end, *curr2;

	while (curr1) 
	{ 
		curr2 = curr1 -> pre;  
		g_print("%d",curr1->draw);
		if(curr1==app.pages[app.curr].start) g_print("start");
		curr1 = curr2; 
	}
	g_print("\n");
}

void debug3()
{
    Point* curr1 = app.pages[app.curr].history_start, *curr2;

	while (curr1) 
	{ 
		curr2 = curr1 -> next;  
		g_print("%d",curr1->draw);
		if(curr1==app.pages[app.curr].history_end) g_print("end");
		curr1 = curr2; 
	}
	g_print("\n");
}

void debug3_pre()
{
    Point* curr1 = app.pages[app.curr].history_end, *curr2;

	while (curr1) 
	{ 
		curr2 = curr1 -> pre;  
		g_print("%d",curr1->draw);
		if(curr1==app.pages[app.curr].history_end) g_print("end");
		curr1 = curr2; 
	}
	g_print("\n");
}