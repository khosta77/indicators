#ifndef INDICATOR_INDICATOR_H_
#define INDICATOR_INDICATOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <iomanip>
#include <numeric>
#include <functional>
#include "candle.h"


namespace SMA {

    std::vector<double> sma(const std::vector<double>& stock, const int& day) {
        if ((stock.size() - 1) < day)
            return std::vector<double>(0);
        else if ((stock.size() - 1) == day) {
            double price = std::accumulate(stock.begin(), stock.end(), double(0));
            std::vector<double> sma;
            sma.push_back(price / day);
            return sma;
        }

        std::vector<double> sma(day, 0);
        for (auto it = (stock.begin() + day); it != stock.end(); ++it)
            sma.push_back((std::accumulate((it - day), it, double(0)) / double(day)));
        return sma;
    }
};  // SMA

#endif // INDICATOR_INDICATOR_H_
