cmake_minimum_required(VERSION 3.15)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

# Homebrew tarafından yüklenen SDL2 ve GLFW'nin kurulu olduğu dizinleri belirtme
set(CMAKE_PREFIX_PATH "/opt/homebrew" ${CMAKE_PREFIX_PATH})

# Kütüphaneleri bulma
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SDL2 REQUIRED)

# İkili dosya ve kütüphaneleri tanımlama
add_executable(MyProject src/main.cpp)

add_library(imgui STATIC
        src/imgui-master/imgui.cpp
        src/imgui-master/imgui_draw.cpp
        src/imgui-master/imgui_tables.cpp
        src/imgui-master/imgui_widgets.cpp
        src/imgui-master/backends/imgui_impl_opengl3.cpp
        src/imgui-master/backends/imgui_impl_glfw.cpp
        src/imgui-master/backends/imgui_impl_sdl2.cpp   # SDL2 backend dosyası
        check_opengl_version.cpp
        src/imgui-master/examples/example_sdl2_opengl3/main.cpp
        src/imgui-master/imgui_demo.cpp
)

# İlgili başlık dosyalarının bulunduğu dizinleri belirtme
include_directories(
        ${CMAKE_SOURCE_DIR}/src/imgui-master
        ${CMAKE_SOURCE_DIR}/src/imgui-master/backends
        /opt/homebrew/include  # Homebrew tarafından yüklenen başlık dosyaları
        ${SDL2_INCLUDE_DIRS}   # SDL2 başlık dosyaları
)

# Bağlantı kütüphanelerini belirleme
target_link_libraries(MyProject imgui
        OpenGL::GL
        glfw
        ${SDL2_LIBRARIES}  # SDL2 kütüphaneleri
)
