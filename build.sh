# Save current directory
cwd=$(pwd)

# First build libchess
cd lib/libchess
mkdir build
cd build
cmake ..
make

cd $cwd
cmake --configure .
cmake --build .


