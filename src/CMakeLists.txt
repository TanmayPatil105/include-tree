set(SOURCES
    main.c
    header.c
    set.c
    utils.c
    args.c
    log.c
)

set (CMAKE_C_COMPILER gcc)
set (CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(itree ${SOURCES})

install(TARGETS itree DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
