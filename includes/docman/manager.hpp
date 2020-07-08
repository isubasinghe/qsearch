#ifndef MANAGER_HPP
#define MANAGER_HPP

#define PADDING_SIZE 128 

#include <iostream>
#include <vector>
#include <set>
#include <thread>

#include <folly/container/F14Map.h>
#include <folly/container/F14Set.h>
#include <folly/AtomicLinkedList.h>
#include <folly/futures/Future.h> 
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <boost/tokenizer.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/container/list.hpp>
#include <boost/heap/fibonacci_heap.hpp>
#include <boost/heap/pairing_heap.hpp>


#include "docman/batchinsert.hpp"
#include "fst/fst.hpp"
#include "scorer/scorer.hpp"
#include "scorer/tfidf.hpp"
#include "exceptions/notimpl.hpp"

namespace docman {
    typedef struct {
        std::string id;
        double score;
    } SearchResult;
    typedef struct {
        bool operator()(const SearchResult& a, const SearchResult& b) const {
            return a.score > b.score;
        }
    } SearchResultCompare;

    typedef struct {
        bool operator()(const fst::scoreIteratorPair& a, const fst::scoreIteratorPair& b) const {
            double ascore = (*std::get<0>(a)).score;
            double bscore = (*std::get<0>(b)).score;
            return ascore < bscore;
        }
    } KWayMergeCompare;

    class Manager {
        private:
            folly::F14FastMap<std::string, std::string> documents;
            folly::F14FastMap<std::string, unsigned long long> *wordMap;
            scorer::Scorer *scorer;
            bool insertToFST(std::string &id, double score, const std::string &word);
            bool insertToDocuments(std::string id, std::string document);
            void rebuildIndicies(std::string &word);
        public:
            Manager(BatchInserter *batchInsertJob);
            Manager();
            ~Manager();
             fst::FST fst;
            bool insertDocument(std::string document, std::string id);
            bool insertDocument(std::string document);
            std::string retrieveDocument(std::string id);
            boost::container::list<std::string> search(std::string query, unsigned long long k); 
    };
};

#endif // MANAGER_HPP