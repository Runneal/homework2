#include "Stack.h" 
#include <iostream>
using namespace std;

int main() {
    Stack<float> S;
	char Str[] = "1.2*3+(2+5)+3!-2^3+6/2-2.4/2";
	cout<<"运算结果："<<S.evaluate(Str)<<endl;
}
