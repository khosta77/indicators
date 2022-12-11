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
#include "indicator.h"
#include <functional>
#include <algorithm>
#include <iomanip>

class Menu {
    std::vector<std::pair<std::string, Stock>> stocks;

    int code = 1;

    std::string path;
    std::string tablename;
    std::string filename;
    std::string ind;

    Stock stck;

    void print_menu() {
        std::cout << "1. Stock in memory\n"
                  << "2. Read stock\n"
                  << "3. Save stock\n"
                  << "4. Print stock\n"
                  << "5. Apply indicator\n"
                  << "6. Exit." << std::endl;
        std::cin >> code;
        std::cout << std::endl;
    }
//    void print_indicators();

//    void open_file(const std::string& fn);
//    void apply_indicator(const Stock& sk, const int& indi_id);
//    void save_file(const stock& sk, const std::string& fn);
//    void pring_stock(const stock& sk);
public:
    Menu(/* На вход параметры из main*/) = default;
    ~Menu() = default;

    void run() {
        int code = 1;
        while (code != 6) {
            std::cout << "1. Stock in memory\n"
                      << "2. Read stock\n"
                      << "3. Save stock\n"
                      << "4. Print stock\n"
                      << "5. Apply indicator\n"
                      << "6. Exit." << std::endl;
            std::cin >> code;
            std::cout << std::endl;
            switch (code) {
            case 1: //
                std::cout << std::setw(3) << std::left << "N" << " name" << std::endl;
                for (size_t i = 0; i < stocks.size(); ++i) {
                    std::cout << std::setw(3) << std::right << i
                              << " " << std::left << stocks[i].first << std::endl;
                }
                std::cout << std::endl;
                break;
            case 2:
                std::cout << "Enter path to table: ";
                std::cin >> path;
                if (stck.read_csv(path) != 1) {
                    std::cout << "The table does not open!" << std::endl;
                    break;
                }
                std::cout << "Success! Enter the name of the table: ";
                std::cin >> path;
                stocks.push_back(std::pair(path, stck));
                std::cout << std::endl;
                break;
            case 3:
                std::cout << "Enter the name of the table: ";
                std::cin >> tablename;
                std::cout << "Enter the new file name: ";
                std::cin >> filename;
                for (auto &it : stocks)
                    if (it.first == tablename)
                        it.second.save_csv(filename);
                std::cout << std::endl;
                break;
            case 4:
                std::cout << "Enter the name of the table: ";
                std::cin >> tablename;
                for (auto &it : stocks)
                    if (it.first == tablename)
                        it.second.print();
                std::cout << std::endl;
                break;
          /*  case 5:
                for (auto &it : indicators)
                    std::cout << it.first << std::endl;
                std::cout << "Select the indicator: ";
                int day, candle_marker;
                std::cin >> ind;
                std::cout << "Enter a range: ";
                std::cin >> day;
                std::cout << "Candle marker(OPEN: 1, HIGH: 2, LOW: 3, CLOSE: 4): ";
                std::cin >> candle_marker;
                std::cout << "Enter the name of the table: ";
                std::cin >> tablename;
                for (auto &stckIt : stocks)
                    if (stckIt.first == tablename)
                        for (auto &indic : indicators)
                            if (indic.first == ind)
                                stckIt.apIndi(indic.second(stckIt.get_price_stock(candle_marker), day));
                break; */
            case 6:
                std::cout << std::endl;
                break;
            default:
                std::cout << "Unknown command" << std::endl;
                break;
            }
        }
    }

};

#endif // INDICATOR_UTILITES_H_
