// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure
            //       to initialize it here.
            explicit Node(const TYPE &val)
        : elt{ val }, child{ nullptr }, sibling{ nullptr }, previous { nullptr }
            {}

            // Description: Allows access to the element at that Node's
            //              position. There are two versions, getElt() and a
            //              dereference operator, use whichever one seems
            //              more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data
            // members of this Node class from within the PairingPQ class.
            // (ie: myNode.elt is a legal statement in PairingPQ's add_node()
            // function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            Node *previous;
            // TODO: Add one extra pointer (parent or previous) as desired.
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.

            while (start != end) {
                push(*start);
                ++start;
            }

    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare } {
            std::deque<Node*> dq;
            dq.push_back(other.root);
            Node* current;
            
            while (!dq.empty()){
                current = dq.back();
                dq.pop_back();
                
                if (current->sibling != nullptr){
                    dq.push_back(current->sibling);
                }
                if (current->child != nullptr){
                    dq.push_back(current->child);
                }
                
                push(current->elt);
            } //while
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        // TODO: Implement this function.
        PairingPQ temp(rhs);
        std::swap(root, temp.root);
        std::swap(count, temp.count);
        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        // TODO: Implement this function.
        std::deque<Node*> dq;
        dq.push_back(root);
        Node* temp;
        
        if (count != 0) {
            while (!dq.empty()) {
                temp = dq.back();
                dq.pop_back();
                if (temp->sibling != nullptr) {
                    dq.push_back(temp->sibling);
                } //if statement
                if (temp->child != nullptr) {
                    dq.push_back(temp->child);
                } //second if statement
                delete temp;
            } //while loop
        } //if statement
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant. You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        std::deque<Node*> dq;
        dq.push_back(root);
        root =  nullptr;
        Node* temp;

        while (!dq.empty()){
            temp = dq.back();
            dq.pop_back();
            if (temp->sibling != nullptr){
                dq.push_back(temp->sibling);
            } //if statement
            if (temp->child != nullptr){
                dq.push_back(temp->child);
            } //second if statement
            temp->previous = nullptr;
            temp->sibling = nullptr;
            temp->child = nullptr;
            root = meld(root, temp);
        } //while loop
    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely in
    //              the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    //       an element when the pairing heap is empty. Though you are
    //       welcome to if you are familiar with them, you do not need to use
    //       exceptions in this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        // TODO: Implement this function.
        if (count == 1) {
            delete root;
            root = nullptr;
            count--;
        } //if statement
        else {
            Node* temp = root->child;
            temp->previous = nullptr;
            delete root;
            
            std::deque<Node*> dq;
            dq.push_back(temp);
            while (temp->sibling != nullptr) {
                dq.push_back(temp->sibling);
                temp = temp->sibling;
            } //while loop
            
            while (dq.size() != 1) {
                Node* first = dq.front();
                dq.pop_front();
                first->previous = nullptr;
                first->sibling = nullptr;
                
                Node* second = dq.front();
                dq.pop_front();
                second->previous = nullptr;
                second->sibling = nullptr;
                
                dq.push_back(meld(first, second));
            } //second while loop
            root = dq.front();
            count--;
        } //else statement
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function
        static TYPE temp;
        temp = root->elt;
        return temp;
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return count;
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        if (count == 0) {
            return true;
        }
        return false;
    } // empty()


    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value. Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //               extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE &new_value) {
        // TODO: Implement this function
        node->elt = new_value;
        
        //left
        if (node->previous->child == node){
            if (node->sibling != nullptr){
                node->sibling->previous = node->previous;
            }
            
            node->previous->child = node->sibling;
            node->sibling = nullptr;
            node->previous = nullptr;
            root = meld(root, node);
        }
        else{
            if (node->sibling != nullptr){
                //middle
                node->previous->sibling = node->sibling;
                node->sibling->previous = node->previous;
                
                node->sibling = nullptr;
                node->previous = nullptr;
            }
            
            else{
                //right
                node->previous->sibling = nullptr;
                node->previous = nullptr;
            }
            root = meld(root, node);
        }

    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    // Runtime: O(1)
    Node* addNode(const TYPE &val) {
        // TODO: Implement this function
        Node* temp = new Node(val);
        root = meld(root, temp);
        count++;
        return temp;
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you
    //       require here.
    Node* root;
    size_t count = 0;
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap
    Node * meld(Node* a, Node* b) {
        if (count == 0) {
            root = b;
            return b;
        } //if
        else if (a == nullptr) {
            root = b;
            return b;
        } //else if
        else {
            if (this->compare (a->elt, b->elt)) {
                if (b->child != nullptr){
                    b->child->previous = a;
                    a->sibling = b->child;
                    b->child = a;
                    a->previous = b;
                    return b;
                } //if
                else{
                    b->child = a;
                    a->previous = b;
                    return b;
                    
                } //else
            } //if statement
            else{
                if (a->child != nullptr){
                    a->child->previous = b;
                    b->sibling = a->child;
                    a->child = b;
                    b->previous = a;
                    return a;
                }
                else{
                    a->child = b;
                    b->previous = a;
                    return a;
                }
            }
            
        } //else
    }
};


#endif // PAIRINGPQ_H
