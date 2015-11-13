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
  root = NULL;

  print_descendants(argv[1], &root);

  printTree(root);

  return EXIT_SUCCESS;
}

/* returns 1 if path_name represents a directory
   0 if it isn't */
int is_dir(char *path_name) {

  struct stat buff;

  if (stat(path_name, &buff) < 0){
    fprintf(stderr, "stat: %s\n", strerror(errno));
    return 0;
  }
  printf("checking if dir: %s\n", path_name);
  printf("1 for dir, 0 for file: %d\n\n", S_ISDIR(buff.st_mode));
  return S_ISDIR(buff.st_mode);
}

void print_descendants(char *pathname, struct node** rt) {

  if (is_dir(pathname)) {

    DIR *d;
    struct dirent *p;
    
    char *hashValue;
    char path[MAX_PATH_LENGTH];
    struct node *temp;
    
    if ((d = opendir(pathname)) == NULL){
      fprintf(stderr, "opendir %s  %s\n", path, strerror(errno));
      return;
    } 

    while ((p = readdir(d)) != NULL) {
      if (strcmp(".", p->d_name)==0 || /* skip "." and ".." */
        strcmp("..", p->d_name)==0 || strcmp(".git", p->d_name)==0 )
        continue;

      //printf("pathname: %s\n", pathname);
      //printf("p->d_name: %s\n", p->d_name);
      if (is_dir(p->d_name)) {
        // Generatate Hash String
        if ((hashValue = (char*)malloc(SHA_DIGEST_LENGTH*2+1)) == NULL)  {
         printf("ERROR: No more space\n");
         exit(1);
        }
      
       // Generate hash
       getHash(p->d_name, hashValue);

       //Create node and insert into tree
       temp = createNode(hashValue, p->d_name);

       // Insert into new Node
       insert(temp, rt);
      }

      // Set next file name
      snprintf(path, MAX_PATH_LENGTH, "%s/%s", pathname, p->d_name);

      print_descendants(path, rt);
    }

    closedir(d);
  }
}