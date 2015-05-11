#include <gtk/gtk.h>
#include <stdio.h>
#include "buddy_system.h"
#include <time.h>
#include <stdlib.h>


GtkWidget *fixed_container, *depthText;
GtkWidget *window;
struct mem_sys * bs;
time_t start, end;
int depth;
int index;

void paint(struct mem_sys* bs, int index, int level, GtkWidget* box){
	char *buf[80];
	GtkWidget* event_box;
	GtkWidget* label;
	GdkRGBA color;
	 if(bs->depth-1 == level) {
      if(bs->bst[index] == 1) {
      		sprintf(buf,"Size: 2^%d", bs->depth-level);
            label = gtk_label_new(buf);
            event_box = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(event_box), label);
            gdk_color_parse ("red", &color);
            gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL, &color);

           /* gtk_frame_set_label_align(frame, 0.5, 0);*/
            gtk_container_add(GTK_CONTAINER(box), event_box);
        }
        else if(bs->bst[index] == 0 && bs->bst[index - 1 + (index & 1) * 2] == 1) {
            sprintf(buf,"Size: 2^%d", bs->depth-level);
            label = gtk_label_new(buf);
            event_box = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(event_box), label);
            gdk_color_parse ("green", &color);
            gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL, &color);

           /* gtk_frame_set_label_align(frame, 0.5, 0);*/
            gtk_container_add(GTK_CONTAINER(box), event_box);       
        }
        else if(bs->bst[index] == 0 && bs->bst[index - 1 + (index & 1) * 2] == 2) {
            sprintf(buf,"Size: 2^%d", bs->depth-level);
            label = gtk_label_new(buf);
            event_box = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(event_box), label);
            gdk_color_parse ("green", &color);
            gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL, &color);

           /* gtk_frame_set_label_align(frame, 0.5, 0);*/
            gtk_container_add(GTK_CONTAINER(box), event_box);
        }
        else {

        }
    }    
    else {
        if(bs->bst[index] == 1) {
             sprintf(buf,"Size: 2^%d", bs->depth-level);
            label = gtk_label_new(buf);
            event_box = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(event_box), label);
            gdk_color_parse ("red", &color);
            gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL, &color);

           /* gtk_frame_set_label_align(frame, 0.5, 0);*/
            gtk_container_add(GTK_CONTAINER(box), event_box);
        }
        else if(bs->bst[index] == 0 && bs->bst[index - 1 + (index & 1) * 2] == 1) {
            sprintf(buf,"Size: 2^%d", bs->depth-level);
            label = gtk_label_new(buf);
            event_box = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(event_box), label);
            gdk_color_parse ("green", &color);
            gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL, &color);

           /* gtk_frame_set_label_align(frame, 0.5, 0);*/
            gtk_container_add(GTK_CONTAINER(box), event_box);       
		}
        else if(bs->bst[index] == 0 && bs->bst[index - 1 + (index & 1) * 2] == 2) {
            sprintf(buf,"Size: 2^%d", bs->depth-level);
            label = gtk_label_new(buf);
            event_box = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(event_box), label);
            gdk_color_parse ("green", &color);
            gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL, &color);

           /* gtk_frame_set_label_align(frame, 0.5, 0);*/
            gtk_container_add(GTK_CONTAINER(box), event_box);       
        }
        else{
         	paint(bs, index*2+1, level+1, box);
          	paint(bs, index*2+2, level+1, box);
        }
    }
}

static gboolean run (GtkWidget* widget) {

  srand(time(NULL));
  int r = rand();
  if(r%2 == 0) {
    deallocate(bs, index);
  }
  else {
    index = allocate(bs, r%2^bs->depth-1);
  }
  
  GList *children, *iter;

  children = gtk_container_get_children(GTK_CONTAINER(widget));
  for(iter = children; iter != NULL; iter = g_list_next(iter))
  gtk_widget_destroy(GTK_WIDGET(iter->data));
  g_list_free(children);
	
  paint(bs, 0, 0, widget);
  gtk_widget_show_all(window);
	return TRUE;

}

int	main (int argc, char **argv)	{
	int size;
	if(argc != 2) {
		printf("Command line usage - \n\t\tPlease enter an integer from 2-7 specifying the size of system.");
		exit(0);
	}
	else {
		size = strtol(argv[1], NULL, 0);
	}
	bs = new_system(size);
  index = 0;
  	
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Buddy Memory Simulator");
	gtk_window_set_default_size (GTK_WINDOW (window), 500, 200);

	GtkWidget* box = gtk_hbox_new(TRUE, 4);
  gtk_container_add(GTK_CONTAINER(window), box);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_timeout_add(1000, (GSourceFunc) run, (gpointer) box);
  gtk_widget_show_all (window);
  run(box);

  	gtk_main();

  return 0;
}

