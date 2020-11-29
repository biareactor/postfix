#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  double res;
  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  cin >> expression;
  cout << expression <<endl;
  try 
  {
	  TPostfix postfix(expression);
	  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	  postfix.ToPostfix();
	  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

	  res = postfix.Calculate();
	  cout << res << endl;
  }
  catch (const char* s)
  {
	  cout << s;
  }
  return 0;
}
