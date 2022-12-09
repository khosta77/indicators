#ifndef INDICATOR_UTILITES_H_
#define INDICATOR_UTILITES_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <iomanip>
#include "candle.h"


void outCandle(std::vector<Candle> cndls) {
#define SIZE_COLOMN 9
    std::cout << std::setw(SIZE_COLOMN) << std::right << "DATE"
              << std::setw(SIZE_COLOMN) << std::right << "TIME"
              << std::setw(SIZE_COLOMN) << std::right << "OPEN" 
              << std::setw(SIZE_COLOMN) << std::right << "CLOSE" 
              << std::setw(SIZE_COLOMN) << std::right << "HIGH" 
              << std::setw(SIZE_COLOMN) << std::right << "LOW" << std::endl;
    for (auto &it : cndls) {
        std::cout << std::setw(SIZE_COLOMN) << std::right << it.date 
                  << std::setw(SIZE_COLOMN) << std::right << it.time 
                  << std::setw(SIZE_COLOMN) << std::right << it.open 
                  << std::setw(SIZE_COLOMN) << std::right << it.close 
                  << std::setw(SIZE_COLOMN) << std::right << it.high 
                  << std::setw(SIZE_COLOMN) << std::right << it.low << std::endl;
    }
}

/* \brief Метод возращает массив одного из тикеров, для дальнейшей удобной его обработки
 * \param cndls - массив свечей
 * \param id - код тикера один из {OPEN, CLOSE, LOW, HIGH}
 * */
const std::vector<double> get_price_stock(const std::vector<Candle>& cndls, const int& id) {
    std::vector<double> history_stock;
    switch (id) {
    case OPEN:
        for (auto &it: cndls)
            history_stock.push_back(it.open);
        break;
    case CLOSE:
        for (auto &it: cndls)
            history_stock.push_back(it.close);
        break;
    case LOW:
        for (auto &it: cndls)
            history_stock.push_back(it.low);
        break;
    case HIGH:
        for (auto &it: cndls)
            history_stock.push_back(it.high);
        break;
    };
    return history_stock;
}

#endif // INDICATOR_UTILITES_H_
