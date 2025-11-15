#ifndef LFU_CACHE
#define LFU_CACHE

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <assert.h>

const int INIT_MAX_FREQ = 100;

template <typename Key_t, typename Value_t>
struct cache_cell_t {
    Key_t   key   {};
    Value_t value {};

    size_t freq_of_requests {};
    size_t last_accessed    {};
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
    LFU_cache_t(size_t size_p) : size(size_p), list(), curr_time(0), min_freq(INIT_MAX_FREQ), hash_table() {};

    bool lookup_update(Key_t key, Value_t value) {
        if(size == 0) return false;
        //print_list();
        //std::cout << "min_freq = " << min_freq << ",curr_time = " << curr_time << std::endl;
        curr_time++;
        auto hit = hash_table.find(key);

        if (hit != hash_table.end()) {         //hit
            //std::cout << "hit" << std::endl;
            ListIt list_it = hit->second;
            //std::cout << "list_it: " << &list_it << std::endl;
            bool update_min_freq = 0;

            if(list_it->freq_of_requests == min_freq) {
                for(auto it = list.begin(); it != list.end(); it++) {
                    if(it->freq_of_requests == min_freq && it != list_it) {
                        update_min_freq = 1;
                        break;
                    }
                }
                if(!update_min_freq) {
                    min_freq++;
                }
            }
            list_it->freq_of_requests++;

            //update_cache(list_it);
            //print_list();
            return true;
        }
        else
        {
            //std::cout << "MISS" << std::endl << "LIST_SIZE = " << list.size() << " size = " << size << std::endl;
            if(list.size() >= size) { pop_elem(); }
            //std::cout << "chlen1" << std::endl;
            add_new_elem(key, value);
            //print_list();
            return false;
        }

    };

private:
    void update_cache(ListIt list_it) {
        auto cell = *list_it;
        list.erase(list_it);
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
        ListIt candidate_for_delete = list.begin();
        for(auto it = candidate_for_delete; it != list.end(); it++)
        {
            if(it->freq_of_requests == min_freq)
            {
                if(it->last_accessed < candidate_for_delete->last_accessed)
                {
                    candidate_for_delete = it;
                }
            }
        }

        hash_table.erase(candidate_for_delete->key);
        list.erase(candidate_for_delete);
        /*for (auto it = list.begin(); it != list.end(); it++) {
            if (it->freq_of_requests == min_freq) {
                hash_table.erase(it->key);
                list.erase(it);
                break;
            }
        }*/
    }

    void add_new_elem(Key_t key, Value_t value) {
        cache_cell_t<Key_t, Value_t> new_cell{key, value, 1, curr_time};

        auto it = list.begin();
        while (it != list.end() && it->freq_of_requests == 1) {
            it++;
        }
        ListIt new_it = list.insert(it, new_cell);
        hash_table[key] = new_it;
        min_freq = 1;
    }

    void print_list() {
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (it == list.begin())
        {
            std::cout << it->value << "[" << it->freq_of_requests << "]";
        }
        else
        {
            std::cout << " <-> " << it->value << "[" << it->freq_of_requests << "]";
        }
    }
    std::cout << std::endl;
}
};
#endif
