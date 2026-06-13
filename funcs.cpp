#include "funcs.h"

#include "custom_map.h"
#include "exceptions.h"
#include "iostream"
#include "string"
#include "fstream"
#include "node.h"
#include "string_helpers.h"

/*
 * Извлекает две строки, разделенные пробелом
 */
std::pair<std::string, std::string> ExtractTwoVariablesFromString(const std::string& str) {
    using namespace std;
    size_t pos = str.find(' ');
    string first = str.substr(0, pos);
    string second = str.substr(pos + 1);
    return pair<string, string>(first, second);
}

Map LoadPathsFromFile(std::ifstream& file) {
    using namespace std;

    // Пара: .first - путь до вершины от корня, .second - значение вершины
    Map result_map;


    // читаем каждую строку. Используем getline(), чтобы читать каждую строку (т.к. формат ввода - каждая вершина в новой строке)
    // при этом учитываем некоторые случаи, когда:
    // 1. Строка может начинаться и заканчиваться пробелами (пр. "  5  1010  "). Обрезаем строки в начале и конце
    // 2. Между значением вершины и путем до вершины может быть хоть сколько пробелов (пр. "5        1010"). Игнорируем лишние пробелы
    // 3. Значение вершины может содержать или быть строкой (пр. "5f 1010" или "f 1010"). Выбрасываем ошибку
    // 4. Путь до вершины может содержать или быть строкой (при. "5 10f1" или "5 f"). Выбрасываем ошибку
    // 5. В строке дано либо только значение вершины, либотолько путь до вершины (пр. "1010" или "5"). Выбрасываем ошибку
    // 6. Путь вершины может содержать не только 1 или 0 (пр. "5 1020"). Выбрасываем ошибку.
    // 7. Пути до вершины может не существовать. Выбрасываем ошибку

    string line;
    int row = 0; // текущая строка. просто для выбросов ошибок, чтобы пользователь понимал где ошибка
    while (getline(file, line)) {
        row++;

        StringHelpers::Trim(line);  // Удаляем
        StringHelpers::RemoveSuperfluousSpaces(line); // Удаляем пробелы между значением и путем

        if (line.empty())
            continue;

        // Теперь, так как наша строка не имеет лишних пробелов (в начале, в конце и между), то проверяем количество "элементов".
        // Если количество пробелов = 1, то строка корректная. Иначе, некорректная и выбрасываем ошибку
        if (StringHelpers::CountSpaces(line) != 1)
            throw InvalidFileContentException("Нет вершины или пути до вершины (строка в файле №" + to_string(row) + ")");

        // На данном этапе строка гарантированно имеет вид "abc def"
        // Проверяем, что обе части строки (до и после пробела) - это числа
        pair<string, string> parts = ExtractTwoVariablesFromString(line);
        string path = parts.second;

        // Проверка, что обе части - это числа.
        // При этом первую часть мы сразу преобразуем в число методом TryParseToInt. А вторую часть лишь проверяем, что она число
        int value;
        if (!StringHelpers::TryParseToInt(parts.first, value) || !StringHelpers::StringIsNumber(path))
            throw InvalidFileContentException("Одна из частей не является числом (строка в файле №" + to_string(row) + ")");

        // Проверка, что путь до вершины имеет цифры только 1 и 0
        // Получаем количество единиц и нулей. Складываем. Если сумма равна длине строки, то цифры корректные.
        // Если количество не совпадает, то соответственно строка некорректная
        if (StringHelpers::CountTargetChars(path, '1') + StringHelpers::CountTargetChars(path, '0') != path.length())
            throw InvalidFileContentException("Некорректный путь до вершины (строка в файле №" + to_string(row) + ")");


        // Проверка уникальности пути. Пытаемся добавить в итоговый map новую пару
        if (result_map.Contains(path))
            throw InvalidFileContentException("Такой путь уже есть (строка в файле №" + to_string(row) + ")");

        result_map.Insert(path, value);

    }

    return result_map;
}

void InitTask() {
    using namespace std;

    string filename;
    Map paths;

    while (true) {
        cout << "Введите название файла (пр. input.txt) или \"Отмена\" для выхода: ";
        getline(cin, filename);

        if (filename == "Отмена" || filename == "отмена")
            return;

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл, попробуйте еще раз" << endl;
            continue;
        }

        try {
            paths = LoadPathsFromFile(file);
            break;
        } catch (const InvalidFileContentException& e) {
            cout << "Ошибка чтения файла: " << e.GetError() << endl;
        }
    }

    // Заполнение дерева
    Node tree(0);   // 0 так как по условию задачи корень это 0

    for (pair<string, int> kv : paths) {
        tree.InsertByPath(kv.first, kv.second);
    }

    if (!tree.IsValidTree())
        cout << "Дерево нельзя построить, так как есть промежуточные узлы без значений" << endl;
    else {
        cout << "Дерево успешно построено" << endl;
        tree.Print();
    }
}
