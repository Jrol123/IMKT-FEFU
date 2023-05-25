#include "graphics.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <vector>
#include <fstream>
#pragma comment(lib,"graphics.lib")
#define vec std::vector

const float winX = 1920;
const float winY = 1200;

const float scale = (125 - 30) / 2;

struct Point
{
    struct Vector
    {
        float x_coord, y_coord;

        Vector(const Point* pt1, const Point& pt2)
        {
            this->x_coord = pt1->x_coord - pt2.x_coord;
            this->y_coord = pt1->y_coord - pt2.y_coord;
        }

        float ScalarMul(const Vector& other)
        {
            float x = this->x_coord * other.x_coord;
            float y = this->y_coord * other.y_coord;
            return (x + y);
        }

        float len()
        {
            return std::sqrt(x_coord * x_coord + y_coord * y_coord);
        }
    };


    float x_coord, y_coord;

    Point(const float& x_coord, const float& y_coord)
    {
        this->x_coord = x_coord;
        this->y_coord = y_coord;
    }

    

    float angle_points(Point& pt1, Point& pt2)
    {
        Vector vc1(this, pt1);
        Vector vc2(this, pt2);
        float len1 = vc1.len();
        float len2 = vc2.len();
        float scalar = vc1.ScalarMul(vc2);
        float arc = std::acos(scalar / (len1 * len2));

        return arc;
    }

};

int coord(float x, bool state)
{
    if (state == false)
    {
        return int(winY / 2 - scale * x);
    }
    return int(winX / 2 + 2 * scale * x);
}

void draw_point()
{

}

int main()
{
    std::ifstream inf("input.txt");

    vec<Point> vector_points;

    short int count_points;
    inf >> count_points;

    for (int index = 0; index < count_points; ++index)
    {
        float x, y;
        inf >> x >> x;
        
        vector_points.push_back(Point(x, y));
    }
    inf.close();

    float angle1 = vector_points[0].angle_points(vector_points[1], vector_points[2]);
    float angle2 = vector_points[1].angle_points(vector_points[2], vector_points[0]);
    float angle3 = vector_points[2].angle_points(vector_points[0], vector_points[1]);

    std::ofstream outf("output.txt");

    if (angle1 == 120 || angle2 == 120 || angle3 == 120)
    {
        outf << "WIN";
    }
    else
    {
        outf << angle1 << std::endl << angle2 << std::endl << angle3;
    }

    outf.close();

    return 0;
}