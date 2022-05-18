
/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "stack.h"

/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100u;

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Sort an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

int main(int argc, char *argv[]) {
  char *filepath = NULL;
  stack s;
  s = stack_empty();

  /* parse the filepath given in command line arguments */
  filepath = parse_filepath(argc, argv);

  /* create an array of MAX_SIZE elements */
  int array[MAX_SIZE];

  /* parse the file to fill the array and obtain the actual length */
  unsigned int length = array_from_file(array, MAX_SIZE, filepath);
  printf("Original: ");
  array_dump(array, length);

  int *arrayNew = NULL;

  arrayNew = stack_to_array(s);
  printf("%p\n", (void*)arrayNew);

  for(unsigned int i = 0u; i < 1u; ++i){
    s = stack_push(s, array[i]);
  }

  s = stack_pop(s); 

  for(unsigned int i = 0u; i < 1u; ++i){
    s = stack_push(s, array[i]);
  }

  arrayNew = stack_to_array(s);

  array_dump(arrayNew, 1u);

  s = stack_destroy(s);

  free(arrayNew); 

  return (EXIT_SUCCESS);
}