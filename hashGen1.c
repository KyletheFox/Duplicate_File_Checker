#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "dup_finder.h"

/*
int main(int argc, char const *argv[])
{
	FILE *fp;
	char *hashValue;

	if ((fp=fopen(argv[1], "r"))==NULL) {
      		fprintf(stderr, "error opening %s for reading\n", argv[1]);
    	}

  	if ((hashValue = (char*)malloc(SHA_DIGEST_LENGTH*2+1)) == NULL)  {
  		printf("ERROR: No more space\n");
  		exit(1);
  	}

  	getHash(fp, hashValue);

    //printf("Before hash func\n");
    //hashValue = getHash(fp, hashValue);
    printf("Hash Value: %s\n", hashValue);

	return 0;
}
*/

/*
 ---------- TEST MAIN ----------------
int main(int argc, char const *argv[])
{
	int i;
 	int c;
 	unsigned char hash[SHA_DIGEST_LENGTH];
 	char hash_as_string[SHA_DIGEST_LENGTH*2+1];

 	SHA_CTX ctx;
 	FILE *fp;
  
 	for (i=1; i<argc; i++) {
   		if ((fp=fopen(argv[i], "r"))==NULL) {
      		fprintf(stderr, "error opening %s for reading\n", argv[i]);
      		continue;
    	}

    	SHA1_Init(&ctx);

    	while ((c=fgetc(fp))!=EOF) {
    		SHA1_Update(&ctx, &c, 1);
    	}

    	SHA1_Final(hash, &ctx);
    	to_hex_string(hash, hash_as_string, SHA_DIGEST_LENGTH);
    	printf("%s: %s\n", argv[i], hash_as_string);
  	}

  return 0;
}
*/

/* 
Function to compute file hash
*/
void getHash(char *file, char *hashStr) {
 	int c;
 	unsigned char hash[SHA_DIGEST_LENGTH];
 	//char hash_as_string[SHA_DIGEST_LENGTH*2+1];

 	SHA_CTX ctx;
 	FILE *fp;
  
 	if ((fp=fopen(file, "r"))==NULL) {
    		fprintf(stderr, "error opening %s for reading\n", *fp);
    }
    printf("Opened file to hash: %s\n\n", file);
    SHA1_Init(&ctx);
   	
   	while ((c=fgetc(fp))!=EOF) {
   		SHA1_Update(&ctx, &c, 1);
   	}

   	SHA1_Final(hash, &ctx);
   	//printf("Made it here\n");
   	to_hex_string(hash, hashStr, SHA_DIGEST_LENGTH);

    fclose(fp);

   	//return hashStr;

}

/* fills str with a C-string version of the digest stored
   in bytes[] */
void to_hex_string(unsigned char bytes[], char str[], int len) {
  int i;

  for (i=0; i<len; i++) {
    sprintf(str, "%02X", (unsigned char)bytes[i]);
    str += 2;
  }

  //printf("%s\n", str);
}
	