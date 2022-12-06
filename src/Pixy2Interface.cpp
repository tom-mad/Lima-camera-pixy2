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

#include "pixy2/Interface.h"
#include "pixy2/Camera.h"
#include "pixy2/DetInfoCtrlObj.h"
#include "pixy2/SyncCtrlObj.h"

using namespace lima;
using namespace lima::pixy2;

Interface::Interface(Camera& cam) :
  m_cam(cam)
{
  m_det_info = new DetInfoCtrlObj(cam);
  m_sync = new SyncCtrlObj(cam);
  DEB_CONSTRUCTOR();
}

Interface::~Interface()
{
  DEB_DESTRUCTOR();
  delete m_det_info;
  delete m_sync;

}

void Interface::getCapList(CapList &cap_list) const
{
  cap_list.push_back(HwCap(m_det_info));
  HwBufferCtrlObj *buffer = m_cam.getBufferCtrlObj();
  cap_list.push_back(HwCap(buffer));

  cap_list.push_back(HwCap(m_sync));
}

void Interface::reset(ResetLevel reset_level)
{
  DEB_MEMBER_FUNCT();
  DEB_PARAM() << DEB_VAR1(reset_level);
}

void Interface::prepareAcq()
{
  DEB_MEMBER_FUNCT();
}

void Interface::startAcq()
{
  DEB_MEMBER_FUNCT();
}

void Interface::stopAcq()
{
  DEB_MEMBER_FUNCT();
}

void Interface::getStatus(StatusType& status)
{
  DEB_MEMBER_FUNCT();
}

int Interface::getNbHwAcquiredFrames()
{
  DEB_MEMBER_FUNCT();
  
  // TODO: get the number of acquired frames
  int acq_frames = 0;
  
  return acq_frames;
}
