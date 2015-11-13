#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <openssl/sha.h>
#include "dup_finder.h"

#define SPACES_PER_INDENT_LEVEL 3
#define MAX_PATH_LENGTH 512

#define EXIT_USAGE_ERROR 1
#define EXIT_SUCCESS 0

extern int errno;

/*   --In dup_finder.h--
void usage(char**);
void make_space(int num_spaces);
void print_descendants(char *pathname, int n);
int is_dir(char *path_name);
*/
int main(int argc, char **argv) {

  struct node* root;
  //root = createNode(NULL, NULL);    // emplty pointers
  printf("------- Root ----------\n");

  printf("%s\n", argv[1]);
  print_descendants(argv[1], &root);

  printTree(root);

  return EXIT_SUCCESS;
}

/* returns 1 if path_name represents a directory
   0 if it isn't */
int is_dir(char *path_name) {

  printf("pathname: %s\n", path_name);
  struct stat buff;

  if (stat(path_name, &buff) < 0){
    fprintf(stderr, "stat: %s\n", strerror(errno));
    return 0;
  }

  return S_ISDIR(buff.st_mode);
}

void print_descendants(char *pathname, struct node** rt) {

  if (is_dir(pathname)) {
//Gets past here
    printf("BP\n");


    printf("address of pathname: %x\n", pathname);
    DIR *d;
    FILE *fp;
    struct dirent *p;
    
    char *hashValue;
    char path[MAX_PATH_LENGTH];
    struct node *temp;
    
    printf("BP2\n");
    if ((d = opendir(pathname)) == NULL){
      fprintf(stderr, "opendir %s  %s\n", path, strerror(errno));
      return;
    } 
    printf("BP3\n");

    while ((p = readdir(d)) != NULL) {
      if (strcmp(".", p->d_name)==0 || /* skip "." and ".." */
        strcmp("..", p->d_name)==0 || strcmp(".git", p->d_name)==0)
        continue;

      //make_space(depth*SPACES_PER_INDENT_LEVEL);
      //printf("this is what p->d_name is: %s\n", p->d_name);

      // Open File
      if ((fp=fopen(p->d_name, "r"))==NULL) {
          printf("ERROR: File Doesn't Exist\n");
          exit(1);
      }

      // Generatate Hash String
      if ((hashValue = (char*)malloc(SHA_DIGEST_LENGTH*2+1)) == NULL)  {
        printf("ERROR: No more space\n");
        exit(1);
      }
      // Generate hash
      getHash(fp, hashValue);

      // Set file name
      snprintf(path, MAX_PATH_LENGTH, "%s/%s", pathname, p->d_name);

      //Create node and insert into tree
      temp = createNode(hashValue, p->d_name);

      printf("Temp address: %x\n", temp);
      printf("Temp left address: %x\n", temp->left);
      printf("Temp right address: %x\n", temp->right);

      // Insert into tree
      insert(temp, rt);

      // Close file
      fclose(fp);

      print_descendants(path, rt);
    }

    closedir(d);
  }
}