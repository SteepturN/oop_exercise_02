#include <cmath>
#include <iostream>
//1 фунт = 20 шиллингов, 1 шиллинг = 12 пенни.
class BritishMoney{
	public:
	BritishMoney(unsigned long long funt, unsigned char shil, unsigned char penny)
	:	funt(funt), shil(shil), penny(penny) {};
	//1 фунт = 20 шиллингов, 1 шиллинг = 12 пенни
	BritishMoney operator+(const BritishMoney& bm) const noexcept{
		int conv_penny = (penny+bm.penny)/12;
		int _penny = (penny+bm.penny)%12;
		int conv_shil = (shil+bm.shil+conv_penny)/20;
		int _shil = (shil+bm.shil+conv_penny)%20;
		unsigned long long _funt = funt+bm.funt+conv_shil;
		return BritishMoney(_funt, _shil, _penny);
	}
	BritishMoney operator-(const BritishMoney& bm) const noexcept{
		int k = bm < (*this) ? 1 : 0;
		unsigned long long _funt = (funt-bm.funt)*k;
		int _shil = (shil-bm.shil)*k;
		int _penny = (penny-bm.penny)*k;
		if(_penny < 0) {_shil-=1; _penny+=12;}
		if(_shil < 0) {_funt-=1; _shil+=20;}
		return BritishMoney(_funt, _shil, _penny);
	}
	double operator/(const BritishMoney& bm) const noexcept{
		return (funt+shil/12.0+penny/240.0)/(bm.funt+bm.shil/12.0+bm.penny/240.0);
	}
	BritishMoney operator/(const long double& num) const noexcept{
		if(num == 0) return BritishMoney(0, 0, 0);
		long double res = (funt+shil/12.0L+penny/240.0L)/num;
		unsigned long long _funt = trunc(res);
		unsigned char _shil = static_cast<unsigned char>(trunc((res-_funt)*20));
		unsigned char _penny = static_cast<unsigned char>(trunc(((res-_funt)*20-_shil)*12));
		return BritishMoney(_funt, _shil, _penny);
	}
	BritishMoney operator*(const long double& num) const noexcept{
		long double res = (funt+shil/12.0L+penny/240.0L)*num;
		unsigned long long _funt = trunc(res);
		unsigned char _shil = static_cast<unsigned char>(trunc((res-_funt)*20));
		unsigned char _penny = static_cast<unsigned char>(trunc(((res-_funt)*20-_shil)*12));
		return BritishMoney(_funt, _shil, _penny);
	}
	bool operator<(const BritishMoney& bm) const noexcept{
		if(funt < bm.funt) return true;
		else if(funt == bm.funt){
			if(shil < bm.shil) return true;
			else if(shil == bm.shil)
				return penny < bm.penny;
			else return false;
		}
		else return false;
	}
	void print(){
		std::cerr << "фунты = " << funt << ", шиллинги = " << static_cast<int>(shil) << ", пенсы = " << static_cast<int>(penny);
	}
	BritishMoney exec(const char* command, const BritishMoney& bm) const noexcept {
		if(static_cast<std::string>(command) == "a") return *this+bm;
		else if(static_cast<std::string>(command) == "s") return *this-bm;
		else return BritishMoney(0,0,0);
	}
	BritishMoney exec(const char* command, const double koef) const noexcept {
		if(static_cast<std::string>(command) == "dbn") return *this/koef;
		else if(static_cast<std::string>(command) == "m") return *this*koef;
		else return BritishMoney(0,0,0);
	}
	unsigned long long funt;
	unsigned char shil;
	unsigned char penny;
};
