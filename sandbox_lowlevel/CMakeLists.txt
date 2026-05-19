add_executable (sandbox_lowlevel "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sandbox_lowlevel PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(sandbox_lowlevel PUBLIC "../engine")
target_link_libraries(sandbox_lowlevel sf2dlib)
