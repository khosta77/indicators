#ifndef INDICATOR_MENU_H_
#define INDICATOR_MENU_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <iomanip>
#include "candle.h"
#include "indicator.h"
#include <functional>
#include <algorithm>
#include <iomanip>

class Menu {
    /* \brief я пытался засуноть имя индикатора и его вызов в один объект, чтобы только в одном месте новые индикаторы
     *        надо было добавлять, но там возникали архитектурные проблемы, по этому решил сделать этот момент
     *        немногот вульгарно, и просто в двух местах их указать, в памяти какие есть и при вызове конкретный вызывать.
     *
     *        Времени мало было, решил не рисковать и по этому так сделал.
     * */
    std::vector<std::string> indicators = {
        "SMA"
    };
    const int SMA = 1;
    //

    std::vector<std::pair<std::string, Stock>> stocks;

    int code = 1;  // Переменная для цикла с выбором меню 

    // Три переменные ниже созданы как объект класса, чтобы в дальнейшем в методах их не создавать
    std::string path;  // Путь к котировкам акции
    std::string tablename;  // Имя таблицы с котировками
    std::string filename;  // Имя файла, в который будем все сохранять

    Stock stck;  // Переменная нужна для записи новых таблиц котировок

    void print_menu();             // Вывести меню
    void print_stock_in_memory();  // вывести все таблицы с котиорвками в памяти
    void open_file();              // открыть котировки акции
    void save_file();              // сохранить таблицу
    void pring_stock();            // вывести в консоль таблицу
    void apply_indicator();        // применить индикатор к таблице

public:
    Menu() = default;
    ~Menu();

    void run();  // Исполняющий метод
};

#endif // INDICATOR_MENU_H_
