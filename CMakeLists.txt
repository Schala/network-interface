project (cmmnet)
cmake_minimum_required (VERSION 3.18)

list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package (Boost REQUIRED)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

option (BUILD_SERVER "Build server targets" ON)
option (BUILD_KDX "Build the KDX module" ON)
option (BUILD_PALACE "Build the Palace module" ON)
option (SQLITE_FRONTEND "Build the SQLite frontend" ON)
option (MYSQL_FRONTEND "Build the MySQL/MariaDB frontend" OFF)
option (BUILD_TESTS "Build tests" ON)

if (BUILD_PALACE OR BUILD_KDX)
	set (SQLITE_FRONTEND ON)
endif ()

if (BUILD_PALACE AND BUILD_SERVER)
	find_package (OpenSSL REQUIRED)
endif ()

if (SQLITE_FRONTEND)
	find_package (SQLite3 REQUIRED)
endif ()

if (MYSQL_FRONTEND)
	find_package (MariaDBClient REQUIRED)
endif ()

add_subdirectory (src)
add_subdirectory (test)
