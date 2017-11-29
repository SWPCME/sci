/******************************************************************************
 * $Id: phy_ctl.hxx 2017-09 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Phy controler definition.
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

#ifndef SCI_PHY_CTL_HXX_INCLUDED
#define SCI_PHY_CTL_HXX_INCLUDED

#include "phy_base.hxx"

namespace sci
{
    class CEarthCtl;
    class SCIPHY_LIB CPhyCtl
    {
      public:
        CPhyCtl();
        ~CPhyCtl();

        UErrCodeT Init();
        CEarthCtl *Earth();

      protected:
      private:
    };
}

#endif  // SCI_PHY_CTL_HXX_INCLUDED
