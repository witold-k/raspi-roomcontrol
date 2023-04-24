cmake_minimum_required (VERSION 3.10)
project (raspi_roomcontrol)

include(GNUInstallDirs)
enable_testing()

add_subdirectory(sensor-data)
add_subdirectory(raspi-sensor)
add_subdirectory(room-datatransfer)
