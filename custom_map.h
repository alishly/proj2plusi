
#ifndef PROJ2_CUSTOM_MAP_H
#define PROJ2_CUSTOM_MAP_H
#include <string>
#include <vector>

class Map {
private:
    std::vector<std::pair<std::string, int>> data;

public:
    void Insert(const std::string& key, int value) {
        using namespace std;

        // Если пара с таким ключем уже есть, то не добавляем
        for (size_t i = 0; i < data.size(); i++)
            if (data[i].first == key)
                return;

        data.push_back(pair<string, int>(key, value));
    }

    bool Contains(const std::string& key) const {
        // Если пара с таким ключем есть, то возвращаем true
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].first == key) {
                return true;
            }
        }
        return false;
    }

    /*
     * Итератор для for
     */
    std::vector<std::pair<std::string, int>>::const_iterator begin() const {
        return data.begin();
    }

    /*
     * Итератор для for
     */
    std::vector<std::pair<std::string, int>>::const_iterator end() const {
        return data.end();
    }
};

#endif //PROJ2_CUSTOM_MAP_H