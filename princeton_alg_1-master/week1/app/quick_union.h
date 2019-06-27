#pragma once

#include <vector>

class QuickUnion {
public:
    QuickUnion(unsigned size);
    void link(unsigned, unsigned);
    bool connected(unsigned, unsigned);

private:
    typedef std::vector<unsigned> IntArray;
    IntArray m_roots;
    IntArray m_sizes;

    unsigned getRoot(unsigned) const;
};
