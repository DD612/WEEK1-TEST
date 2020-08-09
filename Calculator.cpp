#include <iostream>
#include <string>
#include<stack>
using namespace std;


//定义一个Stack
enum Judgement { success, overflow, underflow };
const int MAXSIZE = 20;

template <class T> class Stack {
public:
	Stack();
	bool empty() const;
	bool full() const;
	int size() const;
	void clear();
	Judgement top(T& item) const;
	Judgement pop();
	Judgement push(const T& item);
private:
	int count;
	T entry[MAXSIZE];
};

template <class T> Stack<T>::Stack()
{
	count = 0;
}

template <class T> bool Stack<T>::empty() const
{
	return count == 0;
}

template <class T> bool Stack<T>::full() const
{
	return count == MAXSIZE;
}

template <class T> int Stack<T>::size() const
{
	return count;
}

template <class T> void Stack<T>::clear()
{
	count = 0;
}

template <class T> Judgement Stack<T>::top(T& item) const
{
	if (empty()) return underflow;
	item = entry[count - 1];
	return success;
}

template <class T> Judgement Stack<T>::pop()
{
	if (empty()) return underflow;
	count--;
	return success;
}

template <class T> Judgement Stack<T>::push(const T& item)
{
	if (full()) return overflow;
	entry[count++] = item;
	return success;
}







//进行计算的函数
void calculate(char s, Stack<double>& num)
{
	double a, b;
	num.top(b);
	num.pop();
	num.top(a);
	num.pop();
	switch (s) {
	case'+':num.push(a + b); break;
	case'-':num.push(a - b); break;
	case'*':num.push(a * b); break;
	case'/':if (b != 0.0) num.push(a / b);
		   else cout << "分母不能为0" << endl;
		break;
	}
}


//判断优先级，得到结果的函数
void do_command(Stack<double>& num, Stack<char>& ch) {
	string sentence;
	string s;
	int i = 0;
	double answer;
	string char_num = "";
	char sign;
	cout << "请输入要计算的式子" << endl;

	cin >> sentence;
	s = sentence;
	//接下来作为预读;

	while (1)
	{
		if (sentence[i] >= '0' && sentence[i] <= '9' || sentence[i] == '.')
		{
			char_num = char_num + sentence[i];
			i++;
			while (sentence[i] >= '0' && sentence[i] <= '9' || sentence[i] == '.')
			{
				char_num = char_num + sentence[i];
				i++;
			}
			//得到一个数以后进行压栈操作
			num.push(atof(char_num.c_str()));



		}
		else
		{
			sign = sentence[i];
			i++;//得到了一个字符以后进行压栈操作
			ch.push(sign);

		}
		char_num = "";//当且仅当读入了2个数字以上才能继续进行
		if (num.size() == 2)
			break;

	}
	while (sentence[i] != '\0') {
		if (sentence[i] >= '0' && sentence[i] <= '9' || sentence[i] == '.') {
			char_num = char_num + sentence[i];
			i++;
			while (sentence[i] >= '0' && sentence[i] <= '9' || sentence[i] == '.') {
				char_num = char_num + sentence[i];
				i++;
			}//得到一个数以后进行压栈操作
			num.push(atof(char_num.c_str()));
		}



		else
		{
			sign = sentence[i];

			i++;
			switch (sign) {
				char c;

			case'+':
			case'-':ch.top(c);
				if (c != '(')
				{
					calculate(c, num); ch.pop();
				}
				if (ch.size() == 0) { ch.push(sign); break; }
				ch.top(c);
				while (c == '+' || c == '-')
				{
					calculate(c, num); ch.pop();
					if (ch.size() >= 1)
						ch.top(c);
					else break;
				}
				ch.push(sign);
				break;
			case'*':
			case'/':if (ch.size() >= 1)ch.top(c); 
				   if (c == '*' || c == '/')
				   {
					   calculate(c, num); ch.pop();
				   }
				   ch.push(sign);
				   break;
			case'(':ch.push(sign);
				break;
			case')':ch.top(c);

				calculate(c, num);
				ch.pop();
				ch.top(c);
				if (c == '(') { ch.pop(); break; }
				else {
					while (c != '(') {
						calculate(c, num);
						ch.pop();
						if (ch.size() >= 1)ch.top(c); else break;
					}
				}
				if (c == '(')
					ch.pop();


				break;
			case'=':ch.top(c);
				if (c != '(')
				{
					calculate(c, num);
					ch.pop();
					while (ch.size() != 0) {
						ch.top(c);
						calculate(c, num);
						ch.pop();
					}
				}
				break;
			default:cout << "输入有误" << endl; break;
			}//退出switch
		}//退出else
		char_num = "";


	}
	if (num.size() == 1 && ch.size() == 0) {
		num.top(answer);
		cout << "计算成功" << endl;
		cout << s << "的计算结果是" << answer << endl;

	}
	else {
		cout << "输入有误，请重新输入一个正确的式子" << endl;

	}

}

//判断用户是否还是要继续计算的函数
bool yes_or_no() {
	cout << "请问您还要继续吗？继续的话，输入y。不继续的话，输入n。" << endl;
	string choice;
	cin >> choice;
	while (1) {
		if (choice == "Y" || choice == "y")
			return true;
		else if (choice == "N" || choice == "n")
			return false;
		else {
			cout << "输入了错误的选择，请重新输入" << endl;
			cin >> choice;
		}

	}
}


//介绍程序	      
void introduction() {
	cout << "这是一个简易计算器，请您在命令行输入类似于(1.2+1)*2=的算式，回车后会出现结果。" << endl;
	cout << "支持加减乘除四则混合运算，除号请输入“/”，符号请注意要为英文符号，包括括号。" << endl;
	cout << "支持整数和小数的混合运算。" << endl;
	
}






int main() {
	introduction();
	Stack<double>num_entry;
	Stack<char>ch_entry;
	do {
		num_entry.clear();
		num_entry.clear();
		do_command(num_entry, ch_entry);
	} while (yes_or_no());



	return 0;
}