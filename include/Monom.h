#pragma once

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cmath>

template <size_t N, size_t MAX_DEG>
class Monom {
	std::vector<size_t> _degree;
	double _coef = 0;


	enum class states {
		minus_or_number_or_x,
		number_or_x,
		number_or_dot_or_x,
		number_after_dot,
		number_after_x,
		number_or_deg,
		number_after_deg,
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
				if ((int)e >= 48 && (int)e <= 57)
					state = states::number_or_dot_or_x;
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


public:
	Monom() = default;
	Monom(const Monom& m) : _degree(m._degree), _coef(m._coef) {}

	bool parse(std::string s) {
		if (check_state_machine(s)) {
			std::vector<size_t> indexes = catch_indexes(s);
			std::vector<size_t> degrees = catch_degrees(s);

			if (check_indexes(indexes) && check_degrees(degrees)) {
				_degree = std::vector<size_t>(N);

				for (size_t i = 0; i < degrees.size(); i++)
					_degree[indexes[i]] = degrees[i];

				_coef = catch_coef(s);

				return true;
			}
		}
		return false;
	}

	double calculate(const std::vector<double>& x) const {
		if (N != x.size())
			throw "size of vector doesn't match the number of variables";

		double result = _coef;

		for (size_t i = 0; i < N; i++)
			result *= std::pow(x[i], _degree[i]);

		return result;
	}

	std::string get_str() const {
		if (_coef == 0)
			return "";

		std::string monom_str = std::to_string(_coef);

		int last_zero = monom_str.size() - 1;
		for (int i = monom_str.size() - 1; i >= 0; i--) {
			if (monom_str[i] != '0') {
				last_zero = i;
				break;
			}
		}

		monom_str = monom_str.substr(0, last_zero + 1);

		for (size_t i = 0; i < _degree.size(); i++) {
			if (_degree[i] != 0) {
				monom_str += 'x';
				monom_str += std::to_string(i);
				monom_str += '^';
				monom_str += std::to_string(_degree[i]);
			}
		}

		return monom_str;
	}
	double get_coef() const { return _coef; }
	std::vector<size_t> get_deg() const { return _degree; }

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
	bool is_similar(const Monom& m) {
		return _degree == m._degree;
	}
	bool operator<(const Monom& m) const {
		for (size_t i = 0; i < _degree.size(); i++) {
			if (_degree[i] < m._degree[i])
				return true;

			else if (_degree[i] > m._degree[i])
				return false;
		}

		return false;
	}
	bool operator>(const Monom& m) const {
		for (size_t i = 0; i < _degree.size(); i++) {
			if (_degree[i] > m._degree[i])
				return true;

			else if (_degree[i] < m._degree[i])
				return false;
		}

		return false;
	}

	Monom& operator+=(const Monom& m) {
		if (!is_similar(m))
			throw "monoms are not similar";

		_coef += m._coef;

		return *this;

	}
	Monom operator+(const Monom& m) const {
		Monom<N, MAX_DEG> result(*this);
		result += m;
		return result;
	}
	Monom& operator-=(const Monom& m) {
		if (!is_similar(m))
			throw "monoms are not similar";
		_coef -= m._coef;
		return *this;
	}
	Monom operator-(const Monom& m) const {
		Monom<N, MAX_DEG> result(*this);
		result -= m;
		return result;
	}
	Monom& operator*=(double c) {
		_coef *= c;
		if (c == 0)
			_degree = std::vector<size_t>();
		return *this;
	}
	Monom operator*(double c) const {
		Monom<N, MAX_DEG> result(*this);
		result *= c;
		return result;
	}
};