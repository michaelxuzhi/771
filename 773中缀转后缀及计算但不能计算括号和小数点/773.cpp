#include <iostream>
#include <stack>
#include <math.h>
using namespace std;

bool Number(char ch)//�ж��Ƿ�Ϊ���֣����򷵻�true
{
    if (ch >= 48 && ch <= 57)
        return true;
    else
        return false;
}

void InPut(char*& str)//�����������׺���ʽ�ĺ����������ж��Ƿ�Ϸ�
{
    cout << "Please Enter What You Want To calculation:" << endl;
    while (1)
    {
        cin >> str;

        if (Number(str[0]))//��׺���ʽ�ĵ�һ���ض������֣�������ǣ���Ƿ�
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

int GetPriority(char sy)//���ø��������������ȼ�
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


void AddSpace(char*& arr)//��ת�ɵĺ�׺���ʽ�����ֺͷ�����ӿո�����ÿ���ַ�
{
    *arr = ' ';
    arr++;
}

char* GetBack()//��ȡ��׺���ʽ�ĺ���
{
    char* middle = new char[30];
    char* back = new char[30];
    char* backend = back;
    InPut(middle);
    stack<char> s;
    s.push('#');
    while (*middle)
    {
        if (Number(*middle) || *middle == '.')//��������ֻ���С���Ļ���ֱ�����
        {
            *back = *middle;
            back++, middle++;
        }
        else
        {
            if (Number(*(back - 1)))//ֻ��������һ��ʱ���ֵĻ����ż������ո�
                                    //�����������������������������ڶ���ո�
            {
                //*back = ' ';
                //back++;
                AddSpace(back);
            }
            if (*middle == ')')//��������ŵĻ���������в�����ֱ�����������ţ����������Ӧ��һ������
            {
                while (s.top() != '(')
                {
                    *back = s.top();
                    s.pop();
                    back++; middle++;
                    AddSpace(back);
                }
                s.pop();//����������
            }
            else if (*middle == '(')//���������ţ������ջ
            {
                s.push(*middle); middle++;
            }
            else if (GetPriority(*middle) > GetPriority(s.top()))//���ջ�ڵĲ��������ȼ�����ջ������ȼ�������ջ
            {
                s.push(*middle); middle++;
            }
            else if (GetPriority(*middle) <= GetPriority(s.top()))
                                                     //���ջ�ڵĲ��������ȼ����ڻ����ջ������ȼ������ջ�ڵķ��ţ�����ջջ��ķ���
            {
                *back = s.top();
                s.pop(); 
                s.push(*middle);
                back++; middle++;
                AddSpace(back);
            }
        }
    }
    while (s.top() != '#')//��׺���ʽ������ɣ�����=ջ�л��з��Ŵ��ڣ�һһ��ջ���
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
    //��Ϊ���Ϊchar*�����Կ�����λ�����ϵ����ֱ��𿪣��˺���Ϊ��ȷ�õ�����
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

double Cauculate(char ch, double left, double right)//������������Ӧ�Ĳ���
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
        if (Number(*back))//��������
        {
            s.push(GetNumber(back));//����ȷ��������ջ
        }
        else if (*back == ' ')
        {
            back++;//�����ո�����
        }
        else
        {
            double a = s.top();
            s.pop();
            double b = s.top();
            s.pop();
            s.push(Cauculate(*back, b, a));//��������ʱ��ȡջ���ĵڶ������͵�һ������⣬����ջ
            back++;
        }
    }
    while (s.size() >= 2)//����ջ�ڴ��ڵ�������2ʱ���������㣬ֱ��ֻʣ��һ����
    {
        double a = s.top();
        s.pop();
        double b = s.top();
        s.pop();
        s.push(Cauculate(*back, b, a));
    }
    //����������֣��������ս��
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