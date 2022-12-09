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

    const std::pair<std::string, std::vector<double>> sma(const std::vector<double>& stock, const int& day);

};  // SMA

#endif // INDICATOR_INDICATOR_H_
