#include "docman/persistedengine.hpp"


PersistedEngine::PersistedEngine() {
    this->options.IncreaseParallelism();
    this->options.OptimizeLevelStyleCompaction();
    this->options.create_if_missing=true;
};

bool PersistedEngine::setup() {
    rocksdb::Status s = rocksdb::DB::Open(this->options, "./db", &(this->db));

    return s.ok();
}

PersistedEngine::~PersistedEngine() {
    delete db;
};