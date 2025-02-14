cmake_minimum_required(VERSION 3.30)

project(calculator)

add_executable(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME}
    PUBLIC    
    calculator.cpp
    calc.lexer.cc
    calc.parser.cc    
    main.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../winflexbison/out/install/x64"        
)

target_compile_definitions(
    ${PROJECT_NAME}
    PUBLIC
    YY_NO_UNISTD_H    
)

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC
    /wd4005
)