#include "docman/manager.hpp"

namespace docman {
    Manager::Manager() {
        throw exceptions::NotImplementedException();
        this->scorer = new scorer::TFIDFScorer(&(this->documents), this->wordMap);
        // Guess about the number of words
        this->wordMap = new folly::F14FastMap<std::string, unsigned long long>(20000);
        // May return 0 if it fails to detect, so add 1
        this->threadPoolExec = new folly::CPUThreadPoolExecutor(std::thread::hardware_concurrency() + 1);
    }
    Manager::Manager(BatchInserter *bi) {
        this->wordMap = bi->wordMap;
        this->scorer = new scorer::TFIDFScorer(&(this->documents), this->wordMap);
         // May return 0 if it fails to detect, so add 1
        this->threadPoolExec = new folly::CPUThreadPoolExecutor(std::thread::hardware_concurrency() + 1);
        
        unsigned long long size = (bi->documents).size();
        for(auto docEntry: (bi->documents)) {
            folly::F14FastMap<std::string, unsigned long long>& docWords = (docEntry.second)->docWords;
            for(auto mappedValues: docWords) {
                double score = this->scorer->score(size, 
                    (*(this->wordMap))[mappedValues.first], 
                        mappedValues.second, (docEntry.second)->wordsCount);
                this->fst.addWord(docEntry.first, score, mappedValues.first);
            }
        }
    }
    Manager::~Manager() {
        delete this->scorer;
        // Ensure BatchInserter does not delete this, or a double free will occur.
        delete this->wordMap;
    }

    bool Manager::insertToFST(std::string &id, double score, const std::string &word) {
        return fst.addWord(id, score, word);
    }

    bool Manager::insertToDocuments(std::string id, std::string document) {
        (this->documents)[id] = document;
        return true;
    }

    bool Manager::insertDocument(std::string document, std::string id) {
        throw exceptions::NotImplementedException();
        boost::tokenizer<> tok(document);
        folly::F14FastMap<std::string, unsigned long long> docWords;
        unsigned long long wordsCount = 0;
        if(!(this->insertToDocuments(id, document))) {
            return false;
        }
        for(boost::tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
            docWords[*beg] += 1;
            wordsCount++;
        }
        for (auto entry: docWords) {
            // Need to perform this operation before score calculation.
            // update the number of documents with this word by 1
            (*(this->wordMap))[entry.first]++;

            double score = this->scorer->score(entry.first, entry.second, wordsCount);
            this->insertToFST(id, score, entry.first);


        }
        return true;
    }

    bool Manager::insertDocument(std::string document) {
        throw exceptions::NotImplementedException();
        boost::uuids::random_generator gen;
        boost::uuids::uuid uuid = gen();
        std::string uuidText = boost::lexical_cast<std::string>(uuid);
        return this->insertDocument(document, uuidText);
    }
    
    boost::container::list<std::string> Manager::search(std::string query, unsigned long long k) {
        boost::container::list<std::string> ids;
        boost::tokenizer<> tok(query);
     
        std::vector<fst::scoreIteratorPair> results;
        for(boost::tokenizer<>::iterator beg=tok.begin(); beg != tok.end(); ++beg) {
            std::string word = *beg;
            auto iterPair = (this->fst).getIterator(word);
            results.push_back(iterPair);
        }

        boost::heap::fibonacci_heap<SearchResult, boost::heap::compare<SearchResultCompare>> topK;

        boost::heap::fibonacci_heap<fst::scoreIteratorPair, boost::heap::compare<KWayMergeCompare>> extractHeap;

        folly::F14FastMap<std::string, boost::heap::fibonacci_heap<SearchResult, 
            boost::heap::compare<SearchResultCompare>>::handle_type> handleMap(k);

        for(fst::scoreIteratorPair& result: results) {
            if(std::get<0>(result) != std::get<1>(result)) {
                extractHeap.push(result);
            }
        }

        unsigned long long documents = 0;

        while(documents < k) {
            if(extractHeap.size() < 1) {
                break;
            }

            fst::scoreIteratorPair iterPair = extractHeap.top();
            extractHeap.pop();
            std::string id = (*std::get<0>(iterPair)).docId;
            double score = (*std::get<0>(iterPair)).score;
            std::get<0>(iterPair)++;
            if(std::get<0>(iterPair) != std::get<1>(iterPair)) {
                extractHeap.push(iterPair);
            }

            auto maybeValue = handleMap.find(id);
            if(maybeValue == handleMap.end()) {
                SearchResult searchResult;
                searchResult.id = id;
                searchResult.score = score;
                if((topK.size() < k)) {
                    auto handle = topK.push(searchResult);
                    handleMap[id] = handle;
                    documents++;
                }else {
                    auto value = topK.top();
                    if(value.score < score) {
                        topK.pop();
                        handleMap.erase(value.id);
                        auto handle = topK.push(searchResult);
                        handleMap[id] = handle;
                        documents++;
                    }
                }
            }else {
                (*(maybeValue->second)).score += score;
                topK.decrease(maybeValue->second);
            }
        }

        for(auto& result: topK) {
            std::cout << result.id << "\t" << result.score << std::endl;
        }
        
        return ids;
        
    }
}
