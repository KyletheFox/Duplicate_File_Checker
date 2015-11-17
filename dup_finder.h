#ifndef DUP_FINDER_H_INCLUDED
#define DUP_FINDER_H_INCLUDED

struct node {
	int copy;
	char *fileName; 
	char *hash;
	struct node* left;
	struct node* right;
} node;

// printDir.c 
void make_space(int);
void print_descendants(char *, struct node**);
int is_dir(char *);

// hashGen.c
void to_hex_string(unsigned char bytes[], char str[], int len);
void getHash(char *,char *hashStr);

// tree2.c
struct node *createNode(char *, char *);
void insert(struct node*, struct node**);
void printTree(struct node*);
void printCopies(struct node*);


#endif