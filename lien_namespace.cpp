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