#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

bool validDelimiter(char open, char close)
{

    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

bool delimitersOk(const string &expression)
{

    stack<char> s;
    char ch;

    for (int i = 0; i < expression.size(); i++)
    {

        ch = expression[i];

        if (ch == '(' || ch == '{' || ch == '[')
        {
            s.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (s.empty())
            {
                return false;
            }

            if (!validDelimiter(s.top(), ch))
            {
                return false;
            }

            s.pop();
        }
    }

    if(!s.empty())
        return false;

    return true;
};

int main()
{

    ifstream file("input.txt");

    int t;

    file >> t;
    bool res;
    string str;

    for (int i = 0; i < t; i++)
    {
        file >> str;
        res = delimitersOk(str);

        if (res)
            cout << "Valid" << endl;
        else
            cout << "Invalid" << endl;
    }

    return 0;
}