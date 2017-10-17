#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <list>
#include <iterator>
#include <vector>

using namespace std;

typedef struct ChainHashTable {
	list<int> chain;
}ChainHashTable;

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Error: include the name of the input file as an argument\n");
		return 0;
	}

	printf("Attempting to open file %s\n", argv[1]);
	//FILE *f = fopen(argv[1], "r");
	//printf("The file is now open for reading\n");
	//printf("Attempting to read an integer value from the file\n");
	
	ifstream inputFile;
	inputFile.open(argv[1], ios::in);


	//p = size of hash table
	//n = number of keys to be inserted
	//k1 = key to search for after all keys are inserted
	int p, n, k1;

	//a = used in linear hashing
	float a;

	inputFile >> p;
	inputFile >> a;
	inputFile >> n;
	printf("The value of p is %d\n", p);//for testing to be deleted
	printf("The value of a is %f\n", a);//for testing
	printf("The value of n is %d\n", n);//for testing

	//keys will be my array of size of n that contains the keys
	int *keys = new int[n];

	//fill the array with keys from file
	for (int i = 0; i < n; i++) {
		inputFile >> keys[i];
	}

	//and finally assign the last line in the file to k1
	inputFile >> k1;
	
	printf("The value of k1 is %d\n", k1);//for testing 
	for (int i = 0; i < n; i++) {
		cout << keys[i] << " ";			//for testing
	}
	cout << endl;

	//close the file
	inputFile.close();

	/////////////CHAIN/////////////////

	//create chained hash
	vector<ChainHashTable> ht(p);
	for (int i = 0; i < n; i++) {
		int k = keys[i] % p;
		ht[k].chain.push_front(keys[i]);
	}
	

	for (int i = 0; i < n; i++) {
		cout << i << ":      ";
		std::copy(begin(ht[i].chain), std::end(ht[i].chain), std::ostream_iterator<int>(std::cout, " "));
		cout << endl;
	}

	//find slot that contains k1 and print it out
	int target = k1 % p;
	list<int>::iterator myIter;
	for (myIter = ht[target].chain.begin(); myIter != ht[target].chain.end(); myIter++) {
		if (*myIter == k1) {
			cout << target << endl;
		}
	}


	/////////////Linear///////////////
	vector<ChainHashTable> linearT(p);
	


	//std::copy(begin(ht[3].chain), std::end(ht[3].chain), std::ostream_iterator<int>(std::cout, " "));
	
	//fscanf(f, "%d", &number);
	//printf("Read number %d from the file\n", number);
	//fclose(f);
	//printf("The file is now closed\n");
	getchar();//delete.  For use in Visual Studio only
	return 0;



}