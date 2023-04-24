cmake_minimum_required (VERSION 3.10)
project (raspi_roomcontrol)


include(GNUInstallDirs)
enable_testing()

find_package(Alloc     REQUIRED)
find_package(Container REQUIRED)
find_package(Realtime  REQUIRED)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_path(WIRINGPI_INCLUDE_DIRS NAMES wiringPi.h)

#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(WiringPi DEFAULT_MSG WIRINGPI_LIBRARIES WIRINGPI_INCLUDE_DIRS)
#message(WIRINGPI_INCLUDE_DIRS="${WIRINGPI_INCLUDE_DIRS}")
#message(WIRINGPI_LIBRARIES="${WIRINGPI_LIBRARIES}")


if (DEFINED CMAKE_TARGET_SYSTEM_IS_NATIVE)
find_package(GTest    REQUIRED)
endif()
#find_package(WiringPi QUIET)
if("${WIRINGPI_LIBRARIES}" STREQUAL "WIRINGPI_LIBRARIES-NOTFOUND")
    message("WiringPi: not found")
    set(NO_SENSOR 1)
endif()

set (HEADER_SRC
  include/raspi_sensor
  src/DHT_11_22.hpp
  src/raspi_sensor_common.h
)


set (SRC
  src/DHT_11_22.cpp
)


add_library(raspi-sensor SHARED ${SRC})
if(DEFINED NO_SENSOR)
  target_compile_definitions(raspi-sensor PUBLIC -DNO_SENSOR=1)
endif()
target_include_directories(raspi-sensor PUBLIC ../sensor-data/src
    ${ALLOC_INCLUDE_DIRS}
    ${CONTAINER_INCLUDE_DIRS}
    ${REALTIME_INCLUDE_DIRS}
)
if(NOT DEFINED NO_SENSOR)
    target_link_libraries(raspi-sensor wiringPi
        ${REALTIME_LIBRARIES}
        ${CONTAINER_LIBRARIES}
        ${ALLOC_LIBRARIES}
    )
else()
    target_link_libraries(raspi-sensor
        ${REALTIME_LIBRARIES}
        ${CONTAINER_LIBRARIES}
        ${ALLOC_LIBRARIES}
    )
endif()

add_executable(sensortest main/sensortest.cpp)
target_include_directories(sensortest PUBLIC include ../sensor-data/src
    ${ALLOC_INCLUDE_DIRS}
    ${CONTAINER_INCLUDE_DIRS}
    ${REALTIME_INCLUDE_DIRS}
)
target_link_libraries(sensortest raspi-sensor
    ${REALTIME_LIBRARIES}
    ${CONTAINER_LIBRARIES}
    ${ALLOC_LIBRARIES}
)


set_target_properties(raspi-sensor
  PROPERTIES
  FRAMEWORK     TRUE
  PUBLIC_HEADER "${HEADER_SRC}"
)


if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

install(TARGETS raspi-sensor
  LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/raspi-sensor
)

endif (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
