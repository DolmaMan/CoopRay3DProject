#pragma once
#include <unordered_map>
#include<string>
#include<iostream>
#include"config.h"

class Figure
{
private:
	static inline unsigned CountObjects{};

public:
	std::unordered_map<std::string, float> Properties;
	std::string figureName;
	Color color;
	Rectangle figureRect;
	bool isHighlighted;

	Figure(std::string, std::unordered_map<std::string, float> p);
	Figure(std::string, std::unordered_map<std::string, float> p, Color color);
	~Figure();

	bool operator==(Figure* f1);

private:
	void ChangeAllId(std::multimap<std::string, Figure*>::iterator itFrom);
};

Color GetRandomColor();