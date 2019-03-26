cmake_minimum_required(VERSION 3.0)

project(RayTracer)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE PATH "cmake install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

if(MSVC)
  set(CMAKE_DEBUG_POSTFIX "d")
else()
  set(CMAKE_DEBUG_POSTFIX "")
endif()



###################### OpenMP ####################
option(WITH_OPENMP "Enable OpenMP support?" ON)
if(WITH_OPENMP)
 find_package(OpenMP REQUIRED)
 if(OPENMP_FOUND)
     if(APPLE)
         if(CMAKE_C_COMPILER_ID MATCHES "Clang")
             set(OpenMP_C "${CMAKE_C_COMPILER}")
             set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
             set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
             set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
             set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
             set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
         endif()
         if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
             set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
             set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
             set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
             set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
             set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
             set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})
         endif()
     elseif(MSVC)
         set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
     endif()
 endif()
 add_definitions(-DWITH_OPENMP)
endif()

####################### header-only dependencies ###################

set(EIGEN3_INCLUDE_DIR "EIGEN3-NOT-FOUND" CACHE PATH "Eigen3 include dir")
include_directories(${EIGEN3_INCLUDE_DIR})

####################### add library #########################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(ImageIO include/ImageIO.h src/ImageIO.cpp)

set(RAYTRACER_HEADERS
    include/Utilities.h
    include/Material.h 
    include/Hitable.h 
    include/Sphere.h 
    include/Ray.h 
    include/Scene.h
    include/Camera.h)

set(RAYTRACER_SOURCES
    src/Utilities.cpp
    src/Material.cpp
    src/Sphere.cpp 
     src/Scene.cpp 
     src/Camera.cpp)
add_library(RayTracer ${RAYTRACER_HEADERS} ${RAYTRACER_SOURCES})
target_link_libraries(RayTracer ImageIO)

######################## add executable ##########################

add_executable(${CMAKE_PROJECT_NAME}Main src/main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME}Main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${CMAKE_PROJECT_NAME}Main PRIVATE ImageIO RayTracer)

####################### installing configure ####################

install(TARGETS ${CMAKE_PROJECT_NAME}Main
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)