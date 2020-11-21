#pragma once
// Filename: avl.h
// 
// Header file for the class AVL that represents an AVL tree
// 
// C. Seshadhri, Jan 2020
// 
// Nick Kornienko Nov 2020

#ifndef AVL_H
#define AVL_H

#include <string>

using namespace std;

// node struct to hold data
class Node
{
public:
	string key;
	int height, subtreeSize;
	Node* left, * right, * parent;

	Node() // default constructor
	{
		height = 0;
		subtreeSize = 0;
		left = right = parent = NULL; // setting everything to NULL
	}

	Node(string val) // constructor that sets key to val
	{
		key = val;
		height = 1;
		subtreeSize = 0;
		left = right = parent = NULL; // setting everything to NULL
	}
};

class AVL
{
private:
	Node* root; // Stores root of tree

	Node* rotateLeft(Node*); // left rotation utility
	Node* rotateRight(Node*); // right rotation utility
	int height(Node*); // height utility to prevent nullptr
	int balance(Node*); // balance utility
	int subTree(Node*); // subtreeSize utility to prevent nullptr
public:
	AVL(); // Default constructor sets root to null
	void insert(string); // insert string into list 
	Node* insert(Node*, Node*, string); // recursive version that inserts a node
	string printPreOrder(); // Construct string with tree printed PreOrder
	string printPreOrder(Node* start); // Construct string with rooted subtree printed PreOrder

	int range(string, string); // finds the number of nodes between two values
	int range(Node*, string, string); // recursive workhorse for range
};

#endif