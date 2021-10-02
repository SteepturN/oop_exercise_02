
class BritishMoney{
	public:
	BritishMoney(unsigned long long funt, unsigned char shil, unsigned char penny)
	:	funt(funt), shil(shil), penny(penny) {};
	private:
	unsigned long long funt;
	unsigned char shil;
	unsigned char penny;
	//1 фунт = 20 шиллингов, 1 шиллинг = 12 пенни
	BritishMoney operator+(const BritishMoney& bm) const noexcept{
		int conv_penny = (penny+bm.penny)/12;
		int _penny = (penny+bm.penny)%12;
		int conv_shil = (shil+bm.shil+conv_penny)/20;
		int _shil = (shil+bm.shil+conv_penny)%20;
		int _funt = funt+bm.funt+conv_shil;
		return BritishMoney(_funt, _shil, _penny);
	}
	BritishMoney operator-(const BritishMoney& bm) const noexcept{
		int k = bm<this*? 1 : -1;
		int _funt = (funt-bm.funt)*k;
		int _shil = (shil-bm.shil)*k;
		int _penny = (penny-bm.penny)*k;
		if(_penny < 0) _shil-=1; _penny+=12;
		if(_shil < 0) _funt-=1; _shil+=20;
		return BritishMoney(_funt*k, _shil*k, _penny*k);
	}
	double operator/(const BritishMoney& bm) const noexcept{
		return (funt+shil/12.0+penny/240.0)/(bm.funt+bm.shil/12.0+bm.penny/240.0);
	}
	BritishMoney operator/(double& num) const noexcept{
		long double res = (funt+shil/12.0+penny/240.0)/num;
		unsigned long long _funt = trunc(value);
		unsigned char _shil = trunc((res-funt)*12);
		unsigned char _penny = trunc(((res-funt)*12-_shil)*20);
		return BritishMoney(_funt, _shil, _penny);
	}
	BritishMoney operator*(double& num) const noexcept{
		int conv_penny = (penny*num)/12;
		int _penny = (penny*num)%12;
		int conv_shil = (shil*num+conv_penny)/20;
		int _shil = (shil*num+conv_penny)%20;
		int _funt = funt*num+conv_shil;
		return BritishMoney(_funt, _shil, _penny);
	}
	bool operator<(const BritishMoney& bm) const noexcept{
		if(funt < bm.funt) return true;
		else if(funt == bm.funt){
			if(shil < bm.shil) return true;
			else if(shil == bm.shil)
				return penny < penny.bm;
			else return false;
		}
		else return false;
	}
}
