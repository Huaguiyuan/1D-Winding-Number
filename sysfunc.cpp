#include "wind.h"
#include <cmath>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <complex>
#include <eigen3/Eigen/Eigenvalues>

#define PI 3.141592

sys::sys(double p_, double mu_, double delta_)
{

    std::complex<double> eps( mu_ - cos( p_ ), 0.0 );
    std::complex<double> gap( 0.0, delta_ * sin( p_ ) );

    hamiltonian(0,0) = 0.5 * eps;
    hamiltonian(0,1) = 0.5 * gap;
    hamiltonian(1,0) = 0.5 * std::conj(gap);
    hamiltonian(1,1) = -0.5 * eps;
    /*
    std::complex<double> eps;
    std::complex<double> gap;
    std::complex<double> I(0.0,1.0);

    eps = I * (std::polar(mu_, PI - p_) + std::polar(mu_, -PI) + std::polar(mu_,p_));
    gap = I * (1.0 + std::polar(delta_,-PI) + std::polar(delta_, PI - p_));


    hamiltonian(0,0) = 0.5 * (eps + std::conj(eps));
    hamiltonian(0,1) = 0.5 * gap;
    hamiltonian(1,0) = 0.5 * std::conj(gap);
    hamiltonian(1,1) = -0.5 * (eps + std:: conj(eps));
    */

    Eigen::ComplexEigenSolver<Eigen::Matrix2cd> ces(hamiltonian);

    Eigen::Vector2cd temp;
    temp = ces.eigenvectors().col(0);

    sVec(0) = std::real(temp.dot(pauli(1).output() * temp));
    sVec(1) = std::real(temp.dot(pauli(2).output() * temp));
    sVec(2) = std::real(temp.dot(pauli(3).output() * temp));

    Eigen::Vector2cd eigenvaluetemp;
    eigenvaluetemp = ces.eigenvalues();

    if (std::real(eigenvaluetemp[0]) < std::real(eigenvaluetemp[1]))
    {
        eigenvalue[0] = eigenvaluetemp[0];
        eigenvalue[1] = eigenvaluetemp[1];
    }
    else
    {
        eigenvalue[0] = eigenvaluetemp[1];
        eigenvalue[1] = eigenvaluetemp[0];
    }

    gapdiff = std::real(eigenvalue[1] - eigenvalue[0]);
   // std::cout << gapdiff << " ";
}
