/*
 * notebooks.c
 * gcc notebooks.c -o notebooks $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);

static void switch_page (GtkButton*, GtkNotebook*);


int main(int argc,
         char *argv[])
{
     GtkWidget *window, *notebook;
     GtkWidget *label1, *label2, *child1, *child2;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Notebook");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 250, 100);

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);

    notebook = gtk_notebook_new ();
    label1 = gtk_label_new ("Page One");
    label2 = gtk_label_new ("Page Two");
    child1 = gtk_label_new ("Go to page 2 to find the answer.");
    child2 = gtk_label_new ("Go to page 1 to find the answer.");

    /* Notice that two widgets were connected to the same callback function! */
    g_signal_connect (G_OBJECT (child1), "clicked",
                      G_CALLBACK (switch_page),
                      (gpointer) notebook);
    g_signal_connect (G_OBJECT (child2), "clicked",
                      G_CALLBACK (switch_page),
                      (gpointer) notebook);
    
    /* Append to pages to the notebook container. */
    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), child1, label1);
    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), child2, label2);

    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_BOTTOM);

    gtk_container_add (GTK_CONTAINER (window), notebook);
    gtk_widget_show_all (window);

    gtk_main ();

    return 0;
}

/* Switch to the next or previous GtkNotebook page. */
static void
switch_page (GtkButton *button,
             GtkNotebook *notebook)
{
    gint page = gtk_notebook_get_current_page (notebook);

    if (page == 0)
        gtk_notebook_set_current_page (notebook, 1);
    else
        gtk_notebook_set_current_page (notebook, 0);
}

/* Stop the GTK+ main loop function when the windows is destroyed. */
static void
destroy (GtkWidget *window,
         gpointer data)
{
    gtk_main_quit ();
}

/* Return FALSE to destroy the widget. By returning TRUE, you can cancel
 * a delete-event. This can be used to confirm quitting the application. */
static gboolean
delete_event (GtkWidget *window,
              GdkEvent *event,
              gpointer data)
{
    return FALSE;
}
