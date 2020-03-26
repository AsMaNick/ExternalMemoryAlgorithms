#include <random>
#include <cstdlib>
#include <iostream>
#include "io.hpp"
#include "tqdm.hpp"

using namespace std;

void write_big_file(const string &filename, size_t n) {
    const size_t buffer_size = 1000000;
    mt19937_64 generator;
    Writer<buffer_size> writer(filename);
    Tqdm tq(n, 1000000);
    tq.start();
    for (size_t i = 0; i < n; ++i) {
        writer.write<long long>(generator());
        tq.update();
    }
    writer.flush();
    tq.finish();
}

void read_big_file(const string &filename, size_t n) {
    const size_t buffer_size = 1000000;
    Reader<buffer_size> reader(filename);
    Tqdm tq(n, 1000000);
    tq.start();
    for (size_t i = 0; i < n; ++i) {
        long long x = reader.read<long long>();
        tq.update();
    }
    tq.finish();
}

double get_sequential_read_speed() {
}

double get_sequential_write_speed() {
}

double get_random_read_speed() {
}

double get_random_write_speed() {
}

int main() {
    write_big_file("data.bin", 2000000000);
    return 0;
}
