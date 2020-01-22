#ifndef NEURALFIELD2DHEADERDEF
#define NEURALFIELD2DHEADERDEF

#include "AbstractODEInterface.hpp"

class NeuralField2D: public AbstractODEInterface
{
public:

    //this method computes and stores the rhs f of the m+1 ODEs
    void ComputeRHS(const double t, const Vector& u, Vector& f) const;

    double ComputeSynapticKernel(const double x, const double y, const double x_dash, const double y_dash) const;

    double ComputeFiringRate(const double u) const;

    void SetMeshPointsX(Vector* pMeshPointsX);

    void SetMeshPointsY(Vector* pMeshPointsY);

    void SetWeights(Vector* pWeights);

    //Specialised constructor
    NeuralField2D(const Vector parameters, const Vector* pMeshPointsX, const Vector* pMeshPointsY, const Vector* pWeights);

    //Destructor
    ~NeuralField2D();

private:

    //Hidden default constructor
    NeuralField2D();


    //Contains a vector of parameters A1,A2, b, mu, theta and other parameters if implementation requires
    Vector mParameters;

    Vector* mpMeshPointsX;
    Vector* mpMeshPointsY;
    Vector* mpWeights;
};
#endif // NEURALFIELD2DHEADERDEF

