/******************************************************************************
 * $Id: earth_base.hxx 2017-09 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Earth controler implementation.
 * Author:   Weiwei Huang, 898687324@qq.com
 *
 ******************************************************************************
 * Copyright (c) 2017-09, Weiwei Huang
 *
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free 
 * Software Foundation, either version 3 of the License, or (at your option) 
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
 * more details.
 *
 * You should have received a copy of the GNU General Public License along 
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#ifndef SCI_EARTH_BASE_HXX_INCLUDED
#define SCI_EARTH_BASE_HXX_INCLUDED

#include "atr_base.hxx"

#define SCIEARTH_LIB SCIATR_LIB

// Unit: kg.
const UFloatT kEarthMassEarth = 5.972E24;
const UFloatT kEarthMassMoon = 7.342E22;
const UFloatT kEarthMassSun = 1.989E30;

// Unit: meter
const UFloatT kEarthRadiusEquatorial = 6378137.0;
const UFloatT kEarthRadiusPolar = 6356752.3;
const UFloatT kEarthRadiusAverage = 6371230.0;
const UFloatT kEarthDistanceMoonAverage = 3.84402E8;
const UFloatT kEarthDistanceSunAverage = 149597870700;

#endif  // SCI_EARTH_BASE_HXX_INCLUDED
