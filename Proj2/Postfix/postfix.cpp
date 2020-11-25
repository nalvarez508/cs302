#include <iostream>
#include <string>
#include <ctype.h>

#include "StackLinked.h"

using namespace std;

float postfix_input(const string postfix, StackLinked<float> & stack);
float calculate(const float operand1, const float operand2, const char oprtr);
float polynomial(const float operand1, const float operand2);

int main()
{
  StackLinked<float> pStack;

  cout << "Exercise 1: Five postfix expressions.\n";

  cout << "(5+6)*(4/3) = 56+43/* = " << postfix_input("56+43/*", pStack) << endl;
  cout << "((5-1)/(6/3))^3 = 51-63//3^ = " << postfix_input("51-63//3^", pStack) << endl;
  cout << "6+9-3/5*4 = 69+35/4*- = " << postfix_input("69+35/4*-", pStack) << endl;
  cout << "(7*7*5)-(8+9-5+0/3) = 77*5*89+5-03/+- = " << postfix_input("77*5*89+5-03/+-", pStack) << endl;
  cout << "4^2*3/6 = 42^3*6/ = " << postfix_input("42^3*6/", pStack) << endl;

}

float postfix_input(const string postfix, StackLinked<float> & stack)
{
  int size = postfix.length();
  for (int x=0; x<size; x++)
  {
    if (isdigit(postfix[x]) == 1)
    {
      stack.push(postfix[x]-'0'); //Convert to float
    }
    else //Operators are applied
    {
      char newOperator = postfix[x];
      float operand1 = stack.pop();
      float operand2 = stack.pop();
      float output = calculate(operand1, operand2, newOperator);
      stack.push(output);
    }
  }
  float finalOutput = stack.pop();
  return finalOutput;
}

float calculate(const float operand1, const float operand2, const char oprtr)
{
  switch (oprtr)
  {
    case '+':
      return operand2 + operand1;
    case '-':
      return operand2 - operand1;
    case '*':
      return operand2 * operand1;
    case '/':
      return operand2 / operand1;
    case '^':
      return polynomial(operand2, operand1);
    default:
      cout << "No operator\n";
  }
}

float polynomial(const float operand1, const float operand2)
{
  if (operand2 != 0)
  {
    return (operand1*polynomial(operand1, (operand2-1)));
  }
  else
  {
    return 1;
  }
}