/*
 * Listing 4-11. Using the Font Selection Button (fontbuttons.c)
 * gcc fontbuttons.c $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

static void font_changed (GtkFontButton*, GtkWidget*);

/* Connect the main window to the destroy and delete-event signals. */
static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);

int main(int argc,
         char *argv[])
{
    GtkWidget *window, *vbox, *button, *label;
    PangoFontDescription *initial_font;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Font Button");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    label = gtk_label_new ("Look at the font!");
    initial_font = pango_font_description_from_string ("Sans Bold 12");
    gtk_widget_modify_font (label, initial_font);

    /* Create a new font selection button with the given default font. */
    button = gtk_font_button_new_with_font ("Sans Bold 12");
    gtk_font_button_set_title (GTK_FONT_BUTTON (button), "Choose a Font");

    /* Monitor for changes to the font chosen in the font button */
    g_signal_connect (G_OBJECT (button), "font_set",
                      G_CALLBACK (font_changed),
                      (gpointer) label);

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);
    
    vbox = gtk_vbox_new (FALSE, 5);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), button);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), label);

    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show_all (window);

    gtk_main ();

    return 0;
}

/*
 * When the font is changed, display the font both as the text
 * of a label nad as the label's physical font.
 */
static void
font_changed (GtkFontButton *button,
              GtkWidget *label)
{
    const gchar *font, buffer[512];
    PangoFontDescription *desc;

    font = gtk_font_button_get_font_name (button);
    desc = pango_font_description_from_string (font);

    g_snprintf (buffer, sizeof (buffer), "Font: %s", font);
    gtk_label_set_text (GTK_LABEL (label), buffer);
    gtk_widget_modify_font (label, desc);
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
