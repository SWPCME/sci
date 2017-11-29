/******************************************************************************
 * $Id: sci_modulectl.hxx 2017-07 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Module controler definition.
 * Author:   Weiwei Huang, 898687324@qq.com
 *
 ******************************************************************************
 * Copyright (c) 2017-07, Weiwei Huang
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

#include "sci_modulectl.hxx"

#include "base_macrodefn.hpp"

// sci::subj
#include "atr_ctl.hxx"

#define SCI_REGISTER(aCode, aClass)             \
    BMD_REGISTER(aCode, aClass, mMCodeH)

using namespace sci;

/**
 * \brief Constructor.
 */
CSciModuleCtl::CSciModuleCtl() : mMCodeH(UContainerMap)
{
}

/**
 * \brief Destructor.
 */
CSciModuleCtl::~CSciModuleCtl()
{
}

/**
 * \brief Initilize.
 */
UErrCodeT CSciModuleCtl::Init()
{
    return UErrFalse;
}

/**
 * \brief Register.
 */
UErrCodeT CSciModuleCtl::Register(SciCodeT aCode)
{
    if (mMCodeH.FindByKey(aCode) == UErrFalse)
    {
        return UErrFalse;
    }

    switch (aCode)
    {
        // subj
        SCI_REGISTER(SciMAtr, CAtrCtl);
    default:
        return UErrTrue;
    }

    return UErrTrue;
}

/**
 * \brief Module.
 */
UHandleT CSciModuleCtl::Module(SciCodeT aCode)
{
    if (mMCodeH.FindByKey(aCode) == UErrFalse)
    {
        return (UHandleT) mMCodeH[aCode];
    }

    return NULL;
}
