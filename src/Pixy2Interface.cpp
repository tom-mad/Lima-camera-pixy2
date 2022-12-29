#include "pixy2/Interface.h"
#include "pixy2/Camera.h"
#include "pixy2/DetInfoCtrlObj.h"
#include "pixy2/SyncCtrlObj.h"

using namespace lima;
using namespace lima::pixy2;

Interface::Interface(Camera& cam) :
  m_cam(cam)
{
  m_det_info = new DetInfoCtrlObj(cam);
  m_sync = new SyncCtrlObj(cam);
  DEB_CONSTRUCTOR();
}

Interface::~Interface()
{
  DEB_DESTRUCTOR();
  delete m_det_info;
  delete m_sync;

}

void Interface::getCapList(CapList &cap_list) const
{
  cap_list.push_back(HwCap(m_det_info));
  HwBufferCtrlObj *buffer = m_cam.getBufferCtrlObj();
  cap_list.push_back(HwCap(buffer));

  cap_list.push_back(HwCap(m_sync));
}

void Interface::reset(ResetLevel reset_level)
{
  DEB_MEMBER_FUNCT();
  DEB_PARAM() << DEB_VAR1(reset_level);
}

void Interface::prepareAcq()
{
  DEB_MEMBER_FUNCT();

  m_cam.prepareAcq();
}

void Interface::startAcq()
{
  DEB_MEMBER_FUNCT();

  m_cam.startAcq();
}

void Interface::stopAcq()
{
  DEB_MEMBER_FUNCT();

  m_cam.stopAcq();
}

void Interface::getStatus(StatusType& status)
{
  DEB_MEMBER_FUNCT();
  
  switch (m_cam.getStatus())
  {
    case Camera::Ready:
      status.set(HwInterface::StatusType::Ready);
      break;
    case Camera::Exposure:
      status.set(HwInterface::StatusType::Exposure);
      break;
    case Camera::Readout:
      status.set(HwInterface::StatusType::Readout);
      break;
    case Camera::Latency:
      status.set(HwInterface::StatusType::Latency);
      break;
    case Camera::Fault:
      status.set(HwInterface::StatusType::Fault);
  }
}

int Interface::getNbHwAcquiredFrames()
{
  DEB_MEMBER_FUNCT();

  return m_cam.getNbHwAcquiredFrames();
}
