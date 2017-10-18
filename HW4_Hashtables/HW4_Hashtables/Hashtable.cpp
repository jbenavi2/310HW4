#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <list>
#include <iterator>
#include <vector>
#include <math.h>
#include <iomanip>

//using namespace std;

typedef struct ChainHashTable {
	std::list<int> chain;
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
	
	std::ifstream inputFile;
	inputFile.open(argv[1], std::ios::in);


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
		std::cout << keys[i] << " ";			//for testing
	}
	std::cout << std::endl;

	//close the file
	inputFile.close();

	/////////////CHAIN/////////////////
	std::list<int>::iterator myIter;

	//create chained hash
	std::vector<ChainHashTable> ht(p);
	for (int i = 0; i < n; i++) {
		int k = keys[i] % p;
		ht[k].chain.push_front(keys[i]);
	}
	
	for (int i = 0; i < n; i++) {
		std::cout << std::setfill(' ') << std::setw(3) << i;
		std::cout << ":    ";
		copy(ht[i].chain.begin(), ht[i].chain.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}


	//for (int i = 0; i < n; i++) {
	//	std::cout << std::setfill(' ') << std::setw(3) << i;
	//	std::cout << ":    ";
	//	copy(begin(ht[i].chain), end(ht[i].chain), std::ostream_iterator<int>(std::cout, " "));
	//	std::cout << std::endl;
	//}

	//open output file.  name it chain.txt
	std::ofstream chainOutputFile;
	chainOutputFile.open("chain.txt");

	//write ht to output file.
	for (int i = 0; i < n; i++) {
		chainOutputFile << std::setfill(' ') << std::setw(3) << i;
		chainOutputFile << ":    ";
		copy(ht[i].chain.begin(), ht[i].chain.end(), std::ostream_iterator<int>(chainOutputFile, " "));
		chainOutputFile << std::endl;
	}

	//find slot that contains k1 and print it out and write it to output file
	int target = k1 % p;
	//std::list<int>::iterator myIter;
	for (myIter = ht[target].chain.begin(); myIter != ht[target].chain.end(); myIter++) {
		if (*myIter == k1) {
			chainOutputFile << target << std::endl;
			std::cout << target << std::endl << std::endl << std::endl;
		}
	}

	//close the output file
	chainOutputFile.close();


	/////////////Linear///////////////
	//array that contains my hash table of size p
	int *linearT = new int[p];
	const int NIL = -1;
	//cout << "size of linearT is  " << sizeof(linearT) << endl;  //doesn't work with dynamic allocation
	
	//fill linearT with NIL to indicate empty spot
	for (int i = 0; i < p; i++) {
		linearT[i] = NIL;
	}
	//memset(linearT, NIL, sizeof(linearT)); //doesn't work for dynamic allocation

	
	//insert
	int i = 0;	//starting point of my keys at index 0
	do {
		int j = 0; //starting point of hash table
		int h_prime_k = floor(p*(fmodf((a*keys[i]), 1.0)));	// h'(k) = p((a * k) mod 1)
		//int hki = (h_prime_k + j) % p;					
		do {
			int hki = (h_prime_k + j) % p;					// h(k,i) = (h'(k) + i) mod p
			if (linearT[hki] == NIL) {			//if the spot is emtpy
				linearT[hki] = keys[i];			//insert key
				break;
			}
			else
				j++;				//spot not empty go to next spot
		} while (j != p);
		i++;				//go to next key
	} while (i != n);
	

	for (int i = 0; i < p; i++) {			//for testing to see what the array gets filled with.  to be deleted
		std::cout << std::setfill(' ') << std::setw(3) << i;
		std::cout << ":    ";
		std::cout << linearT[i] << std::endl;
		}

	//open output file.  name it linear.txt
	std::ofstream linearOutputFile;
	linearOutputFile.open("linear.txt");

	//write linearT to output file.
	for (int i = 0; i < p; i++) {
		linearOutputFile << std::setfill(' ') << std::setw(3) << i;
		linearOutputFile << ":    ";
		linearOutputFile << linearT[i] << std::endl;
	}

	//search linear	and write sequence of probes to output file
	int j = 0;
	int h_prime_k = floor(p*(fmodf((a*k1), 1.0)));
	int spot;
	do {
		int hki = (h_prime_k + j) % p;
		spot = hki;
		if (linearT[hki] == k1) {
			linearOutputFile << spot << std::endl;
			std::cout << spot << std::endl << std::endl;
			break;
		}
		else if(linearT[hki] != NIL){
			linearOutputFile << spot << " ";
			std::cout << spot << " ";
			//j++;
		}
		j++;
	} while (linearT[spot] != NIL && j != p);

	//close the output file.
	linearOutputFile.close();

	///////////////Double//////////////////////

	//array that contains my hash table of size p
	int *doubleT = new int[p];

	//fill doubleT with NIL to indicate empty spot
	for (int i = 0; i < p; i++) {
		doubleT[i] = NIL;
	}
	
	int k = 0;		//starting point of keys from index 0
	do {
		int j = 0;
		int h1 = keys[k] % p;
		int h2 = 1 + (keys[k] % (p - 2));
		do {
			int hki = (h1 + j*h2) % p;
			if (doubleT[hki] == NIL) {
				doubleT[hki] = keys[k];
				break;
			}
			else
				j++;
		} while (j != p);
		k++;
	} while (k != n);

	for (int i = 0; i < p; i++) {
		std::cout << std::setfill(' ') << std::setw(3) << i;
		std::cout << ":    ";
		std::cout << doubleT[i] << std::endl;
	}
	
	//open output file.  name it double.txt.
	std::ofstream doubleOutputFile;
	doubleOutputFile.open("double.txt");

	//write doubleT to output file.
	for (int i = 0; i < p; i++) {
		doubleOutputFile << std::setfill(' ') << std::setw(3) << i;
		doubleOutputFile << ":    ";
		doubleOutputFile << doubleT[i] << std::endl;
	}

	//search double and write sequence of probes to output file
	j = 0;
	int h1 = k1 % p;
	int h2 = 1 + (k1 % (p - 2));
	int doubleSpot;
	do {
		int hki = (h1 + j*h2) % p;
		doubleSpot = hki;
		if (doubleT[hki] == k1) {
			doubleOutputFile << doubleSpot << std::endl;
			std::cout << doubleSpot << std::endl << std::endl;
			break;
		}
		else if (doubleT[hki] != NIL) {
			doubleOutputFile << doubleSpot << " ";
			std::cout << doubleSpot << " ";
		}
		j++;
	} while (doubleT[doubleSpot] != NIL && j != p);

	//close the output file.
	doubleOutputFile.close();


	//std::copy(begin(ht[3].chain), std::end(ht[3].chain), std::ostream_iterator<int>(std::cout, " "));
	
	//fscanf(f, "%d", &number);
	//printf("Read number %d from the file\n", number);
	//fclose(f);
	//printf("The file is now closed\n");
	getchar();//delete.  For use in Visual Studio only
	return 0;



}