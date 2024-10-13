#pragma once
#include "SFML/Graphics.hpp"
extern sf::Vector2u ScreenSize;
extern const sf::Vector2u BaseScreenSize;
float operator""vh(unsigned long long a);
float operator""vw(unsigned long long a);
float operator""vh(long double a);
float operator""vw(long double a);
float operator""p(unsigned long long a);
float operator""px(size_t a);
float operator""px(long double a);
