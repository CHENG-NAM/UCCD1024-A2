#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


// Question 1
bool BST::duplicateInsert(BTNode* cur, int item)
{
	if (cur == NULL)
	{
		return false;
	}

	if (cur->item.id == item)
	{
		return true;
	}

	if (duplicateInsert(cur->left, item))
	{
		return true;
	}

	return duplicateInsert(cur->right, item);
}

// Question (b)
// Finds and prints all the nodes at the deepest level
bool BST::deepestNodes() {
	if (empty()) {
		cout << "The binary search tree is empty. Please read file first." << endl;
		return false;
	}

	int depth = height(root);		// 
	cout << "The deepest nodes of t1 --> ";
	printDeepestNodes(root, 1, depth); 
	cout << endl;
	return true;
}

// Sub-function to get the height of the tree
int BST::height(BTNode* root) {
	if (root == NULL) {
		return 0;
	}
	else {
		// Compute the height of each subtree
		int left_Height = height(root->left);
		int right_Height = height(root->right);

		// Use the larger one
		if (left_Height > right_Height) {
			return(left_Height + 1);
		}
		else {
			return(right_Height + 1);
		}
	}
}

// Sub-function to print nodes at the deepest level
void BST::printDeepestNodes(BTNode* node, int level, int height) {
	if (node == NULL) return; // base case

	if (level == height) { // base case
		// Assuming the student ID is stored in the item.id field
		cout << node->item.id << "\t";
		return;
	}

	printDeepestNodes(node->left, level + 1, height);
	printDeepestNodes(node->right, level + 1, height);
}


// Question (c)
// Traverses a BST tree recursively and print the content of every node 
bool BST::display(int source, int order) {
	if (empty())
	{
		cout << "The binary search tree is empty. Please read file first." << endl;
		return false;
	}
	
	if (source == 1)
	{
		if (order == 1) {  // Print in ascending order
			inOrderPrint();
			return true;
		}
		else if (order == 2) {  // Print in descending order
			inOrderPrintDesc();
			return true;
		}
	}
	else if (source == 2) {
		ofstream outputFile("student-info.txt", ios::trunc);

		if (order == 1) 
		{
			inOrderPrintFile(); // Write to the file in ascending order
			cout << endl;  
			cout << "Student Informations successfully inserted into text file by ASCENDING OREDER." << endl;
			return true;
		}
		else if (order == 2) 
		{
			inOrderPrintFileDesc(); // Write to the file in descending order
			cout << endl;
			cout << "Student Information successfully inserted into text file by DESCENDING ORDER." << endl;
			return true;
		}
		outputFile.close();
	}
	return true;
}


void BST::inOrderPrintDesc() 
{
	if (root == NULL) return;  // special case
	else inOrderPrintDesc2(root);  // normal case
	cout << endl;
}

void BST::inOrderPrintDesc2(BTNode* cur) 
{
	if (cur == NULL) return;		// base case
	inOrderPrintDesc2(cur->right); // recursively process right subtree
	cur->item.print(cout);		// Print current node's data
	inOrderPrintDesc2(cur->left);	// recursively process left subtree
}

void BST::inOrderPrintFile()
{
	if (root == NULL) return;       // special case
	else inOrderPrintFile2(root);	// normal case
	cout << endl;
}

void BST::inOrderPrintFile2(BTNode* cur)
{
	if (cur == NULL) return;		// bases case
	inOrderPrintFile2(cur->left);	// recursive case
	cur->item.printstudent();
	inOrderPrintFile2(cur->right);	// recursive case

}

void BST::inOrderPrintFileDesc()
{
	if (root == NULL) return;
	else inOrderPrintFileDesc2(root);
	cout << endl;
}

void BST::inOrderPrintFileDesc2(BTNode* cur)
{
	if (cur == NULL) return;
	inOrderPrintFileDesc2(cur->right);
	cur->item.printstudent();
	inOrderPrintFileDesc2(cur->left);

}


// Question (d)
// Clone a subtree in t1 where the root of the subtree contain value item
bool BST::CloneSubtree(BST t1, type item) {
	if (t1.empty()) {
		cout << "The BST is an empty tree" << endl;
		return false;
	}

	// Define a pointer to hold the node we are looking to clone.
	BTNode* targetNode = NULL;

	// Check if  the item exists in the tree.
	if (!searchCloneNode(t1.root, item, targetNode)) {
		cout << "Item not found for cloning." << endl;
		return false;
	}

	// Use a queue to help in the rooted at targetNode.
	Queue q;
	cloneSubtreeRecursive(targetNode, q);

	//Traverse through the queue and insert the items the new tree.
	while (!q.empty()) {
		BTNode* cur;
		q.dequeue(cur);
		insert(cur->item);
	}

	return true;
}


// Sub-function to search for the current item.
bool BST::searchCloneNode(BTNode* cur, type item, BTNode*& targetNode) {
	if (cur == NULL) return false;

	if (cur->item.id == item.id) {
		targetNode = cur;
		return true;
	}

	return searchCloneNode(cur->left, item, targetNode) || searchCloneNode(cur->right, item, targetNode);
}

// Sub-function to traverse all the children of the selected nodes
void BST::cloneSubtreeRecursive(BTNode* cur, Queue& q) {
	if (cur == NULL) return;

	q.enqueue(cur);
	cloneSubtreeRecursive(cur->left, q);
	cloneSubtreeRecursive(cur->right, q);
}

// Question (e)
// Print nodes according to level in a BST
bool BST::printLevelNodes() {
	BTNode* currentNode = root;
	if (empty())
	{
		cout << "\n The binary search tree is empty." << endl;
		cout << endl;
		return false;
	}

	//Initialize a queue for level order traversal
	Queue q;
	q.enqueue(currentNode);

	int currentLevelCount = 1; // Number of nodes at the current level
	int nextLevelCount = 0;		// Number of nodes at the next level
	int level = 1; //Start with root level

	cout << "Level " << level << " nodes: ";
	while (!q.empty()) {
		q.dequeue(currentNode);
		currentLevelCount--;

		// Print the student ID
		cout << currentNode->item.id << " ";

		if (currentNode->left != NULL) {
			q.enqueue(currentNode->left);
			nextLevelCount++;
		}
		if (currentNode->right != NULL) {
			q.enqueue(currentNode->right);
			nextLevelCount++;
		}
		if (currentLevelCount == 0) {
			cout << endl;

			if (!q.empty())
			{
				level++;
				cout << "Level " << level << " nodes: ";
			}
			currentLevelCount = nextLevelCount; // Update count for the current level
			nextLevelCount = 0;
		}
	}
	return true;
}

//Question (f)
// Print all the external path in a BST
bool BST::printPath()
{
	if (empty())
	{
		cout << "The binary search tree is empty. Please read File First." << endl;
		return false;
	}

	int pathNumber = 0;
	int path[1000];
	printPath2(root, path, 0, pathNumber);

	int totalPaths = countPaths(root);
	cout << "Total number of paths: " << totalPaths << endl;

	return true;
}

void BST::printPath2(BTNode* cur, int path[], int pathlength, int& pathNumber)
{
	if (cur == NULL)
	{
		return;
	}

	path[pathlength] = cur->item.id;
	pathlength++;

	if (cur->left == NULL && cur->right == NULL)
	{
		printPathArray(path, pathlength, pathNumber);
	}
	else
	{
		printPath2(cur->left, path, pathlength, pathNumber);
		printPath2(cur->right, path, pathlength, pathNumber);
	}
}

void BST::printPathArray(int path[], int length, int &pathNumber)
{
	pathNumber++;
	cout << "Path " << pathNumber << " --> ";
	int i = 0;
	while (i < length) {
		cout << path[i] << " ";
		i++;
	}

	cout << "[ Number of Node -->" << length << " ]" << endl;
	cout << endl;

}

int BST::countPaths(BTNode* node) {
	if (node == NULL)
		return 0;

	// Count paths for left and right children
	int leftPaths = countPaths(node->left);
	int rightPaths = countPaths(node->right);

	// If it's a leaf node, there's only one path (itself)
	if (node->left == NULL && node->right == NULL) {
		return 1;
	}

	// Total paths from current node is the sum of paths from left and right children
	return leftPaths + rightPaths;
}

