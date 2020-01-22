#ifndef TRAPEZIUM1D
#define TRAPEZIUM1D

#include "Vector.hpp"
#include "AbstractQuadrature.hpp"

class Trapezium1D: public AbstractQuadrature
{
public:

    //Specialised Constructor
    Trapezium1D(const double lHBoundary, const double rHBoundary, const int numNodes);

   //Destructor
   ~Trapezium1D();

   //Virtual functions in base class to be overwritten
    void ComputeMesh();

    void ComputeWeights();

private:

    //Hidden Default Constructor
    Trapezium1D();

};
#endif // TRAPEZIUM1D
