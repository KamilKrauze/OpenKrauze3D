#!/bin/bash
premake5 gmake

# If directories don't exist, make-em.
if [ ! -d "./thirdparty/include" ]; then
    echo "Creating 'include' directory..."
    echo

    cd ./thirdparty
    mkdir include
    mkdir ./include/glad
    mkdir ./include/KHR

    # Move files into include
    cp -a ./glm/glm ./include/glm
    cp -a ./glfw/include/GLFW ./include/
    cp -a ./stb/ ./include/stb

    # Fetch glad files to project
    wget -O ./include/glad/glad.h https://glad.dav1d.de/generated/tmpnbaj81ksglad/include/glad/glad.h
    wget -O ../src/glad.c https://glad.dav1d.de/generated/tmpnbaj81ksglad/src/glad.c

    # Fetch KHR file to include
    wget -O ./include/KHR/khrplatform.h https://glad.dav1d.de/generated/tmpnbaj81ksglad/include/KHR/khrplatform.h

    cd ..
fi

if [ ! -d "./thirdparty/lib" ]; then
    echo "Creating 'lib' directory..."
    cd ./thirdparty
    mkdir lib
    cd ..
fi

echo "Done..."