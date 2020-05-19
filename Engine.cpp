#include "Engine.h"

// ������ �������� ��������� �� ��� �������� �� ������������ ����������
void Engine::printParameter(Parameters parameter)
{
    std::cout.fill(' ');
    switch (parameter)
    {
    case Parameters::inertionMoment:
        std::cout << std::setw(50) << std::left << "Inertion moment (kg*m2): " << std::setw(10) << std::right << inertionMoment << '\n';
        break;
    case Parameters::ambTemperature:
        std::cout << std::setw(50) << std::left << "Ambient temperature (C): " << std::setw(10) << std::right << ambTemperature << '\n';
        break;
    case Parameters::overheatTemperature:
        std::cout << std::setw(50) << std::left << "Maximum temperature (C): " << std::setw(10) << std::right << overheatTemperature << '\n';
        break;
    case Parameters::k_HeatByMoment:
        std::cout << std::setw(50) << std::left << "coefficient of heating (by moment): " << std::setw(10) << std::right << k_HeatByMoment << '\n';
        break;
    case Parameters::k_HeatByVelocity:
        std::cout << std::setw(50) << std::left << "coefficient of heating (by velocity): " << std::setw(10) << std::right << k_HeatByVelocity << '\n';
        break;
    case Parameters::k_CoolByTemperature:
        std::cout << std::setw(50) << std::left << "coefficient of cooling (by temperature): " << std::setw(10) << std::right << k_CoolByTemperature << '\n';
        break;
    default:
        break;
    }
}

// ���������� ������� ��������� ������
void Engine::showData()
{
    for (int p = 1; p < static_cast<int>(Parameters::parameters_number); ++p)
        printParameter(static_cast<Parameters>(p));
    std::cout << std::endl << std::endl;
}

// ����� ��������� ��������� ������ 
void Engine::changeData()
{
    while (true) // ���� ������������ ����� ������ ���������
    {
        // �������� �������� ��� ��������� �� ������:
        std::cout << "Choose the parameter number you would like to change:\n";
        for (int p = 1; p < static_cast<int>(Parameters::parameters_number); ++p)
        {
            std::cout << p << " - ";
            printParameter(static_cast<Parameters>(p));
        }
        std::cout << "\n\nYour choice: ";
        int chosenP = get_number(1, static_cast<int>(Parameters::parameters_number) - 1);
        printParameter(static_cast<Parameters>(chosenP));

        std::cout << "Input a new value: ";
        switch (static_cast<Parameters>(chosenP))
        {
            case Parameters::inertionMoment:
                inertionMoment = get_number(0.0, 1000.0);
                break;
            case Parameters::ambTemperature:
                ambTemperature = get_number(-50.0, 50.0);
                break;
            case Parameters::overheatTemperature:
                overheatTemperature = get_number(30.0, 300.0);
                break;
            case Parameters::k_HeatByMoment:
                k_HeatByMoment = get_number(0.0, 1.0);
                break;
            case Parameters::k_HeatByVelocity:
                k_HeatByVelocity = get_number(0.0, 1.0);
                break;
            case Parameters::k_CoolByTemperature:
                k_CoolByTemperature = get_number(0.0, 1.0);
                break;
        }

        // ����� �������� ������, ����� ����������, ����� �� ���������� �������������, � ���� ��� - �������
        std::cout << "\nNew value for parameter has been saved. Do you want to change other parameters?" << std::endl;
        std::cout << "1 - " << "continue\n";
        std::cout << "2 - " << "finish" << std::endl;
        std::cout << "\nYour choice: ";
        int continueORfinish = get_number(1, 2);
        if (continueORfinish == 2)
            break;
    }
}