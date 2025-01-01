# Defines the dup time
add_definitions(-DDUP_TIME=120)
# Define the image reading method
add_definitions(-DGray)
add_definitions(-DDiv=5)
add_executable(${EXAMPLE_BUILD_NAME} ${EXAMPLE_BUILD_NAME}.cpp)
target_link_libraries(${EXAMPLE_BUILD_NAME}
    PUBLIC
        ${OpenCV_LIBRARIES}
)

target_include_directories(${EXAMPLE_BUILD_NAME}
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)
