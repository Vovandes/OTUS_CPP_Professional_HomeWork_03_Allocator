cmake_minimum_required(VERSION 3.23)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(my_allocator VERSION ${PROJECT_VERSION})

option(WITH_GTEST "Whether to build Google test" ON)

configure_file(include/version.hpp.in version.hpp)
include_directories(${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(my_allocator_cli src/main.cpp)

add_library(my_allocator src/custom_allocator.cpp)

# Add source to the include directories for the test target
target_include_directories(my_allocator PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_include_directories(my_allocator PRIVATE "${CMAKE_BINARY_DIR}")

set_target_properties(my_allocator_cli my_allocator PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(my_allocator_cli PRIVATE
    my_allocator
)

if(WITH_GTEST)
    find_package(GTest REQUIRED)
    enable_testing()

    add_executable(test_allocator_gtest tests/test_gtest.cpp)

    set_target_properties(test_allocator_gtest PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(test_allocator_gtest
	    GTest::gtest_main
        my_allocator
    )

    gtest_discover_tests(test_allocator_gtest)
endif()

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")
endif()

install(TARGETS my_allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT akms@bk.ru)
include(CPack)