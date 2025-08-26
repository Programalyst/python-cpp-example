#include <pybind11/pybind11.h>

// A simple function that adds two integers
int add(int i, int j) {
    return i + j;
}

// The pybind11 module definition
PYBIND11_MODULE(sumInt, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("add", &add, "A function which adds two numbers");
}