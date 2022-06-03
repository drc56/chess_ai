# Save current directory
cwd=$(pwd)

# First build libchess
cd lib/libchess
mkdir build
cd build
cmake ..
make

# Then build actual app
cd $cwd
cmake --configure .
cmake --build .


