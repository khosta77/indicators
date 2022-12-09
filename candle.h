#ifndef INDICATOR_CANDLE_H_
#define INDICATOR_CANDLE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

#define DATE 0
#define TIME 1
#define OPEN 2
#define CLOSE 3
#define HIGH 4
#define LOW 5
#define VOL 6

struct Candle {
    double open;
    double close;
    double low;
    double high;
    int date;
    int time;
    unsigned long long value;
};

typedef std::pair<std::vector<Candle>, std::map<std::string>, std::vector<double>> Stock;

/* \brief Функция считывает из csv файла таблицу с котировками, ввиду того, что для анализа обычно используют
 *        не обработанные данные, то соответственно считываются только стандартные данные свечи.
 * \param filename - путь до файла
 * */
std::vector<Candle> readcsv(const std::string& filename);

/* \brief
 * */
//int writecsv(const std::vector<Candle>& cndls, std::string& filename);

#endif // INDICATOR_CANDLE_H_
