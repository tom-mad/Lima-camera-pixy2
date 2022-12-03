###########################################################################
# This file is part of LImA, a Library for Image Acquisition
#
#  Copyright (C) : 2009-2020
#  European Synchrotron Radiation Facility
#  CS40220 38043 Grenoble Cedex 9
#  FRANCE
#
#  Contact: lima@esrf.fr
#
#  This is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 3 of the License, or
#  (at your option) any later version.
#
#  This software is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, see <http://www.gnu.org/licenses/>.
############################################################################

set(SDK_INCLUDE_DIRS)
set(SDK_LIBRARIES)
set(SDK_DEFINITIONS)

find_path(SDK_INCLUDE_DIRS sdk/sdk.h)
find_library(SDK_LIBRARIES sdk)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDK
  DEFAULT_MSG
  SDK_LIBRARIES
  SDK_INCLUDE_DIRS
)

if(SDK_FOUND)
    if(NOT TARGET SDK::SDK)
        add_library(SDK::SDK INTERFACE IMPORTED)
    endif()
    if(SDK_INCLUDE_DIRS)
        set_target_properties(SDK::SDK PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${SDK_INCLUDE_DIRS}")
    endif()
    if(SDK_DEFINITIONS)
        set_target_properties(SDK::SDK PROPERTIES
            INTERFACE_COMPILE_DEFINITIONS "${SDK_DEFINITIONS}")
    endif()
    foreach(LIB IN LISTS SDK_LIBRARIES)
        get_filename_component(MOD ${LIB} NAME_WE)
        add_library(SDK::${MOD} SHARED IMPORTED)
        set_target_properties(SDK::${MOD} PROPERTIES
            IMPORTED_LINK_INTERFACE_LANGUAGES "C"
            IMPORTED_LOCATION "${LIB}")
        target_link_libraries(SDK::SDK INTERFACE SDK::${MOD})
    endforeach()
endif()
