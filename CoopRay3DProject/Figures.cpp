#include "Figures.h"

Figure::Figure(std::string figureName, std::unordered_map<std::string, float> p)
{
	Properties = p;
    color = RED;
    mapFigures[figureName].push_back((Figure)*this);
}

Figure::Figure(std::string figureName, std::unordered_map<std::string, float> p, Color color)
{
    Properties = p;
    this->color = color;
    mapFigures[figureName].push_back((Figure)*this);
}

Color GetRandomColor()
{
    int R = GetRandomValue(0, 255);
    int G = GetRandomValue(0, 255);
    int B = GetRandomValue(0, 255);
    double delta, min;
    double h = 0, s, v;
    min = std::min(std::min(R, G), B);
    v = std::max(std::max(R, G), B);
    delta = v - min;
    if (v == 0.0) s = 0; else s = delta / v;
    if (s == 0) h = 0.0; else {
        if (R == v) h = (G - B) / delta;
        else if (G == v) h = 2 + (B - R) / delta;
        else if (B == v) h = 4 + (R - G) / delta;
        h *= 60;
        if (h < 0.0) h = h + 360;
    }
    return ColorFromHSV(h, s, (v / 255));
}
