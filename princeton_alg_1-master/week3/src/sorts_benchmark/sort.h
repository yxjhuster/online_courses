#include <vector>
#include <list>
#include <iterator>
#include <algorithm>

namespace my {

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // insertion sort algorithm:
    // O(N^2) running time
    // not stable 
    // O(1) extra memory
    template <typename RandomAccessIterator>
    void insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
       if(first >= last)
           return;
       // maintain loop invariant - at each iteration all elements before 'current' iterator are sorted
       for(RandomAccessIterator current = first + 1; current != last; ++current) {
           RandomAccessIterator lastSorted = current - 1;
           // determine position where 'current' element must be inserted
           RandomAccessIterator insertPos = current;
           while(*(insertPos - 1) > *current && insertPos > first)
               --insertPos;
           // make room for element to be inserted
           typename RandomAccessIterator::value_type tmpVal = *current;
           for(RandomAccessIterator mv = current; mv >= insertPos; --mv) {
               *mv = *(mv - 1);
           }
           // insert element
           *insertPos = tmpVal;
       }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // merge sort algorithm (recursive):
    // O(N * lgN) running time
    // stable 
    // O(N) extra memory

    template <typename T>
    using BufferType = std::vector<T>;

    template <typename RandomAccessIterator, typename ValueType>
    void merge_rec(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, BufferType<ValueType>& mergeBuff) {
        auto itLeft = first;
        auto itRight = middle;
        auto itMerged = mergeBuff.begin();
        for(auto i = 0; i < last - first; ++i) {
            if(itRight == last)
                *itMerged = *(itLeft++);
            else if(itLeft == middle)
                *itMerged = *(itRight++);
            else if(*itLeft <= *itRight)
                *itMerged = *(itLeft++);
            else 
                *itMerged = *(itRight++);
            ++itMerged;
        }
        std::copy(mergeBuff.begin(), itMerged, first);
    }

    template <typename RandomAccessIterator, typename ValueType>
    void sort_helper(RandomAccessIterator first, RandomAccessIterator last, BufferType<ValueType>& mergeBuff) {
        auto problemSize = std::distance(first, last);
        if(problemSize < 7) {
            insertion_sort(first, last);
            return;
        }
        RandomAccessIterator middle = first + problemSize / 2;
        sort_helper(first, middle, mergeBuff);
        sort_helper(middle, last, mergeBuff);
        merge_rec(first, middle, last, mergeBuff);
    }

    template <typename RandomAccessIterator>
    void merge_sort_recursive(RandomAccessIterator first, RandomAccessIterator last) {
        if(first >= last)
            return;
        auto buffSize = last - first;
        // buffer we use to merge to sorted arrays
        BufferType<typename RandomAccessIterator::value_type> mergeBuff(buffSize);
        sort_helper(first, last, mergeBuff);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // quick sort algorithm
    // O(N * lgN) average running time, O(N^2) worst case
    // not stable 
    // O(1) extra memory
    template <typename RandomAccessIterator>
    RandomAccessIterator quick_partition(RandomAccessIterator first, RandomAccessIterator last) {
        if(first >= last)
            return first;
                
        // select pivot element and move it to the end of the array
        auto problemSize = std::distance(first, last);
        RandomAccessIterator pivot = first + std::rand() % problemSize;
        std::swap(*pivot, *(last - 1));

        int lessEqualIndex = 0;
        int biggerIndex = 0;
        const auto& pivotVal = *(last - 1);
        for(RandomAccessIterator curr = first; curr != (last - 1); ++curr) {
            if(*curr > pivotVal)
                ++biggerIndex;
            else {
                // swap first element that bigger than pivot with `curr`
                std::swap(*(first + lessEqualIndex), *curr);
                ++lessEqualIndex;
                ++biggerIndex;
            }
        }

        std::swap(*(last - 1), *(first + lessEqualIndex));
        return first + lessEqualIndex;
    }

    template <typename RandomAccessIterator>
    void quick_sort(RandomAccessIterator first, RandomAccessIterator last) {
        if(last - first <= 1)
            return;
        RandomAccessIterator pivot = quick_partition(first, last);
        quick_sort(first, pivot);
        quick_sort(pivot, last);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // bottom-up merge sort algorithm (non recursive)
    // O(N * lgN) worst case
    // stable 
    // O(N) extra memory

    template <typename RandomAccessIter, typename T>
    void merge_btm(RandomAccessIter first, RandomAccessIter mid, RandomAccessIter last, std::vector<T>& merge_buff) {
        if (last - first == 1)
            return;

        std::copy(first, last, merge_buff.begin());
        RandomAccessIter mrg_first = merge_buff.begin();
        RandomAccessIter mrg_last = mrg_first + (last - first);
        RandomAccessIter mrg_mid = mrg_first + (mid - first);
        
        RandomAccessIter mrg_l = mrg_first;
        RandomAccessIter mrg_r = mrg_mid;
        for (RandomAccessIter curr = first; curr != last; ++curr) {
            if (mrg_l == mrg_mid) 
                *curr = *mrg_r++;
            else if (mrg_r == mrg_last) 
                *curr = *mrg_l++;
            else {
                if(*mrg_l <= *mrg_r) 
                    *curr = *mrg_l++;
                else
                    *curr = *mrg_r++;
            }
        }
    }

    int div_ceil(int x, int y) {
        return x / y + (x % y ? 1 : 0);
    }

    template <typename RandomAccessIter>
    void bottom_up_mergesort(RandomAccessIter first, RandomAccessIter last) {
        unsigned N = last - first;
        std::vector<typename RandomAccessIter::value_type> merge_buff(N);

        unsigned task_size = 2;
        while (true) {
            auto task_count = div_ceil(N, task_size);
            for (auto i = 0; i < task_count; i++ ) {
                auto task_first = first + (i * task_size);
                unsigned elems_left = last - task_first;
                auto task_mid = elems_left >= task_size / 2
                    ? task_first + task_size / 2
                    : task_first + elems_left;
                elems_left = last - task_mid;
                auto task_last = elems_left >= task_size / 2
                    ? task_mid + task_size / 2
                    : task_mid + elems_left;
                merge_btm(task_first, task_mid, task_last, merge_buff);
            }
            if (task_size >= N)
                break;
            task_size *= 2;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // bottom-up merge sort algorithm for linked list-like structures (non recursive)
    // O(N * lgN) worst case
    // stable 
    // O(N) extra memory

    template<typename ForwardIterator>
    void list_merge(ForwardIterator first, ForwardIterator mid, ForwardIterator last, unsigned taskSize) {
        if (last == first)
            return;
        
        // copy data to temp buffer
        std::list<typename ForwardIterator::value_type> buff;
        ForwardIterator buffMid = buff.end();
        for(ForwardIterator it = first; it != last; ++it) {
            buff.push_back(*it);
            if(it == mid) {
                buffMid = buff.end();
                --buffMid;
            }
        }

        // begin merging
        ForwardIterator mrgL = buff.begin();
        ForwardIterator mrgR = buffMid;
        for (ForwardIterator curr = first; curr != last; ++curr) {
            if (mrgL == buffMid) 
                *curr = *mrgR++;
            else if (mrgR == buff.end()) 
                *curr = *mrgL++;
            else {
                if(*mrgL <= *mrgR) 
                    *curr = *mrgL++;
                else
                    *curr = *mrgR++;
            }
        }
    }

    template<typename ForwardIterator>
    void list_mergesort(ForwardIterator first, ForwardIterator last) {
        auto taskSize = 2;
        while(true) {
            ForwardIterator curr = first;
            bool firstTask = true;
            while(curr != last) {
                auto i = 0;
                ForwardIterator taskL = curr;
                ForwardIterator taskM = curr;
                ForwardIterator taskR = curr;
                while(i < taskSize && taskR != last) {
                    ++i;
                    ++taskR;
                    if(firstTask) {
                        if(i <= taskSize / 2)
                            ++taskM;
                    } else {
                        if (i % 2 == 0) 
                            ++taskM;
                    }
                }
                list_merge(taskL, taskM, taskR, taskSize);
                firstTask = false;
                curr = taskR;
                if(taskL == first && taskR == last)
                    return;
            }
            taskSize *= 2;
        }
    }
}

