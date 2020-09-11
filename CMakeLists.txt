CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
Project(ConsoleApplication1)

cmake_policy(SET CMP0015 NEW)

# Set Wt include and library paths
INCLUDE_DIRECTORIES("Wt 4.3.1 msvs2019 x64/include/")
TARGET_LINK_DIRECTORIES("ConsoleApplication1 Wt 4.3.1 msvs2019 x64/lib/")
INCLUDE_DIRECTORIES("include/")

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

TARGET_LINK_LIBRARIES(ConsoleApplication1
  debug wtd.lib optimized wt.lib
  debug wthttpd.lib optimized wthttp.lib
  )
