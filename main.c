#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void main(void) {
	char username[256];
	long code = 0;

	printf("::: CrackMe#1 by Pride.exe keygen by skynetuniverse @ 2009 :::\n\n\n");

	printf("User: ");

	scanf("%s",&username);

	code = (strlen(username) + 0x0CA) ^ 0x3d8d40f;

	printf("\nSerial Number is : %d", code);

	printf("\n\n");

	system("pause");

}
