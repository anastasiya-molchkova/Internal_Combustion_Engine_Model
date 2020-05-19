#ifndef ENGINE_H
#define ENGINE_H

#include "Data.h"
#include <iomanip>   // для редактирования вывода на консоль

class Engine
{
protected: 
    // Примечание: я не знаю, какие точно параметры общие у всех двигателей, я решила сделать эти:
    double inertionMoment;      // кг*м2
    double overheatTemperature; // градусы цельсия

    // коэффициенты:
    double k_HeatByMoment;      // градусы/Н*м*сек
    double k_HeatByVelocity;    // градусы*сек/радиан2
    double k_CoolByTemperature; // 1/сек

    // печать значения параметра по его названию из перечисления параметров
    void printParameter(Parameters parameter);
public:
    // простой конструктор класса:
    Engine(const double IMomnt, const double MaxTemp, const double k_HeatMomnt, const double k_HeatVel, const double k_CoolTemp):
        inertionMoment(IMomnt), overheatTemperature(MaxTemp), k_HeatByMoment(k_HeatMomnt), k_HeatByVelocity(k_HeatVel), k_CoolByTemperature(k_CoolTemp)
    {}

    // показываем текущие начальные данные
    void showData();
    // режим изменения начальных данных 
    void changeData();
};

#endif

