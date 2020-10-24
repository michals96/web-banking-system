CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
Project(ConsoleApplication1)

#cmake_policy(SET CMP0015 NEW)

# If Visual Studio IDE
IF(MSVC_IDE)
	# Copy user file
  FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.vcxproj.user DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDIF(MSVC_IDE)

# If Eclipse IDE
IF(${CMAKE_EXTRA_GENERATOR} MATCHES ".*Eclipse.*")
	IF(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		# Copy debug user file
    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}-debug.exe.launch DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	ENDIF()
	IF(${CMAKE_BUILD_TYPE} STREQUAL "Release")
		# Copy release user file
    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}-release.exe.launch DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	ENDIF()
ENDIF()

# Copy resources to build tree
# FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

SET(ConsoleApplication1_SRC src/Main.cpp)

# If Visual Studio IDE
IF(MSVC_IDE)
	SET(ConsoleApplication1_SRC ${ConsoleApplication1_SRC} src/Main.cpp)
ENDIF(MSVC_IDE)

ADD_EXECUTABLE(ConsoleApplication1 ${ConsoleApplication1_SRC})

ADD_SUBDIRECTORY("wt-4.3.1/" "Wt 4.3.1 msvs2019 x64/lib/")
# Set Wt include and library paths
INCLUDE_DIRECTORIES("Wt 4.3.1 msvs2019 x64/include/")

INCLUDE_DIRECTORIES("include")
FILE(GLOB SOURCES "src/*.cpp")
ADD_EXECUTABLE(ConsoleApplication1 ${SOURCES})
TARGET_LINK_DIRECTORIES(ConsoleApplication1 PUBLIC "Wt 4.3.1 msvs2019 x64/lib/")

TARGET_LINK_LIBRARIES(ConsoleApplication1
  debug wtd optimized wt
  debug wthttpd optimized wthttp
  debug wtdbod optimized wtdbo
  debug wtdbosqlite3d optimized wtdbosqlite3
  )

enable_testing()
add_subdirectory("Test/" "Test/out"/)