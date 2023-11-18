#include "arithmetic.h"



Arifm::Arifm(std::string s) : string(s)
{

}



void Arifm::Convert(std::string s)
{
	int size = s.size();
	std::string buff;
	Stack<Lexem> st;
	bool flag = 0;
	for (int i = 0; i < size; ++i)
	{
		//обработка числа
		buff = "";
		while (i < size && '0' <= s[i] && s[i] <= '9' || s[i] == '.')// это число
		{
			if (buff.size() == 0 && s[i] == '.')
				throw Error = { i,"Wrong Number" };
			buff += s[i++];
		}
		if (buff.size() != 0)
		{
			Lexem a;
			a.numb = stod(buff);
			a.numb *= (1 - 2 * flag);
			flag = 0;
			a.pos = i - 1;
			postfix.push_back(a);
		}
		if (i >= size)
			break;
		//---------------------------------------------------

		if (s[i] == '+' || s[i] == '*' || s[i] == '-' || s[i] == '/')
		{

			if (s[i] == '-' && (i==0 || s[i-1]=='('))//минус перед числом
			{
				flag=1;
				continue;
			}

			while (!st.isEmpty() && (st.Top().op == '*' || st.Top().op == '/'))
			{
				Lexem a = st.Top();
				st.pop();
				postfix.push_back(a);
			}
			Lexem a;
			a.op = s[i];
			a.isOp = 1;
			a.pos = i;
			st.push(a);
		}
		else if (s[i] == '(')
		{
			Lexem a;
			a.op = s[i];
			a.isOp = 1;
			a.pos = i;
			st.push(a);
		}
		else if (s[i] == ')')
		{
			while (!st.isEmpty() && st.Top().op != '(')
			{
				Lexem a = st.Top();
				st.pop();
				postfix.push_back(a);
			}
			if (st.isEmpty())//нет открывающей скобки
				throw Error = { i,"Bracket is missed" };
			else
				st.pop();
		}
		else //неопознанная лексема
		{
			throw Error = { i,"wrong lexem!" };
		}
	}
	while (!st.isEmpty())
	{
		Lexem a = st.Top();
		if (a.isOp && a.op == '(')
			throw Error = { a.pos,"Missing bracket" };
		st.pop();
		postfix.push_back(a);
	}
}

double Arifm::Calculate()
{

	Stack<double> st;
	for (Lexem el : postfix)
	{
		if (!el.isOp)
		{
			st.push(el.numb);
		}
		else
		{
			char symb = el.op;
			double num1;
			double num2;
			double itog;
			if (!st.isEmpty())
			{
				num1 = st.Top();
				st.pop();
			}
			else
			{
				throw Error = { el.pos,"Mising Number" };
			}

			if (!st.isEmpty())
			{
				num2 = st.Top();
				st.pop();
			}
			else
			{
				throw Error = { el.pos,"Mising Number" };
			}

			switch (symb)
			{
			case '+':
				itog = num1 + num2;
				break;
			case '-':
				itog = num2-num1;
				break;
			case '*':
				itog = num1 * num2;
				break;
			case '/':
				if (num1 == 0)
				{
					throw Error = { el.pos + 1,"Division by Zero!" };
				}
				itog = num2 / num1;
				break;
			}
			st.push(itog);
		}
	}
	double ans = st.Top();
	st.pop();
	if (!st.isEmpty())//Теоретически, этой ошибки быть не должно
		throw "Number Left";
	return ans;
}

// Второй флаг==-1 - ошибка
std::pair<double, int> Arifm::Execution()
{
	double x = 0;
	try
	{
		Convert(string);
		x = Calculate();
	}
	catch (std::pair<int, std::string> Error)
	{
		std::cout << "Error:" << Error.second << " on position:" << Error.first+1 << std::endl;
		return { -1,-1 };
	}
	return { x,0 };
}