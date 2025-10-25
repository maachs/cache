#ifndef LFU_CACHE
#define LFU_CACHE

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>

const int INIT_MAX_FREQ = 100;

template <typename Key_t, typename Value_t>
struct cache_cell_t {
    Key_t   key   {};
    Value_t value {};

    size_t freq_of_requests{0};
    size_t last_accessed   {0};
};

template <typename Key_t, typename Value_t>
struct LFU_cache_t {
private:
    size_t size;                                    //cache size
    std::list<cache_cell_t<Key_t, Value_t>> list;
    size_t curr_time;                               //algorithm operation time(amount of all request)
    size_t min_freq;

    using ListIt = typename std::list<cache_cell_t<Key_t, Value_t>>::iterator;
    std::unordered_map<Key_t, ListIt> hash_table;
public:
    LFU_cache_t(size_t size_p) : size(size_p), list(), curr_time(0), min_freq(100), hash_table() {};

    bool lookup_update(Key_t key, Value_t value) {
        if(size == 0) return false;

        curr_time++;
        auto hit = hash_table.find(key);

        if(hit != hash_table.end()) {           //hit
            ListIt list_it = hit->second;
            list_it->value = value;
            list_it->freq_of_requests++;

            update_cache(list_it);
            return true;
        } else {
            if(hash_table.size() >= size) { pop_elem(); }

            add_new_elem(key, value);
            return false;
        }

    };

private:
    void update_cache(ListIt list_it) {
        auto cell = *list_it;
        list.erase(list_it); //TODO хэш таблица не должна расти бесконечно
        auto it = list.begin();
        while (it != list.end() && it->freq_of_requests <= cell.freq_of_requests) {
            ++it;
        }
        ListIt new_it = list.insert(it, cell);
        hash_table[cell.key] = new_it;
        cell.last_accessed = curr_time;
        //std::cout << curr_time << std::endl;
    }

    void pop_elem() {
        for (auto it = list.begin(); it != list.end(); it++) {
            if (it->freq_of_requests == min_freq) {
                hash_table.erase(it->key);
                list.erase(it);
                break;
            }
        }
    }

    void add_new_elem(Key_t key, Value_t value) {
        cache_cell_t<Key_t, Value_t> new_cell{key, value, 1};

        auto it = list.begin();
        while (it != list.end() && it->freq_of_requests == 1) {
            it++;
        }
        ListIt new_it = list.insert(it, new_cell);
        hash_table[key] = new_it;
        min_freq = 1;
    }


};
#endif
