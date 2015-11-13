#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "dup_finder.h"

int main(int argc, char const *argv[])
{
	FILE *fp;
	char *hashValue;
	struct node* root;
	struct node* temp;

	root = NULL;

	// Open File
	if ((fp=fopen(argv[1], "r"))==NULL) {
      		printf("ERROR: File Doesn't Exist\n");
      		exit(1);
    	}

	// Generatate Hash String
    if ((hashValue = (char*)malloc(SHA_DIGEST_LENGTH*2+1)) == NULL)  {
  		printf("ERROR: No more space\n");
  		exit(1);
  	}

  	getHash(fp, hashValue);

  	// Create Node
  	temp = createNode(hashValue, argv[1]);

  	//Insert Node
  	insert(temp, &root);

  	//Print Tree
  	printTree(root);
	
	return 0;
}