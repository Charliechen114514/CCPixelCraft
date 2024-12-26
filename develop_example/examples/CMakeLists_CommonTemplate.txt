add_executable(${EXAMPLE_BUILD_NAME} ${EXAMPLE_BUILD_NAME}.cpp)
target_link_libraries(${EXAMPLE_BUILD_NAME}
    PUBLIC
        ${OpenCV_LIBRARIES}
)

target_include_directories(${EXAMPLE_BUILD_NAME}
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)
