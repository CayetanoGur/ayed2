/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last entry in flight table
* @return True when is the last entry of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(LayoverTable a) {
  for (unsigned int hour = 0u; hour < HOURS; ++hour) {
    for (unsigned int type = 0u; type < TYPE; ++type) {
      Flight f = a[hour][type];
      fprintf(stdout, "%c: %s at %u:00 with %u passengers", f.code, f.type == 0 ? "arrives" : "departs", f.hour - 1, f.passengers_amount);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int passengers_amount_in_airport (LayoverTable a, unsigned int h) {
  /* COMPLETAR
    TENGO QUE SUMAR TODOS LOS QUE LLEGARON HASTA ESA HORA Y RESTAR LOS QUE SE FUERON HASTA ESA HORA
   */
  unsigned int p_llegada = 0u;
  unsigned int p_salida = 0u;
  Flight llegada;
  Flight salida;
  
  for (unsigned i = 0; i < h; ++i){
    llegada = a[i][0];
    p_llegada = p_llegada + llegada.passengers_amount;
  }

  for (unsigned j = 0; j < h; ++j){
    salida = a[j][1];
    p_salida = p_salida + salida.passengers_amount;
  }
  
  return p_llegada - p_salida;
}


void array_from_file(LayoverTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  //int i=0; //DONDE DEBERIA USAR ESA I?
  while (!feof(file)) {
    int res = fscanf(file, "_%c_", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    Flight flight_arrival = flight_from_file(file,code);
    Flight flight_departure = flight_from_file(file,code);
    array[flight_arrival.hour][0] = flight_arrival;
    array[flight_departure.hour][1] = flight_departure;
  }
  fclose(file);
}
