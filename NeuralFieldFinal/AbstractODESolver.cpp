#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

#include "AbstractODESolver.hpp"

// Printing details of solver and headers before iterations begin
void AbstractODESolver::
PrintHeader(const std::string solverName, const double stepSize) const
{
  std::cout << "------------------------------------------------"
            << std::endl
            << " Attempt to solve system of ODEs using " + solverName
            << std::endl
            <<" Step size = " << stepSize <<std::endl
            << "------------------------------------------------"
            << std::endl;
                std::cout << std::setw(10) << "Time"
              << std::setw(40) << "uCalc"
              << std::endl;
}

//Method to save header to file
void AbstractODESolver::SaveHeader(const std::string solverName, const double stepSize, std::string outputFileName) const
{

    //File
    std::ofstream output_file;
    output_file.setf(std::ios::scientific,std::ios::floatfield);
    output_file.precision(6);
    //Indicating which file to open
    output_file.open(outputFileName);
    //Checking file is open
    assert(output_file.is_open());

    output_file << "------------------------------------------------"
            << std::endl
            << " Attempt to solve system of ODEs using " + solverName
            << std::endl
            <<" Step size = " << stepSize <<std::endl
            << "------------------------------------------------"
            << std::endl;
    output_file << std::setw(10) << "Time"
              << std::setw(40) << "uCalc"
              << std::endl;

    output_file.close();
}

//Printing out details at each iteration
void AbstractODESolver::PrintSolution(const double t, const Vector &u) const
{
    //Printing t
    std::cout << std::setw(10) << t;

    //Determining if d or 3 is larger
    int n;
    if(u.GetSize()>=3)
        {
        n = 3;
        }
    else
        {
        n = u.GetSize();
        }
    //Printing solution
    for (int i=0; i<n; i++)
        {
        std::cout << std::scientific
                << std::setprecision(6)
                << std::setw(40) << u.Read(i) <<"   ";
        }
        std::cout<<std::endl;

//    //Bool to determine if we print out E(h)
//    if (initialiseE)
//        {
//        std::cout << std::scientific
//                << std::setprecision(6)
//                << "E(h) =" << E<<std::endl;
//        }
}

//Method to save data to file
void AbstractODESolver::SaveSolution(const double t, const Vector &u, std::string outputFileName) const
{
    //File
    std::ofstream output_file;
    output_file.setf(std::ios::scientific,std::ios::floatfield);
    output_file.precision(6);
    //Indicating which file to open
    output_file.open(outputFileName, std::fstream::in | std::fstream::out | std::fstream::app);
    //Checking file is open
    assert(output_file.is_open());

    //True if we want to print out solution
    output_file << std::setw(10) << t;
        //Saving all entries of the solution to file
        for (int i=0; i<u.GetSize(); i++)
            {
            output_file << std::scientific
                << std::setprecision(6)
                << std::setw(40) << u.Read(i);
            }
            output_file<<std::endl;

    output_file.close();

}

double AbstractODESolver::GetInitialTime() const
{
    return mInitialTime;
}

double AbstractODESolver::GetFinalTime() const
{
    return mFinalTime;
}

Vector AbstractODESolver::GetInitialState() const
{
    return *mpState;
}

void AbstractODESolver::SetStepSize(const double h)
{
    mStepSize = h;
}

void AbstractODESolver::SetTimeInterval(const double t0, const double t1)
{
    mInitialTime = t0;
    mFinalTime = t1;
}

void AbstractODESolver::SetInitialState(Vector& initialState)
{
    mpState = &initialState;
}

void AbstractODESolver::SetODESystem(AbstractODEInterface& anODESystem)
{
    mpODESystem = &anODESystem;
}

void AbstractODESolver::SetPrintGap(const int printGap)
{
    mPrintGap = printGap;
}

void AbstractODESolver::SetSaveGap(const int saveGap)
{
    mSaveGap = saveGap;
}

void AbstractODESolver::SetOutputFileName(const std::string outputFileName)
{
    mOutputFileName = outputFileName;
}
