#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "dup_finder.h"

/* 
Function to compute file hash
*/
void getHash(char *file, char *hashStr) {
 	int c;
 	unsigned char hash[SHA_DIGEST_LENGTH];
 	//char hash_as_string[SHA_DIGEST_LENGTH*2+1];

 	SHA_CTX ctx;
 	FILE *fp;

  //printf("should be full path: %s\n", file);
  
 	if ((fp=fopen(file, "r"))==NULL) {
    		fprintf(stderr, "error opening %s for reading\n", *fp);
    }
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

}
	


