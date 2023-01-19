#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

class Spinlock {
  std::atomic_flag flag;

public:
  Spinlock() : flag(ATOMIC_FLAG_INIT) {}

  void lock() {
    while (flag.test_and_set())
      ;
  }

  void unlock() { flag.clear(); }
};

Spinlock spin;
std::mutex mtx{};

void workOnResource() {
  spin.lock();
  // shared resource
  std::cout << "Take resource"
            << "1"
            << "2"
            << "3" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  std::cout << "Work done" << std::endl;
  ;
  spin.unlock();
}

void workOnResource_m() {
  mtx.lock();
  // shared resource
  std::cout << "Take resource"
            << "1"
            << "2"
            << "3" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  std::cout << "Work done" << std::endl;
  ;
  mtx.unlock();
}

int main() {
  std::thread t(workOnResource);
  std::thread t2(workOnResource);

  t.join();
  t2.join();
}
