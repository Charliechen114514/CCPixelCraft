# Some Utils functions that requires in using
function(add_example_subdirectory EXAMPLE_NAME)
    set(EXAMPLE_BUILD_NAME ${EXAMPLE_NAME})
    add_subdirectory(${EXAMPLE_NAME})
endfunction()

function(configuring_common_example_srclist srclist)
    list(APPEND ${srclist} ${EXAMPLE_COMMON_SRC})
    set(${srclist} ${${srclist}} PARENT_SCOPE)
endfunction()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Configuring Common Example Build configurations
set(EXAMPLE_COMMON_PATH ${CMAKE_SOURCE_DIR}/develop_example/examples)
set(EXAMPLE_COMMON_SRC ${EXAMPLE_COMMON_PATH}/example_common.cpp)
configure_file(example_common.h.in ${CMAKE_CURRENT_BINARY_DIR}/example_common.h)

# Examples sub building
# Following examples follow the common build, so do the copy file
# as direct

# 确保这里是正确的列表格式
set(EXAMPLES_LISTS beginners basic_usage imread cvtcolor)  # 定义一个包含多个元素的列表
foreach(each_build_sub ${EXAMPLES_LISTS})
    add_example_subdirectory(${each_build_sub})
endforeach()




