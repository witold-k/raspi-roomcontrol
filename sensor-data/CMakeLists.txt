cmake_minimum_required (VERSION 3.10)
project (raspi_roomcontrol)


include(GNUInstallDirs)
enable_testing()


find_package(Alloc     REQUIRED)
find_package(Container REQUIRED)
find_package(Realtime  REQUIRED)


if (DEFINED CMAKE_TARGET_SYSTEM_IS_NATIVE)
find_package(GTest    REQUIRED)
endif()
include(GoogleTest)

set (HEADER_SRC
  include/sensor_data
  src/Fixed.hpp
  src/Time.hpp
  src/UInt32.hpp
  src/UInt64.hpp
  src/sensor_data_common.h
)


set (SRC
  src/DataSetHistory.cpp
)


add_library(sensor-data SHARED STATIC ${SRC})
target_link_libraries(sensor-data
    ${REALTIME_LIBRARIES}
    ${CONTAINER_LIBRARIES}
    ${ALLOC_LIBRARIES}
)
target_include_directories(sensor-data
    PUBLIC
    ${ALLOC_INCLUDE_DIRS}
    ${CONTAINER_INCLUDE_DIRS}
    ${REALTIME_INCLUDE_DIRS}
)
set_target_properties(sensor-data
  PROPERTIES
  FRAMEWORK     TRUE
  PUBLIC_HEADER "${HEADER_SRC}"
)


if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

install(TARGETS sensor-data
  LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sensor-data
)

endif (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")


if (DEFINED CMAKE_TARGET_SYSTEM_IS_NATIVE)
  add_executable(sensor_test
    test/FixedTest.cpp
    test/DataSetTest.cpp
    )
  if(DEFINED NO_SENSOR)
    target_compile_definitions(sensor_test PUBLIC -DNO_SENSOR=1)
  endif()

  target_include_directories(sensor_test
    PUBLIC
    ${ALLOC_INCLUDE_DIRS}
    ${CONTAINER_INCLUDE_DIRS}
    ${REALTIME_INCLUDE_DIRS}
  )

  target_link_libraries(sensor_test sensor-data GTest::gtest_main GTest::gtest pthread)
  add_test(sensor_test sensor_test)
endif()
