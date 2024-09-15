cmake_minimum_required(VERSION 3.10)

# Proje adı
project(Ft_vox)

# C++ standardı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dosya dizinlerini belirtelim
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/inc")
set(LIBS_DIR "${PROJECT_SOURCE_DIR}/libs")

# Kaynak ve header dosyalarını otomatik ekleyelim
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${INCLUDE_DIR}/*.hpp")

# İkili dosya hedefi oluşturalım
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include dizinlerini ekleyelim
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBS_DIR}/glm)

# SDL2 kütüphanesini bulup ekleyelim
find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
else()
    message(FATAL_ERROR "SDL2 not found!")
endif()

# Vulkan kütüphanesini bulup ekleyelim
find_package(Vulkan REQUIRED)
if (Vulkan_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
else()
    message(FATAL_ERROR "Vulkan not found!")
endif()

# glm kütüphanesini manuel olarak ekleyelim
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBS_DIR}/glm)

# Derleme çıktısını daha temiz tutmak için
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Ekstra derleyici uyarılarını ekleyelim (opsiyonel)
# if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#     target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
# endif
