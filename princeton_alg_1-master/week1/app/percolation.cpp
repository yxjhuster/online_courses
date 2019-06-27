#include <stdexcept>
#include <iostream>
#include <stdlib.h>     
#include <time.h>      

#include "percolation.h"

Percolation::Percolation(int N)
    : m_union(N * N + 2)
    , m_N(N) {
    m_top = m_N * m_N;
    m_boottom = m_top + 1;
    m_site.resize(N * N, 0);
}

bool Percolation::isInvalid(int i) {
    return i < 1 || i > m_N;
}

bool Percolation::isOpen(int i, int j) {
    if(isInvalid(i) || isInvalid(j)) 
        throw std::invalid_argument("Percolation::isOpen(): arguments are out of range");
    return m_site[translate(i, j)] != 0;
}
    
unsigned Percolation::translate(int row, int col) {
    return (row - 1) * m_N + col - 1;
}

// connect two given sites if both are open
void Percolation::link(unsigned p, unsigned q) {
    bool p_ok = (p == m_top) || (p == m_boottom) || m_site[p];
    bool q_ok = (q == m_top) || (q == m_boottom) || m_site[q];
    if(p_ok && q_ok)
        m_union.link(p, q);
}

void Percolation::open(int i, int j) {
    if(isInvalid(i) || isInvalid(j)) 
        throw std::invalid_argument("Percolation::open(): arguments are out of range");
    // open given site
    unsigned current = translate(i, j);
    m_site[current] = 1;
    // connect newly open site with all open neighborhood
    unsigned neighbour_top = (i == 1) ? m_top : translate(i - 1, j);
    unsigned neighbour_bottom = (i == m_N) ? m_boottom : translate(i + 1, j);
    link(current, neighbour_top);
    link(current, neighbour_bottom);
    if(j > 1)
        link(current, translate(i, j -1));
    if(j < m_N)
        link(current, translate(i, j + 1));
}

bool Percolation::percolates() {
    return m_union.connected(m_top, m_boottom);
}

PercolationStats::PercolationStats(int N, int T) 
    : m_mean(0) {
    for(unsigned i = 0; i < T; i++) {
        m_mean += performTest(N);
    }
    m_mean = m_mean / T;
}

double PercolationStats::performTest(int N) {
    Percolation perc(N);
    unsigned opened = 0;
    while(!perc.percolates()) {
        int i = rand() % N + 1;
        int j = rand() % N + 1;
        perc.open(i, j);
        opened++;
    }
    return ((double)opened) / (N * N);
}

double PercolationStats::mean() {
    return m_mean;
}

double PercolationStats::stddev() {
    // TODO 
    return 0;
}

double PercolationStats::confidenceLo() {
    // TODO 
    return 0;
}

double PercolationStats::confidenceHi() {
    // TODO 
    return 0;
}
