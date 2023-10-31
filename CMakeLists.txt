cmake_minimum_required(VERSION 3.25)
project(JetSim)

find_package(ROOT CONFIG REQUIRED)

set(PYTHIA8_DIR "/home/pasha/Programs/pythia8309")
set(LHAPDF_DIR "/home/pasha/Programs/LHAPDF")
set(FASTJET_DIR "/home/pasha/Programs/fastjet-install")
set(CMAKE_VERBOSE_MAKEFILE ON)
#set(PYTHIA8_FLAGS "'.${PYTHIA8_DIR}/bin/pythia8-config --cppflags --libs'")
#add_definitions(${PYTHIA8_FLAGS})


set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR "src")
set(CMAKE_CXX_FLAGS "-Wall -pedantic")
file(GLOB SRCS ${SOURCE_DIR}/*.cpp)
add_executable(JetSim ${SRCS})

# find pythia8 and LHAPDF libraries
find_library(PYTHIA_LIB NAMES pythia8 
                  PATHS ${PYTHIA8_DIR}/lib
                  REQUIRED)
find_library(LHAPDF_LIB NAMES LHAPDF 
                  PATHS ${LHAPDF_DIR}/lib
                  REQUIRED)
find_library(FASTJET_LIB NAMES fastjet
		  PATHS ${FASTJET_DIR}/lib
                  REQUIRED)

#target_link_libraries(PromptSim ${LIBS})
target_link_libraries(JetSim ${ROOT_LIBRARIES} ${PYTHIA_LIB} ${LHAPDF_LIB} ${FASTJET_LIB})
target_include_directories(JetSim ${PYTHIA8_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/include ${LHAPDF_DIR}/include ${FASTJET_DIR}/include)
message(${LHAPDF_LIB})


