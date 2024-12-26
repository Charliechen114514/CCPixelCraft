set(example_list_build ${EXAMPLE_BUILD_NAME}.cpp)
configuring_common_example_srclist(example_list_build)
add_executable(${EXAMPLE_BUILD_NAME} ${example_list_build})
target_link_libraries(${EXAMPLE_BUILD_NAME}
    PUBLIC
        ${OpenCV_LIBRARIES}
)

target_include_directories(${EXAMPLE_BUILD_NAME}
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)
