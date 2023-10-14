/* Mayuresh Chavan
 * AI A B2:5 Operating Systems
 * queue.cpp
 */

#import <iostream>
#import <deque>
#import <vector>
#import <string>
#import "PCB.cpp"

using namespace std;

class Queue {
  public:
    Queue();
    Queue(string, vector<PCB>);
    void print();
    PCB pop();
    PCB pop(int);
    void push(PCB);
    void push(PCB,int);
    void delete_pos(int);
    void delete_PCB(int);
    int length();
    PCB& operator[](int);
    string get_name();
  private:
    deque<PCB> queue;
    string name;
};

Queue::Queue() {}

// constructor that adds all the PCBs to the queue
Queue::Queue(string n, vector<PCB> arr) {
    name = n;
    for (int i=0; i < arr.size(); i++) {
        queue.push_back(arr[i]);
        cout << "Added Process " << arr[i].get_pid() << " to the " << n << " queue.\n";
    }
}

// This will print the contents of the Queue
void Queue::print() {
    cout << "Contents of the " << name << " Queue:\n";
    for (int i=0; i<queue.size(); i++) {
      cout << "Position:    [" << i+1 << "]\n";
      queue[i].print();
    }
    cout << "End contents of the " << name << " Queue.\n\n";
}

PCB Queue::pop() {
    PCB p = queue.front();
    queue.pop_front();
    return p;
}

// pops an element at a specific position 1 = 1st, 2 = 2nd
PCB Queue::pop(int pos) {
    PCB p = queue.at(pos-1);
    queue.erase(queue.begin()+pos-1);
    return p;
}

void Queue::push(PCB pcb) {
    queue.push_back(pcb);
    cout << "Process " << pcb.get_pid() << " added to the " << get_name() << " queue.\n";
}

// pushes an element at a specific position 1 = 1st, 2 = 2nd
void Queue::push(PCB pcb, int pos) {
    if (pos > queue.size())
        pos = queue.size()+1;
    deque<PCB>::iterator it = queue.begin()+pos-1;
    queue.insert(it, pcb);
    cout << "Process " << pcb.get_pid() << " added to the " << get_name() << " queue.\n";
}

// this method will delete the PCB at a given position
void Queue::delete_pos(int pos) {
    if (pos > queue.size())
        pos = queue.size()+1;
    PCB p = pop(pos);
}

// this method will delete the PCB in the queue with the associated PID
void Queue::delete_PCB(int pid) {
    PCB p;
    for (int i=0; i<queue.size(); i++) {
        p = queue[i];
        if (p.get_pid() == pid) {
            delete_pos(i+1);
            cout << "Process " << p.get_pid() << " deleted to the " << get_name() << " queue.\n";
            return;
        }
    }
}

int Queue::length() {
    return queue.size();
}

PCB& Queue::operator[](int i) {
    return queue[i];
}

string Queue::get_name() {
    return name;
}
