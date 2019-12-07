# Data Structures and Algorithms In C++

Implementations of **data structures** and **algorithms** using **C++** by *Junkang Huang*.


### pTime
A simple tool using `std::chrono` to measure how long a program runs. And you can set multiple checkpoints conveniently in a program.

### myPrint
Print vector in various mode to given ostream object.

### mySwap
Swap two elements in a vector.


### myList
Class template implementation of linked list. 
But you cannot use iterator here. Use pointer to `myList<T>::node` instead.
Pay special attention to friend declaration and class template.

### myStack
Use `std::vector` to implement stack data structure.
### myQueue
Use `std::vector` would be much too easy. Instead, I use circular fundamental array to implement queue.


### myBinaryTreeNode
General binary tree node structure, with only copy and move constructors (no default constructor)

### infix2postfix
A function to convert an infix expression to postfix expression

### myExpressionTree
Expression Tree Implementation:
Using `myBinaryTreeNode` template and use `std::string` to instantiate it
In expression tree, leaf node contain operand strings and non-leaf node contain operators (in string).
Expression public routines include three expression notation: *prefix*, *infix*, *postfix*
By now, only support binary operators: +, -, *, /

### myBST
Binary search tree(BST) implementation, containing an inner node structure.

### myAVLTree
AVL Tree, a balanced type of binary search tree. With height recorded in each node and an additional balance routine.
Balance routine include single rotation and double rotation, which is critical for AVL tree.

### mySplayTree
Splay tree, from top down implementation. None recursive element reference.

### myTreeEvaluator
A test routine to evaluate performance of a tree template.
Template should support int type element, and tolerate repeat insertion.

### myBubbleSort
Bubble sort implementation.


### Selection Problem

**Input:** 	N numbers (not sorted)

**Output:** 	the k-th largest number  of input 
Using `std::priority_queue`.

### myBraceChecker
A simple tools to check brace balance of a file. 
Using `std::stack`.

### myPostfixCalculator
Using `std::stack` to calculate a postfix expression which is inputed as a std::string.
### myCalculator
Using `std::stack` to translate a infix expression into corresponding postfix expression.
Then using `myPostfixCalculator()` to calculate the result.