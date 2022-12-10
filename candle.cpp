#include "candle.h"

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

/* \brief Метод возращает массив свечей
 * \param line - строка с численной информацией
 * \param title - колонки
 * */
static const Candle get_candle_from_line(const std::string& line, 
                                         const std::map<std::string, int>& title) {
    Candle cndl;
    for (auto &it : title)
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

/* \brief Функция считывает из csv файла таблицу с котировками, ввиду того, что для анализа обычно используют
 *        не обработанные данные, то соответственно считываются только стандартные данные свечи.
 * \param filename - путь до файла
 * */
std::vector<Candle> readcsv(const std::string& filename) {
    std::vector<Candle> cndls;
    std::ifstream in(filename);
    if (in.is_open()) {
        std::string line;
        getline(in, line);
        auto title = read_colomn_name_and_position(line);
        while (getline(in, line))
            cndls.push_back(get_candle_from_line(line, title));
    }
    in.close();
    return cndls;
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
void Stock::read_csv(const std::string& fn) {
    std::vector<Candle> cndls;
    std::ifstream in(fn);
    if (in.is_open()) {
        std::string line;
        getline(in, line);
        auto title = read_colomn_name_and_position(line);
        while (getline(in, line))
            cndls.push_back(get_candle_from_line(line, title));
    }
    in.close();
    stock.first = cndls;
    cndls.clear;
    stock.second = std::map<std::string, std::vector<double>>();
}

void Stock::save_csv(const std::string& fn) {
    std::ofstream out;
    out.open(fn);
    if (out.is_open()) {
        // Записываем заголовок
        out << "DATE;TIME;OPEN;HIGH;LOW;CLOSE;VOL";
        if (!stock.second.empty())
            for (auto &it : stock)
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
                for (auto &it : stock)
                    out << ";" <<it.second[i];
                out << std::endl;
            }   
        }
    }
}

void Stock::print() {

}

//// indicators
void Stock::apIndi(const std::pair<std::string, std::vector<double>>& indi);

//// get
_obj Stock::getThis();
std::vector<Candle> Stock::getCandle();
std::map<std::string, std::vector<double>> Stock::getIndicators();
 

