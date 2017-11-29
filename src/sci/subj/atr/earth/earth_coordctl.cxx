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

#include "earth_coordctl.hxx"

using namespace sci;

// hub
#include "hub_modulectl.hpp"
// hub::cls
#include "cls/cls_ctl.hpp"
#include "cls/cls_mathctl.hpp"
#include "cls/cls_mathconst.hpp"
#include "cls/cls_mathtype.hpp"
#include "cls/cls_matharith.hpp"
#include "cls/cls_arithround.hpp"
#include "cls/cls_mathexp.hpp"
#include "cls/cls_mathtrig.hpp"
#include "cls/cls_mathitrig.hpp"

// sci::base
#include "base_ctl.hxx"
#include "subj_ctl.hxx"
#include "atr_ctl.hxx"
// sci::earth
#include "earth_ctl.hxx"
#include "earth_timectl.hxx"

// #define SWPCME_TEST

/**
 * \brief Constructor.
 */
CEarthCoordCtl::CEarthCoordCtl()
{
    // math
    BMD_POINTER_INIT(mMathConst);
    BMD_POINTER_INIT(mMathType);
    BMD_POINTER_INIT(mArithRound);
    BMD_POINTER_INIT(mExp);
    BMD_POINTER_INIT(mTrig);
    BMD_POINTER_INIT(mITrig);
    // earth
    BMD_POINTER_INIT(mEarthTime);
}

/**
 * \brief Destructor.
 */
CEarthCoordCtl::~CEarthCoordCtl()
{
}

/**
 * \brief Initialize.
 *
 * @return UErrFalse, if successful; UErrTrue, if failed.
 */
UErrCodeT CEarthCoordCtl::Init()
{
    CBaseCtl *base = CBaseCtl::Base();
    CHubModuleCtl *hubM = base->HubM();

    CClsCtl *clsCtl = (CClsCtl *) hubM->Module(HubMCls);
    CClsMathCtl *mathCtl = clsCtl->Math();
    mMathConst = mathCtl->Const();
    mMathType = mathCtl->Type();
    CClsMathArith *mathArith = mathCtl->Arith();
    mArithRound = mathArith->Round();
    mExp = mathCtl->Exp();
    mTrig = mathCtl->Trig();
    mITrig = mathCtl->ITrig();

    CSubjCtl *subj = base->Subj();
    CAtrCtl *atr = subj->Atr();
    CEarthCtl *earth = atr->Earth();
    mEarthTime = earth->Time();

    return UErrFalse;
}

/**
 * \brief Geocentric latitude.
 * Unit: radian.
 */
UErrCodeT CEarthCoordCtl::GcLat(UFloatT *aGcLat, const BGeomCsGdT *aGd)
{
    UFloatT e = 1.0 / 298.256;
    UFloatT s1SeP2;
    mExp->Pow(&s1SeP2, 1 - e, 2);

    UFloatT lat = 0.0;
    mMathType->DegToRad(&lat, aGd->lat);
    UFloatT latTan = 0.0;
    mTrig->Tan(&latTan, lat);

    mITrig->ATan(aGcLat, s1SeP2 *latTan);

    return UErrFalse;
}

/**
 * \brief Average distance of earth and moon ratio with 
 *        instance distance of earth and moon, adem : idem.
 */
UErrCodeT CEarthCoordCtl::AdemRIdem(UFloatT *aRatio, const BTimeTmT *aTm)
{
    UFloatT s = MeanLonM(aTm);
    UFloatT mp = MeanLonMp(aTm);
    UFloatT h = MeanLonS(aTm);
    UFloatT sp = MeanLonSp(aTm);

    UFloatT r1 = 1.0;

    UFloatT sSpCos = 0.0;
    mTrig->Cos(&sSpCos, s - mp);
    UFloatT r2 = 0.0545 * sSpCos;

    UFloatT sSpM2Cos = 0.0;
    mTrig->Cos(&sSpM2Cos, (s - mp) * 2.0);
    UFloatT r3 = 0.003 * sSpM2Cos;

    UFloatT sS2hApcos = 0.0;
    mTrig->Cos(&sS2hApcos, s - 2 * h +mp);
    UFloatT r4 = 0.01 * sS2hApcos;

    UFloatT sShM2Cos = 0.0;
    mTrig->Cos(&sShM2Cos, (s - h) * 2.0);
    UFloatT r5 = 0.0082 * sShM2Cos;

    UFloatT s2Mh3AspCos = 0.0;
    mTrig->Cos(&s2Mh3AspCos, (2 * s - 3 * h + sp));
    UFloatT r6 = 0.0006 * s2Mh3AspCos;

    UFloatT s3Mh2MmpCos = 0.0;
    mTrig->Cos(&s3Mh2MmpCos, 3 * s - 2 * h - mp);
    UFloatT r7 = 0.0009 * s3Mh2MmpCos;

    *aRatio = r1 + r2 + r3 + r4 + r5 + r6 + r7;

    return UErrFalse;
}

/**
 * \brief Average distance of earth and sun ratio with 
 *        instance distance of earth and sun, ades : ides.
 */
UErrCodeT CEarthCoordCtl::AdesRIdes(UFloatT *aRatio, const BTimeTmT *aTm)
{
    UFloatT h = MeanLonS(aTm);
    UFloatT p = MeanLonSp(aTm);

    UFloatT r1 = 1.0;

    UFloatT hSpCos = 0.0;
    mTrig->Cos(&hSpCos, h - p);
    UFloatT r2 = 0.0168 * hSpCos;

    UFloatT hSpM2Cos = 0.0;
    mTrig->Cos(&hSpM2Cos, 2 * (h - p));
    UFloatT r3 = 0.0003 * hSpM2Cos;

    *aRatio = r1 + r2 + r3;

    return UErrFalse;
}

/**
 * \brief Calculate the distance of earth with moon.
 */
UErrCodeT CEarthCoordCtl::DistEm(UFloatT *aDist, const BTimeTmT *aTm)
{
    UFloatT e = AcTideEmE();
    UFloatT s = MeanLonM(aTm);
    UFloatT p = MeanLonMp(aTm);
    UFloatT h = MeanLonS(aTm);
    UFloatT c = kEarthDistanceMoonAverage;
    UFloatT m = AcTideEmM();

    UFloatT eP2 = 0.0;
    mExp->Pow(&eP2, e, 2);
    UFloatT e2 = c * (1 - eP2);

    UFloatT a1 = 1 - eP2;

    UFloatT spCos = 0.0;
    mTrig->Cos(&spCos, s - p);
    UFloatT a2 = e * spCos;

    UFloatT s2spCos = 0.0;
    mTrig->Cos(&s2spCos, 2 * (s - p));
    UFloatT a3 = eP2 * s2spCos;

    UFloatT s2hpCos = 0.0;
    mTrig->Cos(&s2hpCos, s - 2 * h + p);
    UFloatT a4 = (15.0 / 8.0) * m * e * s2hpCos;

    UFloatT s2shCos = 0.0;
    mTrig->Cos(&s2shCos, 2 * (s - h));
    UFloatT mP2 = 0.0;
    mExp->Pow(&mP2, m, 2);
    UFloatT a5 = mP2 * s2shCos;

    *aDist = e2 / (a1 + a2 + a3 + a4 + a5);

    return UErrFalse;
}

/**
 * \brief Calculate the distance of earth and sun.
 */
UErrCodeT CEarthCoordCtl::DistEs(UFloatT *aDist, const BTimeTmT *aTm)
{
    UFloatT e = AcTideEsE(aTm);
    UFloatT h = MeanLonS(aTm);
    UFloatT p = MeanLonSp(aTm);
    UFloatT c = kEarthDistanceSunAverage;

    UFloatT hpCos = 0.0;
    mTrig->Cos(&hpCos, h - p);
    UFloatT eP2 = 0.0;
    mExp->Pow(&eP2, e, 2);
    *aDist = c / (1 + (e / (1 - eP2)) * hpCos);

    return UErrFalse;
}

/**
 * \brief Calculate the point with height above the sea level on the earth 
 *        in spherical coordinate system.
 */
UErrCodeT CEarthCoordCtl::PointH(UFloatT *aR, const BGeomCsGdT *aGd)
{
    const UFloatT kRe = kEarthRadiusAverage;

    UFloatT lat = 0.0;
    mMathType->DegToRad(&lat, aGd->lat);
    UFloatT latSin = 0.0;
    mTrig->Sin(&latSin, lat);
    UFloatT latSinP2 = 0.0;
    mExp->Pow(&latSinP2, latSin, 2);
    UFloatT latSqrt = 0.0;
    mExp->Sqrt(&latSqrt, 1 + 0.006738 * latSinP2);
    *aR = kRe / latSqrt + aGd->h * 100;

    return UErrFalse;
}

/**
 * \brief Calculate the mean longitude of moon.
 */
UFloatT CEarthCoordCtl::MeanLonM(const BTimeTmT *aTm)
{
    UFloatT t = mEarthTime->Jct(aTm);
    UFloatT tP2 = 0.0;
    mExp->Pow(&tP2, t, 2);
    UFloatT tP3 = 0.0;
    mExp->Pow(&tP3, t, 3);

    UFloatT m = 4.720023438  + 8399.7093 * t + 4.40695E-5 * tP2
                + 3.29E-8  * tP3;
#ifdef SWPCME_TEST
    UFloatT angle = 270.43659 + 481267.89057 * t + 0.00198 * tP2
                    + 0.000002 * tP3;
    mMathType->DegToRad(&m, angle);
#endif  // SWPCME_TEST

    return m;
}

/**
 * \brief Calculate the mean longitude of sun.
 */
UFloatT CEarthCoordCtl::MeanLonS(const BTimeTmT *aTm)
{
    UFloatT t = mEarthTime->Jct(aTm);
    UFloatT tP2 = 0.0;
    mExp->Pow(&tP2, t, 2);

    UFloatT s = 4.881627934 + 628.33195 * t + 5.2796E-6  * tP2;

#ifdef SWPCME_TEST
    UFloatT angle = 279.69668 + 36000.76892 * t + 0.0003 * tP2;
    mMathType->DegToRad(&s, angle);
#endif  // SWPCME_TEST

    return s;
}

/**
 * \brief Calculate the mean longitude of moon perigee.
 */
UFloatT CEarthCoordCtl::MeanLonMp(const BTimeTmT *aTm)
{
    UFloatT t = mEarthTime->Jct(aTm);
    UFloatT tP2 = 0.0;
    mExp->Pow(&tP2, t, 2);
    UFloatT tP3 = 0.0;
    mExp->Pow(&tP3, t, 3);

    UFloatT mp = 5.835124721 + 71.018009 * t - 1.80546E-4 * tP2
                 - 2.181E-7 * tP3;

#ifdef SWPCME_TEST
    UFloatT angle = 334.32956 + 4069.03403 * t -0.01032 * tP2 -0.00001 * tP3;
    mMathType->DegToRad(&mp, angle);
#endif  // SWPCME_TEST

    return mp;
}

/**
 * \brief Calculate the mean longitude of sun perigee.
 */
UFloatT CEarthCoordCtl::MeanLonSp(const BTimeTmT *aTm)
{
    UFloatT t = mEarthTime->Jct(aTm);
    UFloatT tP2 = 0.0;
    mExp->Pow(&tP2, t, 2);
    UFloatT tP3 = 0.0;
    mExp->Pow(&tP3, t, 3);

    UFloatT sp = 4.908229467 + 3.0005264E-2 * t + 7.9024E-6  * tP2
                 + 5.81E-8  * tP3;

#ifdef SWPCME_TEST
    UFloatT angle = 281.22083 + 1.71902 * t + 0.00045 * tP2 + 0.000003 * tP3;
    mMathType->DegToRad(&sp, angle);
#endif  // SWPCME_TEST

    return sp;
}

/**
 * \brief Calculate the mean longitude of moon ascending node.
 */
UFloatT CEarthCoordCtl::MeanLonMan(const BTimeTmT *aTm)
{
    UFloatT t = mEarthTime->Jct(aTm);
    UFloatT tP2 = 0.0;
    mExp->Pow(&tP2, t, 2);
    UFloatT tP3 = 0.0;
    mExp->Pow(&tP3, t, 3);

    UFloatT man = 4.523588570 - 33.757153 * t + 3.67488E-5 * tP2
            + 3.87E-8 * tP3;

#ifdef SWPCME_TEST
    UFloatT angle = 259.18328 - 1934.14201 * t + 0.00208 * tP2 + 0.000002 * tP3;
    mMathType->DegToRad(&man, angle);
#endif  // SWPCME_TEST

    return man;
}

/**
 * \brief Angle with ecliptic and equator.
 * Formual: angle = 23.45229 - 0.01301 * t - 0.000002 * t ^ 2.
 */
UFloatT CEarthCoordCtl::AEclipticEquator(const BTimeTmT *aTm)
{
    UFloatT t = mEarthTime->Jct(aTm);
    UFloatT tP2 = 0.0;
    mExp->Pow(&tP2, t, 2);

    UFloatT radian = 0.4093196775 - 0.0002270673 * t - 0.0000000349 * tP2;

#ifdef SWPCME_TEST
    UFloatT angle = 23.45229 - 0.01301 * t - 0.000002 * tP2;
    mMathType->DegToRad(&radian, angle);
#endif  // SWPCME_TEST

    return radian;
}

/**
 * \brief Celestial coordinate system for moon.
 */
UErrCodeT CEarthCoordCtl::CelestialCsM(BGeomCsGdT *aGd, const BTimeTmT *aTm)
{
    UFloatT s = MeanLonM(aTm);
    UFloatT mp = MeanLonMp(aTm);
    UFloatT h = MeanLonS(aTm);
    UFloatT sp = MeanLonSp(aTm);
    UFloatT man = MeanLonMan(aTm);

    // For longitude.
    UFloatT lon1 = s;

    UFloatT hSspSin = 0.0;
    mTrig->Sin(&hSspSin, h - sp);
    UFloatT lon2 = (-0.0032) * hSspSin;

    UFloatT hSmpM2Sin = 0.0;
    mTrig->Sin(&hSmpM2Sin, (h - mp) * 2);
    UFloatT lon3 = (-0.001) * hSmpM2Sin;

    UFloatT sS3hAmpAspSin = 0.0;
    mTrig->Sin(&sS3hAmpAspSin, s - 3 * h + mp + sp);
    UFloatT lon4 = 0.001 * sS3hAmpAspSin;

    UFloatT sS2hAmpSin = 0.0;
    mTrig->Sin(&sS2hAmpSin, s - 2 * h + mp);
    UFloatT lon5 = 0.0222 * sS2hAmpSin;

    UFloatT sShSmpSspSin = 0.0;
    mTrig->Sin(&sShSmpSspSin, s - h - mp - sp);
    UFloatT lon6 = 0.0007 * sShSmpSspSin;

    UFloatT sShSin = 0.0;
    mTrig->Sin(&sShSin, s - h);
    UFloatT lon7 = (-0.0006) * sShSin;

    UFloatT sSmpSin = 0.0;
    mTrig->Sin(&sSmpSin, s - mp);
    UFloatT lon8 = 0.1098 * sSmpSin;

    UFloatT sAhSmpSspSin = 0.0;
    mTrig->Sin(&sAhSmpSspSin, s + h - mp - sp);
    UFloatT lon9 = (-0.0005) * sAhSmpSspSin;

    UFloatT s2Sh3AspSin = 0.0;
    mTrig->Sin(&s2Sh3AspSin, s * 2 - h * 3 + sp);
    UFloatT lon10 = 0.0008 * s2Sh3AspSin;

    UFloatT sShM2Sin = 0.0;
    mTrig->Sin(&sShM2Sin, (s - h) * 2.0);
    UFloatT lon11 = 0.0115 * sShM2Sin;

    UFloatT sSmpM2Sin = 0.0;
    mTrig->Sin(&sSmpM2Sin, (s - mp) * 2.0);
    UFloatT lon12 = 0.0037 * sSmpM2Sin;

    UFloatT sSmanM2Sin = 0.0;
    mTrig->Sin(&sSmanM2Sin, (s - man) * 2.0);
    UFloatT lon13 = (-0.002) * sSmanM2Sin;

    UFloatT s3Sh2SmpSin = 0.0;
    mTrig->Sin(&s3Sh2SmpSin, s * 3 - h * 2 - mp);
    UFloatT lon14 = 0.0009 * s3Sh2SmpSin;

    aGd->lon = lon1 + lon2 + lon3 + lon4 + lon5 + lon6 + lon7 + lon8 + lon9
        + lon10 + lon11 + lon12 + lon13 + lon14;

    // For latitude.
    UFloatT mpSmanSin = 0.0;
    mTrig->Sin(&mpSmanSin, mp - man);
    UFloatT lat1 = (-0.0048) * mpSmanSin;

    UFloatT h2SmpSmanSin = 0.0;
    mTrig->Sin(&h2SmpSmanSin, h * 2 - mp - man);
    UFloatT lat2 = (-0.0008) * h2SmpSmanSin;

    UFloatT sSh2AmanSin = 0.0;
    mTrig->Sin(&sSh2AmanSin, s - h * 2.0 + man);
    UFloatT lat3 = 0.0003 * sSh2AmanSin;

    UFloatT sSmanSin = 0.0;
    mTrig->Sin(&sSmanSin, s - man);
    UFloatT lat4 = 0.0895 * sSmanSin;

    UFloatT s2Sh2AmpSmanSin = 0.0;
    mTrig->Sin(&s2Sh2AmpSmanSin, s * 2 - h * 2 + mp - man);
    UFloatT lat5 = 0.0010 * s2Sh2AmpSmanSin;

    UFloatT s2SmpSmanSin = 0.0;
    mTrig->Sin(&s2SmpSmanSin, s * 2 - mp - man);
    UFloatT lat6 = 0.0049 * s2SmpSmanSin;

    UFloatT s3Sh2SmanSin = 0.0;
    mTrig->Sin(&s3Sh2SmanSin, s * 3 - h * 2 - man);
    UFloatT lat7 = 0.0006 * s3Sh2SmanSin;

    aGd->lat = lat1 + lat2 + lat3 + lat4 + lat5 + lat6 + lat7;

    return UErrFalse;
}

/**
 * \brief Celestial coordinate system for sun.
 */
UErrCodeT CEarthCoordCtl::CelestialCsS(BGeomCsGdT *aGd, const BTimeTmT *aTm)
{
    UFloatT h = MeanLonS(aTm);
    UFloatT sp = MeanLonSp(aTm);

    // For longitude.
    UFloatT lon1 = h;

    UFloatT hSspSin = 0.0;
    mTrig->Sin(&hSspSin, h - sp);
    UFloatT lon2 = 0.0335 * hSspSin;

    UFloatT hSspM2Sin = 0.0;
    mTrig->Sin(&hSspM2Sin, (h - sp) * 2);
    UFloatT lon3 = 0.0004 * hSspM2Sin;

    aGd->lon = lon1 + lon2 + lon3;

    // For latitude.
    aGd->lat = 0.0;

    return UErrFalse;
}

/**
 * \brief Equatorial coordinate system for moon.
 */
UErrCodeT CEarthCoordCtl::EquatorialCsM(BGeomCsGdT *aGd, const BTimeTmT *aTm)
{
    // For latitude.
    UFloatT eta = AEclipticEquator(aTm);
    BGeomCsGdT gd;
    CelestialCsM(&gd, aTm);
    UFloatT lambda = gd.lon;
    UFloatT beta = gd.lat;

    UFloatT etaSin = 0.0;
    mTrig->Sin(&etaSin, eta);
    UFloatT etaCos = 0.0;
    mTrig->Cos(&etaCos, eta);

    UFloatT lambdaSin = 0.0;
    mTrig->Sin(&lambdaSin, lambda);

    UFloatT betaSin = 0.0;
    mTrig->Sin(&betaSin, beta);
    UFloatT betaCos = 0.0;
    mTrig->Cos(&betaCos, beta);

    UFloatT latSin = etaSin * betaCos * lambdaSin + etaCos * betaSin;
    mITrig->ASin(&(aGd->lat), latSin);

    // For longitude.

    return UErrFalse;
}

/**
 * \brief Hour angle for moon.
 */
UErrCodeT CEarthCoordCtl::HourAngleM(UFloatT *aHa, const BTimeTmT *aTm,
                                     const BGeomCsGdT *aGd)
{
    UFloatT eta = AEclipticEquator(aTm);

    BGeomCsGdT cGd;
    CelestialCsM(&cGd, aTm);
    UFloatT lambda = cGd.lon;
    UFloatT beta = cGd.lat;

    UFloatT theta = 0.0;
    SiderealTimeM(&theta, aTm, aGd);

    BGeomCsGdT eGd;
    EquatorialCsM(&eGd, aTm);
    UFloatT delta = eGd.lat;

    UFloatT etaSin = 0.0;
    mTrig->Sin(&etaSin, eta);
    UFloatT etaCos = 0.0;
    mTrig->Cos(&etaCos, eta);

    UFloatT lambdaSin = 0.0;
    mTrig->Sin(&lambdaSin, lambda);
    UFloatT lambdaCos = 0.0;
    mTrig->Cos(&lambdaCos, lambda);

    UFloatT betaSin = 0.0;
    mTrig->Sin(&betaSin, beta);
    UFloatT betaCos = 0.0;
    mTrig->Cos(&betaCos, beta);

    UFloatT thetaSin = 0.0;
    mTrig->Sin(&thetaSin, theta);
    UFloatT thetaCos = 0.0;
    mTrig->Cos(&thetaCos, theta);

    UFloatT deltaCos = 0.0;
    mTrig->Cos(&deltaCos, delta);

    UFloatT h1 = betaCos * lambdaCos * thetaCos;
    UFloatT h2 = thetaSin * (etaCos * betaCos * lambdaSin - etaSin * betaSin);
    UFloatT h3 = deltaCos;
    UFloatT haCos = (h1 + h2) / h3;
    mITrig->ACos(aHa, haCos);

    return UErrFalse;
}

/**
 * \brief Sidereal time for moon.
 * Unit: radian.
 */
UErrCodeT CEarthCoordCtl::SiderealTimeM(UFloatT *aSt, const BTimeTmT *aTm,
                                        const BGeomCsGdT *aGd)
{
    UFloatT h = MeanLonS(aTm);
    UFloatT angle = aTm->hour * 15 + h + aGd->lon - 180;
    mMathType->DegToRad(aSt, angle);

    return UErrFalse;
}

/**
 * \brief Zenith angle with earth and moon.
 */
UErrCodeT CEarthCoordCtl::ZenithAngleEm(UFloatT *aAngle, const BTimeTmT *aTm,
                                        const BGeomCsGdT *aGd,
                                        const UFlagCodeT aFlag)
{
    if (aFlag == UFlagOn)
    {
        UFloatT psi = PZaEmPsi(aTm);
        UFloatT omega = PZaEmOmega(aTm);
        UFloatT ksi = PZaEmKsi(aTm, aGd);
        ZenithAngle(aAngle, aTm, aGd, psi, omega, ksi);

        return UErrFalse;
    }

    UFloatT phi = 0.0;
    GcLat(&phi, aGd);

    BGeomCsGdT eGd;
    EquatorialCsM(&eGd, aTm);
    UFloatT delta = eGd.lat;

    UFloatT eta = 0.0;
    HourAngleM(&eta, aTm, aGd);

    UFloatT phiSin = 0.0;
    mTrig->Sin(&phiSin, phi);
    UFloatT phiCos = 0.0;
    mTrig->Cos(&phiCos, phi);

    UFloatT deltaSin = 0.0;
    mTrig->Sin(&deltaSin, delta);
    UFloatT deltaCos = 0.0;
    mTrig->Cos(&deltaCos, delta);

    UFloatT etaCos = 0.0;
    mTrig->Cos(&etaCos, eta);

    UFloatT cosA = phiSin * deltaSin + phiCos *deltaCos * etaCos;
    mITrig->ACos(aAngle, cosA);

    return UErrFalse;
}

/**
 * \brief Zenith angle with earth and sun.
 */
UErrCodeT CEarthCoordCtl::ZenithAngleEs(UFloatT *aAngle, const BTimeTmT *aTm,
                                        const BGeomCsGdT *aGd,
                                        const UFlagCodeT aFlag)
{
    if (aFlag == UFlagOn)
    {
        UFloatT psi = PZaEsPsi(aTm);
        UFloatT omega = PZaEsOmega();
        UFloatT ksi = PZaEsKsi(aTm, aGd);
        ZenithAngle(aAngle, aTm, aGd, psi, omega, ksi);

        return UErrFalse;
    }

    UFloatT phi = 0.0;
    GcLat(&phi, aGd);

    BGeomCsGdT cGd;
    CelestialCsS(&cGd, aTm);
    UFloatT lambda = cGd.lon;

    UFloatT eta = AEclipticEquator(aTm);;

    UFloatT theta = 0.0;
    SiderealTimeM(&theta, aTm, aGd);

    UFloatT phiSin = 0.0;
    mTrig->Sin(&phiSin, phi);
    UFloatT phiCos = 0.0;
    mTrig->Cos(&phiCos, phi);

    UFloatT lambdaSin = 0.0;
    mTrig->Sin(&lambdaSin, lambda);
    UFloatT lambdaCos = 0.0;
    mTrig->Cos(&lambdaCos, lambda);

    UFloatT etaSin = 0.0;
    mTrig->Sin(&etaSin, eta);
    UFloatT etaCos = 0.0;
    mTrig->Cos(&etaCos, eta);

    UFloatT thetaSin = 0.0;
    mTrig->Sin(&thetaSin, theta);
    UFloatT thetaCos = 0.0;
    mTrig->Cos(&thetaCos, theta);

    UFloatT cosA1 = phiSin * etaSin * lambdaSin;
    UFloatT cosA2 = phiCos;
    UFloatT cosA3 = lambdaCos * thetaCos + lambdaSin * thetaSin * etaCos;
    UFloatT cosA = cosA1 + cosA2 * cosA3;
    mITrig->ACos(aAngle, cosA);

    return UErrFalse;
}

/***** Private A *****/

/**
 * \brief Argument correct for tide with earth and moon, e.
 *
 * Warnning: equivocal, how to calculate this num.
 */
UFloatT CEarthCoordCtl::AcTideEmE()
{
    UFloatT e = 0.054899720;

    return e;
}

/**
 * \brief Argument correct for tide with earth and sun, e.
 *
 * Warnning: equivocal, how to calculate this num.
 */
UFloatT CEarthCoordCtl::AcTideEsE(const BTimeTmT *aTm)
{
    UFloatT t = mEarthTime->Jct(aTm);
    UFloatT tP2 = 0.0;
    mExp->Pow(&tP2, t, 2);
    UFloatT e = 0.01675104 - 4.18E-5 * t - 1.26E-7 * tP2;

    return e;
}

/**
 * \brief Argument correct for tide with earth and moon, i.
 */
UFloatT CEarthCoordCtl::AcTideEmI()
{
    UFloatT i = 0.08979719;

    return i;
}

/**
 * \brief Argument correct for tide with earth and moon, m.
 */
UFloatT CEarthCoordCtl::AcTideEmM()
{
    UFloatT m = 0.074804;

    return m;
}

/**
 * \brief Zenith angle with earth-sun or earth-moon.
 */
UErrCodeT CEarthCoordCtl::ZenithAngle(UFloatT *aAngle, const BTimeTmT *aTm,
                                      const BGeomCsGdT *aGd,
                                      const UFloatT aPsi,
                                      const UFloatT aOmega,
                                      const UFloatT aKsi)
{
    UFloatT lat = 0.0;
    mMathType->DegToRad(&lat, aGd->lat);
    UFloatT latSin = 0.0;
    mTrig->Sin(&latSin, lat);
    UFloatT latCos = 0.0;
    mTrig->Cos(&latCos, lat);

    UFloatT psiSin = 0.0;
    mTrig->Sin(&psiSin, aPsi);

    UFloatT omegaSin = 0.0;
    mTrig->Sin(&omegaSin, aOmega);

    UFloatT cosA1 = latSin * omegaSin * psiSin;

    UFloatT cosA21 = latCos;

    UFloatT omegaD2Cos = 0.0;
    mTrig->Cos(&omegaD2Cos, aOmega / 2);
    UFloatT omegaD2CosP2 = 0.0;
    mExp->Pow(&omegaD2CosP2, omegaD2Cos, 2);

    UFloatT psiKsiCos = 0.0;
    mTrig->Cos(&psiKsiCos, aPsi - aKsi);
    UFloatT cosA22 = omegaD2CosP2 * psiKsiCos;

    UFloatT omegaD2Sin = 0.0;
    mTrig->Sin(&omegaD2Sin, aOmega / 2);
    UFloatT omegaD2SinP2 = 0.0;
    mExp->Pow(&omegaD2SinP2, omegaD2Sin, 2);

    UFloatT psiAKsiCos;
    mTrig->Cos(&psiAKsiCos, aPsi + aKsi);
    UFloatT cosA23 = omegaD2SinP2 * psiAKsiCos;

    UFloatT cosA2 = cosA21 * (cosA22 + cosA23);

    UFloatT cosA = cosA1 + cosA2;

    mITrig->ACos(aAngle, cosA);

    return UErrFalse;
}

/**
 * \brief Parameter for Zenith angle with earth and sun, omega.
 */
UFloatT CEarthCoordCtl::PZaEsOmega()
{
    UFloatT omega = 0.4093146162;

    return omega;
}

/**
 * \brief Parameter for Zenith angle, iota;
 */
UFloatT CEarthCoordCtl::PZaEmOmega(const BTimeTmT *aTm)
{
    UFloatT iota = AcTideEmI();
    UFloatT iotaCos = 0.0;
    mTrig->Cos(&iotaCos, iota);
    UFloatT iotaSin = 0.0;
    mTrig->Sin(&iotaSin, iota);

    UFloatT esOmega = PZaEsOmega();
    UFloatT esOmegaCos = 0.0;
    mTrig->Cos(&esOmegaCos, esOmega);
    UFloatT esOmegaSin = 0.0;
    mTrig->Sin(&esOmegaSin, esOmega);

    UFloatT man = MeanLonMan(aTm);
    UFloatT manCos = 0.0;
    mTrig->Cos(&manCos, man);

    UFloatT cosOmega = esOmegaCos * iotaCos - esOmegaSin * iotaSin * manCos;
    UFloatT omega = 0.0;
    mITrig->ACos(&omega, cosOmega);

    return omega;
}
/**
 * \brief Parameter for zenith angle with earth and moon, eta.
 */
UFloatT CEarthCoordCtl::PZaEmEta(const BTimeTmT *aTm)
{
    UFloatT iota = AcTideEmI();
    UFloatT iotaSin = 0.0;
    mTrig->Sin(&iotaSin, iota);

    UFloatT man = MeanLonMan(aTm);
    UFloatT manSin = 0.0;
    mTrig->Sin(&manSin, man);

    UFloatT emOmega = PZaEmOmega(aTm);
    UFloatT emOmegaSin = 0.0;
    mTrig->Sin(&emOmegaSin, emOmega);

    UFloatT eta = 0.0;
    mITrig->ASin(&eta, iotaSin * manSin / emOmegaSin);

    return eta;
}

/**
 * \brief Parameter for zenith angle with earth and moon, ksi.
 */
UFloatT CEarthCoordCtl::PZaEmKsi(const BTimeTmT *aTm, const BGeomCsGdT *aGd)
{
    UFloatT eta = PZaEmEta(aTm);
    UFloatT emKsi = PZaEsKsi(aTm, aGd);
    UFloatT ksi = emKsi - eta;

    return ksi;
}

/**
 * \brief Parameter for zenith angle with earth and sun, ksi.
 */
UFloatT CEarthCoordCtl::PZaEsKsi(const BTimeTmT *aTm, const BGeomCsGdT *aGd)
{
    UFloatT tm = mEarthTime->JctD(aTm);
    UFloatT h = MeanLonS(aTm);
    UFloatT pi = mMathConst->Pi();


    UFloatT lon = 0.0;
    mMathType->DegToRad(&lon, aGd->lon);

    UFloatT tmFloor = 0.0;
    mArithRound->Floor(&tmFloor, tm);

    UFloatT t = 2 * pi * (tm - tmFloor) + lon;
    UFloatT ksi = t + h;

    return ksi;
}

/**
 * \brief Parameter for Zenith angle with earth and moon, psi.
 */
UFloatT CEarthCoordCtl::PZaEmPsi(const BTimeTmT *aTm)
{
    UFloatT s = MeanLonM(aTm);
    UFloatT p = MeanLonMp(aTm);
    UFloatT h = MeanLonS(aTm);

    UFloatT man = MeanLonMan(aTm);
    UFloatT manSin = 0.0;
    mTrig->Sin(&manSin, man);
    UFloatT manCos = 0.0;
    mTrig->Cos(&manCos, man);

    UFloatT e = AcTideEmE();
    UFloatT m = AcTideEmM();

    UFloatT emOmega = PZaEmOmega(aTm);
    UFloatT emOmegaSin = 0.0;
    mTrig->Sin(&emOmegaSin, emOmega);

    UFloatT esOmega = PZaEsOmega();
    UFloatT esOmegaSin = 0.0;
    mTrig->Sin(&esOmegaSin, esOmega);
    UFloatT esOmegaCos = 0.0;
    mTrig->Cos(&esOmegaCos, esOmega);

    UFloatT eta = PZaEmEta(aTm);
    UFloatT etaSin = 0.0;
    mTrig->Sin(&etaSin, eta);
    UFloatT etaCos = 0.0;
    mTrig->Cos(&etaCos, eta);

    UFloatT alfa1 = esOmegaSin * manSin / emOmegaSin;
    UFloatT alfa21 = 1;
    UFloatT alfa22 = manCos * etaCos;
    UFloatT alfa23 = manSin * etaSin * esOmegaCos;
    UFloatT alfa2 = alfa21 + alfa22 + alfa23;
    UFloatT alfa1A2ATan = 0.0;
    mITrig->ATan(&alfa1A2ATan, alfa1 / alfa2);
    UFloatT alfa = 2 * alfa1A2ATan;

    UFloatT sigma = s - man + alfa;

    UFloatT psi1 = sigma;

    UFloatT spSin = 0.0;
    mTrig->Sin(&spSin, s - p);
    UFloatT psi2 = 2.0 * e * spSin;

    UFloatT s2spSin = 0.0;
    mTrig->Sin(&s2spSin, 2 * (s - p));
    UFloatT psi3 = 5.0 / 4.0 * e * e * s2spSin;

    UFloatT s2hpSin = 0.0;
    mTrig->Sin(&s2hpSin, s - 2 * h + p);
    UFloatT psi4 = 15.0 / 4.0 * m * e * s2hpSin;

    UFloatT s2shSin = 0.0;
    mTrig->Sin(&s2shSin, 2 * (s - h));
    UFloatT psi5 = 11.0 / 8.0 * m * m * s2shSin;

    UFloatT psi = psi1 + psi2 + psi3 + psi4 + psi5;

    return psi;
}

/**
 * \brief Parameter for Zenith angle with earth and sun, psi.
 */
UFloatT CEarthCoordCtl::PZaEsPsi(const BTimeTmT *aTm)
{
    UFloatT h = MeanLonS(aTm);
    UFloatT e = AcTideEsE(aTm);
    UFloatT p = MeanLonSp(aTm);

    UFloatT hpSin = 0.0;
    mTrig->Sin(&hpSin, h - p);

    UFloatT psi = h + 2 * e * hpSin;

    return psi;
}

/**
 * \brief Doodson numbers.
 */
// UErrCodeT CEarthCoordCtl::DoodsonNum()
// {
//     return UErrFalse;
// }

/***** Private B  *****/
