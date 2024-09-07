#include <gtk/gtk.h>

// Функция обратного вызова GTK
static void my_activate_function(GtkApplication *app, gpointer user_data) {
    // Создаем основное окно
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "C-Project");

    // Устанавливаем позицию окна по центру
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Получаем дисплей
    GdkDisplay *display = gdk_display_get_default();

    // Получаем основной монитор
    GdkMonitor *monitor = gdk_display_get_primary_monitor(display);

    // Получаем разрешение экрана
    GdkRectangle monitor_geometry;
    gdk_monitor_get_geometry(monitor, &monitor_geometry);

    int screen_width = monitor_geometry.width;
    int screen_height = monitor_geometry.height;

    // Устанавливаем размер окна
    // gtk_window_set_default_size(GTK_WINDOW(window), screen_width * 0.2, screen_height * 0.4);
    gtk_window_set_default_size(GTK_WINDOW(window), 600,  650);


    // Создаем виджет прокрутки
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    // Создаем коробку для размещения элементов внутри виджета прокрутки
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(scrolled_window), box);

    // Загрузка и изменение размера первого изображения
    GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_resource("/resources/img/main1.png", NULL);
    if (!pixbuf1) {
        g_print("Error: Unable to load image from file.\n");
        return;
    }
    GdkPixbuf *scaled_pixbuf1 = gdk_pixbuf_scale_simple(pixbuf1, 600, 600, GDK_INTERP_BILINEAR);
    g_object_unref(pixbuf1);

    GtkWidget *image1 = gtk_image_new_from_pixbuf(scaled_pixbuf1);
    g_object_unref(scaled_pixbuf1);
    gtk_box_pack_start(GTK_BOX(box), image1, TRUE, TRUE, 0);

    // Загрузка и изменение размера второго изображения
    GdkPixbuf *pixbuf2 = gdk_pixbuf_new_from_resource("/resources/img/main2.png", NULL);
    if (!pixbuf2) {
        g_print("Error: Unable to load image from file.\n");
        return;
    }
    GdkPixbuf *scaled_pixbuf2 = gdk_pixbuf_scale_simple(pixbuf2, 600, 400, GDK_INTERP_BILINEAR);
    g_object_unref(pixbuf2);

    GtkWidget *image2 = gtk_image_new_from_pixbuf(scaled_pixbuf2);
    g_object_unref(scaled_pixbuf2);
    gtk_box_pack_start(GTK_BOX(box), image2, TRUE, TRUE, 0);

    // GTK функция: показываем все элементы
    gtk_widget_show_all(window);
}

// Основная функция программы
int main(int argc, char **argv) {
    // GTK функция: создаем объект приложения
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.C-Project", G_APPLICATION_FLAGS_NONE);

    // GTK функция: связываем сигнал с функцией
    g_signal_connect(app, "activate", G_CALLBACK(my_activate_function), NULL);

    // GTK функция: запускаем приложение
    status = g_application_run(G_APPLICATION(app), argc, argv);

    // GTK функция: освобождаем ресурсы приложения
    g_object_unref(app);

    return status;
}
