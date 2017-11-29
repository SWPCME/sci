/******************************************************************************
 * $Id: earth_tidebasic.hxx 2017-10 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Tide basic definition.
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

#ifndef SCIEARTH_TIDEBASIC_HXX_INCLUDED
#define SCIEARTH_TIDEBASIC_HXX_INCLUDED

#include "earth_base.hxx"

// hub
#include "base_timetype.hpp"
#include "base_geomtype.hpp"

// cls
class CClsMathExp;
class CClsMathTrig;
// gsl
class CGslPhyCAstro;
class CGslLegendreAssoc;

namespace sci
{
    class CEarthCoordCtl;

    class SCIEARTH_LIB CEarthTideBasic
    {
      public:
        CEarthTideBasic();
        ~CEarthTideBasic();

        UErrCodeT Init();
        UErrCodeT Potential(UFloatT *aTp, const BTimeTmT *aTm,
                            const BGeomCsGdT *aGd);

      protected:
      private:
        UFloatT GmL3(const BTimeTmT *aTm, const BGeomCsGdT *aGd);
        UFloatT GsL2(const BTimeTmT *aTm, const BGeomCsGdT *aGd);

        CClsMathExp *mExp;
        CClsMathTrig *mTrig;

        CGslPhyCAstro *mAstro;
        CGslLegendreAssoc *mAssocSa;

        CEarthCoordCtl *mCoord;
    };
}

#endif  // SCIEARTH_TIDEBASIC_HXX_INCLUDED
