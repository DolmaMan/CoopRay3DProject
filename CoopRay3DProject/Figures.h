#pragma once
#include <unordered_map>
#include<string>
#include<iostream>

#include <cmath>
#include"config.h"

class Figure
{
private:
	static inline unsigned CountObjects{};

public:
	/*std::unordered_map<std::string, float> Properties;
	std::string figureName;
	Color color;
	Rectangle figureRect;
	bool isHighlighted;*/
	struct FigureParams
	{
		Color color;
		Rectangle figureInMenuRect;
		bool isHighlightedInMenu;
	};

	FigureParams baseParams;

	Figure(){}
	/*Figure(Color c, Rectangle r, bool isH) : baseParams{c, r, isH}{}

	Figure(std::string, std::unordered_map<std::string, float> p);
	Figure(std::string, std::unordered_map<std::string, float> p, Color color);
	~Figure();

	bool operator==(Figure* f1);*/

	virtual std::string getClassName() const = 0;
};

class Circle : public Figure 
{
public:
	struct CircleParams : Figure::FigureParams {
		Vector3 center;
		Vector3 rotationAxis;
		float radius;
		float rotationAngle;
	};

	CircleParams Properties;

	Circle(CircleParams p);
	~Circle();

	static void DrawCircle(Circle* circle, int segments = 320);
	std::string getClassName() const override { return "Circle"; }
};

class Ellipse : public Figure {

public:
	struct EllipseParams : Figure::FigureParams {
		Vector3 center;
		Vector3 rotationAxis;
		float radius;
		float rotationAngle;
	};

	EllipseParams Properties;

	Ellipse(EllipseParams p) : Properties(p) {}

	std::string getClassName() const override { return "Ellipse"; }
};
Color GetRandomColor();

using figure_variant = std::variant<Circle*, Ellipse*>;
extern std::vector<figure_variant> vecFigures;