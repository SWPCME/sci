/******************************************************************************
 * $Id: base_ctl.cxx 2017-09 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Base implementation.
 * Author:   Weiwei Huang, 898687324@qq.com
 *
 ******************************************************************************
 * Copyright (c) 2017-09 ~ 2017, Weiwei Huang
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

#include "base_ctl.hxx"

// hub
#include "base_macrodefn.hpp"
#include "hub_ctl.hpp"
#include "hub_modulectl.hpp"

// sci
#include "subj_ctl.hxx"

using namespace sci;

/**
 * \brief Static handle of base.
 */
CBaseCtl *CBaseCtl::mBase = NULL;
CBaseCtl *CBaseCtl::Base()
{
    BMD_CLASS_NEW(mBase, CBaseCtl);

    return mBase;
}

/**
 * \brief Initialize.
 *
 * @return UErrFalse, if successful; UErrTrue, if failed.
 */
UErrCodeT CBaseCtl::Init()
{
    return UErrFalse;
}

/**
 * \brief Hub module.
 */
CHubModuleCtl *CBaseCtl::HubM()
{
    if (mHubM == NULL)
    {
        CHubCtl *hubCtl = CHubCtl::Hub();
        mHubM = hubCtl->RegModule();
        mHubM->Register(HubMCls);
        mHubM->Register(HubMGsl);
    }

    return mHubM;
}

/**
 * \brief Subj.
 */
CSubjCtl *CBaseCtl::Subj()
{
    BMD_CLASS_NEW(mSubj, CSubjCtl);

    return mSubj;
}

/***** Private A *****/

/**
 * \brief Constructor.
 */
CBaseCtl::CBaseCtl()
{
    BMD_POINTER_INIT(mSubj);
    BMD_POINTER_INIT(mHubM);
}

/**
 * \brief Destructor.
 */
CBaseCtl::~CBaseCtl()
{
    BMD_CLASS_DEL(mSubj);
    mHubM->DeregisterAll();
}

/***** Private B *****/
