cmake_minimum_required(VERSION 3.22)
project(JetSim)

find_package(ROOT CONFIG REQUIRED)

# Set directories
set(PYTHIA8_DIR $ENV{PYTHIA8})        
set(LHAPDF_DIR $ENV{LHAPDF6})
set(FASTJET_DIR $ENV{FASTJET3})

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR "src")
set(CMAKE_CXX_FLAGS "-Wall -pedantic")
set(CMAKE_VERBOSE_MAKEFILE ON)


file(GLOB SRCS ${SOURCE_DIR}/*.cpp)
add_executable(generate_pythia ${SRCS})

# find pythia8 and LHAPDF libraries
find_library(PYTHIA_LIB NAMES pythia8 
                  PATHS ${PYTHIA8_DIR}/lib
                  REQUIRED)
find_library(PYTHIA_LHAPDF_LIB NAMES pythia8lhapdf6 
                  PATHS ${PYTHIA8_DIR}/lib
                  REQUIRED)
find_library(LHAPDF_LIB NAMES LHAPDF 
                  PATHS ${LHAPDF_DIR}/lib
                  REQUIRED)
find_library(FASTJET_LIB NAMES fastjet
		  PATHS ${FASTJET_DIR}/lib
                  REQUIRED)

#target_link_libraries(PromptSim ${LIBS})
target_link_libraries(generate_pythia ${ROOT_LIBRARIES} ${PYTHIA_LIB} ${PYTHIA_LHAPDF_LIB} ${LHAPDF_LIB} ${FASTJET_LIB})
target_include_directories(generate_pythia PRIVATE ${PYTHIA8_DIR}/include ${ROOT_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/include ${LHAPDF_DIR}/include ${FASTJET_DIR}/include)
message(${LHAPDF_LIB})


