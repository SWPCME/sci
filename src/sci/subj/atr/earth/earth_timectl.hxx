/******************************************************************************
 * $Id: earth_timectl.hxx 2017-11 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Time controler definition.
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

#ifndef SCIEARTH_TIMECTL_HXX_INCLUDED
#define SCIEARTH_TIMECTL_HXX_INCLUDED

#include "earth_base.hxx"

// base
#include "base_timetype.hpp"

// cls
class CClsTimeCtl;

namespace sci
{
    class SCIEARTH_LIB CEarthTimeCtl
    {
      public:
        CEarthTimeCtl();
        ~CEarthTimeCtl();

        UErrCodeT Init();
        UFloatT Jct(const BTimeTmT *aTm);
        UFloatT JctD(const BTimeTmT *aTm);

    protected:
      private:
        CClsTimeCtl *mTime;
    };
}

#endif  // SCIEARTH_TIMECTL_HXX_INCLUDED
