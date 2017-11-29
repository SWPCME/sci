/******************************************************************************
 * $Id: atr_ctl.cxx 2017-11 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Atr controler implementation.
 * Author:   Weiwei Huang, 898687324@qq.com
 *
 ******************************************************************************
 * Copyright (c) 2017-11 ~ 2017, Weiwei Huang
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

#include "atr_ctl.hxx"

// atr
#include "earth_ctl.hxx"
// hub::base
#include "base_macrodefn.hpp"

using namespace sci;

/**
 * \brief Constructor.
 */
CAtrCtl::CAtrCtl()
{
    BMD_POINTER_INIT(mEarth);
}

/**
 * \brief Destructor.
 */
CAtrCtl::~CAtrCtl()
{
    BMD_CLASS_DEL(mEarth);
}

/**
 * \brief Initialize.
 */
UErrCodeT CAtrCtl::Init()
{
    return UErrFalse;
}

/**
 * \brief Earth.
 */
CEarthCtl *CAtrCtl::Earth()
{
    BMD_CLASS_NEW(mEarth, CEarthCtl);

    return mEarth;
}
