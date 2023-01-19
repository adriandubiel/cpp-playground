#include <iostream>
#include <memory>

using namespace std;

class A {
  int a;

public:
  explicit A(int val) : a(val) {}
  void print() { cout << "A:" << a << endl; }
  ~A(){ cout << "~A:" << a << endl;}
};

int main() {
  cout << "Hello Ptrs" << endl;

  unique_ptr<int[]> arr1(new int[5]{3});
  arr1[4] = 10;
  cout << arr1[4] << endl;

  unique_ptr<A> a1(new A{3});
  unique_ptr<A> a2 = std::move(a1);

  a2->print();


  return 0;
}
