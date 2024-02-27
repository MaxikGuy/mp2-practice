#ifndef TPOLYNOM_H
#define TPOLYNOP_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "tringlist.h"
#include "tdata.h"
#include "tmonom.h"
#include "tstack.h"

using namespace std;

class TPolynom {
private:
	TRingList<TMonom>* monoms;
	string name;
public:
	TPolynom();
	TPolynom(const string _name);
	TPolynom(const TRingList<TMonom>& ringlist);
	TPolynom(const TPolynom& polynom);
	~TPolynom();

	const TPolynom& operator=(const TPolynom& polynom);

	TPolynom operator+(const TPolynom& polynom);
	TPolynom operator-(const TPolynom& polynom);
	TPolynom operator*(const TPolynom& polynom);
	double operator()(double x, double y, double z);

	TPolynom dif_x() const;
	TPolynom dif_y() const;
	TPolynom dif_z() const;

private:
	vector<string> postfix;
	vector<string> lexems;
	static map<string, int> priority;
	map<string, double> operands;
};

#endif // !TPOLYNOM_H
