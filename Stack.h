#include "Vector.h"
#include <cstring>
#include <cmath>
#include <cstdio> 
#define N_OPTR 9
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;

const char pri[N_OPTR][N_OPTR] = {
/* + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
/* - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
/* * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
/* / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
/* ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
/* ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
/* ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
/* ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
/*\0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};
	

template <typename T> class Stack: public Vector<T> {

private:
	
	T* _elem;
	int _top;
	int _capacity;
	int _size;
    
	T calcu(T pOpnd1, char op, T pOpnd2) {
		switch(op) {
			case '+': return pOpnd1 + pOpnd2;
			case '-': return pOpnd1 - pOpnd2;
			case '*': return pOpnd1 * pOpnd2;
			case '/': return (pOpnd2 == 0) ? 0 : pOpnd1 / pOpnd2;
			case '^': return std::pow(pOpnd1, pOpnd2);
			default: std::exit(-1);
		}
	}

	T calcu(char op, T pOpnd) {
		switch(op) {
			case '!': {
				if (pOpnd == 0) return 1;
				float result = 1;
				for (int i = 1; i <= static_cast<int>(pOpnd); ++i) {
					result *= i;
				}
				return result;
			}
		}
	}

	char orderBetween(char a, char b) {
		return pri[getIndexOfOptr(a)][getIndexOfOptr(b)];
	}

	int getIndexOfOptr(char op) {
    	switch (op) {
        	case '+': return ADD;
        	case '-': return SUB;
        	case '*': return MUL;
        	case '/': return DIV;
        	case '^': return POW;
        	case '!': return FAC;
        	case '(': return L_P;
        	case ')': return R_P;
        	case '\0': return EOE;
    	}
	}
		
	float readNumber(char* &S, Stack<float> &opnd) {
		float x = 0.0;
		bool point=false;
		int i = 0;
		while (isdigit(*S)||*S=='.') {
			
			if (*S != '.') {
				if (point == false)
					x = x * 10 + (*(S++) - 48);
				if (point == true) { 
					x = x * 10 + (*(S++) - 48);
					i++; 
				}
			}
			else { S++; point = true; }
		}
		int temp = 1;
		for (int j = 0; j < i; j++) temp *= 10;
		x = x / temp;
		opnd.push(x);
		return x;
	}

public: 
    Stack(int capacity = DEFAULT_CAPACITY) {
        _elem = new T[capacity];
        _top = -1;
        _capacity = capacity;
        _size = 0;
    }
	Rank size() const {return _size;}
	void push(T const& e) { _size++;this->insert( size(), e); }
	
	T pop() {T A = this->remove ( size() ); _size--; return A; }
	
	T& top() { return (*this) [ size() ]; }

	bool empty() const { return Vector<T>::empty(); }

	float evaluate ( char* S ) { 
		Stack<float> opnd; Stack<char> optr; 
		// std::cout<<"声明成功"<<std::endl;
		optr[0] = '\0'; 
		while ( !optr.empty() || *S ) { 
			// std::cout<<"读入..."<<std::endl;
			if ( isdigit ( *S ) ) {
				// std::cout<<*S<<"是数字"<<std::endl;
				readNumber ( S, opnd );
				//append ( RPN, opnd.top() );
				// std::cout<<"当前栈内操作数个数："<<opnd.size()<<std::endl;
			}
			else {
				// std::cout<<*S<<"是运算符"<<std::endl;
				switch ( orderBetween ( optr.top(), *S ) ) { 
					case '<': 
						// std::cout<<"当前运算符"<<*S<<"比栈顶运算符"<<optr.top()<<"优先级低："<<std::endl;
						optr.push ( *S ); S++; 
						// std::cout<<"当前栈内运算符个数："<<optr.size()<<std::endl;
						// std::cout<<"当前栈顶运算符个数："<<optr.top()<<std::endl;
						break;
					case '=': 
						// std::cout<<"当前运算符"<<*S<<"与栈顶运算符"<<optr.top()<<"优先级相等："<<std::endl;
						optr.pop(); S++; 
						// std::cout<<"当前栈内运算符个数："<<optr.size()<<std::endl;
						// std::cout<<"当前栈顶运算符个数："<<optr.top()<<std::endl;
						break; 
					case '>': {
						// std::cout<<"当前运算符"<<*S<<"比栈顶运算符"<<optr.top()<<"优先级高："<<std::endl;
						char op = optr.pop(); //append ( RPN, op ); 
						if ( '!' == op ) {
							// std::cout<<"进行一元运算"<<std::endl;
 							float pOpnd = opnd.pop(); 
							opnd.push ( calcu ( op, pOpnd ) );
						}
						else {
							// std::cout<<"进行二元运算"<<std::endl;
							float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); 
							opnd.push ( calcu ( pOpnd1, op, pOpnd2 ) );
							// std::cout<<"运算结果："<<opnd.top()<<std::endl;
							// std::cout<<"运算后当前栈内运算符个数："<<optr.size()<<std::endl;
							// std::cout<<"当前栈顶运算符个数："<<optr.top()<<std::endl;
						}
						break;
					}
					default : std::exit ( -1 ); 
				}
			}
			if(optr.size() < 0)
				break;
		}
		float result = opnd.top();
		opnd.pop();
		return result;
	}
};
	/*
	void append(char*& p, T e) {
    	size_t n = std::strlen(p); // ��ǰ�ַ����ĳ���
    	char* buf = new char[n + 2]; // �����µĻ�����
    	memcpy(buf, p, n); // ����ԭ�����ַ���
    	buf[n] = e; // �����ַ�����ĩβ����Ԫ�� e
    	buf[n + 1] = '\0'; // ��֤���ַ����� \0 ��β
    	delete[] p; // �ͷ�ԭ���Ŀռ�
    	p = buf; // ����ָ��
	}
	*/
    // �ж�һ���ַ��Ƿ�������
    /*void push(T* elems, int n) { //��һ�������ڵ�Ԫ��һ������ջ������ĩβԪ��Ϊ��ջ�� 
        while (n-- > 0) 
            this->push(*elems++); 
    } */
    
	//T& peek() const { return (*this)[this->size() - 1]; } //ȡ������������������ĩԪ�أ����ϵ�pop����˼ʵ���ǻ��������壩 
    
	//const T& pop() { return (*this) [size() - 1]; } //����ȡ��const�� 
	/*
	void convert ( Stack<char>& S, long long n, int base ) { //ʮ������n��base���Ƶ�ת�� 
		static char digit[] //0 < n��1 < base <= 16���½����µ���λ���ţ�����base��ȡֵ��Χ�ʵ����� 
		= { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'A', 'B', 'C', 'D', 'E', 'F' };
		while ( n > 0) { //��һ������½����µĸ�λ�� 
			int remainder = ( int ) ( n % base ); S.push ( digit[remainder] ); //������ջ 
			n /= base; //n����Ϊ���base�ĳ��� 
		}
	} //�½������ɸߵ��͵ĸ���λ���Զ����±�����ջS�� 
	
	bool paren ( const char exp[] ) { //���ڱ���ʽexp��������ƥ���飬�ɼ���������� 
		Stack<char> S; //ʹ��ջ��¼�ѷ��ֵ���δƥ���������
		int lo = 0;
		int hi = (int)S.size(); 
		for ( int i = lo; i <= hi; i++ ) { //��һ��鵱ǰ�ַ� 
			switch ( exp[i] ) { //������ֱ�ӽ�ջ������������ջ��ʧ�������ʽ�ز�ƥ�� 
				case '(': case '[': case'{': S.push( exp[i] ); break;
				case ')': if ( ( S.empty() ) || ( '(' != S.pop() ) ) return false; break;
				case ']': if ( ( S.empty() ) || ( '[' != S.pop() ) ) return false; break;
				case '}': if ( ( S.empty() ) || ( '{' != S.pop() ) ) return false; break;
				default: break; //�������ַ����� 
			}
		}
		return S.empty(); //��������ʽɨ�����ջ�������в������������ţ���ƥ�䣻���򣨼�ջ�գ�����ƥ�� 
	}
	*/
	
    // ��һ��Ԫ�����ӵ��沨��ʽ����ʽ��ĩβ
    /* static void append( char*& rpn, char elem) {
        size_t n = std::strlen(rpn);
        char* newRpn = new char[n + 2];
        std::strcpy(newRpn, rpn);
        newRpn[n] = elem;
        newRpn[n + 1] = '\0';
        delete[] rpn;
        rpn = newRpn;
    } */
    /*
	void readNumber ( char* &p, Stack<float>& stk ) {
    	stk.push ( ( float ) ( *p - '0' ) );
    	while ( isdigit ( *++p ) ) 
        	stk.push ( stk.pop() * 10 + *p - '0' );
    	if ( '.' != *p ) return;
    	float fraction = 1; 
    	while ( isdigit ( *++p ) ) 
        	stk.push ( stk.pop() + ( *p - '0' ) * ( fraction /= 10 ) );
	}
    */
