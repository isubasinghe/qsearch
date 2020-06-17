#!/usr/bin/env bash

# build the service definitions
cd grpc 
protoc --proto_path=. --cpp_out=. ./ops.proto
cd ..

mkdir build
cd build

if [[ "$OSTYPE" == "darwin"* ]]; then
    cmake .. -DCMAKE_OSX_SYSROOT="/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk"
else
    cmake ..
fi

make -j 12
