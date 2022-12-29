#pragma once

#include "lima/HwInterface.h"

#include <pixy2_export.h>

#include "pixy2/Camera.h"

namespace lima
{
namespace pixy2
{

/// Control object providing detector info interface
class PIXY2_EXPORT DetInfoCtrlObj : public HwDetInfoCtrlObj {
  DEB_CLASS_NAMESPC(DebModCamera, "DetInfoCtrlObj", "Pixy2");

public:
  DetInfoCtrlObj(Camera &cam);
  ~DetInfoCtrlObj();

  virtual void getMaxImageSize(Size &max_image_size);
  virtual void getDetectorImageSize(Size &det_image_size);

  virtual void getDefImageType(ImageType &def_image_type);
  virtual void getCurrImageType(ImageType &curr_image_type);
  virtual void setCurrImageType(ImageType curr_image_type);

  virtual void getPixelSize(double &x_size, double &y_size);
  virtual void getDetectorType(std::string &det_type);
  virtual void getDetectorModel(std::string &det_model);

  virtual void registerMaxImageSizeCallback(HwMaxImageSizeCallback &cb);
  virtual void unregisterMaxImageSizeCallback(HwMaxImageSizeCallback &cb);

private:
  Camera &m_cam;
};

} // namespace pixy2
} // namespace lima
