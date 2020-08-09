#include <iostream>
#include <string>
#include<stack>
using namespace std;


//����һ��Stack
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







//���м���ĺ���
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
		   else cout << "��ĸ����Ϊ0" << endl;
		break;
	}
}


//�ж����ȼ����õ�����ĺ���
void do_command(Stack<double>& num, Stack<char>& ch) {
	string sentence;
	string s;
	int i = 0;
	double answer;
	string char_num = "";
	char sign;
	cout << "������Ҫ�����ʽ��" << endl;

	cin >> sentence;
	s = sentence;
	//��������ΪԤ��;

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
			//�õ�һ�����Ժ����ѹջ����
			num.push(atof(char_num.c_str()));



		}
		else
		{
			sign = sentence[i];
			i++;//�õ���һ���ַ��Ժ����ѹջ����
			ch.push(sign);

		}
		char_num = "";//���ҽ���������2���������ϲ��ܼ�������
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
			}//�õ�һ�����Ժ����ѹջ����
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
			default:cout << "��������" << endl; break;
			}//�˳�switch
		}//�˳�else
		char_num = "";


	}
	if (num.size() == 1 && ch.size() == 0) {
		num.top(answer);
		cout << "����ɹ�" << endl;
		cout << s << "�ļ�������" << answer << endl;

	}
	else {
		cout << "������������������һ����ȷ��ʽ��" << endl;

	}

}

//�ж��û��Ƿ���Ҫ��������ĺ���
bool yes_or_no() {
	cout << "��������Ҫ�����𣿼����Ļ�������y���������Ļ�������n��" << endl;
	string choice;
	cin >> choice;
	while (1) {
		if (choice == "Y" || choice == "y")
			return true;
		else if (choice == "N" || choice == "n")
			return false;
		else {
			cout << "�����˴����ѡ������������" << endl;
			cin >> choice;
		}

	}
}


//���ܳ���	      
void introduction() {
	cout << "����һ�����׼�����������������������������(1.2+1)*2=����ʽ���س������ֽ����" << endl;
	cout << "֧�ּӼ��˳����������㣬���������롰/����������ע��ҪΪӢ�ķ��ţ��������š�" << endl;
	cout << "֧��������С���Ļ�����㡣" << endl;
	
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