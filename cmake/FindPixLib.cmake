find_package( OpenCV REQUIRED )

set(PixLib_INCLUDE_DIRS /home/tango-cs/PROJECT/pixy2_sdk/API/include ${OpenCV_INCLUDE_DIRS})
set(PixLib_LIBRARIES /home/tango-cs/PROJECT/pixy2_sdk/API/bin/libpixy2.a)
set(PixLib_DEFINITIONS -lusb-1.0)


link_directories(/home/tango-cs/PROJECT/pixy2_sdk/API/bin/)

link_directories(/usr/lib/x86_64-linux-gnu/)
