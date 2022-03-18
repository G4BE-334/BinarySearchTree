#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct node {
	string data;
	node* left;
	node* right;
};

node* insert (node* nd, string data) {
	if (nd == NULL) {
		node* nd = new node;
		nd -> data = data;
		nd -> left = NULL;
		nd -> right = NULL;
		return nd;
	}
	else {
		if (data < nd->data) {
			nd -> left = insert(nd->left, data);
		}
		else if (data > nd->data) {
			nd -> right = insert(nd->right, data);
		}
		else {
			return nd;
		}
	}
	return nd;
};

bool search(node* nd, string target, int count) {
	count ++;
	if (nd == NULL){
		cout << "Inpescted " << count << " elements\n" << target << " not in tree" << endl;
		return false;
	}
	else {
		if (target == nd->data) {
			cout << "Inpescted " << count << " elements\n" << nd->data << " located in tree" << endl;
			return true;
		}
		else if (target < nd->data) {
			return search(nd->left, target, count);
		}
		else {
			return search(nd->right, target, count);
		}
	}
};

void display(node* temp) {
	if (temp == NULL) {
		return;
	}
	// Inorder display
	// LEFT -> PRINT -> RIGHT
	display(temp->left);
	cout << temp->data << " ";
	display(temp->right);
};

node* minVal(node* nd) {
	node* current = nd;
	while (current && current->left != NULL) {
		current = current->left;
	}
	return current;
};

node* deleteNode(node* root, string key) {
	if (root == NULL) {
		return root;
	}
	if (key < root->data) {
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->data) {
		root->right = deleteNode(root->right, key);
	}
	else {
		if (root->left == NULL) {
			node* temp = root->right;
			delete(root);
			return temp;
		}
		else if (root->right == NULL) {
			node * temp = root -> left;
			delete(root);
			return temp;
		}

		node* temp = minVal(root->right);
		root->data = temp->data;
		root->right = deleteNode(root->right, key);
	}

	return root;
}

int main(){
	string getText;
	ifstream openfile("text.txt");
	cout << "Original text:" << endl;
	while (! openfile.eof()) {
		getline(openfile, getText);
		cout << getText;
	}
	cout << '\n' << endl;
	cout << "Ordered text:" << endl;
	ifstream file("text.txt");
	node *head = NULL;
	string str;
	while (file>>str) {
		head = insert(head, str);
	}

	display(head);

	string searchW;

	while (searchW != "-1") {
		cout << endl << "\nEnter string to look for in the text, enter -1 to quit: ";
		cin >> searchW;
		search(head, searchW, 0);
	}

	string deleteW;
	while (deleteW != "-1") {
		cout << "\nEnter string to remove (enter -1 to quit): ";
		cin >> deleteW;
		deleteNode(head, deleteW);
		display(head);
	}
	
}