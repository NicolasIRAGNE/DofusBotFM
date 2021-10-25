include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(${PROJECT_NAME}Tests)

target_sources(
    ${PROJECT_NAME}Tests
    PRIVATE
        "ItemTest.cpp"
        "RunePropertiesTest.cpp"
        "StatsDensityTest.cpp")

target_link_libraries(${PROJECT_NAME}Tests ${PROJECT_NAME}Lib gtest_main)
set_property(TARGET ${PROJECT_NAME}Tests PROPERTY ${PROJECT_NAME}Lib_PRIVATE_HEADERS 1)

gtest_discover_tests(${PROJECT_NAME}Tests)
