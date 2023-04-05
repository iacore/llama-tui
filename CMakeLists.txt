cmake_minimum_required (VERSION 3.11)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG textarea
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# --- Fetch llama.cpp ----------------------------------------------------------

FetchContent_Declare(llama
  GIT_REPOSITORY https://github.com/iacore/llama.cpp
  GIT_TAG custom
)

FetchContent_GetProperties(llama)
if(NOT llama_POPULATED)
  FetchContent_Populate(llama)
  add_subdirectory(${llama_SOURCE_DIR} ${llama_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------

project(llama-tui
  LANGUAGES C CXX
  VERSION 1.0.0
)

add_executable(llama-tui
  src/main.cpp
  src/llm.cpp
  src/llm.hpp
)
set_property(TARGET llama-tui PROPERTY CXX_STANDARD_REQUIRED 20)
target_include_directories(llama-tui PRIVATE src ${llama_SOURCE_DIR} ${llama_SOURCE_DIR}/examples)

target_link_libraries(llama-tui
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE ggml
  PRIVATE llama
)

if (EMSCRIPTEN) 
  string(APPEND CMAKE_CXX_FLAGS " -s USE_PTHREADS") 
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s ASYNCIFY") 
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s PROXY_TO_PTHREAD") 

  foreach(file "index.html" "run_webassembly.py")
    configure_file("src/${file}" ${file})
  endforeach(file)
endif() 
