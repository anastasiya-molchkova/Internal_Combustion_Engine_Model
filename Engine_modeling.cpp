// MAIN //

#include <iostream>
#include "InternalCombustionEngine.h"

int main()
{
    while (true)
    {
        std::cout << "This program models engine work, making calculation of its velocity and temperature\n";
        askAmbTemperature();   // по условию задачи это нужно сделать в начале программы

		// создаём один двигатель внутреннего сгорания, с которым будем работать
		InternalCombustionEngine engineOne(20.0, 120.0, 0.01, 0.0001, 0.1, 
			                     { MomentByVelocity({0, 20}), MomentByVelocity({75,75}),
						           MomentByVelocity({150,200}),MomentByVelocity({200,205}),
						           MomentByVelocity({250,75}), MomentByVelocity({300,0}) });

		while (true) // работа пользователя с двигателем в главном меню
		{
			switch (mainMenu())
			{
			case Users_options::check_data:
				engineOne.showData();
				break;
			case Users_options::change_data:
				engineOne.changeData();
				break;
			case Users_options::start_test:
				engineOne.startTest();
				break;
			case Users_options::finish:
				std::cout << "Good job, it was a pleasure to work with you! See you later!" << std::endl << std::endl;
				return 0;
			}
		}
    }
}