/******************************************************************************
 * $Id: base_ctl.hxx 2017-09 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Base definition.
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

#ifndef SCI_BASE_CTL_HXX_INCLUDED
#define SCI_BASE_CTL_HXX_INCLUDED

#include "sci_base.hxx"

class CHubModuleCtl;

namespace sci
{
    class CSubjCtl;

    class SCI_LIB CBaseCtl
    {
      public:
        static CBaseCtl *Base();

        UErrCodeT Init();
        CHubModuleCtl *HubM();
        CSubjCtl *Subj();

      protected:
      private:
        CBaseCtl();
        ~CBaseCtl();

        static CBaseCtl *mBase;

        CHubModuleCtl *mHubM;

        CSubjCtl *mSubj;
    };
}

#endif  // SCI_BASE_CTL_HXX_INCLUDED
