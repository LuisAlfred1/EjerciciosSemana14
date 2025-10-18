cmake_minimum_required(VERSION 3.16)
project(parser_expr C)

# --- Buscar módulos de Flex y Bison ---
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# --- Especificar las rutas de win_flex y win_bison (ajusta si es necesario) ---
set(FLEX_EXECUTABLE "C:/msys64/mingw64/bin/win_flex.exe")
set(BISON_EXECUTABLE "C:/msys64/mingw64/bin/win_bison.exe")

# --- Generar scanner y parser ---
FLEX_TARGET(Scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.c COMPILE_FLAGS "--wincompat")
BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/parser.h")
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

# --- Crear el ejecutable ---
add_executable(parser_expr
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
        main.c
)

# --- Incluir cabeceras generadas ---
target_include_directories(parser_expr PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# --- Configuración general ---
set_target_properties(parser_expr PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED ON
)
