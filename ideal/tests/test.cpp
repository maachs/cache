#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <gtest/gtest.h>
#include "../include/cache.hpp"

TEST(CacheTest, TEST1)
{
    std::vector<int> data = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
    ideal_cache_t<int, int> cache {4, data};

    int hits = 0, misses = 0;
    bool result = 0;
    for(int data_elem : data) {
        result = cache.lookup_update(data_elem, data_elem);
        if(result) {
            hits++;
        } else {
            misses++;
        }
    }

    EXPECT_EQ(hits, 7);
    EXPECT_EQ(misses, 5);
}

TEST(CacheTest, TEST2)
{
    std::vector<int> data = {0, 0, 0, 2, 2,
                              0, 0, 2, 1, 6,
                              8, 9, 8, 8, 1};
    ideal_cache_t<int, int> cache {3, data};

    int hits = 0, misses = 0;
    bool result = 0;
    for(int data_elem : data) {
        result = cache.lookup_update(data_elem, data_elem);
        if(result) {
            hits++;
        } else {
            misses++;
        }
    }

    EXPECT_EQ(hits, 9);
    EXPECT_EQ(misses, 6);
}

TEST(CacheTest, TEST3)
{
    std::vector<int> data = {5,4, 9,9,2,3,4,5,5,9};
    ideal_cache_t<int, int> cache {3, data};

    int hits = 0, misses = 0;
    bool result = 0;
    for(int data_elem : data) {
        result = cache.lookup_update(data_elem, data_elem);
        if(result) {
            hits++;
        } else {
            misses++;
        }
    }

    EXPECT_EQ(hits, 5);
    EXPECT_EQ(misses, 5);
}

