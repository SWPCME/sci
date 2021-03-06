/******************************************************************************
 * $Id: atr_ctl.hxx 2017-11 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Atr controler definition.
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

#ifndef SCIATR_CTL_HXX_INCLUDED
#define SCIATR_CTL_HXX_INCLUDED

#include "atr_base.hxx"

namespace sci
{
    class CEarthCtl;

    class SCIATR_LIB CAtrCtl
    {
      public:
        CAtrCtl();
        ~CAtrCtl();

        UErrCodeT Init();
        CEarthCtl *Earth();

      protected:
      private:
        CEarthCtl *mEarth;
    };
}

#endif  // SCIATR_CTL_HXX_INCLUDED
