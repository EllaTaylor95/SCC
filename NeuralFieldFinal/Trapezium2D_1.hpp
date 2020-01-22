#ifndef TRAPEZIUM2D
#define TRAPEZIUM2D

#include "Vector.hpp"
#include "AbstractQuadrature.hpp"

class Trapezium2D: public AbstractQuadrature
{
public:

    //Specialised Constructor
    Trapezium2D(const Vector* boundaryX, const Vector* boundaryY, const int numNodes);

   //Destructor
   ~Trapezium2D();

   //Virtual functions in base class to be overwritten
    void ComputeMesh();

    void ComputeWeights();

private:

    //Hidden Default Constructor
    Trapezium2D();

};
#endif // TRAPEZIUM
