#include "log_service.hpp"
#include "design_char_constants.hpp" // adjust path if your headers are in GameElements/ subfolder

#include <filesystem>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

namespace HanoiTower {
    namespace Services {

        void LogService::ToFileShort(const vector<string>& content,
                                     const string& role,
                                     int noDisks,
                                     int steps)
        {
            namespace fs = filesystem;

            // Create Logs directory next to current working directory
            fs::path logDir = fs::current_path() / "Logs";
            if (!fs::exists(logDir)) {
                error_code ec;
                fs::create_directory(logDir, ec);
                // if creation failed, we just attempt to continue; the ofstream open will fail later
            }

            // Get current local time for file name and header
            time_t t = time(nullptr);
            tm tm = *localtime(&t);

            // Filename: day_month_year_MovesLog_<role>.txt
            ostringstream fname;
            fname << tm.tm_mday << "_" << (tm.tm_mon + 1) << "_" << (tm.tm_year + 1900)
                  << "_MovesLog_" << role << ".txt";

            fs::path filePath = logDir / fname.str();

            ofstream writer(filePath.string(), ios::out);
            if (!writer.is_open()) {
                // Could not open file — silently return (or you may log to stderr)
                return;
            }

            // Print header (DesignCharConstants::Header is a vector<string>)
            for (const auto& s : HanoiTower::GameElements::DesignCharConstants::Header) {
                writer << s << "\n";
            }
            writer << "\n";

            // Human readable timestamp
            writer << put_time(&tm, "%c %Z") << "\n";

            // Meta line
            writer << "#" << steps << "   No. of disks: " << noDisks
                   << "   Played by: " << role << "\n";

            writer << HanoiTower::GameElements::DesignCharConstants::LineBreak << "\n\n";

            // Write moves: prefix numbered items that contain "->"
            int noSteps = 1;
            for (const auto& line : content) {
                if (line.find("->") != string::npos) {
                    writer << noSteps << ") " << line << "\n";
                    ++noSteps;
                } else {
                    writer << line << "\n";
                }
            }

            writer.close();
        }

    } // namespace Services
} // namespace HanoiTower
