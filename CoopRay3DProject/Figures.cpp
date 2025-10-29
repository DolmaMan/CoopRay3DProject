#include "Figures.h"

Color GetRandomColor()
{
    static std::vector<Color> vecColors
    {
        DARKGRAY,
        ORANGE,
        PINK,
        MAROON,
        GREEN,
        LIME,
        DARKGREEN,
        SKYBLUE,
        BLUE,
        DARKBLUE,
        PURPLE,
        VIOLET,
        DARKPURPLE,
        BEIGE,
        BROWN,
        DARKBROWN,
        BLACK
    };
    return vecColors[GetRandomValue(0, vecColors.size() - 1)];
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

void Circle::DrawCircle(Circle* circle, int segments)
{
    Vector3 tiltAngles = (*circle).Properties.tiltAngles;

    float tiltXRad = tiltAngles.x * DEG2RAD;
    float tiltYRad = tiltAngles.y * DEG2RAD;
    float tiltZRad = tiltAngles.z * DEG2RAD;

    float cosX = cosf(tiltXRad);
    float sinX = sinf(tiltXRad);
    float cosY = cosf(tiltYRad);
    float sinY = sinf(tiltYRad);
    float cosZ = cosf(tiltZRad);
    float sinZ = sinf(tiltZRad);

    Vector3 prevPoint;
    bool firstPoint = true;

    for (int i = 0; i <= segments; i++) {
        float angle = (float)i / (float)segments * 2.0f * PI;
        float cosAngle = cosf(angle);
        float sinAngle = sinf(angle);

        // точки без наклона
        float x = cosAngle * (*circle).Properties.radius;
        float y = 0.0f;
        float z = sinAngle * (*circle).Properties.radius;

        // наклон по Z
        float x1 = x * cosZ - y * sinZ;
        float y1 = x * sinZ + y * cosZ;
        float z1 = z;

        // наклон по Y
        float x2 = x1 * cosY + z1 * sinY;
        float y2 = y1;
        float z2 = -x1 * sinY + z1 * cosY;

        // наклон по X
        float x3 = x2;
        float y3 = y2 * cosX - z2 * sinX;
        float z3 = y2 * sinX + z2 * cosX;

        Vector3 currentPoint = {
            (*circle).Properties.center.x + x3,
            (*circle).Properties.center.y + y3,
            (*circle).Properties.center.z + z3
        };

        if (!firstPoint) {
            if(!(*circle).Properties.isHighlightedInMenu)
                DrawLine3D(prevPoint, currentPoint, (*circle).Properties.color);
            else
                DrawLine3D(prevPoint, currentPoint, RED);
        }

        prevPoint = currentPoint;
        firstPoint = false;
    }
}

void Ellipse::DrawEllipse(Ellipse* ellipse, int segments)
{
    float rx = (*ellipse).Properties.tiltAngles.x * DEG2RAD;
    float ry = (*ellipse).Properties.tiltAngles.y * DEG2RAD;
    float rz = (*ellipse).Properties.tiltAngles.z * DEG2RAD;

    float cx = cosf(rx), sx = sinf(rx);
    float cy = cosf(ry), sy = sinf(ry);
    float cz = cosf(rz), sz = sinf(rz);

    // лямбда для поворота
    auto rotatePoint = [&](float x, float y, float z) -> Vector3 {
        // поворот вокруг Z
        float x1 = x * cz - y * sz;
        float y1 = x * sz + y * cz;
        float z1 = z;

        // поворот вокруг Y
        float x2 = x1 * cy + z1 * sy;
        float y2 = y1;
        float z2 = -x1 * sy + z1 * cy;

        // поворот вокруг X
        float x3 = x2;
        float y3 = y2 * cx - z2 * sx;
        float z3 = y2 * sx + z2 * cx;

        return { 
            (*ellipse).Properties.center.x + x3,
            (*ellipse).Properties.center.y + y3,
            (*ellipse).Properties.center.z + z3 
        };
    };

    // плоскость YZ
    Vector3 prevPointX;
    bool firstPointX = true;
    for (int i = 0; i <= segments; i++) {
        float angle = (float)i / (float)segments * 2.0f * PI;
        Vector3 point = rotatePoint(0, (*ellipse).Properties.radius.y * cosf(angle), (*ellipse).Properties.radius.z * sinf(angle));

        if (!firstPointX) {
            if(!(*ellipse).Properties.isHighlightedInMenu)
                DrawLine3D(prevPointX, point, (*ellipse).Properties.color);
            else
                DrawLine3D(prevPointX, point, RED);
        }
        prevPointX = point;
        firstPointX = false;
    }

    // плоскость XZ
    Vector3 prevPointY;
    bool firstPointY = true;
    for (int i = 0; i <= segments; i++) {
        float angle = (float)i / (float)segments * 2.0f * PI;
        Vector3 point = rotatePoint((*ellipse).Properties.radius.x * cosf(angle), 0, (*ellipse).Properties.radius.z * sinf(angle));

        if (!firstPointY) {
            if (!(*ellipse).Properties.isHighlightedInMenu)
                DrawLine3D(prevPointY, point, (*ellipse).Properties.color);
            else
                DrawLine3D(prevPointY, point, RED);
        }
        prevPointY = point;
        firstPointY = false;
    }

    // плоскость XY
    Vector3 prevPointZ;
    bool firstPointZ = true;
    for (int i = 0; i <= segments; i++) {
        float angle = (float)i / (float)segments * 2.0f * PI;
        Vector3 point = rotatePoint((*ellipse).Properties.radius.x * cosf(angle), (*ellipse).Properties.radius.y * sinf(angle), 0);

        if (!firstPointZ) {
            if (!(*ellipse).Properties.isHighlightedInMenu)
                DrawLine3D(prevPointZ, point, (*ellipse).Properties.color);
            else
                DrawLine3D(prevPointZ, point, RED);
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

    // синусы и косинусы для каждого угла
    float cx = cosf(rx), sx = sinf(rx);
    float cy = cosf(ry), sy = sinf(ry);
    float cz = cosf(rz), sz = sinf(rz);

    // общее количество витков
    float totalCircles = (*helix).Properties.height / (*helix).Properties.circleStep;
    float totalAngle = totalCircles * 2.0f * PI;

    int segments = (int)(totalAngle * 10.0f); // 10 сегментов на радиан
    if (segments < 36) segments = 36;

    Vector3 prevPoint;
    bool firstPoint = true;

    for (int i = 0; i <= segments; i++) {
        // текущий угол и высота
        float currentAngle = (float)i / (float)segments * totalAngle;
        float currentHeight = ((float)i / (float)segments - 0.5f) * (*helix).Properties.height;

        float localX = (*helix).Properties.radius * cosf(currentAngle);
        float localY = (*helix).Properties.radius * sinf(currentAngle);
        float localZ = currentHeight;

        // поворот вокруг Z
        float x1 = localX * cz - localY * sz;
        float y1 = localX * sz + localY * cz;
        float z1 = localZ;

        // поворот вокруг Y
        float x2 = x1 * cy + z1 * sy;
        float y2 = y1;
        float z2 = -x1 * sy + z1 * cy;

        // поворот вокруг X
        float x3 = x2;
        float y3 = y2 * cx - z2 * sx;
        float z3 = y2 * sx + z2 * cx;

        Vector3 point = {
            (*helix).Properties.center.x + x3,
            (*helix).Properties.center.y + y3,
            (*helix).Properties.center.z + z3
        };

        if (!firstPoint) {
            if(!(*helix).Properties.isHighlightedInMenu)
                DrawLine3D(prevPoint, point, (*helix).Properties.color);
            else
                DrawLine3D(prevPoint, point, RED);
        }

        prevPoint = point;
        firstPoint = false;
    }
}
