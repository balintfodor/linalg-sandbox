add_library(linalg_sandbox
    matrix.cpp
    householder.cpp
)

target_compile_features(linalg_sandbox PRIVATE cxx_std_17)
target_link_libraries(linalg_sandbox)
