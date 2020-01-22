#include "AbstractQuadrature.hpp"
#include "Trapezium.hpp"
#include "Vector.hpp"

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>

//A code that tests the quadrature codes that return the mesh points and weight
//F = Exp(x+y)

double ComputeF2D(double x, double y)
{
    return exp(x)*exp(y);
}

double IntegrateF2D(double x1, double x2, double y1, double y2)
{
    return ( exp(x2) - exp(x1) )*( exp(y2) - exp(y1) );
}

int main()
{
    double L = 1.0;
    Vector* pBoundaryX = new Vector(2);
    Vector* pBoundaryY = new Vector(2);

    (*pBoundaryX)(1) = -L;
    (*pBoundaryX)(2) = L;
    (*pBoundaryY)(1) = -L;
    (*pBoundaryY)(2) = L;

    std::cout<<"Integral exactly = "<<IntegrateF2D(-L,L,-L,L)<<std::endl;

    //int numNodesX = pow(2,2), numNodesY = pow(2,2), n = numNodesX*numNodesY;

    std::cout<<"n"<<std::setw(9)<<"h"<<std::setw(18)<<"Err"<<std::endl;
    std::cout<<"---------------------------------------"<<std::endl;

   for (int i = 2; i < 8; i++)
    {
//int i = 2;
        int numNodes = pow(2,i), n = numNodes*numNodes;

        Trapezium2D* pTrapezium = new Trapezium2D(pBoundaryX, pBoundaryY, numNodes);

        pTrapezium->ComputeMesh();
        pTrapezium->ComputeWeights();

        Vector* pMeshPointsX = new Vector(*(pTrapezium->GetMeshPointsX()));
        Vector* pMeshPointsY = new Vector(*(pTrapezium->GetMeshPointsY()));
        Vector* pWeights = new Vector(*(pTrapezium->GetWeights()));

        double sum = 0;
        double h = ( pBoundaryX->Read(1) - pBoundaryX->Read(0) ) / ( (double)(numNodes) - 1.0 );

        for(int k = 0; k < n; k++)
        {
            sum += ComputeF2D(pMeshPointsX->Read(k),pMeshPointsY->Read(k)) * (pWeights->Read(k));
        }

        double Err = fabs(sum - IntegrateF2D(-L,L,-L,L));

        std::cout<<numNodes<<std::setw(9)<<h<<std::setw(18)<<Err<<std::endl;


        delete pMeshPointsX;
        delete pMeshPointsY;
        delete pWeights;
    }


    return 0;
}
