include(FetchContent)

# Fetch Catch2
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.4 # Replace with latest if needed
)
FetchContent_MakeAvailable(catch2)

# Build test binary
add_executable(test_tuple test_tuple.cpp)
target_link_libraries(test_tuple PRIVATE math Catch2::Catch2WithMain)

# Add to ctest
include(CTest)
include(Catch)
catch_discover_tests(test_tuple)
