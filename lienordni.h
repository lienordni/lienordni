/*

Lienordni Class
Copyright (C) 2016 Indroneil Kanungo

Can be used to perform basic arithmetic operations for very large integers.

It stores and manipulates a number as a string and operations for Addition, 
Subtraction and Multiplication (Karatsuba Algorithm) as been implemented so far.

Feel free to contribute to this repository or make your own version of it.

This program is free software. You can redistribute it and/or modify it under the terms
of the GNU General Public License,
as published by the Free Software Foundation.

This program has been published in the hope that it would be useful and
it comes without any warranty; without even the implied warranty of
merchantibility or fitness for a particular purpose. See the
GNU General Public License for more details.

You should have recieved a copy of the GNU Public License along with this file.
If not, please visit (https://www.gnu.org/licenses/gpl.txt)

*/


/* 

Things to be added : 

	increment operators
	division
	remainder
	extras : factorial

*/

#ifndef LIENORDNI_H
#define LIENORDNI_H

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

	lienordni operator-() const;
	
	void operator++();
	void operator--();

	void operator=(lienordni);
	void operator=(int);
	void operator=(std::string);

	// int operator[] (int i);
	// int operator[] (int i);	
	char& operator[] (int i);

	friend std::ostream& operator<<(std::ostream&, const lienordni&);
	friend std::istream& operator>>(std::istream&, lienordni&);

	int getIntValue() const; // Returns 0 if number is greater than 32 bits.
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

	lienordni factorial() const ;

};

#include "lien_namespace.cpp"
#include "lienordni.cpp"

#endif

/*
1) unsigned int functionality
2) Type convertor functions.
*/