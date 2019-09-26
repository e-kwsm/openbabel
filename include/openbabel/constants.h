/**********************************************************************
constants.h - Physical Constants
Copyright (C) Copyright (C) 2019 by Eisuke Kawashima

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
***********************************************************************/

//! \file constants.h
//! \brief Physical Constants

#ifndef OB_CONSTANTS_H
#define OB_CONSTANTS_H

namespace OpenBabel {
namespace constants {
const double calorie_to_joule = 4.1868;

inline namespace codata2018 {
//const double atomic_mass_constant = 1.66053906660e-27;  // kg
//const double electron_mass = 9.1093837015e-31;  // kg
const double avogadro_constant = 6.02214076e+23;  // mol^-1
const double bohr_radius = 0.529177210903e-10;  // m
const double elementary_charge = 1.602176634e-19;  // C
const double hartree = 4.3597447222071e-18;  // J
const double molar_gas_constant = 8.314462618153240;  // J mol^-1 K^-1
const double planck_constant = 6.62607015e-34;  // J s^-1
const double speed_of_light = 299792458.0;  // m s^-1

const double bohr_to_angstrom = 0.529177210903;
const double electronvolt_to_kcal_per_mol = elementary_charge * avogadro_constant / calorie_to_joule * 1.0e-3;
const double hartree_to_electronvolt = 27.211386245988;
const double hartree_to_kcal_per_mol = hartree * avogadro_constant / calorie_to_joule * 1.0e-3;
//const double amu_to_au = ;
}  // namespace _2018
}  // namespace constants
}  // namespace OpenBabel

#endif // OB_CONSTANTS_H
