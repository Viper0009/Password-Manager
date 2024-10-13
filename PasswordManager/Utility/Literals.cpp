#include "Literals.h"
float operator""vh(unsigned long long a) {
	return ScreenSize.y * (a / 100.f);
}
float operator""vw(unsigned long long a) {
	return ScreenSize.x * (a / 100.f);
}
float operator""p(unsigned long long a) {
	return a / 100.f;
}
float operator""px(size_t a)
{
    return a * ((float)ScreenSize.x / BaseScreenSize.x);
}
float operator""px(long double a)
{
	return a * ((float)ScreenSize.x / BaseScreenSize.x);
}
float operator""vh(long double a) {
	return ScreenSize.y * (a / 100.f);
}
float operator""vw(long double a) {
	return ScreenSize.x * (a / 100.f);
}
