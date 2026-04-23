cmake_minimum_required(VERSION 3.10)
project(FirstGame)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(
    include
    C:/Libraries/glfw-3.4.bin.WIN64/include
    C:/Libraries/glad/include
)

# Automatically grab all .cpp files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(main
    ${SOURCES}
    C:/Libraries/glad/src/glad.c
)

# Link libraries
link_directories(C:/Libraries/glfw-3.4.bin.WIN64/lib-mingw-w64)

target_link_libraries(main
    C:/Libraries/glfw-3.4.bin.WIN64/lib-mingw-w64/libglfw3.a
    opengl32
)