#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

std::vector<int> mySharedWork;
std::mutex mutex_;
std::condition_variable condVar;

bool dataReady{false};

void waitingForWork() {
  std::cout << "Waiting " << std::endl;
  std::unique_lock<std::mutex> lck(mutex_);

  condVar.wait(lck, [] { return dataReady; });
  mySharedWork[1] = 2;
  std::cout << "Work done " << std::endl;
}

void setDataReady() {
  mySharedWork = {1, 0, 3};

  std::lock_guard<std::mutex> lck(mutex_);
  dataReady = true;

  std::cout << "Data prepared" << std::endl;
  condVar.notify_one();
}

int main() {

  std::cout << std::endl;

  std::thread t1(waitingForWork);
  std::thread t2(setDataReady);

  t1.join();
  t2.join();

  for (auto v : mySharedWork) {
    std::cout << v << " ";
  }

  std::atomic<bool> atflag;
  std::atomic_bool atb;
  std::atomic_flag af;

  class A {
    int x;

  public:
    void g() volatile {}
    void f() volatile {
      x = 3;
      g();
    }
  };

  std::atomic<A> atA{};
  static_cast<A>(atA).f();

  std::cout << "\n\n";
}
