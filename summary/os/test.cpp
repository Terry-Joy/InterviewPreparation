#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
	pid_t pid = fork();
	pid = fork();
	if (!pid) {
		printf("son");
	} else if (pid > 0) {
		sleep(100000000);
		printf("fuqin");
	}
}