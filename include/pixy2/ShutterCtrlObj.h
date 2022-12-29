#pragma once

#include "lima/HwInterface.h"

#include <pixy2_export.h>

#include "pixy2/Camera.h"

namespace lima
{
namespace pixy2
{

/// Control object providing camera shutter interface
class PIXY2_EXPORT ShutterCtrlObj : public HwShutterCtrlObj {
  DEB_CLASS_NAMESPC(DebModCamera, "ShutterCtrlObj", "Pixy2");

public:
  enum CamShutterMode { FRAME, MANUAL };

  ShutterCtrlObj(Camera &cam);
  virtual ~ShutterCtrlObj();

  virtual bool checkMode(ShutterMode shut_mode) const;
  virtual void getModeList(ShutterModeList &mode_list) const;
  virtual void setMode(ShutterMode shut_mode);
  virtual void getMode(ShutterMode &shut_mode) const;

  virtual void setState(bool shut_open);
  virtual void getState(bool &shut_open) const;

  virtual void setOpenTime(double shut_open_time);
  virtual void getOpenTime(double &shut_open_time) const;
  virtual void setCloseTime(double shut_close_time);
  virtual void getCloseTime(double &shut_close_time) const;

private:
  Camera &m_cam;
  CamShutterMode m_shutter_mode = FRAME;
  bool m_manual_state           = false;
  double m_open_time            = 0.0;
  double m_close_time           = 0.0;
};

} // namespace Iris

} // namespace lima
