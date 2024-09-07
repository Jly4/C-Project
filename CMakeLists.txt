cmake_minimum_required(VERSION 3.10)
project(C-Project)

# Найти пакеты
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Установите флаги компиляции и линковки
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

# Определите путь к файлу ресурсов
set(RESOURCE_XML ${CMAKE_SOURCE_DIR}/resources/resources.xml)
set(RESOURCE_C ${CMAKE_BINARY_DIR}/resources.c)

## Сгенерируйте файл ресурсов
#add_custom_command(
#        OUTPUT ${RESOURCE_C}
#        COMMAND cd ${CMAKE_SOURCE_DIR}/resources
#        COMMAND glib-compile-resources ${RESOURCE_XML} --target=${RESOURCE_C} --generate-source
#        DEPENDS ${RESOURCE_XML}
#        COMMENT "Generating resource file ${RESOURCE_C}"
#)

# Определите исходные файлы
set(SOURCES
        src/main.c
        ${RESOURCE_C}
        src/main.c # Добавьте сгенерированный файл ресурсов в список исходных файлов
)

# Создайте исполняемый файл
#add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})