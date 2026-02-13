cmake_minimum_required(VERSION 3.19)
project(Simpato LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Simpato
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/main_window.cpp
    src/main_window.h
    src/main_window.ui
    src/item_view.ui
    src/item_view.h
    src/item_view.cpp
    src/note_view.ui
    src/note_view.h
    src/note_view.cpp

)

target_include_directories(Simpato PUBLIC src)

target_link_libraries(Simpato
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Simpato
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Simpato
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

