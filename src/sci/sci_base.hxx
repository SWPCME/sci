/******************************************************************************
 * $Id: sci_base.hxx 2017-07 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Base definition.
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

#ifndef SCI_BASE_HXX_INCLUDED
#define SCI_BASE_HXX_INCLUDED

#include "hub_base.h"

#define SCI_LIB HUB_LIB

namespace sci
{
    typedef enum
    {
        SciMMth = 1,
        SciMPhy = 2,
        SciMAtr = 3,
    } SciCodeT;
}

#endif  // SCI_BASE_HXX_INCLUDED
