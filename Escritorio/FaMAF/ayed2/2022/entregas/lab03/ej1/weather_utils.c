#include "weather_utils.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int min_temp_all(WeatherTable array){
    int min = INT16_MAX;
    
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if(array[year][month][day]._min_temp < min){
                    min = array[year][month][day]._min_temp;
                }
            }
        }
    }
    return min;
}

void max_temp_each_year(WeatherTable array, int years_max[]){
    int max = INT16_MIN;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
              if(array[year][month][day]._max_temp > max){
                    max = array[year][month][day]._max_temp;
                }  
            }
        }
        years_max[year] = max;
        max = INT16_MIN;
    }
}

void max_rainfall_monthly(WeatherTable array, int monthly_max[]){

    unsigned int temp = 0u;
    unsigned int temp2 = 0u;

    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
              if(array[year][month][day]._rainfall > temp){
                    temp = array[year][month][day]._rainfall;
                    temp2 = month+1u;
                }  
            }
        }
        monthly_max[year] = temp2;
        temp2 = 0u;
        temp = 0u;
    }
}