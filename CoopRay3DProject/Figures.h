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
	struct FigureParams
	{
		Color color;
		Rectangle figureInMenuRect;
		bool isHighlightedInMenu;
	};

	FigureParams baseParams;

	Figure(){}

	virtual std::string getClassName() const = 0;
	virtual Vector3 getPoint(float t) const = 0;
	virtual Vector3 getFirstDerivative(float t) const = 0;
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

	Circle(CircleParams p) : Properties(p) {}

	static void DrawCircle(Circle* circle, int segments = 320);
	std::string getClassName() const override { return "Circle"; }

	Vector3 getPoint(float t) const;
	Vector3 getFirstDerivative(float t) const;
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

	Vector3 getPoint(float t) const;
	Vector3 getFirstDerivative(float t) const;
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

	Vector3 getPoint(float t) const;
	Vector3 getFirstDerivative(float t) const;
};


Color GetRandomColor();

using figure_variant = std::variant<Circle*, Ellipse*, Helix*>;
extern std::vector<figure_variant> vecFigures;