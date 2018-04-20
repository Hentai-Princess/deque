//Заменить каждое четное число на разность максимального и минимального чисел.
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <iterator>
using namespace std;
//Создание файла из рандомных значений с помощью цикла
ofstream CreateFileRand(string FileName, int N, int M) {
    ofstream fs(FileName);
    for (int i = 0; i < N; ++i) {
        
        int r = rand()%(2*M +1)-M;
        fs << r << " ";
    }
    fs.close();
    return fs;
}

//Создание файла из рандомных значений с помощью generate
ofstream CreateFileGenerate(string FileName, int N, int M) {
    ofstream fs;
    fs.open(FileName);
    generate_n(std::ostream_iterator<int>(fs, " "), N, [M]() {int i = rand() % (2 * M + 1) - M; return i; });
    fs.close();
    return fs;
}

//Загрузка из файла
deque<int> LoadFromFile(ifstream &fin) {
    deque<int> dec;
    if (!fin) {
        cout << "Файл не найден." << endl;
        return dec;
    }
    
    int a;
    if (!(fin >> a)) {
        cout << "Неверный формат данных." << endl;
        return dec;
    }
    if (fin.eof()) {
        cout << "Файл пуст." << endl;
    } else {
        while (!fin.eof()) {
            dec.push_back(a);
            
            if (!(fin >> a) && !fin.eof()) {
                cout << "Неверный формат данных." << endl;
                dec.clear();
                return dec;
            }
        }
    }
    return dec;
}

//Преобразование дека с циклом for
deque<int> Modify(deque<int> &dec1) {
    deque<int> dec = dec1;
    int max = dec[1];
    int min = dec[1];
    int len = dec.size();
    for (const int i : dec) {
        if (i > max) {
            max = i;
        }
        if (i < min) {
            min = i;
        }
    }
    for (int &i: dec) {
        if (!(i & 1)) { //побитовое и
            i = max-min;
        }
    }
    return dec;
}

//Преобразование дека с итераторами
void Modify(deque<int>::iterator begin, deque<int>::iterator end) {
    int max = *begin;
    for (deque<int>::iterator i = begin; i != end; i++) {
        if (*i > max) max = *i;
    }
    int min = *begin;
    for (deque<int>::iterator i = begin; i != end; i++) {
        if (*i < min) min = *i;
    }
    for (deque<int>::iterator i = begin; i != end; i++) {
        if (!(*i & 1)) *i=max-min;
    }
}

//Преобразование дека с transform
void Modify_Transform(deque<int> &dec) {
    int max = *dec.begin();
    int min = *dec.begin();
    transform(dec.begin(), dec.end(), dec.begin(), [&max](int i) { if (i > max) max = i;    return i; });
    transform(dec.begin(), dec.end(), dec.begin(), [&min](int i) { if (i < min) min = i;    return i; });
    int d = max-min;
    transform(dec.begin(), dec.end(), dec.begin(), [d](int i) {return i & 1 ? i : d; });
}

//Преобразование дека с for_each
void Modify_For_Each(deque<int> &dec) {
    int max = *dec.begin();
    int min = *dec.begin();
    for_each(dec.begin(), dec.end(), [&max](int i) { if (i > max) max = i; });
    for_each(dec.begin(), dec.end(), [&min](int i) { if (i < min) min = i; });
    int d = max-min;
    for_each(dec.begin(), dec.end(), [d](int &i) { i= i & 1 ? i : d; });
}

//Подсчет суммы элементов
int Summ(deque<int> dec) {
    int summ = 0;
    for_each(dec.begin(), dec.end(), [&summ](int i) {summ+=i; });
    return summ;
}

//Подсчет среднего арифметического
double MidArith(deque<int> &dec) {
    return (double)Summ(dec) / dec.size();
}

//Печать в файл
void  Print(fstream &st,deque<int> &dec) {
    for_each(dec.begin(), dec.end(), [&st](int i) {st << i << " "; });
}

//Перегруженный метод, печать в консоль
void  Print(ostream &st, deque<int> dec) {
    for_each(dec.begin(), dec.end(), [&st](int i) {st << i << " "; });
    st << endl;
}

//Консольное меню
int Menu(int flag) {
    cout << "---------------------------------------" << endl;
    cout << "                 МЕНЮ                  " << endl;
    cout << "---------------------------------------" << endl;
    cout << 1 << " - " << "Создать новый файл со случайной последовательностью чисел." << endl;
    cout << 2 << " - " << "Загрузить последовательность из файла." << endl;
    if (flag > 0) {
        cout << 3 << " - " << "Заменить каждое четное число на разность максимального и минимального чисел. for" << endl;
        cout << 4 << " - " << "iterators" << endl;
        cout << 5 << " - " << "transform" << endl;
        cout << 6 << " - " << "for each" << endl;
        cout << 7 << " - " << "Вычислить сумму членов последовательности." << endl;
        cout << 8 << " - " << "Вычислить среднее арифметическое." << endl;
        cout << 9 << " - " << "Записать последовательность в файл." << endl;
        cout << 10 << " - " << "Напечатать последовательность." << endl;
    }
    cout << 0 << " - " << "Выход." << endl<<endl;
    cout << "---------------------------------------" << endl;

    int res;
    while (!(cin >> res) || (flag <= 0 && (res > 2)) || ((flag > 0) && (res > 10)));
    return res;
    
}

//Ввод ответа да/нет
bool InputQuery(string question) {
    cout << question << endl;
    cout << 1 << " - Да" << endl;
    cout << 0 << " - Нет" << endl;
    int res;
    while (!(cin >> res) || ((res != 0) && (res != 1)));
    return res==1;
}

//Ввод имени файла
string InputFileName() {
    string name;
    cout << "Введите имя файла" << endl;
    cin >> name;
    return name;
}

//Ввод числа
int InputNum(string str) {
    int Num;
    cout << str << endl;
    while (!(cin >> Num) || Num <= 0);
    return Num;
}

int main() {
    setlocale(LC_ALL, "Russian");
    bool exit = false;
    deque<int> dec;
    string FileName="";
    int N;
    int M;
    ofstream ofs;
    ifstream ifs;
    do {
        switch (Menu(dec.size())) {
            case 1:
                N = InputNum("Введите количество элементов.");
                M = InputNum("Введите максимальный модуль чисел.");
                FileName = InputFileName();
                ofs = CreateFileGenerate(FileName, N, M);
                break;
            case 2:
                if (FileName == "") FileName=InputFileName();
                else if (!InputQuery("Использовать текущий файл?")) {
                    FileName = InputFileName();
                }
                ifs.open(FileName);
                dec = LoadFromFile(ifs);
                ifs.close();
                break;
            case 3:
                dec = Modify(dec);
                break;
            case 4:
                Modify(dec.begin(), dec.end());
                break;
            case 5:
                Modify_Transform(dec);
                break;
            case 6:
                Modify_For_Each(dec);
                break;
            case 7:
                cout << "Сумма элементов равна " << Summ(dec) << endl;
                break;
            case 8:
                cout << "Среднее арифметическое равно " << MidArith(dec) << endl;
                break;
            case 9:
                FileName = InputFileName();
                ofs.open(FileName);
                Print(ofs, dec);
                ofs.close();
                break;
            case 10:
                Print(cout, dec);
                break;
            default:
                return 0;
        }
    } while (1);
    
}

