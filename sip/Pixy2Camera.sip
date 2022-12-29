namespace pixy2
{
  class Camera
  {
%TypeHeaderCode
#include <pixy2/Camera.h>
%End

  public:
    Camera();
    ~Camera();

    // pixy2 info object
    void getDetectorImageSize(Size &size);
    void getDetectorModel(std::string &det_model);

  private:
    Camera(const pixy2::Camera&);
  };
};
