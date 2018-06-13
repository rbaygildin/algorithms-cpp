#include <iostream>
#include <assert.h>
#include <stdexcept>
//#include <conio.h>


#include "IntStack.h"
#include "StackMachine.h"


using namespace std;

void testStack()
{
    IntStack s;

    s.push(42);
    //int a = s.pop();
    assert(s.top() == 42);            // EXPECT_EQ()
    assert(s.pop() == 42);            // EXPECT_EQ()

    // an exception should be thrown
    bool exc = false;
    try {
        s.pop();
    }
    catch(std::logic_error& e)
    {
        std::cout << "An expected exception on pop() operation is succesfully catched\n";
        exc = true;
    }
    assert(exc);

    // test for overflow
    for(int i = 0; i < IntStack::STACK_SIZE; ++i)
        s.push(i);

    // next element cannot be added and, thus, en exception should be thrown
    exc = false;
    try {
        s.push(43);
    }
    catch(std::logic_error& e)
    {
        std::cout << "An expected exception on push() operation is succesfully catched\n";
        exc = true;
    }
    assert(exc);

    //int b = 0;
}

void testStackMachine()
{
    StackMachine sm;
    MinusOp minusOp;
    PlusOp plusOp;
    sm.registerOperation('-', &minusOp);
    sm.registerOperation('+', &plusOp);

    int res = sm.calculate("12 15 10 - +");
    int r1 = sm.getStack().top();
    assert(res == 17);
    assert(r1 == 17);

}

int main()
{
    testStack();
    testStackMachine();
    getchar();
    return 0;
}