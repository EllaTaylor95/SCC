#include <cassert>

#include "Vector.hpp"
#include "AbstractQuadrature.hpp"

void AbstractQuadrature::SetNumNodes(const int numNodes)
{
    mNumNodes = numNodes;
}

void AbstractQuadrature::SetInterval(const Vector* boundaryX, const Vector* boundaryY)
{
    mpBoundaryX = new Vector(*boundaryX);
    mpBoundaryY = new Vector(*boundaryY);
}

Vector* AbstractQuadrature::GetMeshPointsX() const
{
    return mpMeshPointsX;
}

Vector* AbstractQuadrature::GetMeshPointsY() const
{
    return mpMeshPointsY;
}

Vector* AbstractQuadrature::GetWeights() const
{
    return mpWeights;
}

int AbstractQuadrature::GetNumNodes() const
{
    return mNumNodes;
}

