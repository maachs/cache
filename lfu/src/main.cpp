#include "cache.hpp"

int main()
{
    size_t cache_size = 0, data_size = 0;
    std::cin >> cache_size >> data_size;
    LFU_cache_t<int, int> cache {cache_size};

    int data_elem = 0;
    std::vector<int> data = {};
    for(size_t i = 0; i < data_size; ++i) {
        std::cin >> data_elem;
        data.push_back(data_elem);
    }
    //std::vector<int> data = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
    //std::vector<int> data = {1, 2, 3 ,4, 1, 1};
    //std::vector<int> data = {1, 1, 2, 3, 4, 5, 3, 4, 5, 3 ,3 ,6, 1,  2, 1};

    int hits = 0, misses = 0;
    bool result = 0;
    for(int data_element : data) {
        result = cache.lookup_update(data_element, data_element);
        if(result) {
            hits++;
        } else {
            misses++;
        }
    }

    //std::cout << "hits: " << hits << std::endl << "misses: " << misses << std::endl;
    std::cout << hits << std::endl;
}
