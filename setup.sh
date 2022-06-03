# !/bin/bash
# script to setup system

# init submodules
git submodule update --init

# install necessary packages
sudo apt-get install cmake
sudo apt-get install libspdlog-dev
