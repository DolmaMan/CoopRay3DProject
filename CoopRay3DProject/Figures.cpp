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
    Properties.tiltAngles = p.tiltAngles;
    Properties.color = p.color;
    Properties.radius = p.radius;
    Properties.figureInMenuRect = p.figureInMenuRect;
    Properties.isHighlightedInMenu = p.isHighlightedInMenu;
}

Circle::~Circle()
{
    
}



void Circle::DrawCircle(Circle* circle, int segments)
{
    //// Создаем точки на окружности
    //Vector3 rotationAxis = (*circle).Properties.rotationAxis;

    //float length = sqrtf(
    //    rotationAxis.x * rotationAxis.x +
    //    rotationAxis.y * rotationAxis.y +
    //    rotationAxis.z * rotationAxis.z
    //);
    //if (length == 0.0f) {
    //    rotationAxis = { 0.0f, 1.0f, 0.0f }; // По умолчанию вертикальная плоскость
    //}
    //else {
    //    rotationAxis.x /= length;
    //    rotationAxis.y /= length;
    //    rotationAxis.z /= length;
    //}

    //// Находим два перпендикулярных вектора в плоскости окружности
    //Vector3 u, v;

    //// Выбираем вектор, не параллельный нормали
    //if (fabsf(rotationAxis.x) < fabsf(rotationAxis.y) &&
    //    fabsf(rotationAxis.x) < fabsf(rotationAxis.z)) {
    //    u = { 1.0f, 0.0f, 0.0f };
    //}
    //else if (fabsf(rotationAxis.y) < fabsf(rotationAxis.z)) {
    //    u = { 0.0f, 1.0f, 0.0f };
    //}
    //else {
    //    u = { 0.0f, 0.0f, 1.0f };
    //}

    //// Вектор u перпендикулярен нормали
    //u = {
    //    u.x - rotationAxis.x * (u.x * rotationAxis.x + u.y * rotationAxis.y + u.z * rotationAxis.z),
    //    u.y - rotationAxis.y * (u.x * rotationAxis.x + u.y * rotationAxis.y + u.z * rotationAxis.z),
    //    u.z - rotationAxis.z * (u.x * rotationAxis.x + u.y * rotationAxis.y + u.z * rotationAxis.z)
    //};

    //// Нормализуем u
    //float uLength = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
    //if (uLength > 0.0f) {
    //    u.x /= uLength;
    //    u.y /= uLength;
    //    u.z /= uLength;
    //}

    //// Вектор v = normal × u (векторное произведение)
    //v = {
    //    rotationAxis.y * u.z - rotationAxis.z * u.y,
    //    rotationAxis.z * u.x - rotationAxis.x * u.z,
    //    rotationAxis.x * u.y - rotationAxis.y * u.x
    //};

    //// Создаем и рисуем окружность
    //Vector3 prevPoint;
    //bool firstPoint = true;

    //for (int i = 0; i <= segments; i++) {
    //    float angle = (float)i / (float)segments * 2.0f * PI;
    //    float cosAngle = cosf(angle);
    //    float sinAngle = sinf(angle);

    //    // Точка в плоскости окружности
    //    Vector3 pointInPlane = {
    //        cosAngle * (*circle).Properties.radius,
    //        sinAngle * (*circle).Properties.radius,
    //        0.0f
    //    };

    //    // Преобразуем в мировые координаты
    //    Vector3 worldPoint = {
    //        (*circle).Properties.center.x + pointInPlane.x * u.x + pointInPlane.y * v.x,
    //        (*circle).Properties.center.y + pointInPlane.x * u.y + pointInPlane.y * v.y,
    //        (*circle).Properties.center.z + pointInPlane.x * u.z + pointInPlane.y * v.z
    //    };

    //    // Рисуем линию от предыдущей точки к текущей
    //    if (!firstPoint) {
    //        DrawLine3D(prevPoint, worldPoint, (*circle).Properties.color);
    //    }

    //    prevPoint = worldPoint;
    //    firstPoint = false;
    //}
    // Конвертируем градусы в радианы
    Vector3 tiltAngles = (*circle).Properties.tiltAngles;

    float tiltXRad = tiltAngles.x * DEG2RAD;
    float tiltYRad = tiltAngles.y * DEG2RAD;
    float tiltZRad = tiltAngles.z * DEG2RAD;

    // Предварительно вычисляем синусы и косинусы для каждого наклона
    float cosX = cosf(tiltXRad);
    float sinX = sinf(tiltXRad);
    float cosY = cosf(tiltYRad);
    float sinY = sinf(tiltYRad);
    float cosZ = cosf(tiltZRad);
    float sinZ = sinf(tiltZRad);

    // Создаем точки окружности с учетом наклона
    Vector3 prevPoint;
    bool firstPoint = true;

    for (int i = 0; i <= segments; i++) {
        float angle = (float)i / (float)segments * 2.0f * PI;
        float cosAngle = cosf(angle);
        float sinAngle = sinf(angle);

        // Базовая точка в плоскости XZ (без наклона)
        float x = cosAngle * (*circle).Properties.radius;
        float y = 0.0f;
        float z = sinAngle * (*circle).Properties.radius;

        // Применяем наклон по Z (вращение вокруг Z)
        float x1 = x * cosZ - y * sinZ;
        float y1 = x * sinZ + y * cosZ;
        float z1 = z;

        // Применяем наклон по Y (вращение вокруг Y)
        float x2 = x1 * cosY + z1 * sinY;
        float y2 = y1;
        float z2 = -x1 * sinY + z1 * cosY;

        // Применяем наклон по X (вращение вокруг X)
        float x3 = x2;
        float y3 = y2 * cosX - z2 * sinX;
        float z3 = y2 * sinX + z2 * cosX;

        // Смещаем к центру
        Vector3 currentPoint = {
            (*circle).Properties.center.x + x3,
            (*circle).Properties.center.y + y3,
            (*circle).Properties.center.z + z3
        };

        // Рисуем линию от предыдущей точки к текущей
        if (!firstPoint) {
            DrawLine3D(prevPoint, currentPoint, (*circle).Properties.color);
        }

        prevPoint = currentPoint;
        firstPoint = false;
    }
}

void Ellipse::DrawEllipse(Ellipse* ellipse, int segments)
{
    //for (int i = 0; i <= segments; i++) {
    //    float theta = (float)i / (float)segments * PI; // от 0 до PI

    //    Vector3 prevPoint;
    //    bool firstPoint = true;

    //    for (int j = 0; j <= segments; j++) {
    //        float phi = (float)j / (float)segments * 2.0f * PI; // от 0 до 2*PI

    //        // Параметрическое уравнение эллипсоида
    //        Vector3 point = {
    //            (*ellipse).Properties.center.x + (*ellipse).Properties.radius.x * sinf(theta) * cosf(phi),
    //            (*ellipse).Properties.center.y + (*ellipse).Properties.radius.y * sinf(theta) * sinf(phi),
    //            (*ellipse).Properties.center.z + (*ellipse).Properties.radius.z * cosf(theta)
    //        };

    //        if (!firstPoint) {
    //            DrawLine3D(prevPoint, point, (*ellipse).Properties.color);
    //        }

    //        prevPoint = point;
    //        firstPoint = false;
    //    }
    //}

    //// Рисуем вертикальные меридианы
    //for (int j = 0; j <= segments; j++) {
    //    float phi = (float)j / (float)segments * 2.0f * PI;

    //    Vector3 prevPoint;
    //    bool firstPoint = true;

    //    for (int i = 0; i <= segments; i++) {
    //        float theta = (float)i / (float)segments * PI;

    //        Vector3 point = {
    //            (*ellipse).Properties.center.x + (*ellipse).Properties.radius.x * sinf(theta) * cosf(phi),
    //            (*ellipse).Properties.center.y + (*ellipse).Properties.radius.y * sinf(theta) * sinf(phi),
    //            (*ellipse).Properties.center.z + (*ellipse).Properties.radius.z * cosf(theta)
    //        };

    //        if (!firstPoint) {
    //            DrawLine3D(prevPoint, point, (*ellipse).Properties.color);
    //        }

    //        prevPoint = point;
    //        firstPoint = false;
    //    }
    //}
    float rx = (*ellipse).Properties.tiltAngles.x * DEG2RAD;
    float ry = (*ellipse).Properties.tiltAngles.y * DEG2RAD;
    float rz = (*ellipse).Properties.tiltAngles.z * DEG2RAD;

    // Вычисляем синусы и косинусы для каждого угла
    float cx = cosf(rx), sx = sinf(rx);
    float cy = cosf(ry), sy = sinf(ry);
    float cz = cosf(rz), sz = sinf(rz);

    // Функция для применения поворота к точке
    auto rotatePoint = [&](float x, float y, float z) -> Vector3 {
        // Поворот вокруг Z
        float x1 = x * cz - y * sz;
        float y1 = x * sz + y * cz;
        float z1 = z;

        // Поворот вокруг Y
        float x2 = x1 * cy + z1 * sy;
        float y2 = y1;
        float z2 = -x1 * sy + z1 * cy;

        // Поворот вокруг X
        float x3 = x2;
        float y3 = y2 * cx - z2 * sx;
        float z3 = y2 * sx + z2 * cx;

        return { 
            (*ellipse).Properties.center.x + x3,
            (*ellipse).Properties.center.y + y3,
            (*ellipse).Properties.center.z + z3 
        };
    };

    // Ось X (эллипс в плоскости YZ)
    Vector3 prevPointX;
    bool firstPointX = true;
    for (int i = 0; i <= segments; i++) {
        float angle = (float)i / (float)segments * 2.0f * PI;
        Vector3 point = rotatePoint(0, (*ellipse).Properties.radius.y * cosf(angle), (*ellipse).Properties.radius.z * sinf(angle));

        if (!firstPointX) {
            DrawLine3D(prevPointX, point, (*ellipse).Properties.color);
        }
        prevPointX = point;
        firstPointX = false;
    }

    // Ось Y (эллипс в плоскости XZ)
    Vector3 prevPointY;
    bool firstPointY = true;
    for (int i = 0; i <= segments; i++) {
        float angle = (float)i / (float)segments * 2.0f * PI;
        Vector3 point = rotatePoint((*ellipse).Properties.radius.x * cosf(angle), 0, (*ellipse).Properties.radius.z * sinf(angle));

        if (!firstPointY) {
            DrawLine3D(prevPointY, point, (*ellipse).Properties.color);
        }
        prevPointY = point;
        firstPointY = false;
    }

    // Ось Z (эллипс в плоскости XY)
    Vector3 prevPointZ;
    bool firstPointZ = true;
    for (int i = 0; i <= segments; i++) {
        float angle = (float)i / (float)segments * 2.0f * PI;
        Vector3 point = rotatePoint((*ellipse).Properties.radius.x * cosf(angle), (*ellipse).Properties.radius.y * sinf(angle), 0);

        if (!firstPointZ) {
            DrawLine3D(prevPointZ, point, (*ellipse).Properties.color);
        }
        prevPointZ = point;
        firstPointZ = false;
    }
}

void Helix::DrawHelix(Helix* helix)
{
    float rx = (*helix).Properties.tiltAngles.x * DEG2RAD;
    float ry = (*helix).Properties.tiltAngles.y * DEG2RAD;
    float rz = (*helix).Properties.tiltAngles.z * DEG2RAD;

    // Вычисляем синусы и косинусы для каждого угла
    float cx = cosf(rx), sx = sinf(rx);
    float cy = cosf(ry), sy = sinf(ry);
    float cz = cosf(rz), sz = sinf(rz);

    // Рассчитываем общее количество витков на основе высоты и шага
    float totalCircles = (*helix).Properties.height / (*helix).Properties.circleStep;
    float totalAngle = totalCircles * 2.0f * PI;

    // Рассчитываем количество сегментов
    int segments = (int)(totalAngle * 10.0f); // 10 сегментов на радиан
    if (segments < 36) segments = 36;

    Vector3 prevPoint;
    bool firstPoint = true;

    for (int i = 0; i <= segments; i++) {
        // Вычисляем текущий угол и высоту
        float currentAngle = (float)i / (float)segments * totalAngle;
        float currentHeight = ((float)i / (float)segments - 0.5f) * (*helix).Properties.height;

        // Вычисляем координаты точки на спирали в локальной системе
        float localX = (*helix).Properties.radius * cosf(currentAngle);
        float localY = (*helix).Properties.radius * sinf(currentAngle);
        float localZ = currentHeight;

        // Применяем наклон (поворот точки)
        // Поворот вокруг Z
        float x1 = localX * cz - localY * sz;
        float y1 = localX * sz + localY * cz;
        float z1 = localZ;

        // Поворот вокруг Y
        float x2 = x1 * cy + z1 * sy;
        float y2 = y1;
        float z2 = -x1 * sy + z1 * cy;

        // Поворот вокруг X
        float x3 = x2;
        float y3 = y2 * cx - z2 * sx;
        float z3 = y2 * sx + z2 * cx;

        // Смещаем точку в центр
        Vector3 point = {
            (*helix).Properties.center.x + x3,
            (*helix).Properties.center.y + y3,
            (*helix).Properties.center.z + z3
        };

        if (!firstPoint) {
            DrawLine3D(prevPoint, point, (*helix).Properties.color);
        }

        prevPoint = point;
        firstPoint = false;
    }
}
