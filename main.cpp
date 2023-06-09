#include "CMakeProject1.h"

// Usage example

int main()
{
    // Enter the number of curves and the array in which they will be stored
    int n = 100;
    std::vector<Curve3D*> A;

    // Filling the array with n random curves
    Fill_Random_Curves(A, n);

    // Calculate the coordinates and the derivative (PI / 4) for each curve
    double t = MyPI / 4;
    Get_Curves_Info(A, t);

    // We get an array of pointers to circles
    std::vector<Circle3D*> A_Circles = Get_Circles(A);

    // Sorting
    Sorting_Circles(A_Circles);

    // Counting the sum of the radii
    std::cout << Get_Sum(A_Circles) << std::endl;

    // Ñalculate the sum of the radii using parallelization
    std::cout << Get_Quick_Sum(A_Circles) << std::endl;

    return 0;
}