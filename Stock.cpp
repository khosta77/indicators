#include "Stock.h"

/* \brief Функция возращает код тикера
 * \param id - тикер
 * */
static const int get_code_id(const std::string& id) {
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
}

/* \brief Возращает начало строки из ячейки
 * \param l - строка с информацие
 * \param pos - номер ячейки, отсчет от 0
 * */
static const std::string get_num_from_line(const std::string& l, const int& pos) {
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
}

/* \brief Данный метод возращает заголовки и позиции соответсвующих колонок в .csv таблице. Ввиду того, что
 *        почти все индикаторы при анализе биржи используют историчские данные, которые ранее не 
 *        обрабатывались, то было решено извлекать фиксированные колонки, которые как правило имеют 
 *        фиксированные имена.
 * \param line - строка, с заколовком
 * */
static const std::map<std::string, int> read_colomn_name_and_position(const std::string& line) {
    std::map<std::string, int> title = {{"DATE", -1}, {"TIME", -1}, {"OPEN", -1}, {"CLOSE", -1}, 
                                        {"HIGH", -1}, {"LOW", -1}, {"VOL", -1}};
    size_t pos;  // Позиция ключевого слова в заголовке
    int count;   // Колличество колонок
    for (auto &it : title) {
        pos = line.find(it.first);
        if (pos != std::string::npos) {
            count = 0; // чтобы считать .csv будем считать колличество разделительных колонок
            for (size_t i = 0; i != pos; ++i)
                if (line[i] == ';')
                    ++count;
            it.second = count;
        }
    }
    return title;
}

const Candle Stock::get_candle_from_line(const std::string& line, const std::map<std::string, int>& title) {
    Candle cndl;
    for (auto it : title)
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
    return cndl;
}


//// Constructor && destructor
Stock::Stock(const std::string& fn) {
    read_csv(fn);
}

//// in && out methods
/* \brief Функция считывает из csv файла таблицу с котировками, ввиду того, что для анализа обычно используют
 *        не обработанные данные, то соответственно считываются только стандартные данные свечи.
 * \param filename - путь до файла
 * */
int Stock::read_csv(const std::string& fn) {
    std::vector<Candle> cndls;
    std::ifstream in(fn);
    if (in.is_open()) {
        std::string line;
        getline(in, line); 
        auto title = read_colomn_name_and_position(line);
        while (getline(in, line))
            cndls.push_back(get_candle_from_line(line, title));
    } else 
        return -1;
    in.close();
    stock.first = cndls;
    cndls.clear();
    stock.second = std::map<std::string, std::vector<double>>();
    return 1;
}

void Stock::save_csv(const std::string& fn) {
    std::ofstream out;
    out.open(fn);
    if (out.is_open()) {
        // Записываем заголовок
        out << "DATE;TIME;OPEN;HIGH;LOW;CLOSE;VOL";
        if (!stock.second.empty())
            for (auto &it : stock.second)
                out << ";" << it.first;
        out << std::endl;

        // записываем основоной набор данных
        if (stock.second.empty())
            for (size_t i = 0; i < stock.first.size(); ++i)
                out << stock.first[i].date << ";" << stock.first[i].time << ";" << stock.first[i].open << ";" 
                    << stock.first[i].high << ";" << stock.first[i].low << ";" << stock.first[i].close << ";"
                    << stock.first[i].value << std::endl;
        else {
            for (size_t i = 0; i < stock.first.size(); ++i) {
                out << stock.first[i].date << ";" << stock.first[i].time << ";" << stock.first[i].open << ";" 
                    << stock.first[i].high << ";" << stock.first[i].low << ";" << stock.first[i].close << ";"
                    << stock.first[i].value;
                for (auto &it : stock.second)
                    out << ";" <<it.second[i];
                out << std::endl;
            }   
        }
    }
}

void Stock::print() {
    // Записываем заголовок
    std::cout << std::setw(SIZE_COLUMN) << "DATE"
              << std::setw(SIZE_COLUMN) << "TIME"
              << std::setw(SIZE_COLUMN) << "OPEN"
              << std::setw(SIZE_COLUMN) << "HIGH"
              << std::setw(SIZE_COLUMN) << "LOW"
              << std::setw(SIZE_COLUMN) << "CLOSE"
              << std::setw(SIZE_COLUMN) << "VOL";
    if (!stock.second.empty())
        for (auto &it : stock.second)
            std::cout << std::setw(SIZE_COLUMN) << it.first;
    std::cout << std::endl;

    // записываем основоной набор данных
    if (stock.second.empty())
        for (size_t i = 0; i < stock.first.size(); ++i)
            std::cout << std::setw(SIZE_COLUMN) << stock.first[i].date
                      << std::setw(SIZE_COLUMN) << stock.first[i].time 
                      << std::setw(SIZE_COLUMN) << stock.first[i].open 
                      << std::setw(SIZE_COLUMN) << stock.first[i].high 
                      << std::setw(SIZE_COLUMN) << stock.first[i].low 
                      << std::setw(SIZE_COLUMN) << stock.first[i].close 
                      << std::setw(SIZE_COLUMN) << stock.first[i].value << std::endl;
    else {
        for (size_t i = 0; i < stock.first.size(); ++i) {
            std::cout << std::setw(SIZE_COLUMN) << stock.first[i].date
                      << std::setw(SIZE_COLUMN) << stock.first[i].time
                      << std::setw(SIZE_COLUMN) << stock.first[i].open
                      << std::setw(SIZE_COLUMN) << stock.first[i].high
                      << std::setw(SIZE_COLUMN) << stock.first[i].low
                      << std::setw(SIZE_COLUMN) << stock.first[i].close
                      << std::setw(SIZE_COLUMN) << stock.first[i].value;
            for (auto &it : stock.second)
                std::cout << std::setw(SIZE_COLUMN) <<it.second[i];
            std::cout << std::endl;
        }   
    }
}

//// indicators
const std::vector<double> Stock::get_price_stock(const int& id) {
    std::vector<double> history_stock;
    switch (id) {
    case OPEN:
        for (auto &it : stock.first)
            history_stock.push_back(it.open);
        break;
    case CLOSE:
        for (auto &it : stock.first)
            history_stock.push_back(it.close);
        break;
    case LOW:
        for (auto &it : stock.first)
            history_stock.push_back(it.low);
        break;
    case HIGH:
        for (auto &it : stock.first)
            history_stock.push_back(it.high);
        break;
    };
    return history_stock;
}

void Stock::apIndi(const std::pair<std::string, std::vector<double>>& indi) {
    stock.second[indi.first] = indi.second;
}

//// get
std::pair<std::vector<Candle>, std::map<std::string, std::vector<double>>> Stock::getThis() const {
    return stock;
}

std::vector<Candle> Stock::getCandle() const {
    return stock.first;
}

std::map<std::string, std::vector<double>> Stock::getIndicators() const {
    return stock.second;
}
 

