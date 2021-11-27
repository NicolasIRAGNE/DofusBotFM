include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(DBFTests)

target_sources(
    DBFTests
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/FMTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ItemTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/RunePropertiesTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/StatsDensityTest.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/StatsRunesTest.cpp"
        
        "${CMAKE_CURRENT_SOURCE_DIR}/Mock/MockRuneApplication.h")

target_link_libraries(DBFTests DBFLib gtest_main gmock_main)
set_property(TARGET DBFTests PROPERTY DBFLib_PRIVATE_HEADERS 1)

gtest_discover_tests(DBFTests)
