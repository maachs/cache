#include "cache.hpp"

int main()
{
    size_t cache_size = 0, data_size = 0;
    std::cin >> cache_size >> data_size;

    int data_elem = 0;
    std::vector<int> data = {};
    for(size_t i = 0; i < data_size; ++i) {
        std::cin >> data_elem;
        data.push_back(data_elem);
    }
    ideal_cache_t <int, int> cache (cache_size, data);

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

    std::cout << hits << std::endl;
}
