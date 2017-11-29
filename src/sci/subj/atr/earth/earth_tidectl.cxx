/******************************************************************************
 * $Id: earth_tidectl.hxx 2017-09 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Tide controler implementation.
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

#include "earth_tidectl.hxx"

// hub
#include "base_macrodefn.hpp"

// earth
#include "earth_tidebasic.hxx"
#include "earth_tidegravity.hxx"

using namespace sci;

/**
 * \brief Constructor.
 */
CEarthTideCtl::CEarthTideCtl()
{
    InitPointer();
}

/**
 * \brief Destructor.
 */
CEarthTideCtl::~CEarthTideCtl()
{
    BMD_CLASS_DEL(mGravity);
}

/**
 * \brief Initialize.
 */
UErrCodeT CEarthTideCtl::Init()
{
    return UErrFalse;
}

/**
 * \brief Basic.
 */
CEarthTideBasic *CEarthTideCtl::Basic()
{
    BMD_CLASS_NEW(mBasic, CEarthTideBasic);

    return mBasic;
}

/**
 * \brief Gravity.
 */
CEarthTideGravity *CEarthTideCtl::Gravity()
{
    BMD_CLASS_NEW(mGravity, CEarthTideGravity);

    return mGravity;
}

/**
 * \brief Tilt.
 */
// CEarthTideTilt CEarthTideCtl::Tilt()
// {
//     BMD_CLASS_NEW(mTilt, CEarthTideTilt);

//     return mTilt;
// }

// /**
//  * \brief Linear strain.
//  */
// CEarthTideLs CEarthTideCtl::Strain()
// {
//     BMD_CLASS_NEW(mLs , CEarthTideLs);

//     return mLs;
// }

/***** Private A ******/

/**
 * \brief Initialize pointer.
 *
 * @return UErrFalse, if successful; UErrTrue, if failed.
 */
UErrCodeT CEarthTideCtl::InitPointer()
{
    BMD_POINTER_INIT(mBasic);
    BMD_POINTER_INIT(mGravity);
    // BMD_POINTER_INIT(mTilt);
    // BMD_POINTER_INIT(mLs);

    return UErrFalse;
}

/***** Private B ******/
