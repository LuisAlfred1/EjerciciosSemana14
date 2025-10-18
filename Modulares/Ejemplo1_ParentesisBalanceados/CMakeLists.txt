cmake_minimum_required(VERSION 3.20)
project(ParBalanceadosMod C)

find_package(BISON 3.0 REQUIRED)
find_package(FLEX 2.6 REQUIRED)

BISON_TARGET(
        Parser
        ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
        ${CMAKE_CURRENT_BINARY_DIR}/parser.c
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
)

FLEX_TARGET(
        Scanner
        ${CMAKE_CURRENT_SOURCE_DIR}/scanner.l
        ${CMAKE_CURRENT_BINARY_DIR}/scanner.c
)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_executable(par_balanceados
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
)

target_include_directories(par_balanceados PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(par_balanceados PRIVATE YY_NO_UNISTD_H)

if(FLEX_LIBRARIES)
    target_link_libraries(par_balanceados PRIVATE ${FLEX_LIBRARIES})
endif()

if(MSVC)
    target_compile_definitions(par_balanceados PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# 💡 Nota: Parser generado con analizador LR(1) canónico
