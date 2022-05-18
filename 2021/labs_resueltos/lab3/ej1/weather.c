/*
  @file weather.c
  @brief Implements weather mesuarement structure and methods
*/
#include <stdlib.h>
#include "weather.h"

static const int AMOUNT_OF_WEATHER_VARS = 6 ;

Weather weather_from_file(FILE* file)
{
    Weather weather;
    int pressure;
    int moisture;
    int rainfall;

    int fscanf_result = fscanf(file, " %d %d %d %d %d %d " , &weather._average_temp, 
      	&weather._max_temp, &weather._min_temp, &pressure, &moisture, &rainfall);
    weather._pressure = pressure;
    weather._moisture = moisture;
    weather._rainfall = rainfall;
    if(fscanf_result != AMOUNT_OF_WEATHER_VARS || pressure < 0 || rainfall < 0 || moisture < 0){
    	printf("Invalid array.\n");
        exit(EXIT_FAILURE);
    	}
    
    return weather;
}

void weather_to_file(FILE* file, Weather weather)
{
    fprintf(file, EXPECTED_WEATHER_FILE_FORMAT, weather._average_temp, 
            weather._max_temp, weather._min_temp, weather._pressure, weather._moisture, weather._rainfall);
}
