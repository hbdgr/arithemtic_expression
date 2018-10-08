file(GLOB project_headers "*.hpp")
file(GLOB project_sources "*.cpp")
list(REMOVE_ITEM project_sources main.cpp)

add_library (my_lib ${project_sources} ${project_headers})
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} my_lib)
