/******************************************************************************
 * $Id: sci_modulectl.hxx 2017-07 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Module controler definition.
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

#ifndef SCI_MODULECTL_HXX_INCLUDED
#define SCI_MODULECTL_HXX_INCLUDED

#include "sci_base.hxx"

// hub::ust
#include "ust/ust_containertype.hpp"

namespace sci
{
    class SCI_LIB CSciModuleCtl
    {
      public:
        CSciModuleCtl();
        ~CSciModuleCtl();

        UErrCodeT Init();
        UErrCodeT Register(SciCodeT aCode);
        UHandleT Module(SciCodeT aCode);

      protected:
      private:
        typedef UContainerT<UHandleT, SciCodeT> MHandleCodeT;
        typedef UIteratorT<UHandleT, SciCodeT> MHandleCodeItT;

        MHandleCodeT mMCodeH;     /* Register handle. */
    };
}

#endif  // SCI_MODULECTL_HXX_INCLUDED
