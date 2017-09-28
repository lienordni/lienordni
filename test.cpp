#ifndef LIENORDNI_H
#define LIENORDNI_H

#include <iostream>
#include <algorithm>
#include <sstream>

class lienordni {

private:
	std::string integer;
	bool sign;

public:
	lienordni();
	lienordni(int);
	lienordni(std::string);
	lienordni(std::string, bool);
	lienordni(const lienordni &x);
	lienordni(lienordni, bool);

	bool operator==(const lienordni) const;
	bool operator>(const lienordni) const;
	bool operator>=(const lienordni) const;
	bool operator<(const lienordni) const;
	bool operator<=(const lienordni) const;
	bool operator!=(const lienordni) const;

	bool operator==(const int) const;
	bool operator>(const int) const;
	bool operator>=(const int) const;
	bool operator<(const int) const;
	bool operator<=(const int) const;
	bool operator!=(const int) const;

	lienordni operator+(const lienordni&) const;
	void operator+=(lienordni);

	lienordni operator-(const lienordni&) const;
	void operator-=(lienordni);

	lienordni operator*(const lienordni&) const;
	void operator*=(lienordni);

	lienordni operator%(const lienordni&) const;
	void operator%=(lienordni);

	lienordni operator/(const lienordni&) const;
	void operator/=(lienordni);

	lienordni operator-() const;
	
	void operator++();
	void operator--();

	void operator=(lienordni);
	void operator=(int);
	void operator=(std::string);

	char& operator[] (int i);

	friend std::ostream& operator<<(std::ostream&, const lienordni&);
	friend std::istream& operator>>(std::istream&, lienordni&);

	// int getIntValue() const; // Returns 0 if number is greater than 32 bits.
	std::string getString() const;
	lienordni magnitude() const;
	bool getSign() const;
	void setSign(bool);
	void negate();

	int size() const;
	void raise(int);
	void reverse();
	
	std::string substr(int, int) const;
	std::string substr(int) const;
	
	void trim();
	int trailingZeroes() const ;

	// lienordni factorial() const ;

};

namespace lien {
	bool isInteger(std::string);
	lienordni sum(lienordni, lienordni);
	lienordni difference(lienordni, lienordni);
	lienordni normal_product(lienordni, lienordni);
	lienordni product(lienordni, lienordni);
	size_t getTrimIndex(const std::string&);
	inline lienordni withoutTrailingZeroes(lienordni);
	lienordni withoutTrailingZeroes(lienordni, int&);
}

bool lien::isInteger(std::string integer) {
	if(integer[0]=='-')
		return lien::isInteger(integer.substr(1));

	for (int i = 0; i < (int) integer.size() ; i++) {
		if(integer[i] < '0' || integer[i] > '9')
			return false;
	}
	return true;
}

lienordni lien::sum(lienordni x, lienordni y) { // Always assumes both are positive

	int a_n = std::max((int)(y.getString().size() - x.getString().size()), 0);
	int b_n = std::max((int)(x.getString().size() - y.getString().size()), 0);
	std::string a = std::string(a_n, '0') + x.getString();
	std::string b = std::string(b_n, '0') + y.getString();

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	std::string result; int carry = 0;

	for (int i = 0; i < (int)a.size(); i++) {
	   int sum = (a[i] - '0') + (b[i] - '0') + carry;
	   result += ((char)(sum % 10 + '0'));
	   carry = sum / 10;
	}

	if (carry != 0) result += ((char)(carry + '0'));

	reverse(result.begin(), result.end());

	return lienordni(result.substr(lien::getTrimIndex(result)));

}

lienordni lien::difference(lienordni a, lienordni b) { // Always assumes x>y and both are positive.
	std::string x=a.getString();
	std::string y=b.getString();

	reverse(x.begin(), x.end());
	reverse(y.begin(), y.end());

	// std::cout<<x<<std::endl;
	// std::cout<<y<<std::endl;

	lienordni r=0;

	int i;

	for(i=0;i<y.size();++i){
		if(x[i]<y[i]){
			x[i]+=10;
			x[i+1]--;
		}
		r[i]=x[i]-y[i]+'0';
	}

	while(i<x.size()){
		if(x[i]=='0'-1){
			r[i]='9';
			x[i+1]--;
			i++;
			continue;
		}
		r[i]=x[i];
		i++;
	}

	r.reverse();
	return r;
}

lienordni lien::normal_product(lienordni x, lienordni y) { // Always assumes both are positive.
	std::string a = y.getString();
	std::string b = x.getString();

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	lienordni ret("0");

	for (int i = 0; i < (int)a.size(); i++) {
		int carry = 0; std::string tmp = std::string(i, '0');

		for (int j = 0; j < (int)b.size(); j++) {
			int mul = (a[i] - '0') * (b[j] - '0') + carry;
			tmp += ((char)(mul % 10 + '0'));
			carry = mul / 10;
		}

		if (carry != 0) tmp += (carry + '0');

		reverse(tmp.begin(), tmp.end());

		ret +=(tmp.substr(getTrimIndex(tmp)));
	}

	return ret;
}

lienordni lien::product(lienordni x, lienordni y) { // Always Assumes both are positive.
	if(y>x)
		return lien::product(y,x);

	if(y==0)
		return 0;

	if(y==1)
		return x;

	if(x<10 || y<10)
		return lien::normal_product(y,x);

	int m=std::max(x.size(), y.size());
	int m2=m/2;

	lienordni h1(x.substr(0,m2));
	lienordni l1(x.substr(m2));

	lienordni h2(y.substr(0,y.size()-(x.size()-m2)));
	lienordni l2(y.substr(y.size()-(x.size()-m2)));
	
	lienordni z0, z1, z2;

	z0=lien::product(l1,l2);
	z2=lien::product(h1,h2);
	z1=lien::product(l1+h1,l2+h2)-z0-z2;

	z2.raise(2*(x.size()-m2));
	z1.raise(x.size()-m2);

	return z0+z1+z2;
}

size_t lien::getTrimIndex(const std::string& s) {
	size_t index = 0;
	
	while (s[index] == '0' && index < s.size() - 1)
		index++;

	return index;
}

inline lienordni lien::withoutTrailingZeroes(lienordni x) {
	return x.substr(0,x.size()-x.trailingZeroes());
}

lienordni lien::withoutTrailingZeroes(lienordni x, int& n) {
	n=x.trailingZeroes();
	return x.substr(0,x.size()-n);
}

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

lienordni lienordni::operator%(const lienordni& x) const {
	if(x==2){
		return lienordni(int((this->getString())[((this->getString()).size())-1])%2);
	}
}

void lienordni::operator%=(lienordni x){

}

lienordni lienordni::operator/(const lienordni& x) const{
	if(x==2){
		std::string s;
		int i;
		int c=0;
		std::string dividend=this->getString();
		for(i=0;i<dividend.size();++i){
			s+=std::to_string((10*c+int(dividend[i])-'0')/2);
			c=(10*c+int(dividend[i])-'0')%2;
		}
		return s;
		
	}
}

void lienordni::operator/=(lienordni x){

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

#endif

int main() {
	lienordni n("1283761238476185");
	std::cout<<n/2<<std::endl;
}