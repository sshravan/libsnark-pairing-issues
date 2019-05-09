
To compile this, start by recursively fetching the dependencies.
```
git clone --recursive git@github.com:sshravan/test.git
cd test
git submodule update --init --recursive
mkdir -p build && cd build
cd .. && rm -rf build && mkdir build && cd build && cmake .. && make
make
./src/main
# Change the Cmake file to swap curves.
```
