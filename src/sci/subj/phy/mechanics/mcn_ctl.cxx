/******************************************************************************
 * $Id: mcn_ctl.cxx 2017-09 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Mechanics controler implementation.
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

#include "mcn_ctl.hxx"
// base
#include "base_macrodefn.hpp"
// mcn
#include "mcn_gravityctl.hxx"

using namespace sci;

/**
 * \brief Constructor.
 */
CMcnCtl::CMcnCtl()
{
    InitPointer();
}

/**
 * \brief Destructor.
 */
CMcnCtl::~CMcnCtl()
{
    BMD_CLASS_DEL(mGravity);
}

/**
 * \brief Initialize.
 */
UErrCodeT CMcnCtl::Init()
{
    return UErrFalse;
}

/**
 * \brief Gravity
 */
CMcnGravityCtl *CMcnCtl::Gravity()
{
    BMD_CLASS_NEW(mGravity, CMcnGravityCtl);

    return mGravity;
}

/***** Private A *****/

/**
 * \brief Init pointer.
 */
UErrCodeT CMcnCtl::InitPointer()
{
    BMD_POINTER_INIT(mGravity);

    return UErrFalse;
}

/***** Private B *****/
