#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

#include <deque>

using namespace std;

template<typename T>
class MinPriorityQueue {
    #define LEFT(i) 2*i
    #define RIGHT(i) 2*i + 1
    #define PARENT(i) i/2
  public:
    MinPriorityQueue() {
        q_.clear();
        q_.push_back(T());
        n_elements_ = 0;
    }
    void Insert(const T& element) {
        q_.push_back(element);
        ++n_elements_;
        // Index of the newly inserted element is equal to the
        // number of elements since q_[0] isn't used.
        PercolateUp(n_elements_);
    }
    // The 'hole' moves up
    void PercolateUp(int index) {
        T element = q_[index];
        while (element < q_[PARENT(index)]) {
            q_[index] = q_[PARENT(index)];
            index = PARENT(index);
        }
        q_[index] = element;
    }
    // The 'hole' moves down (and is then popped)
    void PercolateDown(int index) {
        T element = q_[index];
        while (LEFT(index) <= n_elements_) {
            int child_index = LEFT(index);
            if (RIGHT(index) <= n_elements_ && q_[child_index] > q_[RIGHT(index)]) {
                child_index = RIGHT(index);
            }
            if (element > q_[child_index]) {
                q_[index] = q_[child_index];
                index = child_index;
            } else {
                break;
            }
        }
        q_[index] = element;
    }
    T ExtractMin() {
        if (n_elements_ == 0) return T();
        T min = q_[1];
        q_[1] = q_[n_elements_];
        q_.pop_back();
        --n_elements_;
        if (n_elements_ > 1) {
            PercolateDown(1);
        }
        return min;
    }
    int GetLength() { return n_elements_; }
    T& at(int index) {
        if (index >= n_elements_) {
            //printf("Error! %d >= %d\n", index, n_elements_);
            return q_[0];
        }
        return q_[index+1];
    }
  private:
    deque<T> q_;
    int n_elements_;
    #undef LEFT
    #undef RIGHT
    #undef PARENT
};

#endif // MINPRIORITYQUEUE_H
