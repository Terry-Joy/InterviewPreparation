#include<stdio.h>
#include<iostream>
struct
{
    int i;    
    char c1;  
    char c2;  
}x1;

struct{
    char c1;  
    int i;    
    char c2;  
}x2;

struct{
    char c1;  
    char c2; 
    int i;    
}x3;

int main()
{
	std::cout << sizeof(x1) << " " << sizeof(x2) << " " << sizeof(x3);
    return 0;
}