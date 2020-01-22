#include <iostream>
#include <cmath>

#include "NeuralField.hpp"


NeuralField2D::NeuralField2D(const Vector parameters, const Vector* pMeshPointsX, const Vector* pMeshPointsY, const Vector* pWeights): mParameters(parameters)
{
    mpMeshPointsX = new Vector(*pMeshPointsX);
    mpMeshPointsY = new Vector(*pMeshPointsY);
    mpWeights = new Vector(*pWeights);
}

void NeuralField2D::SetMeshPointsX(Vector* pMeshPointsX)
{
    mpMeshPointsX = new Vector(*pMeshPointsX);
}

void NeuralField2D::SetMeshPointsY(Vector* pMeshPointsY)
{
    mpMeshPointsY = new Vector(*pMeshPointsY);
}

void NeuralField2D::SetWeights(Vector* pWeights)
{
    mpWeights = new Vector(*pWeights);
}

double NeuralField2D::ComputeSynapticKernel(const double x, const double y, const double x_dash, const double y_dash) const
{
    double euclideanDist = pow(pow(x - x_dash,2)+pow(y - y_dash,2),0.5);
    return mParameters.Read(0)*exp(-pow(euclideanDist,2)) + mParameters.Read(1)*exp(-mParameters.Read(2)*euclideanDist)*(mParameters.Read(2)*sin(euclideanDist)+cos(euclideanDist));
}

double NeuralField2D::ComputeFiringRate(const double u) const
{
    return 1.0/(1.0+ exp(-mParameters.Read(3)*(u-mParameters.Read(4))));
}

void NeuralField2D:: ComputeRHS(const double t, const Vector &u, Vector &f) const
{
    int numNodes = mpWeights->GetSize();
    Vector sum(numNodes);

    for(int i = 1; i<=numNodes; i++)
    {
        for (int j = 1; j<=numNodes; j++)
            {
            sum(i) =+ ComputeSynapticKernel(mpMeshPointsX->Read(i-1),mpMeshPointsY->Read(i-1),mpMeshPointsX->Read(j-1),mpMeshPointsY->Read(j-1))*ComputeFiringRate(u.Read(j-1))*mpWeights->Read(j-1);
            }
        //Calculating f
        f(i) = -u.Read(i-1) + sum(i);
    }
}

NeuralField2D::~NeuralField2D()
{
    delete mpMeshPointsX;
    delete mpMeshPointsY;
    delete mpWeights;
}
