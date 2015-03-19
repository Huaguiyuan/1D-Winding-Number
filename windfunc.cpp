#include "wind.h"
#include <iostream>

#define PI 3.141592

void wind::linspace(double pmin, double pmax, int pint)
{
    double step = (pmax-pmin) / (pint-1);
    double shift = 1e-4;

    while(pmin <= pmax)
    {
        pVec.push_back(pmin);
        pVecShift.push_back(pmin+shift);
        pmin += step;
    }
}


wind::wind( double mu_, double delta_, int pint_ )
{
    int i;
    linspace(-PI,PI,pint_);
    for(i = 0; i < pint_; i++)
    {
        momSpace.resize(i,sys(pVec[i], mu_, delta_));
        momSpaceShift.resize(i,sys(pVecShift[i], mu_, delta_));
    }


    double shift = 1e-4;
    windN = 0;
    Eigen::Vector3d temp, tempShift, dsVec, crossed, normV;
    double windPart;
    double windTemp;
    double gaptemp = 100.0;

    for(i = 0; i < pint_-1; i++)
    {

        temp = momSpace[i].output();
        tempShift = momSpaceShift[i].output();
        dsVec = (tempShift - temp)/shift;
        crossed = temp.cross(dsVec);
        normV(0) = std::abs(crossed(0)/(crossed.norm() + 1e-5));
        normV(1) = std::abs(crossed(1)/(crossed.norm() + 1e-5));
        normV(2) = std::abs(crossed(2)/(crossed.norm() + 1e-5));
        windPart = crossed.dot(normV);

        windTemp += windPart;

        //std::cout << tempShift << '\t' << temp;
    }

    windN = windTemp/pint_;

    for (i = 0; i < pint_-1; i++)
    {
        if ( momSpace[i].getgap() < gaptemp )
        {
            gaptemp = momSpace[i].getgap();
        }
    }

    mingap = gaptemp;
}
