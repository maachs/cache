#ifndef ARC_CACHE
#define ARC_CACHE

#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

template <typename T, typename KeyT = int >
struct cache_t {
    size_t size;
    std::list<T> list;

    using ListIt = typename std::list<T>::iterator;
    std::unordered_map<KeyT, ListIt> hash_table;

    bool is_cache_full() const {
        return list.size() >= size;
    };

    cache_t(size_t size_p) : size(size_p), list(),  hash_table() {};

    bool lookup_update(KeyT key) {
        auto hit = hash_table.find(key);
        if(hit == hash_table.end()) {
            if(is_cache_full()) {
                hash_table.erase(list.back());
                list.pop_back();
            }
            list.push_front(key);
            hash_table[key] = list.begin();
            return false;
        }
        auto eltit = hit->second;
        if(eltit != list.begin()) {
            list.splice(list.begin(), list, eltit, std::next(eltit));
        }
        return true;
    };

    void cache_dump() {
        for(auto i = list.begin(); i != list.end(); i++) {
            std::cout << *i << ' ' ;
        }
        std::cout << std::endl;
    }
};

#endif
