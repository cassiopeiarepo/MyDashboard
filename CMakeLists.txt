cmake_minimum_required(VERSION 3.5)

project(MyDashboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 COMPONENTS Widgets Network Multimedia MultimediaWidgets Qml REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Multimedia MultimediaWidgets Qml REQUIRED)

set(PROJECT_SOURCES				
				coreqt/Common/Tml.h
				coreqt/Common/Tml.cpp
				coreqt/Common/TmlDef.h
				coreqt/Common/TmlDef.cpp
				coreqt/Common/TmlPreprocessor.h
				coreqt/Common/TmlPreprocessor.cpp
				coreqt/Utils/QStringUtils.h
				coreqt/Utils/QStringUtils.cpp
				coreqt/Utils/Tags.h
				coreqt/Utils/Tags.cpp
				coreqt/Utils/Singleton.h
				
				app/Utils/Log.h
                app/Utils/Log.cpp
                app/Utils/Calendar.h
				app/Utils/Calendar.cpp
				app/Utils/Script.h
				app/Utils/Script.cpp
				app/Utils/Workspace.h
				app/Utils/Workspace.cpp
				app/Utils/TypeDef.h
				app/Utils/TypeDef.cpp
                app/Utils/Gui.h
                app/Utils/Gui.cpp
				app/Utils/SceneUtils.h
				app/Utils/SceneUtils.cpp
				app/Utils/GitHubRepoSync/GitHubRepoSync.h
				app/Utils/GitHubRepoSync/GitHubRepoSync.cpp
				
				
				app/Nodes/UI/NodeUi.h
				app/Nodes/UI/NodeUi.cpp
				app/Nodes/UI/NodeQWidget.h
				app/Nodes/UI/NodeQWidget.cpp
				app/Nodes/UI/NodeQLabel.h
				app/Nodes/UI/NodeQLabel.cpp
				app/Nodes/UI/NodeQPushButton.h
				app/Nodes/UI/NodeQPushButton.cpp
				app/Nodes/UI/NodeQTextEdit.h
				app/Nodes/UI/NodeQTextEdit.cpp
				app/Nodes/UI/NodeQWindow.h
				app/Nodes/UI/NodeQWindow.cpp
				
				app/Nodes/Document/NodeDocumentFileType.h
				app/Nodes/Document/NodeDocumentFileType.cpp
				app/Nodes/NodeBase.h
				app/Nodes/NodeBase.cpp
				app/Nodes/NodeInclude.h
				app/Nodes/NodeInclude.cpp
				app/Nodes/NodeVar.h
				app/Nodes/NodeVar.cpp
				app/Nodes/NodePanel.h
				app/Nodes/NodePanel.cpp
				app/Nodes/Pim/NodeEvent.h
				app/Nodes/Pim/NodeEvent.cpp
				app/Nodes/Pim/NodePerson.h
				app/Nodes/Pim/NodePerson.cpp
				app/Nodes/Pim/NodeProject.h
				app/Nodes/Pim/NodeProject.cpp
				app/Nodes/Pim/NodeTask.h
				app/Nodes/Pim/NodeTask.cpp
				app/Nodes/Basic/NodeText.h
				app/Nodes/Basic/NodeText.cpp
				app/Nodes/Basic/NodeHeading1.h
				app/Nodes/Basic/NodeHeading1.cpp
				app/Nodes/Basic/NodeHeading2.h
				app/Nodes/Basic/NodeHeading2.cpp
				app/Nodes/Basic/NodeHeading3.h
				app/Nodes/Basic/NodeHeading3.cpp
				app/Nodes/Basic/NodeLink.h
				app/Nodes/Basic/NodeLink.cpp
				app/Nodes/Media/NodeImage.h
				app/Nodes/Media/NodeImage.cpp
				app/Nodes/Media/NodeVideo.h
				app/Nodes/Media/NodeVideo.cpp
				app/Nodes/Media/NodeAudio.h
				app/Nodes/Media/NodeAudio.cpp
				
				app/Nodes/TmlDef/NodeTmlDef.h
				app/Nodes/TmlDef/NodeTmlDef.cpp
				app/Nodes/TmlDef/NodeTmlNodeDef.h
				app/Nodes/TmlDef/NodeTmlNodeDef.cpp
				app/Nodes/TmlDef/NodeTmlNodeDefArg.h
				app/Nodes/TmlDef/NodeTmlNodeDefArg.cpp
				app/Nodes/TmlDef/NodeTmlNodeDefChild.h
				app/Nodes/TmlDef/NodeTmlNodeDefChild.cpp
				app/Nodes/TmlDef/NodeTmlTypeDefEnum.h
				app/Nodes/TmlDef/NodeTmlTypeDefEnum.cpp
				app/Nodes/TmlDef/NodeTmlTypeDefRef.h
				app/Nodes/TmlDef/NodeTmlTypeDefRef.cpp
				app/Nodes/TmlDef/NodeTmlTypeDefRegex.h
				app/Nodes/TmlDef/NodeTmlTypeDefRegex.cpp
				
				app/Gui/Widgets/TrivialSceneWidget.h
				app/Gui/Widgets/TrivialSceneWidget.cpp
				app/Gui/Widgets/TrivialSceneTreeWidget.h
				app/Gui/Widgets/TrivialSceneTreeWidget.cpp
				app/Gui/Widgets/TrivialQObjectPropertyWidget.h
				app/Gui/Widgets/TrivialQObjectPropertyWidget.cpp
				app/Gui/Widgets/TrivialAudioPlayerWidget.h
				app/Gui/Widgets/TrivialAudioPlayerWidget.cpp
				app/Gui/Widgets/TrivialVideoPlayerWidget.h
				app/Gui/Widgets/TrivialVideoPlayerWidget.cpp
				app/Gui/Widgets/TrivialCommonNodesWidget.h
				app/Gui/Widgets/TrivialCommonNodesWidget.cpp
				app/Gui/Widgets/TrivialNewNodeWidget.h
				app/Gui/Widgets/TrivialNewNodeWidget.cpp
				
				
                app/Gui/Views/TrivialTextEditor.h
                app/Gui/Views/TrivialTextEditor.cpp
				app/Gui/Views/TrivialGraphicsView.h
                app/Gui/Views/TrivialGraphicsView.cpp
				app/Gui/Views/TrivialGraphicsItem.h
				app/Gui/Views/TrivialGraphicsItem.cpp
				app/Gui/Views/TrivialGuiItems.h
				app/Gui/Views/TrivialGuiItems.cpp
				app/Gui/Views/TrivialTextItem.h
                app/Gui/Views/TrivialTextItem.cpp
				app/Gui/Views/TrivialDirExplorer.h
				app/Gui/Views/TrivialDirExplorer.cpp
				app/Gui/Views/TrivialDocumentsView.h
				app/Gui/Views/TrivialDocumentsView.cpp

				app/Gui/Views/TrivialTextDocument.h
				app/Gui/Views/TrivialTextDocument.cpp
				app/Gui/Views/TrivialScriptView.h
				app/Gui/Views/TrivialScriptView.cpp
				app/Gui/Views/TrivialLogView.h
				app/Gui/Views/TrivialLogView.cpp
				app/Gui/Views/TrivialSceneView.h
				app/Gui/Views/TrivialSceneView.cpp
				app/Gui/Views/TrivialSceneTreeView.h
				app/Gui/Views/TrivialSceneTreeView.cpp
				app/Gui/Views/TrivialObjectTreePropView.h
				app/Gui/Views/TrivialObjectTreePropView.cpp
				app/Gui/Views/TrivialMainView.h
				app/Gui/Views/TrivialMainView.cpp
				app/Gui/Views/TrivialSignalSlotView.h
				app/Gui/Views/TrivialSignalSlotView.cpp
				
				app/Gui/Windows/TrivialMainWindow.h
				app/Gui/Windows/TrivialMainWindow.cpp
				app/Gui/Windows/TrivialMiniWindow.h
				app/Gui/Windows/TrivialMiniWindow.cpp
				app/Gui/Windows/TrivialQObjectPropertyWindow.h
				app/Gui/Windows/TrivialQObjectPropertyWindow.cpp
				app/Gui/Windows/TrivialNewNodeWindow.h
				app/Gui/Windows/TrivialNewNodeWindow.cpp
				
				
				app/Gui/PropertyWidgets/ITrivialPropertyWidget.h
				app/Gui/PropertyWidgets/NodePropTest.h
				app/Gui/PropertyWidgets/NodePropTest.cpp
				app/Gui/PropertyWidgets/TrivialIntPropertyWidget.h
				app/Gui/PropertyWidgets/TrivialIntPropertyWidget.cpp
				app/Gui/PropertyWidgets/TrivialStringPropertyWidget.h
				app/Gui/PropertyWidgets/TrivialStringPropertyWidget.cpp
				app/Gui/PropertyWidgets/TrivialBoolPropertyWidget.h
				app/Gui/PropertyWidgets/TrivialBoolPropertyWidget.cpp
				app/Gui/PropertyWidgets/TrivialFloatPropertyWidget.h
				app/Gui/PropertyWidgets/TrivialFloatPropertyWidget.cpp
				app/Gui/PropertyWidgets/TrivialDoublePropertyWidget.h
				app/Gui/PropertyWidgets/TrivialDoublePropertyWidget.cpp
				app/Gui/PropertyWidgets/TrivialQDateTimePropertyWidget.h
				app/Gui/PropertyWidgets/TrivialQDateTimePropertyWidget.cpp
				app/Gui/PropertyWidgets/TrivialQTimePropertyWidget.h
				app/Gui/PropertyWidgets/TrivialQTimePropertyWidget.cpp
				app/Gui/PropertyWidgets/TrivialQDatePropertyWidget.h
				app/Gui/PropertyWidgets/TrivialQDatePropertyWidget.cpp
				
				app/Gui/SceneWidgets/ITrivialSceneWidget.h
				app/Gui/SceneWidgets/TrivialSceneNodeTextWidget.h
				app/Gui/SceneWidgets/TrivialSceneNodeTextWidget.cpp
				app/Gui/SceneWidgets/TrivialSceneNodeHeading1Widget.h
				app/Gui/SceneWidgets/TrivialSceneNodeHeading1Widget.cpp
				app/Gui/SceneWidgets/TrivialSceneNodeHeading2Widget.h
				app/Gui/SceneWidgets/TrivialSceneNodeHeading2Widget.cpp
				app/Gui/SceneWidgets/TrivialSceneNodeHeading3Widget.h
				app/Gui/SceneWidgets/TrivialSceneNodeHeading3Widget.cpp
				app/Gui/SceneWidgets/TrivialSceneNodeLinkWidget.h
				app/Gui/SceneWidgets/TrivialSceneNodeLinkWidget.cpp
				
				app/Gui/SceneWidgets/TrivialSceneNodeImageWidget.h
				app/Gui/SceneWidgets/TrivialSceneNodeImageWidget.cpp
				app/Gui/SceneWidgets/TrivialSceneNodeVideoWidget.h
				app/Gui/SceneWidgets/TrivialSceneNodeVideoWidget.cpp
				app/Gui/SceneWidgets/TrivialSceneNodeAudioWidget.h
				app/Gui/SceneWidgets/TrivialSceneNodeAudioWidget.cpp
				
				
				
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        resource.qrc
)





source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


#set(CMAKE_PREFIX_PATH D:/Projekty/cpp/vcpkg/packages/zlib_x86-windows)
#set(CMAKE_PREFIX_PATH D:/Projekty/cpp/vcpkg/packages/curl_x86-windows)


#	FIND_PACKAGE(ZLIB QUIET)

#	IF (ZLIB_FOUND)
		#ADD_DEFINITIONS(-DZLIB_FOUND)
    
#		MESSAGE(STATUS "Cmake FindZLIB: using ZLIB includes at: ${ZLIB_INCLUDE_DIR}")
#    	MESSAGE(STATUS "Cmake FindZLIB: using ZLIB libraries: ${ZLIB_LIBRARIES}")

#		SET(PROG_LIBS   ${PLATFORM_LIBS} ${ZLIB_LIBRARIES} )
#		INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})	
	
#	ELSE(ZLIB_FOUND)
#		SET(ZLIB_LIBRARIES "")
#	ENDIF (ZLIB_FOUND)
	
	
#	FIND_PACKAGE(CURL QUIET)

#	IF (CURL_FOUND)
		#ADD_DEFINITIONS(-DZLIB_FOUND)
    
#		MESSAGE(STATUS "Cmake FindCURL: using ZLIB includes at: ${CURL_INCLUDE_DIR}")
#    	MESSAGE(STATUS "Cmake FindCURL: using ZLIB libraries: ${CURL_LIBRARIES}")

#		SET(PROG_LIBS   ${PLATFORM_LIBS} ${CURL_LIBRARIES} )
#		INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})	
	
#	ELSE(CURL_FOUND)
#		SET(CURL_LIBRARIES "")
#	ENDIF (CURL_FOUND)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MyDashboard
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TestAndroid APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MyDashboard SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MyDashboard
            ${PROJECT_SOURCES}
        )
    endif()
endif()

#include_directories(D:/Projekty/Qt/qmqtt-master/src/mqtt)
#target_link_libraries(MyDashboard PRIVATE D:/Projekty/Qt/qmqtt-master-build64/Debug/qmqtt.lib)

#include_directories("C:/Program Files (x86)/Mono/include/mono-2.0")
#target_link_libraries(MyDashboard PRIVATE "C:/Program Files (x86)/Mono/lib/mono-2.0-sgen.lib")

#link_directories(D:/Projekty/Qt/qmqtt-master-build/Debug)

target_link_libraries(MyDashboard PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets Qt${QT_VERSION_MAJOR}::Qml)

set_target_properties(MyDashboard PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS MyDashboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MyDashboard)
endif()
