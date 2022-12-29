#pragma once

#include <pixy2_export.h>

#include "lima/HwInterface.h"

namespace lima
{
namespace pixy2
{
  class DetInfoCtrlObj;
  class SyncCtrlObj;
  class Camera;
  
  class PIXY2_EXPORT Interface : public HwInterface
  {
    DEB_CLASS_NAMESPC(DebModCamera, "Pixy2Interface", "Pixy2");

  public:
    Interface(Camera&);
    virtual ~Interface();
    //- From HwInterface
    virtual void	getCapList(CapList&) const;
    virtual void	reset(ResetLevel reset_level);
    virtual void	prepareAcq();
    virtual void	startAcq();
    virtual void	stopAcq();
    virtual void	getStatus(StatusType& status);
    virtual int	  getNbHwAcquiredFrames();

  private:
    Camera&		m_cam;
    // CapList		m_cap_list;
    DetInfoCtrlObj*	m_det_info;
    SyncCtrlObj*	m_sync;
  };

} // namespace pixy2
} // namespace lima
