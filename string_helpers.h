
#ifndef PROJ2_STRING_HELPERS_H
#define PROJ2_STRING_HELPERS_H
#include <string>

class StringHelpers {
public:
    /*
     * Убирает пробелы вначале и в конце строки
     */
    static void Trim(std::string& str) {
        // вычисляем откуда будем "вырезать" строку
        size_t start = 0;
        while (start < str.length() && (str[start] == ' ' || str[start] == '\t')) {
            start++;
        }

        // и до куда
        size_t end = str.length();
        while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' || str[end - 1] == '\r' || str[end - 1] == '\n')) {
            end--;
        }

        str = str.substr(start, end - start);
    }

    static bool StringIsNumber(const std::string& str) {
        if (str.empty())
            return false;

        size_t start = 0;
        if (str[0] == '-') {
            start = 1;
            if (start == str.length()) // если после минуса ничего нет, то возвращаем false
                return false;
        }

        for (size_t i = start; i < str.length(); i++) {
            if (str[i] < '0' || str[i] > '9') {
                return false;
            }
        }
        return true;
    }

    static bool TryParseToInt(const std::string& str, int& result) {
        if (!StringIsNumber(str)) {
            return false;
        }

        bool negative = false;
        size_t start = 0;
        if (str[0] == '-') {
            negative = true;
            start = 1;
        }

        result = 0;
        for (size_t i = start; i < str.length(); i++) {
            int digit = str[i] - '0';
            if (!negative && result > (INT_MAX - digit) / 10) { // проверка на переполнение
                return false;
            }
            if (negative && result > (INT_MAX - digit) / 10) {
                // Для отрицательных чисел вначале накапливаем модуль. после этого изменим на отрицательное
                // Если result > (INT_MAX - digit) / 10, то при умножении на 10 и добавлении digit получим > INT_MAX и возникнет переполнение.
                return false;
            }
            result = result * 10 + digit;
        }

        if (negative) {
            result = -result;
            // если result стал равен 2147483648 после смены знака, то значит произошло переполнение
            if (result > 0 && negative) { // например, если было -2147483648, модуль 2147483648 не влезает в int
                return false;
            }
        }
        return true;
    }

    static void RemoveSuperfluousSpaces(std::string& str) {
        using namespace std;

        string result;
        bool already_added_space = false;


        // Читаем каждый символ строки. Если встретили пробел и already_added_space = false
        // и конечная строка (result) не пустая, то добавляем пробел и ставим already_added_space = true.
        // Если встречаем символ, то добавляем его к result и устанавливаем already_added_space = false

        for (const char& ch : str) {
            if (isspace(static_cast<unsigned char>(ch))) {
                if (!already_added_space && !result.empty()) {
                    result += ' ';
                    already_added_space = true;
                }
            } else {
                result += ch;
                already_added_space = false;
            }
        }

        // Если в конце исходной строки был пробел, то он так же добавится. Поэтому удаляем его
        if (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }

        str = result;
    }

    static int CountSpaces(const std::string& str) {
        int count = 0;
        for (const char& ch : str) {
            if (ch == ' ')
                count++;
        }

        return count;
    }

    static int CountTargetChars(const std::string& str, const char& target) {
        int count = 0;
        for (const char& ch : str) {
            if (ch == target)
                count++;
        }

        return count;
    }
};

#endif //PROJ2_STRING_HELPERS_H