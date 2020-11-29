#include "postfix.h"
#include "stack.h"

bool TPostfix::isCorrect(string str)
{
	string unacceptable = "!@#^&.,<>{}[]|=_?";
	int count = 0, k = 0, countOperation = 0, length = str.length();
	if ((operands.find(str[0]) != string::npos) || (operands.find(str[length - 1]) != string::npos))
		return false;
	for (int i = 0; i < length; i++)
	{
		if (unacceptable.find(str[i]) != string::npos)
			return false;
		if (str[i] == '(')
			count++;
		if (str[i] == ')')
			count--;
		if ((str[i] - 'a' >= 0) && (str[i] - 'a' <= 26))
			k++;
		else
			k = 0;
		if (operands.find(str[i]) != string::npos)
			countOperation++;
		else
			countOperation = 0;
		if ((k > 1) || (countOperation > 1))
			return false;
	}
	if (count != 0)
		return false;
	return true;
}

string TPostfix::ToPostfix()
{
	TStack<char> opStack(MaxStackSize);
	string tmp = "+-*/()";
	int length = infix.length();
	for (int i = 0; i < length; i++)
	{
		if (tmp.find(infix[i]) == string::npos)
			postfix += infix[i];
		if ((infix[i] >= '0') && (infix[i] <= '9'))
			if (i != length)
			{
				if ((infix[i + 1] < '0') || (infix[i + 1] > '9'))
					postfix += '>';
			}
			else
				postfix += '>';
		if (infix[i] == '(')
			opStack.push(infix[i]);
		if (infix[i] == ')')
		{
			char temp = opStack.pop();
			while (temp != '(')
			{
				postfix += temp;
				temp = opStack.pop();
			}
		}
		if (operands.find(infix[i]) != string::npos)
		{
			if (opStack.empty())
				opStack.push(infix[i]);
			else
			{
				int index2 = operands.find(infix[i]);
				while (!opStack.empty())
				{
					char temp = opStack.pop();
					if (temp == '(')
					{
						opStack.push(temp);
						break;
					}
					int index1 = operands.find(temp);
					if (priority[index2] <= priority[index1])
						postfix += temp;
					else
					{
						opStack.push(temp);
						break;
					}
				}
				opStack.push(infix[i]);
			}
		}
	}
	while (!opStack.empty())
	{
		postfix += opStack.pop();
	}
	return postfix;
}

double TPostfix::Calculate()
{
    if (postfix.length() == 0) ToPostfix();
	int length = postfix.length();
	TStack<double> res(MaxStackSize);
	string nameValues;
	double *values = new double[length];
	for (int i = 0; i < length; i++)
	{
		if (operands.find(postfix[i]) == string::npos)
		{
			double p;
			if ((postfix[i] < 48) || (postfix[i] > 57))
			{
				if (nameValues.find(postfix[i]) == string::npos)
				{
					nameValues += postfix[i];
					cout << "Введите значение переменной - " << postfix[i] << endl;
					cin >> p;
					values[nameValues.length() - 1] = p;
				}
				else
				{
					p = values[nameValues.find(postfix[i])];
				}
				//res.push(p);
			}
			else
			{
				string number;
				while (postfix[i] != '>')
				{
					number += postfix[i];
					i++;
				}
				p = stoi(number);
			}
			res.push(p);
		}
		else
		{
			double val1, val2, val3;
			val2 = res.pop();
			val1 = res.pop();
			switch (postfix[i])
			{
			case '+': val3 = val1 + val2; break;
			case '-': val3 = val1 - val2; break;
			case '*': val3 = val1 * val2; break;
			case '/': val3 = val1 / val2; break;
			}
			res.push(val3);
		}
	}
	delete[] values;
	return res.pop();
}