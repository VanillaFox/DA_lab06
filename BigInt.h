#pragma once
#include<iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

const int BASE = 10000;
const int BASE_POW = 4;

class TBigInt {
private:
	std::vector<int> Number;
public:
    TBigInt() = default;
	TBigInt(std::string& num);
	~TBigInt();

	TBigInt operator+(TBigInt& second);
	TBigInt operator-(TBigInt& second);
	TBigInt operator*(TBigInt& second);
	TBigInt operator*(int second);

	bool operator>(TBigInt& second);
	bool operator<(TBigInt& second);
	bool operator==(TBigInt& second);

	TBigInt operator/(TBigInt& second);
	TBigInt operator/(int second);
	TBigInt operator^(TBigInt& second);
	TBigInt operator^(int second);

	TBigInt& operator=(TBigInt second);
	friend std::ostream& operator<<(std::ostream&, const TBigInt&);
};
