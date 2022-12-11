#ifndef INDICATOR_STOCK_H_
#define INDICATOR_STOCK_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

#define DATE 0
#define TIME 1 
#define OPEN 2
#define HIGH 3
#define LOW 4
#define CLOSE 5
#define VOL 6

/* \brief Объект свечя, при анализе используют обычно свечи, а не прямой поток графика, по этому 
 *        рационально сделать было объект свечи, внутри класса акция
 * */
struct Candle {
    double open;
    double close;
    double low;
    double high;
    int date;  // Дата и время просто подрят записываются, это дешевле и проще чем создание отдельного объекта.
    int time;
    unsigned long long value;
};

class Stock {
    std::pair<std::vector<Candle>, std::map<std::string, std::vector<double>>> stock;  // Сама акция
    const int SIZE_COLUMN = 8;  // Привыводе в консоль ширина колонки будет 8

    /* \brief Метод возращает массив свечей
     * \param line - строка с численной информацией
     * \param title - колонки
     * */
    const Candle get_candle_from_line(const std::string& line, const std::map<std::string, int>& title);
public:
    // Constructor && destrucktor
    Stock() = default;    
    Stock(const std::string& fn);
    ~Stock() {
        stock.first.clear();
        stock.second.clear();
    }

    // in && out methods
    /* \brief Метод считывает из csv файла таблицу с котировками, ввиду того, что для анализа обычно используют
     *        не обработанные данные, то соответственно считываются только стандартные данные свечи.
     * \param filename - путь до файла
     * */
    int read_csv(const std::string& fn);

    /* \brief Метод записывает все данные в csv файл. В отличии от считывания записывает их без исключеният
     * \param filename - путь до файла
     * */
    void save_csv(const std::string& fn);

    /* \brief Метод выводит всю таблицу в консоль, может быть полезно для проверки
     * */
    void print();

    // indicators
    /* \brief Метод возращает массив одного из тикеров, для дальнейшей удобной его обработки
     * \param id - код тикера один из {OPEN, CLOSE, LOW, HIGH}
     * */
    const std::vector<double> get_price_stock(const int& id);

    /* \breif Для более аккуратного пременения идикатора
     * */
    void apIndi(const std::pair<std::string, std::vector<double>>& indi);

    // get
    std::pair<std::vector<Candle>, std::map<std::string, std::vector<double>>> getThis() const;
    std::vector<Candle> getCandle() const;
    std::map<std::string, std::vector<double>> getIndicators() const;
        
};

#endif // INDICATOR_STOCK_H_
