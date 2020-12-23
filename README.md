[![CodeFactor](https://www.codefactor.io/repository/github/isubasinghe/qsearch/badge)](https://www.codefactor.io/repository/github/isubasinghe/qsearch) 
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/2d2258adaac04c4b8408590d23e965bc)](https://www.codacy.com/manual/isubasinghe/qsearch?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=isubasinghe/qsearch&amp;utm_campaign=Badge_Grade)
![GitHub issues](https://img.shields.io/github/issues/isubasinghe/qsearch)

## Project is being rewritten in Rust with more advanced features. Will be open sourced soonish 

# QSearch
QSearch (quicksearch) is a search engine for read only data. This means it has the potential to be far more performant than other search engines. 


Please make sure to update tests as appropriate.

## Features 
* Batch Insert documents at the initialisation of the document manager
* Compression and fast retrieval of words thanks to the Automata that powers the query engine. 

## TODO
- [ ] Add document length normalisation
- [ ] Add support for write operations without sacrificing read speed
- [ ] Implement sift4 inheriting from some Corrector class in order to add fuzzy search
- [ ] Implement categorical search without performance hits (perhaps map categories to trees in the underlying sorted score container)
- [ ] expose API over an Abstract transport class
- [ ] expose API over HTTP
- [ ] Implement Raft over TCP or RSocket
- [ ] Implement ringpop in order to distribute documents over cluster
## License
GPL
