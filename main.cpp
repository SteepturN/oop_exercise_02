/*
Бутырев М8О-206Б-20
Создать класс BritishMoney для работы с денежными суммами в старой британской система.
Сумма денег должна быть представлено тремя полями:
-типа unsigned long long для фунтов стерлингов,
-типа unsigned char – для шиллингов,
-unsigned char – для пенсов (пенни).
Реализовать
сложение сумм,
вычитание,
деление сумм,
деление суммы на дробное число,
умножение на дробное число и
операции сравнения.
1 фунт = 20 шиллингов, 1 шиллинг = 12 пенни.
*/
#include <iostream>
#include <string>
#include "BritishMoney.cpp"
#include "Read_input.cpp"
#include <cstdio>
#include <set>
int main(){
	const char a[] = "You can use\n\
--add: a (funt1) (shilling1) (penny1) (funt2) (shilling2) (penny2)\n\
--subtraction: s (funt1) (shilling1) (penny1) (funt2) (shilling2) (penny2)\n\
--division of sums: d (funt1) (shilling1) (penny1) (funt2) (shilling2) (penny2)\n\
--sum1 < sum2: lth (funt1) (shilling1) (penny1) (funt2) (shilling2) (penny2)\n\n\
--divide by number: dbn (funt1) (shilling1) (penny1) (real number)\n\
--multiplication by number: m (funt1) (shilling1) (penny1) (real number)\n\n\
--exit\n";
	long double input_real_number(0.0);
	unsigned long long funt1n(0), funt2n(0); unsigned int shil1n(0), shil2n(0), penny1n(0), penny2n(0);
	int conv_penny(0), conv_shil(0);
	BritishMoney bm1(0,0,0);
	BritishMoney bm2(0,0,0);
	
	char ch(' ');
	char command[20];
	std::set<std::string> valid_commands = {"a", "s", "d", "dbn", "m", "lth", "exit"};
	std::cout << a;
	do {
		bool exit = false;
		do{
			read_return_t answer = get_command(valid_commands, command);
			switch(answer) {
				case END_OF_FILE: return 0;
				case END_OF_LINE: continue;
				case VALID_INPUT: exit = true; break;
				case INVALID_INPUT:
					do ch=getchar(); while((ch != EOF) && (ch != '\n'));
					std::cout << "wrong input" << std::endl;
					if(ch == EOF) return 0;
					else break;
				}
		} while(!exit);
		if(static_cast<std::string>(command) == "exit") return 0;
		if((get_value<unsigned long long>(funt1n) != VALID_INPUT) || (get_value<unsigned int>(shil1n) != VALID_INPUT) || (get_value<unsigned int>(penny1n) != VALID_INPUT)) {
			do ch = getchar(); while((ch != EOF) && (ch != '\n'));
			std::cout << "wrong input" << std::endl;
			if(ch == EOF) return 0;
			continue;
		}
		if((static_cast<std::string>(command) == "dbn") || (static_cast<std::string>(command) == "m")) {
			if((get_value<long double>(input_real_number) != VALID_INPUT) || (input_real_number < 0)) {
				do ch=getchar(); while((ch != EOF) && (ch != '\n'));
				std::cout << "wrong input" << std::endl;
				if(ch == EOF) return 0;
				continue;
			}
		} else if((get_value<unsigned long long>(funt2n) != VALID_INPUT) || (get_value<unsigned int>(shil2n) != VALID_INPUT) || (get_value<unsigned int>(penny2n) != VALID_INPUT)) {
			do ch = getchar(); while((ch != EOF) && (ch != '\n'));
			std::cout << "wrong input" << std::endl;
			if(ch == EOF) return 0;
			continue;
		}

		conv_penny = (penny1n)/12;
		bm1.penny = (penny1n)%12;
		conv_shil = (shil1n+conv_penny)/20;
		bm1.shil = (shil1n+conv_penny)%20;
		bm1.funt = funt1n+conv_shil;

		conv_penny = (penny2n)/12;
		bm2.penny = (penny2n)%12;
		conv_shil = (shil2n+conv_penny)/20;
		bm2.shil = (shil2n+conv_penny)%20;
		bm2.funt = funt2n+conv_shil;

		bm1.print();
		std::cout << '\t' << command << '\t';
		if((static_cast<std::string>(command) == "dbn") || (static_cast<std::string>(command) == "m")) {
			std::cout << input_real_number << '\t';
		} else {
			bm2.print();
		}
		std::cout << '\t' << '=' << '\t';


		if((static_cast<std::string>(command) == "dbn") || (static_cast<std::string>(command) == "m")) {
			if((input_real_number == 0) && (static_cast<std::string>(command) == "dbn"))
				std::cout << "division by 0 is forbidden";
			else bm1.exec(command, input_real_number).print();
		} else if (static_cast<std::string>(command) == "lth") {
			std::cout << (bm1<bm2);
		} else if (static_cast<std::string>(command) == "d") {
			std::cout << (bm1/bm2);
		} else {
			bm1.exec(command, bm2).print();
		}
		std::cout << std::endl;

	} while(true);
	return 0;
}
