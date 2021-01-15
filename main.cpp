#include <bits/stdc++.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <ctype.h>

#define MAXSTACK 100

#define POSTFIX_STACK
#define CALC_STACK

using namespace std;

char Stack[MAXSTACK];
int top=-1;

//( 5 * ( 6 + 2 ) - 12 / 4 )

//      Checking Level of plus,minus,multiple,division & power....
int checkPrecendence(char c)
{
    if(c=='^')
        return 3;
    else if(c=='*'||c=='/')
        return 2;
    else if(c=='+'||c=='-')
        return 1;
    else
        return -1;
}

//      Pushing value to stack and incrementing top...
void pushStack(char ch)
{
    if(top>MAXSTACK)
    {
        cout<<"Stack Overflow.."<<endl;
    }
    else
    {
        top++;
        Stack[top] = ch;
    }

}
//      Popping from stack and decrement top...
char popStack()
{
    if(top == -1)
    {
        //cout<<"Underflow.."<<endl;
        return -1;
    }
    else
        return Stack[top--];
}
int STACK[MAXSTACK];
int Top=-1;

void stackPush(int num)
{
    if(Top>MAXSTACK)
    {
        cout<<"Stack Overflow.."<<endl;
    }
    else
    {
        Top++;
        STACK[Top]=num;
    }

}

int stackPop()
{
    if(Top == -1)
    {
        return -1;
    }
    else
        return STACK[Top--];
}


//      This function receive a postfix expression
//      and return it's value
int getValue(string str)
{
    int i,num;
    int n=str.size();
    Top=-1;         //initializing stack

#ifdef CALC_STACK
cout<<endl<<"\tPostfix \tStack"<<endl;
#endif // CALC_STACK

    for(i=0;i<n;i++)
    {
        if(str[i]==' ') // Ignoring spaces
            continue;

        if(isdigit(str[i])) // isdigit() determines if 0-9
        {
            num=0;
            while(isdigit(str[i]))// taking bigger multi-digit number as integer...
            {
                num=num*10+str[i]-'0';
                i++;
            }

#ifdef CALC_STACK
    cout<<"\t"<<num;
#endif // CALC_STACK

            stackPush(num); //  Pushing digit/number to stack as integer...

        }
        else//else takes care of operators in postfix expression...
        {

#ifdef CALC_STACK
cout<<"\t"<<str[i];
#endif // CALC_STACK

            //  Popping back last two number for performing operations..
            int b = stackPop();
            int a = stackPop();

            // Checking operator one by one..
            // Then Pushing their operated value

            if(str[i] == '+')
                stackPush(a+b);

            else if(str[i] == '-')
                stackPush(a-b);

            else if(str[i] == '*')
                stackPush(a*b);

            else if(str[i] == '/')
                stackPush(int(a/b));

            else if(str[i] == '^')
                stackPush(pow(a,b));

        }

#ifdef CALC_STACK
int j;
cout<<"\t\t";
for(j=0;j<=Top;j++)
{
    cout<<STACK[j]<<" ";
}
cout<<endl;
#endif // CALC_STACK
    }
    return stackPop();
}


//  This Function takes an INFIX expression and
//  Returns equivalent POSTFIX expression
string toPostfix(string infix)
{
    int i,n;
    char ch;
    string postfix;

    top=-1;  //initializing an empty stack
    n=infix.size();

#ifdef POSTFIX_STACK // To see simulation...
cout<<endl<<"\tInfix \tStack \t Postfix"<<endl;
#endif // POSTFIX_STACK

    //  Scanning the infix expression from left to right...
    for(i=0;i<n;i++)
    {
        if(infix[i]==' ')   //  ignoring spaces
            continue;

        if(isalnum(infix[i]))
        {
            while(isalnum(infix[i])) // taking multi-digit number until space or operator is found
            {
                postfix+=infix[i];
                i++;
            }
            i--;
            postfix+=" ";       //  adding space

        }
        else if(infix[i] == '(') // Pushing left parenthesis to the stack
        {
            pushStack(infix[i]);
        }

        //  If right parenthesis is found
        //  Repeatedly popping form the stack until '(' is found
        else if(infix[i] == ')')
        {
            char ch;
            ch=popStack();
            while(ch != -1 && ch!='(')
            {
                postfix+=ch;
                postfix+=" ";
                ch=popStack();
            }

        }
        else // else take care of operators
        {
            ch=popStack();
            //  Repeatedly popping operators which has higher or same precedence than new one
            if(checkPrecendence(infix[i]) < checkPrecendence(ch)) //
            {
                while((checkPrecendence(infix[i]) <= checkPrecendence(ch)) && (ch != -1))
                {
                    postfix+=ch;
                    postfix+=+" ";
                    ch=popStack();
                }
                pushStack(infix[i]);
            }
            else        // if new operator has lower precedence simply push it to stack
            {
                pushStack(ch);
                pushStack(infix[i]);
            }
        }
// Nothing just diplaying the stack simulation...
#ifdef POSTFIX_STACK
int j;
cout<<"\t";
cout<<infix[i]<<"\t";
for(j=0;j<=top;j++)
{
    cout<<Stack[j]<<" ";
}
    for(;j<6;j++)
    {
        cout<<"  ";
    }
    cout<<postfix<<endl;
    cout<<endl;
#endif // POSTFIX_STACK
    }

    //  Repeatedly popping the stack and adding to POSTFIX until stack is empty
    ch=popStack();
    while(ch != -1)
    {
        postfix+=ch;
        postfix+=+" ";

#ifdef POSTFIX_STACK
int j;
cout<<infix[i]<<"\t";
for(j=0;j<=top;j++)
{
    cout<<Stack[j]<<" ";
}
    for(;j<6;j++)
    {
        cout<<"  ";
    }
    cout<<postfix<<endl;
    cout<<endl;
#endif // POSTFIX_STACK

        ch=popStack();

    }

    return postfix;
}

int main()
{
    string infix;
    string postfix;
    int value;

    cout<<endl<<"\tEnter an infix expression: ";
    getline(cin,infix);

    postfix = toPostfix(infix);
    cout<<endl<<"\tEquivalent postfix expression : ";
    cout<<postfix<<endl;


    value=getValue(postfix);
    cout<<endl<<"\tValue: "<<value<<endl;

    return 0;
}
