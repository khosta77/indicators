#include "Menu.h"

void Menu::print_menu() {
    std::cout << "1. Stock in memory\n"
              << "2. Read stock\n"
              << "3. Save stock\n"
              << "4. Print stock\n"
              << "5. Apply indicator\n"
              << "6. Exit." << std::endl;
    std::cin >> code;
    std::cout << std::endl;
}

void Menu::print_stock_in_memory() {
    std::cout << std::setw(3) << std::left << "N" << " Name" << std::endl;
    for (size_t i = 0; i < stocks.size(); ++i)
        std::cout << std::setw(3) << std::right << int(i + 1) << " " << std::left << stocks[i].first << std::endl;
    std::cout << std::endl;
}

void Menu::open_file() {
    std::cout << "Enter path to table: ";
    std::cin >> path;
    if (stck.read_csv(path) != 1) {
        std::cout << "The table does not open!" << std::endl;
        return;
    }
    std::cout << "Success! Enter the name of the table: ";
    std::cin >> path;
    stocks.push_back(std::pair(path, stck));
    std::cout << std::endl;
}

void Menu::save_file() {
    std::cout << "Enter the name of the table: ";
    std::cin >> tablename;
    std::cout << "Enter the new file name: ";
    std::cin >> filename;
    for (auto &it : stocks)
        if (it.first == tablename)
            it.second.save_csv(filename);
    std::cout << std::endl;
}

void Menu::print_stock() {
    std::cout << "Enter the name of the table: ";
    std::cin >> tablename;
    for (auto &it : stocks)
        if (it.first == tablename)
           it.second.print();
    std::cout << std::endl;
}

void Menu::apply_indicator() {
    std::cout << std::setw(3) << std::left << "N" << " Name" << std::endl;
    for (size_t i = 0; i < indicators.size(); ++i)
        std::cout << std::setw(3) << int(i + 1) << " " << indicators[i] << std::endl;
    std::cout << "Select the indicator: ";
    int day, candle_marker, ind;
    std::cin >> ind;
    std::cout << "Enter a range: ";
    std::cin >> day;
    std::cout << "Candle marker(OPEN: 1, HIGH: 2, LOW: 3, CLOSE: 4): ";
    std::cin >> candle_marker;
    std::cout << "Enter the name of the table: ";
    std::cin >> tablename;
    switch (ind) {
    case 1:
        for(auto &it : stocks)
            if (it.first == tablename)
                it.second.apIndi(SMA::sma(it.second.get_price_stock(candle_marker), day));
        break;
    defualt:
        std::cout << "Unknown indicator" << std::endl;
        break;
    };
    std::cout << std::endl;
}

Menu::~Menu() {
    stocks.clear();
    path.clear();
    filename.clear();
    tablename.clear();
    indicators.clear();
}

void Menu::run() {  // Исполняющий метод
    while (code != 6) {
        print_menu();
        switch (code) {
        case 1:
            this->print_stock_in_memory();
            break;
        case 2:
            this->open_file();
            break;
        case 3:
            this->save_file();
            break;
        case 4:
            this->print_stock();
            break;
        case 5:
            this->apply_indicator();
            break;
        case 6:
            std::cout << std::endl;
            break;
        default:
            std::cout << "Unknown command" << std::endl;
            break;
        };
    }
}
