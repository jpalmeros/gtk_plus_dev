/*
 * expanders.c
 * gcc expanders.c -o expanders $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);

int main(int argc,
         char *argv[])
{
    GtkWidget *window, *expander, *label;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Expander");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 200, 100);

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);

    expander = gtk_expander_new_with_mnemonic ("Click _Me For More!");
    label = gtk_label_new ("Hide me or show me,\nthat is your choice.");

    gtk_container_add (GTK_CONTAINER (expander), label);
    gtk_expander_set_expanded (GTK_EXPANDER (expander), TRUE);
    gtk_container_add (GTK_CONTAINER (window), expander);

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
