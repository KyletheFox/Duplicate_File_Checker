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

int main(int argc, char **argv) {
  struct node* root;

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

  return S_ISDIR(buff.st_mode);
}

void print_descendants(char *pathname, struct node** rt) {
  if (is_dir(pathname)) {
    DIR *d;
    struct dirent *p;
    char path[MAX_PATH_LENGTH];

    char *hashStr;
    struct node* temp;
    
    if ((d = opendir(pathname)) == NULL){
      fprintf(stderr, "opendir %s  %s\n", path, strerror(errno));
      return;
    } 

    while ((p = readdir(d)) != NULL) {
      if (strcmp(".", p->d_name)==0 || /* skip "." and ".." */
	  strcmp("..", p->d_name)==0 || strcmp(".git", p->d_name)==0)
	continue;
     

      printf("%s\n", p->d_name);

      snprintf(path, MAX_PATH_LENGTH, "%s/%s", pathname, p->d_name);

      // Malloc hash
      if ((hashStr = (char *)malloc(SHA_DIGEST_LENGTH*2+1)) == NULL)
      {
        printf("MALLOC hashStr Error\n");
        exit(1);
      }

      getHash(path, hashStr);

      temp = createNode(hashStr, path);

      insert(temp, rt);

      print_descendants(path, rt);
    }
    closedir(d);
  }
}