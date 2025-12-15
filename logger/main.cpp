#include "iface.h"
#include "loggers.h"

#include <thread>
#include <vector>
#include <sstream>


// Пример использования директив проверки system-специфичных макросов
#ifdef _WIN32
    #include <windows.h>          // Windows
    void clear_screen() {
        system("cls");
    }
#else
    #include <unistd.h>           // Unix/Linux/macOS
    void clear_screen() {
        system("clear");
    }
#endif


void worker(int id) {
    std::ostringstream oss;
    oss << "Worker " << id << " started";
    GLogger::info(oss.str());

    for (int i = 0; i < 5; ++i) {
        std::ostringstream step;
        step << "Worker " << id << " processing step " << i;
        GLogger::info(step.str());
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    if (id == 2) {
        GLogger::error("Something went wrong in worker 2!");
    }

    std::ostringstream fin;
    fin << "Worker " << id << " finished";
    GLogger::info(fin.str());
}

int main() {
    ConsoleLogger* console = new ConsoleLogger();
    FileLogger* file = new FileLogger("app.log");

    GLogger::add(console);
    GLogger::add(file);

#ifdef __linux__
    SyslogLogger* syslog = new SyslogLogger();
    GLogger::add(syslog);
#endif

    GLogger::info("Application started");

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) t.join();

    GLogger::info("Application finished");

    delete console;
    delete file;
#ifdef __linux__
    delete syslog;
#endif

    return 0;
}