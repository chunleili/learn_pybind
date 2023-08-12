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


struct Pet {
    Pet(const std::string &name) : name(name) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }
    int getAge() const { return age; }
    void setAge(int age_) { age = age_; }
    std::string name;

    // 重载函数
    void set(int age_) { age = age_; }
    void set(const std::string &name_) { name = name_; }

private:
    int age;
};

struct Dog : Pet {
    Dog(const std::string &name) : Pet(name) { }
    std::string bark() const { return "woof!"; }
};



struct PolymorphicPet {
    virtual ~PolymorphicPet() = default;
};

struct PolymorphicDog : PolymorphicPet {
    std::string bark() const { return "woof!"; }
};



struct PetWithEnum {
    enum Kind {
        Dog = 0,
        Cat
    };

    struct Attributes {
        float age = 0;
    };


    PetWithEnum(const std::string &name, Kind type) : name(name), type(type) { }

    std::string name;
    Kind type;
    Attributes attr;
};


PYBIND11_MODULE(mymod, m) {
    //增加docstring（optional）
    m.doc() = "pybind11 example plugin";
    // 绑定一个函数
    m.def("add", &add, "A function which adds two numbers");
    // b=m.add(1, 2)


    // 绑定一个类
    py::class_<SomeClass>(m, "SomeClass")
    .def("multiply", &SomeClass::multiply)
    .def(py::init<float>());
    // a = m.SomeClass(3.0)
    // a.multiply(2.0)


    // 绑定一个变量
    m.attr("the_answer") = 42;
    py::object world = py::cast("World");
    m.attr("what") = world;
    // print(m.the_answer)
    // print(m.what)

    //绑定一个函数，并且显式告知参数名称
    m.def("add", &add, "A function which adds two numbers",
      py::arg("i"), py::arg("j"));
    // print(m.add(i=3, j=2))

    //简化写法
    using namespace pybind11::literals;
    m.def("add2", &add, "i"_a, "j"_a);


    //默认参数
    // regular notation
    m.def("add1", &add, py::arg("i") = 1, py::arg("j") = 2);
    // shorthand
    m.def("add2", &add, "i"_a=1, "j"_a=2);


    // //绑定一个类 Pet
    // py::class_<Pet>(m, "Pet")
    //     .def(py::init<const std::string &>())
    //     .def("setName", &Pet::setName)
    //     .def("getName", &Pet::getName);


    //设置类: 第一个参数只是个临时代称，第二个参数是Python的类名，第三个参数py::dynamic_attr()是开启动态属性（即可以在Python中动态添加属性，会损失一点性能）
    py::class_<Pet> pet(m, "Pet", py::dynamic_attr());
    pet
    .def(py::init<const std::string &>())
    // 设置类的方法
    .def("setName", &Pet::setName)
    .def("getName", &Pet::getName)
    // 设置类的字符串表示
    .def("__repr__", 
        [](const Pet &a) {
            return "<mymod.Pet named '" + a.name + "'>";
        }
    )
    //设置可读写的属性
    .def_readwrite("name", &Pet::name) 
    //通过getset方式设置可读写的私有属性
    .def_property("age", &Pet::getAge, &Pet::setAge);


    // 设置子类
    py::class_<Dog, Pet> petWithSubclass(m, "Dog");
    petWithSubclass.def(py::init<const std::string &>());
    petWithSubclass.def("bark", &Dog::bark);


    // 设置多态：注意，基类必须要至少有一个虚函数才会被认为开启多态。我们设置了一个虚析构函数
    // Same binding code
    py::class_<PolymorphicPet>(m, "PolymorphicPet");
    py::class_<PolymorphicDog, PolymorphicPet>(m, "PolymorphicDog")
        .def(py::init<>())
        .def("bark", &PolymorphicDog::bark);

    // Again, return a base pointer to a derived instance
    m.def("pet_store2", []() { return std::unique_ptr<PolymorphicPet>(new PolymorphicDog); });


    // 设置重载函数
   pet.def("set", static_cast<void (Pet::*)(int)>(&Pet::set), "Set the pet's age")
   .def("set", static_cast<void (Pet::*)(const std::string &)>(&Pet::set), "Set the pet's name");





    py::class_<PetWithEnum> petWithEnum(m, "PetWithEnum");

    petWithEnum.def(py::init<const std::string &, PetWithEnum::Kind>())
        .def_readwrite("name", &PetWithEnum::name)
        .def_readwrite("type", &PetWithEnum::type)
        .def_readwrite("attr", &PetWithEnum::attr);

    py::enum_<PetWithEnum::Kind>(petWithEnum, "Kind")
        .value("Dog", PetWithEnum::Kind::Dog)
        .value("Cat", PetWithEnum::Kind::Cat)
        .export_values();

    py::class_<PetWithEnum::Attributes>(petWithEnum, "Attributes")
        .def(py::init<>())
        .def_readwrite("age", &PetWithEnum::Attributes::age);

}

