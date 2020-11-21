// Filename: bst.cpp
// 
// Contains the class AVL which represents an AVL tree. Contains implementations of insert, find, and range
// 
// C. Seshadhri, Jan 2020
// 
// Nick Kornienko Nov 2020

#include "avl.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// rotate with left, return new root node 
Node* AVL::rotateLeft(Node* node)
{
	// store some nodes
	Node* temp = node->right;
	Node* nodeParent = node->parent;
	Node* tempLeft = temp->left;

	// store sub-tree sizes
	// subTree(node->left) + subTree(temp->left);	
	int nodeSize = (!node->left ? 0 : subTree(node->left) + 1) + (!temp->left ? 0 : subTree(temp->left) + 1); // subTree doesn't count itself :/
	int tempSize = subTree(node);

	// rotate
	node->right = temp->left;
	temp->left = node;

	// update parents
	temp->parent = nodeParent;
	node->parent = temp;
	if (tempLeft)
		tempLeft->parent = node;

	// update subtree sizes
	node->subtreeSize = nodeSize;
	temp->subtreeSize = tempSize;

	// update height
	node->height = max(height(node->left), height(node->right)) + 1;
	temp->height = max(height(node->right), height(node)) + 1;

	return temp;
}

// rotate with right, return new root node
Node* AVL::rotateRight(Node* node)
{
	// store some nodes
	Node* temp = node->left;
	Node* nodeParent = node->parent;
	Node* tempRight = temp->right;

	// store sub-tree sizes
	// subTree(node->right) + subTree(temp->right);	
	int nodeSize = (!node->right ? 0 : subTree(node->right) + 1) + (!temp->right ? 0 : subTree(temp->right) + 1); // subTree doesn't count itself :/
	int tempSize = subTree(node);

	// rotate
	node->left = temp->right;
	temp->right = node;

	// update parents
	temp->parent = nodeParent;
	node->parent = temp;
	if (tempRight)
		tempRight->parent = node;

	// update subtree sizes
	node->subtreeSize = nodeSize;
	temp->subtreeSize = tempSize;

	// update height
	node->height = max(height(node->left), height(node->right)) + 1;
	temp->height = max(height(node->right), height(node)) + 1;

	return temp;
}

// returns the height or 0 if the node is null(prevents nullptr)
int AVL::height(Node* node)
{
	return !node ? 0 : node->height;
}

// returns the balance factor of the node as an int
int AVL::balance(Node* node)
{
	return !node ? 0 : height(node->left) - height(node->right);
}

// returns subtree size(prevents nullptr)
int AVL::subTree(Node* node)
{
	return !node ? 0 : node->subtreeSize;
}

// Default constructor sets head and tail to null
AVL::AVL()
{
	root = NULL;
}

// Insert(string val): Inserts the string val into tree, at the head of the list. Just calls the recursive function
// Input: string to insert into the BST
// Output: Void, just inserts new Node
void AVL::insert(string val)
{
	root = insert(root, nullptr, val); // make call to recursive insert, starting from root
	return;
}

// insert(Node* start, Node* to_insert): Recursive insert that maintains a self-balancing tree
// Input: string to insert into the subtree
// Output: Node* new root node
Node* AVL::insert(Node* start, Node* parent, string val)
{
	// base case, insert here
	if (!start)
	{
		Node* node = new Node(val);
		node->parent = parent;
		return node;
	}

	start->subtreeSize++; // node will be inserted below here, increment subtree size along the path

	// inserted node has smaller key, insert in left sub-tree
	if (val < start->key)
		start->left = insert(start->left, start, val);
	// inserted node has larger key, insert in the right sub-tree
	else
		start->right = insert(start->right, start, val);

	start->height = max(height(start->left), height(start->right)) + 1; // update height

	// rebalance if needed
	if (balance(start) > 1)
	{
		if (val < start->left->key) // left left
		{
			return rotateRight(start);
		}
		else // left right
		{
			start->left = rotateLeft(start->left);
			return rotateRight(start);
		}
	}
	if (balance(start) < -1)
	{
		if (val > start->right->key) // right right
		{
			return rotateLeft(start);
		}
		else // right left
		{
			start->right = rotateRight(start->right);
			return rotateLeft(start);
		}
	}
	return start;
}

// returns number of nodes between two strings, just calls its recursive function
int AVL::range(string str1, string str2)
{
	return range(root, str1, str2);
}

// recursive workhorse
int AVL::range(Node* node, string str1, string str2)
{
	// base case, no more nodes on this path
	if (!node)
		return 0;

	int subtree = 0;
	// on a valid path
	if (node->key >= str1 && node->key <= str2)
	{
		if (node->parent) // not at the root
		{
			if (node->key > node->parent->key) // if the child is greater than parent, left sub-tree of child is between parent and child
			{
				subtree = 0;
				if (node->key > str1) // add in left sub-tree as long as its values are greater than str1
					subtree = !node->left ? 0 : subTree(node->left) + 1;
				return 1 +
					subtree +
					range(node->right, str1, str2);
			}
			else // if the child is less than the parent, right sub-tree is between parent and child
			{
				subtree = 0;
				if (node->key < str2) // add in right sub-tree as long as its values are less than str2
					subtree = !node->right ? 0 : subTree(node->right) + 1;
				return 1 +
					range(node->left, str1, str2) +
					subtree;
			}
		}
		else // at the root, have to check both sub-trees
		{
			return 1 +
				range(node->left, str1, str2) +
				range(node->right, str1, str2);
		}
	}
	if (node->key < str1) // go right
	{
		return range(node->right, str1, str2);
	}
	return range(node->left, str1, str2); // go left
}

// Prints tree Preorder. Calls the recursive function from the root
// Input: None
// Output: string that has all elements of the tree pre order
string AVL::printPreOrder()
{
	return printPreOrder(root);
}

// Prints rooted subtree tree preorder, by making recursive calls
// Input: None
// Output: string that has all elements of the rooted tree preorder
string AVL::printPreOrder(Node* start)
{
	if (start == NULL) // base case
		return ""; // return empty string
	string leftpart = printPreOrder(start->left);
	string rightpart = printPreOrder(start->right);
	string output = start->key;
	if (leftpart.length() != 0) // left part is empty
		output = output + " " + leftpart; // append left part
	if (rightpart.length() != 0) // right part in empty
		output = output + " " + rightpart; // append right part
	return output;
}