/*
 * Listing 4-2. Using Toggle Buttons (togglebuttons.c)
 * gcc togglebuttons.c $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

static void button_toggled (GtkToggleButton*, GtkWidget*);
/* Connect the main window to the destroy and delete-event signals. */
static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);

int main (int argc,
           char *argv[])
{
    GtkWidget *window, *vbox, *toggle1, *toggle2;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Toggle Buttons");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    vbox = gtk_vbox_new (TRUE, 5);
    toggle1 = gtk_toggle_button_new_with_mnemonic ("_Deactivate the other one!");
    toggle2 = gtk_toggle_button_new_with_mnemonic ("_No! Deactivate that one!");

    g_signal_connect (G_OBJECT (toggle1), "toggled",
                      G_CALLBACK (button_toggled),
                      (gpointer) toggle2);
    g_signal_connect (G_OBJECT(toggle2), "toggled",
                      G_CALLBACK (button_toggled),
                      (gpointer) toggle1);

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);
    
    gtk_box_pack_start_defaults (GTK_BOX (vbox), toggle1);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), toggle2);

    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show_all (window);

    gtk_main();

    return 0;
}

/*
 * If the toggle button was activated, set the other as disabled.
 * Otherwise, enable the other toggle button
 */
static void
button_toggled (GtkToggleButton *toggle,
                GtkWidget *other_toggle)
{
    if (gtk_toggle_button_get_active (toggle))
        gtk_widget_set_sensitive (other_toggle, FALSE);
    else
        gtk_widget_set_sensitive (other_toggle, TRUE);
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