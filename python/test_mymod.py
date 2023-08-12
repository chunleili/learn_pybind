import mymod as m

b=m.add(1, 2)
print(b)

a = m.SomeClass(3.0)
a.multiply(2.0)

print(m.the_answer)
print(m.what)

print(m.add2(i=3, j=2))

print("默认参数 ",m.add2())

help(m.add2)



p = m.Pet("Molly")
print(p)
print(p.getName())
p.setName("Molly2")
print(p.getName())


print("可读写属性 ",p.name)
p.name="Molly3"
print(p.name)

p.age = 10  
print("通过setget读写私有属性 ",p.age)

# 开启动态属性py::dynamic_attr()
p.color = "red"
print("color ",p.color)



# 增加子类
dog = m.Dog("Ally")
print(dog.bark())


# 具有多态性的子类
p_with_poly = m.pet_store2()
print(type(p_with_poly))
print(p_with_poly.bark())


# 重载函数
p.set(12)
print(p.age)



# 带有枚举的类
pp = m.PetWithEnum("Molly", m.PetWithEnum.Cat)
print("茉莉是一只",pp.type)

print(f"都有哪些种类？\n{m.PetWithEnum.Kind.__members__}")