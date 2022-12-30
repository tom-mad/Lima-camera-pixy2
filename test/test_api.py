import unittest
import logging
import numpy
import time

from Lima import Core, Pixy2



_logger = logging.getLogger(__name__)


class AcquisitionStatusFromImageStatusCallback(Core.CtControl.ImageStatusCallback):
    def __init__(self):
        super().__init__()
        self.last_base_image_ready = -1
        self.last_image_acquired = -1
        self.last_image_ready = -1
        self.last_image_saved = -1
        self.last_counter_ready = -1

    def imageStatusChanged(self, image_status):
        self.last_base_image_ready = image_status.LastBaseImageReady
        self.last_image_acquired = image_status.LastImageAcquired
        self.last_image_ready = image_status.LastImageReady
        self.last_image_saved = image_status.LastImageSaved
        self.last_counter_ready = image_status.LastCounterReady


class TestPixy2API(unittest.TestCase):
    @classmethod
    def setUpClass(cls):        
        cls.pixy2_cam = Pixy2.Camera()
        time.sleep(2)
        cls.pixy2_hw = Pixy2.Interface(cls.pixy2_cam)
        time.sleep(2)
        cls.pixy2_ct = Core.CtControl(cls.pixy2_hw)
        time.sleep(2)
        cls.pixy2_ctimage = Core.CtImage(cls.pixy2_hw, cls.pixy2_ct)

    def test_should_check_get_image_type(self):
        self.assertEqual(TestPixy2API.pixy2_ctimage.getImageType(), Core.ImageType(0))

    def test_should_check_get_max_image_size(self):
        self.assertEqual(TestPixy2API.pixy2_ctimage.getMaxImageSize(), Core.Size(316,208))

    def test_should_check_read_write_ExpTime(self):
        TestPixy2API.pixy2_cam.setExpTime(0.5)
        self.assertEqual(TestPixy2API.pixy2_cam.getExpTime(), 0.5)

    def test_should_check_read_write_NbHwFrames(self):
        TestPixy2API.pixy2_cam.setNbHwFrames(5)
        self.assertEqual(TestPixy2API.pixy2_cam.getNbHwFrames(), 5)

    def test_should_check_multiple_time_running_acquisition(self):
        acq_status = AcquisitionStatusFromImageStatusCallback()
        TestPixy2API.pixy2_ct.registerImageStatusCallback(acq_status)

        acq = TestPixy2API.pixy2_ct.acquisition()
        acq.setTriggerMode(Core.ExtTrigSingle)
        acq.setAcqNbFrames(0)
        acq.setAcqExpoTime(0.01)

        self.assertEqual(TestPixy2API.pixy2_ct.getStatus().AcquisitionStatus, Core.AcqReady)
        TestPixy2API.pixy2_ct.prepareAcq()
        TestPixy2API.pixy2_ct.startAcq()
        self.assertEqual(TestPixy2API.pixy2_ct.getStatus().AcquisitionStatus, Core.AcqRunning)
        time.sleep(4)
        TestPixy2API.pixy2_ct.stopAcq()
        # TestPixy2API.pixy2_ct.resetAcq()

        acq.setTriggerMode(Core.ExtTrigSingle)
        acq.setAcqNbFrames(3)
        acq.setAcqExpoTime(0.01)
        TestPixy2API.pixy2_ct.prepareAcq()
        TestPixy2API.pixy2_ct.startAcq()
        self.assertEqual(TestPixy2API.pixy2_ct.getStatus().AcquisitionStatus, Core.AcqRunning)
        time.sleep(2)
        self.assertEqual(TestPixy2API.pixy2_ct.getStatus().AcquisitionStatus, Core.AcqReady)

        self.assertEqual(acq_status.last_image_ready, 2)