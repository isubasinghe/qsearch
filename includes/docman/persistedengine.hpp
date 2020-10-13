#ifndef PERSISTEDENGINE_HPP
#define PERSISTEDENGINE_HPP


#include <iostream>
#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>

class PersistedEngine {
    public:
        PersistedEngine();
        ~PersistedEngine();
        bool setup();
    private:
        rocksdb::DB* db;
        rocksdb::Options options;
};


#endif // PERSISTEDENGINE_HPP