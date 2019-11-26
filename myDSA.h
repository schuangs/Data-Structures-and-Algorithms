/**
 * This is the header of myDSA.cpp
 * myDSA includes implementations of various data structures and algorithms
 * @author Junkang_Huang huangjk8@mail2.sysu.edu.cn
**/

# ifndef MYDSA_H
# define MYDSA_H

# include <vector>
# include <string>
# include <queue>
# include <ctime>
# include <chrono>
# include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::priority_queue;


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
    time_point_t start;
    time_point_t end;
    vector<time_point_t> points;
    bool counting = false;
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
        for (auto i = 0; i < points.size(); ++i)
            cout << "# " << i+1 << "    " << (points[i]-start).count() << " ms" << endl;
        cout << endl << "Running time:     " << (end - start).count() << " ms" << endl;
        return;
    }
};


//
//  Selection Problem solution 1:
//  Using std::priority_queue to record all the numbers, and pop() for k times
//
template <typename T>
T selectionProblem1(const vector<T> &array, int k){
    priority_queue<T> pq;
    for (auto item : array)
        pq.push(item);
    for (auto i = 0; i < k - 1; ++i)
        pq.pop();
    return pq.top();
}

# endif