add_library (sf2dlib "../external/glad/src/glad.c" "../external/stb/stb_image.cpp" "sf2d.hpp"  "core/engine/Window.hpp" "core/engine/Window.cpp" "core/engine/Engine.cpp"   "core/utils.cpp" "core/status.cpp" "core/engine/GLState.cpp" "core/engine/GLAPI.cpp" "core/engine/time.cpp" "core/engine/Renderer.cpp" "core/engine/VertexArray.cpp" "core/engine/Buffer.cpp" "core/engine/Shader.cpp" "core/engine/Texture.cpp" "core/engine/transform.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sf2dlib PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(sf2dlib PUBLIC 
	"../external/glm" 
	"../external/glad/include/"
	"../external/stb/"
	"./core")
	
target_link_libraries(sf2dlib PUBLIC glfw)
