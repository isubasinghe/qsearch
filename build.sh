#!/usr/bin/env bash

mkdir build
cd build

if [[ "$OSTYPE" == "darwin"* ]]; then
    cmake .. -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl -DCMAKE_OSX_SYSROOT="/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk"
else
    cmake ..
fi

make -j 12
