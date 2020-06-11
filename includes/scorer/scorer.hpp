#ifndef SCORER_HPP
#define SCORER_HPP

#include <folly/container/F14Map.h>
#include <iostream>

namespace scorer {
    class Scorer {
        private:
            folly::F14FastMap<std::string, std::string> *documents;
        public:
            Scorer(folly::F14FastMap<std::string, std::string> *documents);
            virtual ~Scorer();
    };
};

#endif // SCORER_HPP