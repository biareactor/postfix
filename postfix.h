#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <iostream>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix;
  string postfix;
  string operands = "+-*/";
  //int arity[4] = { 2,2,2,2 };
  int priority[4] = { 1,1,2,2 };
  bool isCorrect(string str);
public:
  TPostfix(string inf = "a+b")
  {
	 if (!isCorrect(inf))
		  throw "Error";
	 for (int i = 0; i < inf.length(); i++)
	  if (inf[i] != ' ')
		 infix += inf[i];
	 if (infix.length() < 1)
		 throw "Error";
  }
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  string ToPostfix();
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
