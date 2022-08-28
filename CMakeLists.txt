cmake_minimum_required(VERSION 3.5)

project(MyDashboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Script REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Script REQUIRED)

set(PROJECT_SOURCES
				core/types/Base.h
				core/types/List.h
				core/types/Str.h
                core/types/Str.cpp
				core/types/Vector.h
                core/utils/Singleton.h
				core/node/Node.h
				core/node/Node.cpp
				core/node/NodeFactory.h
				core/node/NodeFactory.cpp
				core/node/NodeType.h
				core/node/NodeType.cpp
				core/node/NodeTypeList.h
				core/node/NodeTypeList.cpp
				core/node/Property.h
				core/node/Property.cpp
				core/node/PropertySet.h
				core/node/PropertySet.cpp
				core/node/PropertyType.h
				core/node/PropertyType.cpp
				
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
				
				app/Utils/Log.h
                app/Utils/Log.cpp
                app/Utils/Calendar.h
				app/Utils/Calendar.cpp
				app/Utils/Workspace.h
				app/Utils/Workspace.cpp
				
				app/Nodes/NodeBase.h
				app/Nodes/NodeBase.cpp
				app/Nodes/NodeInclude.h
				app/Nodes/NodeInclude.cpp
				app/Nodes/NodeVar.h
				app/Nodes/NodeVar.cpp
				app/Nodes/Pim/NodeEvent.h
				app/Nodes/Pim/NodeEvent.cpp
				app/Nodes/Pim/NodePerson.h
				app/Nodes/Pim/NodePerson.cpp
				app/Nodes/Pim/NodeProject.h
				app/Nodes/Pim/NodeProject.cpp
				app/Nodes/Pim/NodeTask.h
				app/Nodes/Pim/NodeTask.cpp
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
				app/Gui/Views/TrivialMainWindow.h
				app/Gui/Views/TrivialMainWindow.cpp
				app/Gui/Views/TrivialTextDocument.h
				app/Gui/Views/TrivialTextDocument.cpp
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
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
else()
    if(ANDROID)
        add_library(MyDashboard SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(MyDashboard
            ${PROJECT_SOURCES}
        )
		
		
    endif()
endif()

target_link_libraries(MyDashboard PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Script)

set_target_properties(MyDashboard PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MyDashboard)
endif()
