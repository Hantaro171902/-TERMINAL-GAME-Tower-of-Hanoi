#pragma once

#include <vector>
#include <string>

namespace HanoiTower {
    namespace Services {
        class LogService {
        public:
            // Writes a short moves log file under ./Logs/
            static void ToFileShort(const std::vector<std::string>& content,
                                    const std::string& role,
                                    int noDisks,
                                    int steps);
        };
    }
}
