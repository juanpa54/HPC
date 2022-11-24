cmake_minimum_required(VERSION 3.14)

project(LinealRegresion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Se crea una variable para las fuentes
set(project_sources
    main.cpp
    Extraccion/extractiondata.cpp
    Regression/linearregresion.cpp)

# Se crea una variable par alas interfaces
set(project_headers
    main.cpp
    Extraccion/extractiondata.h
    Regression/linearregresion.h)

add_executable(${PROJECT_NAME}
               ${project_sources}
               ${project_headers})

# Se debe crear una variable para agregar la
# direccion en donde se encuentre la clase
# Extraccion

#Extraccion/extraction.h
#Extraccion/extraction.cpp
