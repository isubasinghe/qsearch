#include "docman/manager.hpp"

namespace docman {
    Manager::Manager() {
        throw exceptions::NotImplementedException();
        this->scorer = new scorer::TFIDFScorer(&(this->documents), this->wordMap);
        // Guess about the number of words
        this->wordMap = new folly::F14FastMap<std::string, unsigned long long>(20000);
    }
    Manager::Manager(BatchInserter *bi) {
        this->wordMap = bi->wordMap;
        this->scorer = new scorer::TFIDFScorer(&(this->documents), this->wordMap);
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
    
    boost::container::list<std::string> search(std::string& query) {
        
    }
}
