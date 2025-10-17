#include "Figures.h"

//Figure::Figure(std::string fn, std::unordered_map<std::string, float> p)
//{
//	//Properties = p;
// //   figureName = fn;
// //   Properties["id"] = CountObjects++;
// //   color = RED;
// //   mapFigures.insert({ figureName, this });
// //   //mapFigures[figureName].push_back(this);
//}
//
//Figure::Figure(std::string fn, std::unordered_map<std::string, float> p, Color color)
//{
//    //Properties = p;
//    //figureName = fn;
//    //Properties["id"] = CountObjects++;
//    //this->color = color;
//    //mapFigures.insert({ figureName, this });
//    ////mapFigures.push_back(this);
//}
//
//Figure::~Figure()
//{
//    /*CountObjects--;
//    auto it = mapFigures.begin();
//    for (; it != mapFigures.end(); it++) {
//        if ((*it).second->Properties["id"] == this->Properties["id"]) {
//            mapFigures.erase(it);
//            break;
//        }
//    }
//    ChangeAllId(it);*/
//}
//
//bool Figure::operator==( Figure* f1)
//{
//    //return (*this).Properties.at("id") == (*f1).Properties.at("id");
//}

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

Circle::Circle(CircleParams p)
{
    Properties.center = p.center;
    Properties.rotationAxis = p.rotationAxis;
    Properties.color = p.color;
    Properties.radius = p.radius;
    Properties.rotationAngle = p.rotationAngle;
    Properties.figureInMenuRect = p.figureInMenuRect;
    Properties.isHighlightedInMenu = p.isHighlightedInMenu;
}

Circle::~Circle()
{
    
}



void Circle::DrawCircle(Circle* circle, int segments)
{
    //// Нормализуем ось вручную
    //Vector3 axis = (*circle).Properties.rotationAxis;
    //float length = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    //if (length > 0) {
    //    axis.x /= length;
    //    axis.y /= length;
    //    axis.z /= length;
    //}

    //// Находим перпендикулярные векторы
    //Vector3 u, v;

    //// Вектор, не параллельный оси
    //Vector3 temp = { 1, 0, 0 };
    //if (fabs(axis.x) > 0.9f) {
    //    temp = { 0.0f, 1.0f, 0.0f };
    //}

    //// u = axis × temp
    //u.x = axis.y * temp.z - axis.z * temp.y;
    //u.y = axis.z * temp.x - axis.x * temp.z;
    //u.z = axis.x * temp.y - axis.y * temp.x;

    //// Нормализуем u
    //length = sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
    //if (length > 0) {
    //    u.x /= length;
    //    u.y /= length;
    //    u.z /= length;
    //}

    //// v = axis × u
    //v.x = axis.y * u.z - axis.z * u.y;
    //v.y = axis.z * u.x - axis.x * u.z;
    //v.z = axis.x * u.y - axis.y * u.x;

    //// Применяем поворот если нужно
    //if ((*circle).Properties.rotationAngle != 0) {
    //    float cosA = cos((*circle).Properties.rotationAngle);
    //    float sinA = sin((*circle).Properties.rotationAngle);

    //    Vector3 u_new = {
    //        u.x * cosA - v.x * sinA,
    //        u.y * cosA - v.y * sinA,
    //        u.z * cosA - v.z * sinA
    //    };

    //    Vector3 v_new = {
    //        u.x * sinA + v.x * cosA,
    //        u.y * sinA + v.y * cosA,
    //        u.z * sinA + v.z * cosA
    //    };

    //    u = u_new;
    //    v = v_new;
    //}

    //// Рисуем окружность
    //for (int i = 0; i < segments; i++) {
    //    float angle1 = (float)i / segments * 2 * PI;
    //    float angle2 = (float)(i + 1) / segments * 2 * PI;

    //    Vector3 p1 = {
    //        (*circle).Properties.center.x + (*circle).Properties.radius * (cos(angle1) * u.x + sin(angle1) * v.x),
    //        (*circle).Properties.center.y + (*circle).Properties.radius * (cos(angle1) * u.y + sin(angle1) * v.y),
    //        (*circle).Properties.center.z + (*circle).Properties.radius * (cos(angle1) * u.z + sin(angle1) * v.z)
    //    };

    //    Vector3 p2 = {
    //        (*circle).Properties.center.x + (*circle).Properties.radius * (cos(angle2) * u.x + sin(angle2) * v.x),
    //        (*circle).Properties.center.y + (*circle).Properties.radius * (cos(angle2) * u.y + sin(angle2) * v.y),
    //        (*circle).Properties.center.z + (*circle).Properties.radius * (cos(angle2) * u.z + sin(angle2) * v.z)
    //    };
    //    DrawSphere(p1, 5, RED);
    //    DrawLine3D(p1, p2, (*circle).Properties.color);
    //}

    //// Рисуем диаметры
    //for (int i = 0; i < 4; i++) {
    //    float angle = (float)i * PI / 4.0f;

    //    Vector3 p1 = {
    //        (*circle).Properties.center.x + (*circle).Properties.radius * (cos(angle) * u.x + sin(angle) * v.x),
    //        (*circle).Properties.center.y + (*circle).Properties.radius * (cos(angle) * u.y + sin(angle) * v.y),
    //        (*circle).Properties.center.z + (*circle).Properties.radius * (cos(angle) * u.z + sin(angle) * v.z)
    //    };

    //    Vector3 p2 = {
    //        (*circle).Properties.center.x - (*circle).Properties.radius * (cos(angle) * u.x + sin(angle) * v.x),
    //        (*circle).Properties.center.y - (*circle).Properties.radius * (cos(angle) * u.y + sin(angle) * v.y),
    //        (*circle).Properties.center.z - (*circle).Properties.radius * (cos(angle) * u.z + sin(angle) * v.z)
    //    };

    //    DrawLine3D(p1, p2, (*circle).Properties.color);
    //}
    // Создаем точки на окружности

    float length = sqrtf((*circle).Properties.rotationAxis.x * (*circle).Properties.rotationAxis.x +
        (*circle).Properties.rotationAxis.y * (*circle).Properties.rotationAxis.y +
        (*circle).Properties.rotationAxis.z * (*circle).Properties.rotationAxis.z);
    if (length == 0.0f) {
        (*circle).Properties.rotationAxis = { 0.0f, 1.0f, 0.0f }; // По умолчанию вертикальная плоскость
    }
    else {
        (*circle).Properties.rotationAxis.x /= length;
        (*circle).Properties.rotationAxis.y /= length;
        (*circle).Properties.rotationAxis.z /= length;
    }

    // Находим два перпендикулярных вектора в плоскости окружности
    Vector3 u, v;

    // Выбираем вектор, не параллельный нормали
    if (fabsf((*circle).Properties.rotationAxis.x) < fabsf((*circle).Properties.rotationAxis.y) &&
        fabsf((*circle).Properties.rotationAxis.x) < fabsf((*circle).Properties.rotationAxis.z)) {
        u = { 1.0f, 0.0f, 0.0f };
    }
    else if (fabsf((*circle).Properties.rotationAxis.y) < fabsf((*circle).Properties.rotationAxis.z)) {
        u = { 0.0f, 1.0f, 0.0f };
    }
    else {
        u = { 0.0f, 0.0f, 1.0f };
    }

    // Вектор u перпендикулярен нормали
    u = {
        u.x - (*circle).Properties.rotationAxis.x * (u.x * (*circle).Properties.rotationAxis.x +
        u.y * (*circle).Properties.rotationAxis.y + u.z * (*circle).Properties.rotationAxis.z),
        u.y - (*circle).Properties.rotationAxis.y * (u.x * (*circle).Properties.rotationAxis.x +
            u.y * (*circle).Properties.rotationAxis.y + u.z * (*circle).Properties.rotationAxis.z),
        u.z - (*circle).Properties.rotationAxis.z * (u.x * (*circle).Properties.rotationAxis.x +
            u.y * (*circle).Properties.rotationAxis.y + u.z * (*circle).Properties.rotationAxis.z)
    };

    // Нормализуем u
    float uLength = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
    if (uLength > 0.0f) {
        u.x /= uLength;
        u.y /= uLength;
        u.z /= uLength;
    }

    // Вектор v = normal × u (векторное произведение)
    v = {
        (*circle).Properties.rotationAxis.y * u.z - (*circle).Properties.rotationAxis.z * u.y,
        (*circle).Properties.rotationAxis.z * u.x - (*circle).Properties.rotationAxis.x * u.z,
        (*circle).Properties.rotationAxis.x * u.y - (*circle).Properties.rotationAxis.y * u.x
    };

    // Создаем и рисуем окружность
    Vector3 prevPoint;
    bool firstPoint = true;

    for (int i = 0; i <= segments; i++) {
        float angle = (float)i / (float)segments * 2.0f * PI;
        float cosAngle = cosf(angle);
        float sinAngle = sinf(angle);

        // Точка в плоскости окружности
        Vector3 pointInPlane = {
            cosAngle * (*circle).Properties.radius,
            sinAngle * (*circle).Properties.radius,
            0.0f
        };

        // Преобразуем в мировые координаты
        Vector3 worldPoint = {
            (*circle).Properties.center.x + pointInPlane.x * u.x + pointInPlane.y * v.x,
            (*circle).Properties.center.y + pointInPlane.x * u.y + pointInPlane.y * v.y,
            (*circle).Properties.center.z + pointInPlane.x * u.z + pointInPlane.y * v.z
        };

        // Рисуем линию от предыдущей точки к текущей
        if (!firstPoint) {
            DrawLine3D(prevPoint, worldPoint, (*circle).Properties.color);
        }

        prevPoint = worldPoint;
        firstPoint = false;
    }
}