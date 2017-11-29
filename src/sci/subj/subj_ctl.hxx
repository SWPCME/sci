/******************************************************************************
 * $Id: subj_ctl.hxx 2017-09 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Subject control definition.
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

#ifndef SCI_SUBJ_CTL_HXX_INCLUDED
#define SCI_SUBJ_CTL_HXX_INCLUDED

#include "subj_base.hxx"

namespace sci
{
    class CMthCtl;
    class CPhyCtl;
    class CAtrCtl;

    class SCISUBJ_LIB CSubjCtl
    {
      public:
        CSubjCtl();
        ~CSubjCtl();

        UErrCodeT Init();
        CAtrCtl *Atr();

      protected:
      private:
        CMthCtl *mMth;
        CPhyCtl *mPhy;
        CAtrCtl *mAtr;
    };
}

#endif  // SCI_SUBJ_CTL_HXX_INCLUDED
