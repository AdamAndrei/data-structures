#include "linked-lists/demos/StackDemo.h"
#include "linked-lists/stack/Stack.h"
#include <iostream>

static bool checkBrackets(const std::string &expression)
{
    auto rank = [](char c) -> int
    {
        switch (c)
        {
        case '{':
            return 1;
        case '[':
            return 2;
        case '(':
            return 3;
        case '}':
            return 4;
        case ']':
            return 5;
        case ')':
            return 6;
        default:
            return 0;
        }
    };

    Stack<char> stack;

    for (char c : expression)
    {
        int r = rank(c);
        if (r == 0)
            continue; // not a bracket, skip

        if (r <= 3)
        { // opening bracket
            stack.push(c);
        }
        else
        { // closing bracket
            if (stack.isEmpty())
                return false; // nothing to close
            if (r - rank(stack.peek()) != 3)
                return false; // wrong type, e.g. ( closed by ]
            stack.pop();
        }
    }

    return stack.isEmpty();
}

static void demoCheckBrackets()
{
    std::string s1 = "(3+ [2+4*5]{([ksjbdkj](.ksnd))})";
    std::string s2 = "(3+ [2+4*5]{([ksjbdkj](.ksnd)])})";

    std::cout << s1 << (checkBrackets(s1) ? " is correct" : " is not correct") << std::endl;
    std::cout << s2 << (checkBrackets(s2) ? " is correct" : " is not correct") << std::endl;
}

void demoStack()
{
    Stack<int> s;

    std::cout << "Stack demo:" << std::endl;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    std::cout << s << std::endl;

    std::cout << "Popped value: " << s.pop() << std::endl;
    std::cout << "Peeked value: " << s.peek() << std::endl;

    demoCheckBrackets();
}