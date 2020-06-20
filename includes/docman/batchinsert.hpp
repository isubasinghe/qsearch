#ifndef BATCH_INSERT_HPP
#define BATCH_INSERT_HPP

#include <folly/container/F14Map.h>
#include <folly/container/F14Set.h>
#include <folly/AtomicHashmap.h>
#include <folly/AtomicLinkedList.h>
#include <boost/tokenizer.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

#include <iostream>

namespace docman {
    class BatchInserter {
        private:
            folly::F14FastMap<std::string, std::string> documents;
            folly::F14FastMap<std::string, unsigned long long> wordMap;
            friend class Manager;
        public:
            void addDocument(std::string doc);
    };
};

#endif // BATCH_INSERT_HPP