
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

        // если в строке хоть какой-то символ не является цифрой, то строка - не число
        for (size_t i = 0; i < str.length(); i++) {
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
        result = 0;
        for (const char& ch : str) {
            result = result * 10 + (ch - '0');
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