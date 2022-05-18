/*
  @file weather_utils.h
  @brief defines weather utils methods. These methods operates over multidimensional (year, month, day) array of weather
*/

#ifndef WEATHER_UTILS_H
#define WEATHER_UTILS_H

#include <stdio.h>
#include "weather.h"
#include "array_helpers.h"

/**
 * @brief returns the record low temperature registered in Cordoba according to the data in the array
 */

int min_record_temp(WeatherTable array);

/**
 * @brief stores the record high temperature registered in Cordoba in each year according to the data in the array
 */

void max_yearly_temp(WeatherTable array, int output[YEARS]);

/**
 * @brief stores the record high rainfall per month registered in Cordoba in each year according to the data in the array
 */

void max_yearly_rainfall(WeatherTable array, t_month output[YEARS]);

#endif	

