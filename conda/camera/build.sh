#!/bin/bash
cmake -Bbuild -H. -GNinja -DLIMA_ENABLE_PYTHON=1 -DCAMERA_ENABLE_TESTS=1 -DCMAKE_INSTALL_PREFIX=$PREFIX -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_FIND_ROOT_PATH=$PREFIX
cmake --build build --target install
