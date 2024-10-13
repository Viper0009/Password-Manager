#pragma once
// Graphics
#include "SFML/Graphics.hpp"
// Input / Output
#include "iostream"
#include "fstream"
// data structures
#include "string"
#include "vector"
#include "list"
#include "map"
#include "set"
#include "memory"
#include "Blank.h"
// functions
#include "algorithm"
#include "numeric"
#include "random"
// Time
#include "chrono"
// Librares
#include "UiFramework.h"
#include "Utility.h"
#include "Logging.h"
#include "FileReader.h"
// Source
#include "Sources.h"
// extern vars
extern Vector2u ScreenSize;
// typedefs
typedef Button<InputTextBox> BiTextBox;
typedef Button<TextBox> TButton;
// usings
using namespace sf;
// using std
using std::cout;
using std::cin;
using std::cerr;
using std::wcout;
using std::wcin;
using std::wcerr;
using std::endl;
using std::string;
using std::vector;
using std::wstring;
using std::list;
using std::map;
using std::set;
using std::ofstream;
using std::fstream;
using std::istream;
using std::wofstream;
using std::ifstream;
using std::wifstream;

using std::swap;
using std::sort;
using std::count;
using std::count_if;
using std::find;
using std::find_if;
using std::move;
using std::begin;
using std::end;
using std::accumulate;
using std::copy;
using std::copy_if;

using std::make_unique;
using std::make_shared;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
