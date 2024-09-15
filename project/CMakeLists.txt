cmake_minimum_required(VERSION 3.10)
project(FTVox)

# C++ 17 standardı kullanılıyor
set(CMAKE_CXX_STANDARD 17)

# Vulkan SDK'yı bul
find_package(Vulkan REQUIRED)

# SDL2'yi bul
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# GLM'yi projeye dahil et
add_subdirectory(libs/glm)
include_directories(libs/glm)

# Proje ana dosyalarını ekle
file(GLOB_RECURSE SRC_FILES src/*.cpp)

include_directories(inc)
add_executable(Ft_vox ${SRC_FILES})


# SDL2, Vulkan ve GLM ile linkle
target_link_libraries(Ft_vox ${SDL2_LIBRARIES} Vulkan::Vulkan glm)
