#include "pixy2/Camera.h"

using namespace lima;
using namespace lima::pixy2;


//---------------------------
//- Acq Thread
//---------------------------
class Camera::_AcqThread : public Thread
{
    DEB_CLASS_NAMESPC(DebModCamera, "Camera", "_AcqThread");
    public:
      _AcqThread(Camera &aCam);
      virtual ~_AcqThread();
    
    protected:
        virtual void threadFunction();
    
    private:
        Camera& pixy_cam;
};

Camera::_AcqThread::~_AcqThread()
{
    AutoMutex aLock(pixy_cam.pixy_cond.mutex());
    pixy_cam.pixy_quit = true;
    pixy_cam.pixy_cond.broadcast();
    aLock.unlock();
    
    join();
}

//---------------------------
//- Ctor
//---------------------------
Camera::Camera():
pixy_image_number(0),
pixy_nb_frames(0),
pixy_status(Ready),
pixy_quit(false),
pixy_wait_flag(true),
pixy_thread_running(true),
pixy_acq_thread(nullptr),
pixy_acq_started(false),
pixy_exposure_time(0.)
{
  DEB_CONSTRUCTOR();

  printf ("Connecting to Pixy2...");

  int Result = pixy.init();

  if (Result < 0)
  {
    printf ("Error\n");
    printf ("pixy.init() returned %d\n", Result);
    exit(Result);
  }

  printf ("Success\n");

  pixy_acq_thread = new _AcqThread(*this);
  if (pixy_acq_thread)
  {
    pixy_acq_thread->start();
  }
}

//---------------------------
//- Dtor
//---------------------------
Camera::~Camera()
{
  DEB_DESTRUCTOR();
}

//---------------------------
//- Acq Thread
//---------------------------
void Camera::_AcqThread::threadFunction() {
  DEB_MEMBER_FUNCT();

  StdBufferCbMgr& buffer_mgr = pixy_cam.pixy_buffer_ctrl_obj.getBuffer();

  while (!pixy_cam.pixy_quit)
  {
    while(pixy_cam.pixy_wait_flag && !pixy_cam.pixy_quit)
    {
      DEB_TRACE() << "Wait";
      std::cout<<"Wait"<<std::endl;
      pixy_cam.pixy_thread_running = false;
      pixy_cam.pixy_cond.broadcast();
      pixy_cam.pixy_cond.wait();
    }
    pixy_cam.pixy_thread_running = true;
    if (pixy_cam.pixy_quit) return;

    pixy_cam.pixy_status = Camera::Exposure;
    pixy_cam.pixy_cond.broadcast();

    bool continueAcq = true;
    bool isError = false;
    uint32_t rgbFrame[PIXY2_RAW_FRAME_WIDTH*PIXY2_RAW_FRAME_HEIGHT];

    uint8_t *bayerFrame;
    pixy_cam._setStatus(Camera::Readout, false);
    while(continueAcq && (!pixy_cam.pixy_nb_frames || pixy_cam.pixy_image_number < pixy_cam.pixy_nb_frames))
    {
      // auto start = high_resolution_clock::now();
      if (pixy_cam.pixy_wait_flag)
      {
        pixy_cam._setStatus(Camera::Ready, false);
        break;
      } 
      // grab raw frame, BGGR Bayer format, 1 byte per pixel
      std::cout<<"test1"<<std::endl;
      pixy_cam.pixy.m_link.getRawFrame(&bayerFrame);
      std::cout<<"test12"<<std::endl;
      // pixy_cam.mark_lines(bayerFrame);
      // convert Bayer frame to RGB frame
      // pixy_cam.demosaic(PIXY2_RAW_FRAME_WIDTH, PIXY2_RAW_FRAME_HEIGHT, bayerFrame, rgbFrame);
      std::cout<<"test4"<<std::endl;
      HwFrameInfoType frame_info;
      frame_info.acq_frame_nb = pixy_cam.pixy_image_number;
      void *framePt = buffer_mgr.getFrameBufferPtr(pixy_cam.pixy_image_number);

      std::cout<<"test5"<<std::endl;
      const FrameDim& fDim = buffer_mgr.getFrameDim();
      void* srcPt = ((char*)bayerFrame);

      std::cout<<"test6"<<fDim.getMemSize()<<std::endl;
      memcpy(framePt, srcPt, fDim.getMemSize());
      std::cout<<"test7"<<std::endl;
      DEB_TRACE() << "memcpy:" << DEB_VAR2(srcPt, framePt);
      std::cout<<"test8"<<std::endl;
        
      std::cout<<"test3"<<std::endl;
      continueAcq = buffer_mgr.newFrameReady(frame_info);
      ++pixy_cam.pixy_image_number;
      // auto stop = high_resolution_clock::now();
      // std::cout << "update picture "<<pixy_cam.pixy_image_number<<" of "<<pixy_cam.pixy_nb_frames<<"Time: "<<duration_cast<seconds>(stop - start).count()<<std::endl;
      
    } // end acquisition while
    pixy_cam._stopAcq(true);
    pixy_cam.pixy_wait_flag = true;
  }
}

Camera::_AcqThread::_AcqThread(Camera &aCam) : pixy_cam(aCam) {
  pthread_attr_setscope(&m_thread_attr,PTHREAD_SCOPE_PROCESS);
}

//---------------------------
//- Internal
//---------------------------
void Camera::demosaic(uint16_t width, uint16_t height, const uint8_t *bayerImage, uint32_t *image)
{
  uint32_t x, y, xx, yy, r, g, b;
  uint8_t *pixel0, *pixel;
  
  for (y=0; y<height; y++)
  {
    yy = y;
    if (yy==0)
      yy++;
    else if (yy==height-1)
      yy--;
    pixel0 = (uint8_t *)bayerImage + yy*width;
    for (x=0; x<width; x++, image++)
    {
      xx = x;
      if (xx==0)
	xx++;
      else if (xx==width-1)
	xx--;
      pixel = pixel0 + xx;
      if (yy&1)
      {
        if (xx&1)
        {
          r = *pixel;
          g = (*(pixel-1)+*(pixel+1)+*(pixel+width)+*(pixel-width))>>2;
          b = (*(pixel-width-1)+*(pixel-width+1)+*(pixel+width-1)+*(pixel+width+1))>>2;
        }
        else
        {
          r = (*(pixel-1)+*(pixel+1))>>1;
          g = *pixel;
          b = (*(pixel-width)+*(pixel+width))>>1;
        }
      }
      else
      {
        if (xx&1)
        {
          r = (*(pixel-width)+*(pixel+width))>>1;
          g = *pixel;
          b = (*(pixel-1)+*(pixel+1))>>1;
        }
        else
        {
          r = (*(pixel-width-1)+*(pixel-width+1)+*(pixel+width-1)+*(pixel+width+1))>>2;
          g = (*(pixel-1)+*(pixel+1)+*(pixel+width)+*(pixel-width))>>2;
          b = *pixel;
        }
      }
      *image = (b<<16) | (g<<8) | r; 
    }
  }
}

void Camera::_startAcq()
{
  DEB_MEMBER_FUNCT();
  pixy.m_link.stop();

  pixy_wait_flag = false;
  pixy_cond.broadcast();
  pixy_acq_started = true;
}

void Camera::_stopAcq(bool internalFlag)
{
  DEB_MEMBER_FUNCT();

  pixy_wait_flag = true;
  pixy_cond.broadcast();
  pixy.m_link.resume();
}

void Camera::_setStatus(Camera::Status status, bool force)
{
  DEB_MEMBER_FUNCT();
  pixy_status = status;
  pixy_cond.broadcast();
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
  std::cout<<"val: "<<pixy_acq_started<<std::endl;
  if (!pixy_acq_started) {
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

  // DEB_RETURN() << DEB_VAR1(status);
}

int Camera::getNbHwAcquiredFrames()
{
  return pixy_image_number;
}



void Camera::getDetectorImageSize(Size &size)
{
  DEB_MEMBER_FUNCT();

  size = Size(PIXY2_RAW_FRAME_WIDTH, PIXY2_RAW_FRAME_HEIGHT);
  DEB_RETURN() << DEB_VAR1(size);
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
  image_type = Bpp16;
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

}
void Camera::getLatTime(double &lat_time)
{

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
