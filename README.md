# cpp_template

how to build (on ubuntu):

step one: add dependency
```
sudo apt install libfmt-dev
```
step two: build

if you want to build with google test:
```
git submodule update --init --recursive
```
```
mkdir build && cd build 
cmake .. -DTEST_OPTION=ON 
make -j4
```

if you do not want to build with google test:
```
mkdir build && cd build 
cmake .. -DTEST_OPTION=OFF 
make -j4
```

step three: run the program

`./main` at build/bin to run main program.

`./tests` at build/tests to run tests.

you can also run `make test` to run tests.

you can use `make install` to get dynamic link library at install.
