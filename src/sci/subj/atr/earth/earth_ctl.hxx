/******************************************************************************
 * $Id: earth_ctl.hxx 2017-11 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Earth controler implementation.
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

#ifndef SCI_EARTH_CTL_HXX_INCLUDED
#define SCI_EARTH_CTL_HXX_INCLUDED

#include "earth_base.hxx"

namespace sci
{
    class CEarthTypeCtl;
    class CEarthCoordCtl;
    class CEarthTimeCtl;
    class CEarthTideCtl;

    class SCIEARTH_LIB CEarthCtl
    {
      public:
        CEarthCtl();
        ~CEarthCtl();

        UErrCodeT Init();
        CEarthTypeCtl *Type();
        CEarthCoordCtl *Coord();
        CEarthTimeCtl *Time();
        CEarthTideCtl *Tide();

      protected:
      private:
        CEarthTypeCtl *mType;
        CEarthCoordCtl *mCoord;
        CEarthTimeCtl *mTime;
        CEarthTideCtl *mTide;
    };
}

#endif  // SCI_EARTH_CTL_HXX_INCLUDED
