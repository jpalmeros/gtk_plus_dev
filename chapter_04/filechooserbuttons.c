/*
 * Listing 4-10. Using the File Chooser Button (filechooserbuttons.c)
 * gcc filechooserbuttons.c $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

static void folder_changed (GtkFileChooser*, GtkFileChooser*);
static void file_changed (GtkFileChooser*, GtkLabel*);

/* Connect the main window to the destroy and delete-event signals. */
static void destroy (GtkWidget*, gpointer);
static gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);

int main(int argc,
         char *argv[])
{
    GtkWidget *window, *chooser1, *chooser2, *label, *vbox;
    GtkFileFilter *filter1, *filter2;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "File Chooser Button");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    label = gtk_label_new ("");

    /*
     * Create two buttons, one to select a folder and one to select a file.
     */
    chooser1 = gtk_file_chooser_button_new ("Chooser a Folder",
                                            GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    chooser2 = gtk_file_chooser_button_new ("Chooser a Folder",
                                            GTK_FILE_CHOOSER_ACTION_OPEN);
    
    /*
     * Monitor when the selected folder or file are changed.
     */
    g_signal_connect (G_OBJECT (chooser1), "selection_changed",
                      G_CALLBACK (folder_changed),
                     (gpointer) chooser2);
    g_signal_connect (G_OBJECT (chooser2), "selection_changed",
                      G_CALLBACK (file_changed),
                      (gpointer) label);

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (destroy), NULL);
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);
    
    /*
     * Set both file chooser buttons to the location of the user's home directory.
     */
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (chooser1),
                                         g_get_home_dir());
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (chooser2),
                                         g_get_home_dir());
    
    /*
     * Provide a filter to show all files and one to show only 3 types of images.
     */
    filter1 = gtk_file_filter_new ();
    filter2 = gtk_file_filter_new ();
    gtk_file_filter_set_name (filter1, "Image Files");
    gtk_file_filter_set_name (filter2, "All Files");
    gtk_file_filter_add_pattern (filter1, "*.png"); 
    gtk_file_filter_add_pattern (filter1, "*.jpg"); 
    gtk_file_filter_add_pattern (filter1, "*.gif"); 
    gtk_file_filter_add_pattern (filter2, "*");

    /*
     * Add both the filters to the file chooser button that select files.
     */
    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (chooser2), filter1);
    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (chooser2), filter2);

    vbox = gtk_vbox_new (FALSE, 5);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), chooser1);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), chooser2);
    gtk_box_pack_start_defaults (GTK_BOX (vbox), label);

    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show_all (window);

    gtk_main();

    return 0;
}

/*
 * When a folder is selected, use that as the new location of the other chooser.
 */
static void
folder_changed (GtkFileChooser *chooser1,
                GtkFileChooser *chooser2)
{
    gchar *folder = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser1));
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (chooser2), folder);
}

/*
 * When a file is selected, display the full path in the GtkLabel widget.
 */
static void
file_changed (GtkFileChooser *chooser2,
              GtkLabel *label)
{
    gchar *file = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser2));
    gtk_label_set_text (label, file);
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
