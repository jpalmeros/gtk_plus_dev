/*
 * Listing 4-4. Selfish Toggle Buttons (radiobuttons.c)
 * gcc radiobuttons.c $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

/* Connect the main window to the destroy and delete-event signals. */
static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);

int main(int argc,
         char *argv[])
{
    GtkWidget *window, *vbox, *radio1, *radio2, *radio3, *radio4;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Radio Buttons");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* Create three radio buttons where the second two join radio1's group */
    radio1 = gtk_radio_button_new_with_label (NULL, "I want to be clicked!");
    radio2 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1), "Click me instead!");
    radio3 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1), "No! Click me!");

    /* Note: The radio button you create the new widget from does not matter as
     * long as it is already a member of the group!
     */
    radio4 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio3), "No! Click me instead!");

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);
    
    vbox = gtk_vbox_new (FALSE, 5);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), radio1);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), radio2);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), radio3);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), radio4);

    gtk_container_add (GTK_CONTAINER (window), vbox);
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
