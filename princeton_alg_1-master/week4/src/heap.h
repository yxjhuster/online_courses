#include <iostream>
#include <vector>
#include <stdexcept>

namespace my {

    template<typename T>
    class MaxHeap {
    public:
        MaxHeap(size_t capacity = 8);
        // insert item to heap
        void insert(const T&);
        // get number of items in heap
        size_t getSize() const;
        // get max element in heap
        const T& getMax();
        // pop max element from the heap
        void popMax();

    private:

        // current capacity of buffer
        size_t m_capacity;
        // buffer for storing heap data
        std::vector<T> m_buff;
        // index of item next to the last one
        size_t lastIndex;

        // helper functions
        void sink(size_t idx);
        void swimUp(size_t idx);
        void resize(bool);
        size_t getMaxChild(size_t idx);
    };


    template<typename T>
    MaxHeap<T>::MaxHeap(size_t capacity)
        : lastIndex(1)
        , m_capacity(capacity) {
        m_buff.resize(m_capacity + 1);
    }

    template<typename T>
    void MaxHeap<T>::insert(const T& val) {
        if(m_buff.size() - 1 == lastIndex)
            resize(true);
        m_buff[lastIndex] = val;
        swimUp(lastIndex);
        ++lastIndex;
    }

    template<typename T>
    size_t MaxHeap<T>::getSize() const {
        return lastIndex - 1;
    }

    template<typename T>
    const T& MaxHeap<T>::getMax() {
        if(getSize() == 0)
            throw std::out_of_range("can't get max from empty heap");
        return m_buff[1];
    }

    template<typename T>
    void MaxHeap<T>::popMax() {
        if(getSize() == 0)
            throw std::out_of_range("can't pop from empty heap");
        std::swap(m_buff[1], m_buff[lastIndex - 1]);
        --lastIndex;
        sink(1);

        if(lastIndex < m_buff.size() / 4)
            resize(false);
    }

    template<typename T>
    void MaxHeap<T>::sink(size_t idx) {
        size_t childMax = getMaxChild(idx);
        if(childMax && m_buff[idx] < m_buff[childMax]) {
            std::swap(m_buff[idx], m_buff[childMax]);
            sink(childMax);
        }
    }

    template<typename T>
    size_t MaxHeap<T>::getMaxChild(size_t idx) {
        size_t child1 = idx * 2 >= lastIndex     ? 0 : idx * 2;
        size_t child2 = idx * 2 + 1 >= lastIndex ? 0 : idx * 2 + 1;

        if(child1 == 0 && child2 == 0) return 0;
        else if(child1 == 0) return child2;
        else if(child2 == 0) return child1;
        else return m_buff[child1] >= m_buff[child2] ? child1 : child2;
    }

    template<typename T>
    void MaxHeap<T>::swimUp(size_t idx) {
        size_t parent = idx / 2;
        if(parent && m_buff[parent] < m_buff[idx]) {
            std::swap(m_buff[parent], m_buff[idx]);
            swimUp(parent);
        }
    }

    template<typename T>
    void MaxHeap<T>::resize(bool up) {
        size_t newSize = up ? m_buff.size() * 2 : m_buff.size() / 2;
        std::vector<T> tmp(newSize);
        std::copy(m_buff.begin() + 1, m_buff.begin() + lastIndex, tmp.begin());
        m_buff.swap(tmp);
    }

}

