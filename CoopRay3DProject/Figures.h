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
		Vector3 tiltAngles;
		float radius;
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
		Vector3 tiltAngles;
		Vector3 radius;
	};

	EllipseParams Properties;

	Ellipse(EllipseParams p) : Properties(p) {}

	static void DrawEllipse(Ellipse* ellipse, int segments = 320);
	std::string getClassName() const override { return "Ellipse"; }
};

class Helix : public Figure {

public:
	struct HelixParams : Figure::FigureParams {
		Vector3 center;
		Vector3 tiltAngles;
		float radius;
		float height;
		float circleStep;
	};

	HelixParams Properties;

	Helix(HelixParams p) : Properties(p) {}

	static void DrawHelix(Helix* helix);
	std::string getClassName() const override { return "Helix"; }
};


Color GetRandomColor();

using figure_variant = std::variant<Circle*, Ellipse*, Helix*>;
extern std::vector<figure_variant> vecFigures;