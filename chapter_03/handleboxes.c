/*
 * handleboxes.c
 * gcc handleboxes.c -o handleboxes $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);


int main(int argc,
         char *argv[])
{
     GtkWidget *window, *handle, *label;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Handle Box");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 200, 100);

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);

    handle = gtk_handle_box_new ();
    label = gtk_label_new ("Detach Me");

    /* Add a shadow to the handle box, set the handle position on the left and
     * set the snap edge to the top of the widget. */
    gtk_handle_box_set_shadow_type (GTK_HANDLE_BOX (handle), GTK_SHADOW_IN);
    gtk_handle_box_set_handle_position (GTK_HANDLE_BOX (handle), GTK_POS_LEFT);
    gtk_handle_box_set_snap_edge (GTK_HANDLE_BOX (handle), GTK_POS_TOP);

    gtk_container_add (GTK_CONTAINER (handle), label);
    gtk_container_add (GTK_CONTAINER (window), handle);
    gtk_widget_show_all (window);

    gtk_main ();

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
