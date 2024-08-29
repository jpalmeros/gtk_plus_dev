/*
 * tables.c
 * gcc tables.c -o tables $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);

int main(int argc,
         char *argv[])
{
    GtkWidget *window, *table, *label, *label2, *name;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Tables");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 150, 100);

    table = gtk_table_new (2, 2, TRUE);
    label = gtk_label_new ("Enter the following information ...");
    label2 = gtk_label_new ("Name: ");
    name = gtk_entry_new ();

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);

    /* Attach the two labels and entry widget to their parent container. */
    gtk_table_attach (GTK_TABLE (table), label, 0, 2, 0, 1,
                      GTK_EXPAND, GTK_SHRINK, 0, 0);
    gtk_table_attach (GTK_TABLE (table), label2, 0, 1, 1, 2,
                      GTK_EXPAND, GTK_SHRINK, 0, 0);
    gtk_table_attach (GTK_TABLE (table), name, 1, 2, 1, 2,
                      GTK_EXPAND, GTK_SHRINK, 0, 0);
    
    /* Add five pixels of spacing between every row and every column. */
    gtk_table_set_row_spacings (GTK_TABLE (table), 5);
    gtk_table_set_col_spacings (GTK_TABLE (table), 5);

    gtk_container_add (GTK_CONTAINER (window), table);
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
