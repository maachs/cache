#include "cache.hpp"

int main() {
    LFU_cache_t<size_t, int> cache {4};

    std::vector<int> data = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};

    int hits = 0, misses = 0;
    bool res = 0;

    for(int key : data) {
        res = cache.lookup_update(key);
        if(res) {
            hits++;
        } else {
            misses++;
        }
        //cache.cache_dump();
    }

    std::cout << "hits: " << hits << std::endl << "misses: " << misses << std::endl;
}
