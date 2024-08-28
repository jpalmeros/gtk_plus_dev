/*
 * helloworld.c
 * gcc helloworld.c -o helloworld $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

int main(int argc,
         char *argv[])
{
    GtkWidget *window;

    /* Initializa GTK+ and all of its supporting libraries. */
    gtk_init (&argc, &argv);

    /* Create a new window, give it a tittle and display it to the user. */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Hello World");
    gtk_window_set_icon_from_file(GTK_WINDOW (window), "instagram_2111463.png", NULL);
    gtk_widget_show (window);

    /* Hand control over to the main loop */
    gtk_main ();
    return 0;
}
