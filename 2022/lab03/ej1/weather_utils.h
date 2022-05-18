#include "weather.h"
#include "array_helpers.h"

/** @brief Funcion que obtenga la menor temperatura historica registrada. */
int min_temp_all(WeatherTable array);

/** @brief Procedimiento que registre para cada año la mayor temperatura maxima */
void max_temp_each_year(WeatherTable array, int years_max[]);

/** @brief Procedimiento que registra para cada año el mes de ese año en que se registr la mayor cant mensul de precipitaciones*/
void max_rainfall_monthly(WeatherTable array,int monthly_max[]);