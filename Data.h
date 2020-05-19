#ifndef DATA_H
#define DATA_H

#include <iostream>

// ������������ ������������ ������������:
enum class Users_options
{
    check_data = 1, change_data, start_test, finish, options_number
};

// ��������� �� ������������ �������� � �������� ���������
template <typename T>
T get_number(const T min, const T max);

// ������� ������ ������� � �������������
Users_options mainMenu();

// ������������ ��������� ����������:
enum class Parameters { inertionMoment = 1, ambTemperature, overheatTemperature, 
                        k_HeatByMoment, k_HeatByVelocity, k_CoolByTemperature, 
                        momentByVelocity, parameters_number};

// ����������� ���������� �����, ������� �������
extern double ambTemperature;      

// ��������� ����������� ���������� �����
void askAmbTemperature();

#endif