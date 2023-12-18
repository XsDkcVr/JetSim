# Requirements
Python 3 (all dependencies are listed in notebook under dir macro).

External packages: [ROOT](https://root.cern/) (w/ python), [Pythia8](https://pythia.org/), [FastJet](https://fastjet.fr/), [LHAPDF6](https://lhapdf.hepforge.org/) (w/ python). To build with [CMake](https://cmake.org/): export install directories in appropriate variables (see CMakeLists.txt).

# Build
Make sure that all directories for external libraries are set up, then

    mkdir build
    cd build
    cmake ../
    cmake --build .
    cd ..

# Run
See pythia_pp.cpp for main program arguments, then run

    ./build/generate_pythia 1000 123 src/pp_settings.cmnd rootfiles/output_tree.root 0  

# Calculate
After generation is complete use notebook under directory macro to get the results.

# Output examples
![ds_dpt](/plots/ds_dpt_num.png)
![ds_dpt](/plots/ds_dy_pythia.png)
