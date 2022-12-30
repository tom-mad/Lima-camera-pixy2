#include "pixy2/Camera.h"

using namespace lima;
using namespace lima::pixy2;

void Camera::_startAcq()
{
  DEB_MEMBER_FUNCT();
  pixy_wait_flag = false;
  pixy_acq_started = true;
  pixy_cond.broadcast();
}

void Camera::_stopAcq(bool internalFlag)
{
  DEB_MEMBER_FUNCT();

  pixy_wait_flag = true;
  pixy_status = Camera::Ready;
}

void Camera::_setStatus(Camera::Status status, bool force)
{
  DEB_MEMBER_FUNCT();
  pixy_status = status;
}

//---------------------------
//- Interface
//---------------------------
void Camera::prepareAcq()
{
  DEB_MEMBER_FUNCT();
  pixy_image_number = 0;
  pixy_acq_started = false;
}
void Camera::startAcq()
{
  DEB_MEMBER_FUNCT();

  if (!pixy_acq_started) 
  {
    pixy_buffer_ctrl_obj.getBuffer().setStartTimestamp(Timestamp::now());
    _startAcq();
  }

}
void Camera::stopAcq()
{
  DEB_MEMBER_FUNCT();
  _stopAcq();
}
void Camera::reset()
{
  DEB_MEMBER_FUNCT();
  try
  {
    _stopAcq();
  }
  catch(Exception e)
  {
    THROW_HW_ERROR(Error) << e;
  }
}

Camera::Status Camera::getStatus()
{
  DEB_MEMBER_FUNCT();

  return pixy_status;
}

int Camera::getNbHwAcquiredFrames()
{
  return pixy_image_number;
}

void Camera::getDetectorImageSize(Size &size)
{
  DEB_MEMBER_FUNCT();

  size = Size(PIXY2_RAW_FRAME_WIDTH, PIXY2_RAW_FRAME_HEIGHT);
}

void Camera::getDetectorModel(std::string &det_model)
{
  DEB_MEMBER_FUNCT();

  int8_t Result = pixy.getVersion();
  det_model = std::to_string(Result);
}
void Camera::getImageType(ImageType &image_type)
{
  DEB_MEMBER_FUNCT();
  image_type = Bpp8;
}
//---------------------------
//- SyncCtrlObj
//---------------------------
void Camera::setTrigMode(TrigMode trig_mode)
{

}
void Camera::getTrigMode(TrigMode &trig_mode)
{

}
void Camera::setExpTime(double exp_time)
{
  pixy_exposure_time = exp_time;
}
void Camera::getExpTime(double &exp_time)
{
  exp_time = pixy_exposure_time;
}
void Camera::setLatTime(double lat_time)
{
  prog = static_cast<int>(lat_time);
}
void Camera::getLatTime(double &lat_time)
{
  lat_time = static_cast<double>(prog);
}
void Camera::setNbHwFrames(int nb_frames)
{
  DEB_MEMBER_FUNCT();
  DEB_PARAM() << DEB_VAR1(nb_frames);
  pixy_nb_frames = nb_frames;
}
void Camera::getNbHwFrames(int &nb_frames)
{
  DEB_MEMBER_FUNCT();
  nb_frames = pixy_nb_frames;
  DEB_RETURN() << DEB_VAR1(nb_frames);

}
