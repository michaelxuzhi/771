#include <iostream>  
#include <cstdio>  
#include <stack>  
#include <cstring>  
#include <string>  
using namespace std;  
char str[1100];  
int Compare(char n_ope)  
{  
    if(n_ope=='+'||n_ope=='-') return 1;  
    if(n_ope=='*'||n_ope=='/') return 2;  
    if(n_ope=='(') return 0;  
    return -1;  
}  
int main()  
{  
    int T;  
    scanf("%d",&T);  
    while(T--)  
    {  
        memset(str,'\0',sizeof str);  
        scanf(" %s",str);  
        const int len = strlen(str);  
        stack<char> s;  
        s.push('#');  
        for(int i=0;i<len;i++)  
        {  
            if(isdigit(str[i])){  
                printf("%c",str[i]);  
            }  
            else if(str[i]=='('){  
                s.push(str[i]);  
            }  
            else if(str[i]==')'){  
                while(s.top()!='(')  
                {  
                    printf("%c",s.top());  
                    s.pop();  
                }  
                s.pop();//½«×óÀ¨ºÅµ¯³ö  
            }  
            else{  
                while(Compare(s.top())>=Compare(str[i]))  
                {  
                    printf("%c",s.top());  
                    s.pop();  
                }  
                s.push(str[i]);  
            }  
  
        }  
        while(s.top()!='#'){  
            printf("%c",s.top());  
            s.pop();  
        }  
        printf("\n");  
    }  
    return 0;  
} 