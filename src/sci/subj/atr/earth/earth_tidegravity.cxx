/******************************************************************************
 * $Id: earth_tidegravity.cxx 2017-10 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Tide gravity implementation.
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

#include "earth_tidegravity.hxx"

// hub
#include "hub_modulectl.hpp"
// cls
#include "cls/cls_ctl.hpp"
#include "cls/cls_mathctl.hpp"
#include "cls/cls_mathexp.hpp"
#include "cls/cls_mathtrig.hpp"

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
CEarthTideGravity::CEarthTideGravity()
{
    BMD_POINTER_INIT(mExp);
    BMD_POINTER_INIT(mTrig);
    BMD_POINTER_INIT(mCoord);
}

/**
 * \brief Destructor.
 */
CEarthTideGravity::~CEarthTideGravity()
{
    BMD_POINTER_INIT(mExp);
    BMD_POINTER_INIT(mTrig);
    BMD_POINTER_INIT(mCoord);
}

/**
 * \brief Initialize.
 *
 * @reutrn UErrFalse, if successful; UErrTrue, if failed.
 */
UErrCodeT CEarthTideGravity::Init()
{
    // hub
    CBaseCtl *baseCtl = CBaseCtl::Base();
    CHubModuleCtl *hubM = baseCtl->HubM();

    // cls
    CClsCtl *clsCtl = (CClsCtl *) hubM->Module(HubMCls);
    CClsMathCtl *mathCtl = clsCtl->Math();
    mExp = mathCtl->Exp();
    mTrig = mathCtl->Trig();

    // earth
    CSubjCtl *subj = baseCtl->Subj();
    CAtrCtl *atr = subj->Atr();
    CEarthCtl *earth = atr->Earth();
    mCoord = earth->Coord();

    return UErrFalse;
}

/**
 * \brief Calculate.
 *
 * @param aG Result.
 * @param aTm Time.
 * @param aS Site.
 * @reutrn UErrFalse, if successful; UErrTrue, if failed.
 */
UErrCodeT CEarthTideGravity::Calc(UFloatT *aG, const BTimeTmT *aTm,
                                  const BGeomCsGdT *aGd, const UFloatT aFactor)
{
    UFloatT gcLat = 0.0;
    mCoord->GcLat(&gcLat, aGd);
    UFloatT gcLatFunc = GcLatFunc(gcLat);
    UFloatT aRIm = 0.0;
    mCoord->AdemRIdem(&aRIm, aTm);
    UFloatT aRIs = 0.0;
    mCoord->AdesRIdes(&aRIs, aTm);
    UFlagCodeT flag = UFlagOn;
    UFloatT zaEm = 0.0;
    mCoord->ZenithAngleEm(&zaEm, aTm, aGd, flag);
    UFloatT zaEs = 0.0;
    mCoord->ZenithAngleEs(&zaEs, aTm, aGd, flag);

    UFloatT aRImP3;
    mExp->Pow(&aRImP3, aRIm, 3);
    UFloatT aRImP4;
    mExp->Pow(&aRImP4, aRIm, 4);

    UFloatT aRIsP3;
    mExp->Pow(&aRIsP3, aRIs, 3);

    UFloatT zaEmCos;
    mTrig->Cos(&zaEmCos, zaEm);
    UFloatT zaEmCosP2;
    mExp->Pow(&zaEmCosP2, zaEmCos, 2);

    UFloatT zaEsCos;
    mTrig->Cos(&zaEsCos, zaEs);
    UFloatT zaEsCosP2;
    mExp->Pow(&zaEsCosP2, zaEsCos, 2);

    UFloatT g1 = gcLatFunc;
    UFloatT gFix[3] = {-165.17, -1.37, -76.08};
    UFloatT g2 = gFix[0] * aRImP3 * (zaEmCosP2 - 1.0 / 3.0);
    UFloatT g3 = gFix[1] * gcLatFunc * aRImP4 * zaEmCos * (5 * zaEmCosP2 - 3);
    UFloatT g4 = gFix[2] * aRIsP3 * (zaEsCosP2 - 1.0 / 3.0);
    *aG = g1 * (g2 + g3 + g4);
    *aG *= aFactor;

    return UErrFalse;
}

/***** Private A *****/

/**
 * \brief Geocentric latitude function.
 */
UFloatT CEarthTideGravity::GcLatFunc(const UFloatT aLat)
{
    UFloatT lat2Cos = 0.0;
    mTrig->Cos(&lat2Cos, 2 * aLat);
    UFloatT gcLatFunc = 0.998327 + 0.001676 * lat2Cos;

    return gcLatFunc;
}

/**
 * \brief Gravity moon.
 */
// UFloatT CEarthTideGravity::Gm()
// {
//     UFloatT gm = 0.0;

//     return gm;
// }

/**
 * \brief Gravity sun.
 */
// UErrCodeT CEarthTideGravity::Gs()
// {
//     UFloatT gs = 0.0;

//     return gs;
// }

/***** Private B *****/
