/******************************************************************************
 * $Id: earth_tidectl.hxx 2017-09 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Tide controler definition.
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

#ifndef SCI_EARTH_TIDE_CTL_HXX_INCLUDED
#define SCI_EARTH_TIDE_CTL_HXX_INCLUDED

#include "earth_base.hxx"

namespace sci
{
    class CEarthTideBasic;
    class CEarthTideGravity;
    class CEarthTideTilt;
    class CEarthTideLs;

    class SCIEARTH_LIB CEarthTideCtl
    {
      public:
        CEarthTideCtl();
        ~CEarthTideCtl();

        UErrCodeT Init();
        CEarthTideBasic *Basic();
        CEarthTideGravity *Gravity();
        CEarthTideTilt *Tilt();
        CEarthTideLs *Ls();

      protected:
      private:
        UErrCodeT InitPointer();

        CEarthTideBasic *mBasic;
        CEarthTideGravity *mGravity;
        CEarthTideTilt *mTilt;
        CEarthTideLs *mLs;
    };
}

#endif  // SCI_EARTH_TIDE_CTL_HXX_INCLUDED
