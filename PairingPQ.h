// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>
#include <queue>
using namespace std;

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
            // to initialize it here.
            explicit Node(const TYPE &val)
                : elt{ val }, child{ nullptr }, sibling{ nullptr }, previous{nullptr}
            {}

            // Description: Allows access to the element at that Node's
            // position.  There are two versions, getElt() and a dereference
            // operator, use whichever one seems more natural to you.
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
        BaseClass{ comp } , root{nullptr}, numNodes{0} {
        
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, root{nullptr}, numNodes{0} {
        // TODO: Implement this function.
        for (auto iterator = start; iterator != end; iterator++){
            push(*iterator);
        }
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare } , root{nullptr}, numNodes{0} {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
        deque<Node*> copyDeque;
        if (other.root){
            copyDeque.push_back(other.root);
  
        }
        while(!copyDeque.empty()){
            Node* current = copyDeque.front();
            if(current->child){
                copyDeque.push_back(current->child);
            }
            if(current->sibling){
                copyDeque.push_back(current->sibling);
            }
            push(current->elt);
            copyDeque.pop_front();
        }
       
            
        }
     // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        // TODO: Implement this function.
        // HINT: Use the copy-swap method from the "Arrays and Containers"
        // lecture.
        if(this != &rhs){
           copyFunc(rhs);
        }
            return *this;
        
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
       deque<Node*> deleteDeque;
       if(!empty()){
        deleteDeque.push_back(root);
       }
      while(!deleteDeque.empty()){
        Node* current = deleteDeque.front();
        if(current->sibling){
            deleteDeque.push_back(current->sibling);
        }
         if(current->child){
            deleteDeque.push_back(current->child);
        }
        deleteDeque.pop_front();
        delete current;
        }

  
 } // ~PairingPQ()
    


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant.  You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
       deque<Node*> nodeDeque;


        //if pairing heap is not empty, then push back the root
        if(!empty()){
            nodeDeque.push_back(root);
            root = nullptr;
        }
       while(!nodeDeque.empty()){
        Node* current = nodeDeque.front();

        current->previous = nullptr;
           if(current->sibling){
            nodeDeque.push_back(current->sibling);
            current->sibling = nullptr;
        }
        if(current->child){
            nodeDeque.push_back(current->child);
            // for meld
            current->child = nullptr;
        }

        if(root == nullptr){
          root = current;
        }
        else{
            root = meld(current, root);
        }


        nodeDeque.pop_front();
       }
    }
    // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely
    //              in the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);

    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the pairing heap is empty. Though you are welcome to
    // if you are familiar with them, you do not need to use exceptions in
    // this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
    
    Node* popElement = root->child;
    delete root;
    root = nullptr;
    numNodes--;
    if(popElement == nullptr){
        return;
    }
    deque<Node*> popDeque;
    for(Node* i = popElement; i != nullptr; i = i->sibling){
        popDeque.push_back(i);     
    }

    while(popDeque.size() != 1){
        Node* a = popDeque.front();
        popDeque.pop_front();
        //break connections
      a->previous = nullptr;
      a->sibling = nullptr;
      Node* b = popDeque.front();
  
        popDeque.pop_front();
        a->previous = nullptr;
        a->sibling = nullptr;
        popDeque.push_back(meld(a, b));

        //pop twice bc nodeDeque.front() + 1
    
       }

       root = popDeque.front();       

    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function
        return root->elt;
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function
      return numNodes;
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // T
  if(numNodes == 0){
    return true;
  }
  else{
    return false;
  }
    } // empty()


    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value.  Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //              extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE &new_value) {
        //have to change the value
        
        node->elt = new_value;
      if(node->previous == nullptr){
            return;
        }
        //if node is  leftmost
        if(node->previous->child != node){
            //sets new root child to node's sibling
             node->previous->child = node->sibling;
             node->sibling->previous = node->previous;
             
        }
        else{
             node->previous->child = node->sibling;
        }
        //if node has a sibling, reset the pointers next to it
        if(node->sibling != nullptr){
            node->sibling->previous = node->previous; 
            // make sure node has no connections for meld
            node->sibling = nullptr;
        }

        node->previous = nullptr;
        root = meld(node, root);

    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // Runtime: O(1)
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    Node* addNode(const TYPE &val) {
        // TODO: Implement this function 
      Node* newNode = new Node(val);

    if(root == nullptr){
        root = newNode;
    }
    else{
        root =  meld(root, newNode);// Delete this line when you implement this function // TODO: Delete or change this line
     }
        numNodes++;
      return newNode;
      
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you
    // require here.
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap
    // papers).

    // keep track of Nodes in node deque?
    // 
    // nodes cannot have parents or prev, or sibling

    void copyFunc(PairingPQ rhs){
        swap(numNodes, rhs.numNodes);
        swap(root, rhs.root);
    }

    Node* meld(Node* a, Node* b){
        if(this->compare(a->elt, b->elt)){
            if(b->child != nullptr){
                a->sibling = b->child;
                b->child->previous = a;
            }

            a->previous = b;
            b->child = a;
            return b;
        }

        else {
            if(a->child != nullptr){
                b->sibling = a->child;
                a->child->previous = b;
            }
            b->previous = a;
            a->child = b;
            return a;    
            
        }
        //return pointer to the bigger node
        //TEMP

    }
    
    Node* root;
    size_t numNodes = 0;
    
    // NOTE: For member variables, you are only allowed to add a "root
    //       pointer" and a "count" of the number of nodes. Anything else
    //       (such as a deque) should be declared inside of member functions
    //       as needed.
};


#endif // PAIRINGPQ_H
