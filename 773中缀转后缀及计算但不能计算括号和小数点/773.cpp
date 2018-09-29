#include <iostream>
#include <stack>
#include <math.h>
using namespace std;

bool Number(char ch)//判断是否为数字，是则返回true
{
    if (ch >= 48 && ch <= 57)
        return true;
    else
        return false;
}

void InPut(char*& str)//接收输入的中缀表达式的函数，并简单判断是否合法
{
    cout << "Please Enter What You Want To calculation:" << endl;
    while (1)
    {
        cin >> str;

        if (Number(str[0]))//中缀表达式的第一个必定是数字，如果不是，则非法
        {
            break; 
        }
        else
        {
            cout << "Illegal Input,Please Input Again:";
            delete[] str;
        }
    }
}

int GetPriority(char sy)//设置各个操作符的优先级
{
    switch (sy)
    {
    case '#':
        return 0;
    case '(':
        return 1;
    case '+':
    case '-':
        return 3;
    case '*':
    case '/':
        return 5;
    case ')':
        return 6;
    default:
        return -1;
    }
}


void AddSpace(char*& arr)//给转成的后缀表达式的数字和符号添加空格，区分每个字符
{
    *arr = ' ';
    arr++;
}

char* GetBack()//获取后缀表达式的函数
{
    char* middle = new char[30];
    char* back = new char[30];
    char* backend = back;
    InPut(middle);
    stack<char> s;
    s.push('#');
    while (*middle)
    {
        if (Number(*middle) || *middle == '.')//如果是数字或者小数的话，直接输出
        {
            *back = *middle;
            back++, middle++;
        }
        else
        {
            if (Number(*(back - 1)))//只有他的上一个时数字的话，才继续给空格
                                    //否则遇到多个操作符，则输出域会存在多个空格
            {
                //*back = ' ';
                //back++;
                AddSpace(back);
            }
            if (*middle == ')')//如果右括号的话，输出所有操作符直到遇到左括号，并抛弃相对应的一堆括号
            {
                while (s.top() != '(')
                {
                    *back = s.top();
                    s.pop();
                    back++; middle++;
                    AddSpace(back);
                }
                s.pop();//抛弃左括号
            }
            else if (*middle == '(')//遇到左括号，则进入栈
            {
                s.push(*middle); middle++;
            }
            else if (GetPriority(*middle) > GetPriority(s.top()))//如果栈内的操作符优先级高于栈外的优先级，则入栈
            {
                s.push(*middle); middle++;
            }
            else if (GetPriority(*middle) <= GetPriority(s.top()))
                                                     //如果栈内的操作符优先级低于或等于栈外的优先级，输出栈内的符号，并入栈栈外的符号
            {
                *back = s.top();
                s.pop(); 
                s.push(*middle);
                back++; middle++;
                AddSpace(back);
            }
        }
    }
    while (s.top() != '#')//中缀表达式遍历完成，但是=栈中还有符号存在，一一出栈输出
    {
        AddSpace(back);
        *back = s.top();
        s.pop(); back++;
    }
    *back = '\0';
    cout << "The Back Is: " << backend << endl;
    return backend;
}

double GetNumber(char*& arr)
{
    //因为输出为char*，所以可能两位数以上的数字被拆开，此函数为正确得到数字
    double sum[10] = { 0 }; int i = 0; double result = 0;
    while (*arr != ' ')
    {
        sum[i] = *arr-48;
        i++;
        arr++;
    }
    int k = i - 1;
    for (int j = 0; j < i; j++,k--)
    {
        result += (sum[j] * pow(10, k));
    }
    return result;
}

double Cauculate(char ch, double left, double right)//各个操作符对应的操作
{
    switch (ch)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    default:
        return 0;
        break;
    }
}

double CountBack(char* back)
{
    stack<double> s;
    while (*back)
    {
        if (Number(*back))//遇到数字
        {
            s.push(GetNumber(back));//将正确的数字入栈
        }
        else if (*back == ' ')
        {
            back++;//遇到空格跳过
        }
        else
        {
            double a = s.top();
            s.pop();
            double b = s.top();
            s.pop();
            s.push(Cauculate(*back, b, a));//遇到符号时，取栈顶的第二个数和第一个数求解，并入栈
            back++;
        }
    }
    while (s.size() >= 2)//最终栈内存在的数大于2时，继续计算，直到只剩下一个数
    {
        double a = s.top();
        s.pop();
        double b = s.top();
        s.pop();
        s.push(Cauculate(*back, b, a));
    }
    //返回这个数字，既是最终结果
    return s.top();
}

void FunTest()
{
    cout << "The Result Is: " <<CountBack(GetBack()) << endl;
}

int main()
{
    FunTest();
    system("pause");
    return 0;
}