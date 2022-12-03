//###########################################################################
// This file is part of LImA, a Library for Image Acquisition
//
// Copyright (C) : 2009-2021
// European Synchrotron Radiation Facility
// BP 220, Grenoble 38043
// FRANCE
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

#include "pixy2/SyncCtrlObj.h"

using namespace lima;
using namespace lima::pixy2;

SyncCtrlObj::SyncCtrlObj(Camera &cam) : HwSyncCtrlObj(), m_cam(cam) {}

SyncCtrlObj::~SyncCtrlObj() {}

bool SyncCtrlObj::checkTrigMode(TrigMode trig_mode)
{
  switch (trig_mode) {
  case IntTrig:
  case IntTrigMult:
  case ExtTrigSingle:
  case ExtTrigMult:
    return true;
  default:
    return false;
  }
}

void SyncCtrlObj::setTrigMode(TrigMode trig_mode)
{
  if (!checkTrigMode(trig_mode)) throw LIMA_HW_EXC(InvalidValue, "Invalid (external) trigger");
  // TODO
}

void SyncCtrlObj::getTrigMode(TrigMode &trig_mode)
{
  // TODO
}

void SyncCtrlObj::setExpTime(double exp_time)
{
  // TODO
}

void SyncCtrlObj::getExpTime(double &exp_time)
{
  // TODO
}

void SyncCtrlObj::setLatTime(double lat_time)
{
  // TODO
}

void SyncCtrlObj::getLatTime(double &lat_time)
{
  // TODO
}

void SyncCtrlObj::setNbHwFrames(int nb_frames)
{
  // TODO
}

void SyncCtrlObj::getNbHwFrames(int &nb_frames)
{
  // TODO
}

void SyncCtrlObj::getValidRanges(ValidRangesType &valid_ranges)
{
  double min_time           = 10e-9;
  double max_time           = 1e6;
  valid_ranges.min_exp_time = min_time;
  valid_ranges.max_exp_time = max_time;
  valid_ranges.min_lat_time = min_time;
  valid_ranges.max_lat_time = max_time;
}
