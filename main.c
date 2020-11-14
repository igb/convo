/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>

#define OPTSTR "lh:"


typedef struct {
  int           little_endian;
} options_t;


void usage(char *name, int opt) {
  printf ("usage: %s [-lh] binary_string\n\t-l\t\tsets endianess to little endian (default is big endian)\n", name);
  
}
int  do_the_needful(options_t *options);

int main(int argc, char *argv[]) {

  int opt;
  int opt_count;


  
  options_t options = { 0 };

  opterr = 0;
  
  while ((opt = getopt(argc, argv, OPTSTR)) != EOF) {

      opt_count++;
      
    switch(opt) {
      
    case 'l' :
      options.little_endian += 1;
      break;

    case 'h':
    default:
      usage(argv[0], opt);
      break;
    }
  }



  char bin_str[sizeof argv[argc - 1]];

  
  strcpy(bin_str, argv[argc - 1]);

  int i;
  
  for (i = 0; i < strlen(bin_str); i++){
    char c = bin_str[i];
    if (!((c == '0') || (c == '1'))) {
	printf("Expected string representation of a binary sequence! (i.e. 00100111)\n");
	exit(1);
    }

  }


  //buffer for endianed string
  char endianed_bin_str[sizeof bin_str];

  //init with input value, assumning big endianess
  strcpy(endianed_bin_str, bin_str);
  
  // if little endianess is specified, reverse string before parsing
  if ( options.little_endian ) {
    for (i = 0; i < strlen(bin_str); i++){
      char c = bin_str[i];
      endianed_bin_str[strlen(endianed_bin_str) - (i + 1)] = c;
    }

  }

  
  int dec_val = strtol(endianed_bin_str, NULL, 2);
  
  printf("%d\n", dec_val);

    
}
