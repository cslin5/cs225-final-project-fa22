# README

## Github Organization

The code is split up into different folders and sections based upon the purpose of the code, as well as some of the other files. The actual dataset that pertains to the bus routes exists within the dataset folder. In the documentation folder exists written details for the project proposal and contract. The library folder consists of the edge and vertex structs that are used throughout the code. The src folder contains both the data parsing, which is represented by the Transit files, and the algorithms to run on the graph that are contained within the algorithms file. The test folder contains the information for our test cases, which also includes the example test files that we parse from for the test cases. The results folder contains the printed out results of the algorithms run on our dataset, as well as links to the presentation video, its corresponding slides, and the written report.

## Running Instructions

### Using CMake

Like our other CS225 problems, we are using CMake to compile our code instead of just make. To use this feature, run `mkdir build` in the base directory of the project, followed by `cd build` and `cmake ..`.

```
mkdir build
cd build
cmake ..
```

Now, you can use commands in this build directory to run code from this project.

### How to use the dataset

Our dataset comes from the `dataset` folder and it is called `stop_times.txt`. To run our algorithms in it, you can use the `main.cpp` file and run it with `./main`.

### Running the test suite

The tests were created as we went, so every part of the process has been tested.

We have tested the constructors for Vertex, Edge, Transit, and Algorithm; we have tested the algorithms themselves (`Tarjan()` and `Prim()`) and the DFS (`RouteConnection()`).

To run the tests, run `./test` and the name or tag of the test you want to run, such as `[transit]` or `"Transit Constructor Test 1"`.

```
./test [transit]
./test "Transit Constructor Test 1"
```

If you only use `./test`, all test cases will run.