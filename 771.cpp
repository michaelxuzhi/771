#include <iostream>
#include <stack>
#include <string>
using namespace std;

/**
 *�жϵ�ǰ�ַ��Ƿ�Ϊ����
 */
bool isNumber(char s) {
    string opers = "+-*/()";
    for (int i = 0; i < opers.length(); i++) {
        if (s == opers.at(i)) {
            return false;
        }
    }
    return true;
}

/**
 * �жϵ�ǰ�������ջ������������ȼ���С
 */
bool isPriorityLow(char currOper, char topOper) {
    if (currOper == '+' || currOper == '-') {
        if (topOper == '*' || topOper == '/' || topOper == '+' || topOper == '-') {
            return true;
        }
    }

    if (currOper == '*' || currOper == '/') {
        if (topOper == '*' || topOper == '/') {
            return true;
        }
    }

    return false;
}

/**
 * �����ǰ��������ȼ�С�ڻ����ջ�������, ��ջ������������ӵ���׺���ʽβ,
 * ���������бȽ�, ֱ����ǰ��������ȼ�����ջ����������ȼ�
 */
void loopPushOperator(string& s, char oper, stack<char>& operators) {
    if (operators.size() > 0 && isPriorityLow(oper, operators.top())) {
        s += operators.top();
        operators.pop();
        loopPushOperator(s, oper, operators);
    }
}

/**
 * �ж��������ѹ�������ջ���Ǽӵ���׺���ʽβ
 */
void handleOperator(string& s, char oper,  stack<char>& operators) {
    switch (oper) {
    case '+':
    case '-':
    case '*':
    case '/':
        //��������ջΪ��, ֱ�ӽ���ǰ�����ѹջ
        if (operators.size() <= 0) {
            operators.push(oper);
        //�����ǰ��������ȼ�С�ڵ���ջ����������ȼ�, ��ջ��������ӵ���׺���ʽβ
        } else if (isPriorityLow(oper, operators.top())) {
            loopPushOperator(s, oper, operators);
            operators.push(oper);
        ///�����ǰ��������ȼ�����ջ����������ȼ�, ����ǰ�����ѹջ
        } else {
            operators.push(oper);
        }
        break;
    case '(':
        operators.push(oper);  //��ǰ�����Ϊ'('ֱ��ѹջ
        break;
    case ')':
        //��ջ��Ԫ�ص����ӵ���׺���ʽβ,ֱ�����������"("
        while (operators.top() != '(') {
            s += operators.top();
            operators.pop();
        }
        operators.pop();
        break;
    default:
        break;
    }
}

/**
 * ��׺���ʽת��׺���ʽ
 */
string infixToSuffix(string& s) {
    stack<char> operators;     //�����ջ
    string suffix;                        //��׺���ʽ

    for (int i = 0; i < s.length(); i++) {
        if (isNumber(s.at(i))) {   //���������ֱ�Ӽӵ���׺���ʽβ
            suffix += s.at(i);
        } else {
            handleOperator(suffix, s.at(i), operators);  //���������
        }
    }

    if (suffix.length() > 0) {
        while (operators.size() > 0) {  //�������ջ�����е������ȫ����ջ�ӵ���׺���ʽβ
            suffix += operators.top();
            operators.pop();
        }
        return suffix;
    } else {
        return "";
    }
}

/**
 * ���������,����ջ����������ֵ,���������ֵѹջ
 */
void CalculateResult( char oper, stack<int>& tmpStack) {
    if (tmpStack.size() < 2) {
        return;
    }
    //ջ���Ƚ����,�����ȵ������ǵڶ���ֵ
    int secondVal = tmpStack.top();
    tmpStack.pop();
    int firstVal = tmpStack.top();
    tmpStack.pop();

    int result = 0;
    switch (oper) {
    case '+':
        result = firstVal + secondVal;
        break;
    case '-':
        result = firstVal - secondVal;
        break;
    case '*':
        result = firstVal * secondVal;
        break;
    case '/':
        result = firstVal / secondVal;
        break;
    default:
        break;
    }

    tmpStack.push(result);
}

/**
 * ͨ����׺���ʽ������
 * ����׺���ʽ������ջ, ���Ϊ������, ����ջ������Ԫ�ؼ�������ѹ��ջ��
 */
float getResultUseSuffix(string& s) {
    if (s.length() <= 0) {
        return 0;
    }

    stack<int> tmpStack;
    for (int i = 0; i < s.length(); i++) {
        if (isNumber(s.at(i))) {
            tmpStack.push(s.at(i) - '0');
        } else {
            CalculateResult(s.at(i), tmpStack);
        }
    }
    return tmpStack.top();
}

int main() {
    string infix;
    //������ַ��������пո�
    cin>>infix;
    string suffix = infixToSuffix(infix);
    float result = getResultUseSuffix(suffix);
    cout<<"������Ϊ: "<<result<<endl;
    return 0;
}