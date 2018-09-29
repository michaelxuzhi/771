#include <stack>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
string postfix_to_infix(vector<string> expr) {
    stack<string> s;
    for (int i = 0; i < expr.size(); ++i) {
        // a number
        if (!expr[i].empty() && expr[i][0] >= '0' && expr[i][0] <= '9') {
            s.push(expr[i]);
        }
        // an operator
        else {
            string second = s.top(); s.pop();
            string first = s.top(); s.pop();
            s.push("(" + first + expr[i] + second + ")");
        }
    }
    return s.top();
}
int main() {
    vector<string> expr = {"3", "2", "5", "-", "6", "*", "3", "/", "+"};
    // output: (3+(((2-5)*6)/3))
    cout << postfix_to_infix(expr) << endl;
    return 0;
}