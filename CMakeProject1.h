
#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <omp.h>
#include <stdexcept>
#define MyPI 3.1415926535


double Random(double a, double b);

// the designations of the type of figures
enum CurveType
{
    ELLIPSE,
    CIRCLE,
    HELIX
};

// 3D-Point
struct Point3D
{
    double x;
    double y;
    double z;

    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
    Point3D() : x(0), y(0), z(0) {}
};


// Base class for 3D curves
class Curve3D
{
public:
    virtual Point3D GetPoint(const double t) const = 0;
    virtual Point3D GetDerivative(const double t) const = 0;
    virtual CurveType GetType() const = 0;
};


// A class for an ellipse in 3D
class Ellipse3D : public Curve3D
{
protected:
    double R_xAxis;
    double R_yAxis;
    Point3D center;

public:
    Ellipse3D(double xAxis, double yAxis, Point3D Center)
        : R_xAxis(xAxis), R_yAxis(yAxis), center(Center) 
    {
        if (xAxis <= 0 || yAxis <= 0)
        {
            throw std::invalid_argument("Invalid ellipse parameters: negative or zero axis length.");
        }
    }

    Point3D GetPoint(double t) const override;
    Point3D GetDerivative(double t) const override;
    CurveType GetType() const override;
};


// a circle is a special case of an ellipse, so it is inherited from it
class Circle3D : public Ellipse3D
{
public:
    Circle3D(double Radius, Point3D Center)
        : Ellipse3D(Radius, Radius, Center) 
    {

    }

    double Radius();

    CurveType GetType() const override;
};



// Класс для 3D-спирали
class Helix3D : public Curve3D
{
private:
    double R;
    double step;
    Point3D center;

public:
    Helix3D(double Radius, double Step, Point3D Center)
        : R(Radius), step(Step), center(Center)
    {
        if (Radius <= 0)
        {
            throw std::invalid_argument("Invalid helix parameters: negative or zero values.");
        }
    }

    Point3D GetPoint(const double t) const override;
    Point3D GetDerivative(const double t) const override;
    CurveType GetType() const override;
};


void Fill_Random_Curves(std::vector<Curve3D*>& A, const int n);
void Get_Curves_Info(std::vector<Curve3D*>& A, const double t);
std::vector<Circle3D*> Get_Circles(std::vector<Curve3D*>& A);
void Sorting_Circles(std::vector<Circle3D*>& A);
double Get_Sum(std::vector<Circle3D*>& A_Circles);
double Get_Quick_Sum(std::vector<Circle3D*>& A_Circles);