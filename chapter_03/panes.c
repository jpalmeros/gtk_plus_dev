/*
 * panes.c
 * gcc panes.c -o panes $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);

int main(int argc,
         char *argv[])
{
    GtkWidget *window, *hpaned, *button1, *button2;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Panes");

    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 255, 150);

    hpaned = gtk_hpaned_new ();
    button1 = gtk_button_new_with_label ("Resize");
    button2 = gtk_button_new_with_label ("Me!");

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);

    g_signal_connect_swapped (G_OBJECT (button1), "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              (gpointer) window);
    g_signal_connect_swapped (G_OBJECT (button2), "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              (gpointer) window);
    
    /* Pack both buttons as the two children of the GtkHPaned widget */
    gtk_paned_add1 (GTK_PANED (hpaned), button1);
    gtk_paned_add2 (GTK_PANED (hpaned), button2);

    gtk_container_add (GTK_CONTAINER (window), hpaned);
    gtk_widget_show_all (window);

    gtk_main();
    return 0;
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
