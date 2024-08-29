/*
 * eventboxes.c
 * gcc eventboxes.c -o eventboxes $(pkg-config --cflags gtk+-2.0) $(pkg-config --libs gtk+-2.0)
 */
#include <gtk/gtk.h>

static void destroy(GtkWidget*, gpointer);
static gboolean delete_event(GtkWidget*, GdkEvent*, gpointer);

static gboolean button_pressed(GtkWidget*, GdkEventButton*, GtkLabel*);

int main(int argc,
         char *argv[])
{
    GtkWidget *window, *eventbox, *label;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Event Box");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 200, 50);

    /* Connect the main window to the destroy and delete-event signals. */
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(destroy), NULL);
    g_signal_connect(G_OBJECT(window), "delete_event",
                     G_CALLBACK(delete_event), NULL);

    eventbox = gtk_event_box_new();
    label = gtk_label_new("Double-Click Me!");

    /* Set the order in which widgets will receive notifications of events. */
    gtk_event_box_set_above_child(GTK_EVENT_BOX(eventbox), FALSE);

    g_signal_connect(G_OBJECT(eventbox), "button_press_event",
                     G_CALLBACK(button_pressed), (gpointer)label);

    gtk_container_add(GTK_CONTAINER(eventbox), label);
    gtk_container_add(GTK_CONTAINER(window), eventbox);

    /* Allow the event box to catch button presses, realize the widget, and set the
     * cursor that will be displayed when the mouse is over the event box. */
    gtk_widget_set_events(eventbox, GDK_BUTTON_PRESS_MASK);
    gtk_widget_realize(eventbox);
    gdk_window_set_cursor(eventbox->window, gdk_cursor_new(GDK_HAND1));
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

/* This is called every time a button-press event occurs on the GtkEventBox. */
static gboolean
button_pressed(GtkWidget *eventbox,
               GdkEventButton *event,
               GtkLabel *label)
{
    if (event->type == GDK_2BUTTON_PRESS)
    {
        const gchar *text = gtk_label_get_text(label);

        if (text[0] == 'D')
            gtk_label_set_text(label, "I Was Double-Clicked!");
        else
            gtk_label_set_text(label, "Double-Click Me Again!");
    }

    return FALSE;
}

/* Stop the GTK+ main loop function when the windows is destroyed. */
static void
destroy(GtkWidget *window,
        gpointer data)
{
    gtk_main_quit();
}

/* Return FALSE to destroy the widget. By returning TRUE, you can cancel
 * a delete-event. This can be used to confirm quitting the application. */
static gboolean
delete_event(GtkWidget *window,
             GdkEvent *event,
             gpointer data)
{
    return FALSE;
}
