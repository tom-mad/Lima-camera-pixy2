.. _camera-pixy2:

Pixy2
--------

.. image:: pixy2.jpg

Introduction
````````````

This is the official Lima camera pixy2. It has been made to help you getting started with Lima and to test/play Lima without any hardware.

Prerequisite
````````````

There is no special prerequisite, the pixy2 plugin can be compiled and tested on both Linux and Windows platforms.

Installation & Module configuration
````````````````````````````````````

Follow the generic instructions in :ref:`build_installation`. If using CMake directly, add the following flag:

.. code-block:: sh

  -DLIMACAMERA_PIXY2=true

For the Tango server installation, refers to :ref:`tango_installation`.

Initialisation and Capabilities
```````````````````````````````

Implementing a new plugin for new detector is driven by the LIMA framework but the developer has some freedoms to choose which standard and specific features will be made available. This section is supposed to give you the correct information regarding how the camera is exported within the LIMA framework.

Camera initialisation
.....................

.. cpp:namespace-push:: lima::pixy2

The camera will be initialized within the :cpp:class:`Camera` object. The :cpp:func:`Camera` constructor takes an optional mode parameter.

Standard capabilities
.....................

Described the standard capabilites offered by the camera.

Optional capabilities
.....................

Described the optional capabilites offered by the camera.

Configuration
`````````````

Described the eventual configuration steps.

Getting started
```````````````

For a quick test one can use the python binding, here is a short code example:

.. code-block:: python

  from Lima import Simulator
  from Lima import Core
  import time

  def test_mode_generator(cam, nb_frames_prefetched = 0):
      if nb_frames_prefetched:
          cam.setMode(Simulator.Camera.MODE_GENERATOR_PREFETCH)
          fb = cam.getFrameGetter()
          fb.setNbPrefetchedFrames(nb_frames_prefetched);
      else:
          cam.setMode(Simulator.Camera.MODE_GENERATOR)
          fb = cam.getFrameGetter()

      # Add a peak
      p1 = Simulator.GaussPeak(10, 10, 23, 1000) # peak at 10,10 fwhm=23 and max=1000
      fb.setPeaks([p1])


  def test_mode_loader(cam, nb_frames_prefetched = 0):
      if nb_frames_prefetched:
          cam.setMode(Simulator.Camera.MODE_LOADER_PREFETCH)
          fb = cam.getFrameGetter()
          test = fb.getNbPrefetchedFrames();
      else:
          cam.setMode(Simulator.Camera.MODE_LOADER)
          fb = cam.getFrameGetter()

      # Set file pattern
      fb.setFilePattern(b'input\\test_*.edf')

  cam = Simulator.Camera()

  # Select one of the mode to test
  #test_mode_generator(cam)
  #test_mode_generator(cam, 10)
  #test_mode_loader(cam)
  test_mode_loader(cam, 100)

  # Get the hardware interface
  hwint = Simulator.Interface(cam)

  # Get the control interface
  control = Core.CtControl(hwint)

  # Get the acquisition control
  acq = control.acquisition()

  # Set new file parameters and autosaving mode
  saving=control.saving()

  pars=saving.getParameters()
  pars.directory='/tmp/'
  pars.prefix='testsimul_'
  pars.suffix='.edf'
  pars.fileFormat=Core.CtSaving.EDF
  pars.savingMode=Core.CtSaving.AutoFrame
  saving.setParameters(pars)

  # Now ask for 2 sec. exposure and 10 frames
  acq.setAcqExpoTime(2)
  acq.setAcqNbFrames(10)

  control.prepareAcq()
  control.startAcq()

  # Wait for last image (#9) ready
  lastimg = control.getStatus().ImageCounters.LastImageReady
  while lastimg !=9:
    time.sleep(0.1)
    lastimg = control.getStatus().ImageCounters.LastImageReady

  # read the first image
  im0 = control.ReadImage(0)
