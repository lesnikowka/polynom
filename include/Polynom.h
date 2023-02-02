#pragma once
#include <vector>
#include <list>
#include <string>

template <size_t N, size_t MAX_DEG>
class Monom {
	std::vector<size_t> _degree;
	double _coef;

	enum class states {
		//start
		minus_or_number_or_x,
		//after minus and after numb after first deg numb
		number_or_x,
		//after number
		number_or_dot_or_x,
		//after dot
		number_after_dot,
		//after x
		number_after_x,
		//after first num after x
		number_or_deg,
		//after deg
		number_after_deg, // => number or x
	};

	bool check_state_machine(const std::string& s) {
		if (s == "") return false;

		states state = states::minus_or_number_or_x;
		for (auto e : s) {
			switch (state) {
			case states::minus_or_number_or_x:
				if (e == '-')
					state = states::number_or_x;
				else if ((int)e >= 48 && (int)e <= 57)
					state = states::number_or_dot_or_x;
				else if (e == 'x')
					state = states::number_after_x;
				else
					return false;
				break;

			case states::number_or_x:
				if ((int)e >= 48 && (int)e <= 57);
				else if (e == 'x')
					state = states::number_after_x;
				else
					return false;
				break;

			case states::number_or_dot_or_x:
				if ((int)e >= 48 && (int)e <= 57);
				else if (e == '.')
					state = states::number_after_dot;
				else if (e == 'x')
					state = states::number_after_x;
				else
					return false;
				break;

			case states::number_after_dot:
				if ((int)e >= 48 && (int)e <= 57)
					state = states::number_or_x;
				else
					return false;
				break;

			case states::number_after_x:
				if ((int)e >= 48 && (int)e <= 57)
					state = states::number_or_deg;

			case states::number_or_deg:
				if ((int)e >= 48 && (int)e <= 57);
				else if (e == '^')
					state = states::number_after_deg;
				else
					return false;
				break;

			case states::number_after_deg:
				if ((int)e >= 48 && (int)e <= 57)
					state = states::number_or_x;
				else
					return false;
				break;
			}
		}

		if (state != states::number_or_x) return false;
	}

	std::vector<size_t> catch_indexes(const std::string& s) {
		std::vector<size_t> indexes;
		size_t start;
		for (size_t i = 0; i < s.size(); i++) {
			if (s[i] == 'x')
				start = i + 1;
			else if (s[i] == '^')
				indexes.push_back((size_t)std::stoul(s.substr(start, i - start)));
		}
		return indexes;
	}

	std::vector<size_t> catch_degrees(const std::string& s) {
		size_t start;
		std::vector<size_t> degrees;
		bool begin = true;
		for (size_t i = 0; i <= s.size(); i++) {
			if (s[i] == '^') {
				begin = false;
				start = i + 1;
			}
			else if (!begin && (i == s.size() || s[i] == 'x'))
				degrees.push_back((size_t)std::stoul(s.substr(start, i - start)));
		}
		return degrees;
	}

	double catch_coef(const std::string& s) {
		double coef = 0;
		for (size_t i = 0; i < s.size(); i++) {
			if (s[i] == 'x') {
				std::string c = s.substr(0, i);
				if (c == "") 
					coef = 1.0;
				else if (c == "-") 
					coef = -1.0;
				else 
					coef = std::stod(c);
			}
		}
		return coef;
	}

	bool check_indexes(const std::vector<size_t>& indexes) {
		for (size_t i = 0; i < indexes.size(); i++)
			for (size_t j = i; j < indexes.size(); j++)
				if (indexes[i] > N || (indexes[i] == indexes[j] && i != j))
					return false;
	}

	bool check_degrees(const std::vector<size_t>& degrees) {
		for (auto e : degrees)
			if (e > MAX_DEG)
				return false;
	}

public:
	Monom() = delete;
	Monom(std::vector<size_t> degree = std::vector<size_t>(), double coef = double()) : _degree(degree), _coef(coef) {}
	Monom(const Monom& m) : _degree(m._degree), _coef(m._coef) {}
	Monom(const std::string& s) {
		parse(s);
	}

	bool parse(std::string s) {
		if (check_state_machine(s)) {
			std::vector<size_t> indexes = catch_indexes(s);
			std::vector<size_t> degrees = catch_degrees(s);

			if (check_indexes(indexes) && check_degrees(degrees)) {
				_degree = std::vector<size_t>(N);
				for (size_t i = 0; i < degrees.size(); i++) {
					_degree[indexes[i]] = degrees[i];
				}
				_coef = catch_coef(s);
				return true;
			}
		}
		return false;
	}


	std::vector<size_t> get_degree() { return _degree; }
	void set_degree(const std::vector<size_t>& degree) { _degree = degree; }

	double get_coef() { return _coef; }
	void set_coef(double coef) { _coef = coef; }

	Monom& operator=(const Monom& m) {
		_degree = m._degree;
		_coef = m._coef;
		return *this;
	}
	bool operator==(const Monom& m) {
		return _degree == m._degree && _coef == m._coef;
	}
	bool operator!=(const Monom& m) {
		return !operator==(m);
	}

	Monom& operator+=(const Monom& m) {
		if (_degree != m._degree) throw "degrees are not equate";
		_coef += m.coef;
		return *this;
		
	}
	Monom operator+(const Monom& m) {
		if (_degree != m._degree) throw "degrees are not equate";
		Monom<double, N> result(*this);
		result._coef += m.coef;
		return result;
	}
	Monom& operator-=(const Monom& m) {
		if (_degree != m._degree) throw "degrees are not equate";
		_coef -= m.coef;
		return *this;
	}
	Monom operator-(const Monom& m) {
		if (_degree != m._degree) throw "degrees are not equate";
		Monom<double, N> result(*this);
		result._coef -= m.coef;
		return result;
	}
	Monom& operator*=(const Monom& m) {
		if (_degree != m._degree) throw "degrees are not equate";
		_coef *= m._coef;
		for (size_t i = 0; i < _degree.size(); i++) {
			_degree[i] += m._degree[i];
		}
		return *this;

	}
	Monom operator*(const Monom& m) {
		if (_degree != m._degree) throw "degrees are not equate";
		Monom<double, N> result(*this);
		result._coef *= m._coef;
		for (size_t i = 0; i < _degree.size(); i++) {
			result._degree[i] += m._degree[i];
		}
		return *this;
	}
};

template <class N, size_t MAX_DEG>
class Polynom {
	
	size_t Max_degree = 10;

	Polynom() = delete;
	Polynom(std::string s) {

	}
};