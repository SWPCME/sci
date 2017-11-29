[+ AutoGen5 template +]
/******************************************************************************
 * $Id: [+ file_name +] [+ date_now +] $
 *
 * Project:  [+ project +]
 * Purpose:  [+ purpose +]
 * Author:   [+ author_name +], [+ author_email +]
 *
 ******************************************************************************
 * Copyright (c) [+ date_begin +] ~ [+ date_end +], [+ author_name +]
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

#ifndef [+ file_def +]
#define [+ file_def +]

namespace [+ namespace_name +]
{
    class [+ lib +] [+ class_name +]
    {
      public:
        [+ class_name +]();
        ~[+ class_name +]();

        UErrCodeT Init();

      protected:
      private:
    };
}
 
#endif  // [+ file_def +]
