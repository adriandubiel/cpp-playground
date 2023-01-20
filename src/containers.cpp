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
#include <forward_list>
#include <utility>

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

  S(const S& s){
    cout << "COPY S() id:" << s.id << endl;
    name = s.name;
    id = s.id;
  }

  S(S&& s) = default;
  S& operator=(S&& other) = default;


  bool operator<(const S &s) const {
    return id < s.id;
  } // needed by for eg. std::set
  bool operator>(const S &s) const {
    return id > s.id;
  } // needed by for eg. std::set

  bool operator==(const S &s) const {
    return s.id == id;
  }

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

static vector<S> vs2{ S{"ydfd", 22}};

int main() {

  vector<int> v1{3, 2, 1, 5, 6, 4, 2, 2, 4, 7};
  array<int, 9> a1{3, 2, 1, 5, 4, 2, 2, 4, 7};
  list<int> l1{3, 2, 1, 5, 4, 2, 2, 4, 7};
  
  forward_list<int> fwd1 {4,3,5,6,41,4,2,7};
  
  fwd1.insert_after(find(fwd1.begin(), fwd1.end(), 41), 42);
  //print(fwd1);
  
  
  /* 
  reverse(v1.begin(), v1.end());
  print(v1);

  print(v1);
  auto itv = find(v1.begin(), v1.end(), 5);
  v1.erase(itv);  
  print(v1);
  v1.erase(remove(v1.begin(), v1.end(), 2), v1.end());
  print(v1);  
  */

  vector<S> vs1{ {"zsd", 3}, {"gds", 5}, {"xds", 5}, {"yfd", 1}};
  vs1.emplace_back(std::move(S{"fds", 6}));
  
  //vs1.erase(find(vs1.begin(), vs1.end(), S{"yfd", 1}));
  vs1.erase(remove_if(vs1.begin(), vs1.end(), [](const S& s) {
    return s.id == 5;
  }), vs1.end());

  print(vs1);

  string str = "ala ma kota";

  str.erase(str.find("ma"), 2);
  print(str);

  //v1.erase()

  //std::sort(vs1.begin(), vs1.end(),[](S a, S b) { return a.id < b.id; });
  //print(vs1);

  // stack<int> s1 {3,2,1,5,4,2,2,4,7};

  std::sort(v1.begin(), v1.end());

  //TestSet();

  return 0;
}
