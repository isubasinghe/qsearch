#include "docman/manager.hpp"

namespace docman {
    Manager::Manager() {

    }
    Manager::~Manager() {

    }

    bool Manager::insertToFST(std::string word) {
        return true;
    }

    bool Manager::processWord(std::string word) {
        this->insertToFST(word);
        return true;
    }

    bool Manager::insertToDocuments(std::string id, std::string document) {
        (this->documents)[id] = document;
        return true;
    }

    bool Manager::insertDocument(std::string document, std::string id) {
        boost::tokenizer<> tok(document);
        folly::F14FastSet<std::string> set;
        if(!(this->insertToDocuments(id, document))) {
            return false;
        }
        for(boost::tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
            this->processWord(*beg);
            set.insert(*beg);
        }
        for (std::string entry: set) {
            (this->wordMap)[entry]++;
        }
        return true;
    }

    bool Manager::insertDocument(std::string document) {
        boost::uuids::random_generator gen;
        boost::uuids::uuid uuid = gen();
        std::string uuidText = boost::lexical_cast<std::string>(uuid);
        return this->insertDocument(document, uuidText);
    }
}
