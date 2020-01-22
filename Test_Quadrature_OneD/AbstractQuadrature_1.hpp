#ifndef ABSTRACTQUADRATURE
#define ABSTRACTQUADRATURE

#include "Vector.hpp"

class AbstractQuadrature
{
public:

    virtual void ComputeMesh() = 0;

    virtual void ComputeWeights() = 0;

    void SetNumNodes(const int numNodes);

    void SetInterval(const double lHBoundary, const double rHBoundary);

    Vector* GetMeshPoints() const;

    Vector* GetWeights() const;

    int GetNumNodes() const;

protected:

//Boundary of mesh
double mLHBoundary;
double mRHBoundary;

//number of nodes
int mNumNodes;

Vector* mpMeshPoints;
Vector* mpWeights;

};
#endif // ABSTRACTQUADRATURE
