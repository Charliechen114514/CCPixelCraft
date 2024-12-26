enable_testing()
set(GLOBAL_GTEST_DIR "D:\\vcpkg\\installed\\x64-windows\\share\\gtest")
set(GTEST_DIR ${GLOBAL_GTEST_DIR})
include_directories(${TARGET_SEARCHING_PATH})
message(${TARGET_SEARCHING_PATH})
find_package(GTest CONFIG REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test_all TestImport/tst_testlocalimport.cpp)
# 链接测试库
target_link_libraries(test_all
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

# 添加到测试
add_test(AllTestsInMain main)
