#include "Figures.h"

Figure::Figure(std::string fn, std::unordered_map<std::string, float> p)
{
	Properties = p;
    figureName = fn;
    Properties["id"] = CountObjects++;
    color = RED;
    mapFigures.insert({ figureName, this });
    //mapFigures[figureName].push_back(this);
}

Figure::Figure(std::string fn, std::unordered_map<std::string, float> p, Color color)
{
    Properties = p;
    figureName = fn;
    Properties["id"] = CountObjects++;
    this->color = color;
    mapFigures.insert({ figureName, this });
    //mapFigures.push_back(this);
}

Figure::~Figure()
{
    CountObjects--;
    auto it = mapFigures.begin();
    for (; it != mapFigures.end(); it++) {
        if ((*it).second->Properties["id"] == this->Properties["id"]) {
            mapFigures.erase(it);
            break;
        }
    }
    ChangeAllId(it);
}

bool Figure::operator==( Figure* f1)
{
    return (*this).Properties.at("id") == (*f1).Properties.at("id");
}

void Figure::ChangeAllId(std::multimap<std::string, Figure*>::iterator itFrom)
{
    for (auto it = itFrom; it != mapFigures.end(); it++) {
        (*(*it).second).Properties["id"]--;
    }
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
