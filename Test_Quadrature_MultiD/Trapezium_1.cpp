#include <cassert>
#include <iostream>
#include <cmath>

#include "Vector.hpp"
#include "AbstractQuadrature.hpp"
#include "Trapezium.hpp"

Trapezium2D::Trapezium2D(const Vector* boundaryX, const Vector* boundaryY, const int numNodes)
{
    SetInterval(boundaryX, boundaryY);

    assert(numNodes > 0);
    SetNumNodes(numNodes);

    int n = numNodes*numNodes;
    mpMeshPointsX = new Vector(n);
    mpMeshPointsY = new Vector(n);
    mpWeights = new Vector(n);
}

Trapezium2D::~Trapezium2D()
{
    delete mpMeshPointsX;
    delete mpMeshPointsY;
    delete mpWeights;
}

void Trapezium2D::ComputeMesh()
{
    double h = (mpBoundaryX->Read(1) - mpBoundaryX->Read(0))/(double)(mNumNodes-1.0);

    for(int j = 1; j<=mNumNodes; j++)
    {
        for(int i = 1; i<=mNumNodes; i++)
        {
            int k = (j-1)*mNumNodes + i;
            (*mpMeshPointsX)(k) = mpBoundaryX->Read(0) + h*(double)(i-1);
            (*mpMeshPointsY)(k) = mpBoundaryY->Read(0) + h*(double)(j-1);
        }
    }
}

void Trapezium2D::ComputeWeights()
{

    double h = (mpBoundaryX->Read(1) - mpBoundaryX->Read(0))/(double)(mNumNodes-1.0);

    for(int j = 1; j<=mNumNodes; j++)
    {
        for(int i = 1; i<=mNumNodes; i++)
        {
            int k = (j-1)*mNumNodes + i;
           (*mpWeights)(k) = h*h;

            if( i == 1 || i == mNumNodes || j == 1 || j == mNumNodes )
            {
                (*mpWeights)(k) = 0.5*h*h;
            }

            if( ( i == 1 && j == 1 ) || ( i == 1 && j == mNumNodes) || ( i == mNumNodes && j == 1 ) || ( i == mNumNodes && j == mNumNodes ) )
            {
                (*mpWeights)(k) = 0.25*h*h;
            }
        }
    }
}
