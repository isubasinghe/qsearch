#include "docman/batchinsert.hpp"

namespace docman {
    BatchInserter::BatchInserter() {
        this->documents.clear();
    }
    void BatchInserter::addDocument(std::string id, std::string document) {
        boost::tokenizer<> tok(document);
        DocMetadata *doc = new DocMetadata();
        doc->content = document;
        for(boost::tokenizer<>::iterator beg=tok.begin(); beg != tok.end(); ++beg) {
            (doc->docWords)[*beg] += 1;
            (doc->wordsCount)++;
        }
        for(auto entry: (doc->docWords)) {
            (this->wordMap)[entry.first]++;
        }
        (this->documents)[id] = doc;
    }
    void BatchInserter::addDocument(std::string document) {
        boost::uuids::random_generator gen;
        boost::uuids::uuid uuid = gen();
        std::string uuidText = boost::lexical_cast<std::string>(uuid);
        this->addDocument(uuidText, document);
    }
    BatchInserter::~BatchInserter() {
        for (auto entry: (this->documents)) {
            delete entry.second;
        }
    }
};