#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define BUFSIZE 32

// unused...?
void hack() {
	printf("you've been hacked!\n");
	exit(0);
}

void foo() {
    // stack allocate some variables
    const int fav_number = 12; // your favorite number is a constant so it can't change
    char buf[BUFSIZE];

    // print favorite number
	printf("My favorite number is %d and it will always be %d and nothing can change that\n", fav_number, fav_number);

    // get a string from stdin
    gets(buf);

    // print favorite number again bc its a great number and you want the world to know
    printf("My favorite number is %d and it will always be %d and nothing can change that\n", fav_number, fav_number);

}

int main(int argc, char **argv) {

    foo();

    printf("Returned to main safe and sound\n");

    return 0;
}
