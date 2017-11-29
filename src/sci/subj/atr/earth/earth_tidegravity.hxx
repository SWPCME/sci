/******************************************************************************
 * $Id: earth_tidegravity.hxx 2017-10 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Tide gravity definition.
 * Author:   Weiwei Huang, 898687324@qq.com
 *
 ******************************************************************************
 * Copyright (c) 2017-10, Weiwei Huang
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

#ifndef SCIEARTH_TIDEGRAVITY_HXX_INCLUDED
#define SCIEARTH_TIDEGRAVITY_HXX_INCLUDED

#include "earth_base.hxx"

// hub::base
#include "base_timetype.hpp"
#include "base_geomtype.hpp"

// hub::cls
class CClsMathExp;
class CClsMathTrig;

namespace sci
{
    class CEarthCoordCtl;

    class SCIEARTH_LIB CEarthTideGravity
    {
      public:
        CEarthTideGravity();
        ~CEarthTideGravity();

        UErrCodeT Init();
        UErrCodeT Calc(UFloatT *aG, const BTimeTmT *aTm,
                       const BGeomCsGdT *aGd, const UFloatT aFactor = 1.16);

      protected:
      private:
        UFloatT GcLatFunc(const UFloatT aLat);

        CClsMathExp *mExp;
        CClsMathTrig *mTrig;

        CEarthCoordCtl *mCoord;
    };
}

#endif  // SCIEARTH_TIDEGRAVITY_HXX_INCLUDED
