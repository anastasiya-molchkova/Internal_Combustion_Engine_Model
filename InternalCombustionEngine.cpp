#include "InternalCombustionEngine.h"

// получаем от пользователя упорядоченные по скорости значения скорость - момент
void InternalCombustionEngine::inputMomentVelocityData()
{
    momentByVelocity.clear();
    static const unsigned minDataNumber = 4; // меньшее количество данных - просто смешно

    /* условия набора данных - они должны возрастать по скорости,
    начинаться с нулевой скорости и заканчиваться нулевым моментом: */
    std::cout << "\nInput new ordered data for velocity and moment, starting from velocity = 0 to moment = 0\n";
    std::cout << "Enter a moment = 0 to finish\n" << std::endl;

    // первые данные - для нулевой скорости
    std::cout << "First velocity (should be zero): ";
    double previous_velocity = get_number(0.0, 0.0);
    std::cout << "First moment (for zero velocity): ";
    double previous_moment = get_number(0.0, 1000.0);
    momentByVelocity.push_back(MomentByVelocity({ previous_velocity, previous_moment}));
    
    // пока недостаточно данных или пока не введёт данные с нулевым моментом
    while ((previous_moment != 0) || (momentByVelocity.size() < minDataNumber))
    {
        if ((previous_moment == 0) && (momentByVelocity.size() < minDataNumber))
            std::cout << "\nPlease continue, since this number of data is not enough...";

        // просим очередные значения, ограничивая скорость снизу предыдущим значением:
        std::cout << "\nthe next velocity: ";
        double current_velocity = get_number(previous_velocity, 1000.0);
        std::cout << "moment for this value: ";
        double current_moment = get_number(0.0, 1000.0);

        // добавляем данные:
        momentByVelocity.push_back(MomentByVelocity({current_velocity, current_moment}));
        
        // для следующего цикла:
        previous_velocity = current_velocity;
        previous_moment = current_moment;
    }
}

// печать значения параметра по его названию из перечисления параметров
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

// показываем текущие начальные данные
void InternalCombustionEngine::showData()
{
    for (int p = 1; p < static_cast<int>(Parameters::parameters_number); ++p)
        printParameter(static_cast<Parameters>(p));
    std::cout << std::endl << std::endl;
}

// переопределяем родительскую функцию режима изменения начальных данных, т.к. в этом классе есть ещё и вектор зависимостей
void InternalCombustionEngine::changeData()
{
    while (true) // пока пользователь хочет менять параметры
    {
        // выбирает параметр для изменения по номеру:
        std::cout << "Choose the parameter number you would like to change:\n";
        for (int p = 1; p < static_cast<int>(Parameters::parameters_number); ++p)
        {
            std::cout << p << " - ";
            printParameter(static_cast<Parameters>(p));
        }
        std::cout << "\n\nYour choice: ";
        int chosenP = get_number(1, static_cast<int>(Parameters::parameters_number) - 1);
        printParameter(static_cast<Parameters>(chosenP));

        // для введения множества значений - отдельная функция
        if (static_cast<Parameters>(chosenP) == Parameters::momentByVelocity)
            inputMomentVelocityData();
        else // задаём новое значение выбранному параметру, подбирая разумные границы:
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
        // новое значение задано, далее спрашиваем, хочет ли продолжить редактировать, и если нет - выходим
        std::cout << "\nNew value for parameter has been saved. Do you want to change other parameters?" << std::endl;
        std::cout << "1 - " << "continue\n";
        std::cout << "2 - " << "finish" << std::endl;
        std::cout << "\nYour choice: ";
        int continueORfinish = get_number(1, 2);
        if (continueORfinish == 2)
            break;
    }
}

// ускорение
double InternalCombustionEngine::acceleration(const double rotationMoment)
{
    return rotationMoment / inertionMoment;
}

// скорость нагревания
double InternalCombustionEngine::heatingVelocity(const double rotationMoment, const double rotationVelocity)
{
    return (rotationMoment * k_HeatByMoment) + (pow(rotationVelocity, 2) * k_HeatByVelocity);
}

// скорость охлаждения
double InternalCombustionEngine::coolingVelocity(const double engineTemperature)
{
    return k_CoolByTemperature * (ambTemperature - engineTemperature);
}

/* функция определяет момент по скорости, исходя из экспериментальных данных об их зависимости
 грубо говоря, мы предполагаем линейное соединение между двумя известными данными, и по скорости ищем значение момента на этом отрезке
 хотя здесь мог бы быть какой-нибудь метод аппрокисмации этой зависимости в виде функции. 
 Например, метод наименьших квадратов выдавал бы нам зависимость в виде полинома. 
 Я проверила, как этот метод работает на данных из задачи и решила не заморачиваться, данных мало,
 погрешность для полинома второй степени получилась довольно большой, поэтому оставляю простой алгоритм */
double InternalCombustionEngine::rotationMoment(const double rotationVelocity)
{
    // определяем ближайщие известные данные со скоростью <= искомой 
    MomentByVelocity closest_lower = momentByVelocity[0];
    MomentByVelocity closest_upper = momentByVelocity[momentByVelocity.size() - 1];

    // сразу проверяем предельные значения скорости, для которых знаем результат:
    if (rotationVelocity <= closest_lower.exp_Velocity)
        return closest_lower.exp_Moment;
    if (rotationVelocity >= closest_upper.exp_Velocity)
        return closest_upper.exp_Moment;

    // ищем наиболее близкие известные значения скорости сверху и снизу:
    for (const auto& data : momentByVelocity)
    {
        // если скорость точно совпала с известной
        if (data.exp_Velocity == rotationVelocity)
            return data.exp_Moment;
        if ((data.exp_Velocity < rotationVelocity)
            && ((rotationVelocity - data.exp_Velocity) < abs(rotationVelocity - closest_lower.exp_Velocity)))
            closest_lower = data;
        if ((data.exp_Velocity > rotationVelocity)
            && ((data.exp_Velocity - rotationVelocity) < abs(rotationVelocity - closest_upper.exp_Velocity)))
            closest_upper = data;
    }

    // определяем момент пропорционально его расстоянию по скорости от известных значений:
    double rotMoment = closest_lower.exp_Moment;
    rotMoment += ((closest_upper.exp_Moment - closest_lower.exp_Moment)
        * (rotationVelocity - closest_lower.exp_Velocity) / (closest_upper.exp_Velocity - closest_lower.exp_Velocity));
    return rotMoment;
}

// печать текущего результата теста 
void InternalCombustionEngine::printCurrentTestResult(const unsigned timeSeconds, const double moment, const double velocity, const double temperature)
{
    // время печатаем как минуты и секунды
    std::cout << std::setw(3) << timeSeconds / 60 << "min " << std::setw(2) << timeSeconds % 60 << "sec  ";
    // остальное округляем до 3-го знака после запятой:
    std::cout << std::setw(15) << round(moment * 1000) / 1000;
    std::cout << std::setw(15) << round(velocity * 1000) / 1000;
    std::cout << std::setw(15) << round(temperature * 1000) / 1000 << std::endl;
}

// тест двигателя внутреннего сгорания
void InternalCombustionEngine::startTest()
{
    // на случай, если перегрева не произойдёт, задаём максимальное время работы в секунудах:
    static const unsigned timeMax = 1000;
    // значение для разницы с температурой перегрева. Разницу меньше этого значения считаем нулевой
    static const double smallDifference = 0.001;

    // печатаем шапку начала теста:
    std::cout << "The test has been started:\n\n";
    std::cout << std::setw(15) << std::left << "    time"
        << std::setw(15) << std::left << "moment"
        << std::setw(15) << std::left << "velocity"
        << std::setw(15) << std::left << "temperature" << std::endl;

    // данные начала работы:
    double velocity = 0.0;
    double temperature = ambTemperature;
    double moment = rotationMoment(velocity);
    unsigned timeSeconds = 0;

    // производим тест с печатью промежуточных данных пока не перегреется или не достигнем лимита по времени:
    while ((abs(overheatTemperature - temperature) > smallDifference) && (timeSeconds < timeMax))
    {
        // каждые 10 секунд выводим результат:
        if (timeSeconds % (10) == 0)
            printCurrentTestResult(timeSeconds, moment, velocity, temperature);

        ++timeSeconds;

        /* для ускорения нам понадобится момент, его рассчитываем по скорости предыд секунды,
           то есть предполагаем, что момент, действующий на данной секунде, зависит от скорости предыдущей секунды */
        moment = rotationMoment(velocity);

        /* теперь разбираемся с температурой, она зависит от температуры предыд секунды
           и нагревания-охлаждения, которые действуют постоянно. Нам известны их скорости в секунду
           по той же логике, предполагаем скорости охлаждения и нагревания */
        temperature += (heatingVelocity(moment, velocity) + coolingVelocity(temperature));

        /* теперь, когда все данные по предыд секунде полученй, вычисляем скорость,
           она считается как скорость предыд секунды плюс ускорение за секунду: */
        velocity += acceleration(moment);
    }
    // печатаем результат, на котором остановились:
    printCurrentTestResult(timeSeconds, moment, velocity, temperature);

    // подводим итог теста:
    if (timeSeconds >= timeMax)
        std::cout << "The test has been finished, the time limit for test " 
        << timeSeconds << " seconds was reached." << std::endl;
    else
        std::cout << "The test has been finished, the maximum temperature " 
        << overheatTemperature << " C was reached." << std::endl;
}