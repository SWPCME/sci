/******************************************************************************
 * $Id: earth_ctl.cxx 2017-11 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Earth controler implementation.
 * Author:   Weiwei Huang, 898687324@qq.com
 *
 ******************************************************************************
 * Copyright (c) 2017-09 ~ 2017, Weiwei Huang
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

#include "earth_ctl.hxx"

// hub
#include "base_macrodefn.hpp"
// earth
#include "earth_typectl.hxx"
#include "earth_coordctl.hxx"
#include "earth_timectl.hxx"
#include "earth_tidectl.hxx"

using namespace sci;

/**
 * \brief Constructor.
 */
CEarthCtl::CEarthCtl()
{
    BMD_POINTER_INIT(mType);
    BMD_POINTER_INIT(mCoord);
    BMD_POINTER_INIT(mTime);
    BMD_POINTER_INIT(mTide);
}

/**
 * \brief Destructor.
 */
CEarthCtl::~CEarthCtl()
{
    BMD_CLASS_DEL(mType);
    BMD_CLASS_DEL(mCoord);
    BMD_CLASS_DEL(mTime);
    BMD_CLASS_DEL(mTide);
}

/**
 * \brief Initialize.
 *
 * @return UErrFalse, if successful; UErrTrue, if failed.
 */
UErrCodeT CEarthCtl::Init()
{
  return UErrFalse;
}

/**
 * \brief Type controler.
 *
 * @return Handle of type, if successful; NULL, if failed.
 */
CEarthTypeCtl *CEarthCtl::Type()
{
    BMD_CLASS_NEW(mType, CEarthTypeCtl);

    return mType;
}

/**
 * \brief Coordinate controler.
 *
 * @return Handle of coordinate, if successful; NULL, if failed.
 */
CEarthCoordCtl *CEarthCtl::Coord()
{
    BMD_CLASS_NEW(mCoord, CEarthCoordCtl);

    return mCoord;
}

/**
 * \brief Time.
 */
CEarthTimeCtl *CEarthCtl::Time()
{
    BMD_CLASS_NEW(mTime, CEarthTimeCtl);

    return mTime;
}

/**
 * \brief Tide controler.
 *
 * @return Handle of tide, if successful; NULL, if failed.
 */
CEarthTideCtl *CEarthCtl::Tide()
{
    BMD_CLASS_NEW(mTide, CEarthTideCtl);

    return mTide;
}
