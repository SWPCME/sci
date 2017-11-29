[+ AutoGen5 template -*- mode: text -*-
################################################################################
# $Id: cxx_ctl_tpl.tpl 2017-10 $
#
# Project:  Sci amg (Sci: Science; amg: automated program generator.).
# Purpose:  Cxx controler tpl.
# Author:   Weiwei Huang, 898687324@qq.com
#
################################################################################
# Copyright (c) 2017-10 ~ 2017 Weiwei Huang
#
# This program is free software; you can redistribute it and/or modify it under 
# the terms of the GNU General Public License as published by the Free Software 
# Foundation, either version 3 of the License, or \(at your option\) any later 
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT 
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more 
# details.
#
# You should have received a copy of the GNU General Public License along with 
# this program.  If not, see <http://www.gnu.org/licenses/>.
################################################################################
+]
[+ amg_tpl_head +]

[+ set_writable_not +]

[+ # Create hxx. +]
[+ out_push_new_hxx +]

[+ # Create cxx. +]
[+ out_push_new_cxx +]