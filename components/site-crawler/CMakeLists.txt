cmake_minimum_required(VERSION 3.16)
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Gui)

add_library(SiteCrawler)

target_sources(SiteCrawler
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/SiteCrawler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SiteCrawler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/SiteCrawlerModel.h
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SiteCrawlerModel.cpp
    )

set_target_properties(SiteCrawler
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        AUTOMOC TRUE
)

target_include_directories(SiteCrawler
    PUBLIC
        "include"
)

target_link_libraries(SiteCrawler
    PRIVATE
        Qt5::Core
        Qt5::Gui
)



