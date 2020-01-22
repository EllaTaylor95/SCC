#ifndef TRAPEZIUM
#define TRAPEZIUM

#include "Vector.hpp"
#include "AbstractQuadrature.hpp"

class Trapezium: public AbstractQuadrature
{
    public:

    //Specialised Constructor
    Trapezium(const double lHBoundary, const double rHBoundary, const int numNodes);

   //Destructor
   ~Trapezium();

   //Virtual functions in base class to be overwritten
    void ComputeMesh();

    void ComputeWeights();

    private:

    //Hidden Default Constructor
    Trapezium();

};
#endif // TRAPEZIUM
