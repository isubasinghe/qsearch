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
    typedef struct {
        std::string content;
        unsigned long long wordsCount = 0;
        folly::F14FastMap<std::string, unsigned long long> docWords;
    } DocMetadata;
    class BatchInserter {
        private:
            folly::F14FastMap<std::string, DocMetadata *> documents;
            folly::F14FastMap<std::string, unsigned long long> *wordMap;
            friend class Manager;
        public:
            BatchInserter();
            ~BatchInserter();
            void addDocument(std::string doc);
            void addDocument(std::string id, std::string document);
    };
};

#endif // BATCH_INSERT_HPP