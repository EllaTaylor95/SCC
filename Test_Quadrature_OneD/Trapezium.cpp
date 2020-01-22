#include <cassert>
#include <iostream>

#include "Vector.hpp"
#include "AbstractQuadrature.hpp"
#include "Trapezium.hpp"

Trapezium::Trapezium(const double lHBoundary, const double rHBoundary, const int numNodes)
{
    assert(lHBoundary < rHBoundary);
    SetInterval(lHBoundary, rHBoundary);

    assert(numNodes > 0);
    SetNumNodes(numNodes);

    mpMeshPoints = new Vector(mNumNodes);
    mpWeights = new Vector(mNumNodes);
}

Trapezium::~Trapezium()
{
    delete mpMeshPoints;
    delete mpWeights;
}

void Trapezium::ComputeMesh()
{
    //Mesh points of trap quadrature x_i = x0+ (xn-x0)/h
    double h = (mRHBoundary - mLHBoundary)/(mNumNodes-1.0);
    delete mpMeshPoints;
    mpMeshPoints = new Vector(mNumNodes);
    for(int i = 1; i<=mNumNodes; i++)
        {
        (*mpMeshPoints)(i) = mLHBoundary + h*(double)(i-1);
        }
}

void Trapezium::ComputeWeights()
{
    double h = (mRHBoundary - mLHBoundary)/(mNumNodes-1.0);
    delete mpWeights;
    mpWeights = new Vector(mNumNodes);
    for(int i = 2; i<=mNumNodes-1; i++)
        {
        (*mpWeights)(i) = h;
        }
    (*mpWeights)(1) = h/2.0;
    (*mpWeights)(mNumNodes) = h/2.0;
}
