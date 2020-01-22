#include "AbstractQuadrature.hpp"
#include "Trapezium.hpp"
#include "Vector.hpp"

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>

//A code that tests the quadrature codes that return the mesh points and weight


double ComputeF(double x)
{
    return exp(x);
}

double IntegrateF(double x1, double x2)
{
    return exp(x2) - exp(x1);
}

double CalculatedTrapezium(double* meshPoints, double* weights, double lHBoundary, double rHBoundary, int numNodes)
{
   double h = (rHBoundary - lHBoundary)/(double)(numNodes-1), sum = 0.0;

   for (int i = 0; i<numNodes; i++)
   {
       //Mesh points
       meshPoints[i] = lHBoundary + h*i;

       //Weights
       if((i > 0) && (i < numNodes - 1))
       {
           weights[i] = h;
       }
       else
       {
           weights[i] = h/2.0;
       }

       //Computing the Trapezium approximation
       sum =+ ComputeF(meshPoints[i])*weights[i];
   }
   return sum;
}

int main()
{
    int numNodes;

    std::cout<<"h"<<std::setw(7)<<"Error"<<std::endl;

    for(int j = 1; j < 8; j++)
    {
    numNodes = pow(10,j)+1;

    double lHBoundary = 0.0, rHBoundary = 1.0, sum = 0.0;
    double* actualMeshPoints = new double[numNodes];
    double* actualWeights = new double[numNodes];

    CalculatedTrapezium(actualMeshPoints, actualWeights, lHBoundary, rHBoundary, numNodes);

    Trapezium* pTrapezium = new Trapezium(lHBoundary, rHBoundary, numNodes);

    double spaceStep = (rHBoundary - lHBoundary)/((double)(numNodes - 1));

    Vector* pMeshPoints = new Vector(numNodes);
    Vector* pWeights = new Vector(numNodes);

    pTrapezium->ComputeMesh();
    pTrapezium->ComputeWeights();

    for(int i = 1; i<=numNodes; i++)
    {
        (*pMeshPoints)(i) = (*(pTrapezium->GetMeshPoints()))(i);
        (*pWeights)(i) = (*(pTrapezium->GetWeights()))(i);
//        assert(fabs(actualMeshPoints[i-1]-(*pMeshPoints)(i))<pow(10,-3));
//        assert(fabs(actualWeights[i-1] - (*pWeights)(i))<pow(10,-3));

        sum += ComputeF((*pMeshPoints)(i))*((*pWeights)(i));
    }

    double Error = fabs(sum - IntegrateF(lHBoundary, rHBoundary));
    std::cout<<(rHBoundary - lHBoundary)/(numNodes-1)<<std::setw(15)<<Error<<std::endl;

    delete pMeshPoints;
    delete pWeights;
    delete pTrapezium;
    }

    return 0;
}
