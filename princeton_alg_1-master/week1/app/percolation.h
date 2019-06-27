#include "quick_union.h"
#include <vector>

class Percolation {
public:
    Percolation(int N);            // create N-by-N grid, with all sites blocked
    void open(int i, int j);       // open site (row i, column j) if it is not open already
    bool isOpen(int i, int j);     // is site (row i, column j) open?
    bool percolates();             // does the system percolate?
private:
    QuickUnion m_union;
    unsigned translate(int row, int col);
    int m_N;
    unsigned m_top;
    unsigned m_boottom;
    std::vector<unsigned> m_site;
    bool isInvalid(int i);
    void link(unsigned, unsigned);

};

class PercolationStats {
    double performTest(int N);
    double m_mean;
public:
    PercolationStats(int N, int T);     // perform T independent experiments on an N-by-N grid
    double mean();                      // sample mean of percolation threshold
    double stddev();                    // sample standard deviation of percolation threshold
    double confidenceLo();              // low  endpoint of 95% confidence interval
    double confidenceHi();              // high endpoint of 95% confidence interval
};
