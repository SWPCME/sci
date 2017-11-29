/******************************************************************************
 * $Id: sci_ctl.hxx 2017-07 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Sci controler implementation.
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

#include "sci_ctl.hxx"
#include "sci_modulectl.hxx"

// hub
#include "hub_modulectl.hpp"

using namespace sci;

// Global static
CSciCtl* CSciCtl::mSci = NULL;

/**
 * \brief Constructor.
 */
CSciCtl::CSciCtl()
{
    BMD_POINTER_INIT(mModule);
    BMD_CLASS_NEW(mModule, CSciModuleCtl);
}

/**
 * \brief Destructor.
 */
CSciCtl::~CSciCtl()
{
    BMD_CLASS_DEL(mModule);
}

/**
 * \brief Sci.
 */
CSciCtl *CSciCtl::Sci()
{
    BMD_CLASS_NEW(mSci, CSciCtl);

    return mSci;
}

/**
 * \brief Initialize.
 */
UErrCodeT CSciCtl::Init()
{
    return UErrFalse;
}

/**
 * \brief Register.
 */
UErrCodeT CSciCtl::Register(SciCodeT aCode)
{
    return mModule->Register(aCode);
}

/**
 * \brief Module.
 */
UHandleT CSciCtl::Module(SciCodeT aCode)
{
    return mModule->Module(aCode);
}

/**
 * \brief Atr.
 */
CAtrCtl *CSciCtl::Atr()
{
    return (CAtrCtl *) mModule->Module(SciMAtr);
}
