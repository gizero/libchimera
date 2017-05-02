cmake_minimum_required(VERSION 2.8.7)
project(libchimera)

set(LIBCHIMERA_VERSION_MAJOR 0)
set(LIBCHIMERA_VERSION_MINOR 1)
set(LIBCHIMERA_VERSION_BUGFIX 0)
set(VERSION "${LIBCHIMERA_VERSION_MAJOR}.${LIBCHIMERA_VERSION_MINOR}.${LIBCHIMERA_VERSION_BUGFIX}")

include(GNUInstallDirs)

# Get the GIT hash of the latest commit
include(FindGit OPTIONAL)
if (GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --show-toplevel
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE LIBCHIMERA_GIT_REPO
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if (${LIBCHIMERA_GIT_REPO} MATCHES ${CMAKE_CURRENT_SOURCE_DIR})
        execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            OUTPUT_VARIABLE LIBCHIMERA_VERSION_GIT
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    endif()
endif()

if (NOT LIBCHIMERA_VERSION_GIT)
    set(LIBCHIMERA_VERSION_GIT v${VERSION})
endif()

#replace this stuff with libsystemd
#find_library(LIBUSB_LIBRARIES usb-1.0)
#find_path(LIBUSB_INCLUDE_DIR libusb-1.0/libusb.h)
#if (LIBUSB_LIBRARIES AND LIBUSB_INCLUDE_DIR)
#    option(WITH_USB_BACKEND "Enable the libusb backend" ON)
#
#    if(WITH_USB_BACKEND)
#        add_definitions(-DUSB_BACKEND=1)
#        set(LIBCHIMERA_CFILES ${LIBCHIMERA_CFILES} usb.c)
#        set(LIBS_TO_LINK ${LIBS_TO_LINK} ${LIBUSB_LIBRARIES})
#        set(CHIMERAD_CLIENT 1)
#        set(NEED_LIBXML2 1)
#        set(NEED_THREADS 1)
#
#        include_directories(${LIBUSB_INCLUDE_DIR})
#    endif()
#endif()

set(LIBCHIMERA_CFILES log.c)
set(LIBCHIMERA_HEADERS log.h)

add_library(chimera ${LIBCHIMERA_CFILES} ${LIBCHIMERA_HEADERS})
set_target_properties(chimera PROPERTIES
    VERSION ${VERSION}
    SOVERSION ${LIBCHIMERA_VERSION_MAJOR}
    PUBLIC_HEADER ${LIBCHIMERA_HEADERS}
)
#    FRAMEWORK TRUE
#    C_STANDARD 99
#    C_STANDARD_REQUIRED ON
#    C_EXTENSIONS OFF
target_link_libraries(chimera LINK_PRIVATE ${LIBS_TO_LINK})

install(TARGETS chimera
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_file(config.h.cmakein ${CMAKE_CURRENT_BINARY_DIR}/config.h)
