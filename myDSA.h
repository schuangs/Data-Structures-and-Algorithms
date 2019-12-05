/**
 * This is the header of myDSA.cpp
 * myDSA includes implementations of various data structures and algorithms
 * all of the functions are named with a "my-" prefix for distinguishing.
 * @author Junkang_Huang huangjk8@mail2.sysu.edu.cn
**/

# ifndef MYDSA_H
# define MYDSA_H

# include <vector>
# include <string>
# include <queue>
# include <stack>
# include <map>
# include <ctime>
# include <chrono>
# include <iostream>
# include <fstream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::priority_queue;

//
// -------------------- pTime --------------------
//
// 
//  A routine to count the time cost by a program in milliseconds.
//  Using std::chrono library and std::chrono::steady_clock as clock epoch.
//
//      pTime() to create a new counter.
//      pStart():  Start counting.
//      addPoint():  Add check points at this moment.
//      pEnd():   Stop counting.
//      pDuration():  Return the length of total duration in ms.
//      pDisplay():   Quickly display the counting result.
//
class pTime{
    // alias
    using time_point_t = std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds>;
private:
    // Member variables
    time_point_t start; // Start of counting
    time_point_t end;   // End of counting
    vector<time_point_t> points;    // Checkpoints during counting
    bool counting = false;  // Whether pTime is still running
public:
    // Start couting
    void pStart(){
        points.clear();
        counting = true;
        start = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
        return;
    }
    // Add check points during counting
    void addPoint(){
        if ( counting != true ) {
            std::cerr << "Invalid check point." << endl;
            return;
        }
        points.push_back(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()));
        return;
    }
    // End counting
    void pEnd(){
        counting = false;
        end = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
        return;
    }
    // Return duration between start and end in millisecond.
    int pDuration() const {
        if ( counting == true ){
            cerr << "pTime is still counting !" << endl;
            return 0;
        }
        return (end - start).count();
    }
    // Display counting information
    void pDisplay() const {
        if ( counting == true ){
            cerr << "pTime is still counting !" << endl;
            return;
        }
        // Display checkpoints
        for (auto i = 0; i < points.size(); ++i)
            cout << "# " << i+1 << "    " << (points[i]-start).count() << " ms" << endl;
        // Display total time
        cout << endl << "Running time:     " << (end - start).count() << " ms" << endl;
        return;
    }
};

//
// -------------------- Fundamental --------------------
//

//
// Print:
//  Print a container
//    con                        - the container need to print
//    os                         - ostream object where the container to be print to
//    mode                       - "Normal" : print in one line
//                                 "Vertical" : print one item a line
//

template <typename Container>
void myPrint(const Container &con, std::ostream &os = std::cout, string mode = "Normal"){
    if ( mode == "Normal" ) {
        // "Normal" mode: print in the form as : [ a1, a2, a3, ... ]
        os << "[ ";
        for (auto itr = con.begin(); itr != con.end(); ++itr)
            os << *itr << ", ";
        os << con.back() << " ]" << endl;
    } else if ( mode == "Vertical" ) {
        // "Vertical" mode: print each item at a line
        for (auto itr = con.begin(); itr != con.end(); ++itr)
            os << *itr << endl;
        os << con.back() << endl;
    }
    return;
}

//
// Swap:
//  Swap two elements of a vector
//
template <typename T>
void mySwap (vector<T> &v, int a, int b) {
    if ( a == b ) return;
    if ( a > v.size() || b > v.size() || a < 0 || b < 0 ) {
        cerr << "Error: Invalid index." << endl;
        return;
    }
    std::swap(v[a], v[b]);
    return;
}


//
// -------------------- Linear List --------------------
//

//
//  Linked list implementation:
//   Just one direction. And for briefness, I do not encapsulate node, and it is visible to users.
//   In fact, I could make it more professional if I encapsulate node and create an iterator class for node reference.
//   But that would cost heavier works. Maybe in the future!
//

template <typename T>
class myList {
public:
    // Internal node structure.
    class node {
    public:
        T getValue() const {
            return value;
        }
        void setValue(T val){
            value = val;
        }
        // Read only, which means that you cannot change the next node through this node.
        // The only way that you can change the interconnnection between nodes is through myList functions.
        const node *getNext() const {
            return next;
        }
        // Even node is put inside myList, 
        // if myList want to use the private members, node should still possess a friend claim.
        friend class myList<T>;
    private:
        T value = 0;
        node *next = nullptr;
    };

    // Constructor and destructor
    myList () {
        head = new node;
        tail = new node;
        head -> next = tail;
        listSize = 0;
    }
    // Destructor
    ~myList () {
        clear();
        delete head;
        delete tail;
    }

    // Attention: Lack of copy function, default only shallow copy

    // Get the size
    unsigned size() const {
        return listSize;
    }
    // push and pop
    void push_back(node *ptr){
        insert(tail, ptr);
    }
    void push_front(node *ptr){
        insert(head->next, ptr);
    }
    void pop_back(){
        remove(back());
    }
    void pop_front(){
        remove(head->next);
    }
    // Insert ptr at the position in front of pos
    void insert(node *pos, node *ptr){
        node *last = head;
        while (last->next != pos){
            if (last == tail) {
                cerr << "Insert error: inserting position is not in this list." << endl;
                return;
            }
            last = last->next;
        }
        last->next = ptr;
        ptr->next = pos;
        ++listSize;
    }
    // Remove node
    void remove(node *ptr){
        if (empty()){
            cerr << "Empty list cannot apply remove()." << endl;
            return;
        }
        node *last = head;
        while (last->next != ptr){
            if (last == tail){
                cerr << "Remove error: node is not in this list." << endl;
                return;
            }
            last = last->next;
        }
        last->next = ptr->next;
        delete ptr;
        --listSize;
    }
    // Front and back, editable
    node *back(){
        if (empty()){
            cerr << "Error： cannot apply back() on empty list." << endl;
            return {};
        }
        node *ptr = head;
        while (ptr->next != tail)
            ptr = ptr->next;
        return ptr;
    }
    node *front(){
        if (empty()){
            cerr << "Error： cannot apply front() on empty list." << endl;
            return {};
        }
        return head->next;
    }
    // Front and back, read only
    const node *back() const {
        if (empty()){
            cerr << "Error： cannot apply back() on empty list." << endl;
            return {};
        }
        node *ptr = head;
        while (ptr->next != tail)
            ptr = ptr->next;
        return ptr;
    }
    const node *front() const {
        if (empty()){
            cerr << "Error： cannot apply front() on empty list." << endl;
            return {};
        }
        return head->next;
    }
    bool empty() const {
        return listSize == 0;
    }
    void clear(){
        while (listSize != 0)
            pop_front();
    }
    // Print the list to output
    void print(std::ostream &output) const {
        auto ptr = head->next;
        output << "[";
        while (ptr != tail && ptr->next != tail){
            output << ptr->value << ", ";
            ptr = ptr->next;
        }
        output << ptr->value << "]" << endl;
    }
private:
    // Two sentinel nodes at the begin and end of the list
    node *head;
    node *tail;
    unsigned listSize;
};


//
//  Stack implementation:
//  Use std::vector, and it is pretty easy.
//

template <typename T>
class myStack{
public:
    T top() const {
        if (empty()){
            cerr << "Error: cannot get the top element of empty stack." << endl;
            return {};
        }
        return list.back();
    }
    void pop() {
        if (empty()){
            cerr << "Error: cannot apply pop() on empty stack." << endl;
            return;
        }
        list.pop_back();
    }
    // Left reference input
    void push(const T &elem){
        list.push_back(elem);
    }
    // Right reference input
    void push(T &&elem){
        list.push_back(std::move(elem));
    }
    bool empty() const {
        return list.empty();
    }
    void clear() {
        list.clear();
    }
    unsigned size() const {
        return list.size();
    }
private:
    vector<T> list;
};


//
//  Queue implementation:
//  Use circular array
// 
template <typename T>
class myQueue{
public:
    myQueue():
        capacity(16), listSize(0), start(1), end(0){
        list = new T[INITSIZE];
    }
    ~myQueue(){
        delete list;
    }
    void push(const T &elem){
        if (listSize == capacity - 1)
            resize();
        // Circular
        if (++end == capacity) end = 0;
        list[end] = elem;
        ++listSize;
    }
    void push(T &&elem){
        if (listSize == capacity - 1)
            resize();
        if (++end == capacity) end = 0;
        list[end] = elem;
        ++listSize;
    }
    void pop(){
        if (empty()){
            cerr << "Error: cannot apply pop() on empty queue." << endl;
            return;
        }
        if (++start == capacity) start = 0;
        --listSize;
    }

    // Change the array to new and larger one.
    // That is make capacity larger.
    void resize() {
        T *newList = new T[2*capacity+1];
        unsigned j = 0;
        for (auto i = start; i != end; ++i){
            if (i == capacity) i = 0;
            newList[j++] = list[i];
        }
        newList[j] = list[end];
        capacity = capacity*2 + 1;
        delete list;
        list = newList;
        start = 1;
        end = 0;
    }
    T front() const {
        return list[start];
    }
    T back() const {
        return list[end];
    }
    bool empty() const {
        return listSize == 0;
    }
    void clear() {
        start = 1;
        end = 0;
        listSize = 0;
    }
    unsigned size() const {
        return listSize;
    }
    
private:
    // Initial capacity of real array
    const unsigned INITSIZE = 16;
    T *list;
    // Capacity is the real capacity of the array
    unsigned capacity;
    // listSize is the size of valid data
    unsigned listSize;
    // Start and end mark the start and end position of valid data
    unsigned start;
    unsigned end;
};


//
// -------------------- Tree --------------------
//

//
// Binary tree node structure
//
template <typename T>
struct myBinaryTreeNode {
    T value;
    myBinaryTreeNode *left = nullptr;
    myBinaryTreeNode *right = nullptr;
    // Constructor
    myBinaryTreeNode(const T &val): value(val){}
    myBinaryTreeNode(T &&val): value(std::move(val)){}
};

//
//  Converter from infix to postfix expression
//
std::string infix2Postfix(const string &infix) {
    std::vector<char> operatorList{'+','-','*','/','(',')', ' '};
    std::map<char, unsigned> priority{
        {'(', 100},
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2}
    };
    std::stack<char> s;
    string postfix;
    // Deal with prefix sign '+' and '-'
    size_t i = 0;
    string infixNew{infix};
    while (i < infixNew.size() && infixNew[i] == ' ') ++i;
    if (i >= infixNew.size()) return 0;
    // Sign at the beginning of expression
    if (infixNew[i] == '-' || infixNew[i] == '+')
        infixNew.insert(i, 1,'0');
    while (i < infixNew.size()-1){
        // sign in the middle, '(-' and '(+'
        if (infixNew[i] == '(' && (infixNew[i+1] == '-' || infixNew[i+1] == '+'))
            infixNew.insert(i+1, 1,'0');
        ++i;
    }
    // convert
    for (auto c : infixNew){
        if ( isdigit(c) || c == '.' ){
            postfix.push_back(c);
        } else {
            postfix.push_back(' ');
            if ( c == ' ' ) continue;
            if ( c == ')' ){
                while ( s.top() != '(' ){
                    postfix.push_back(s.top());
                    s.pop();
                }
                s.pop();
            } else {
                while ( !s.empty() && s.top() != '(' && priority[s.top()] >= priority[c] ){
                    postfix.push_back(s.top());
                    s.pop();
                }
                s.push(c);
            }
        }
    }
    while ( !s.empty() ){
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}


//
//  Expression Tree Implementation:
//  Using myBinaryTreeNode template and use std::string to instantiate it
//  In expression tree, leaf node contain operand strings and non-leaf node contain operators (in string).
//  Expression public routines include three expression notation: prefix, infix, postfix
//  By now, only support binary operators: +, -, *, /
//
class myExpressionTree{
public:
    // Destructor
    ~myExpressionTree(){
        clear();
    }

    // Using std::stack to create expression tree
    void readPostfix(const std::string &postfix) {
        std::stack<myBinaryTreeNode<string> *> s;
        // operand : temperarily store operand strings
        std::string operand;
        for (auto c : postfix){
            if (c == ' ' || c == '+' || c == '-' || c == '*' || c == '/'){
                // push operand node to stack
                if (!operand.empty()){
                    myBinaryTreeNode<string> *leaf = new myBinaryTreeNode<string>(operand);
                    s.push(leaf);
                    operand.clear();
                }
                // push operator node to stack
                if (c != ' '){
                    myBinaryTreeNode<string> *node = new myBinaryTreeNode<string>(string() + c);
                    auto right = s.top(); s.pop();
                    auto left = s.top(); s.pop();
                    node->left = left;
                    node->right = right;
                    s.push(node);
                }
            } else {
                // record operand string
                operand.push_back(c);
            }
        }
        root = s.top(); s.pop();
        if (!s.empty()){
            cerr << "Error: Invalid postfix expression." << endl;
            return;
        }
    }
    // Use infix2Postfix to convert infix to postfix, then read postfix
    void readInfix(const std::string &infix) {
        std::string postfix = infix2Postfix(infix);
        readPostfix(postfix);
    }

    // Return three types of expression
    void printInfix(std::ostream &output = std::cout) const {
        printInfix(root, output);
    }
    void printPostfix(std::ostream &output = std::cout) const {
        printPostfix(root, output);
    }
    void printPrefix(std::ostream &output = std::cout) const {
        printPrefix(root, output);
    }

    // clear() and empty()
    void clear() {
        clear(root);
    }
    bool empty() const {
        return root == nullptr;
    }

private:
    // Tree root
    myBinaryTreeNode<string> *root = nullptr;

    // Private real print function, using pointer as first parameter
    void printInfix(myBinaryTreeNode<string> *node, std::ostream &output) const {
        if (node == nullptr) return;
        printInfix(node->left, output);
        output << node->value << " ";
        printInfix(node->right, output);
    }
    void printPostfix(myBinaryTreeNode<string> *node, std::ostream &output) const {
        if (node == nullptr) return;
        printPostfix(node->left, output);
        printPostfix(node->right, output);
        output << node->value << " ";
    }
    void printPrefix(myBinaryTreeNode<string> *node, std::ostream &output) const {
        if (node == nullptr) return;
        output << node->value << " ";
        printPrefix(node->left, output);
        printPrefix(node->right, output);
    }

    // Private real clear function, using pointer as parameter
    // Attention: Here use reference of the pointer to node. So the pointer can be set as nullptr.
    void clear(myBinaryTreeNode<string> *&node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
        // Set pointer to nullptr
        node = nullptr;      
    }
};


//
//  Binary Search Tree (BST):
//  node->values repeat is not allowed
//
template <typename T>
class myBST{
public:
    // Constructors
    myBST() = default;
    // Copy constructor
    myBST(const myBST<T> &rhs){
        root = clone(rhs.root);
    }
    // Move constructor
    myBST(myBST<T> &&rhs){
        root = rhs.root;
    }
    // Destructor
    ~myBST(){
        clear(root);
    }

    // Get the minimum and maximum value
    T min() const {
        return min(root);
    }
    T max() const {
        return max(root);
    }
    // Whether contain val
    bool contain(T val) const {
        return contain(root, val);
    }
    // empty and clear
    bool empty() const {
        return root == nullptr;
    }
    void clear() {
        clear(root);
    }

    // insert and remove
    void insert(const T &val) {
        insert(root, val);
    }
    void insert(T &&val){
        insert(root, std::move(val));
    }
    void remove(const T &val){
        remove(root, val);
    }
    void remove(T &&val){
        // Remove a right reference is of no profit
        // So I just use left reference again
        remove(root, val);
    }

private:
    // Inner node structure
    struct node{
        T value;
        node *left = nullptr;
        node *right = nullptr;

        // Constructors
        node() = default;
        node(const T &val, node *l, node *r):
            value(val), left(l), right(r){}
        node(T &&val, node *l, node *r):
            value(std::move(val)), left(l), right(r){}
    };
    
    // The only member variable
    node *root = nullptr;

    // Return a clone of the tree pointed by ptr
    node *clone(node *ptr){
        if (ptr == nullptr) return nullptr;
        return new node{ptr->value, clone(ptr->left), clone(ptr->right)};
    }
    // Private versions of all routines
    T min(node *ptr) const {
        if (ptr == nullptr) {
            cerr << "Error: cannot get min value of nullptr" << endl;
            return {};
        }
        T result = ptr->value;
        if (ptr->left != nullptr)
            result = std::min(result, min(ptr->left));
        if (ptr->right != nullptr)
            result = std::min(result, min(ptr->right));
        return result;
    }
    T max(node *ptr) const {
        if (ptr == nullptr) {
            cerr << "Error: cannot get max value of nullptr" << endl;
            return {};
        }
        T result = ptr->value;
        if (ptr->left != nullptr)
            result = std::max(result, max(ptr->left));
        if (ptr->right != nullptr)
            result = std::max(result, max(ptr->right));
        return result;
    }
    bool contain(node *ptr, T val) const {
        if (ptr == nullptr) return false;
        return ptr->value == val || contain(ptr->left, val) || contain(ptr->right, val);
    }
    void clear(node *&ptr){
        if (ptr == nullptr) return;
        clear(ptr->left);
        clear(ptr->right);
        delete ptr;
        ptr = nullptr;
    }

    // Real insert routine
    void insert(node *&ptr, const T &val){
        if (ptr == nullptr){
            auto newNode = new node{val, nullptr, nullptr};
            ptr = newNode;
        } else if (ptr->value > val){
            insert(ptr->left, val);
        } else if (ptr->value < val){
            insert(ptr->right, val);
        } else {
            // cerr << "Error: inserted value already exist." <<  endl;
        }
    }
    void insert(node *&ptr, T &&val){
        if (ptr == nullptr){
            auto newNode = new node{std::move(val), nullptr, nullptr};
            ptr = newNode;
        } else if (ptr->value > val){
            insert(ptr->left, std::move(val));
        } else if (ptr->value < val){
            insert(ptr->right, std::move(val));
        } else {
            // cerr << "Error: inserted value already exist." <<  endl;
        }
    }

    // Real remove routine
    void remove(node *&ptr, const T &val){
        if (ptr == nullptr){
            // cerr << "Error: removed value dosen't exist." << endl;
            return;
        }
        if (ptr->value > val) remove(ptr->left, val);
        else if (ptr->value < val) remove(ptr->right, val);
        else {
            // For leaf nodes
            if (ptr->left == nullptr && ptr->right == nullptr){
                delete ptr;
                ptr = nullptr;
            } else if (ptr->left == nullptr){
                // For nodes with only one child at right branch
                auto p = ptr;
                ptr = ptr->left;
                delete p;
            } else if (ptr->right == nullptr){
                // For nodes with only one child at left branch
                auto p = ptr;
                ptr = ptr->right;
                delete p;
            } else {
                // For nodes with two children, find the max of right child,
                // and move the max value to the node, recursively remove the max node.
                auto rightMin = min(ptr->right);
                ptr->value = rightMin;
                remove(ptr->right, rightMin);
            }
        }
    }
};


//
//  AVL Tree:
//   Bias is the allowed imbalance of the AVL tree which is set as a private member variable.
//
template <typename T>
class myAVLTree{
public:
    myAVLTree() = default;
    // You can choose to pass a bias value as b, if you want to change bias. And b should be non-negative.
    myAVLTree(const myAVLTree &rhs, int b = 1){
        if (b < 0) {
            cerr << "Error: bias should be non-negative." << endl;
            return;
        }
        root = clone(rhs.root);
        bias = b;
    }
    myAVLTree(myAVLTree &&rhs, int b = 1){
        if (b < 0) {
            cerr << "Error: bias should be non-negative." << endl;
            return;
        }
        root = rhs;
        bias = b;
    }
    ~myAVLTree(){
        clear(root);
    }
    void clear() {
        clear(root);
    }
    bool empty() const {
        return root == nullptr;
    }

    // Get the height of the tree.
    int getHeight() const {
        return getHeight(root);
    }

    // find the maximum and minimum
    T max() const {
        node *maxNode = max(root);
        if (maxNode == nullptr){
            cerr << "Error: cannot get the maximum of empty tree." << endl;
            return {};
        }
        return maxNode->value;
    }
    T min() const {
        node *minNode = min(root);
        if (minNode == nullptr){
            cerr << "Error: cannot get the minimum of empty tree." << endl;
            return {};
        }
        return minNode->value;
    }

    // public contain, insert and remove, just like them in myBST.
    bool contain(const T&val) const {
        return contain(val, root);
    }
    void insert(const T &val) {
        insert(val, root);
    }
    void insert(T &&val){
        insert(std::move(val), root);
    }
    void remove(const T &val){
        remove(val, root);
    }
    void remove(T &&val){
        remove(val, root);
    }
private:
    // inner node structure, there is a height member additional
    struct node {
        T value;
        node *left = nullptr;
        node *right = nullptr;
        int height = 0;
        node(const T &val, node *l, node *r, int h):
            value(val), left(l), right(r), height(h) {}
        node(T &&val, node *l, node *r, int h):
            value(std::move(val)), left(l), right(r), height(h) {}
    };
    // get the height of the node. For convenience, we set height of nullptr as -1.
    int getHeight(node *ptr) const {
        return ptr == nullptr ? -1 : ptr->height;
    }
    // return a clone of the node structure.
    node *clone(node *ptr) const {
        if (ptr == nullptr) return nullptr;
        return new node{ptr->value, clone(ptr->left), clone(ptr->right), ptr->height};
    }
    void clear(node *&ptr) {
        if (ptr == nullptr) return;
        clear(ptr->left);
        clear(ptr->right);
        delete ptr;
        ptr = nullptr;
    }
    node *max(node *ptr) const {
        if (ptr == nullptr) return nullptr;
        T maxVal = ptr->value;
        node *maxNode = ptr;
        if (ptr->left != nullptr){
            node *leftMax = max(ptr->left);
            if (leftMax->value > maxVal){
                maxVal = leftMax->value;
                maxNode = leftMax;
            }
        }
        if (ptr->right != nullptr){
            node *rightMax = max(ptr->right);
            if (rightMax->value > maxVal){
                maxVal = rightMax->value;
                maxNode = rightMax;
            }
        }
        return maxNode;
    }
    node *min(node* ptr) const {
        if (ptr == nullptr) return nullptr;
        T minVal = ptr->value;
        node *minNode = ptr;
        if (ptr->left != nullptr){
            node *leftMin = min(ptr->left);
            if (leftMin->value < minVal){
                minVal = leftMin->value;
                minNode = leftMin;
            }
        }
        if (ptr->right != nullptr){
            node *rightMin = min(ptr->right);
            if (rightMin->value < minVal){
                minVal = rightMin->value;
                minNode = rightMin;
            }
        }
        return minNode;
    }
    bool contain(const T &val, node *ptr) const {
        if (ptr == nullptr) return false;
        return ptr->value == val || contain(val, ptr->left) || contain(val, ptr->right);
    }

    // In AVL tree, insert and remove routines should apply balance() routine to balance the AVL tree.
    void insert(const T &val, node *&ptr) {
        if (ptr == nullptr) {
            node *newNode = new node{val, nullptr, nullptr, 0};
            ptr = newNode;
        } else if (val < ptr->value){
            insert(val, ptr->left);
        } else if (val > ptr->value){
            insert(val, ptr->right);
        } else {
            // cerr << "Error: inserted value already exists." << endl;
            return;
        }
        // Additional balance routine
        balance(ptr);
    }
    void insert(T &&val, node *&ptr){
        if (ptr == nullptr){
            node *newNode = new node{std::move(val), nullptr, nullptr, 0};
            ptr = newNode;
        } else if (val < ptr->value){
            insert(val, ptr->left);
        } else if (val > ptr->value){
            insert(val, ptr->right);
        } else {
            // cerr << "Error: inserted value already exists." << endl;
            return;
        }
        balance(ptr);
    }

    void remove(const T &val, node *&ptr){
        if (ptr == nullptr){
            // cerr << "Error: removed value dosen't exist." << endl;
            return;
        } else if (val < ptr->value){
            remove(val, ptr->left);
        } else if (val > ptr->value){
            remove(val, ptr->right);
        } else {
            if (ptr->left == nullptr && ptr->right == nullptr){
                delete ptr;
                ptr = nullptr;
            } else if (ptr->left == nullptr){
                ptr->value = ptr->right->value;
                delete ptr->right;
                ptr->right = nullptr;
            } else if (ptr->right == nullptr){
                ptr->value = ptr->left->value;
                delete ptr->left;
                ptr->left = nullptr;
            } else {
                node *rightMin = min(ptr->right);
                ptr->value = rightMin->value;
                remove(rightMin->value, rightMin);
            }
            balance(ptr);
        }
    }

    // Critical in AVL tree!
    // balance routine
    void balance(node *&ptr) {
        if (ptr == nullptr) return;
        if (getHeight(ptr->left) - getHeight(ptr->right) > bias) {
            // Left child overload, single rotate or double rotate
            if (getHeight(ptr->left->left) > getHeight(ptr->left->right))
                rotateLeft(ptr);
            else
                doubleRotateLeft(ptr);
        } else if (getHeight(ptr->right) - getHeight(ptr->left) > bias) {
            // Right child overload, single rotate or double rotate
            if (getHeight(ptr->right->right) > getHeight(ptr->right->left))
                rotateRight(ptr);
            else
                doubleRotateRight(ptr);
        }
        // Put height update process in specific rotate routines
    }

    // Single rotate with left child
    void rotateLeft(node *&ptr) {
        // Rotate
        node *newPtr = ptr->left;
        ptr->left = newPtr->right;
        newPtr->right = ptr;
        // Update height
        ptr->height = std::max(getHeight(ptr->left), getHeight(ptr->right)) + 1;
        newPtr->height = std::max(getHeight(newPtr->left), ptr->height) + 1;

        ptr = newPtr;
    }
    // Single rotate with right child
    void rotateRight(node *&ptr) {
        // Rotate
        node *newPtr = ptr->right;
        ptr->right = newPtr->left;
        newPtr->left = ptr;
        // Update height
        ptr->height = std::max(getHeight(ptr->left), getHeight(ptr->right)) + 1;
        newPtr->height = std::max(getHeight(ptr->right), ptr->height) + 1;

        ptr = newPtr;
    }
    // Double rotate can be decomposed as two single rotates
    void doubleRotateLeft(node *&ptr) {
        rotateRight(ptr->left);
        rotateLeft(ptr);
    }
    void doubleRotateRight(node *&ptr) {
        rotateLeft(ptr->right);
        rotateRight(ptr);
    }

    // The only two private member variables
    node *root = nullptr;
    int bias = 1;
};




//
// -------------------- Sort --------------------
//

//
// Bubble sort:
//
template <typename T>
void myBubbleSort(vector<T> &v) {
    while (true){
        int swapped = false;
        for (auto i = 0; i < v.size() - 1; ++i){
            if (v[i] > v[i+1]){
                std::swap(v[i], v[i+1]);
                swapped = true;
            }
        }
        if ( !swapped ) break;
    }
    return;
}


//
// -------------------- Problems & Other Tools --------------------
//

//
//  Selection Problem solution 1:
//  Using std::priority_queue to record all the numbers, and pop() for k times
//
template <typename T>
T mySelectionProblem1(const vector<T> &array, int k){
    priority_queue<T> pq;
    for (auto item : array)
        pq.push(item);
    for (auto i = 0; i < k - 1; ++i)
        pq.pop();
    return pq.top();
}

//
//  Brace checker:
//  Check a file string object (e.g. extracted from a file) whether the braces are balanced ("(", "[", "{"). 
//  Using a std::stack data structure
//
void myBraceChecker(const string &fileName) {
    std::ifstream input(fileName);
    // To record current position
    unsigned line = 1, column = 1;
    // Indicate whether there is an brace error
    bool error = false;
    // Implement with std::stack data structure
    std::stack<char> braceStack;
    char c;
    while (input.get(c)){
        if ( c == ')' ){
            if (braceStack.empty() || braceStack.top() != '('){
                error = true;
                break;
            }
            else braceStack.pop();
        } else if ( c == ']' ){
            if (braceStack.empty() || braceStack.top() != '['){
                error = true;
                break;
            }
            else braceStack.pop();
        } else if ( c == '}' ){
            if (braceStack.empty() || braceStack.top() != '{'){
                error = true;
                break;
            }
            else braceStack.pop();
        } else {
            // Update line and column
            if ( c == '\n' ) {
                ++line;
                column = 0;
            } else if ( c == '(' || c == '[' || c == '{' )
                braceStack.push(c);
            ++column;
        }        
    }
    // Print the result
    if ( error ){
        cout << "Cannot find matching brace at:" << endl;
        cout << "Line: " << line << ",   Column: " << column << endl;
        return;
    } else 
        cout << "Perfect!" << endl;
}

//
//  Postfix calculator:
//  Calculate an expression in postfix notation(reverse Polish notation).
//
double myPostfixCalculator(const string &postfix) {
    std::stack<double> s;
    string operand;
    for (auto c : postfix){
        // Push operands into stack
        if ( !operand.empty() && ( c == '+' || c == '-' || c == '*' || c == '/' || c == ' ' ) ){
            s.push(std::stod(operand));
            operand.clear();
        }
        // Calculation
        if ( c == '+' ){
            double b = s.top(); s.pop();
            double a = s.top(); s.pop();
            s.push(a+b);
        } else if ( c == '-' ){
            double b = s.top(); s.pop();
            double a = s.top(); s.pop();
            s.push(a-b);
        } else if ( c == '*' ){
            double b = s.top(); s.pop();
            double a = s.top(); s.pop();
            s.push(a*b);
        } else if ( c == '/' ){
            double b = s.top(); s.pop();
            if ( b == 0 ) {
                cerr << "Denominator cannot be 0!" << endl;
                return 0;
            }
            double a = s.top(); s.pop();
            s.push(a/b);
        } else if ( c != ' ' ) {
            // Complete operands
            operand.push_back(c);
        }
    }
    return s.top();
}

//
//  Infix calculator
//  Convert an infix expression into postfix expression, then use myPostCalculator to calculate the value.
//
double myCalculator(const string &infix) {
    return myPostfixCalculator(infix2Postfix(infix));
}

# endif