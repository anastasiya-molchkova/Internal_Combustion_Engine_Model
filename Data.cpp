#include "Data.h"

// температура окружающей среды, градусы цельсия
double ambTemperature{ 20 };

// получаем от пользователя число в заданных границах, много где понадобится
template <typename T>
T get_number(const T min, const T max)
{
    T answer;
    std::cin >> answer;
    while (std::cin.fail() || (answer < min) || (answer > max))
    {
        std::cin.clear();
        std::cin.ignore(2000, '\n');
        std::cout << "It should be a number from " << min << " to " << max << ", please correct your input: ";
        std::cin >> answer;
    }
    return answer;
}

// основной диалог с пользователем, получает ответ от пользователя, что он хочет делать (для MAIN)
Users_options mainMenu()
{
    std::cout << std::endl;
    std::cout << "Choose the number for one of the following options:" << std::endl;
    std::cout << static_cast<int>(Users_options::check_data) << "  -  check initial data  " <<
        static_cast<int>(Users_options::change_data) << "  -  change initial data \n" <<
        static_cast<int>(Users_options::start_test) << "  -  start test          " <<
        static_cast<int>(Users_options::finish) << "  -  finish" << std::endl;

    std::cout << "\nYour choice: ";
    int choice = get_number(1, static_cast<int>(Users_options::options_number) - 1);

    return static_cast<Users_options>(choice);
}

// запрос нового значения для температуры окружающей среды 
void askAmbTemperature()
{
    std::cout << "At first, please let us know the ambient temperature: ";
    ambTemperature = get_number(-50.0, 50.0);
}