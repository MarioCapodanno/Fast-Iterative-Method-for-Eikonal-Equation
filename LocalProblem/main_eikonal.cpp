/*
 * main_eikonal.cpp
 *
 *  Created on: Jun 18, 2022
 *      Author: forma
 */
#include "Phi.hpp"
#include "solveEikonalLocalProblem.hpp"
#include <iostream>

#include <limits>

const double INF = std::numeric_limits<double>::infinity();

int main()
{
    // create a simplex
#if DIMENSION==2
    constexpr std::size_t PHDIM=2;

    using Point=Eikonal::Eikonal_traits<PHDIM>::Point;
    using VectorExt=Eikonal::Eikonal_traits<PHDIM>::VectorExt;
    Point p1,p2,p3,p4;
    p1<<0.,0.1;
    p2<<0.,1.5;
    p3<<1.,0.;
    p4<<0.1,0.;

    Eikonal::Eikonal_traits<PHDIM>::MMatrix M;
    M<<3.0,0.0,
       0.0,9.0;
    VectorExt values;
    values<<INF,0;          //values of u at the base
    Eikonal::SimplexData<PHDIM> simplex{{p1,p2,p3},M};

    Eikonal::solveEikonalLocalProblem<PHDIM> solver{simplex,values};
    auto sol = solver();
    std::cout<<"Solution="<<sol.value<<" lambda:"<<sol.lambda.transpose()<<" status:"<<sol.status<<"\n";
#else
    constexpr std::size_t PHDIM=3;
/*
 * tetra
[[0.1 0.2 0.5]
 [0.2 0.1 0.5]
 [0.1 0.1 0.5]
 [0.2 0.1 0.4]]
values
[[4.04806282e-01]
 [4.04806776e-01]
 [1.00000000e+07]]
 */
    using Point=Eikonal::Eikonal_traits<PHDIM>::Point;
    using VectorExt=Eikonal::Eikonal_traits<PHDIM>::VectorExt;
    Point p1,p2,p3,p4;
    p1<<0.1, 0.2, 0.5;
    p2<<0.2,0.1,0.5;
    p3<<0.1,0.1,0.5;
    p4<<0.2,0.1,0.4;


    Eikonal::Eikonal_traits<PHDIM>::MMatrix M;
    M<<1.0,-0.0,0.0,
       0.0,1.0,-0.0,
       0.0,-0.0,1.0;
    VectorExt values;
    values<<1.,1.,1.00000000;
    for (auto i=0; i<10;++i) // a few values, just to try what happens
        {
          values[1]=0.+0.5*i;
          p1[1]=0.1+i/10.;
    Eikonal::SimplexData<PHDIM> simplex{{p1,p2,p3,p4},M};
    Eikonal::solveEikonalLocalProblem<PHDIM> solver{std::move(simplex),
          values};
    auto sol = solver();
    std::cout<<"Solution="<<sol.value<<" lambda:"<<sol.lambda.transpose()<<" status:"<<sol.status<<"\n";
        }

#endif

}



