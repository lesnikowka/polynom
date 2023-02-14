#pragma once

#include "Monom.h"


template <size_t N, size_t MAX_DEG>
class Polynom {
	std::list<Monom<N, MAX_DEG>> _monoms;

	void recomposing() {
		_monoms.sort();
		
		if (_monoms.size() >= 2) {
			auto current = _monoms.begin();
			auto next = _monoms.begin();
			++next;

			while (next != _monoms.end()) {
				if ((*current).is_similar(*next)) {
					*next += *current;
					if ((*next).get_coef() == 0) {
						next = _monoms.erase(next);
					}
					_monoms.erase(current);
					current = next;
				}

				else
					++current;

				++next;
			}
		}
	}

public:
	Polynom() = default;
	Polynom(const Polynom& p) : _monoms(p._monoms) {}

	Polynom& operator=(const Polynom& p) {
		_monoms = p._monoms;

		return *this;
	}

	bool operator==(const Polynom& p) const noexcept {
		if (_monoms != p._monoms)
			return false;

		return true;
	}
	bool operator!=(const Polynom& p) const noexcept {
		return !operator==(p);
	}
	
	bool parse(const std::string& s) {
		std::list<Monom<N, MAX_DEG>> monoms;
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
		recomposing();

		return true;
	}

	double calculate(const std::vector<double>& x) const {
		if (N != x.size())
			throw "size of vector doesn't match the number of variables";

		double result = 0;

		for (auto& e : _monoms)
			result += e.calculate(x);

		return result;
	}

	std::string get_str()  const {
		std::string result;

		if (_monoms.size() == 0)
			return "";

		for (auto& e : _monoms) {
			if (e.get_coef() > 0) 
				result += "+";
				
			result += e.get_str();
		}
		
		if (result.front() == '+')
			result = result.substr(1);

		return result;
	}

	Polynom& operator*=(double c) {
		for (auto& e : _monoms)
			e *= c;

		return *this;
	}
	Polynom operator*(double c) const {
		Polynom<N, MAX_DEG> result(*this);

		result *= c;

		return result;
	}

	Polynom& operator+=(const Polynom& p) {
		auto this_it = _monoms.begin();
		auto p_it = p._monoms.begin();
		bool insert_done;
	
		while (p_it != p._monoms.end()) {
			insert_done = false;
			while (this_it != _monoms.end()) {
				if ((*this_it).is_similar(*p_it)) {
					*this_it += *p_it;
					if ((*this_it).get_coef() == 0) {
						this_it = _monoms.erase(this_it);
					}
					else {
						++this_it;
					}
					insert_done = true;
				}
				else if ((*this_it) > (*p_it)) {
					_monoms.insert(this_it, *p_it);
					insert_done = true;
					++this_it;
				}
				else {
					++this_it;
				}
			}
			if (!insert_done) {
				_monoms.push_back(*p_it);
			}
			++p_it;
		}
		return *this;
	}

	Polynom operator+(const Polynom& p) const {
		Polynom<N, MAX_DEG> result(*this);

		result += p;

		return result;
	}
	Polynom& operator-=(const Polynom& p) {
		operator+=(p * (-1));

		return *this;
	}
	Polynom operator-(const Polynom& p) const  {
		Polynom<N, MAX_DEG> result(*this);

		result -= p;

		return result;
	}
};