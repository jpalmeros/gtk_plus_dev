/*
 * Listing 4-9. Color Buttons and GdkColors (colorbuttons.c)
 * gcc colorbuttons.c $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

static void color_changed (GtkColorButton*, GtkWidget*);

/* Connect the main window to the destroy and delete-event signals. */
static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);

int main(int argc,
         char *argv[])
{
    GtkWidget *window, *button, *label, *hbox;
    GdkColor color;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Color Buttton");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);
    
    /*
     * Set the initial color as #003366 and set the dialog title.
     */
    gdk_color_parse ("#003366", &color);
    button = gtk_color_button_new_with_color (&color);
    gtk_color_button_set_title (GTK_COLOR_BUTTON (button), "Select a Color");

    label = gtk_label_new ("Look at my color!");
    gtk_widget_modify_fg (label, GTK_STATE_NORMAL, &color);

    g_signal_connect (G_OBJECT (button), "color set",
                      G_CALLBACK (color_changed),
                      (gpointer) label);
    
    hbox = gtk_hbox_new (FALSE, 5);
    gtk_box_pack_start_defaults (GTK_BOX (hbox), button);
    gtk_box_pack_start_defaults (GTK_BOX (hbox), label);

    gtk_container_add (GTK_CONTAINER (window), hbox);
    gtk_widget_show_all (window);

    gtk_main();

    return 0;
}

/*
 * Retrieve the selected color and set it as the GtkLabel's foreground color.
 */
static void
color_changed (GtkColorButton *button,
               GtkWidget *label)
{
    GdkColor color;
    gtk_color_button_get_color (button, &color);
    gtk_widget_modify_fg (label, GTK_STATE_NORMAL, &color);
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
