//###########################################################################
// This file is part of LImA, a Library for Image Acquisition
//
// Copyright (C) : 2009-2020
// European Synchrotron Radiation Facility
// CS40220 38043 Grenoble Cedex 9
// FRANCE
//
// Contact: lima@esrf.fr
//
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//###########################################################################

#pragma once

#include <pixy2_export.h>
#include <lima/HwBufferMgr.h>
#include "lima/HwInterface.h"
#include <lima/Debug.h>

#include "libpixyusb2.h"

namespace lima
{
namespace pixy2
{

  class PIXY2_EXPORT Camera
  {
    DEB_CLASS_NAMESPC(DebModCamera, "Camera", "Pixy2");
  public:
    Camera();
    ~Camera();

    HwBufferCtrlObj *getBufferCtrlObj() { return &m_buffer_ctrl_obj; }

  private:
    // lima stuff
      SoftBufferCtrlObj m_buffer_ctrl_obj;
  };

} // namespace pixy2
} // namespace lima
