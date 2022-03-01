#include <iostream>
#include <stdio.h>
using namespace std;
struct A{
	int a;
};
struct B {
	int b;
	B(int x = 0) : b(x) {} 
};
class C {
pu
	int x;
};
int main()
{
	C c = {5};
	return 0;
}