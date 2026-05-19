add_executable (sandbox_application "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sandbox_application PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(sandbox_application PUBLIC "../engine")
target_link_libraries(sandbox_application sf2dlib)
