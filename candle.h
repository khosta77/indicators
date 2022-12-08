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

    std::map<std::string, std::vector<double>> indicator;
};

std::vector<Candle> readcsv(const std::string& filename) {
    auto get_code_id = [](const std::string& id) {
        if (id == "DATE")
            return DATE;
        if (id == "TIME")
            return TIME;
        if (id == "OPEN")
            return OPEN;
        if (id == "CLOSE")
            return CLOSE;
        if (id == "HIGH")
            return HIGH;
        if (id == "LOW")
            return LOW;
        if (id == "VOL")
            return VOL;
        return -1;
    };
    auto get_num_from_line = [](const std::string& l, const int& pos) {
        std::string num = "";
        if (pos == -1)
            return num;

        size_t j = 0;  // позиция ячейки
        if (pos != 0)
            for (int now_pos = 0; j < l.size() && now_pos != pos; ++j)
                if (l[j] == ';')
                    ++now_pos;

        for (size_t i = j; i < l.size() && l[i] != ';'; ++i)
            num += l[i];
        return num;
    };
    std::vector<Candle> cndls;
    std::string line;
    std::ifstream in(filename);
    if (in.is_open()) {
        std::map<std::string, int> title = {{"DATE", -1},
                                               {"TIME", -1},
                                               {"OPEN", -1},
                                               {"CLOSE", -1},
                                               {"HIGH", -1},
                                               {"LOW", -1},
                                               {"VOL", -1}}; 
        getline(in, line);
        for (auto &it : title) { // 
            size_t pos = line.find(it.first);
            if (pos != std::string::npos) {
                int count = 0; // чтобы считать .csv будем считать колличество разделительных колонок
                for (size_t i = 0; i != pos; ++i)
                    if (line[i] == ';')
                        ++count;
                it.second = count;
            }
        }
        Candle cndl;
        while (getline(in, line)) {
            for (auto &it : title) { // вынести
                switch (get_code_id(it.first)) {
                case DATE:
                    cndl.date = std::atoi(get_num_from_line(line, it.second).c_str());
                    break;
                case TIME:
                    cndl.time = std::atoi(get_num_from_line(line, it.second).c_str());
                    break;
                case OPEN:
                    cndl.open = std::atof(get_num_from_line(line, it.second).c_str());
                    break;
                case CLOSE:
                    cndl.close = std::atof(get_num_from_line(line, it.second).c_str());
                    break;
                case HIGH:
                    cndl.high = std::atof(get_num_from_line(line, it.second).c_str());
                    break;
                case LOW:
                    cndl.low = std::atof(get_num_from_line(line, it.second).c_str());
                    break;
                case VOL:
                    cndl.value = std::strtoll(get_num_from_line(line, it.second).c_str(), 0, 0);
                    break;
                };
            }
            cndls.push_back(cndl);
        }
    }
    in.close();
    return cndls;
}

#endif // INDICATOR_CANDLE_H_
