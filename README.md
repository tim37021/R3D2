# R3D2
Real-time 3D Engine is a cross-platform graphics framework written in C++. I write it for practicing design pattern and C++11. 

# Build
- Download litehtml in R3D2/ext/
    
        cd ext && git clone https://github.com/litehtml/litehtml

 - Download glfw3 in your workspace, then build and install

        git clone https://github.com/glfw/glfw && cd glfw
        mkdir build && cd build
        cmake ..
        make && sudo make install

 - Generate makefile in R3D2/bin and make

        mkdir bin && cd bin
        cmake .. && make
        # You can specify your compiler, this project can be perfectly compiled by clang
        # cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
