#include <gtest/gtest.h>
#include "../app/percolation.h"

TEST(Percolation, init) {
    Percolation perc(3);
    ASSERT_FALSE(perc.percolates());
}

TEST(Percolation, trivial) {
    Percolation perc(1);
    perc.open(1, 1);
    ASSERT_TRUE(perc.percolates());
}

TEST(Percolation, size2) {
    Percolation perc(2);
    perc.open(1, 1);
    ASSERT_FALSE(perc.percolates());
    perc.open(2, 2);
    ASSERT_FALSE(perc.percolates());
    perc.open(1, 2);
    ASSERT_TRUE(perc.percolates());
}

TEST(Percolation, size3) {
    Percolation perc(3);
    ASSERT_FALSE(perc.percolates());
    perc.open(1, 1);
    perc.open(1, 2);
    ASSERT_FALSE(perc.percolates());
    perc.open(2, 1);
    ASSERT_FALSE(perc.percolates());
    perc.open(3, 2);
    perc.open(3, 3);
    ASSERT_FALSE(perc.percolates());
    perc.open(2, 2);
    ASSERT_TRUE(perc.percolates());
}

TEST(Percolation, size6) {
    Percolation perc(6);
    ASSERT_FALSE(perc.percolates());
    perc.open(1, 6);
    perc.open(2, 6);
    perc.open(3, 6);
    ASSERT_FALSE(perc.percolates());
    perc.open(3, 5);
    perc.open(3, 4);
    perc.open(2, 4);
    perc.open(2, 3);
    perc.open(2, 2);
    ASSERT_FALSE(perc.percolates());
    perc.open(3, 2);
    perc.open(4, 2);
    perc.open(5, 2);
    ASSERT_FALSE(perc.percolates());
    perc.open(5, 3);
    perc.open(5, 4);
    perc.open(5, 5);
    ASSERT_FALSE(perc.percolates());
    perc.open(6, 5);
    ASSERT_TRUE(perc.percolates());
}

