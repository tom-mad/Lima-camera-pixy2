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
  m_cam.setTrigMode(trig_mode);
}

void SyncCtrlObj::getTrigMode(TrigMode &trig_mode)
{
  m_cam.getTrigMode(trig_mode);
}

void SyncCtrlObj::setExpTime(double exp_time)
{
  m_cam.setExpTime(exp_time);
}

void SyncCtrlObj::getExpTime(double &exp_time)
{
  m_cam.getExpTime(exp_time);
}

void SyncCtrlObj::setLatTime(double lat_time)
{
  m_cam.setLatTime(lat_time);
}

void SyncCtrlObj::getLatTime(double &lat_time)
{
  m_cam.getLatTime(lat_time);
}

void SyncCtrlObj::setNbHwFrames(int nb_frames)
{
  m_cam.setNbHwFrames(nb_frames);
}

void SyncCtrlObj::getNbHwFrames(int &nb_frames)
{
  m_cam.getNbHwFrames(nb_frames);
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
