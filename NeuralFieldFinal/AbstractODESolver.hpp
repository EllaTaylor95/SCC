#ifndef ABSTRACTODESOLVERHEADERDEF //instructs compiler to computer the code below only if macro is not already defined
#define ABSTRACTODESOLVERHEADERDEF //define the macro. this ensures code is only compiled once no matter how many times it is included

#include "AbstractODEInterface.hpp"
#include "Vector.hpp"

#include <iostream>

class AbstractODESolver
{
    public:

    //Defining the Solve() a pure virtual method
    virtual void Solve() = 0;

    void PrintHeader(const std::string solverName, const double stepSize) const;

    void SaveHeader(const std::string solverName, const double stepSize, std::string outputFileName) const;

    void PrintSolution(const double t, const Vector &u) const;

    void SaveSolution(const double t, const Vector &u, std::string outputFileName) const;

    double GetInitialTime() const;

    double GetFinalTime() const;

    Vector GetInitialState() const;

    void SetStepSize(const double h);

    void SetTimeInterval(const double t0, const double t1);

    void SetInitialState(Vector& initialState);

    void SetODESystem(AbstractODEInterface& anODESystem);

    void SetPrintGap(const int printGap);

    void SetSaveGap(const int saveGap);

    void SetOutputFileName(const std::string outputFileName);

    protected:

    // Initial and final times
    double mFinalTime;
    double mInitialTime;

    // The ODE system under consideration
    AbstractODEInterface* mpODESystem;

    // Stepsize h
    double mStepSize;

    Vector* mpState;

    int mSaveGap;
    int mPrintGap;

    std::string mOutputFileName;

};

#endif // ABSTRACTODESOLVERHEADERDEF
