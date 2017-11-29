/******************************************************************************
 * $Id: earth_timectl.cxx 2017-11 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Test earth implementation.
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

#include "test_earth.hxx"
#include "sci_ctl.hxx"
#include "atr_ctl.hxx"
#include "earth_ctl.hxx"
#include "earth_timectl.hxx"
#include "earth_tidectl.hxx"
#include "earth_tidebasic.hxx"
#include "earth_tidegravity.hxx"

using namespace sci;

UErrCodeT TestTime(CEarthCtl *aEarth);
UErrCodeT TestTide(CEarthCtl *aEarth);

int main()
{
    CSciCtl *sci = CSciCtl::Sci();
    sci->Register(SciMAtr);
    CAtrCtl *atr = sci->Atr();
    CEarthCtl *earth = atr->Earth();
    TestTime(earth);
    TestTide(earth);

    return 0;
}

UErrCodeT TestTime(CEarthCtl *aEarth)
{
    CEarthTimeCtl *time = aEarth->Time();
    BTimeTmT tm;
    tm.year = 2017;
    tm.mon = 1;
    tm.mday = 1;
    tm.hour = 0;
    tm.min = 0;
    tm.sec = 0;
    UFloatT jct = time->Jct(&tm);

    return UErrFalse;
}

UErrCodeT TestTide(CEarthCtl *aEarth)
{
    CEarthTideCtl *tide = aEarth->Tide();
    CEarthTideBasic *basic = tide->Basic();
    CEarthTideGravity *gravity = tide->Gravity();

    BTimeTmT tm;
    tm.year = 2017;
    tm.mon = 1;
    tm.mday = 1;
    tm.hour = 5;
    tm.min = 0;
    tm.sec = 0;

    BGeomCsGdT gd;
    gd.lon = 113;
    gd.lat = 33;
    gd.h = 0.0;
    const UIntT kN = 48;
    UFloatT p[kN];
    UFloatT ug[kN];
    for (UIntT i = 0; i < kN; ++i)
    {
        basic->Potential(&p[i], &tm, &gd);
        p[i] *= 1.158 * 10E7;
        gravity->Calc(&ug[i], &tm, &gd);
	    if (tm.hour % 24 == 0)
        {
            tm.mday += 1;
            tm.hour = 0;
        }
        tm.hour += 1;
    }

    return UErrFalse;
}
