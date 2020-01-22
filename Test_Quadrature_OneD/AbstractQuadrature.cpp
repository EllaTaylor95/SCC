#include "Vector.hpp"
#include "AbstractQuadrature.hpp"

void AbstractQuadrature::SetNumNodes(const int numNodes)
{
    mNumNodes = numNodes;
}

void AbstractQuadrature::SetInterval(const double lHBoundary, const double rHBoundary)
{
    mLHBoundary = lHBoundary;
    mRHBoundary = rHBoundary;
}

Vector* AbstractQuadrature::GetMeshPoints() const
{
    return mpMeshPoints;
}

Vector* AbstractQuadrature::GetWeights() const
{
    return mpWeights;
}


int AbstractQuadrature::GetNumNodes() const
{
    return mNumNodes;
}

//
//void AbstractQuadrature::AssignWeights(Vector& pWeights) const
//{
//    *mpWeights = pWeights;
//}
//
//void AbstractQuadrature::AssignMesh(Vector& pMeshPoints) const
//{
//    *mpMeshPoints = pMeshPoints;
//}
