cmake_minimum_required (VERSION 3.10)
project (room-datatransfer)


include(GNUInstallDirs)
enable_testing()

find_package(Alloc     REQUIRED)
find_package(Container REQUIRED)
find_package(Realtime  REQUIRED)

find_package(LIBUV REQUIRED)
if (DEFINED CMAKE_TARGET_SYSTEM_IS_NATIVE)
find_package(GTest    REQUIRED)
endif()


set (HEADER_SRC
  src/Message.h
  src/uvclient.h
  src/uvserver.h
)


set (SRC
  src/uvclient.cpp
  src/uvserver.cpp
)


add_library(room-datatransfer SHARED STATIC ${SRC})
target_include_directories(room-datatransfer
    PUBLIC
    ${LIBUV_INCLUDE_DIRS}
    ${ALLOC_INCLUDE_DIRS}
    ${CONTAINER_INCLUDE_DIRS}
    ${REALTIME_INCLUDE_DIRS}
    ../sensor-data/src
)
target_include_directories(room-datatransfer
  PUBLIC
  ${ALLOC_INCLUDE_DIRS}
  ${REALTIME_INCLUDE_DIRS}
)
target_link_libraries(room-datatransfer raspi-sensor sensor-data
    ${LIBUV_LIBRARIES}
    ${REALTIME_LIBRARIES}
    ${CONTAINER_LIBRARIES}
    ${ALLOC_LIBRARIES}
)
set_target_properties(room-datatransfer PROPERTIES
  COMPILE_FLAGS "-ggdb"
)

add_executable(roomstatereceiver main/RoomStateReceiver.c)
target_include_directories(roomstatereceiver PUBLIC ../sensor-data/src
  ${ALLOC_INCLUDE_DIRS}
  ${REALTIME_INCLUDE_DIRS}
)
target_link_libraries(roomstatereceiver room-datatransfer)

add_executable(roomstatesender main/RoomStateSender.c)
target_include_directories(roomstatesender PUBLIC ../sensor-data/src
  ${ALLOC_INCLUDE_DIRS}
  ${CONTAINER_INCLUDE_DIRS}
  ${REALTIME_INCLUDE_DIRS}
)
target_link_libraries(roomstatesender room-datatransfer sensor-data)
set_target_properties(roomstatesender PROPERTIES
  COMPILE_FLAGS "-ggdb"
)

set_target_properties(room-datatransfer
  PROPERTIES
  FRAMEWORK     TRUE
  PUBLIC_HEADER "${HEADER_SRC}"
)


if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

install(TARGETS room-datatransfer
  LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/room-datatransfer
)

endif (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
