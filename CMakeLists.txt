cmake_minimum_required(VERSION 3.16)

project(Platformer3D LANGUAGES C CXX)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory($ENV{External}/glfw-3.3.8 external/glfw)
add_subdirectory($ENV{External}/glm external/glm)
add_subdirectory($ENV{External}/glad external/glad)

target_include_directories(${PROJECT_NAME} PRIVATE $ENV{External}/stb)

target_link_libraries(${PROJECT_NAME} glfw glm glad)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_compile_definitions("$<$<CONFIG:Debug>:DEBUG>")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
	)