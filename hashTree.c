#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dup_finder.h"

void insert(struct node* n, struct node** root) {

	if (*root == NULL) {
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
	printf("%s: %s\n", p->fileName, p->hash);
	if (p->right != NULL) {
		printTree(p->right);
	}

}