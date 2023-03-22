qt5_add_resources(UI_RESOURCES resources.qrc)

add_executable(crawlerdemo
        main.cpp
         ${UI_RESOURCES}
)

target_link_libraries(crawlerdemo
        Qt5::Quick
        Qt5::Qml
        Qt5::Gui
        SiteCrawler
    )
set_target_properties(crawlerdemo PROPERTIES AUTOMOC ON)
