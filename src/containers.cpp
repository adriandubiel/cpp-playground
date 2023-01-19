#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>
#include <ostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

template <typename T> void print(const T &container) {
  for (const auto &i : container) {
    cout << i << " ";
  }
  cout << endl;
}

template <typename T> void printVal(T a) { cout << "val: " << a << endl; }

struct S {
  string name;
  int id;

  S(const string &name, int id) : name(name), id(id) {
    cout << "S() id:" << id << endl;
  }

  bool operator<(const S &s) const {
    return id < s.id;
  } // needed by for eg. std::set
  bool operator>(const S &s) const {
    return id > s.id;
  } // needed by for eg. std::set

  friend ostream &operator<<(ostream &o, const S &s) { return o << s.name; }
};

/* Set */
static void TestSet() {
  cout << __FUNCTION__ << endl;

  set<S, std::greater<>> s{
      {"tom", 3}, {"john", 1}, {"mark", 6}, {"tony", 4}, {"tony2", 4}};

  //s.insert(S{"fds", 24});
  s.emplace<S>({"fds", 24});

  print(s);
}

class BF;

class AF{
    public:

    AF(){
        bf.b = 3;
    }

    BF bf;
};

class BF{
    friend class AF;
    int b;
};

int main() {



  vector<int> v1{3, 2, 1, 5, 4, 2, 2, 4, 7};
  array<int, 9> a1{3, 2, 1, 5, 4, 2, 2, 4, 7};
  list<int> l1{3, 2, 1, 5, 4, 2, 2, 4, 7};

  //vector<S> vs1{{"asd", 3}, {"fds", 2}, {"bf", 1}};
  //std::sort(vs1.begin(), vs1.end(), [](S a, S b) { return a.id < b.id; });
  //print(vs1);

  // stack<int> s1 {3,2,1,5,4,2,2,4,7};

  std::sort(v1.begin(), v1.end());

  TestSet();

  return 0;
}
