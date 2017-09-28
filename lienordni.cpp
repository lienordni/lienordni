lienordni::lienordni() {
	integer="0";
	sign=true;
}

lienordni::lienordni(int x) {
	(*this)=x;
}

lienordni::lienordni(std::string x) {
	(*this)=x;
	this->trim();
}

lienordni::lienordni(std::string x, bool s) {
	integer=x;
	sign=s;
	this->trim();
}

lienordni::lienordni(const lienordni &x) {
	integer=x.getString();
	sign=x.getSign();
}

lienordni::lienordni(lienordni x, bool s) {
	integer=x.getString();
	sign=s;
	this->trim();
}

bool lienordni::operator==(const lienordni x) const {
	return (this->integer == x.getString()) && (this->sign==x.sign);
}

bool lienordni::operator<(const lienordni x) const {

	if(*this==x)
		return false;

	if(sign!=x.getSign()){
		if(!sign)
			return true;
		return false;
	}

	if(sign) {
		if(this->size()<x.size())
			return true;

		if(this->size()>x.size())
			return false;
		// std::cout<<"X"<<std::endl;

		for(int i=0;i<(this->size());++i)
			if(this->getString()[i]!=x.getString()[i]){
				return this->getString()[i]<x.getString()[i];
			}

		// return true;
	}

	if(this->size()>x.size())
		return true;

	if(this->size()<x.size())
		return false;

	for(int i=this->size();i>=0;--i)
		if(this->getString()[i]!=x.getString()[i])
			return (this->getString()[i]<x.getString()[i]);

	// return true;	
}

bool lienordni::operator<=(const lienordni x) const {
	return ((*this)==x) || ((*this)<x);
}

bool lienordni::operator>(const lienordni x) const {
	return !((*this)<=x);
}

bool lienordni::operator>=(const lienordni x) const {
	return !((*this)<x);
}

bool lienordni::operator!=(const lienordni x) const {
	return !((*this)==x);
}

bool lienordni::operator==(const int x) const {
	return ((*this)==lienordni(x));
}

bool lienordni::operator>(const int x) const {
	return ((*this)>lienordni(x));
}

bool lienordni::operator>=(const int x) const {
	return ((*this)>=lienordni(x));
}

bool lienordni::operator<(const int x) const {
	return ((*this)<lienordni(x));
}

bool lienordni::operator<=(const int x) const {
	return ((*this)<=lienordni(x));
}

bool lienordni::operator!=(const int x) const {
	return ((*this)!=lienordni(x));
}

lienordni lienordni::operator+(const lienordni& x) const {
	// std::cout<<"X"<<std::endl;
	lienordni z;
	if(this->getSign()==x.getSign()){
		z= lienordni(lien::sum(*this, x),this->sign);
		// std::cout<<*this<<"  "<<x<<"  "<<z<<std::endl;
		return z;
	}

	if(integer==x.getString()){
		z= lienordni(0);
		// std::cout<<*this<<"  "<<x<<"  "<<z<<std::endl;
		return z;
	}

	if((this->magnitude())>x.magnitude()){
		z= lienordni(lien::difference(*this,x),this->getSign());
		// std::cout<<*this<<"  "<<x<<"  "<<z<<std::endl;
		return z;
	}

	z= lienordni(lien::difference(x, *this), x.getSign());
	// std::cout<<*this<<"  "<<x<<"  "<<z<<std::endl;
	return z;
}

void lienordni::operator+=(lienordni x) {
	(*this)=(*this)+x;
}

lienordni lienordni::operator-(const lienordni& x) const {
	return (*this)+(-x);
}

void lienordni::operator-=(lienordni x) {
	(*this)=(*this)-x;
}

lienordni lienordni::operator-() const {
	lienordni z=*this;
	z.negate();
	return z;
}

lienordni lienordni::operator*(const lienordni& x) const {
	int a,b;

	lienordni c=lien::withoutTrailingZeroes(*this,a);
	lienordni d=lien::withoutTrailingZeroes(x,b);

	lienordni y=lien::product(c,d);
	y.raise(a+b);
	return lienordni(y,!((this->getSign())^(x.getSign())));
}

void lienordni::operator*=(lienordni x) {
	(*this)=(*this)*x;
}

void lienordni::operator=(lienordni x) {
	integer=x.getString();
	sign=x.getSign();
	return;
}

void lienordni::operator=(int x) {
	if(x>=0){
		integer=std::to_string(x);
		sign=true;
		return;
	}

	integer=(std::to_string(x)).substr(1);
	sign=false;
	return;
}

void lienordni::operator=(std::string x) {
	if(!lien::isInteger(x)){
		this->integer="0";
		std::cout<<"Invalid Assignment."<<std::endl;
	}

	if(x[0]=='-'){
		this->integer=x.substr(1);
		this->sign=false;
		return;
	}

	this->integer=x;
	this->sign=true;
	return;

}

char& lienordni::operator[](int i) {
	if(i<0) {
		std::string s;
		for(int n=0;n<(-i);++n)
			s+="0";
		integer.insert(0,s);
		return integer[0];
	}

	if(i>=0 && i<integer.size())
		return integer[i];

	this->raise(i-integer.size()+1);
	return integer[integer.size()-1];

}

std::ostream& operator<<(std::ostream& in, const lienordni& x) {
	in<<((x.getSign())?("\0"):("-"))<<x.integer;
	return in;
}

std::istream& operator>>(std::istream& in, lienordni& x) {

	std::string s;
	in>>s;

	if(!lien::isInteger(s)){
		x=0;
		std::cout<<"Invalid Assignment."<<std::endl;
		return in;
	}

	if(s[0]=='-') {
		x=s.substr(1);
	}
	
	return in;
}

// int lienordni::getIntValue() const { //CHECK
// 	int ret = 0;
// 	int biggest = 214748364753;
// 	for (int i = 0; i < (int)integer.size(); i++) {
// 		int unit = integer[i] - '0';
// 		if (ret > (biggest - unit) / 10.0) return 0;
// 		ret = ret * 10 + unit;
// 	}
	
// 	return ret;
// }

std::string lienordni::getString() const {
	return integer;
}

lienordni lienordni::magnitude() const {
	return lienordni(this->integer);
}

bool lienordni::getSign() const {
	return sign;
}

void lienordni::setSign(bool x) {
	this->sign=x;
	return ;
}

void lienordni::negate() {
	this->sign=!(this->sign);
	return ;
}

int lienordni::size() const{
	return integer.size();
}

void lienordni::raise(int n) {
	for(int i=0;i<n;++i)
		integer+="0";
}

void lienordni::reverse() {
	std::reverse(integer.begin(), integer.end());
}

void lienordni::trim() {
	integer=integer.substr(lien::getTrimIndex(integer));
}

std::string lienordni::substr(int i, int length) const{
	if(length<=0)
		return "0";

	if(i>=integer.size())
		return "0";

	if(i>=0) {
		if(length>integer.size()-i)
			return integer.substr(i);
		return integer.substr(i,length);
	}

	if(length<=(-i))
		return "0";

	if(length<=integer.size()-i)
		return integer.substr(0,length+i);

	return integer;

}

std::string lienordni::substr(int i) const {
	if(i>=0)
		return integer.substr(i);

	return integer;	
}

int lienordni::trailingZeroes() const {
	if(integer.size()<2)
		return 0;
	int i=0;
	while(integer[integer.size()-i-1]=='0')
		i++;
	return i;
}

lienordni lienordni::factorial() const {
	
}