# indicators

## Сборка

Проект писал на unix системе, на ней работает 100%. На windows по идеи тоже, так как для сборки я использовал 
cmake, а он мульти платформенный.

Сборка
```commandline
cmake -build .
```

Компиляция
```commandline
make
```

запуск
```commandline
./main
```

## Программа

Является анализатором биржевых акций. Позволяет считать/записать таблицу с котировками, вывести их в консоль/терминал,
и провести по ним анализ(применить выбранный индикатор). Ввиду ограниченности времени применить индикатор возможно только один, это SMA.

### О командах

#### Выбор меню:
```commandline
1. Stock in memory
2. Read stock
3. Save stock
4. Print stock
5. Apply indicator
6. Exit.
```

#### Вывести таблицы которые уже в памяти:

```commandline
1. Stock in memory
2. Read stock
3. Save stock
4. Print stock
5. Apply indicator
6. Exit.
1

N   Name
  1 gazp
```

#### Считать таблицу

```commandline
1. Stock in memory
2. Read stock
3. Save stock
4. Print stock
5. Apply indicator
6. Exit.
2

Enter path to table: GAZP.csv
Success! Enter the name of the table: gazp
```

#### Вывести таблицу

```commandline
1. Stock in memory
2. Read stock
3. Save stock
4. Print stock
5. Apply indicator
6. Exit.
4

Enter the name of the table: gazp
DATE       TIME       OPEN       HIGH       LOW        CLOSE      VOL
20211201   0          338.57     350.37     337.61     345.21     92906220
20211202   0          347.3      352.67     344.8      350.3      75360830
```

#### Сохранить таблицу

```commandline
1. Stock in memory
2. Read stock
3. Save stock
4. Print stock
5. Apply indicator
6. Exit.
3

Enter the name of the table: gazp
Enter the new file name: gazp_sma30.csv
```

#### Применить индикатор

```commandline
1. Stock in memory
2. Read stock
3. Save stock
4. Print stock
5. Apply indicator
6. Exit.
5

N   Name
1   SMA
Select the indicator: 1
Enter a range: 30
Candle marker(OPEN: 2, HIGH: 3, LOW: 4, CLOSE: 5): 2
Enter the name of the table: gazp
```

## Итог

По результатам проверки, результаты в целом совпадают, но местами имеют не значительные отклонения, это может
быть связано с тем, что С++ и Python по разному округляют итоговые значения.

## Полезные ссылки

![SMA(Simple Moving Average) индикатор](https://www.megafx.ru/Indikator-SMA-obzor-i-nastrojki-algoritma/?ysclid=lbjse1b3bf860852736)

![Исторические данные](https://www.finam.ru/profile/moex-akcii/gazprom/export/)


