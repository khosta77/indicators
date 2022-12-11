#include <iostream>
#include "utilites.h"

using namespace std;


int main([[ maybe_unused ]] int argc, [[ maybe_unused ]] const char** argv) {
    Menu mn;
    mn.run();
//	[[ maybe_unused ]] auto cndls = readcsv("./GAZP.csv");
//  [[ maybe_unused ]] auto open = get_price_stock(cndls, OPEN);
//  [[ maybe_unused ]] auto sma30 = SMA::sma(open, 30);
//  cout << "MySMA" << int(30) << endl;
//  for (auto it : sma30)
//      cout << it << endl;
//    outCandle(cndls);
//	for (auto it : cndls)
//		cout << it.date << ";" << it.time << ";" << it.open << ";" << it.close << endl;
    return 0;
}
