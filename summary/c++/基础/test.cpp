#include<iostream>
#include<cstdlib>
#include "a.h"
using namespace std;
// typedef int* ii;
#define ii int*
void F() { 
}
void F2() {
	typedef long long ll;
	cout << (ll)5;
}
int main() {
	int * p = (int *)malloc(sizeof(int) * 5);
	return 0;
}
