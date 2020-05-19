#ifndef DATA_H
#define DATA_H

#include <iostream>

// перечисление возможностей пользователя:
enum class Users_options
{
    check_data = 1, change_data, start_test, finish, options_number
};

// получение от пользователя значения в заданном диапазоне
template <typename T>
T get_number(const T min, const T max);

// главный диалог общения с пользователем
Users_options mainMenu();

// перечисление известных параметров:
enum class Parameters { inertionMoment = 1, ambTemperature, overheatTemperature, 
                        k_HeatByMoment, k_HeatByVelocity, k_CoolByTemperature, 
                        momentByVelocity, parameters_number};

// температура окружающей среды, градусы цельсия
extern double ambTemperature;      

// установка температуры окружающей среды
void askAmbTemperature();

#endif