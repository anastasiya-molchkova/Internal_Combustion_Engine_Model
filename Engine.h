#ifndef ENGINE_H
#define ENGINE_H

#include "Data.h"
#include <iomanip>   // ��� �������������� ������ �� �������

class Engine
{
protected: 
    // ����������: � �� ����, ����� ����� ��������� ����� � ���� ����������, � ������ ������� ���:
    double inertionMoment;      // ��*�2
    double overheatTemperature; // ������� �������

    // ������������:
    double k_HeatByMoment;      // �������/�*�*���
    double k_HeatByVelocity;    // �������*���/������2
    double k_CoolByTemperature; // 1/���

    // ������ �������� ��������� �� ��� �������� �� ������������ ����������
    void printParameter(Parameters parameter);
public:
    // ������� ����������� ������:
    Engine(const double IMomnt, const double MaxTemp, const double k_HeatMomnt, const double k_HeatVel, const double k_CoolTemp):
        inertionMoment(IMomnt), overheatTemperature(MaxTemp), k_HeatByMoment(k_HeatMomnt), k_HeatByVelocity(k_HeatVel), k_CoolByTemperature(k_CoolTemp)
    {}

    // ���������� ������� ��������� ������
    void showData();
    // ����� ��������� ��������� ������ 
    void changeData();
};

#endif

