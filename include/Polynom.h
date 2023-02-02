#pragma once
#include <vector>
#include <list>
#include <string>

template <size_t N, size_t MAX_DEG>
class Monom {
	std::vector<size_t> _degree;
	std::string monom_str;
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
				break;
			}
		}
		return coef;
	}

	bool check_indexes(const std::vector<size_t>& indexes) {
		for (size_t i = 0; i < indexes.size(); i++)
			for (size_t j = i; j < indexes.size(); j++)
				if (indexes[i] >= N || (indexes[i] == indexes[j] && i != j))
					return false;
	}

	bool check_degrees(const std::vector<size_t>& degrees) {
		for (auto e : degrees)
			if (e > MAX_DEG)
				return false;
	}

public:
	Monom() = default;
	Monom(const Monom& m) : _degree(m._degree), _coef(m._coef), monom_str(m.monom_str) {}

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
				monom_str = s;
				return true;
			}
		}
		return false;
	}

	std::string get_str() { return monom_str; }

	Monom& operator=(const Monom& m) {
		_degree = m._degree;
		_coef = m._coef;
		monom_str = m.monom_str;
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
		Monom<double, N> result(*this);
		result += m;
		return result;
	}
	Monom& operator-=(const Monom& m) {
		if (_degree != m._degree) throw "degrees are not equate";
		_coef -= m.coef;
		return *this;
	}
	Monom operator-(const Monom& m) {
		Monom<double, N> result(*this);
		result -= m;
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
		Monom<double, N> result(*this);
		result *= m;
		return result;
	}
	Monom& operator*=(double c) {
		coef *= c;
		if (c == 0)
			_degree = std::vector<size_t>();
		return *this;
	}
	Monom operator*(double c) {
		Monom<N, MAX_DEG> result(*this);
		result *= c;
		return result;
	}

};

template <size_t N, size_t MAX_DEG>
class Polynom {
	std::vector<Monom<N, MAX_DEG>> _monoms;
	std::string polynom_str;

public:
	Polynom() = default;
	Polynom(const Polynom& p) : _monoms(p._monoms), polynom_str(p.polynom_str) {}

	Polynom& operator=(const Polynom& p) {
		_monoms = p._monoms;
		polynom_str = p.polynom_str;
	}

	bool operator==(const Polynom& p) {
		if (polynom_str == p.polynom_str)
			return true;
		return false;
	}

	bool operator!=(const Polynom& p) {
		return !operator==(p);
	}
	
	bool parse(const std::string& s) {
		std::vector<Monom<N, MAX_DEG>> monoms;
		Monom<N, MAX_DEG> m;

		size_t start = 0;
		for (size_t i = 0; i <= s.size(); i++) {
			if (s[i] == '-') {
				if (i != 0) {
					if (!m.parse(s.substr(start, i - start)))
						return false;
					monoms.push_back(m);
				}
				start = i;
			}
			else if (s[i] == '+') {
				if (!m.parse(s.substr(start, i - start)))
					return false;
				monoms.push_back(m);
				start = i + 1;
			}
			else if (i == s.size()) {
				if (!m.parse(s.substr(start, i - start)))
					return false;
				monoms.push_back(m);
			}
		}
		_monoms = monoms;
		polynom_str = s;

		return true;
	}
};