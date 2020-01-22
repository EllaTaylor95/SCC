#ifndef ABSTRACTODEINTERFACEHEADERDEF
#define ABSTRACTODEINTERFACEHEADERDEF

#include "Vector.hpp"

class AbstractODEInterface
{
  public:

    virtual void ComputeAnalyticSolution(const double t, Vector& u ) const;

    // Compute right-hand side (pure virtual)
    virtual void ComputeRHS(const double t, const Vector& u, Vector& f ) const = 0;

};

#endif //ABSTRACTODEINTERFACE
