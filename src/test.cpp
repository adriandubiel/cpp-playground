#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

struct Student {
  int id;
  int age;
};

class A {

public:
  A() { std::cout << "A Ctor" << std::endl; }
  ~A() { std::cout << "A Dtor" << std::endl; }

  A(const A &a) { std::cout << "Copy A CTOR" << std::endl; }

  A &operator=(const A &other) {
    std::cout << "operator= A CTOR" << std::endl;
    return *this;
  };

  virtual void vfun() { std::cout << "VFUN A" << std::endl; }

  void fun() { throw "my excp"; }
};

class B : public A {
public:
  virtual void vfun() { std::cout << "VFUN B" << std::endl; }
};

void ex_test() {
  try {
    A a{};

  } catch (const char *e) {
    // std::cout << "Exception: " << e.what() << std::endl;
    std::cout << "Exception " << e << std::endl;
  } catch (std::overflow_error &e) {
    std::cout << "OVF exception " << e.what() << std::endl;
  }
}

int main() {

  std::vector<Student> students{{1, 23}, {2, 21}, {3, 20},
                                {4, 28}, {5, 19}, {6, 25}};

  std::sort(students.begin(), students.end(),
            [](Student s1, Student s2) { return s1.age < s2.age; });

  std::unique_ptr<A> a = std::make_unique<A>();

  std::unique_ptr<A> b = std::make_unique<A>();
  b = std::make_unique<A>();

  std::cout << "finito" << std::endl;

  return 0;
}