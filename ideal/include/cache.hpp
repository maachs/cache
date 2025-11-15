#ifndef IDEAL_CACHE
#define IDEAL_CACHE

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <queue>

template<typename Key_t, typename Value_t>
class ideal_cache_t {
    size_t size;            //cache size
    size_t curr_time;

    std::unordered_map<Key_t, Value_t> cache;
    std::unordered_map<Key_t, std::queue<size_t>> requests_time;

public:
    ideal_cache_t(size_t cache_size, std::vector<Value_t> data) : size(cache_size), curr_time(0), cache(), requests_time() {
        for(size_t time = 0, end_data = data.size(); time < end_data; time++) {
            requests_time[data[time]].push(time);
        }
    }

    bool lookup_update(Key_t key, Value_t value) {
        if(!requests_time[key].empty() && requests_time[key].front() == curr_time) {
            requests_time[key].pop();
        }

        if(cache.find(key) != cache.end()) {                 //hit
            curr_time++;
            return true;
        } else {                                             //miss
            if(cache.size() < size) {
                cache.emplace(key, value);
                curr_time++;
                return false;
            }

            auto key_to_delete = find_to_delete(key);

            if(key_to_delete != cache.end()) {
                cache.erase(key_to_delete);
                cache.emplace(key, value);
            }
            curr_time++;
            return false;
        }
    }

private:

    auto find_to_delete(Key_t key) {
        auto candidate = cache.end();
        size_t max_dist = 0;

        for(auto it = cache.begin(), end = cache.end(); it != end; it++) {
            if(requests_time[it->first].empty()) {
                candidate = it;
                break;
            }

            size_t dist = requests_time[it->first].front() - curr_time;
            if(dist > max_dist) {
                candidate = it;
                max_dist = dist;
            }
        }

        if(candidate != cache.end() && !requests_time[key].empty()) {
            if(requests_time[key].front() - curr_time < max_dist) {
                return candidate;
            }
        }
        return cache.end();
    }

    void print_requests() {
        for(auto iterator = requests_time.begin(), end_map = requests_time.end(); iterator != end_map; iterator++) {
            std::cout << iterator->first << " - ";
            std::queue<size_t> temp = iterator->second;

            if (temp.empty()) {
            std::cout << "empty";
            } else {
                while(!temp.empty()) {
                    std::cout << temp.front() << ", ";
                    temp.pop();
                }
                std::cout << std::endl;
            }
        }
    }

    void cache_print() {
        for(auto it = cache.begin(), end = cache.end(); it != end; it++) {
            std::cout << it->first << " <-> ";
        }
        std::cout << std::endl;
    }
};
#endif
