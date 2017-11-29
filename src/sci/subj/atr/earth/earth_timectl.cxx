/******************************************************************************
 * $Id: earth_timectl.cxx 2017-11 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Time controler implementation.
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

#include "earth_timectl.hxx"

// hub
#include "hub_modulectl.hpp"
// cls
#include "cls/cls_ctl.hpp"
#include "cls/cls_timectl.hpp"

// sci::base
#include "base_ctl.hxx"

using namespace sci;

/**
 * \brief Constructor.
 */
CEarthTimeCtl::CEarthTimeCtl()
{
    BMD_POINTER_INIT(mTime);
}

/**
 * \brief Destructor.
 */
CEarthTimeCtl::~CEarthTimeCtl()
{
    BMD_POINTER_INIT(mTime);
}

/**
 * \brief Initialize.
 */
UErrCodeT CEarthTimeCtl::Init()
{
    CBaseCtl *base = CBaseCtl::Base();
    CHubModuleCtl *hubM = base->HubM();
    CClsCtl *clsCtl = (CClsCtl *) hubM->Module(HubMCls);
    mTime = clsCtl->Time();

    return UErrFalse;
}

/**
 * \brief Junlian century time.
 */
UFloatT CEarthTimeCtl::Jct(const BTimeTmT *aTm)
{
    UFloatT days = JctD(aTm);
    UFloatT jct = days / 36525 + 1.0;

    return jct;
}

/**
 * \brief Junlian century time of days.
 */
UFloatT CEarthTimeCtl::JctD(const BTimeTmT *aTm)
{
    BTimeTmT tm2000;
    tm2000.year = 2000;
    tm2000.mon = 1;
    tm2000.mday = 1;
    tm2000.hour = 0;
    tm2000.min = 0;
    tm2000.sec = 0;
    tm2000.zone = 0;

    UFloatT secs = 0.0;
    mTime->Diff(&secs, &tm2000, aTm);
    UFloatT days = secs / 24 / 3600;

    return days;
}

/***** Private A *****/

/***** Private B *****/
