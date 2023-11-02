#include <iostream>
#include <string>
#include <vector>

class BooleanFunction {
public:
	explicit BooleanFunction(const std::string value) : m_value(value) {}

	void print() {
		size_t index = 0;

		for (int x = 0; x <= 1; ++x) {
			for (int y = 0; y <= 1; ++y) {
				for (int z = 0; z <= 1; ++z) {
					std::cout << x << ' ' << y << ' ' << z << ' ' << m_value[index] << std::endl;
					index++;
				}
			}
		}
	}

	char& operator[](const int element) {
		return m_value[element];
	}

	bool operator==(const BooleanFunction& other) {
		if (m_value == other.m_value) {
			return true;
		}

		return false;
	}

	BooleanFunction findDouble() {
		BooleanFunction temp(m_value);

		for (size_t i = 0; i < m_value.size(); ++i) {
			bool val = (m_value[i] == '1');
			temp[i] = static_cast<char>(!val + '0');
		}

		temp.reverse();

		return temp;
	}

	bool isSelfDoubled() {
		BooleanFunction temp = findDouble();
		if (this->m_value == temp.m_value) {
			return true;
		}

		return false;
	}

	void printDDNF() {
		std::string result = "";

		size_t index = 0;

		for (int x = 0; x <= 1; ++x) {
			for (int y = 0; y <= 1; ++y) {
				for (int z = 0; z <= 1; ++z) {
					if (m_value[index] == '1') {
						result += "(";
						std::string part = "";

						if (x == 1) { part += " x &&"; } else { part += " -x &&"; }
						if (y == 1) { part += " y &&"; } else { part += " -y &&"; }
						if (z == 1) { part += " z &&"; } else { part += " -z &&"; }

						part = part.substr(0, part.length() - 2);

						result += part;
						result += ") V ";
					}
					index++;
				}
			}
		}
		result = result.substr(0, result.length() - 3);
		std::cout << result;
	}

	void printGegalkin() {
		std::string result = "";

		size_t index = 0;

		for (int x = 0; x <= 1; ++x) {
			for (int y = 0; y <= 1; ++y) {
				for (int z = 0; z <= 1; ++z) {
					if (m_value[index] == '1') {
						result += "(";
						std::string part = "";

						if (x == 0) { part += "(x XOR 1)Ʌ"; } else { part += "xɅ"; }
						if (y == 0) { part += "(y XOR 1)Ʌ"; } else { part += "yɅ"; }
						if (z == 0) { part += "(z XOR 1)Ʌ"; } else { part += "zɅ"; }
						
						result += part;
						result += ")XOR";
						
					}
					index++;
				}
			}
		}
		std::cout << result;
	}

	void printDKNF() {
		std::string result = "";

		size_t index = 0;

		for (int x = 0; x <= 1; ++x) {
			for (int y = 0; y <= 1; ++y) {
				for (int z = 0; z <= 1; ++z) {
					if (m_value[index] == '0') {
						result += "(";
						std::string part = "";

						if (x == 0) { part += " x &&"; } else { part += " -x &&"; }
						if (y == 0) { part += " y &&"; } else { part += " -y &&"; }
						if (z == 0) { part += " z &&"; } else { part += " -z &&"; }

						part = part.substr(0, part.length() - 2);

						result+=part;
						result += ") Ʌ ";
					}
					index++;
				}
			}
		}
		result = result.substr(0, result.length() - 3);
		std::cout << result;
	}

	bool remainsConstant(bool constant) {
		size_t index = 0;

		for (int x = 0; x <= 1; ++x) {
			for (int y = 0; y <= 1; ++y) {
				for (int z = 0; z <= 1; ++z) {
					if (constant) {
						if (x == 1 && y == 1 && z == 1 && m_value[index] == '1') {
							return true;
						}
					}
					else if(!constant) {
						if (x == 0 && y == 0 && z == 0 && m_value[index] == '0') {
							return true;
						}
					}
					index++;
				}
			}
		}

		return false;
	}

	bool isMonotonic() {
		size_t value_index = 0;
		for (int x = 0; x <= 1; ++x) {
			for (int y = 0; y <= 1; ++y) {
				for (int z = 0; z <= 1; ++z) {
					if (x == 1 && y == 1 && z == 1) continue;
					std::string base = std::to_string(x) + std::to_string(y) + std::to_string(z);

					for (size_t i = 0; i < base.size(); ++i) {
						if (base[i] == '0' && m_value[value_index] == '1') {
							std::string base_cpy = base;
							int el = base[i] - '0';
							base_cpy[i] = static_cast<char>(el + 1 + '0');

							auto index = binaryToDecimal(base_cpy);

							if ((static_cast<int>(m_value[index] - '0')) < (static_cast<int>(m_value[binaryToDecimal(base)] - '0')) && m_value[index] == '0')
								return false;
						}
					}
					++value_index;
				}
			}
		}

		return true;
	}

	bool isLinear() {
		size_t index = 0;

		std::vector<std::string> result;

		for (int x = 0; x <= 1; ++x) {
			for (int y = 0; y <= 1; ++y) {
				for (int z = 0; z <= 1; ++z) {
					if (m_value[index] == '1') {
						if (x == 0 && y == 0 && z == 0) result.push_back("1");

						std::string temp;

						if (x == 1) temp += "x";
						if (y == 1) temp += "y";
						if (z == 1) temp += "z";

						if (temp.size() > 1) return false;

						if(!temp.empty()) result.push_back(temp);
					}
					index++;
				}
			}
		}

		for (const auto& el : result) {
			std::cout << el << " + ";
		}
		return true;
	}

	friend std::ostream& operator<<(std::ostream& os, const BooleanFunction& func) {
		os << func.m_value;

		return os;
	}
private:

	inline void reverse() {
		std::reverse(m_value.begin(), m_value.end());
	}

	int binaryToDecimal(std::string binary) {
		int decimal = 0;
		int binaryLength = binary.length();

		for (int i = 0; i < binaryLength; ++i) {
			if (binary[i] == '1') {
				decimal += pow(2, binaryLength - 1 - i);
			}
		}

		return decimal;
	}

	std::string m_value;
};