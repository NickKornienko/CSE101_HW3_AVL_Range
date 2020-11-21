//// Filename: wordrange.cpp
//// 
//// Solution for the Range Searching with AVL Trees
//// 
//// Nick Kornienko Nov 12, 2020
//
//#include "bst.h"
//#include <iostream>
//#include <stack>
//#include <fstream>
//#include <array>
//#include <sstream>
//#include <vector>
//#include <list>
//#include <regex>
//
//using namespace std;
//
//// function declarations
//
//int main()
//{
//	ifstream input; // stream for input file
//	ofstream output; // stream for output file
//
//	input.open("input.txt"); // open input file
//	output.open("output.txt"); // open output file
//
//	BST myBST;
//
//	string line;
//	while (getline(input, line))
//	{
//		istringstream ss(line);
//		vector<string> inputs;
//
//		// delimit by whitespace, push each entry into a vector
//		for (string input; getline(ss, input, ' ');
//			inputs.push_back(input));
//
//		if (inputs[0] == "i") // insert the string (will ignore duplicates)
//			myBST.insert(inputs[1]);
//		else if (inputs[0] == "r") // count number of strings between str1, str2
//			output << myBST.countStr(inputs[1], inputs[2]) << endl;
//	}
//	input.close();
//	output.close();
//}
