/******************************************************************************
 * $Id: earth_tidetilt.cxx 2017-11 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Tide tilt implementation.
 * Author:   Weiwei Huang, 898687324@qq.com
 *
 ******************************************************************************
 * Copyright (c) 2017-10 ~ 2017, Weiwei Huang
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

#include "earth_tidetilt.hxx"

/**
 * \brief Constructor.
 */
CEarthTideTilt::CEarthTideTilt()
{
}

/**
 * \brief Destructor.
 */
CEarthTideTilt::~CEarthTideTilt()
{
}

/**
 * \brief Initialize.
 *
 * @return UErrFalse, if successful; UErrTrue, if failed.
 */
UErrCodeT CEarthTideTilt::Init()
{
    return UErrFalse;
}

/**
 * \brief Calculate north south.
 *
 * @return UErrFalse, if successful; UErrTrue, if failed.
 */
UErrCodeT CEarthTideTilt::CalcNs(UFloatT *aNs)
{
    *aNs = 34.68 * (Cr() / Er()) * ((DemA() / DemI()) ^ 3) * Cos();

    return UErrFalse;
}

/**
 * \brief Calculate West east.
 */
UErrCodeT CEarthTideTilt::CalcWe()
{
    return UErrFalse;
}

/***** Private A *****/

/**
 * \brief Centripetal radius.
 */
UFloatT CEarthTideTilt::Cr()
{
    return kEarthRadiusAverage;
}

/**
 * \brief Earth radius.
 */
UFloatT CEarthTideTilt::Er()
{
    return kEarthRadiusAverage;
}

/**
 * \brief Average distance of earth with moon.
 */
UFloatT CEarthTideTilt::DemA()
{
    return kEarthDistanceMoonAverage;
}

/**
 * \brief Instant distance of earth with moon.
 */
UFloatT CEarthTideTilt::DemI()
{
    return kEarthDistanceMoonAverage;
}

/**
 * \brief Distance of earth with sun.
 */
UFloatT CEarthTideTilt::Des()
{
    return mGslAstro->Au();
}

/**
 * \brief Distance of monitor point with sun.
 */
UFloatT CEarthTideTilt::Dps()
{
    return mGslAstro->Au();
}

/**
 * \brief Zenith angle.
 */
UFloatT CEarthTideTilt::Za()
{
    return 0;
}

/**
 * \brief Ecliptic latutide.
 */
UFloatT CEarthTideTilt::El()
{
    return 0;
}

/**
 * \brief Hour angle.
 */
UFloatT CEarthTideTilt::Ha()
{
    return 0;
}

/**
 * \brief Geocentric latitude.
 */
UFloatT CEarthTideTilt::Gl()
{
    return 0;
}

/***** Private B *****/
