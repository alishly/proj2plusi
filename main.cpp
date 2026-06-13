#include "funcs.h"
#include "io.h"
#include "iostream"
#include "windows.h"


int main() {
    using namespace std;
    
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    while (true) {
        cout << "0) Выход из программы" << endl;
        cout << "1) Построить дерево из файла" << endl;
        cout << "Выберите действие: ";

        int choice;
        if (!IoUtils::TryReadInt(choice)) {
            cout << "Неверный ввод, попробуйте еще раз" << endl;
            continue;
        }

        switch (choice) {
            case 0:
                cout << "Выход" << endl;
                return 0;
            case 1:
                InitTask();
                break;
            default:
                cout << "Неверный ввод, попробуйте еще раз" << endl;
                break;
        }
    }
}
