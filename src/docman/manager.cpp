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
        for(boost::tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
            this->processWord(*beg);
            std::cout << *beg << "\n";
        }
        return true;
    }

    bool Manager::insertDocument(std::string document) {
        return this->insertDocument(document, "1");
    }
}
