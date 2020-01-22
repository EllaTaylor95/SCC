#include <cassert>
#include <iostream>
#include <cmath>

#include "Vector.hpp"
#include "AbstractQuadrature.hpp"
#include "Trapezium2D.hpp"

Trapezium2D::Trapezium2D(const Vector* boundaryX, const Vector* boundaryY, const int totalNumNodes)
{
    SetInterval(boundaryX, boundaryY);

    assert(totalNumNodes > 0);
    SetNumNodes(totalNumNodes);

    mpMeshPointsX = new Vector(totalNumNodes);
    mpMeshPointsY = new Vector(totalNumNodes);
    mpWeights = new Vector(totalNumNodes);
}

Trapezium2D::~Trapezium2D()
{
    delete mpMeshPointsX;
    delete mpMeshPointsY;
    delete mpWeights;
}

void Trapezium2D::ComputeMesh()
{
    int numNodes1D = (int)(pow(mNumNodes,0.5));
    double h = (mpBoundaryX->Read(1) - mpBoundaryX->Read(0))/(double)(numNodes1D-1.0);

    for(int j = 1; j<=numNodes1D; j++)
    {
        for(int i = 1; i<=numNodes1D; i++)
        {
            int k = (j-1)*numNodes1D + i;
            (*mpMeshPointsX)(k) = mpBoundaryX->Read(0) + h*(double)(i-1);
            (*mpMeshPointsY)(k) = mpBoundaryY->Read(0) + h*(double)(j-1);
        }
    }
}

void Trapezium2D::ComputeWeights()
{
    int numNodes1D = (int)(pow(mNumNodes,0.5));
    double h = (mpBoundaryX->Read(1) - mpBoundaryX->Read(0))/(double)(numNodes1D-1.0);

    for(int j = 1; j<=numNodes1D; j++)
    {
        for(int i = 1; i<=numNodes1D; i++)
        {
            int k = (j-1)*numNodes1D + i;
           (*mpWeights)(k) = h*h;

            if( i == 1 || i == numNodes1D || j == 1 || j == numNodes1D )
            {
                (*mpWeights)(k) = 0.5*h*h;
            }

            if( ( i == 1 && j == 1 ) || ( i == 1 && j == numNodes1D) || ( i == numNodes1D && j == 1 ) || ( i == numNodes1D && j == numNodes1D ) )
            {
                (*mpWeights)(k) = 0.25*h*h;
            }
        }
    }
}
