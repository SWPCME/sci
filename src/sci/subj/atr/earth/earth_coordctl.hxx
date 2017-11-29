/******************************************************************************
 * $Id: earth_coordctl.hxx 2017-11 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Coordinate controler definition.
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

#ifndef SCIEARTH_COORDCTL_HXX_INCLUDED
#define SCIEARTH_COORDCTL_HXX_INCLUDED

#include "earth_base.hxx"

// base
#include "base_timetype.hpp"
#include "base_geomtype.hpp"

// hub::cls
class CClsMathConst;
class CClsMathType;
class CClsArithRound;
class CClsMathExp;
class CClsMathTrig;
class CClsMathITrig;

namespace sci
{
    // sci::earth
    class CEarthTimeCtl;

    class SCIEARTH_LIB CEarthCoordCtl
    {
      public:
        CEarthCoordCtl();
        ~CEarthCoordCtl();

        UErrCodeT Init();

        UErrCodeT GcLat(UFloatT *aGcLat, const BGeomCsGdT *aGd);
        UErrCodeT AdemRIdem(UFloatT *aRatio, const BTimeTmT *aTm);
        UErrCodeT AdesRIdes(UFloatT *aRatio, const BTimeTmT *aTm);

        UErrCodeT DistEm(UFloatT *aDist, const BTimeTmT *aTm);
        UErrCodeT DistEs(UFloatT *aDist, const BTimeTmT *aTm);

        UErrCodeT PointH(UFloatT *aR, const BGeomCsGdT *aGd);

        UFloatT MeanLonM(const BTimeTmT *aTm);
        UFloatT MeanLonS(const BTimeTmT *aTm);
        UFloatT MeanLonMp(const BTimeTmT *aTm);
        UFloatT MeanLonSp(const BTimeTmT *aTm);
        UFloatT MeanLonMan(const BTimeTmT *aTm);
        UFloatT AEclipticEquator(const BTimeTmT *aTm);

        UErrCodeT CelestialCsM(BGeomCsGdT *aGd, const BTimeTmT *aTm);
        UErrCodeT CelestialCsS(BGeomCsGdT *aGd, const BTimeTmT *aTm);

        UErrCodeT EquatorialCsM(BGeomCsGdT *aGd, const BTimeTmT *aTm);

        UErrCodeT HourAngleM(UFloatT *aHa, const BTimeTmT *aTm,
                             const BGeomCsGdT *aGd);

        UErrCodeT SiderealTimeM(UFloatT *aSt, const BTimeTmT *aTm,
                                const BGeomCsGdT *aGd);


        UErrCodeT ZenithAngleEm(UFloatT *aAngle, const BTimeTmT *aTm,
                                const BGeomCsGdT *aGd,
                                const UFlagCodeT aFlag = UFlagOff);
        UErrCodeT ZenithAngleEs(UFloatT *aAngle, const BTimeTmT *aTm,
                                const BGeomCsGdT *aGd,
                                const UFlagCodeT aFlag = UFlagOff);

      protected:
      private:
        UFloatT AcTideEmE();
        UFloatT AcTideEsE(const BTimeTmT *aTm);
        UFloatT AcTideEmI();
        UFloatT AcTideEmM();

        UErrCodeT ZenithAngle(UFloatT *aAngle, const BTimeTmT *aTm,
                              const BGeomCsGdT *aGd, const UFloatT aPsi,
                              const UFloatT aOmega, const UFloatT aKsi);

        UFloatT PZaEsOmega();
        UFloatT PZaEmOmega(const BTimeTmT *aTm);
        UFloatT PZaEmEta(const BTimeTmT *aTm);
        UFloatT PZaEmKsi(const BTimeTmT *aTm, const BGeomCsGdT *aGd);
        UFloatT PZaEsKsi(const BTimeTmT *aTm, const BGeomCsGdT *aGd);
        UFloatT PZaEmPsi(const BTimeTmT *aTm);
        UFloatT PZaEsPsi(const BTimeTmT *aTm);

        // cls
        CClsMathConst *mMathConst;
        CClsMathType *mMathType;
        CClsArithRound *mArithRound;
        CClsMathExp *mExp;
        CClsMathTrig *mTrig;
        CClsMathITrig *mITrig;

        CEarthTimeCtl *mEarthTime;
    };
}

#endif  // SCIEARTH_COORDCTL_HXX_INCLUDED
