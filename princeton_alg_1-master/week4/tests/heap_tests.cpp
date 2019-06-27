#include <gtest/gtest.h>
#include "../src/heap.h"

TEST(Heap, basic) {
    my::MaxHeap<int> heap(5);
    heap.insert(3);
    heap.insert(2);
    heap.insert(8);
    heap.insert(-2);
    heap.insert(6);
    ASSERT_TRUE(heap.getMax() == 8);
    heap.popMax();
    ASSERT_TRUE(heap.getMax() == 6);
    heap.popMax();
    heap.insert(12);
    ASSERT_TRUE(heap.getMax() == 12);
    heap.insert(8);
    heap.insert(9);
    heap.insert(5);
    heap.insert(7);
    ASSERT_TRUE(heap.getMax() == 12);
    ASSERT_TRUE(heap.getSize() == 8);
}

