cmake_minimum_required(VERSION 3.20) # Минимальная версия CMake

# Название проекта
project(GeometricFigures LANGUAGES CXX)

# Устанавливаем стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настраиваем флаги компилятора (опционально, но полезно)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# Список исходных файлов
set(SOURCES
        main.cpp
        Figures.cpp
)

# Список заголовочных файлов (для IDE)
set(HEADERS
        Point.h
        Figure.h
        Figures.h
        Array.h
)

# Определяем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Указываем, что исполняемый файл зависит от заголовочных файлов
target_sources(${PROJECT_NAME} PRIVATE ${HEADERS})

