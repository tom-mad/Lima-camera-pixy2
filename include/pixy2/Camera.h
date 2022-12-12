//###########################################################################
// This file is part of LImA, a Library for Image Acquisition
//
// Copyright (C) : 2009-2020
// European Synchrotron Radiation Facility
// CS40220 38043 Grenoble Cedex 9
// FRANCE
//
// Contact: lima@esrf.fr
//
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//###########################################################################

#pragma once

#include <pixy2_export.h>
#include <lima/HwBufferMgr.h>
#include "lima/HwInterface.h"
#include <lima/Debug.h>

#include "libpixyusb2.h"

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
//- Internal
//---------------------------
    void _startAcq();
    void _stopAcq(bool internalFlag = false);
    void _setStatus(Camera::Status status, bool force);
    void demosaic(uint16_t width, uint16_t height, const uint8_t *bayerImage, uint32_t *image);
//---------------------------
//- Interface
//---------------------------
    void prepareAcq();
    void startAcq();
    void stopAcq();
    void reset();
    void getStatus(Camera::Status& status);
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
    int pixy_image_number;
    Camera::Status pixy_status;
//---------------------------
//- SyncCtrlObj
//---------------------------
    int pixy_nb_frames;
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
