#ifndef SIMPLE_H
#define SIMPLE_H

#include <complex>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
#include <iostream>


class pauli //defines a pauli matrix based on pauli_type_ = {1,2,3}
{
    private:
    Eigen::Matrix2cd emptyp;

    public:
    pauli( int pauli_type_ );
    Eigen::Matrix2cd output() { return emptyp;}
};

class sys //defines the hamiltonian and computes the eigenvectors, eigenvalues and winding vector
{
    private:
    Eigen::Matrix2cd hamiltonian;
    Eigen::Vector3d sVec;
    Eigen::Vector2cd eigenvalue;
    double gapdiff;

    public:
    sys(double p, double mu, double delta);
    Eigen::Vector3d output() { return sVec; }
    double getgap() { return gapdiff; }
};

class wind //calculates the winding number and the gap of the system
{
    private:
    std::vector<sys> momSpace;
    std::vector<sys> momSpaceShift;
    std::vector<double> pVec;
    std::vector<double> pVecShift;
    std::vector<double> gaps;
    double windN;
    double mingap;


    public:
    wind( double mu_, double delta_ , int pint_);
    void linspace(double pmin, double pmax, int pint);
    void printWind() {std::cout << windN;}
    double getWind() {return windN;}
    double getgapmin() { return mingap; }
};

class phasespace //scans phase space and calculates the gap and winding number at each point
{
    private:
    std::vector<std::vector<wind>> space;
    std::vector<double> muVec;
    std::vector<double> deltaVec;

    public:
    phasespace(double mumin_, double mumax_, int muint_, double deltamin_, double deltamax_, int deltaint_, int pint_);
    void mulinspace(double mumin_, double mumax_, int muint_);
    void deltalinspace(double deltamin_, double deltamax_, int deltaint_);
    double getmu( int munum_ ) {return muVec[munum_];}
    double getdelta( int deltanum_ ) {return deltaVec[deltanum_];}
    double getWinding(int munum_, int deltanum_);
};

#endif
