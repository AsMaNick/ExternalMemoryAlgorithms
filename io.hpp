#pragma once
#include <cassert>
#include <string>
#include <fstream>

using namespace std;

template<const int buffer_size>
class Reader {
public:
    Reader(const string &filename):
        in(filename, ifstream::binary), position(0), lbuf(0), rbuf(0) {
    }

    template<typename T>
    T read() {
        if (position < lbuf || position + sizeof(T) > rbuf) {
            read_to_buffer(position);
        }
        T *res = (T*) (data + position - lbuf);
        position += sizeof(T);
        return *res;
    }

    void set_position(size_t pos) {
        position = pos;
    }

private:
    void read_to_buffer(size_t start) {
        in.seekg(start);
        in.read(data, buffer_size);
        lbuf = start;
        rbuf = start + in.gcount();
    }

    size_t position, lbuf, rbuf;
    char data[buffer_size];
    ifstream in;
};

template<const int buffer_size>
class Writer {
public:
    Writer(const string &filename): out(filename, ofstream::binary), position(0), lbuf(0), rbuf(0) {
    }

    template<typename T>
    void write(T value) {
        if (position < lbuf || position + sizeof(T) > lbuf + buffer_size) {
            flush();
            lbuf = rbuf = position;
        }
        T *res = (T*) (data + position - lbuf);
        *res = value;
        position += sizeof(T);
        rbuf = max(rbuf, position);
    }

    void set_position(size_t pos) {
        position = pos;
    }

    void flush() {
        out.seekp(lbuf);
        out.write(data, rbuf - lbuf);
        out.flush();
    }

private:
    size_t position, lbuf, rbuf;
    char data[buffer_size];
    ofstream out;
};
