#include <iostream>
#include <stack>
using namespace std;

class Stack {
private:
    stack<int> mainStack;
    stack<int> minStack;
    stack<int> maxStack;

public:
    void push(int x) {
        mainStack.push(x);

        if (minStack.empty() || x <= minStack.top()) {
            minStack.push(x);
        } else {
            minStack.push(minStack.top());
        }

        if (maxStack.empty() || x >= maxStack.top()) {
            maxStack.push(x);
        } else {
            maxStack.push(maxStack.top());
        }
    }

    void pop() {
        if (!mainStack.empty()) {
            mainStack.pop();
            minStack.pop();
            maxStack.pop();
        }
    }

    int top() {
        if (!mainStack.empty()) {
            return mainStack.top();
        }
        return -1;
    }

    int getMin() {
        if (!minStack.empty()) {
            return minStack.top();
        }
        return -1;
    }

    int getMax() {
        if (!maxStack.empty()) {
            return maxStack.top();
        }
        return -1;
    }
};

int main() {
    Stack s;
    s.push(10);
    s.push(5);
    s.push(20);
    s.push(3);

    cout << "Top: " << s.top() << endl;
    cout << "Min: " << s.getMin() << endl;
    cout << "Max: " << s.getMax() << endl;

    s.pop();
    cout << "After popping:" << endl;
    cout << "Top: " << s.top() << endl;
    cout << "Min: " << s.getMin() << endl;
    cout << "Max: " << s.getMax() << endl;
    return 0;
}