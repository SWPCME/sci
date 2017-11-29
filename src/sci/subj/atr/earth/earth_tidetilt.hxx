/******************************************************************************
 * $Id: earth_tidetilt.hxx 2017-11 $
 *
 * Project:  SCI (SCI: Science).
 * Purpose:  Tide tilt definition.
 * Author:   Weiwei Huang, 898687324@qq.com
 *
 ******************************************************************************
 * Copyright (c) 2017-10 ~ 2017, Weiwei Huang
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

#ifndef SCIEARTH_TIDETILT_HXX_INCLUDED
#define SCIEARTH_TIDETILT_HXX_INCLUDED

#include "earth_base.hxx"

class SCIEARTH_LIB CEarthTideTilt
{
  public:
    CEarthTideTilt();
    ~CEarthTideTilt();

    UErrCodeT Init();

  protected:
  private:
};

#endif  // SCIEARTH_TIDETILT_HXX_INCLUDED
