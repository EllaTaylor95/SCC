#include <iostream>
#include <assert.h>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>

#include "RungeKutta4Solver.hpp"

RungeKutta4Solver::RungeKutta4Solver(AbstractODEInterface& anODESystem, Vector &initialState, const double initialTime, const double finalTime,
const double stepSize, const std::string outputFileName, const int saveGap, const int printGap)
{
    SetODESystem(anODESystem);
    SetInitialState(initialState);
    SetTimeInterval(initialTime, finalTime);
    SetStepSize(stepSize);
    SetOutputFileName(outputFileName);
    SetSaveGap(saveGap);
    SetPrintGap(printGap);
}

void RungeKutta4Solver::Solve()
{
//Getting size of system
int size = mpState->GetSize();
int numSteps = 0;
mTime = mInitialTime;

//Setting initial value
Vector uTemp(size);

//Initialising ks
Vector k1(size);
Vector k2(size);
Vector k3(size);
Vector k4(size);

PrintHeader("Runge Kutter 4 Method", mStepSize);
SaveHeader("RungeKutta4Solver", mStepSize, mOutputFileName);
PrintSolution(mTime,*mpState);
SaveSolution(mTime,*mpState,mOutputFileName);

while(mTime < mFinalTime)
    {
    //Computing new solution
    mpODESystem->ComputeRHS(mTime,*mpState, k1);
    for(int i = 1; i<=size; i++)
    {
        uTemp(i) = (*mpState)(i) + k1.Read(i-1)*mStepSize/2.0;
    }
    mpODESystem->ComputeRHS(mTime+(mStepSize/2.0),uTemp,k2);
    for(int i = 1; i<=size; i++)
    {
        uTemp(i) = (*mpState)(i) + k2.Read(i-1)*mStepSize/2.0;
    }
    mpODESystem->ComputeRHS(mTime+(mStepSize/2.0),uTemp,k3);
    for(int i = 1; i<=size; i++)
    {
        uTemp(i) = (*mpState)(i) + k3.Read(i-1)*mStepSize;
    }
    mpODESystem->ComputeRHS(mTime+mStepSize,uTemp,k4);

    for(int i = 1; i<=size; i++)
    {
        (*mpState)(i) = (*mpState)(i) + (k1.Read(i-1) + 2.0*k2.Read(i-1) + 2.0*k3.Read(i-1) + k4.Read(i-1))*(mStepSize/6.0);
    }
    mTime += mStepSize;
    numSteps++;

    if(numSteps % mPrintGap == 0)
        {
        PrintSolution(mTime, *mpState);
        }
    if(numSteps % mSaveGap == 0)
        {
        SaveSolution(mTime, *mpState, mOutputFileName);
        }
    }
}

RungeKutta4Solver::~RungeKutta4Solver()
{
    delete mpState;
}
