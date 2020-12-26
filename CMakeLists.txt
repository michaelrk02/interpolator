cmake_minimum_required(VERSION 3.0)

project("interpolator")

set(src_names
    "Bitmap"
    "Canvas"
    "Color"
    "NewtonPolynomial"

    "main"
)

set(src_files)
foreach(src_name IN LISTS src_names)
    set(src_files ${src_files} "${CMAKE_CURRENT_SOURCE_DIR}/src/${src_name}.cpp")
endforeach(src_name)

add_executable(${PROJECT_NAME} ${src_files})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

