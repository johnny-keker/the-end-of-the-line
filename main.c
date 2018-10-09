#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define FLAG_PRINT_LINE_NUM 1
#define FLAG_INVERT_MATCH 2

int main(int argc, char *argv[]) {
  int flags = 0, opt = 0;
  while ((opt = getopt(argc, argv, "nv")) != -1) {
    switch (opt) {
      case 'n':
        flags |= FLAG_PRINT_LINE_NUM;
        break;
      case 'v':
        flags |= FLAG_INVERT_MATCH;
        break;
      default:
        fprintf(stderr, "Usage: %s [-n] [-v] pattern\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  if (optind >= argc) {
    fprintf(stderr, "Expected pattern after options\n");
    exit(EXIT_FAILURE);
  }
  int i = 0;
  char c;
  char buf[2001];
  while(scanf("%2000[^\n]%c", buf, &c) != EOF) {
    i++;
  	if (c=='\n') {
  		if ((strstr(buf, argv[optind]) != NULL) ^ ((flags & FLAG_INVERT_MATCH) != 0)) {
  			if (flags & FLAG_PRINT_LINE_NUM)
  				printf("%d:%s\n", i, buf);
  			else
  				printf("%s\n", buf);
  		}
  	}
    else {
     	fprintf(stderr, "Line #%d is too long, maximum 2000 characters allowed\n", i);
     	exit(EXIT_FAILURE);
    }
	}
  exit(EXIT_SUCCESS);
}