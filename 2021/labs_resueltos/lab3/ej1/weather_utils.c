/*
  @file weather_utils.c
  @brief Implements weather utils methods
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "weather_utils.h"


int min_record_temp(WeatherTable array){
	int min_temp = INT_MAX;

	for(unsigned int year = 0u; year < YEARS; ++year){
		for(unsigned int month = 0u; month < MONTHS; ++month){
			for(unsigned int day= 0u; day < DAYS; ++day){
				if(array[year][month][day]._min_temp < min_temp){
					min_temp = array[year][month][day]._min_temp;
				}
			}
		}
	}
	return min_temp;
}

void max_yearly_temp(WeatherTable array, int output[YEARS]){

	for(unsigned int year = 0u; year < YEARS; ++year){
		int max_temp_year = INT_MIN;
		for(unsigned int month = 0u; month < MONTHS; ++month){
			int max_temp_month = INT_MIN;
			for(unsigned int day= 0u; day < DAYS; ++day){
				if(array[year][month][day]._max_temp > max_temp_month){
					max_temp_month = array[year][month][day]._max_temp;
				}
			}
			if(max_temp_month > max_temp_year){
				max_temp_year = max_temp_month;
			}
		}
		output[year] = max_temp_year;
	}
}

void max_yearly_rainfall(WeatherTable array, t_month output[YEARS]){

	for(unsigned int year = 0u; year < YEARS; ++year){
		unsigned int max_rainfall_year = 0u; //stores the highest rainfall of each year
		t_month max_rainfall_month = 0u; //stores the month with the highest rainfall per year

		for(unsigned int month = 0u; month < MONTHS; ++month){
			unsigned int total_monthly_rainfall = 0u; //sum of the daily rainfall per month
			
			for(unsigned int day= 0u; day < DAYS; ++day){
				total_monthly_rainfall += array[year][month][day]._rainfall;
			}
			
			if(total_monthly_rainfall > max_rainfall_year){
				max_rainfall_year = total_monthly_rainfall;
				max_rainfall_month = month;
			}
		}

		output[year] = max_rainfall_month;
	}
}
