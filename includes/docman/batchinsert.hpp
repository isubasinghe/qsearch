#ifndef BATCH_INSERT_HPP
#define BATCH_INSERT_HPP

#include <iostream>

namespace docman {
    class BatchInserter() {
        private:
            friend class Manager;
        public:
            void addDocument(std::string doc);
            
    }
};

#endif // BATCH_INSERT_HPP