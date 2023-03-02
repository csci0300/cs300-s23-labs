#include <stdio.h> 

void bar(int a) { 
    int b = 8; 
    printf("%d\n",a + b); 
}

void foo(int a) { 
    bar(a); 
}

int main() { 
    int a = 8;
    foo(a); 
}