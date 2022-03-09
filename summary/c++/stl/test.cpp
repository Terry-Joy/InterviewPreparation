#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<map>
#include<set>
#include<exception>

int ans() {
	try {
		int a = 5, c = 3;
		return a + c;
	} catch(std::exception e) {

	}
}
int main() {	
	std::cout << ans();
	return 0;
}