#pragma once
#include <unordered_map>
#include<string>
#include<iostream>
#include"config.h"

class Figure
{
public:
	std::unordered_map<std::string, float> Properties;
	Color color;

	Figure(std::string, std::unordered_map<std::string, float> p);
	Figure(std::string, std::unordered_map<std::string, float> p, Color color);
};

Color GetRandomColor();