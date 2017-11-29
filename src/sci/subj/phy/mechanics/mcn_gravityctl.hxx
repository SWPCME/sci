/******************************************************************************
 * $Id: mcn_gravityctl.hxx 2017-09 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Gravity controler definition.
 * Author:   Weiwei Huang, 898687324@qq.com
 *
 ******************************************************************************
 * Copyright (c) 2017-09, Weiwei Huang
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

#ifndef SCI_MCN_GRAVITYCTL_HXX_INCLUDED
#define SCI_MCN_GRAVITYCTL_HXX_INCLUDED

#include "mcn_base.hxx"

namespace sci
{
    class SCIMCN_LIB CMcnGravityCtl
    {
      public:
        CMcnGravityCtl();
        ~CMcnGravityCtl();

        UErrCodeT Init();
        UErrCodeT NlUniG(UFloatT *aF, const UFloatT aM1, const UFloatT aM2,
                         const UFloatT aR);

      protected:
      private:
    };
}

#endif  // SCI_MCN_GRAVITYCTL_HXX_INCLUDED
