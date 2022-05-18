#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[]){
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0;
    while(!feof(file)){
        fscanf(file, "%u ", &indexes[i]);
        fscanf(file, "'%c'\n", &letters[i]);
        ++i;
    }
    fclose(file);
    return i;
}

// yo cuando quiero definir una funcion que devuelva un array de chars tengo que ponerle el puntero porque en C char es un solo caracter y *char es un array de caracteres

char *phrase(char sorted[],unsigned int indexes[], char letters[], unsigned int length){
    for (unsigned int i = 0; i < length; ++i){
        sorted[indexes[i]] = letters[i];
    }
    return sorted;
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        //print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 
    //  .----------^
    //  :
    // Debe guardarse aqui la cantidad de elementos leidos del archivo
    
    /* -- completar -- */
    length = data_from_file(filepath,indexes,letters);
    phrase(sorted,indexes,letters,length);
    dump(sorted, length);

    return EXIT_SUCCESS;
}

