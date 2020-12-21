# cpp-python-shared-memory

This example demonstrates how to use shared memory across C++ and Python. The main idea is the build a Python extention that wraps boost::interprocess. The rest are the same as using C++ shared memory.

## Installation

Build Python extension
```
python setup.py build_ext --inplace
```

Build producer binary
```
g++ -o producer_main producer_main.cc -lboost_system -lpthread -lrt
```

## Run the code 

In a terminal
```
python test_shared_memory.py
```

In another terminal
```
./producer_main
```