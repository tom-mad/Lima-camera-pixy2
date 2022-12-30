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
//---------------------------
//- Interface
//---------------------------
    void prepareAcq();
    void startAcq();
    void stopAcq();
    void reset();
    int getNbHwAcquiredFrames();
//---------------------------
//- DetInfoCtrlObj
//---------------------------
    void getDetectorImageSize(Size &size);
    void getDetectorModel(std::string &det_model);
    void getImageType(ImageType &image_type);
//---------------------------
//- SyncCtrlObj
//---------------------------
    void setTrigMode(TrigMode trig_mode);
    void getTrigMode(TrigMode &trig_mode);
    void setExpTime(double exp_time);
    void getExpTime(double &exp_time);
    void setLatTime(double lat_time);
    void getLatTime(double &lat_time);
    void setNbHwFrames(int nb_frames);
    void getNbHwFrames(int &nb_frames);

  private:
    Camera(const pixy2::Camera&);
  };
};
