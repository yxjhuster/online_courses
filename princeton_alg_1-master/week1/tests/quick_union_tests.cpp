#include <gtest/gtest.h>
#include "../app/quick_union.h"

TEST(QuickUnion, init) {
    unsigned size = 10;
    QuickUnion un(size);

    // each element is connected with itself
    for(unsigned i = 0; i < size; i++) 
        ASSERT_TRUE(un.connected(i, i));
    
    // elements not connected with each other
    for(unsigned i = 0; i < size - 1; i++)
        for(unsigned j = i + 1; j < size; j++)
            ASSERT_FALSE(un.connected(i,j));
}

TEST(QuickUnion, connectivity) {
    QuickUnion un(10);
    un.link(0, 1);
    un.link(2, 3);
    un.link(4, 5);
    ASSERT_TRUE(un.connected(0, 1));
    ASSERT_TRUE(un.connected(2, 3));
    ASSERT_TRUE(un.connected(4, 5));
    ASSERT_FALSE(un.connected(0, 5));
    un.link(1, 2);
    ASSERT_FALSE(un.connected(0, 5));
    ASSERT_TRUE(un.connected(0, 2));
    un.link(2, 4);
    ASSERT_TRUE(un.connected(0, 5));
    ASSERT_FALSE(un.connected(0, 6));
    ASSERT_FALSE(un.connected(0, 9));
    ASSERT_FALSE(un.connected(8, 9));
    un.link(6, 9);
    un.link(7, 8);
    ASSERT_FALSE(un.connected(0, 8));
    ASSERT_FALSE(un.connected(0, 9));
    un.link(6, 4);
    ASSERT_TRUE(un.connected(0, 9));
    ASSERT_FALSE(un.connected(0, 8));
    un.link(5, 7);
    ASSERT_TRUE(un.connected(8, 9));
}

TEST(QuickUnion, invalidArgs) {
    QuickUnion un(10);
    ASSERT_THROW(un.link(14, 4), std::invalid_argument);
    ASSERT_THROW(un.connected(4, 21), std::invalid_argument);
}

