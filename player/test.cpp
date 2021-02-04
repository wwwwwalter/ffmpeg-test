#include <iostream>

using namespace std;


typedef struct funs {
	int(*p1)(int a);
	int(*p2)(int a, int b);
}FUNS;


int fun1(int a) {
	cout << a << endl;
	return a;
}

int fun2(int a, int b) {
	cout << a << "," << b << endl;
	return a;
}

int main_test(void) {

	FUNS funs = {
		fun1,
	    fun2,
	};

	funs.p1(10);
	funs.p2(1, 2);

	int a = 1 << 2;

	cout << a << endl;

	return 0;
}