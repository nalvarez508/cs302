//--------------------------------------------------------------------
//
//   delimiters.cpp
//
//--------------------------------------------------------------------

#include <iostream>
#include "StackLinked.h"
using namespace std;

/*#if LAB6_TEST1
#   include "StackLinked.cpp"
#else
#   include "StackArray.cpp"
#endif*/

//--------------------------------------------------------------------

bool delimitersOk ( const string &expression );

//--------------------------------------------------------------------

int main()
{
/*    string inputLine;            // Input line
    char   ch;           */        // Holding pen for input chars

    cout << "This program checks for properly matched delimiters."
         << endl;

/*    while( cin )
    {
        cout << "Enter delimited expression (<EOF> to quit) : "
             << endl;

        // Read in one line
        inputLine = "";
        cin.get(ch);
        while( cin && ch != '\n' )
        {
            inputLine = inputLine + ch;
            cin.get(ch);
        }

        if( ! cin )              // Reached EOF: stop processing
            break;
    
        if ( delimitersOk (inputLine) )
            cout << "Valid" << endl;
        else
            cout << "Invalid" << endl;
    }*/

  cout << "1. {}[]()<> is " << ((delimitersOk("{}[]()<>") ? "valid" : "invalid")) << endl;
  cout << "2. (() is " << (delimitersOk("(()") ? "valid" : "invalid") << endl;
  cout << "3. {{[>]}} is " << (delimitersOk("{{[<]}}") ? "valid" : "invalid") << endl;
  cout << "4. {Used with non-brace characters} is " << (delimitersOk("{Used with non-brace characters}") ? "valid" : "invalid") << endl;
  cout << "5. <{[]}(<>))> is " << (delimitersOk("<{[]}(<>))>") ? "valid" : "invalid") << endl;

  return 0;
}

//--------------------------------------------------------------------
// delimitersOk: the function that students must implement for 
//    Programming Exercise 3.
// Note: we used the term "braces" to describe '[' and ']'. It would
//    have been better to use the term "brackets". The program can be
//    easily modified to process any set of matching delimiters.
//--------------------------------------------------------------------

// Insert your delimitersOk function below

bool delimitersOk(const string &expression)
{
  StackLinked<char> dStack;
  //POP already has logic_error exception in it

  int size = expression.length();
  for (int x=0; x<size; x++)
  {
    switch(expression[x])
    {
      case '(':
      case '[':
      case '{':
      case '<':
      {
        dStack.push(expression[x]);
//        cout << "Push\n";
        break;
      }

      case ')':
      {
//        cout << "Checking )...\t";
        if (dStack.pop() != '(')
        {
//          cout << "Popped )\n";
          return 0;
        }
        break;
      }
      case ']':
      {
//        cout << "Checking ]...\t";
        if (dStack.pop() != '[')
        {
//          cout << "Popped ]\n";
          return 0;
        }
        break;
      }
      case '}':
      {
//        cout << "Checking }...\t";
        if (dStack.pop() != '{')
        {
//          cout << "Popped }\n";
          return 0;
        }
        break;
      }
      case '>':
      {
//        cout << "Checking >...\t";
        if (dStack.pop() != '<')
        {
//          cout << "Popped >\n";
          return 0;
        }
        break;
      }
    }
//    dStack.showStructure();
  }
  if (dStack.isEmpty())
  {
    return 1;
  }
}
