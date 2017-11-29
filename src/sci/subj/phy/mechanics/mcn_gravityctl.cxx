/******************************************************************************
 * $Id: mcn_gravityctl.cxx 2017-09 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Gravity controler implementation.
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

#include "mcn_gravityctl.hxx"

using namespace sci;

/**
 * \brief Constructor.
 */
CMcnGravityCtl::CMcnGravityCtl()
{
}

/**
 * \brief Destructor.
 */
CMcnGravityCtl::~CMcnGravityCtl()
{
}

/**
 * \brief Initialize.
 */
UErrCodeT CMcnGravityCtl::Init()
{
    return UErrFalse;
}

/**
 * \brief Newton's law of universal gravitation.
 *
 * @param aF The force between the masses.
 * @param aM1 The first mass.
 * @param aM2 The second mass.
 * @param aR The distance between the centers of the masses.
 *
 * @return UErrFalse, if successful; UErrTrue, if failed.
 */
UErrCodeT CMcnGravityCtl::NlUniG(UFloatT *aF, const UFloatT aM1,
                                 const UFloatT aM2, const UFloatT aR)
{
    // *aF = kPhyMcnGravitationalConstant * (aM1 * aM2) / (aR * aR);

    return UErrFalse;
}
