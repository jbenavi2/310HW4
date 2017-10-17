#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>

using namespace std;




int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Error: include the name of the input file as an argument\n");
		return 0;
	}

	printf("Attempting to open file %s\n", argv[1]);
	FILE *f = fopen(argv[1], "r");
	printf("The file is now open for reading\n");
	printf("Attempting to read an integer value from the file\n");
	int number;
	fscanf(f, "%d", &number);
	printf("Read number %d from the file\n", number);
	fclose(f);
	printf("The file is now close\n");
	return 0;



}