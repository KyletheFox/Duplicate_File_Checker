#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dup_finder.h"

/*
	Program will only consist of nodes. The program must keep
	track of the root node. 
*/

/*
struct node *createNode(int);
void insert(struct node*, struct node**);
void printTree(struct node*);
*/

/* ----------- TEST MAIN ----------
int main(int argc, char const *argv[]) {
	

	// Create rootnode pointer
	struct node* root;

	// Create rootNode
	struct node* r = createNode("Apple");
	
	// Create a couple Nodes
	struct node* n1 = createNode("Banana");
	struct node* n2 = createNode("Acorn");
	struct node* n3 = createNode("Zebra");

	// Insert all nodes
	insert(r, &root);
	insert(n1, &root);
	insert(n2, &root);
	insert(n3, &root);

	// Print tree
	printTree(root);

	printf("\n");
	
	return 0;
}
*/

void insert(struct node* n, struct node** root) {

 	//printf("Address of n: %x\n", n);
	//printf("Address of n->left: %x\n", n->left);
	//printf("Address of n->right: %x\n", n->right);

	//printf("Address of root: %x\n", (*root));
	//printf("Address of root->left: %x\n", (*root)->left);
	//printf("Address of root->right: %x\n", (*root)->right);

	//printf("BP5\n");
	if (*root == NULL) {
		//printf("*root == NULL : True\n");
		//printf("File Inserted: %s\n", n->fileName);
		*root = n;
	}

	else {

		if (strcmp(n->hash,(*root)->hash) >= 0) {
			//printf("Entering right node\n");
			//printf("right node address: %x\n", (*root)->right);
			insert(n, &((*root)->right));
		}

		else {
			//printf("Entering Left Node\n");
			//printf("left node address: %x\n", (*root)->left);
			insert(n, &((*root)->left));
		}
	}

}

struct node *createNode(char* hash, char *file) {
	struct node* temp;

	if ((temp = (struct node*)malloc(sizeof(struct node))) == NULL) {
		printf("ERROR\n");
		exit(1);	
	}

	temp->copy = 0;
	temp->hash = hash;
	temp->fileName = file;
	temp->left = NULL;
	temp->right = NULL;
    //printf("Address of node: %x\n", temp);
	//printf("Address of new left node: %x\n", temp->left);
	//printf("Address of new right node: %x\n", temp->right);

	return temp;
}

void printTree(struct node* p) {
	//printf("Before print.\n");
	if (p->left != NULL) {
		printTree(p->left);
	}
	printf("%s\n", p->hash);
	if (p->right != NULL) {
		printTree(p->right);
	}

}