/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::mySutherlandTransport

Description
    Transport package using Sutherland's formula.

    Templated into a given thermodynamics package (needed for thermal
    conductivity).

    Dynamic viscosity [kg/m.s]
    \f[
        \mu = A_s \frac{\sqrt{T}}{1 + T_s / T}
    \f]

SourceFiles
    mySutherlandTransportI.H
    mySutherlandTransport.C

\*---------------------------------------------------------------------------*/

#ifndef mySutherlandTransport_H
#define mySutherlandTransport_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of friend functions and operators

template<class Thermo> class mySutherlandTransport;

template<class Thermo>
inline mySutherlandTransport<Thermo> operator+
(
    const mySutherlandTransport<Thermo>&,
    const mySutherlandTransport<Thermo>&
);

template<class Thermo>
inline mySutherlandTransport<Thermo> operator*
(
    const scalar,
    const mySutherlandTransport<Thermo>&
);

template<class Thermo>
Ostream& operator<<
(
    Ostream&,
    const mySutherlandTransport<Thermo>&
);


/*---------------------------------------------------------------------------*\
                    Class mySutherlandTransport Declaration
\*---------------------------------------------------------------------------*/

template<class Thermo>
class mySutherlandTransport
:
    public Thermo
{
    // Private Data

        // Sutherland's coefficients
        scalar As_, Ts_;

        // Reciprocal Prandtl Number []
        scalar rPr_;


    // Private Member Functions

        //- Calculate the Sutherland coefficients
        //  given two viscosities and temperatures
        inline void calcCoeffs
        (
            const scalar mu1, const scalar T1,
            const scalar mu2, const scalar T2
        );

        //- Read coefficient from dictionary
        scalar readCoeff(const word& coeffName, const dictionary& dict);


public:

    // Constructors

        //- Construct from components
        inline mySutherlandTransport
        (
            const Thermo& t,
            const scalar As,
            const scalar Ts,
            const scalar Pr
        );

        //- Construct from two viscosities
        inline mySutherlandTransport
        (
            const Thermo& t,
            const scalar mu1, const scalar T1,
            const scalar mu2, const scalar T2
        );

        //- Construct as named copy
        inline mySutherlandTransport(const word&, const mySutherlandTransport&);

        //- Construct from dictionary
        mySutherlandTransport(const dictionary& dict);

        //- Construct from base thermo and dictionary
        mySutherlandTransport(const Thermo& t,const dictionary& dict);

        //- Construct and return a clone
        inline autoPtr<mySutherlandTransport> clone() const;

        // Selector from dictionary
        inline static autoPtr<mySutherlandTransport> New(const dictionary& dict);


    // Member Functions

        //- Return the instantiated type name
        static word typeName()
        {
            return "mySutherland<" + Thermo::typeName() + '>';
        }

        //- Dynamic viscosity [kg/m/s]
        inline scalar mu(const scalar p, const scalar T) const;

        //- Thermal conductivity [W/m/K]
        inline scalar kappa(const scalar p, const scalar T) const;

        //- Thermal diffusivity of enthalpy [kg/m/s]
        inline scalar alphah(const scalar p, const scalar T) const;

        // Species diffusivity
        // inline scalar D(const scalar p, const scalar T) const;

        //- Write to Ostream
        void write(Ostream& os) const;


    // Member Operators

        inline void operator+=(const mySutherlandTransport&);
        inline void operator*=(const scalar);


    // Friend operators

        friend mySutherlandTransport operator+ <Thermo>
        (
            const mySutherlandTransport&,
            const mySutherlandTransport&
        );

        friend mySutherlandTransport operator* <Thermo>
        (
            const scalar,
            const mySutherlandTransport&
        );


    // Ostream Operator

        friend Ostream& operator<< <Thermo>
        (
            Ostream&,
            const mySutherlandTransport&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "mySutherlandTransportI.H"

#ifdef NoRepository
    #include "mySutherlandTransport.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
