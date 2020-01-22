#ifndef RUNGEKUTTER4SOLVERHEADERDEF
#define RUNGEKUTTER4SOLVERHEADERDEF

#include "AbstractODESolver.hpp"
#include "Vector.hpp"
#include "AbstractODEInterface.hpp"

class RungeKutta4Solver: public AbstractODESolver
{
public:

    //Specialise constructor
    RungeKutta4Solver(AbstractODEInterface& anODESystem, Vector& initialState, const double initialTime, const double finalTime,
    const double stepSize, const std::string outputFileName, const int saveGap, const int printGap);

    //Overriding the pure virtual method
    void Solve();

    //Destructor
    ~RungeKutta4Solver();

private:

    //Hidden default constructor
    RungeKutta4Solver();

    double mTime;

};
#endif //RUNGEKUTTER4SOLVERHEADERDEF
