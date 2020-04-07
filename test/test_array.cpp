#include "gtest/gtest.h"
#include <engine/array.h>

namespace neko{

TEST(Array, MemoryLayout){
    const size_t ALLOCATOR_HEADER_SIZE = 16;
    const size_t SIZE = 64;
    void* start = malloc(SIZE + ALLOCATOR_HEADER_SIZE);

    FreeListAllocator allocator(SIZE + ALLOCATOR_HEADER_SIZE, start);
    DynArray<char> array(allocator);

    for (int i = 0; i < SIZE; ++i)
    {
        array.Push('a');
    }

    // TODO: Oleg@Guillume: clean up from uint64_t to ptr types for test to work.
    std::uint64_t expectedEnd = (std::uint64_t)start + (std::uint64_t)SIZE + (std::uint64_t)ALLOCATOR_HEADER_SIZE;
    DynArray<char>::iterator actualEnd = array.end();
    EXPECT_EQ(expectedEnd, actualEnd);
}

TEST(Array, Iterators){
    // TODO

    // std::find_if(arra.begin(), arra.end(). []{})
}

}// !neko