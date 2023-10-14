// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include "Eecs281PQ.h"
#include <vector>
#include <queue>
#include <deque>
using namespace std;

// A specialized version of the priority queue ADT implemented as a binary heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {

            data.push_back(TYPE{});
        // TODO: Implement this function, or verify that it is already done
    } // BinaryPQ


    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
       BaseClass{ comp }  {
        // TODO: Implement this function
        data.push_back(TYPE{});
        data.insert(data.end(), start, end);
        updatePriorities();
    } // BinaryPQ


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~BinaryPQ() {
    } // ~BinaryPQ()


    // Description: Assumes that all elements inside the heap are out of order and
    //              'rebuilds' the heap by fixing the heap invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
    int size = static_cast<int>(data.size());
    //    for(size_t i = 0; i < data.size() - 1; i++){
    //     //this->compare(data[getelement(i / 2), data[getelement()]])
    //     if(!(this->compare(getElement(i / 2), getElement(i))) && i != 1){
    //         //if index jhas no children
    //     }
    //         //if index has children
        
    //         else if((i * 2) <= (data.size())){
    //             //fix down from the parent node
    //             fixDown(data, size, static_cast<int>(i / 2));
    //         }
        
    // }
    for(size_t i = data.size() / 2; i > 0; i--){
        fixDown(size, static_cast<int>(i));
    }
} // updatePriorities()


    // Description: Add a new element to the PQ.
    // Runtime: O(log(n))
    virtual void push(const TYPE &val) {
        // TODO: Implement this function
        
       data.push_back(val);
       int numSize = static_cast<int>(data.size());
        fixUp(numSize);
      // Delete this line when you implement this function
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the PQ is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: O(log(n))
    virtual void pop() {
        if(data.empty()){
            return;
        }
        getElement(1) = data.back();
        data.pop_back();
        int numSize = static_cast<int>(data.size() - 1);
        fixDown(numSize, 1);
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the PQ. This should be a reference for speed. It MUST
    //              be const because we cannot allow it to be modified, as
    //              that might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function.

        // These lines are present only so that this provided file compiles.
        return getElement(1);
    } // top()


    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function. Might be very simple,
        // depending on your implementation.
    return data.size() - 1;
    } // size()


    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function. Might be very simple,
        // depending on your implementation.
    //   return data.empty();
      if(data.size() == 1){
        return true;
      }
      else{
        return false;
      }
    } // empty()


private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;
    // NOTE: You are not allowed to add any member variables. You don't need
    //       a "heapSize", since you can call your own size() member
    //       function, or check data.size().

    // Translate 1-based indexing into a 0-based vector
    TYPE &getElement(std::size_t i) {
      return data[i - 1];
    }  // getElement()

    const TYPE &getElement(std::size_t i) const {
      return data[i - 1];
    }  // getElement()


    void fixUp(int index){
     
        while(index > 1 && this->compare(getElement(index / 2) , getElement(index))){
            swap(getElement(index), getElement(index/2));
            index /= 2;
        }
    }
    void fixDown(int heapSize, int index){
        while(2 * index <= heapSize) {
            int j = 2 * index;
            if(j < heapSize && this->compare(getElement(j) , getElement(j + 1))){
                ++j;
            }//data[index] >= data[j]){
            if(!this->compare(getElement(index), getElement(j))){
                break;
              }       
            swap(getElement(index), getElement(j));
            index = j;
        }
    }
    // TODO: Add any additional member functions you require here.
    //       For instance, you might add fixUp() and fixDown().
}; // BinaryPQ


#endif // BINARYPQ_H
