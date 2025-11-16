#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <gtest/gtest.h>
#include "../include/cache.hpp"

TEST(CacheTest, CTOR)
{
    LFU_cache_t<int, int> cache {1};

}
TEST(CacheTest, TEST1)
{
    LFU_cache_t<int, int> cache {3};
    std::vector<int> data = {1, 2, 3, 4, 1, 1};

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

    EXPECT_EQ(hits, 1);
    EXPECT_EQ(misses, 5);
}

TEST(CacheTest, TEST2)
{
    LFU_cache_t<int, int> cache {2};
    std::vector<int> data = {1, 1, 1};

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

    EXPECT_EQ(hits, 2);
    EXPECT_EQ(misses, 1);
}

TEST(CacheTest, TEST3)
{
    LFU_cache_t<int, int> cache {3};
    std::vector<int> data = {3, 6, 2, 2};

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

    EXPECT_EQ(hits, 1);
    EXPECT_EQ(misses, 3);
}

TEST(CacheTest, TEST4)
{
    LFU_cache_t<int, int> cache {4};
    std::vector<int> data = {1, 1, 2, 3, 4,
                             5, 3, 4, 5, 3,
                             3, 6, 1, 2, 1};

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

    EXPECT_EQ(hits, 6);
    EXPECT_EQ(misses, 9);
}

TEST(CacheTest, TEST5)
{
    LFU_cache_t<int, int> cache {3};
    std::vector<int> data = {1, 2, 3, 4, 1, 2, 5, 1};

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

    EXPECT_EQ(hits, 1);
    EXPECT_EQ(misses, 7);
}

TEST(CacheTest, TEST6)
{
    LFU_cache_t<int, int> cache {1};
    std::vector<int> data = {1, 1, 1, 1, 1};

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

    EXPECT_EQ(hits, 4);
    EXPECT_EQ(misses, 1);
}

TEST(CacheTest, TEST7)
{
    LFU_cache_t<int, int> cache {4};
    std::vector<int> data = {1, 2, 3, 4, 1, 2, 3, 4, 5, 6};

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

    EXPECT_EQ(hits, 4);
    EXPECT_EQ(misses, 6);
}

TEST(CacheTest, TEST8)
{
    LFU_cache_t<int, int> cache {2};
    std::vector<int> data = {1, 2, 3, 1, 2, 3, 4};

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

    EXPECT_EQ(hits, 0);
    EXPECT_EQ(misses, 7);
}

TEST(CacheTest, TEST9)
{
    LFU_cache_t<int, int> cache {3};
    std::vector<int> data = {1, 2, 3, 1, 2, 3, 4, 4, 4};

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
    EXPECT_EQ(misses, 4);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
