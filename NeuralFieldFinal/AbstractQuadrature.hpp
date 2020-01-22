#ifndef ABSTRACTQUADRATURE
#define ABSTRACTQUADRATURE

#include "Vector.hpp"

class AbstractQuadrature
{
public:

    virtual void ComputeMesh() = 0;

    virtual void ComputeWeights() = 0;

    void SetNumNodes(const int numNodes);

    void SetInterval(const Vector* boundaryX, const Vector* boundaryY);

    Vector* GetMeshPointsX() const;

    Vector* GetMeshPointsY() const;

    Vector* GetWeights() const;

    int GetNumNodes() const;

protected:

//Boundary of mesh
Vector* mpBoundaryX;
Vector* mpBoundaryY;

//number of nodes in each direction
int mNumNodes;

Vector* mpMeshPointsX;
Vector* mpMeshPointsY;
Vector* mpWeights;

};
#endif // ABSTRACTQUADRATURE
