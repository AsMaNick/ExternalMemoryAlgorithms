#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

class Tqdm {
public:
    Tqdm(): it(0), len(-1), message(""), start_clock(clock()) {
    }

    Tqdm(long long len): it(0), len(len), message(""), start_clock(clock()), last_it(0), update_its(1) {
    }

    Tqdm(long long len, long long update_its): it(0), len(len), message(""), start_clock(clock()), last_it(0), update_its(update_its) {
    }

    Tqdm(long long len, long long update_its, const std::string &message): it(0), len(len), message(message), start_clock(clock()), last_it(0), update_its(update_its) {
    }

    void start() {
        start_clock = clock();
        std::cout << message << get_status();
    }

    void update() {
        ++last_it;
        if (last_it != update_its) {
            ++it;
            return;
        }
        last_it = 0;
        std::string old_status = get_status();
        ++it;
        std::string new_status = get_status();
        if (update_its != 1 || old_status != new_status) {
            std::cout << '\r' << message << new_status;
            std::cout.flush();
        }
    }

    void update(long long to, bool force = false) {
        std::string old_status = get_status();
        it = to;
        std::string new_status = get_status();
        if (old_status != new_status || force) {
            std::cout << '\r' << message << new_status;
            std::cout.flush();
        }
    }

    void finish() {
        update(len, true);
        std::cout << std::endl;
    }

    double get_time() const {
        return 1.0 * (clock() - start_clock) / CLOCKS_PER_SEC;
    }

private:

    std::string get_status() const {
        std::stringstream s;
        s << std::fixed << std::setprecision(2) << 100.0 * it / len << "%, elapsed " << std::setprecision(2) << get_time() << "s";
        return s.str();
    }

    long long it, len, start_clock, last_it, update_its;
    std::string message;
};
