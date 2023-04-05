ftxui-starter
-------------

Minimal starter project using the [FTXUI library](https://github.com/ArthurSonzogni/ftxui)


# Build instructions:
~~~bash
mkdir build
cd build
cmake ..
make -j
cd ../target
./ftxui-starter
~~~

## Webassembly build:
~~~bash
mkdir build_emscripten && cd build_emscripten
emcmake cmake ..
make -j
./run_webassembly.py
(visit localhost:8000)
~~~
