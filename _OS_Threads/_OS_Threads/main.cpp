#include "iostream"
#include "thread"
#include "conio.h"

using namespace std;

class Res {
public:
	int y1;
	int y2;
};

void Y1(Res * Obj, int a, int x) {

	cout << "Thread 1 number: " << this_thread::get_id() << '\n';

	if (x < 2) {
		Obj->y1 = 2 - x;
	}

	if (a >= 2) {
		Obj->y1 = a + 3;
	}

}

void Y2(Res * Obj, int a, int x) {

	cout << "Thread 2 number: " << this_thread::get_id() << '\n';

	if (x < a) {
		Obj->y2 = a - 1;
	}

	if (a <= x) {
		Obj->y2 = a * x - 1;
	}

}


int main() {

	Res * Obj = new Res;
	int a, x;

	cin >> a >> x;

	thread Thread1(Y1, Obj, a, x); Thread1.join();
	thread Thread2(Y2, Obj, a, x); Thread2.join();

	cout << "Result: " << Obj->y1 + Obj->y2;

	_getch();

}