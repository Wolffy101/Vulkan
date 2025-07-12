cmake_minimum_required(VERSION 3.16)

project(vulkan)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
# 查找 Vulkan 包
find_package(VulkanHeaders CONFIG)
find_package(Vulkan REQUIRED)

if(MSVC)
    add_compile_options(/utf-8)
endif()
message(STATUS "Vulkan path: ${VULKAN_SDK}")

# 添加源文件
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# 链接库
target_link_libraries(${PROJECT_NAME} 
PRIVATE 
glfw 
glm::glm 
Vulkan::Vulkan 
Vulkan::Headers)