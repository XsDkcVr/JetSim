cmake_minimum_required(VERSION 3.22)
project(JetSim)

find_package(ROOT CONFIG REQUIRED)

# Set directories
set(PYTHIA8_DIR "/home/pashax/Programs/pythia8310")
set(LHAPDF_DIR "/home/pashax/Programs/LHAPDF")
set(FASTJET_DIR "/home/pashax/Programs/fastjet-install")
#set(PYTHIA8_FLAGS "'.${PYTHIA8_DIR}/bin/pythia8-config --cppflags --libs'")
#add_definitions(${PYTHIA8_FLAGS})


set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR "src")
set(MACRO_DIR "macro")
set(CMAKE_CXX_FLAGS "-Wall -pedantic")
set(CMAKE_VERBOSE_MAKEFILE ON)

# only for IDE auto-completion
file(GLOB MACROSRC ${MACRO_DIR}/*.cpp)
#add_executable(RootMacro ${MACROSRC})

file(GLOB SRCS ${SOURCE_DIR}/*.cpp)
add_executable(JetSim ${SRCS} ${MACRO_DIR})

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
target_link_libraries(JetSim ${ROOT_LIBRARIES} ${PYTHIA_LIB} ${PYTHIA_LHAPDF_LIB} ${LHAPDF_LIB} ${FASTJET_LIB})
target_include_directories(JetSim PRIVATE ${PYTHIA8_DIR}/include ${ROOT_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/include ${LHAPDF_DIR}/include ${FASTJET_DIR}/include)
message(${LHAPDF_LIB})

#target_link_libraries(RootMacro ${ROOT_LIBRARIES} ${LHAPDF_LIB} ${FASTJET_LIB})
#target_include_directories(RootMacro PRIVATE ${ROOT_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/include ${LHAPDF_DIR}/include ${FASTJET_DIR}/include)


