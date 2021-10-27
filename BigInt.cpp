#include "BigInt.h"

TBigInt::TBigInt(std::string& num){
    int k = 0, in = 0;
	int start, finish;
	std::stringstream str;
	if (num[0] == '0') {
		while (num[k] == '0') {
			k++;
		}
	}

	for(int i = num.length() - 1; i > k - 1; i -= BASE_POW) {
		finish = ((i - (k - 1)) > BASE_POW - 1) ? BASE_POW : i - k + 1;
		start = i - finish + 1;
		str << num.substr(start, finish);
		str >> in;
		Number.push_back(in);
		str.clear();
	}
	if (k == num.length()) {
		Number.push_back(0);
	}
}


TBigInt::~TBigInt(){
	Number.clear();
}


TBigInt TBigInt::operator+(TBigInt& second) {
	int f_size = Number.size();
	int s_size = second.Number.size();
	int new_size = std::max(f_size, s_size);
	int k = 0;
	long long sum = 0;

	TBigInt res;

	for (int i = 1; i <= new_size; i++) {
		if (f_size < i) {
			sum = second.Number[i - 1];
		}
		else if (s_size < i) {
			sum = Number[i - 1];
		}
		else {
			sum = Number[i - 1] + second.Number[i - 1];
		}
		sum += k;
		res.Number.push_back(sum % BASE);
		k = sum / BASE;
	}

	if (k != 0) {
		res.Number.push_back(k);
	}

	return res;
}


TBigInt TBigInt::operator-(TBigInt& second) {
	int f_size = Number.size();
	int s_size = second.Number.size();

	if (*this < second) {
		throw -1;
	}

	TBigInt res;
	long long  tmp;
	int a, b, k = 0;
	for (long long i = 0; i < Number.size() || k; i++) {
		a = i < Number.size() ? Number[i] : 0;
		b = i < second.Number.size() ? second.Number[i] : 0;
		tmp = a - b - k;
		k = 0;
		if (tmp < 0) {
			tmp += BASE;
			k = 1;
		}
		res.Number.push_back(tmp);
	}

	while (res.Number.size() > 1 && !res.Number.back()){
		res.Number.pop_back();
	}
	return res;
}


TBigInt TBigInt::operator*(TBigInt& second) {
	if (Number.size() == 1) {
		return second * Number[0];
	}
	else if (second.Number.size() == 1) {
		return (*this) * second.Number[0];
	}
	
	int k;
	int f_size = Number.size();
	int s_size = second.Number.size();
	TBigInt res;
	long long sec, r;
	res.Number.resize(f_size + s_size + 1);
	for (int i = 0; i < f_size; i++) {
		k = 0;
		for (int j = 0; (j < s_size) || k; j++) {
			sec = (j < s_size) ? second.Number[j] : 0;
			r = sec * Number[i] + k + res.Number[i + j];
			res.Number[i + j] = r % BASE;
			k = r / BASE;
		}
		res.Number[i + s_size] += k;
	}

	while (res.Number.size() > 1 && !res.Number.back()) {
		res.Number.pop_back();
	}

	return res;
}


TBigInt TBigInt::operator*(int second) {
	TBigInt res;
	long long k = 0, cur, r;
	for (long long i = 0; i < Number.size() || k; i++) {
		cur = (i < Number.size()) ? Number[i] : 0;
		r = cur * second + k;
		res.Number.push_back(r % BASE);
		k = r / BASE;
	}
    while (res.Number.size() > 1 && !res.Number.back()) {
		res.Number.pop_back();
	}
	return res;
}


bool TBigInt::operator>(TBigInt& second) {
	if(Number.size() < second.Number.size()){
		return false;
	}
	else if(Number.size() > second.Number.size()){
		return true;
	}
	else{
		bool ans = false;
		for (int i = Number.size() - 1; i >= 0 && ans == false; i--) {
			if (Number[i] > second.Number[i]) {
				ans = true;
			}
			else if(Number[i] < second.Number[i]){
				return false;
			}
		}
		return ans;
	}
}


bool TBigInt::operator<(TBigInt& second) {
	return ((*this > second) || (*this == second)) ? false : true;
}


bool TBigInt::operator==(TBigInt& second) {
	bool ans = true;
	if (Number.size() != second.Number.size()) {
		ans = false;
	}
	else {
		for (int i = Number.size() - 1; i >= 0 && ans == true; i--) {
			if (!(Number[i] == second.Number[i])) {
				ans = false;
			}
		}
	}
	return ans;
}


TBigInt& TBigInt::operator=(TBigInt second) {
		if (&second == this) {
			return *this;
		}
		if (Number.size() < second.Number.size()) {
			Number.resize(second.Number.size());
		}
		Number.assign(Number.size(), 0);
		std::copy(second.Number.begin(), second.Number.begin() + second.Number.size(), Number.begin());

		return *this;
}


std::ostream& operator<<(std::ostream& stream, const TBigInt& num) {
	int n = num.Number.size();
	stream << num.Number[n - 1];
	for (int i = n - 2; i >= 0; --i) {
		stream << std::setfill('0') << std::setw(BASE_POW) << num.Number[i];
	}
	return stream;
}


TBigInt TBigInt::operator/(TBigInt& second) {
	TBigInt res, tmp;
	if(second > (*this)){
		res.Number.push_back(0);
		return res;
	}
	if(second.Number.size() == 1){
		if(second.Number[0] == 0){
			throw -1;
		}
		else{
			return (*this) / second.Number[0];
		}
	}
	long long n = second.Number.size();
	long long d, curr, rem, guess;
	long long a, b;
	long long m = Number.size() - n;
	d = BASE / (second.Number.back() + 1);
	Number.push_back(0);
	tmp = (*this);
	if(d > 1){
		tmp = tmp * d;
		second = second * d;
	}
	for(int j = m; j >= 0; j--){
		curr = (tmp.Number[n + j] * BASE + tmp.Number[j + n - 1]);
		rem = curr % second.Number[n - 1];
		guess = curr / second.Number[n - 1];

		while(rem < BASE){
			a = guess * second.Number[n - 2];
			b = BASE * rem + tmp.Number[j + n - 2];
			if(guess == BASE || a > b){
				guess--;
				rem += second.Number[n - 1];
			}else break;
		}

		TBigInt cur = second;
		TBigInt mult;
		for(int i = j; i > 0; i--){
			cur = cur * BASE;
		}

		mult = cur * guess;
		try{
			tmp = tmp - mult;
		}
		catch(int c){
			guess--;
			mult = cur * guess;
			tmp = tmp - mult;
		}
		res.Number.push_back(guess);
	}
	
	std::reverse(res.Number.begin(), res.Number.end());
	while (res.Number.size() > 1 && !res.Number.back()) {
		res.Number.pop_back();
	}
	return res;
}


TBigInt TBigInt::operator/(int second) {
	long long rem = 0, guess;
	TBigInt res;
	for(int i = (*this).Number.size(); i > 0; i--){
		guess = ((*this).Number[i - 1] + rem * BASE) / second;
		rem = (*this).Number[i - 1] + rem * BASE - guess*second;
		res.Number.push_back(guess);
	}
	std::reverse(res.Number.begin(), res.Number.end());
	while (res.Number.size() > 1 && !res.Number.back()) {
		res.Number.pop_back();
	}
	return res;
}


TBigInt TBigInt::operator^(int second){
	TBigInt res;
	TBigInt cur = (*this);
	res.Number.push_back(1);
	while(second){
		if(second % 2 != 0){
			res = res * cur;
		}

		cur = cur * cur;
		second /= 2;
	}
	return res;
}

TBigInt TBigInt::operator^(TBigInt& second){
	if(second.Number.size() == 1){
		if(second.Number[0] == 0){
			if((*this).Number.size() == 1 && (*this).Number[0] == 0){
				throw -1;
			}
			else{
				TBigInt res;
				res.Number.push_back(1);
				return res;
			}
		}
		else if(second.Number[0] == 1){
			return (*this);
		}
		return ((*this) ^ second.Number[0]);

	}
	TBigInt res;
	TBigInt cur = (*this);
	res.Number.push_back(1);
	while(!(second.Number.size() == 1 && second.Number[0] == 0)){
		if(second.Number[0] % 2 != 0){
			res = res * cur;
		}
		cur = cur * cur;
		second = second / 2;
		while (second.Number.size() > 1 && !second.Number.back()) {
			second.Number.pop_back();
		}
	}
	return res;
}