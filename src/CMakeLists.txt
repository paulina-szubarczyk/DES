cmake_minimum_required(VERSION 2.8)

project( des )

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_COMPILER_FLAGS} -std=c++11)

add_definitions ("-Wall") 

find_package( Boost 1.54 COMPONENTS system unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(SOURCES 
    DES.cpp
    ExpansionFunction.cpp
    FeistelFunction.cpp
    FeistelPermutation.cpp
    FinalPermutation.cpp
    InitialPermutation.cpp
    Permutation.cpp
    SBoxes.cpp 
    SubkeyGenerator.cpp
    utils.cpp)

add_executable(exe ${SOURCES} main.cpp)
add_executable(test ${SOURCES} test.cpp)
add_executable(signate ${SOURCES} signature.cpp)
#add_executable(verifie ${SOURCES} verifier.cpp)

target_link_libraries(exe ${Boost_LIBRARIES})
target_link_libraries(test ${Boost_LIBRARIES})
target_link_libraries(signate ${Boost_LIBRARIES})
#target_link_libraries(verifie ${Boost_LIBRARIES})


