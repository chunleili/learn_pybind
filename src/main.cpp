#include <pybind11/pybind11.h>
#include <iostream>
namespace py = pybind11;


int add(int i, int j) {
    return i + j;
}

//绑定一个类
class SomeClass
{
    float scale;
public:
    SomeClass(float scale_) : scale(scale_) { };
    float multiply(float input) {
        float res =  scale * input;
        std::cout<<"res:"<<res<<std::endl;
        return res;
    }
};


PYBIND11_MODULE(mymod, m) {
    m.doc() = "pybind11 example plugin";
    m.def("add", &add, "A function which adds two numbers");

    py::class_<SomeClass>(m, "SomeClass")
    .def("multiply", &SomeClass::multiply)
    .def(py::init<float>());


    m.attr("the_answer") = 42;
    py::object world = py::cast("World");
    m.attr("what") = world;
}

