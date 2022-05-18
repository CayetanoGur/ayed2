#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "weather_utils.h"

int min_temp(WeatherTable array){

    int res = array[0u][0u][0u]._min_temp;

    for (unsigned int year = 0; year < YEARS; ++year){

        for (t_month month = 0; month < MONTHS; ++month){

            for (unsigned int day = 0; day < DAYS; ++day){

                if(array[year][month][day]._min_temp < res){
                    res = array[year][month][day]._min_temp;
                }

            }
        }
        
    }
     
return res;
}

void procedimiento(WeatherTable a, int output[YEARS]){

    Weather climate;
    climate._max_temp = a[0u][0u][0u]._max_temp;

    for (unsigned int year = 0; year < YEARS; ++year){

        for (t_month month = 0; month < MONTHS; ++month){
            
            for (unsigned int day = 0; day < DAYS; ++day){

                if (a[year][month][day]._max_temp > climate._max_temp){

                    output[year] = a[year][month][day]._max_temp;
                }
            }
        }
    }

}


void proc_rainfall (WeatherTable a, int res[YEARS][MONTHS]){
   
    Weather clim;
    clim._rainfall = a[0u][0u][0u]._rainfall;
    
    for (unsigned int year = 0; year < YEARS; ++year){

        for (t_month month = 0; month < MONTHS; ++month){
            
            for (unsigned int day = 0; day < DAYS; ++day){

                if (a[year][month][day]._rainfall > clim._rainfall){

                    res[year][month] = a[year][month][day]._rainfall;
                }
            }
        }
    }

}


