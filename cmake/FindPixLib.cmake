set(PixLib_INCLUDE_DIRS /home/tango-cs/PROJECT/pixy2_sdk/API/include)
set(PixLib_LIBRARIES /home/tango-cs/PROJECT/pixy2_sdk/API/bin/libpixy2.a)
set(PixLib_DEFINITIONS -lusb-1.0)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

link_directories(/home/tango-cs/PROJECT/pixy2_sdk/API/bin/)

link_directories(/usr/lib/x86_64-linux-gnu/)



# g++ get_rgb_demo.cpp 
# -I/home/tango-cs/PROJECT/Lima-camera-pixy2/pixy2_sdk/src/host/libpixyusb2/include \
# -I/usr/include/libusb-1.0 \
# -I/home/tango-cs/PROJECT/Lima-camera-pixy2/pixy2_sdk/src/host/arduino/libraries/Pixy2 \
# /home/tango-cs/PROJECT/Lima-camera-pixy2/pixy2_sdk/build/libpixyusb2/libpixy2.a \
# -lusb-1.0
