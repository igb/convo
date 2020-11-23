/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>




typedef struct {
  int           little_endian;
  int           decimal_out;
  int           hexadecimal_out;
} options_t;




void usage(char *name, int opt) {
  printf ("usage: %s [-lh] binary_string\n\t-l\t\tsets endianess to little endian (default is big endian)\n", name);
  
}


int main(int argc, char *argv[]) {


  int opt;
  


  
  options_t options = { 0 };

  opterr = 0;

  int j = 0;
  
  for (j = 0; j  < argc; j++) {

  


      
    if (strcmp(argv[j],  "-l") == 0) {
	options.little_endian += 1;
      }

    if ((strcmp(argv[j],  "-d") == 0) || (strcmp(argv[j],  "--dec") == 0)) {
	if (options.hexadecimal_out) {
	  printf("Error: hexadecimal outpout already set.");
	  usage(argv[0], opt);
	  exit(1);
	}
	options.decimal_out += 1;
      }
      
    if ((strcmp(argv[j],  "-x") == 0) || (strcmp(argv[j],  "--hex") == 0)) {
	if (options.decimal_out) {
	  printf("Error: decimal outpout already set.");
	  usage(argv[0], opt);
	  exit(1);
	}
	options.hexadecimal_out += 1;
      }
    if ((strcmp(argv[j],  "-h") == 0) || (strcmp(argv[j],  "--help") == 0)) {
	usage(argv[0], opt);
	exit(1);
      }
  }
  



  char bin_str[strlen( argv[argc - 1])];

  
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

  
  if (options.hexadecimal_out) {
    printf("%X\n", dec_val);
  } else if (options.decimal_out) {
      printf("%d\n", dec_val);
  } else {
      printf("%d\n", dec_val);
  }
    

    
}
