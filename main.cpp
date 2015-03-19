#include "wind.h"


int main()
{
    double mumin_   = -2.0; //minimum chemical potential
    double mumax_   = 2.0;  //maximum chemical potential
    int muint_      = 61;  //descritisation of chemical potential
    double deltamin_= -2.0; //minimum pairing coupling
    double deltamax_= 2.0;  //maximum pairing coupling
    int deltaint_   = 61;  //descretisation of pairing coupling
    int pint_       = 100;  //descretisation of momentum space
    /*
    double mumin_   = 0.0; //minimum chemical potential
    double mumax_   = 1.0;  //maximum chemical potential
    int muint_      = 101;  //descritisation of chemical potential
    double deltamin_= 0.0; //minimum pairing coupling
    double deltamax_= 1.0;  //maximum pairing coupling
    int deltaint_   = 101;  //descretisation of pairing coupling
    int pint_       = 501;  //descretisation of momentum space
    */

    phasespace PS(mumin_, mumax_, muint_, deltamin_, deltamax_, deltaint_, pint_);
    return 0;
}
