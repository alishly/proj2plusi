#ifndef PROJ2_IO_H
#define PROJ2_IO_H

#include "iostream"

class IoUtils {
public:
    static void ClearInput() {
        using namespace std;
        cin.clear();
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }

    static bool TryReadInt(int &value) {
        using namespace std;

        cin >> value;
        bool success = !cin.fail();
        ClearInput();
        return success;
    }
};

#endif //PROJ2_IO_H
