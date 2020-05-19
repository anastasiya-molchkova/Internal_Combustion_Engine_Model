#ifndef INTERNALCOMBUSTIONENGINE_H
#define INTERNALCOMBUSTIONENGINE_H

#include "Engine.h"
#include <vector>

// структура нужна для данных о зависимости момента от скорости:
struct MomentByVelocity
{
	double exp_Velocity;
	double exp_Moment;
};

class InternalCombustionEngine : public Engine
{
private:
	// кусочно-линейная зависимость крутящего момента от скорости коленвала:
	std::vector <MomentByVelocity> momentByVelocity;
	// получаем от пользователя упорядоченные по скорости значения скорость - момент
	void inputMomentVelocityData();
	// переопределение родительской функции печати значения параметра по его названию из перечисления параметров
	void printParameter(Parameters parameter);

	// ускорение
	double acceleration(const double rotationMoment);
	// скорость нагревания
	double heatingVelocity(const double rotationMoment, const double rotationVelocity);
	// скорость охлаждения
	double coolingVelocity(const double engineTemperature);
	
	// функция определяет момент по скорости, исходя из экспериментальных данных об их зависимости
	double rotationMoment(const double rotationVelocity);
	// функция печати текущего результата тестирования
	void printCurrentTestResult(const unsigned timeSeconds, const double moment, const double velocity, const double temperature);

public:
	// простой конструктор класса:
	InternalCombustionEngine(const double IMomnt, const double MaxTemp, const double k_HeatMomnt, const double k_HeatVel, const double k_CoolTemp, const std::vector <MomentByVelocity> momentVel) :
		 Engine(IMomnt, MaxTemp, k_HeatMomnt, k_HeatVel, k_CoolTemp), momentByVelocity(momentVel)
	{}
	// переопределение родительской функции (показываем текущие начальные данные)
	void showData();
	// переопределение родительской функции режима изменения начальных данных, т.к. в этом классе есть ещё и вектор зависимостей
	void changeData();
	// тест двигателя внутреннего сгорания
	void startTest();
};

#endif