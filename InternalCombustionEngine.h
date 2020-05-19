#ifndef INTERNALCOMBUSTIONENGINE_H
#define INTERNALCOMBUSTIONENGINE_H

#include "Engine.h"
#include <vector>

// ��������� ����� ��� ������ � ����������� ������� �� ��������:
struct MomentByVelocity
{
	double exp_Velocity;
	double exp_Moment;
};

class InternalCombustionEngine : public Engine
{
private:
	// �������-�������� ����������� ��������� ������� �� �������� ���������:
	std::vector <MomentByVelocity> momentByVelocity;
	// �������� �� ������������ ������������� �� �������� �������� �������� - ������
	void inputMomentVelocityData();
	// ��������������� ������������ ������� ������ �������� ��������� �� ��� �������� �� ������������ ����������
	void printParameter(Parameters parameter);

	// ���������
	double acceleration(const double rotationMoment);
	// �������� ����������
	double heatingVelocity(const double rotationMoment, const double rotationVelocity);
	// �������� ����������
	double coolingVelocity(const double engineTemperature);
	
	// ������� ���������� ������ �� ��������, ������ �� ����������������� ������ �� �� �����������
	double rotationMoment(const double rotationVelocity);
	// ������� ������ �������� ���������� ������������
	void printCurrentTestResult(const unsigned timeSeconds, const double moment, const double velocity, const double temperature);

public:
	// ������� ����������� ������:
	InternalCombustionEngine(const double IMomnt, const double MaxTemp, const double k_HeatMomnt, const double k_HeatVel, const double k_CoolTemp, const std::vector <MomentByVelocity> momentVel) :
		 Engine(IMomnt, MaxTemp, k_HeatMomnt, k_HeatVel, k_CoolTemp), momentByVelocity(momentVel)
	{}
	// ��������������� ������������ ������� (���������� ������� ��������� ������)
	void showData();
	// ��������������� ������������ ������� ������ ��������� ��������� ������, �.�. � ���� ������ ���� ��� � ������ ������������
	void changeData();
	// ���� ��������� ����������� ��������
	void startTest();
};

#endif