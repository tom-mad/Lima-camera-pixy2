#pragma once

#include <iostream>
#include <pixy2_export.h>
#include <lima/HwBufferMgr.h>
#include "lima/HwInterface.h"
#include <lima/Debug.h>

#include "libpixyusb2.h"
#include <opencv2/core.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
namespace lima
{
namespace pixy2
{

  class PIXY2_EXPORT Camera
  {
    DEB_CLASS_NAMESPC(DebModCamera, "Camera", "Pixy2");
  public:
    enum Status {
      Ready, Exposure, Readout, Latency, Fault
    };

    Camera();
    ~Camera();
//---------------------------
//- OpenCV methods
//---------------------------
    cv::Mat toMat(uint8_t * img);
    uint8_t * touint8(cv::Mat img);
    uint8_t * draw(uint8_t * img);
    void  get_square_features();
    void  get_blocks();

//---------------------------
//- Internal
//---------------------------

    std::vector<cv::Point> begin_line_point;
    std::vector<cv::Point> end_line_point;

    std::vector<cv::Point> begin_square_point;
    std::vector<cv::Point> end_square_point;
//---------------------------
//- Internal
//---------------------------
    void _startAcq();
    void _stopAcq(bool internalFlag = false);
    void _setStatus(Camera::Status status, bool force);
    void demosaic(uint16_t width, uint16_t height, const uint8_t *bayerImage, uint32_t *image);
    void  get_line_features();
//---------------------------
//- Interface
//---------------------------
    void prepareAcq();
    void startAcq();
    void stopAcq();
    void reset();
    Camera::Status getStatus();
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



    HwBufferCtrlObj *getBufferCtrlObj() { return &pixy_buffer_ctrl_obj; }

  private:
//---------------------------
//- Lima stuff
//---------------------------
    SoftBufferCtrlObj pixy_buffer_ctrl_obj;
//---------------------------
//- Pixy
//---------------------------
    Pixy2 pixy;
    int prog;
    int pixy_image_number;
    Camera::Status pixy_status;
//---------------------------
//- SyncCtrlObj
//---------------------------
    int pixy_nb_frames;
    double pixy_exposure_time;
//---------------------------
//- AcqThread
//---------------------------
    class _AcqThread;
    friend class _AcqThread;
    volatile bool pixy_quit;
    volatile bool pixy_wait_flag;
    volatile bool pixy_thread_running;
    bool pixy_acq_started;
    _AcqThread *pixy_acq_thread;
    Cond pixy_cond;
  };

} // namespace pixy2
} // namespace lima
