/******************************************************************************
 * $Id: earth_tidebasic.cxx 2017-10 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Tide basic implementation.
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

#include "earth_tidebasic.hxx"

// hub
#include "hub_modulectl.hpp"
// gsl
#include "gsl/gsl_ctl.hpp"
#include "gsl/gsl_phyctl.hpp"
#include "gsl/gsl_phyconst.hpp"
#include "gsl/gsl_phycastro.hpp"
#include "gsl/gsl_sfctl.hpp"
#include "gsl/gsl_sflegendre.hpp"
#include "gsl/gsl_legendreassoc.hpp"
// cls
#include "cls/cls_ctl.hpp"
#include "cls/cls_mathctl.hpp"
#include "cls/cls_mathexp.hpp"
#include "cls/cls_mathtrig.hpp"
// ust
#include "ust/ust_stringtype.hpp"

// sci::base
#include "base_ctl.hxx"
#include "subj_ctl.hxx"
#include "atr_ctl.hxx"
// sci::earth
#include "earth_ctl.hxx"
#include "earth_coordctl.hxx"

using namespace sci;

/**
 * \brief Constructor.
 */
CEarthTideBasic::CEarthTideBasic()
{
    BMD_POINTER_INIT(mExp);
    BMD_POINTER_INIT(mTrig);
    BMD_POINTER_INIT(mAstro);
    BMD_POINTER_INIT(mAssocSa);
    BMD_POINTER_INIT(mCoord);
}

/**
 * \brief Destructor.
 */
CEarthTideBasic::~CEarthTideBasic()
{
    BMD_POINTER_INIT(mExp);
    BMD_POINTER_INIT(mTrig);
    BMD_POINTER_INIT(mAstro);
    BMD_POINTER_INIT(mAssocSa);
    BMD_POINTER_INIT(mCoord);
}

/**
 * \brief Initialize.
 *
 * @reutrn UErrFalse, if successful; UErrTrue, if failed.
 */
UErrCodeT CEarthTideBasic::Init()
{
    // hub
    CBaseCtl *baseCtl = CBaseCtl::Base();
    CHubModuleCtl *hubM = baseCtl->HubM();

    // cls
    CClsCtl *clsCtl = (CClsCtl *) hubM->Module(HubMCls);
    CClsMathCtl *mathCtl = clsCtl->Math();
    mExp = mathCtl->Exp();
    mTrig = mathCtl->Trig();

    // gsl
    // phy
    CGslCtl *gslCtl = (CGslCtl *) hubM->Module(HubMGsl);
    CGslPhyCtl *phyCtl = gslCtl->Phy();
    CGslPhyConst *phyC = phyCtl->Const();
    mAstro = phyC->Astro();

    // sf
    CGslSfCtl *sfCtl = gslCtl->Sf();
    CGslSfLegendre *sfLegendre = sfCtl->Legendre();
    mAssocSa = sfLegendre->Assoc(GslSfLegendreAssocSpharm);

    // earth
    CSubjCtl *subj = baseCtl->Subj();
    CAtrCtl *atr = subj->Atr();
    CEarthCtl *earth = atr->Earth();
    mCoord = earth->Coord();

    return UErrFalse;
}

/**
 * \brief Tide potential.
 * Calculates combined upward pull of moon/sun, earth tides.
 */
UErrCodeT CEarthTideBasic::Potential(UFloatT *aTp, const BTimeTmT *aTm,
                                     const BGeomCsGdT *aGd)
{
    *aTp = GmL3(aTm, aGd) + GsL2(aTm, aGd);

    return UErrFalse;
}

/**
 * \brief Formula Cnm.
 *
 * @param aO Output.
 * @param aM Mass of host.
 * @param aD Declination.
 * @reutrn UErrFalse, if successful; UErrTrue, if failed.
 */
// UErrCodeT CEarthTideBasic::Cnm(UFloatT *aY, UFloatT *aMess, UFloatT *aD,
//                                UFloatT aH, UIntT aN, UIntT aM)
// {
//     if (aM == 0)
//     {
//         Cn0();
//     }
//     else
//     {
//         2 * Cn0() * mCls->Cos(m * H);
//     }

//     return UErrFalse;
// }

/**
 * \brief Ylm.
 */
// UErrCodeT CEarthTideBasic::Ylm()
// {
//     return UErrFalse;
// }

/***** Private A *****/

/**
 * \brief Gravity for earth tide with moon.
 */
UFloatT CEarthTideBasic::GmL3(const BTimeTmT *aTm, const BGeomCsGdT *aGd)
{
    const UFloatT kG = mAstro->G();
    const UFloatT kMm = kEarthMassMoon;

    UFloatT r = 0.0;
    mCoord->PointH(&r, aGd);
    UFloatT rP2 = 0.0;
    mExp->Pow(&rP2, r, 2);

    UFloatT dEm = 0.0;
    mCoord->DistEm(&dEm, aTm);
    UFloatT rDEm = 1.0 / dEm;
    UFloatT rDEmP3 = 0.0;
    mExp->Pow(&rDEmP3, rDEm, 3);
    UFloatT rDEmP4 = 0.0;
    mExp->Pow(&rDEmP4, rDEm, 4);

    UFlagCodeT flag = UFlagOn;
    UFloatT theata = 0.0;
    mCoord->ZenithAngleEm(&theata, aTm, aGd, flag);
    UFloatT theataCos = 0.0;
    mTrig->Cos(&theataCos, theata);
    UFloatT theataCosP2 = 0.0;
    mExp->Pow(&theataCosP2, theataCos, 2);
    UFloatT theataCosP3 = 0.0;
    mExp->Pow(&theataCosP3, theataCos, 3);


    UFloatT gm1 = kG * kMm * r * rDEmP3;
    UFloatT gm2 = 3 * theataCosP2 - 1;
    UFloatT gm3 = 3.0 / 2.0 * kG * kMm * rP2 *rDEmP4;
    UFloatT gm4 = 5 * theataCosP3 - 3 * theataCos;
    UFloatT gm = gm1 * gm2 + gm3 * gm4;

    return gm;
}

/**
 * \brief Gravity for earth tide with sun.
 */
UFloatT CEarthTideBasic::GsL2(const BTimeTmT *aTm, const BGeomCsGdT *aGd)
{
    const UFloatT kG = mAstro->G();
    const UFloatT kMs = kEarthMassSun;

    UFloatT r = 0.0;
    mCoord->PointH(&r, aGd);
    UFloatT rP2 = 0.0;
    mExp->Pow(&rP2, r, 2);

    UFloatT dEs = 0.0;
    mCoord->DistEs(&dEs, aTm);
    UFloatT rDEs = 1.0 / dEs;
    UFloatT rDEsP3 = 0.0;
    mExp->Pow(&rDEsP3, rDEs, 3);

    UFlagCodeT flag = UFlagOn;
    UFloatT theata = 0.0;
    mCoord->ZenithAngleEs(&theata, aTm, aGd, flag);
    UFloatT theataCos = 0.0;
    mTrig->Cos(&theataCos, theata);
    UFloatT theataCosP2 = 0.0;
    mExp->Pow(&theataCosP2, theataCos, 2);


    UFloatT gm1 = kG * kMs * r * rDEsP3;
    UFloatT gm2 = 3 * theataCosP2 - 1;
    UFloatT gm = gm1 * gm2;

    return gm;
}

/**
 * \brief Assoc legendre.
 *
 * @reutrn UErrFalse, if successful; UErrTrue, if failed.
 */
// UErrCodeT CEarthTideBasic::AssocSa()
// {
//     UIntT lMax = 0;
//     UIntT arrayN = 0;
//     mAssocSa->ArrayN(&arrayN, lMax);
//     UFloatT resultArray[arrayN];
//     mAssocSa->Array(&resultArray, lMax);

//     return UErrFalse;
// }

/**
 * \brief Sum.
 *
 * @reutrn UErrFalse, if successful; UErrTrue, if failed.
 */
// UErrCodeT CEarthTideBasic::SumAS(UFloatT *aNum, const UIntT aBegin,
//                                  const UIntT aEnd)
// {
//     for (int i = aBegin; i <= aEnd; i++)
//     {
//         AssocSa();
//     }

//     return UErrFalse;
// }

/**
 * \brief Cnm;
 */
// UErrCodeT CEarthTideBasic::Cn0()
// {
//     return UErrFalse;
// }

/***** Private B *****/
