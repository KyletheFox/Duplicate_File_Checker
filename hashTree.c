#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dup_finder.h"

void insert(struct node* n, struct node** root) {

	if (*root == NULL) {
		*root = n;
	}

	else {
		//printf("strcmp(n->hash,(*root)->hash): %d\n", strcmp(n->hash,(*root)->hash));
		if (strcmp(n->hash,(*root)->hash) >= 0) {
			
			if (strcmp(n->hash,(*root)->hash)==0) {
				n->copy=1;
				(*root)->copy=1;
			}
			

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

void printCopies(struct node* p) {
	//printf("Before print.\n");
	if (p->left != NULL) {
		printCopies(p->left);
	}
	if (p->copy == 1)
		printf("%s: %s\n", p->fileName, p->hash);
	if (p->right != NULL) {
		printCopies(p->right);
	}

}