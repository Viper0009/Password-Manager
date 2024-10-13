#include "Encryptor.h"
Encryptor::Encryptor(const int32_t& key) : _k(key)
{
}
void Encryptor::setKey(const int32_t& key)
{
	_k = key;
}
sf::String Encryptor::encrypt(const sf::String& str) {
	std::wstring st;
	if (!str.isEmpty()) {
		int32_t b;
		st.push_back(str[0] * 2 + _k);
		b = _k;
		for (int i = 0; i < str.getSize(); ++i) {
			int32_t
				ch1 = (str[i] / b + b) + 30,
				ch2 = (str[i] % b + b * 2) + 30;
			st.push_back(ch1);
			st.push_back(ch2);
		}
	}
	return st;
}
sf::String Encryptor::decrypt(const sf::String& str) {
	std::wstring st;
	int32_t b;
	b = _k;
	if (!str.isEmpty()) {
		for (int i = 1; i < str.getSize(); i += 2) {
			int32_t
				ch1 = str[i],
				ch2 = str[i + 1];
			ch1 -= 30;
			ch2 -= 30;
			ch1 = (ch1 - b) * b;
			ch2 = (ch2 - b * 2);
			st.push_back(ch1 + ch2);
		}
	}
	return st;
}