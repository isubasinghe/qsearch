#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <folly/container/F14Map.h>
#include <folly/container/F14Set.h>
#include <folly/AtomicHashmap.h>
#include <folly/AtomicLinkedList.h>
#include <boost/tokenizer.hpp>
#include <iostream>

namespace docman {

    class Manager {
        private:
            bool insertToFST(std::string word);
            bool processWord(std::string word);
            bool insertToDocuments(std::string id, std::string document);
            folly::F14FastMap<std::string, std::string> documents;
            folly::F14FastMap<std::string, unsigned long long> wordMap;
          
        public:
            bool insertDocument(std::string document, std::string id);
            bool insertDocument(std::string document);
            std::string retrieveDocument(std::string id);
            Manager();
            ~Manager();
    };
};

#endif // MANAGER_HPP