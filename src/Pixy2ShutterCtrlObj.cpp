#include "pixy2/ShutterCtrlObj.h"

using namespace lima;
using namespace lima::pixy2;

//-----------------------------------------------------
// @brief Ctor
//-----------------------------------------------------
ShutterCtrlObj::ShutterCtrlObj(Camera &cam)
    : m_cam(cam), m_shutter_mode(ShutterCtrlObj::FRAME), m_manual_state(false), m_open_time(0.), m_close_time(0.)
{
  DEB_CONSTRUCTOR();
}

//-----------------------------------------------------
// @brief Dtor
//-----------------------------------------------------
ShutterCtrlObj::~ShutterCtrlObj()
{
  DEB_DESTRUCTOR();
}

//-----------------------------------------------------
// @brief return true if the mode is valid
//-----------------------------------------------------
bool ShutterCtrlObj::checkMode(ShutterMode shut_mode) const
{
  DEB_MEMBER_FUNCT();
  DEB_PARAM() << DEB_VAR1(shut_mode);

  bool valid_mode;
  switch (shut_mode) {
  case ShutterAutoFrame:
  case ShutterManual:
    valid_mode = true;
    break;
  default:
    // No AutoSequence mode for Simulator !
    valid_mode = false;
  }

  DEB_RETURN() << DEB_VAR1(valid_mode);
  return valid_mode;
}

//-----------------------------------------------------
// @brief return the shutter valid mode list
//-----------------------------------------------------
void ShutterCtrlObj::getModeList(ShutterModeList &mode_list) const
{
  DEB_MEMBER_FUNCT();
  mode_list.push_back(ShutterAutoFrame);
  mode_list.push_back(ShutterManual);
}

//-----------------------------------------------------
// @brief set the shutter mode
//-----------------------------------------------------
void ShutterCtrlObj::setMode(ShutterMode shut_mode)
{
  DEB_MEMBER_FUNCT();
  DEB_PARAM() << DEB_VAR1(shut_mode);

  if (!checkMode(shut_mode)) throw LIMA_HW_EXC(InvalidValue, "Invalid Shutter mode");

  m_shutter_mode = (shut_mode == ShutterAutoFrame) ? CamShutterMode::FRAME : CamShutterMode::MANUAL;
}

//-----------------------------------------------------
// @brief return the shutter mode
//-----------------------------------------------------
void ShutterCtrlObj::getMode(ShutterMode &shut_mode) const
{
  DEB_MEMBER_FUNCT();

  shut_mode = (m_shutter_mode == CamShutterMode::FRAME) ? ShutterAutoFrame : ShutterManual;
  DEB_RETURN() << DEB_VAR1(shut_mode);
}

//-----------------------------------------------------
// @brief open or close manually the shutter
//-----------------------------------------------------
void ShutterCtrlObj::setState(bool open)
{
  DEB_MEMBER_FUNCT();
  m_manual_state = open;
}

//-----------------------------------------------------
// @brief return the shutter state, valid if the shutter
// is in manual mode
//-----------------------------------------------------
void ShutterCtrlObj::getState(bool &open) const
{
  DEB_MEMBER_FUNCT();
  open = m_manual_state;
}

//-----------------------------------------------------
// @brief set the shutter opening time
//-----------------------------------------------------
void ShutterCtrlObj::setOpenTime(double shut_open_time)
{
  DEB_MEMBER_FUNCT();
  m_open_time = shut_open_time;
}

//-----------------------------------------------------
// @brief return the shutter opening time
//-----------------------------------------------------
void ShutterCtrlObj::getOpenTime(double &shut_open_time) const
{
  DEB_MEMBER_FUNCT();
  shut_open_time = m_open_time;

  DEB_RETURN() << DEB_VAR1(shut_open_time);
}

//-----------------------------------------------------
// @brief set the shutter closing time
//-----------------------------------------------------
void ShutterCtrlObj::setCloseTime(double shut_close_time)
{
  DEB_MEMBER_FUNCT();
  m_close_time = shut_close_time;
}

//-----------------------------------------------------
// @brief return the shutter closing time
//-----------------------------------------------------
void ShutterCtrlObj::getCloseTime(double &shut_close_time) const
{
  DEB_MEMBER_FUNCT();
  shut_close_time = m_close_time;
}
