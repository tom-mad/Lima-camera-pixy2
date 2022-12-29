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

    bool continueAcq = true;
    bool isError = false;
    uint32_t rgbFrame[PIXY2_RAW_FRAME_WIDTH*PIXY2_RAW_FRAME_HEIGHT];

    pixy_cam._setStatus(Camera::Readout, false);
    while(continueAcq && (!pixy_cam.pixy_nb_frames || pixy_cam.pixy_image_number < pixy_cam.pixy_nb_frames))
    {
      if (pixy_cam.pixy_wait_flag)
      {
        pixy_cam._setStatus(Camera::Ready, false);
        break;
      } 
      std::cout << "update picture "<<pixy_cam.pixy_image_number<<" of "<<pixy_cam.pixy_nb_frames<<std::endl;
      uint8_t *bayerFrame;

      // grab raw frame, BGGR Bayer format, 1 byte per pixel
      pixy_cam.pixy.m_link.getRawFrame(&bayerFrame);
      // convert Bayer frame to RGB frame
      // pixy_cam.demosaic(PIXY2_RAW_FRAME_WIDTH, PIXY2_RAW_FRAME_HEIGHT, bayerFrame, rgbFrame);

      HwFrameInfoType frame_info;
      frame_info.acq_frame_nb = pixy_cam.pixy_image_number;
      void *framePt = buffer_mgr.getFrameBufferPtr(pixy_cam.pixy_image_number);

      const FrameDim& fDim = buffer_mgr.getFrameDim();
      void* srcPt = ((char*)bayerFrame);
      memcpy(framePt, srcPt, fDim.getMemSize());
      DEB_TRACE() << "memcpy:" << DEB_VAR2(srcPt, framePt);
        
      continueAcq = buffer_mgr.newFrameReady(frame_info);
      ++pixy_cam.pixy_image_number;
    } // end acquisition while
    pixy_cam._stopAcq(true);
    pixy_cam.pixy_wait_flag = true;
  }
}

Camera::_AcqThread::_AcqThread(Camera &aCam) : pixy_cam(aCam) {
  pthread_attr_setscope(&m_thread_attr,PTHREAD_SCOPE_PROCESS);
}