// Filename: wordrange.cpp
// 
// Solution for the Range Searching with AVL Trees
// 
// Nick Kornienko Nov 2020

#include "avl.h"
#include <iostream>
#include <stack>
#include <fstream>
#include <array>
#include <sstream>
#include <vector>

using namespace std;

// function declarations

int main()
{
	ifstream input; // stream for input file
	ofstream output; // stream for output file

	input.open("input.txt"); // open input file
	output.open("output.txt"); // open output file

	AVL myAVL;

	string line;
	while (getline(input, line))
	{
		istringstream ss(line);
		vector<string> inputs;

		// delimit by whitespace, push each entry into a vector
		for (string input; getline(ss, input, ' ');
			inputs.push_back(input));

		if (inputs[0] == "i") // insert the string
			myAVL.insert(inputs[1]);
		if (inputs[0] == "r") // count number of strings between str1, str2
		{
			output << myAVL.range(inputs[1], inputs[2]) << endl;
		}		
	}
	input.close();
	output.close();
}
