add_executable(linalg_sandbox_test
    catch_main.cpp
    catch_matrix.cpp
    catch_householder.cpp
)
target_include_directories(linalg_sandbox_test PRIVATE ../src)
target_compile_features(linalg_sandbox_test PRIVATE cxx_std_17)

find_package(Catch2 REQUIRED)

target_link_libraries(linalg_sandbox_test
    PRIVATE
        Catch2::Catch2
        linalg_sandbox
)
add_test(linalg_sandbox_test COMMAND linalg_sandbox_test)
