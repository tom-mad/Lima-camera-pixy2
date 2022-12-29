#include "pixy2/DetInfoCtrlObj.h"

using namespace lima;
using namespace lima::pixy2;

DetInfoCtrlObj::DetInfoCtrlObj(Camera& cam) : m_cam(cam) {}
DetInfoCtrlObj::~DetInfoCtrlObj() {}

void DetInfoCtrlObj::getMaxImageSize(Size &max_image_size)
{
  DEB_MEMBER_FUNCT();
  m_cam.getDetectorImageSize(max_image_size);
}

void DetInfoCtrlObj::getDetectorImageSize(Size &det_image_size)
{
  DEB_MEMBER_FUNCT();
  m_cam.getDetectorImageSize(det_image_size);
}

void DetInfoCtrlObj::getDefImageType(ImageType &def_image_type)
{
  DEB_MEMBER_FUNCT();
  m_cam.getImageType(def_image_type);
}

void DetInfoCtrlObj::setCurrImageType(ImageType curr_image_type)
{
  DEB_MEMBER_FUNCT();
  // TODO
}

void DetInfoCtrlObj::getCurrImageType(ImageType &curr_image_type)
{
  DEB_MEMBER_FUNCT();
  m_cam.getImageType(curr_image_type);
}

void DetInfoCtrlObj::getPixelSize(double &x_size, double &y_size)
{
  DEB_MEMBER_FUNCT();
  // TODO
}

void DetInfoCtrlObj::getDetectorType(std::string &det_type)
{
  DEB_MEMBER_FUNCT();
  det_type = "Pixy2";
}

void DetInfoCtrlObj::getDetectorModel(std::string &det_model)
{
  DEB_MEMBER_FUNCT();
  m_cam.getDetectorModel(det_model);
}

void DetInfoCtrlObj::registerMaxImageSizeCallback(HwMaxImageSizeCallback &cbk)
{
  DEB_MEMBER_FUNCT();

  // TODO
}

void DetInfoCtrlObj::unregisterMaxImageSizeCallback(HwMaxImageSizeCallback &cbk)
{
  DEB_MEMBER_FUNCT();

  // TODO
}
