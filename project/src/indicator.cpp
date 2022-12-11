#include "../include/indicator.h"

namespace SMA {

    const std::pair<std::string, std::vector<double>> sma(const std::vector<double>& stock, const int& day) {
        if ((stock.size() - 1) < day)
            return std::pair(("SMA" + std::to_string(day)), std::vector<double>(0));
        else if ((stock.size() - 1) == day) {
            double price = std::accumulate(stock.begin(), stock.end(), double(0));
            std::vector<double> sma;
            sma.push_back(price / day);
            return std::pair(("SMA" + std::to_string(day)), sma);
        }

        std::vector<double> sma(day, 0);
        for (auto it = (stock.begin() + day); it != stock.end(); ++it)
            sma.push_back((std::accumulate((it - day), it, double(0)) / double(day)));
        return std::pair(("SMA" + std::to_string(day)), sma);
    }

};  // SMA
