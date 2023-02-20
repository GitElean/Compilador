cmake_minium_required(VERSION 3.22)

project(Compiler VERSION 0.1)

add_executable(Compilador main.cpp)

add_subdirectory(src/compilador)

target_include_directories(${PROJECT_NAME}
  PUBLIC src/compilador
)

target_link_directories(${PROJECT_NAME}
  PRIVATE src/compilador
)

target_link_libraries(${PROJECT_NAME}
  regexToAFN
)