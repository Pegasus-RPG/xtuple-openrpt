#
# OpenRPT report writer and rendering engine
# Copyright (C) 2001-2012 by OpenMFG, LLC
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
# Please contact info@openmfg.com with any questions on this license.
#

#
# This file is included by all the other project files
# and is where options or configurations that affect all
# of the projects can be place.
#

CONFIG += release

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0

macx:exists(macx.pri) {
  include(macx.pri)
}

win32:exists(win32.pri) {
  include(win32.pri)
}

unix:exists(unix.pri) {
  include(unix.pri)
}

# OpenRPT includes an embedded copy of libdmtx for convenience on platforms
# where this library is not available as a package.
# Linux users would normally want to use the version supplied by their package
# manager and can do so by setting the environment variable USE_SYSTEM_DMTX
# when building.
USE_SYSTEM_DMTX = $$(USE_SYSTEM_DMTX)
isEmpty( USE_SYSTEM_DMTX ) {
  CONFIG += bundled_dmtx
  LIBDMTX = -lDmtx_Library
} else {
  LIBDMTX = -ldmtx
}

