#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <iomanip>

#include "Vector.hpp"
#include "RungeKutta4Solver.hpp"
#include "NeuralField.hpp"
#include "Trapezium1D.hpp"
#include "Trapezium2D.hpp"

//Function that saves our mesh to file
void SaveMesh(std::string meshFileName, Vector* pMeshPointsX, Vector* pMeshPointsY);

int main()
{
    //Setting parameters
    Vector parameters_i(5);
    parameters_i(1) = 1.0;      //A1
    parameters_i(2) = 0.0;      //A2
    parameters_i(3) = 0.4;      //b
    parameters_i(4) = 3.5;      //mu
    parameters_i(5) = 1.0;      //theta

    int m = 400;
    double L = 50;
    Vector* pBoundaryX = new Vector(2);
    Vector* pBoundaryY = new Vector(2);
    (*pBoundaryX)(1) = -L;
    (*pBoundaryX)(2) = L;
    (*pBoundaryY)(1) = -L;
    (*pBoundaryY)(2) = L;


    Vector* pMeshPointsX;
    Vector* pMeshPointsY;
    Vector* pWeights;
    Vector initialState2D(m);
    double finalTime = 10.0;
    double timeStep = 0.01;
    std::string outputFileName = "NF_2D_Trap";

    //Defining quadrature rule and assigning mesh and weights
    Trapezium2D* pTrapezium2D = new Trapezium2D(pBoundaryX, pBoundaryY, m);

    pTrapezium2D->ComputeMesh();
    pTrapezium2D->ComputeWeights();

    pMeshPointsX = new Vector(*(pTrapezium2D->GetMeshPointsX()));
    pMeshPointsY = new Vector(*(pTrapezium2D->GetMeshPointsY()));
    pWeights = new Vector(*(pTrapezium2D->GetWeights()));

    for(int i = 0; i<m; i++)
    {
        initialState2D(i+1) = 6.0*exp(-(pow(pMeshPointsX->Read(i),2)+pow(pMeshPointsY->Read(i),2))/5.77);
    }

    std::string meshOutputFile = "Mesh2D";
    SaveMesh(meshOutputFile, pMeshPointsX, pMeshPointsY);

    //Defining Neural field system
    NeuralField2D neural_field_i(parameters_i,pMeshPointsX,pMeshPointsY,pWeights);

    RungeKutta4Solver* pSolver = new RungeKutta4Solver(neural_field_i, initialState2D, 0.0, finalTime, timeStep, outputFileName,1,100);

    //pSolver->Solve();

    delete pWeights;
    delete pMeshPointsX;
    delete pMeshPointsY;

    //Changing to 1D case
    //Reassigning number of nodes from [-L,L]
    m = 301;
    double alpha = 0.1;
    Vector initialState1D(m);
    std::string outputFileName1D = "NF_1D_Trap";

    Trapezium1D* pTrapezium1D = new Trapezium1D(-L,L,m);
    pTrapezium1D->ComputeMesh();
    pTrapezium1D->ComputeWeights();

    pMeshPointsX = new Vector(*(pTrapezium1D->GetMeshPointsX()));
    pMeshPointsY = new Vector(m); //Leave all entries equal to zero
    pWeights = new Vector(*(pTrapezium1D->GetWeights()));

    //Saving mesh
    std::string meshOutputFile = "Mesh1D";
    SaveMesh(meshOutputFile, pMeshPointsX, pMeshPointsY);


    for (int i = 1; i<=m; i++)
    {
        initialState1D(i) = 4.0/(pow(cosh(alpha*pMeshPointsX->Read(i-1)),2.0));
    }

    neural_field_i.SetMeshPointsX(pMeshPointsX);
    neural_field_i.SetMeshPointsY(pMeshPointsY);
    neural_field_i.SetWeights(pWeights);

    pSolver->SetInitialState(initialState1D);
    pSolver->SetOutputFileName(outputFileName1D);

    //pSolver->Solve();

    delete pWeights;
    delete pMeshPointsX;
    delete pMeshPointsY;

    return 0;

}

void SaveMesh(std::string meshFileName, Vector* pMeshPointsX, Vector* pMeshPointsY)
{
    int size = pMeshPointsX->GetSize();

    std::ofstream output_file;
    output_file.setf(std::ios::scientific,std::ios::floatfield);
    output_file.precision(6);
    //Indicating which file to open
    output_file.open(meshFileName, std::fstream::in | std::fstream::out | std::fstream::app);
    output_file<<"X  ";
    for (int i=0; i<size; i++)
        {
        output_file << std::scientific
                << std::setprecision(6)
                << std::setw(40) << pMeshPointsX->Read(i)<<"  ";
            }
            output_file<<std::endl<<"Y  ";


    for (int i=0; i<size; i++)
        {
        output_file << std::scientific
                << std::setprecision(6)
                << std::setw(40) << pMeshPointsY->Read(i)<<"  ";
            }
            output_file<<std::endl;

    output_file.close();

}
