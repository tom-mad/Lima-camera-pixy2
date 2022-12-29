#pragma once

#include "lima/HwInterface.h"

#include <pixy2_export.h>

#include "pixy2/Camera.h"

namespace lima
{
namespace pixy2
{

/// Control object providing camera synchronization interface
class PIXY2_EXPORT SyncCtrlObj : public HwSyncCtrlObj {
  DEB_CLASS_NAMESPC(DebModCamera, "ShutterCtrlObj", "Pixy2");
  
public:
  SyncCtrlObj(Camera &simu);
  virtual ~SyncCtrlObj();

  virtual bool checkTrigMode(TrigMode trig_mode);
  virtual void setTrigMode(TrigMode trig_mode);
  virtual void getTrigMode(TrigMode &trig_mode);

  virtual void setExpTime(double exp_time);
  virtual void getExpTime(double &exp_time);

  virtual void setLatTime(double lat_time);
  virtual void getLatTime(double &lat_time);

  virtual void setNbHwFrames(int nb_frames);
  virtual void getNbHwFrames(int &nb_frames);

  virtual void getValidRanges(ValidRangesType &valid_ranges);

private:
  Camera &m_cam;
};

} // namespace Iris
} // namespace lima
