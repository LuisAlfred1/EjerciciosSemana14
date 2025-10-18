# Requiere una versión mínima de CMake para garantizar compatibilidad con comandos usados
cmake_minimum_required(VERSION 3.20)

# Define el nombre del proyecto y el lenguaje principal (C)
project(Ejemplo1_LR1_Expresiones C)

# Estándar de C a utilizar (C11)
set(CMAKE_C_STANDARD 11)

# Busca la herramienta FLEX (scanner) en el sistema. REQUIRED hace que falle si no está.
find_package(FLEX REQUIRED)

# Busca la herramienta BISON (parser) en el sistema. REQUIRED hace que falle si no está.
find_package(BISON REQUIRED)

# Define un objetivo de Bison:
#  - Nombre lógico del target: Parser
#  - Archivo de entrada: parser.y (gramática)
#  - Archivo de salida: parser.tab.c (análisis sintáctico generado)
#  - Archivo de cabecera generado: parser.tab.h (tokens, yylval, prototipos)
BISON_TARGET(Parser
    ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
)

# Define un objetivo de Flex:
#  - Nombre lógico del target: Scanner
#  - Archivo de entrada: scanner.l (reglas léxicas)
#  - Archivo de salida: lex.yy.c (analizador léxico generado)
FLEX_TARGET(Scanner
    ${CMAKE_CURRENT_SOURCE_DIR}/scanner.l
    ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
)

# Establece la dependencia entre Flex y Bison para que CMake construya
# primero lo que corresponda y detecte cambios en orden correcto.
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

# Crea el ejecutable final del proyecto:
#  - main.c es tu punto de entrada
#  - ${BISON_Parser_OUTPUTS} expande a parser.tab.c
#  - ${FLEX_Scanner_OUTPUTS} expande a lex.yy.c
add_executable(${PROJECT_NAME}
    main.c
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Scanner_OUTPUTS}
)

# Agrega el directorio binario (build) al include path para poder
# #incluir "parser.tab.h" desde scanner.l y otros.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# Define YY_NO_UNISTD_H para evitar que el código generado por Flex
# intente incluir <unistd.h> en Windows/MSVC, donde no existe.
target_compile_definitions(${PROJECT_NAME} PRIVATE YY_NO_UNISTD_H)