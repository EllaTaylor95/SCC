#include <cassert>
#include <iostream>

#include "Vector.hpp"
#include "AbstractQuadrature.hpp"
#include "Trapezium1D.hpp"

Trapezium1D::Trapezium1D(const double lHBoundary, const double rHBoundary, const int numNodes)
{
    assert(lHBoundary < rHBoundary);
    (*mpBoundaryX)(1) = lHBoundary;
    (*mpBoundaryX)(2) = rHBoundary;

    assert(numNodes > 0);
    SetNumNodes(numNodes);

}

Trapezium1D::~Trapezium1D()
{
    delete mpMeshPointsX;
    delete mpWeights;
}

void Trapezium1D::ComputeMesh()
{
    //Mesh points of trap quadrature x_i = x0+ (xn-x0)/h
    double h = (mpBoundaryX->Read(1)- mpBoundaryX->Read(0))/(double)((mNumNodes-1.0));
    mpMeshPointsX = new Vector(mNumNodes);
    for(int i = 1; i<=mNumNodes; i++)
        {
        (*mpMeshPointsX)(i) = mpBoundaryX->Read(0) + h*(double)(i-1);
        }
}

void Trapezium1D::ComputeWeights()
{
    double h = (mpBoundaryX->Read(1)- mpBoundaryX->Read(0))/(double)((mNumNodes-1.0));
    mpWeights = new Vector(mNumNodes);
    for(int i = 2; i<=mNumNodes-1; i++)
        {
        (*mpWeights)(i) = h;
        }
    (*mpWeights)(1) = h/2.0;
    (*mpWeights)(mNumNodes) = h/2.0;
}
