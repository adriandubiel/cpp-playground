#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

int count = 0;
std::mutex count_mutex;
std::condition_variable cv;

constexpr int items = 10;

void pass(std::unique_lock<std::mutex> lck) { lck.unlock(); }

void producer(void) {
  std::cout << "producer" << std::endl;
  for (int i = 0; i <= items; i++) {
    std::unique_lock<std::mutex> lk(count_mutex);
    count = i;
    lk.unlock();
    cv.notify_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
  }
}

void consumer(void) {
  std::cout << "consumer" << std::endl;


  for (int i = 0; i < items; i++) {
    std::unique_lock<std::mutex> lk(count_mutex);
    cv.wait(lk, []() { return (count != 0); });
    if (count >= items)
      break;
    std::cout << count << " " << std::flush;
    count = 0;
  }
  std::cout << "\n";
}

int main() {
  std::thread t1(producer);
  std::thread t2(consumer);


  t1.join();
  t2.join();

  return 0;
}