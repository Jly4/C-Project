//Подключаем заголовочные файлы gtk
#include <gtk/gtk.h>

// Слот выхода из программы
G_MODULE_EXPORT void onExit(GtkWidget * w) {
    gtk_main_quit();
}

//Главная функция
int main(int argc, char * argv[]) {
    //Инициализация gtk
    gtk_init(&argc, &argv);

    // Этот объект будет считывать данные из формы
    // и создавать интерфейс на их основе
    GtkBuilder * ui_builder;
    // Если будут какие-либо ошибки, то они появятся здесь
    GError * err = NULL;

    // Инициализируем GtkBuilder
    ui_builder = gtk_builder_new();
    //Загрузка файла с UI в GtkBuilder
    if(!gtk_builder_add_from_file(ui_builder, "../test.glade", &err)) {
        g_critical ("Не вышло загрузить файл с UI : %s", err->message);
        g_error_free (err);
    }

    //Теперь получаем виджет из Builder
    // Помните мы указывали ID? Вот по нему мы и ищем нужный
    // В данном случае ищем виджет окна
    GtkWidget * window = GTK_WIDGET(gtk_builder_get_object(ui_builder, "main_window"));

    //Таким же образом можно получить и другие виджеты
    // но нам они не понадобятся

    //Подключаем сигналы)
    gtk_builder_connect_signals(ui_builder, NULL);

    // Разрешаем отображение
    gtk_widget_show_all(window);

    //Пошла программа
    gtk_main();

    return 0;
}