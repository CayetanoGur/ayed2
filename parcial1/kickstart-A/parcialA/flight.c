/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 3 ;

Flight flight_from_file(FILE* file, char code)
{
    Flight flight;
    flight.code = code;

    char type;

    int res = fscanf(file, " %s %u %u ", &type, &flight.hour, &flight.passengers_amount);
/*    
    NOTA:
    No logro entender porque el fscanf no lee, intente de muchas forma y ninguna termina de andar
    el problema lo tengo en leer el tipo enum, lo que intente fue que lea el tipo de vuelo
    como si fuera un unsigned int y luego asignarlo al flight.type pero no funciona.
*/

    printf("res: %d\n", res);

    flight.type = type;


    printf("type: %u\n", type);  

    if (res != AMOUNT_OF_FLIGHT_VARS ){
      fprintf(stderr, "Invalid amount of weather variables. %d\n", res);
        exit(EXIT_FAILURE);
    }
    return flight;
}


// Flight flight_from_file(FILE* file, char code)
// {
//     Flight flight;
//     flight.code = code;

//     char type;

//     int res = fscanf(file, " %c %u %u ", &type, &flight.hour, &flight.passengers_amount);
//     flight.type = type;

//     /*
//     NOTA:
//     No logro entender porque el fscanf no lee, intente de muchas forma y ninguna termina de andar
//     el problema lo tengo en leer el tipo enum, lo que intente fue que lea el tipo de vuelo
//     como si fuera un unsigned int y luego asignarlo al flight.type pero no funciona.
//     */

//     printf("res: %d\n", res);
//     printf("type: %c\n", type);  

//     if (res != AMOUNT_OF_FLIGHT_VARS ){
//       fprintf(stderr, "Invalid amount of weather variables. %d\n", res);
//         exit(EXIT_FAILURE);
//     }
//     return flight;
// }