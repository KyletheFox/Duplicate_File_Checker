#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
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

void usage(char **argv) {
  fprintf(stderr, "usage: %s filename\n", argv[0]);
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

void print_descendants(char *pathname, int depth) {
  if (is_dir(pathname)) {
    DIR *d;
    struct dirent *p;
    char path[MAX_PATH_LENGTH];
    
    if ((d = opendir(pathname)) == NULL){
      fprintf(stderr, "opendir %s  %s\n", path, strerror(errno));
      return;
    } 

    while ((p = readdir(d)) != NULL) {
      if (strcmp(".", p->d_name)==0 || /* skip "." and ".." */
    strcmp("..", p->d_name)==0)
  continue;
      make_space(depth*SPACES_PER_INDENT_LEVEL);
      printf("%s\n", p->d_name);
      snprintf(path, MAX_PATH_LENGTH, "%s/%s", pathname, p->d_name);
      print_descendants(path, depth+1);
    }
    closedir(d);
  }
}

void make_space(int num_spaces) {
  int i;
  for (i=0; i<num_spaces; i++)
    putchar(' ');
}