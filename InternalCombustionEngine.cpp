#include "InternalCombustionEngine.h"

// �������� �� ������������ ������������� �� �������� �������� �������� - ������
void InternalCombustionEngine::inputMomentVelocityData()
{
    momentByVelocity.clear();
    static const unsigned minDataNumber = 4; // ������� ���������� ������ - ������ ������

    /* ������� ������ ������ - ��� ������ ���������� �� ��������,
    ���������� � ������� �������� � ������������� ������� ��������: */
    std::cout << "\nInput new ordered data for velocity and moment, starting from velocity = 0 to moment = 0\n";
    std::cout << "Enter a moment = 0 to finish\n" << std::endl;

    // ������ ������ - ��� ������� ��������
    std::cout << "First velocity (should be zero): ";
    double previous_velocity = get_number(0.0, 0.0);
    std::cout << "First moment (for zero velocity): ";
    double previous_moment = get_number(0.0, 1000.0);
    momentByVelocity.push_back(MomentByVelocity({ previous_velocity, previous_moment}));
    
    // ���� ������������ ������ ��� ���� �� ����� ������ � ������� ��������
    while ((previous_moment != 0) || (momentByVelocity.size() < minDataNumber))
    {
        if ((previous_moment == 0) && (momentByVelocity.size() < minDataNumber))
            std::cout << "\nPlease continue, since this number of data is not enough...";

        // ������ ��������� ��������, ����������� �������� ����� ���������� ���������:
        std::cout << "\nthe next velocity: ";
        double current_velocity = get_number(previous_velocity, 1000.0);
        std::cout << "moment for this value: ";
        double current_moment = get_number(0.0, 1000.0);

        // ��������� ������:
        momentByVelocity.push_back(MomentByVelocity({current_velocity, current_moment}));
        
        // ��� ���������� �����:
        previous_velocity = current_velocity;
        previous_moment = current_moment;
    }
}

// ������ �������� ��������� �� ��� �������� �� ������������ ����������
void InternalCombustionEngine::printParameter(Parameters parameter)
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
    case Parameters::momentByVelocity:
        std::cout << "Rotation moment (N*m) by rotation velocity (rad/sec):\n";
        for (const auto& data : momentByVelocity)
            std::cout << data.exp_Velocity << "->" << data.exp_Moment << "  ";
        break;
    default:
        break;
    }
}

// ���������� ������� ��������� ������
void InternalCombustionEngine::showData()
{
    for (int p = 1; p < static_cast<int>(Parameters::parameters_number); ++p)
        printParameter(static_cast<Parameters>(p));
    std::cout << std::endl << std::endl;
}

// �������������� ������������ ������� ������ ��������� ��������� ������, �.�. � ���� ������ ���� ��� � ������ ������������
void InternalCombustionEngine::changeData()
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

        // ��� �������� ��������� �������� - ��������� �������
        if (static_cast<Parameters>(chosenP) == Parameters::momentByVelocity)
            inputMomentVelocityData();
        else // ����� ����� �������� ���������� ���������, �������� �������� �������:
        {
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

// ���������
double InternalCombustionEngine::acceleration(const double rotationMoment)
{
    return rotationMoment / inertionMoment;
}

// �������� ����������
double InternalCombustionEngine::heatingVelocity(const double rotationMoment, const double rotationVelocity)
{
    return (rotationMoment * k_HeatByMoment) + (pow(rotationVelocity, 2) * k_HeatByVelocity);
}

// �������� ����������
double InternalCombustionEngine::coolingVelocity(const double engineTemperature)
{
    return k_CoolByTemperature * (ambTemperature - engineTemperature);
}

/* ������� ���������� ������ �� ��������, ������ �� ����������������� ������ �� �� �����������
 ����� ������, �� ������������ �������� ���������� ����� ����� ���������� �������, � �� �������� ���� �������� ������� �� ���� �������
 ���� ����� ��� �� ���� �����-������ ����� ������������� ���� ����������� � ���� �������. 
 ��������, ����� ���������� ��������� ������� �� ��� ����������� � ���� ��������. 
 � ���������, ��� ���� ����� �������� �� ������ �� ������ � ������ �� ��������������, ������ ����,
 ����������� ��� �������� ������ ������� ���������� �������� �������, ������� �������� ������� �������� */
double InternalCombustionEngine::rotationMoment(const double rotationVelocity)
{
    // ���������� ��������� ��������� ������ �� ��������� <= ������� 
    MomentByVelocity closest_lower = momentByVelocity[0];
    MomentByVelocity closest_upper = momentByVelocity[momentByVelocity.size() - 1];

    // ����� ��������� ���������� �������� ��������, ��� ������� ����� ���������:
    if (rotationVelocity <= closest_lower.exp_Velocity)
        return closest_lower.exp_Moment;
    if (rotationVelocity >= closest_upper.exp_Velocity)
        return closest_upper.exp_Moment;

    // ���� �������� ������� ��������� �������� �������� ������ � �����:
    for (const auto& data : momentByVelocity)
    {
        // ���� �������� ����� ������� � ���������
        if (data.exp_Velocity == rotationVelocity)
            return data.exp_Moment;
        if ((data.exp_Velocity < rotationVelocity)
            && ((rotationVelocity - data.exp_Velocity) < abs(rotationVelocity - closest_lower.exp_Velocity)))
            closest_lower = data;
        if ((data.exp_Velocity > rotationVelocity)
            && ((data.exp_Velocity - rotationVelocity) < abs(rotationVelocity - closest_upper.exp_Velocity)))
            closest_upper = data;
    }

    // ���������� ������ ��������������� ��� ���������� �� �������� �� ��������� ��������:
    double rotMoment = closest_lower.exp_Moment;
    rotMoment += ((closest_upper.exp_Moment - closest_lower.exp_Moment)
        * (rotationVelocity - closest_lower.exp_Velocity) / (closest_upper.exp_Velocity - closest_lower.exp_Velocity));
    return rotMoment;
}

// ������ �������� ���������� ����� 
void InternalCombustionEngine::printCurrentTestResult(const unsigned timeSeconds, const double moment, const double velocity, const double temperature)
{
    // ����� �������� ��� ������ � �������
    std::cout << std::setw(3) << timeSeconds / 60 << "min " << std::setw(2) << timeSeconds % 60 << "sec  ";
    // ��������� ��������� �� 3-�� ����� ����� �������:
    std::cout << std::setw(15) << round(moment * 1000) / 1000;
    std::cout << std::setw(15) << round(velocity * 1000) / 1000;
    std::cout << std::setw(15) << round(temperature * 1000) / 1000 << std::endl;
}

// ���� ��������� ����������� ��������
void InternalCombustionEngine::startTest()
{
    // �� ������, ���� ��������� �� ���������, ����� ������������ ����� ������ � ���������:
    static const unsigned timeMax = 1000;
    // �������� ��� ������� � ������������ ���������. ������� ������ ����� �������� ������� �������
    static const double smallDifference = 0.001;

    // �������� ����� ������ �����:
    std::cout << "The test has been started:\n\n";
    std::cout << std::setw(15) << std::left << "    time"
        << std::setw(15) << std::left << "moment"
        << std::setw(15) << std::left << "velocity"
        << std::setw(15) << std::left << "temperature" << std::endl;

    // ������ ������ ������:
    double velocity = 0.0;
    double temperature = ambTemperature;
    double moment = rotationMoment(velocity);
    unsigned timeSeconds = 0;

    // ���������� ���� � ������� ������������� ������ ���� �� ����������� ��� �� ��������� ������ �� �������:
    while ((abs(overheatTemperature - temperature) > smallDifference) && (timeSeconds < timeMax))
    {
        // ������ 10 ������ ������� ���������:
        if (timeSeconds % (10) == 0)
            printCurrentTestResult(timeSeconds, moment, velocity, temperature);

        ++timeSeconds;

        /* ��� ��������� ��� ����������� ������, ��� ������������ �� �������� ������ �������,
           �� ���� ������������, ��� ������, ����������� �� ������ �������, ������� �� �������� ���������� ������� */
        moment = rotationMoment(velocity);

        /* ������ ����������� � ������������, ��� ������� �� ����������� ������ �������
           � ����������-����������, ������� ��������� ���������. ��� �������� �� �������� � �������
           �� ��� �� ������, ������������ �������� ���������� � ���������� */
        temperature += (heatingVelocity(moment, velocity) + coolingVelocity(temperature));

        /* ������, ����� ��� ������ �� ������ ������� ��������, ��������� ��������,
           ��� ��������� ��� �������� ������ ������� ���� ��������� �� �������: */
        velocity += acceleration(moment);
    }
    // �������� ���������, �� ������� ������������:
    printCurrentTestResult(timeSeconds, moment, velocity, temperature);

    // �������� ���� �����:
    if (timeSeconds >= timeMax)
        std::cout << "The test has been finished, the time limit for test " 
        << timeSeconds << " seconds was reached." << std::endl;
    else
        std::cout << "The test has been finished, the maximum temperature " 
        << overheatTemperature << " C was reached." << std::endl;
}