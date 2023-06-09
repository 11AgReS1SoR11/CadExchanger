
#include "CMakeProject1.h"

// returns a random value from [a b]
double Random(double a, double b)
{
    return (double)rand() / RAND_MAX * (std::max(a, b) - std::min(a, b)) + std::min(a, b);
}


// the ellipse equation: ((x-x0)/a)^2 + ((y-y0)/b)^2 = 1
Point3D Ellipse3D::GetPoint(double t) const
{
    double x = R_xAxis * cos(t) + center.x;
    double y = R_yAxis * sin(t) + center.y;
    double z = center.z;
    return Point3D(x, y, z);
}

Point3D Ellipse3D::GetDerivative(double t) const
{
    double dx = -R_xAxis * sin(t);
    double dy = R_yAxis * cos(t);
    double dz = 0.0;
    return Point3D(dx, dy, dz);
}

CurveType Ellipse3D::GetType() const
{
    return ELLIPSE;
}



// Returning the radius of the circle
double Circle3D::Radius()
{
    return R_xAxis;
}

CurveType Circle3D::GetType() const
{
    return CIRCLE;
}

// The helix equation:
// x - x0 = Rcos(t)
// y - y0 = Rsin(t)
// z - z0 = at
Point3D Helix3D::GetPoint(const double t) const
{
    double x = R * cos(t) + center.x;
    double y = R * sin(t) + center.y;
    double z = step * t + center.z;
    return Point3D(x, y, z);
}

Point3D Helix3D::GetDerivative(const double t) const
{
    double dx = -R * sin(t);
    double dy = R * cos(t);
    double dz = step;
    return Point3D(dx, dy, dz);
}

CurveType Helix3D::GetType() const
{
    return HELIX;
}


// Fills an array with random shapes with random parameters (n shapes in total)
void Fill_Random_Curves(std::vector<Curve3D*>& A, const int n)
{
    for (int i = 0; i < n; i++)
    {
        Curve3D* figure = nullptr;
        // Random center value
        Point3D center = { Random(-100, 100), Random(-100, 100), Random(-100, 100) };
        // Random Curve3D
        int choose = Random(1, 4);
        if (choose == 1) figure = new Ellipse3D(Random(0.001, 100), Random(0.001, 100), center);
        else if (choose == 2) figure = new Circle3D(Random(0.001, 100), center);
        else figure = new Helix3D(Random(0.001, 100), Random(-10, 10), center);

        A.push_back(figure);
    }
}

// Outputs the values of coordinates and derivatives at a given point
void Get_Curves_Info(std::vector<Curve3D*>& A, const double t)
{
    for (const auto figure : A)
    {
        Point3D Coordinat = figure->GetPoint(t);
        Point3D Derivativ = figure->GetDerivative(t);
        std::cout << "Coordinates:\nx: " << Coordinat.x << "\ny: " << Coordinat.y << "\nz: " << Coordinat.z << std::endl;
        std::cout << "Derivativ:\nx: " << Derivativ.x << "\ny: " << Derivativ.y << "\nz: " << Derivativ.z << std::endl;
    }
}

// Returns an array of circles from an array of curves
std::vector<Circle3D*> Get_Circles(std::vector<Curve3D*>& A)
{
    std::vector<Circle3D*> A_Circles;
    for (const auto figure : A)
    {
        if (figure->GetType() == CIRCLE)
            A_Circles.push_back(dynamic_cast<Circle3D*>(figure));
    }
    return A_Circles;
}

// Sort by ascending radius
void Sorting_Circles(std::vector<Circle3D*>& A)
{
    std::sort(A.begin(), A.end(), 
        [](Circle3D* a, Circle3D* b) {
        return a->Radius() < b->Radius();
        });
}

// Returns the amount calculated without parallelism
double Get_Sum(std::vector<Circle3D*>& A_Circles)
{
    double sum = std::accumulate(A_Circles.begin(), A_Circles.end(), 0.0,
        [](double accumulator, Circle3D* circle) {
            return accumulator + circle->Radius();
        });
    return sum;
}

// Returns the amount calculated with parallelism
double Get_Quick_Sum(std::vector<Circle3D*>& A_Circles)
{
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < A_Circles.size(); ++i)
    {
        double radius = A_Circles[i]->Radius();
        sum += radius;
    }
    return sum;
}