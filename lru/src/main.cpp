#include <cache.hpp>

int main()
{
    //size_t temp_size = 0;
    //std::cin >> temp_size;
    cache_t<int> cache {4};

    std::vector<int> data = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
    //std::cout << data.size() << std::endl;

    int hits = 0, misses = 0;
    bool res = 0;

    for(int key : data) {
        res = cache.lookup_update(key);

        if(res) {
            hits++;
        } else {
            misses++;
        }

        cache.cache_dump();
    }

    std::cout << "hits: " << hits << std::endl << "misses: " << misses << std::endl;
}
