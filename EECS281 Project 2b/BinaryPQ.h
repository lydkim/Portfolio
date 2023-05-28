// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include "Eecs281PQ.h"

// A specialized version of the priority queue ADT implemented as a binary
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        //Implement this function, or verify that it is already done
    } // BinaryPQ


    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
    BaseClass{ comp }, data{ start, end } {
        //INCLUDED THIS
        updatePriorities();
        //Implement this function

    } // BinaryPQ


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~BinaryPQ() {
    } // ~BinaryPQ()


    // Description: Assumes that all elements inside the heap are out of
    //              order and 'rebuilds' the heap by fixing the heap
    //              invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        //bottomUP, fixDown
        //for loop going through each of the nodes, from the back
        //call fixDown on each of those
        for (size_t i = data.size(); i >= 1; i--) {
            fixDown(i);
        }
    } // updatePriorities()


    // Description: Add a new element to the PQ.
    // Runtime: O(log(n))
    virtual void push(const TYPE &val) {
        data.push_back(val);
        fixUp(data.size());
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    //       an element when the PQ is empty. Though you are welcome to if
    //       you are familiar with them, you do not need to use exceptions in
    //       this project.
    // Runtime: O(log(n))
    virtual void pop() {
        getElement(1) = getElement(data.size());
        data.pop_back();
        fixDown(1);
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the PQ. This should be a reference for speed. It MUST
    //              be const because we cannot allow it to be modified, as
    //              that might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        return getElement(1);
    } // top()


    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return data.size();
        //Implement this function. Might be very simple,

    } // size()


    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        //Implement this function. Might be very simple,
        return (data.empty());
    } // empty()
    


private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;
    // NOTE: You are not allowed to add any member variables. You don't need
    //       a "heapSize", since you can call your own size() member
    //       function, or check data.size().

    // TODO: Add any additional member functions you require here. For
    //       instance, you might add fixUp() and fixDown().
    void fixUp(std::size_t i) {
        while (i > 1 && this->compare(getElement(i/2), getElement(i))) {
            std::swap(getElement(i), getElement(i/2));
            i/= 2;
        }
    }
    
    void fixDown(std::size_t i) {
        //the notes subtract 1 from the data size***************************************************************
        while (2 * i <= data.size()) {
            size_t j = 2 * i;
            if (j < data.size() && this->compare(getElement(j), getElement(j + 1))) {
                ++j;
            }
            //if(this->compare(getElement(j), getElement(i))) {
            if (!this->compare(getElement(i), getElement(j))) {
                break;
            }
            std::swap(getElement(i), getElement(j));
            i = j;
        } //while loop
    }
    
    // Translate 1-based indexing into a 0-based vector
    TYPE &getElement(std::size_t i) {
        return data[i - 1];
    }  // getElement()

    const TYPE &getElement(std::size_t i) const {
        return data[i - 1];
    }  // getElement()
    
}; // BinaryPQ


#endif // BINARYPQ_H
